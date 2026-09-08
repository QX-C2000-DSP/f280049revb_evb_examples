#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
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
// SPIA -> mySPI0 Pinmux
//
//
// SPIA_PICO - GPIO Settings
//
#define GPIO_PIN_SPIA_PICO        16
#define mySPI0_SPIPICO_GPIO       16
#define mySPI0_SPIPICO_PIN_CONFIG GPIO_16_SPIA_SIMO
//
// SPIA_POCI - GPIO Settings
//
#define GPIO_PIN_SPIA_POCI        10
#define mySPI0_SPIPOCI_GPIO       10
#define mySPI0_SPIPOCI_PIN_CONFIG GPIO_10_SPIA_SOMI
//
// SPIA_CLK - GPIO Settings
//
#define GPIO_PIN_SPIA_CLK        18
#define mySPI0_SPICLK_GPIO       18
#define mySPI0_SPICLK_PIN_CONFIG GPIO_18_SPIA_CLK
//
// SPIA_PTE - GPIO Settings
//
#define GPIO_PIN_SPIA_PTE        11
#define mySPI0_SPIPTE_GPIO       11
#define mySPI0_SPIPTE_PIN_CONFIG GPIO_11_SPIA_STE

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
#define mySPI0_BASE      (u32) & SpiaRegs
#define mySPI0_BITRATE   100000
#define mySPI0_DATAWIDTH 16
void mySPI0_init();

#define mySPI1_BASE (u32) & SpibRegs
//  配置波特率
#define mySPI1_BITRATE 10000000
//  配置为8位数据帧
#define mySPI1_DATAWIDTH 8
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
void Board_init();
void SPI_init();
void PinMux_init();
//*****************************************************************************
//
//  Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // end of BOARD_H definition
