// #############################################################################
//
// Copyright (C) 2024 STARRYSTONETECH - http://www.starrystonetech.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of STARRYSTONETECH nor the names of its contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// #############################################################################

//
// Included Files
//
#include "board.h"

#define EPWM_TIMER_TBPRD       50UL
#define MIN_HRPWM_DUTY_PERCENT 4.0
#define MIN_HRPWM_PRD_PERCENT   0
//
// Defines
//
#define LAST_EPWM_INDEX_FOR_EXAMPLE 2
#define EPWM_TBCLK 100e6

//
// Globals
//
float32_t dutyFine = 0;
float32_t freqFine = 0;
float32_t periodFine = 0;

volatile uint32_t ePWM[] = { 0, myEPWM1_BASE};

uint32_t cap2Count[CAP_VALUE_SUM];
uint32_t cap3Count[CAP_VALUE_SUM];
uint32_t cap4Count[CAP_VALUE_SUM];

uint8_t dmaDoneFlag = 0;

uint32_t absCountOn1, absCountOn2;
uint32_t absCountOff1, absCountOff2;
uint32_t absCountPeriod1, absCountPeriod2;

float32_t onTime1 = 0, onTime2 = 0;
float32_t offTime1 = 0, offTime2 = 0;
float32_t period1 = 0, period2 = 0;

uint32_t ecapIntCount;
uint16_t hrcapIntCount   = 0;
uint16_t ecapIntCalCount = 0;
uint16_t calStatus       = 0;

HRCAPCAL_CalResultObj hrcapCalResult;

uint64_t totalCount    = 0;
float32_t inputFreqkHz = 0;
float32_t inputDuty    = 0;

int Position[256] = { 0 };
int HRMSTEP       = 0;

//
// Function Prototypes
//

static int CheckPosition(int *position, u8 hhr_en)
{
    char SampleSequence[512] = { 0 };
    int num                  = 0;
    unsigned int *p;

    if (hhr_en)
        p = (unsigned int *)SFOHHR_BASE;
    else
        p = (unsigned int *)SFO_BASE;

    for (int i = 0; i < 16; i++)
    {
        unsigned int data = *p;
        for (int j = 31; j >= 0; j--)
        {
            if (hhr_en)
                SampleSequence[i * 32 + j] = (data >> (j)) & 1;
            else
                SampleSequence[i * 32 + (31 - j)] = (data >> (j)) & 1;
        }
        p++;
    }

    for (int i = 1; i < 512; i++)
    {
        if (SampleSequence[i] == SampleSequence[i - 1])
        {
            position[num] = (float)(i + 1);
            if (num)
            {
                if (position[num] == (position[num - 1] + 1))
                {
                    position[num - 1] = (float)(i + 1);
                    position[num]     = 0;
                }
                else
                    num++;
            }
            else
                num++;
        }
    }
    return num;
}

static int Liner(int *average, int num)
{
    int x[256]   = { 0 };
    float sum_x2 = 0.0, sum_y = 0.0, sum_x = 0.0, sum_xy = 0.0;
    float k = 0.0;
    for (int i = 0; i < num; i++)
    {
        x[i] = i + 1;
    }
    for (int i = 0; i < num; ++i)
    {
        sum_x2 += x[i] * x[i];
        sum_y += average[i];
        sum_x += x[i];
        sum_xy += x[i] * average[i];
    }
    k           = (num * sum_xy - sum_x * sum_y) / (num * sum_x2 - sum_x * sum_x);
    int HRMSTEP = (int)(2 * k + 0.5f);
    return HRMSTEP;
}

void SFO(u8 hhr_en)
{
    volatile struct HRCAL_REGS *sfo;

    if (hhr_en)
        sfo = (volatile struct HRCAL_REGS *)(SFOHHR_BASE);
    else
        sfo = (volatile struct HRCAL_REGS *)(SFO_BASE);

    sfo->HRCAL.bit.SAMPLE_EN = 0;
    sfo->HRCAL.bit.CAL_DONE  = 0;
    sfo->HRCAL.bit.CAL_EN    = 1;
    for (int i = 0; i < 10; i++)
    {
        __builtin_dsp_nop();
    }
    sfo->HRCAL.bit.SAMPLE_EN = 1;
    if (sfo->HRCAL.bit.SAMPLE_VALID == 1)
    {
        sfo->HRCAL.bit.CAL_EN = 0;

        int num = CheckPosition(Position, hhr_en);
        HRMSTEP = Liner(Position, num);

        sfo->HRCAL.bit.HRMSTEP_TEMP = HRMSTEP;
        sfo->HRCAL.bit.CAL_DONE     = 1;
    }
}

