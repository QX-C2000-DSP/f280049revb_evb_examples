
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
// SPIB -> mySPI1 Pinmux
//
//
// SPIB_PICO - GPIO Settings
//
#define GPIO_PIN_SPIB_SIMO        7
#define mySPI1_SPISIMO_GPIO       7
#define mySPI1_SPISIMO_PIN_CONFIG GPIO_7_SPIB_SIMO
//
// SPIB_POCI - GPIO Settings
//
#define GPIO_PIN_SPIB_SOMI        6
#define mySPI1_SPISOMI_GPIO       6
#define mySPI1_SPISOMI_PIN_CONFIG GPIO_6_SPIB_SOMI
//
// SPIB_CLK - GPIO Settings
//
#define GPIO_PIN_SPIB_CLK        28
#define mySPI1_SPICLK_GPIO       28
#define mySPI1_SPICLK_PIN_CONFIG GPIO_28_SPIB_CLK
//
// SPIB_PTE - GPIO Settings
//
#define GPIO_PIN_SPIB_STE        29
#define mySPI1_SPIPTE_GPIO       29
#define mySPI1_SPIPTE_PIN_CONFIG GPIO_29_SPIB_STE

//*****************************************************************************
//
// SPI Configurations
//
//*****************************************************************************
#define mySPI1_BASE SPIB_BASE
#define mySPI1_BITRATE 1000000
#define mySPI1_DATAWIDTH 16
void mySPI1_init();

//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	SPI_init();
void	PinMux_init();
void    DMA_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
