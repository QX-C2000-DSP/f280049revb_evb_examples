
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
    ADC_setVREF(myADC0_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_1_65V);
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
    //      Trigger         : ADC_TRIGGER_EPWM1_SOCA
    //      Channel         : ADC_CH_ADCIN0
    //      Sample Window   : 8 SYSCLK cycles
    //      Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
    //
    ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 8U);
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
    //
    // ADC Interrupt 1 Configuration
    //      Source  : ADC_SOC_NUMBER0
    //      Interrupt Source: enabled
    //      Continuous Mode : disabled
    //
    //
    ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_disableContinuousMode(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);

    ADC_enableContinuousMode(myADC0_BASE, ADC_INT_NUMBER1);
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
    //ASysCtl_Unsupported_setAnalogReference1P65(ASYSCTL_VREFHIA | ASYSCTL_VREFHIB | ASYSCTL_VREFHIC);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{

    // Interrupt Settings for INT_myADC0_1
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myADC0_1, &adcA1ISR);
    Interrupt_enable(INT_myADC0_1);
}