//
// Main
//
int main(void)
{
    uint16_t i = 0;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize the EPWM GPIO Pins and change the XBAR inputs from using GPIO0
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    SFO(0);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    dutyFine = 43.5;  //%
    freqFine = 1000;  //单位khz

    while (1)
    {
        for (i = 1; i < LAST_EPWM_INDEX_FOR_EXAMPLE; i++)
        {
            //设置高精度周期
            periodFine = EPWM_TBCLK / freqFine /1000;
            float32_t count = ((periodFine - 1) * 256);
            uint32_t compCount = count;
            HRPWM_setTimeBasePeriod(ePWM[i], compCount);

            //设置高精度占空比
            count = (dutyFine * (float32_t)(periodFine * 256))/100;
            compCount = (count);
            HRPWM_setCounterCompareValue(ePWM[i], HRPWM_COUNTER_COMPARE_A, compCount);
            HRPWM_setCounterCompareValue(ePWM[i], HRPWM_COUNTER_COMPARE_B, compCount);
        }

        if (dmaDoneFlag)
        {
            uint32_t cap3CountSum = 0;
            uint32_t cap4CountSum = 0;

            dmaDoneFlag = 0;

            //
            //处理数据
            //
            for(uint8_t i = 0; i < CAP_VALUE_SUM; i++)
            {
                cap3CountSum += cap3Count[i];
                cap4CountSum += cap4Count[i];
            }

            absCountOn2 = cap4CountSum / CAP_VALUE_SUM;
            absCountOff2 = cap3CountSum / CAP_VALUE_SUM;
            absCountPeriod2 = (cap4CountSum + cap3CountSum) / CAP_VALUE_SUM;

            //
            // Convert counts to nanoseconds using the scale factor
            //
            onTime2 = HRCAP_convertEventTimeStampNanoseconds(absCountOn2,
                                                       hrcapCalResult.scaleFactor);
            offTime2 = HRCAP_convertEventTimeStampNanoseconds(absCountOff2,
                                                       hrcapCalResult.scaleFactor);
            period2 = HRCAP_convertEventTimeStampNanoseconds(absCountPeriod2,
                                                       hrcapCalResult.scaleFactor);

            if (period2 != 0 && offTime2 != 0)
            {
                //
                // Convert from nS to kHz
                //
                inputFreqkHz = 1 / (period2 / 1000000);
                inputDuty = (offTime2 / period2) * 100;
            }

            //
            //重新启动DMA
            //
            DMA_startChannel(3);
            DMA_startChannel(4);

        }
    }
}

//
// INT_myECAP0_HR_ISR -  HRCAP Calibration ISR
//
__interrupt void INT_myECAP0_HR_ISR(void)
{
    hrcapIntCount++;

    //
    // Get calibration interrupt sources
    //
    calStatus = HRCAP_getCalibrationFlags(myECAP0_HR_BASE);

    //
    // Get calibration clock counts
    //
    hrcapCalResult.hrclkCount = HRCAP_getCalibrationClockPeriod(myECAP0_HR_BASE,
                                            HRCAP_CALIBRATION_CLOCK_HRCLK);
    hrcapCalResult.sysclkcount = HRCAP_getCalibrationClockPeriod(myECAP0_HR_BASE,
                                            HRCAP_CALIBRATION_CLOCK_SYSCLK);

    //
    // The following options are possible
    //   - HRCALCAL_STATUS_DONE_ISR
    //   - HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR
    //   - Software forced generated interrupt
    //
    if(HRCALCAL_STATUS_DONE_ISR == calStatus)
    {
        //
        // Calculate scale factor
        //
        hrcapCalResult.scaleFactor = HRCAP_getScaleFactor(myECAP0_HR_BASE);
    }
    else if (HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR == calStatus)
    {
        //
        // Calibration done with an overflow. Determine which counter has
        // overflowed
        //
        if(hrcapCalResult.hrclkCount > hrcapCalResult.sysclkcount)
        {
            //
            // HRCLK has overflowed
            //
            hrcapCalResult.scaleFactor = hrcapCalResult.sysclkcount *
                                         HRCAPCAL_INV_OVERFLOW;
        }
        else if(hrcapCalResult.hrclkCount < hrcapCalResult.sysclkcount)
        {
            //
            // SYSCLK has overflowed
            //
            hrcapCalResult.scaleFactor = HRCAPCAL_OVERFLOW /
                                         hrcapCalResult.hrclkCount;
        }
        else
        {
            //
            // Both SYSCLK and HRCLK have overflowed
            //
            hrcapCalResult.scaleFactor = 1.0f;
        }
    }
    else
    {
        //
        // Software generated interrupt
        //
    }

    ECAP_reArm(myECAP0_BASE);
    ECAP_resetCounters(myECAP0_BASE);

    //
    // Clear the interrupts
    //
    HRCAP_clearCalibrationFlags(myECAP0_HR_BASE, calStatus);

    //
    // Acknowledge the PIE interrupt group
    //
    Interrupt_clearACKGroup(INT_myECAP0_HR_INTERRUPT_ACK_GROUP);
}


//
//DMA搬运完成中断，DMA transfer长度最大支持512，在中断中再次启动DMA搬运
//
__interrupt void dmach4ISR(void)
{
    u32 status = DmaCh4Regs.INTSTATUS;
    if (status & DMA_IRQ_DMA_TRF)
    {
        DmaCh3Regs.DAR = (u32)cap3Count;
        DmaCh4Regs.DAR = (u32)cap4Count;

        dmaDoneFlag = 1;
    }
}

//
//10s触发一次，在timer中断种调用校准函数SFO
//

uint8_t time_tick = 0;
__interrupt void timer0_isr(void)
{
    /* timer Tick add */
    time_tick++;
    SFO(0);
}
