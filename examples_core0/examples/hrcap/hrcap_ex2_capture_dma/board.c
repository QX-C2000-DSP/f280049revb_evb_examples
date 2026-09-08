
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
    DMA_init();
    INTERRUPT_init();
    TIMER0_init();


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

    //使能HRPWR，使能之后SFO的mep值才会扩散
    EALLOW;
    EPwm1Regs.HRPWR.all       = 0x8000;
    EDIS;

    HRPWM_setEmulationMode(myEPWM1_BASE, EPWM_EMULATION_FREE_RUN);
    HRPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(myEPWM1_BASE, 49);
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
    HRPWM_enableAutoConversion(myEPWM1_BASE);
    HRPWM_setMEPEdgeSelect(myEPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_A, 50);
    HRPWM_setMEPEdgeSelect(myEPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setHiResCounterCompareValueOnly(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_B, 50);
    HRPWM_enablePeriodControl(myEPWM1_BASE);
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
      ECAP_setCaptureMode(myECAP0_BASE,ECAP_CONTINUOUS_CAPTURE_MODE,ECAP_EVENT_4);
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
      ECAP_enableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_1);
      ECAP_enableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_2);
      ECAP_enableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_3);
      ECAP_enableCounterResetOnEvent(myECAP0_BASE,ECAP_EVENT_4);
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
//      //
//      // Enables interrupt source for myECAP0.
//      //
//      ECAP_enableInterrupt(myECAP0_BASE,(ECAP_ISR_SOURCE_CAPTURE_EVENT_4));

      EALLOW;
      //
      // myECAP0_HR_BASE Calibration Settings
      //
      // Set calibration period (register is in SYSCLK cycles),1.6s recommended(HRCALPRD = 校准时间(s) × SYSCLK频率(Hz))
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

      EDIS;

      //-----------------Signal Monitoring--------------------//

}

