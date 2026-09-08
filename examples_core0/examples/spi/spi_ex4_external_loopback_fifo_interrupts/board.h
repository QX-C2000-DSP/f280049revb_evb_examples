/*
 * Copyright (c) 2020 Hefei Qianxin Technology http://www.starrystonetech.com/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

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
// SPIA -> SPIA_peripheral Pinmux
//
//
// SPIA_PICO - GPIO Settings
//
#define GPIO_PIN_SPIA_PICO 16
#define SPIA_peripheral_SPIPICO_GPIO 16
#define SPIA_peripheral_SPIPICO_PIN_CONFIG GPIO_16_SPIA_SIMO
//
// SPIA_POCI - GPIO Settings
//
#define GPIO_PIN_SPIA_POCI 17
#define SPIA_peripheral_SPIPOCI_GPIO 17
#define SPIA_peripheral_SPIPOCI_PIN_CONFIG GPIO_17_SPIA_SOMI
//
// SPIA_CLK - GPIO Settings
//
#define GPIO_PIN_SPIA_CLK 9
#define SPIA_peripheral_SPICLK_GPIO 9
#define SPIA_peripheral_SPICLK_PIN_CONFIG GPIO_9_SPIA_CLK
//
// SPIA_PTE - GPIO Settings
//
#define GPIO_PIN_SPIA_PTE 11
#define SPIA_peripheral_SPIPTE_GPIO 11
#define SPIA_peripheral_SPIPTE_PIN_CONFIG GPIO_11_SPIA_STE

//
// SPIB -> SPIB_controller Pinmux
//
//
// SPIB_PICO - GPIO Settings
//
#define GPIO_PIN_SPIB_PICO 24
#define SPIB_controller_SPIPICO_GPIO 24
#define SPIB_controller_SPIPICO_PIN_CONFIG GPIO_24_SPIB_SIMO
//
// SPIB_POCI - GPIO Settings
//
#define GPIO_PIN_SPIB_POCI 25
#define SPIB_controller_SPIPOCI_GPIO 25
#define SPIB_controller_SPIPOCI_PIN_CONFIG GPIO_25_SPIB_SOMI
//
// SPIB_CLK - GPIO Settings
//
#define GPIO_PIN_SPIB_CLK 26
#define SPIB_controller_SPICLK_GPIO 26
#define SPIB_controller_SPICLK_PIN_CONFIG GPIO_26_SPIB_CLK
//
// SPIB_PTE - GPIO Settings
//
#define GPIO_PIN_SPIB_PTE 27
#define SPIB_controller_SPIPTE_GPIO 27
#define SPIB_controller_SPIPTE_PIN_CONFIG GPIO_27_SPIB_STE

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_SPIA_peripheral_RX
// ISR need to be defined for the registered interrupts
#define INT_SPIA_peripheral_RX INT_SPIA_RX
#define INT_SPIA_peripheral_RX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP6
extern __interrupt void spiaRxFIFOISR(void);

// Interrupt Settings for INT_SPIA_peripheral_TX
// ISR need to be defined for the registered interrupts
#define INT_SPIA_peripheral_TX INT_SPIA_TX
#define INT_SPIA_peripheral_TX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP6
extern __interrupt void INT_SPIA_peripheral_TX_ISR(void);

// Interrupt Settings for INT_SPIB_controller_RX
// ISR need to be defined for the registered interrupts
#define INT_SPIB_controller_RX INT_SPIB_RX
#define INT_SPIB_controller_RX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP6
extern __interrupt void INT_SPIB_controller_RX_ISR(void);

// Interrupt Settings for INT_SPIB_controller_TX
// ISR need to be defined for the registered interrupts
#define INT_SPIB_controller_TX INT_SPIB_TX
#define INT_SPIB_controller_TX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP6
extern __interrupt void spibTxFIFOISR(void);

//*****************************************************************************
//
// SPI Configurations
//
//*****************************************************************************
#define SPIA_peripheral_BASE SPIA_BASE
#define SPIA_peripheral_BITRATE 500000
#define SPIA_peripheral_DATAWIDTH 16
void SPIA_peripheral_init();
#define SPIB_controller_BASE SPIB_BASE
#define SPIB_controller_BITRATE 500000
#define SPIB_controller_DATAWIDTH 16
void SPIB_controller_init();

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
void	INTERRUPT_init();
void	SPI_init();
void	SYSCTL_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
