//#############################################################################
//
// FILE:   epwm_ex9_dma.c
//
// TITLE:  ePWM Using DMA.
//
//! \addtogroup driver_example_list
//! <h1>ePWM DMA</h1>
//!
//! This example configures ePWM1 and DMA as follows:
//!  - ePWM1 is set up to generate PWM waveforms
//!  - DMA1 is set up to update the CMPAHR, CMPA, CMPBHR and CMPB every period
//!    with the next value in the configuration array. This allows the user to
//!    create a DMA enabled fifo for all the CMPx and CMPxHR registers to
//!    generate unconventional PWM waveforms.
//!  - DMA2 is set up to update the TBPHSHR, TBPHS, TBPRDHR and TBPRD every
//!    period with the next value in the configuration array.
//!  - Other registers such as AQCTL can be controlled through the DMA as well
//!    by following the same procedure. (Not used in this example)
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//!
//! \b Watch \b Variables \n
//! - None.
//
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

#define EPWM_TIMER_TBPRD    20000UL

//
// Defines
//
#define BURST       4              // 4 words per transfer
#define TRANSFER    4              // 4 transfers (different configs)


DMA_LLI lli_1;
DMA_LLI lli_2;
DMA_LLI lli_3;
DMA_LLI lli_4;
DMA_LLI lli_5;
DMA_LLI lli_6;
DMA_LLI lli_7;
DMA_LLI lli_8;

//
// Globals
//

uint16_t phasePeriodConfigs[TRANSFER*BURST] = {
//  TBPHSHR ,   TBPHS   ,  TBPRDHR ,   TBPRD,
    9  << 8 ,    17U    ,  13 << 8 ,   2000U,
    10 << 8 ,    18U    ,  14 << 8 ,   4000U,
    11 << 8 ,    19U    ,  15 << 8 ,   6000U,
    12 << 8 ,    20U    ,  16 << 8 ,   8000U,
};

uint16_t compareConfigs[TRANSFER*BURST] = {
//  CMPAHR  ,   CMPA   ,   CMPBHR  ,   CMPB ,
    1 << 8  ,  1001U   ,   5 << 8  ,   1000U,
    2 << 8  ,  2001U   ,   6 << 8  ,   2000U,
    3 << 8  ,  3001U   ,   7 << 8  ,   3000U,
    4 << 8  ,  4001U   ,   8 << 8  ,   4000U,
};


//
// Function Prototypes
//
void initDMA(void);
void initEPWM(uint32_t base);

__interrupt void epwm1ISR(void);

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
    // Assign the interrupt service routines to ePWM interrupts
    //
    Interrupt_register(INT_EPWM1, &epwm1ISR);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);

    //
    // Configure EPWM and Input X-BAR Pins
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initDMA();
    initEPWM(myEPWM1_BASE);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


    // Enable ePWM interrupts
    //
    Interrupt_enable(INT_EPWM1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    EALLOW;
    DMA_startChannel(1);
    DMA_startChannel(2);

    //
    // IDLE loop. Just sit and loop forever (optional):
    //

    for(;;)
    {

    }
}