//*****************************************************************************
//
// DMA init
//
//*****************************************************************************
void DMA_init()
{
    DMA_ConfigParams dconfig = { 0 };

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

    DMA_initController();

//    // DMA channel 1 config
//    dconfig.srcAddr         = (u32)&ECap7Regs.CAP1;
//    dconfig.destAddr        = (u32)cap1Count;
//    dconfig.srcWidth        = DMA_TRANS_WIDTH_32; // 设置DMA单次传输数据位宽为32bit
//    dconfig.destWidth       = DMA_TRANS_WIDTH_32; // 设置DMA单次传输数据位宽为32bit
//    dconfig.srcMsize        = DMA_MSIZE_1;  // 设置DMA被触发一次传输1个字（burst大小）
//    dconfig.destMsize       = DMA_MSIZE_1;  // 设置DMA被触发一次传输1个字（burst大小）
//    dconfig.blockSize       = CAP_VALUE_SUM - 1;           // 一次DMA业务总长度，共包含20个字
//    dconfig.srcHSInterface  = DMA_TRIGGER_ECAP7;  //设置单次传输完源地址不增长，目标地址连续增长
//    dconfig.destHSInterface = DMA_TRIGGER_MEM;
//    DMA_configChannel(DMA_CH1_BASE, &dconfig);

//    // DMA channel 2 config
//    dconfig.srcAddr         = (u32)&ECap7Regs.CAP2;
//    dconfig.destAddr        = (u32)cap2Count;
//    dconfig.srcWidth        = DMA_TRANS_WIDTH_32;
//    dconfig.destWidth       = DMA_TRANS_WIDTH_32;
//    dconfig.srcMsize        = DMA_MSIZE_1;
//    dconfig.destMsize       = DMA_MSIZE_1;
//    dconfig.blockSize       = CAP_VALUE_SUM - 1;
//    dconfig.srcHSInterface  = DMA_TRIGGER_ECAP7;
//    dconfig.destHSInterface = DMA_TRIGGER_MEM;
//    dconfig.srcInc          = DMA_INC_TYPE_NO_CHANGE;    // 设DMA源地址不变
//    dconfig.destInc         = DMA_INC_TYPE_INCREMENT;    // 设DMA目的地址递增
//    DMA_configChannel(DMA_CH2_BASE, &dconfig);

    // DMA channel 3 config
    dconfig.srcAddr         = (u32)&ECap7Regs.CAP3;
    dconfig.destAddr        = (u32)cap3Count;
    dconfig.srcWidth        = DMA_TRANS_WIDTH_32;
    dconfig.destWidth       = DMA_TRANS_WIDTH_32;
    dconfig.srcMsize        = DMA_MSIZE_1;
    dconfig.destMsize       = DMA_MSIZE_1;
    dconfig.blockSize       = CAP_VALUE_SUM - 1;
    dconfig.srcHSInterface  = DMA_TRIGGER_ECAP7;
    dconfig.destHSInterface = DMA_TRIGGER_MEM;
    dconfig.srcInc          = DMA_INC_TYPE_NO_CHANGE;    // 设DMA源地址不变
    dconfig.destInc         = DMA_INC_TYPE_INCREMENT;    // 设DMA目的地址递增
    DMA_configChannel(DMA_CH3_BASE, &dconfig);

    // DMA channel 4 config
    dconfig.srcAddr         = (u32)&ECap7Regs.CAP4;
    dconfig.destAddr        = (u32)cap4Count;
    dconfig.srcWidth        = DMA_TRANS_WIDTH_32;
    dconfig.destWidth       = DMA_TRANS_WIDTH_32;
    dconfig.srcMsize        = DMA_MSIZE_1;
    dconfig.destMsize       = DMA_MSIZE_1;
    dconfig.blockSize       = CAP_VALUE_SUM - 1;
    dconfig.srcHSInterface  = DMA_TRIGGER_ECAP7;
    dconfig.destHSInterface = DMA_TRIGGER_MEM;
    dconfig.srcInc          = DMA_INC_TYPE_NO_CHANGE;    // 设DMA源地址不变
    dconfig.destInc         = DMA_INC_TYPE_INCREMENT;    // 设DMA目的地址递增
    DMA_configChannel(DMA_CH4_BASE, &dconfig);

    DmaCh4Regs.INTSIGNAL_EN = 0xFFE2; // 使能DMA完成和所有错误中断

    DMA_startChannel(3);
    DMA_startChannel(4);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init(){
    myINPUTXBARINPUT2_init();
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

//    // Interrupt Settings for INT_myECAP0
//    // ISR need to be defined for the registered interrupts
//    Interrupt_register(INT_myECAP0, &INT_myECAP0_ISR);
//    Interrupt_enable(INT_myECAP0);

    // Interrupt Settings for INT_myECAP0_HR
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myECAP0_HR, &INT_myECAP0_HR_ISR);
    Interrupt_enable(INT_myECAP0_HR);

    Interrupt_register(INT_DMA_CH4, &dmach4ISR);
    Interrupt_enable(INT_DMA_CH4);

    /* set timer0 interrupt */
    Interrupt_register(INT_TIMER0, timer0_isr);
    Interrupt_enable(INT_TIMER0);
}

void TIMER0_init(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);

    uint32_t SystemClock = SysCtl_getClock(DEVICE_OSCSRC_FREQ);
    uint32_t prescaler   = CPUTIMER_CLOCK_PRESCALER_1;                              // 设置分频因子
    uint32_t period      = SystemClock / ((prescaler + 1) * SYS_TICKS_PER_SECOND);  // 计算周期

    CPUTimer_stopTimer(CPUTIMER0_BASE);                 // 停止定时器
    CPUTimer_setPeriod(CPUTIMER0_BASE, period - 1);     // 设置周期
    CPUTimer_setPreScaler(CPUTIMER0_BASE, prescaler);   // 设置定时器的时钟源
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);        // 重载初始值
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);           // 设置定时器的中断
    CPUTimer_startTimer(CPUTIMER0_BASE);                // 开启定时器


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
