//#############################################################################
//
// FILE:   hrpwm_ex3_prdupdown_sfo.c
//
// TITLE:  HRPWM Period Control.
//
//! \addtogroup driver_example_list
//! <h1>HRPWM Period Control</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! for high-resolution period with ePWM in Up-Down count mode
//! due to the HRPWM control extension of the respective ePWM module.
//!
//! This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library V8 functions:
//!
//! \b int \b SFO(); \n
//! - updates MEP_ScaleFactor dynamically when HRPWM is in use
//! - updates HRMSTEP register (exists only in EPwm1Regs register space)
//!   with MEP_ScaleFactor value
//! - returns 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!   (Auto-conversion may not function properly under this condition)
//! - returns 1 when complete for the specified channel
//! - returns 0 if not complete for the specified channel
//!
//! This example is intended to explain the HRPWM capabilities. The code can be
//! optimized for code efficiency. Refer to TI's Digital power application
//! examples and TI Digital Power Supply software libraries for details.
//!
//! \b External \b Connections \n
//!  - Monitor ePWM1/2/3/4 A/B pins on an oscilloscope.
//
//#############################################################################
//
//
// $Copyright:
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
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
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
// $
//#############################################################################
//
// Included Files
//
#include "board.h"

//
// Defines
//
#define EPWM_TIMER_TBPRD    20UL
#define LAST_EPWM_INDEX_FOR_EXAMPLE    5
#define MIN_HRPWM_PRD_PERCENT   0.2

//
// Globals
//

float32_t periodFine = MIN_HRPWM_PRD_PERCENT;
uint16_t status;

int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO() function.

volatile uint32_t ePWM[] =
    {0, myEPWM1_BASE, myEPWM2_BASE, myEPWM3_BASE, myEPWM4_BASE};

int Position[256] = { 0 };
int HRMSTEP       = 0;

//
// Function Prototypes
//
void error(void);

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
    // Initialize EPWM GPIOs and change XBAR inputs from using GPIO0
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

    for(;;)
    {
         for(periodFine = MIN_HRPWM_PRD_PERCENT; periodFine < 0.9; periodFine += 0.01)
         {
             DEVICE_DELAY_US(1000);
             for(i=1; i<LAST_EPWM_INDEX_FOR_EXAMPLE; i++)
             {
                 float32_t count = ((EPWM_TIMER_TBPRD) << 8UL) + (float32_t)(periodFine * 256);
                 uint32_t compCount = count;
                 HRPWM_setTimeBasePeriod(ePWM[i], compCount);
             }

             SFO(0);
         }
     }
}

//
// error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}
