
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
    DAC_init();

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
// ASYSCTL Configurations
//
//*****************************************************************************
void ASYSCTL_init(){
    //
    // asysctl initialization
    //
    // Disables the temperature sensor output to the ADC.
    //
    ASysCtl_disableTemperatureSensor();
    //
    // Set the analog voltage reference selection to external.
    //
    ASysCtl_setAnalogReferenceExternal( ASYSCTL_VREFHIA | ASYSCTL_VREFHIB | ASYSCTL_VREFHIC );
}

//*****************************************************************************
//
// DAC Configurations
//
//*****************************************************************************
void DAC_init(){
    myDAC0_init();
}

void myDAC0_init(){

    // 由于DAC需要不超过5MHz的时钟，所以在开启DAC时钟前需要先分频DAC的时钟到5M以下
    DacaRegs.DACCTL.bit.PRESCALE = 60;

    //
    // Set DAC reference voltage.
    //
    DAC_setReferenceVoltage(myDAC0_BASE, DAC_REF_ADC_VREFHI);
    //
    // Set DAC load mode.
    //
    DAC_setLoadMode(myDAC0_BASE, DAC_LOAD_SYSCLK);
    //
    // Enable the DAC output
    //
    DAC_enableOutput(myDAC0_BASE);
    //
    // Set the DAC shadow output
    //
    DAC_setShadowValue(myDAC0_BASE, 0U);

    //
    // Delay for buffered DAC to power up.
    //
    DEVICE_DELAY_US(500);
}

