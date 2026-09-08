#include "board.h"

extern __interrupt void wakeISR(void);

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void Board_init()
{
    EALLOW;

    PinMux_init();
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
    GPIO_MuxConfig(8, GPIO_8_GPIO8, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP, GPIO_QUAL_3SAMPLE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{
    //
    // Interrupt Setings for wake
    //
    Interrupt_register(INT_WAKE, &wakeISR);
    Interrupt_enable(INT_WAKE);
}
