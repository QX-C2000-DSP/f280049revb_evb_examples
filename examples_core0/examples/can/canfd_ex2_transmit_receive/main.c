
//#############################################################################
//
// FILE:   can_ex2_transmit_receive.c
//
// TITLE:   CAN Configuration for Transmit and Receive.
//
//! \addtogroup driver_example_list
//! <h1> CAN Transmit and Receive Configurations </h1>
//!
//! This example shows the basic setup of CAN in order to transmit or receive
//! messages on the CAN bus with a specific Message ID. The CAN Controller is
//! configured according to the selection of the define.
//!
//! When the TRANSMIT define is selected, the CAN Controller acts as a
//! Transmitter and sends data to the second CAN Controller connected
//! externally.If TRANMSIT is not defined the CAN Controller acts as a Receiver
//! and waits for message to be transmitted by the External CAN Controller.
//!
//! \note CAN modules on the device need to be connected to via CAN
//!       transceivers.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver.
//!
//!
//! \b Watch \b Variables \b Transmit \Configuration \n
//!  - MSGCOUNT   - Adjust to set the number of messages
//!  - txMsgCount - A counter for the number of messages sent
//!  - txMsgData  - An array with the data being sent
//!  - errorFlag  - A flag that indicates an error has occurred
//!  - rxMsgCount - Has the initial value as No. of Messages to be received
//!                 and decrements with each message.
//!
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Comment to Make the CAN Controller work as a Receiver.
//
#define TRANSMIT

//
// Defines
//
#define MSGCOUNT        1000

//
// Globals
//
#ifdef TRANSMIT
volatile uint32_t txMsgCount = 0;
uint32_t txMsgSuccessful  = 1;
uint8_t txMsgData[4];
#else
volatile uint32_t rxMsgCount = MSGCOUNT;
uint8_t rxMsgData[4];
#endif
volatile unsigned long i;
volatile uint32_t errorFlag = 0;

//
// Function Prototypes
//
__interrupt void canbISR(void);

//
// Main
//
int main(void)
{
    //
    // Initialize device clock and peripherals
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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

#ifdef TRANSMIT
    //
    // Set can TBUF control.
    //
    CAN_TBUF_Ctrl tx1Ctrl;
    tx1Ctrl.TTSEN = CAN_TTSEN_DISABLE;
    tx1Ctrl.BRS = CANFD_BRS_FAST;
    tx1Ctrl.DLC = CAN_DLC4;
    tx1Ctrl.FDF = CAN_FDF_CANFD;
    tx1Ctrl.IDE = CAN_IDE_EXTEND;
    tx1Ctrl.RTR = CAN_RTR_DATA;

    //
    // Initialize the transmit message object data buffer to be sent
    //
    txMsgData[0] = 0x12;
    txMsgData[1] = 0x34;
    txMsgData[2] = 0x56;
    txMsgData[3] = 0x78;
    //
    // Transmit messages from CAN-A.
    //
    for(i = 0; i < MSGCOUNT; i++)
    {

        //
        // Transmit the message.
        //
        CAN_fillMessage(CANB_BASE, CAN_TX_BUF_PTB, 0x12131415UL, &tx1Ctrl, txMsgData);
        CAN_startTx(CANB_BASE, CAN_TX_REQ_PTB);

        //
        // Delay 0.25 second before continuing
        //
        DEVICE_DELAY_US(250000);

        while(txMsgSuccessful);
        //
        // Increment the value in the transmitted message data.
        //
        txMsgData[0] += 0x01;
        txMsgData[1] += 0x01;
        txMsgData[2] += 0x01;
        txMsgData[3] += 0x01;

        //
        // Reset data if exceeds a byte
        //
        if(txMsgData[0] > 0xFF)
        {
            txMsgData[0] = 0;
        }
        if(txMsgData[1] > 0xFF)
        {
            txMsgData[1] = 0;
        }
        if(txMsgData[2] > 0xFF)
        {
            txMsgData[2] = 0;
        }
        if(txMsgData[3] > 0xFF)
        {
            txMsgData[3] = 0;
        }

        //
        // Update the flag for next message.
        //
        txMsgSuccessful  = 1;
    }
#else
    //
    // Loop to keep receiving data from another CAN Controller.
    //
    while(rxMsgCount)
    {
    }
#endif

}

//
// CAN A ISR - The interrupt service routine called when a CAN interrupt is
//             triggered on CAN module A.
//
__interrupt void canbISR(void)
{

#ifdef TRANSMIT
    if (CAN_getStatus(CANB_BASE, CAN_FLAG_PTB_TX) == SET)
    {
        txMsgSuccessful = 0;
        //
        // Increment a counter to keep track of how many messages have been
        // transmitted. In a real application this could be used to set flags to
        // indicate when a message is transmitted.
        //
        txMsgCount++;
        //
        // Since the message was transmitted, clear any error flags.
        //
        errorFlag = 0;
    }
#else
    if (CAN_getStatus(CANB_BASE, CAN_FLAG_RX))
    {
        CAN_readMessage(CANB_BASE, rxMsgData);
        //
        // Decrement the counter after a message has been received.
        //
        rxMsgCount--;

        //
        // Since the message was received, clear any error flags.
        //
        errorFlag = 0;
    }
#endif

    //
    // check error.
    //
    if ((CAN_getStatus(CANB_BASE, CAN_FLAG_ERR_INT) == SET)       || \
         (CAN_getStatus(CANB_BASE, CAN_FLAG_ERR_PASSIVE) == SET)  || \
         (CAN_getStatus(CANB_BASE, CAN_FLAG_ARBITR_LOST) == SET)  || \
         (CAN_getStatus(CANB_BASE, CAN_FLAG_BUS_ERR) == SET))
    {
        errorFlag = 1;
    }

    CAN_clearInterruptStatus(CANB_BASE, CAN_FLAG_CLR_ALL);

}