//
// DMA setup channels.
//
void initDMA()
{
    // DMA channel 1 config
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

    DMA_ConfigParams dconfig = { 0 };

    dconfig.srcAddr         = (u32)compareConfigs;
    dconfig.destAddr        = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_CMPA);
    dconfig.srcWidth        = DMA_TRANS_WIDTH_16;
    dconfig.destWidth       = DMA_TRANS_WIDTH_16;
    dconfig.srcMsize        = DMA_MSIZE_4;
    dconfig.destMsize       = DMA_MSIZE_4;
    dconfig.blockSize       = 3;
    dconfig.srcHSInterface  = DMA_TRIGGER_MEM;
    dconfig.destHSInterface = DMA_TRIGGER_EPWM1SOCA;
    dconfig.srcInc          = DMA_INC_TYPE_NO_CHANGE;
    dconfig.destInc         = DMA_INC_TYPE_NO_CHANGE;
    dconfig.srcMultblk      = DMA_MBLK_TYPE_LL;
    dconfig.destMultblk     = DMA_MBLK_TYPE_LL;

    DMA_initController();
    DMA_configChannel(DMA_CH1_BASE, &dconfig);

    // create initial LLI
    // 用链表实现将比较值搬到对应寄存器，一次触发搬运四个值，搬运四个之后跳到下一个链表，目标地址回绕，源地址递增到下一组
    lli_1.SAR                              = (u32)compareConfigs;
    lli_1.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_CMPA);
    lli_1.BLOCK_TS                         = 3;
    lli_1.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_1.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_1.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_1.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_1.CTL_H.bit.ARLEN_EN               = 1;
    lli_1.CTL_H.bit.ARLEN                  = 0;
    lli_1.CTL_H.bit.AWLEN_EN               = 1;
    lli_1.CTL_H.bit.AWLEN                  = 0;
    lli_1.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_1.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_1.LLP.all                          = (u32)&lli_2;

    lli_2.SAR                              = (u32)&compareConfigs[4];
    lli_2.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_CMPA);
    lli_2.BLOCK_TS                         = 3;
    lli_2.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_2.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_2.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_2.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_2.CTL_H.bit.ARLEN_EN               = 1;
    lli_2.CTL_H.bit.ARLEN                  = 0;
    lli_2.CTL_H.bit.AWLEN_EN               = 1;
    lli_2.CTL_H.bit.AWLEN                  = 0;
    lli_2.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_2.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_2.LLP.all                          = (u32)&lli_3;

    lli_3.SAR                              = (u32)&compareConfigs[8];
    lli_3.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_CMPA);;
    lli_3.BLOCK_TS                         = 3;
    lli_3.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_3.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_3.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_3.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_3.CTL_H.bit.ARLEN_EN               = 1;
    lli_3.CTL_H.bit.ARLEN                  = 0;
    lli_3.CTL_H.bit.AWLEN_EN               = 1;
    lli_3.CTL_H.bit.AWLEN                  = 0;
    lli_3.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_3.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_3.LLP.all                          = (u32)&lli_4;

    lli_4.SAR                              = (u32)&compareConfigs[12];
    lli_4.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_CMPA);;
    lli_4.BLOCK_TS                         = 3;
    lli_4.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_4.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_4.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_4.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_4.CTL_H.bit.ARLEN_EN               = 1;
    lli_4.CTL_H.bit.ARLEN                  = 0;
    lli_4.CTL_H.bit.AWLEN_EN               = 1;
    lli_4.CTL_H.bit.AWLEN                  = 0;
    lli_4.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_4.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_4.LLP.all                          = (u32)&lli_1;
    DmaCh1Regs.LLP.all                    = (u32)&lli_1;

    // DMA channel 2 config

    dconfig.srcAddr         = (u32)phasePeriodConfigs;
    dconfig.destAddr        = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_TBPHS);
    dconfig.srcWidth        = DMA_TRANS_WIDTH_16;
    dconfig.destWidth       = DMA_TRANS_WIDTH_16;
    dconfig.srcMsize        = DMA_MSIZE_4;
    dconfig.destMsize       = DMA_MSIZE_4;
    dconfig.blockSize       = 3;
    dconfig.srcHSInterface  = DMA_TRIGGER_MEM;
    dconfig.destHSInterface = DMA_TRIGGER_EPWM1SOCA;
    dconfig.srcInc          = DMA_INC_TYPE_NO_CHANGE;
    dconfig.destInc         = DMA_INC_TYPE_NO_CHANGE;
    dconfig.srcMultblk      = DMA_MBLK_TYPE_LL;
    dconfig.destMultblk     = DMA_MBLK_TYPE_LL;

    DMA_initController();
    DMA_configChannel(DMA_CH2_BASE, &dconfig);

    // create initial LLI
    // 用链表实现将相移值搬到对应寄存器，一次触发搬运四个值，搬运四个之后跳到下一个链表，目标地址回绕，源地址递增到下一组
    lli_5.SAR                              = (u32)phasePeriodConfigs;
    lli_5.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_TBPHS);
    lli_5.BLOCK_TS                         = 3;
    lli_5.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_5.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_5.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_5.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_5.CTL_H.bit.ARLEN_EN               = 1;
    lli_5.CTL_H.bit.ARLEN                  = 0;
    lli_5.CTL_H.bit.AWLEN_EN               = 1;
    lli_5.CTL_H.bit.AWLEN                  = 0;
    lli_5.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_5.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_5.LLP.all                          = (u32)&lli_6;

    lli_6.SAR                              = (u32)&phasePeriodConfigs[4];
    lli_6.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_TBPHS);
    lli_6.BLOCK_TS                         = 3;
    lli_6.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_6.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_6.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_6.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_6.CTL_H.bit.ARLEN_EN               = 1;
    lli_6.CTL_H.bit.ARLEN                  = 0;
    lli_6.CTL_H.bit.AWLEN_EN               = 1;
    lli_6.CTL_H.bit.AWLEN                  = 0;
    lli_6.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_6.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_6.LLP.all                          = (u32)&lli_7;

    lli_7.SAR                              = (u32)&phasePeriodConfigs[8];
    lli_7.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_TBPHS);;
    lli_7.BLOCK_TS                         = 3;
    lli_7.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_7.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_7.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_7.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_7.CTL_H.bit.ARLEN_EN               = 1;
    lli_7.CTL_H.bit.ARLEN                  = 0;
    lli_7.CTL_H.bit.AWLEN_EN               = 1;
    lli_7.CTL_H.bit.AWLEN                  = 0;
    lli_7.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_7.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_7.LLP.all                          = (u32)&lli_8;

    lli_8.SAR                              = (u32)&phasePeriodConfigs[12];
    lli_8.DSR                              = (u32)(uint16_t *)(myEPWM1_BASE + EPWM_O_TBPHS);;
    lli_8.BLOCK_TS                         = 3;
    lli_8.CTL_L.bit.SRC_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_8.CTL_L.bit.DST_WIDTH              = DMA_TRANS_WIDTH_16;
    lli_8.CTL_L.bit.SRC_MSIZE              = DMA_MSIZE_4;
    lli_8.CTL_L.bit.DST_MSIZE              = DMA_MSIZE_4;
    lli_8.CTL_H.bit.ARLEN_EN               = 1;
    lli_8.CTL_H.bit.ARLEN                  = 0;
    lli_8.CTL_H.bit.AWLEN_EN               = 1;
    lli_8.CTL_H.bit.AWLEN                  = 0;
    lli_8.CTL_H.bit.IOC_BLKTFR             = 1;
    lli_8.CTL_H.bit.SHADOWREG_OR_LLI_VALID = 1;
    lli_8.LLP.all                          = (u32)&lli_5;

    DmaCh2Regs.LLP.all                    = (u32)&lli_5;


}

