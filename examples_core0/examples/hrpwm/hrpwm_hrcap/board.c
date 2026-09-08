
#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
    EALLOW;

    PinMux_init();
    INPUTXBAR_init();
    SYNC_init();
    EPWM_init();
    ECAP_init();
    INTERRUPT_init();

    EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    //
    // PinMux for modules assigned to CPU1
    //

    //
    // EPWM1 -> myEPWM1 Pinmux
    //
    GPIO_setPinConfig(myEPWM1_EPWMA_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM1_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM1_EPWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myEPWM1_EPWMB_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM1_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM1_EPWMB_GPIO, GPIO_QUAL_SYNC);

    //
    // EPWM2 -> myEPWM2 Pinmux
    //
    GPIO_setPinConfig(myEPWM2_EPWMA_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM2_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM2_EPWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myEPWM2_EPWMB_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM2_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM2_EPWMB_GPIO, GPIO_QUAL_SYNC);

    //
    // EPWM3 -> myEPWM3 Pinmux
    //
    GPIO_setPinConfig(myEPWM3_EPWMA_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM3_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM3_EPWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myEPWM3_EPWMB_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM3_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM3_EPWMB_GPIO, GPIO_QUAL_SYNC);

    //
    // EPWM4 -> myEPWM4 Pinmux
    //
    GPIO_setPinConfig(myEPWM4_EPWMA_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM4_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM4_EPWMA_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myEPWM4_EPWMB_PIN_CONFIG);
    GPIO_setPadConfig(myEPWM4_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myEPWM4_EPWMB_GPIO, GPIO_QUAL_SYNC);

    // GPIO16 -> myGPIO0 Pinmux hrcap input
    GPIO_setPinConfig(GPIO_16_GPIO16);
    GPIO_setPadConfig(myECAPGPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myECAPGPIO, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(myECAPGPIO, GPIO_DIR_MODE_IN);

}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);

    HRPWM_setEmulationMode(myEPWM1_BASE, EPWM_EMULATION_FREE_RUN);
    HRPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(myEPWM1_BASE, 99);
    HRPWM_setTimeBaseCounter(myEPWM1_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    HRPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    HRPWM_setPhaseShift(myEPWM1_BASE, 0);
    HRPWM_setSyncOutPulseMode(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM1_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM1_BASE);
    HRPWM_setFallingEdgeDeadBandDelayInput(myEPWM1_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM1_BASE);
    HRPWM_setMEPEdgeSelect(myEPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_A, 50);
    HRPWM_setMEPEdgeSelect(myEPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_B, 50);

    HRPWM_setEmulationMode(myEPWM2_BASE, EPWM_EMULATION_FREE_RUN);
    HRPWM_setClockPrescaler(myEPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(myEPWM2_BASE, 99);
    HRPWM_setTimeBaseCounter(myEPWM2_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myEPWM2_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(myEPWM2_BASE);
    HRPWM_disablePhaseShiftLoad(myEPWM2_BASE);
    HRPWM_setPhaseShift(myEPWM2_BASE, 0);
    HRPWM_setSyncOutPulseMode(myEPWM2_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM2_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM2_BASE);
    HRPWM_setFallingEdgeDeadBandDelayInput(myEPWM2_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM2_BASE);
    HRPWM_setMEPEdgeSelect(myEPWM2_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM2_BASE, HRPWM_COUNTER_COMPARE_A, 50);
    HRPWM_setMEPEdgeSelect(myEPWM2_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM2_BASE, HRPWM_COUNTER_COMPARE_B, 50);

    HRPWM_setEmulationMode(myEPWM3_BASE, EPWM_EMULATION_FREE_RUN);
    HRPWM_setClockPrescaler(myEPWM3_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(myEPWM3_BASE, 99);
    HRPWM_setTimeBaseCounter(myEPWM3_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myEPWM3_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(myEPWM3_BASE);
    HRPWM_disablePhaseShiftLoad(myEPWM3_BASE);
    HRPWM_setPhaseShift(myEPWM3_BASE, 0);
    HRPWM_setSyncOutPulseMode(myEPWM3_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM3_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM3_BASE);
    HRPWM_setFallingEdgeDeadBandDelayInput(myEPWM3_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM3_BASE);
    HRPWM_setMEPEdgeSelect(myEPWM3_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM3_BASE, HRPWM_COUNTER_COMPARE_A, 50);
    HRPWM_setMEPEdgeSelect(myEPWM3_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM3_BASE, HRPWM_COUNTER_COMPARE_B, 50);

    HRPWM_setEmulationMode(myEPWM4_BASE, EPWM_EMULATION_FREE_RUN);
    HRPWM_setClockPrescaler(myEPWM4_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(myEPWM4_BASE, 99);
    HRPWM_setTimeBaseCounter(myEPWM4_BASE, 0);
    HRPWM_setTimeBaseCounterMode(myEPWM4_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(myEPWM4_BASE);
    HRPWM_disablePhaseShiftLoad(myEPWM4_BASE);
    HRPWM_setPhaseShift(myEPWM4_BASE, 0);
    HRPWM_setSyncOutPulseMode(myEPWM4_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, 0);
    HRPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    HRPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    HRPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM4_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM4_BASE);
    HRPWM_setFallingEdgeDeadBandDelayInput(myEPWM4_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);
    HRPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM4_BASE);
    HRPWM_setMEPEdgeSelect(myEPWM4_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM4_BASE, HRPWM_COUNTER_COMPARE_A, 50);
    HRPWM_setMEPEdgeSelect(myEPWM4_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM4_BASE, HRPWM_COUNTER_COMPARE_B, 50);
}

//*****************************************************************************
//
// ECAP Configurations
//
//*****************************************************************************
void ECAP_init(){
    myECAP0_init();
}

void myECAP0_init(){

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP7);

    //
    // HRCAP module configuration for myECAP0_HR_BASE (part of myECAP0_BASE).
    //
    // Enable High resolution clock
    //
    HRCAP_enableHighResolutionClock(myECAP0_HR_BASE);
    DEVICE_DELAY_US(1); // 1us delay as mentioned in HRCAP chapter of TRM
    //
    // Enable High Resolution module
    //
    HRCAP_enableHighResolution(myECAP0_HR_BASE);
    DEVICE_DELAY_US(1); // 1us delay as mentioned in HRCAP chapter of TRM
    //
    // Disable ,clear all capture flags and interrupts
    //
    ECAP_disableInterrupt(myECAP0_BASE,
        (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
        ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
        ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
        ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
        ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
        ECAP_ISR_SOURCE_COUNTER_PERIOD   |
        ECAP_ISR_SOURCE_COUNTER_COMPARE));
    ECAP_clearInterrupt(myECAP0_BASE,
        (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
        ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
        ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
        ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
        ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
        ECAP_ISR_SOURCE_COUNTER_PERIOD   |
        ECAP_ISR_SOURCE_COUNTER_COMPARE));
    //
    // Disables time stamp capture.
    //
    ECAP_disableTimeStampCapture(myECAP0_BASE);
    //
    // Stops Time stamp counter.
    //
    ECAP_stopCounter(myECAP0_BASE);
    //
    // Sets eCAP in Capture mode.
    //
    ECAP_enableCaptureMode(myECAP0_BASE);
    //
    // Sets the capture mode.
    //
    ECAP_setCaptureMode(myECAP0_BASE,ECAP_ONE_SHOT_CAPTURE_MODE,ECAP_EVENT_4);
    //
    // Sets the Capture event prescaler.
    //
    ECAP_setEventPrescaler(myECAP0_BASE, 0U);
    //
    // Sets the Capture event polarity.
    //
    ECAP_setEventPolarity(myECAP0_BASE,ECAP_EVENT_1,ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(myECAP0_BASE,ECAP_EVENT_2,ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(myECAP0_BASE,ECAP_EVENT_3,ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(myECAP0_BASE,ECAP_EVENT_4,ECAP_EVNT_FALLING_EDGE);
    //
    // Configure counter reset on events
    //
    ECAP_disableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_1);
    ECAP_disableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_2);
    ECAP_disableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_3);
    ECAP_disableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_4);
    //
    // Select eCAP input.
    //
    ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR7);
    //
    // Sets a phase shift value count.
    //
    ECAP_setPhaseShiftCount(myECAP0_BASE,0U);
    //
    // Enable counter loading with phase shift value.
    //
    ECAP_enableLoadCounter(myECAP0_BASE);
    //
    // Configures Sync out signal mode.
    //
    ECAP_setSyncOutMode(myECAP0_BASE,ECAP_SYNC_OUT_SYNCI);
    //
    // Resets eCAP counters and flags.
    //
    ECAP_resetCounters(myECAP0_BASE);
    //
    // Configures emulation mode.
    //
    ECAP_setEmulationMode(myECAP0_BASE,ECAP_EMULATION_STOP);
    //
    // Starts Time stamp counter for myECAP0.
    //
    ECAP_startCounter(myECAP0_BASE);
    //
    // Enables time stamp capture for myECAP0.
    //
    ECAP_enableTimeStampCapture(myECAP0_BASE);
    //
    // Re-arms the eCAP module for myECAP0.
    //
    ECAP_reArm(myECAP0_BASE);
    //
    // Enables interrupt source for myECAP0.
    //
    ECAP_enableInterrupt(myECAP0_BASE,(ECAP_ISR_SOURCE_CAPTURE_EVENT_4));
    //
    // myECAP0_HR_BASE Calibration Settings
    //
    // Set calibration period (register is in SYSCLK cycles), 1.6ms recommended
    //
    HWREG(myECAP0_HR_BASE + HRCAP_O_HRCALPRD) = (uint32_t) (100e9 * (1.6/1000));
    //
    // Configure in continuous calibration mode
    //
    HRCAP_setCalibrationMode(myECAP0_HR_BASE);
    //
    // Enable HRCAP calibration interrupts
    //
    HRCAP_enableCalibrationInterrupt(myECAP0_HR_BASE, (HRCAP_CALIBRATION_DONE
         | HRCAP_CALIBRATION_PERIOD_OVERFLOW));
    //
    // Start HR calibration
    //
    HRCAP_startCalibration(myECAP0_HR_BASE);

    //-----------------Signal Monitoring--------------------//
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init(){
    myINPUTXBARINPUT0_init();
    myINPUTXBARINPUT1_init();
    myINPUTXBARINPUT2_init();
}

void myINPUTXBARINPUT0_init(){
    XBAR_setInputPin(myINPUTXBARINPUT0_INPUT, myINPUTXBARINPUT0_SOURCE);
}
void myINPUTXBARINPUT1_init(){
    XBAR_setInputPin(myINPUTXBARINPUT1_INPUT, myINPUTXBARINPUT1_SOURCE);
}
void myINPUTXBARINPUT2_init(){
    XBAR_setInputPin(myINPUTXBARINPUT2_INPUT, myINPUTXBARINPUT2_SOURCE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){

    // Interrupt Settings for INT_myECAP0
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myECAP0, &INT_myECAP0_ISR);
    Interrupt_enable(INT_myECAP0);

    // Interrupt Settings for INT_myECAP0_HR
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myECAP0_HR, &INT_myECAP0_HR_ISR);
    Interrupt_enable(INT_myECAP0_HR);
}

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
    SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
    //
    // For EPWM1, the sync input is: SYSCTL_SYNC_IN_SRC_EXTSYNCIN1
    //
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_EPWM4, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_EPWM7, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP4, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP6, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
    //
    // SOCA
    //
    SysCtl_enableExtADCSOCSource(0);
    //
    // SOCB
    //
    SysCtl_enableExtADCSOCSource(0);
}
