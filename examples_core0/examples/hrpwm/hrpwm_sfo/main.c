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

#define EPWM_TIMER_TBPRD       100UL
#define MIN_HRPWM_DUTY_PERCENT 4.0
#define MIN_HRPWM_PRD_PERCENT   0.2
//
// Defines
//
#define LAST_EPWM_INDEX_FOR_EXAMPLE 2

//
// Globals
//

float32_t dutyFine = MIN_HRPWM_DUTY_PERCENT;
float32_t periodFine = MIN_HRPWM_PRD_PERCENT;

volatile uint32_t ePWM[] = { 0, myEPWM1_BASE};


//
// Function Prototypes
//

static int CheckPosition(float *position)
{
    char SampleSequence[512] = { 0 };
    int num                  = 0;
    unsigned int *p          = (unsigned int *)(SFO_BASE);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 31; j >= 0; j--)
        {
            SampleSequence[i * 32 + (31 - j)] = ((*p) >> (j)) & 1;
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

static int Liner(float *average, int num)
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

void SFO(void)
{
    volatile struct HRCAL_REGS *sfo = (volatile struct HRCAL_REGS *)(SFO_BASE);
    sfo->HRCAL.bit.SAMPLE_EN        = 0;
    sfo->HRCAL.bit.CAL_DONE         = 0;
    sfo->HRCAL.bit.CAL_EN           = 1;
    for (int i = 0; i < 10; i++)
    {
        __builtin_dsp_nop();
    }
    sfo->HRCAL.bit.SAMPLE_EN = 1;
    if (sfo->HRCAL.bit.SAMPLE_VALID == 1)
    {
        sfo->HRCAL.bit.CAL_EN       = 0;
        float Position[256]         = { 0 };
        int num                     = CheckPosition(Position);
        int HRMSTEP                 = Liner(Position, num);
//        sfo->HRCAL.bit.HRMSTEP_TEMP = HRMSTEP;
//        sfo->HRCAL.bit.CAL_DONE     = 1;
        for (uint8_t i = 1; i < LAST_EPWM_INDEX_FOR_EXAMPLE; i++)
        {
            HRPWM_setMEPStep(ePWM [i], HRMSTEP);
        }
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

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    dutyFine = 40.5; //占空比40.5%
    periodFine = 0.5;

    for (i = 1; i < LAST_EPWM_INDEX_FOR_EXAMPLE; i++)
    {
        //
        //占空比
        //
        uint16_t intpart    = (dutyFine / 100) * EPWM_TIMER_TBPRD;
        float32_t fractpart = (dutyFine / 100) * EPWM_TIMER_TBPRD - intpart;

        // write CMPAHR and CMPBHR
        uint8_t compCount = fractpart * 256;
        HRPWM_setCounterCompareValue(ePWM [i], HRPWM_COUNTER_COMPARE_A, compCount);
        HRPWM_setCounterCompareValue(ePWM[i], HRPWM_COUNTER_COMPARE_B, compCount);

        // write CMPA and CMPB
        EPWM_setCounterCompareValue(ePWM[i], EPWM_COUNTER_COMPARE_A, intpart);
        EPWM_setCounterCompareValue(ePWM[i], EPWM_COUNTER_COMPARE_B, intpart);

        //
        //周期
        //
        float32_t count = ((EPWM_TIMER_TBPRD-1) << 8UL) + (float32_t)(periodFine * 256);
        HRPWM_setTimeBasePeriod(ePWM [i], (uint32_t)count);


    }

    while(1)
    {
        SFO();
        DEVICE_DELAY_US(1000000);
    }

}
