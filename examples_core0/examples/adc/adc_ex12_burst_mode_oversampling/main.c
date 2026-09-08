// #############################################################################
//
//  FILE:   adc_ex12_burst_mode_oversampling.c
//
//  TITLE:  ADC burst mode oversampling example
//
//! \addtogroup driver_example_list
//! <h1>ADC Burst Mode Oversampling</h1>
//!
//! This example is an ADC oversampling example implemented with software. The
//! ADC SOCs are configured in burst mode, triggered by the ePWM SOC A event
//! trigger.
//!
//! \b External \b Connection \n
//!  - A2
//!
//! \b Watch \b Variables \n
//! - \b lv_results - Array of digital values measured on pin A2 (oversampling
//!                 is configured by Oversampling_Amount)
//!
////#############################################################################
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Macros and Enumerations
//
#define DO_TOGGLE 0
typedef enum
{
    Baseline         = 0, //!< No oversampling
    X2_Oversampling  = 1, //!< 2X oversampling
    X4_Oversampling  = 2, //!< 4X oversampling
    X8_Oversampling  = 3, //!< 8X oversampling
    X16_Oversampling = 4, //!< 16X oversampling
} Oversampling_Amount;

//
// Global Variables
//
uint16_t acc;
uint16_t numBins         = 8192;
volatile uint16_t nloops = 0;
volatile uint16_t *lv_results;

// Adjust the Oversampling_Amount variable to change the amount of oversampling
// according to application requirements.
Oversampling_Amount ovrsmplAmt = X2_Oversampling;

//
// Functions
//
__interrupt void INT_myADC0_1_ISR(void);
void initEPWM();
//
// Main
//
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Set up ADCs:
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    //
    // Burst mode configuration:
    // 1 burst of 16 conversions (SOC0 - SOC15) with equal priority
    //
    // Burst mode trigger is EPWM1 SOCA. Select the channels to be
    // converted and configure the S+H duration
    //
    Board_init();

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    initEPWM();
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    //
    // Initialize memory address for results table
    //
    lv_results = (uint16_t *)0xC000;

    //
    // Debug Timing of ePWM and SOC conversions
    //
#if (DO_TOGGLE == 1)
    SysCtl_enableExtADCSOCSource(
        SYSCTL_ADCSOC_SRC_PWM1SOCA); // Routes ePWM SOCA trigger to external pin
    GPIO_setPinConfig(GPIO_8_ADCSOCAO);
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_STD /*GPIO_PIN_TYPE_PULLUP*/);
    GPIO_setPinConfig(GPIO_7_GPIO7);
    GPIO_setDirectionMode(7, GPIO_DIR_MODE_OUT);
    GPIO_writePin(0, 0);
#endif

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Start ePWM1, enabling SOCA and putting the counter in up-count mode
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

    while (1)
        ;
}

//
// Function to configure ePWM1 to generate the SOC.
//
void initEPWM(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //
    // Set the compare A value to 1000 and the period to 1999
    // Assuming ePWM clock is 100MHz, this would give 50kHz sampling
    // 50MHz ePWM clock would give 25kHz sampling, etc.
    // The sample rate can also be modulated by changing the ePWM period
    // directly (ensure that the compare A value is less than the period).
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 1000);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 1999);

    //
    // Set the local ePWM module clock divider to /1
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    //
    // Freeze the counter
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// INT_myADC0_1_ISR - ADC A Interrupt Burst Mode ISR
// Interrupt performs oversampling calculation based on oversampling factor
//
__interrupt void INT_myADC0_1_ISR(void)
{
    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

    //
    // Debug Timing of ePWM and SOC conversions
    //
#if (DO_TOGGLE == 1)
    GPIO_togglePin(myGPIO0);
#endif

    //
    // Accumulate SOC results (store only 1 value per burst)
    //
    if (ovrsmplAmt == Baseline)
    {
        //
        // 1X Oversampling
        //
        lv_results[nloops++] = ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0);
    }
    else if (ovrsmplAmt == X2_Oversampling)
    {
        //
        // 2X Oversampling
        //
        lv_results[nloops++] = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1));
    }
    else if (ovrsmplAmt == X4_Oversampling)
    {
        //
        // 4X Oversampling
        //
        lv_results[nloops++] = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3));
    }
    else if (ovrsmplAmt == X8_Oversampling)
    {
        //
        // 8X Oversampling
        //
        lv_results[nloops++] = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER4)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER5)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER6)
                                + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER7));
    }
    else if (ovrsmplAmt == X16_Oversampling)
    {
        //
        // 16X Oversampling
        //
        acc                = (ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER2)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER3)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER4)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER5)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER6)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER7)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER8)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER9)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER10)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER11)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER12)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER13)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER14)
               + ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER15));
        lv_results[nloops] = acc;
        nloops++;
    }

    //
    // Check if overflow has occurred
    //
    if (true == ADC_getInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    }

    //
    // Check if all results are stored
    //
    if (nloops >= numBins)
    {
        //
        // Disable ADC interrupt
        //
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
        ESTOP0;
    }

    //
    // Debug Timing of ePWM and SOC conversions
    //
#if (DO_TOGGLE == 1)
    GPIO_togglePin(myGPIO0);
#endif

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// End of file
//