//
// epwm1ISR - ePWM 1 ISR
//
__interrupt void epwm1ISR(void)
{
    //
    // Un-comment below to check the status of each register after CTR=0
    //
    // ESTOP0;

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}


void initEPWM(uint32_t base)
{
    EPWM_setEmulationMode(base, EPWM_EMULATION_STOP_AFTER_FULL_CYCLE);

    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(base, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(base, 0U);
    EPWM_setTimeBaseCounter(base, 0U);

    //
    // Set Compare values
    //
    EPWM_setCounterCompareValue(base,
                                EPWM_COUNTER_COMPARE_A,
                                EPWM_TIMER_TBPRD/2);
    EPWM_setCounterCompareValue(base,
                                EPWM_COUNTER_COMPARE_B,
                                EPWM_TIMER_TBPRD/2);

    //
    // Set up counter mode
    //
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(base);
    EPWM_setClockPrescaler(base,
                           EPWM_CLOCK_DIVIDER_64,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);


    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);


    //
    // Interrupt where we will change the Compare Values
    // Select INT on Time base counter zero event,
    // Enable INT, generate INT on 1st event
    //
    EPWM_setInterruptSource(base, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(base);
    EPWM_setInterruptEventCount(base, 1U);

    EPWM_enableADCTrigger(base, EPWM_SOC_A);
    EPWM_setADCTriggerSource(base,
                             EPWM_SOC_A,
                             EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(base,
                                    EPWM_SOC_A,
                                       1);
    EPWM_clearADCTriggerFlag(base,
                             EPWM_SOC_A);
}

