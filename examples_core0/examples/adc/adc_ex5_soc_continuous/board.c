
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
    ASYSCTL_init();
    ADC_init();

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
}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init()
{
    myADC0_init();
}

void myADC0_init()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    //
    // ADC Initialization: Write ADC configurations and power up the ADC
    //
    // Set the analog voltage reference selection and ADC module's offset trims.
    // This function sets the analog voltage reference to internal (with the reference voltage
    // of 1.65V or 2.5V) or external for ADC which is same as ASysCtl APIs.
    //
    ADC_setVREF(myADC0_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_3_3V);
    //
    // Configures the analog-to-digital converter module prescaler.
    //
    ADC_setPrescaler(myADC0_BASE, ADC_CLK_DIV_2_0);
    //
    // Sets the timing of the end-of-conversion pulse
    //
    ADC_setInterruptPulseMode(myADC0_BASE, ADC_PULSE_END_OF_CONV);
    //
    // Powers up the analog-to-digital converter core.
    //
    ADC_enableConverter(myADC0_BASE);
    //
    // Delay for 1ms to allow ADC time to power up
    //
    DEVICE_DELAY_US(5000);
    //
    // SOC Configuration: Setup ADC EPWM channel and trigger settings
    //
    // Disables SOC burst mode.
    //
    ADC_disableBurstMode(myADC0_BASE);
    //
    // Sets the priority mode of the SOCs.
    //
    ADC_setSOCPriority(myADC0_BASE, ADC_PRI_ALL_ROUND_ROBIN);

    //
    // Start of Conversion 0 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 0
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 1 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 1
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 2 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 2
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 3 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 3
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 4 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 4
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 5 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 5
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 6 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 6
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 7 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 7
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_ADCINT2);
    //
    // Start of Conversion 8 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 8
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER8, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // Start of Conversion 9 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 9
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER9, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // Start of Conversion 10 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 10
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER10, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // Start of Conversion 11 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 11
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER11, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // Start of Conversion 12 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 12
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER12, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // Start of Conversion 13 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 13
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER13, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // Start of Conversion 14 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 14
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER14, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER14, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // Start of Conversion 15 Configuration
    //
    //
    // Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
    //      SOC number      : 15
    //      Trigger         : ADC_TRIGGER_SW_ONLY
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 30 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_ADCINT1
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER15, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 30U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER15, ADC_INT_SOC_TRIGGER_ADCINT1);
    //
    // ADC Interrupt 1 Configuration
    //      Source  : ADC_SOC_NUMBER6
    //      Interrupt Source: disabled
    //      Continuous Mode : enabled
    //
    //
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER6);
    ADC_enableContinuousMode(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
    //
    // ADC Interrupt 2 Configuration
    //      Source  : ADC_SOC_NUMBER14
    //      Interrupt Source: disabled
    //      Continuous Mode : enabled
    //
    //
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER14);
    ADC_enableContinuousMode(myADC0_BASE, ADC_INT_NUMBER2);
    ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER2);
    //
    // ADC Interrupt 3 Configuration
    //      Source  : ADC_SOC_NUMBER7
    //      Interrupt Source: disabled
    //      Continuous Mode : enabled
    //
    //
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER7);
    ADC_enableContinuousMode(myADC0_BASE, ADC_INT_NUMBER3);
    ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER3);
    //
    // ADC Interrupt 4 Configuration
    //      Source  : ADC_SOC_NUMBER15
    //      Interrupt Source: disabled
    //      Continuous Mode : enabled
    //
    //
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER15);
    ADC_enableContinuousMode(myADC0_BASE, ADC_INT_NUMBER4);
    ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER4);
}

//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************
void ASYSCTL_init()
{
    //
    // asysctl initialization
    //
    // Disables the temperature sensor output to the ADC.
    //
    ASysCtl_disableTemperatureSensor();
    //
    // Set the analog voltage reference selection to internal.
    //
    ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIA | ASYSCTL_VREFHIB | ASYSCTL_VREFHIC);
    //
    // Set the internal analog voltage reference selection to 1.65V.
    //
   // ASysCtl_Unsupported_setAnalogReference1P65(ASYSCTL_VREFHIA | ASYSCTL_VREFHIB | ASYSCTL_VREFHIC);
}
