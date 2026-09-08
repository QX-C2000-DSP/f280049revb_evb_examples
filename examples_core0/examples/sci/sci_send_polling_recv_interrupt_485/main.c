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

#include <string.h>

//
// Globals
//
const char *msg       = NULL;
char send_frame[256]  = { 0 };
char recv_frame[256]  = { 0 };
char recv_char;
uint8_t recv_cnt = 0;

uint8_t rx_err_cnt = 0;

void recv_data_handle(char recv_char)
{
    recv_frame[recv_cnt++] = recv_char;
    if (recv_char == '\n')
    {
        //
        // Echo back the character.
        //
        msg = "  You sent: \0";
        SCI_writeCharArray(SCI_BASE, (const uint8_t *)msg, strlen(msg));
        DEVICE_DELAY_US(1000);
        SCI_writeCharArray(SCI_BASE, (const uint8_t *)recv_frame, recv_cnt);
        DEVICE_DELAY_US(1000);
        msg = (const char *)"\r\nEnter characters: \0";
        SCI_writeCharArray(SCI_BASE, (const uint8_t *)msg, strlen(msg));
        recv_cnt = 0;
    }
}

__interrupt void scirxISR(void)
{
    uint8_t sci_int_flag;

    sci_int_flag = SCI_getInterruptStatus(SCI_BASE);

    // 1. Check Hardware Error (Break, Framing, Parity, Overrun)
    // SCI_RXST_RXERROR is the logical OR of FE, PE, OE, BRKDT
    if ((sci_int_flag & SCI_INT_RXERR) == SCI_INT_RXERR)
    {
        rx_err_cnt++;
        // Toggle SWRESET to reset the SCI state machine and clear error flags
        SCI_performSoftwareReset(SCI_BASE);
        // Explicitly clear the interrupt flag
        SCI_clearInterruptStatus(SCI_BASE, SCI_INT_RXERR);
    }

    if ((sci_int_flag & SCI_INT_RXFF) == SCI_INT_RXFF)
    {
        while (SCI_isDataAvailableNonFIFO(SCI_BASE))
        {
            recv_char = SCI_readCharNonBlocking(SCI_BASE);
            recv_data_handle(recv_char);
        }
        SCI_clearInterruptStatus(SCI_BASE, SCI_INT_RXFF);
    }
}

void SCI_sendDataPolling(uint8_t data)
{
#if 0
    while (!ScibRegs.LSR.bit.THRE);
    ScibRegs.THR = data;
    // while (!ScibRegs.LSR.bit.TEMT);
#else
    while (!SCI_isSpaceAvailableNonFIFO(SCI_BASE))
        ;
    SCI_writeCharNonBlocking(SCI_BASE, data);
#endif
}

void SCI_sendData(void)
{
    int i = 0;
    for (i = 0; i < sizeof(send_frame); i++)
    {
        send_frame[i] = i;
    }

    for (i = 0; i < sizeof(send_frame); i++)
    {
        SCI_sendDataPolling(send_frame[i]);
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
    msg = (const char *)"\r\n\n\nHello World!\0";
    SCI_writeCharArray(SCI_BASE, (const uint8_t *)msg, strlen(msg));
    DEVICE_DELAY_US(1000);
    msg = (const char *)"\r\nYou will enter characters, and the DSP will echo it back!\n\0";
    SCI_writeCharArray(SCI_BASE, (const uint8_t *)msg, strlen(msg));
    DEVICE_DELAY_US(1000);
    msg = (const char *)"\r\nEnter characters: \0";
    SCI_writeCharArray(SCI_BASE, (const uint8_t *)msg, strlen(msg));
    DEVICE_DELAY_US(1000);

    while (1)
    {

    }
}
