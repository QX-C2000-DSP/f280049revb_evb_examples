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
#include <string.h>
#include "../sci_send_recv_dma/board.h"

//
// Globals
//

char send_frame[256] = { 0 };
char recv_frame[256] = { 0 };

volatile uint8_t recv_status = 0;
volatile uint8_t recv_len    = 0;

uint8_t recv_handle_done = 0;

char *msg = NULL;

#define RECV_STATUS_IDLE      0x0
#define RECV_STATUS_RECV_DATA 0x1

//
// Function Prototypes
//

void SCI_sendFrameByDMA(char *msg, uint32_t len)
{
    memset(send_frame, 0, sizeof(send_frame));
    memcpy(send_frame, msg, len);

    DmaCh1Regs.BLOCK_TS = len - 1;
    DmaCh1Regs.SAR      = (u32)send_frame;
    DMA_startChannel(1);
}

void SCI_recvFrameHandle()
{
    //
    // Echo back the character.
    //
    msg = "  You sent: \0";
    SCI_sendFrameByDMA(msg, strlen(msg));
    DEVICE_DELAY_US(10000);
    SCI_sendFrameByDMA(recv_frame, recv_len);
    DEVICE_DELAY_US(10000);
    recv_handle_done = 1;
}

__interrupt void dmach2ISR(void)
{
    u32 status = DmaCh2Regs.INTSTATUS;
    if (status & DMA_IRQ_DMA_TRF)
    {
        switch (recv_status)
        {
            case RECV_STATUS_IDLE:
                recv_len            = recv_frame[0];
                DmaCh2Regs.BLOCK_TS = recv_frame[0] - 1;
                DmaCh2Regs.DAR      = (u32)recv_frame;
                recv_status         = RECV_STATUS_RECV_DATA;
                DMA_startChannel(2);
                break;
            case RECV_STATUS_RECV_DATA:
                DmaCh2Regs.BLOCK_TS = 0;
                DmaCh2Regs.DAR      = (u32)recv_frame;
                DMA_startChannel(2);
                recv_status = RECV_STATUS_IDLE;
                SCI_recvFrameHandle();
                break;
            default:
                break;
        }
    }
}

int main(void)
{
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

    //
    // Send starting message.
    //
    msg = "\r\n\n\nHello World!\0";
    SCI_sendFrameByDMA(msg, strlen(msg));
    DEVICE_DELAY_US(10000);
    msg = "\r\nYou will enter characters, and the DSP will echo it back!\n\0";
    SCI_sendFrameByDMA(msg, strlen(msg));
    DEVICE_DELAY_US(10000);
    msg = "\r\nEnter characters: \0";
    SCI_sendFrameByDMA(msg, strlen(msg));
    DEVICE_DELAY_US(10000);

    for (;;)
    {
        if (recv_handle_done)
        {
            msg = "\r\nEnter characters: \0";
            SCI_sendFrameByDMA(msg, strlen(msg));
            recv_handle_done = 0;
        }
    }
}
