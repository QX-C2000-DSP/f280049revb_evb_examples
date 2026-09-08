// #############################################################################
//! This example initializes DMA module for memory to memory transmit.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with DMA module
//!
// #############################################################################
//
//  Copyright (C) 2024 STARRYSTONETECH - http://www.starrystonetech.com/
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of STARRYSTONETECH nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// #############################################################################

#include "device.h"
#include "driverlib.h"
#include "board.h"

//
// Globals
//

char src_buf[32] = { 0 };
char dst_buf[32] = { 0 };

int dma_done_flag = 0;

__interrupt void dmach1ISR(void)
{
    u32 status = DmaCh1Regs.INTSTATUS;
    if (status & DMA_IRQ_DMA_TRF)
    {
        dma_done_flag = 1;
    }
}

int main(void)
{
    char *msg = NULL;
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    for (int i = 0; i < 32; i++)
        src_buf[i] = i + 1;

    DMA_startChannel(1);

    while (dma_done_flag == 0)
        ;

    for (int i = 0; i < 32; i++)
    {
        if (src_buf[i] != dst_buf[i])
            NOP; // add break point here, and shoud not hit!
    }
}
