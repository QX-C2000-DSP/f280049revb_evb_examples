// #############################################################################
//
//  FILE:   ipc_ex1_basic.c
//
//  TITLE: SysConfig IPC example with interrupt
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
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - pass
//!
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

//
// Defines
//
#define IPC_CMD_READ_MEM 0x1001
#define IPC_CMD_RESP     0x2001

#define TEST_PASS 0x5555
#define TEST_FAIL 0xAAAA

#define CPU1_to_CPU2_IPC_FLAG0 IPC_FLAG0
#define SYNC_FLAG              IPC_FLAG31
#define SYNC_FLAG              IPC_FLAG31
#define BOOT_MODE_CPU2         C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH

// #pragma DATA_SECTION(readData, "MSGRAM_CPU1_TO_CPU2")
__attribute__((section("MsgRamCpu1ToCpu2File"))) volatile uint32_t readData[10] = { 0x00 };

uint32_t pass = 0;

//
// Main
//
int main(void)
{
    int i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    // Turn on core 1 clock, enable core 1
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU1);

    // Break point debugging here
    // Clear any IPC flags if set already
    //
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG_ALL);

    //
    // Synchronize both the cores.
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, SYNC_FLAG);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Fill in the data to be sent
    //
    for (i = 0; i < 10; i++)
    {
        readData[i] = i;
    }

    //
    // Send a message without message queue
    // Length of the data to be read is passed as data.
    //
    IPC_sendCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG0, IPC_ADDR_CORRECTION_ENABLE, IPC_CMD_READ_MEM,
        (uint32_t)readData, 10);

    //
    // Wait for acknowledgment
    //
    IPC_waitForAck(IPC_CPU1_L_CPU2_R, IPC_FLAG0);

    //
    // Read response
    //
    if (IPC_getResponse(IPC_CPU1_L_CPU2_R) == TEST_PASS)
    {
        pass = 1;
    }
    else
    {
        pass = 0;
    }

    //
    // End of example. Loop forever
    //
    while (1)
        ;

    return 0;
}
