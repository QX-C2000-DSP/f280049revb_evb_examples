
#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// GPIO2 - External trigger signal INPUT
//
#define TRIGGER_INPUT_GPIO 2

//
// GPIO3 - OUTPUT XBAR2 (inverted signal for falling edge detection)
//
#define INVERTED_SIGNAL_GPIO 3

//
// GPIO0 (EPWM1A) - Rising edge 100ns pulse output
//
#define RISING_EDGE_OUTPUT_GPIO 0

//
// GPIO6 (EPWM4A) - Falling edge 100ns pulse output
//
#define FALLING_EDGE_OUTPUT_GPIO 6

//*****************************************************************************
//
// EPWM Configurations
// TBPRD = 9 for 100ns pulse at 100MHz (10 clocks - 1)
//
//*****************************************************************************
#define PULSE_WIDTH_TBPRD 9

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    PinMux_init();
void    INPUTXBAR_init();
void    OUTPUTXBAR_init();
void    EPWMXBAR_init();
void    EPWM_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
