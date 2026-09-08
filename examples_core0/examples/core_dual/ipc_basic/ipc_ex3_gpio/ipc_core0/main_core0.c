// #############################################################################
//
//  FILE:   ipc_ex3_gpio.c
//
//! \addtogroup driver_dual_example_list
//! <h1> IPC basic message passing example with interrupt </h1>
//!
//! This example demonstrates how to configure IPC and pass information from
//! C28x1 to C28x2 core without message queues.
//! It is recommended to run the C28x1 core first, followed by the C28x2 core.
//!
//! \note In the default CPU2 linker cmd file, GS4, FLASH_BANK3 and FLASH_BANK4
//! are used for allocating various CPU2 sections. The CPU1 application
//! assigns the ownership of these memory regions to CPU2 by using SysConfig.
//! Please note that CPU2 .out file can be loaded only after CPU1 completes
//! this configuration.
//!
//! The erase setting (CPU1/CPU2 On-Chip Flash -> erase setting) needs to be
//! configured as selected banks only (Choose the corresponding BANKS allocated
//! for CPUs) or necessary sectors only before loading CPU1/CPU2.out file
//! (This is applicable only for FLASH configuration)
//!
//! \b External \b Connections \n
//!  - GPIO15与GPIO11使用杜邦线连接
//!  - GPIO10与GPIO14使用杜邦线连接
//!
//! \b Watch \b Variables \n
//!  - 示波器观察GPIO1与GPIO2的波形
//!  - 板子上的LED0规律闪烁
//
// #############################################################################
//
// Copyright (C) 2024 STARRYSTONETECH - http://www.starrystonetech.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of STARRYSTONETECH nor the names of its contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// #############################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"

int main(void)
{
    uint16_t state;
    uint32_t count;

    uint32_t regValue = 0x00;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    // Turn on core 1 clock, enable core 1
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1);

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    // Break point debugging here
    Device_initGPIO();

    //
    // Initialize settings from SysConfig
    //
    Board_init();

    //
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Sync the CPUs
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_FLAG31);

    //
    // Set the state to the DAT value of GPIO14
    //
    state = GPIO_readPin(myGPIO14);

    while (1)
    {
        //
        // Generate a Square Wave on GPIO15. This signal will be used to drive
        // GPIO11 input on CPU2
        //
        if (count++ > 1000000)
        {
            count = 0;

            //
            // Toggle GPIO15
            //
            GPIO_togglePin(myGPIO15);
        }

        //
        // Set Flag 10 when GPIO14 input changes
        //
        if (GPIO_readPin(myGPIO14) != state)
        {
            state = GPIO_readPin(myGPIO14);
            //
            // This checks to see if flag 10 for CPU1_to_CPU2 is already set, then sets the Flag if
            // it wasn't busy
            //
            IPC_sendCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG10, IPC_ADDR_CORRECTION_ENABLE, 0, 0, 0);
        }

        //
        // Toggle GPIO31 output if Flag 11 is set by CPU2
        //
        if (IPC_isFlagBusyRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG11))
        {
            //
            // Toggle GPIO1 (LED1)
            //
            GPIO_togglePin(CPU1_LED);

            //
            // Acknowledge and clear the flag
            //
            IPC_ackFlagRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG11);
        }
    }

    return 0;
}
