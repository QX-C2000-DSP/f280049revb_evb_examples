//#############################################################################
//
// FILE:   can_ex4_loopback_interrupts.c
//
// TITLE:   CAN External Loopback with Interrupts Example
//
//! \addtogroup driver_example_list
//! <h1> CAN External Loopback with Interrupts </h1>
//!
//! This example shows the basic setup of CAN in order to transmit and receive
//! messages on the CAN bus.  The CAN peripheral is configured to transmit
//! messages with a specific CAN ID.  A message is then transmitted once per
//! second, using a simple delay loop for timing.  The message that is sent is
//! a 4 byte message that contains an incrementing pattern.  A CAN interrupt
//! handler is used to confirm message transmission and count the number of
//! messages that have been sent.
//!
//! This example sets up the CAN controller in External Loopback test mode.
//! Data transmitted is visible on the CANTXB pin and is received internally
//! back to the CAN Core. Please refer to details of the External Loopback
//! Test Mode in the CAN Chapter in the Technical Reference Manual.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - txMsgCount - A counter for the number of messages sent
//!  - rxMsgCount - A counter for the number of messages received
//!  - txMsgData - An array with the data being sent
//!  - rxMsgData - An array with the data that was received
//!  - errorFlag - A flag that indicates an error has occurred
//!
//
//#############################################################################
//
//
// $Copyright:
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
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
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
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define MSG_DATA_LENGTH    4
#define TX_MSG_OBJ_ID      1
#define RX_MSG_OBJ_ID      2

//
// Globals
//
volatile uint32_t txMsgCount = 0;
volatile uint32_t rxMsgCount = 0;
volatile uint32_t errorFlag = 0;
uint8_t txMsgData[4];
uint8_t rxMsgData[4];

//
// Function Prototypes
//
__interrupt void canbISR(void);

//
// Main
//
int main(void)
{
    CAN_TBUF_Ctrl tx1Ctrl;
    tx1Ctrl.TTSEN = CAN_TTSEN_DISABLE;
    tx1Ctrl.BRS = CANFD_BRS_SLOW;
    tx1Ctrl.DLC = CAN_DLC4;
    tx1Ctrl.FDF = CAN_FDF_CAN20;
    tx1Ctrl.IDE = CAN_IDE_STANDARD;
    tx1Ctrl.RTR = CAN_RTR_DATA;

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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;
    //
    // Initialize the transmit message object data buffer to be sent
    //
    txMsgData[0] = 0x12;
    txMsgData[1] = 0x34;
    txMsgData[2] = 0x56;
    txMsgData[3] = 0x78;

    //
    // Loop Forever - A new message will be sent once per second.
    //
    for(;;)
    {

        //
        // Verify that the number of transmitted messages equal the number of
        // messages received before sending a new message
        //
        if(txMsgCount == rxMsgCount)
        {
            //
            // Transmit the message.
            //
            CAN_fillMessage(CANB_BASE, CAN_TX_BUF_PTB, 0x1UL, &tx1Ctrl, txMsgData);
            CAN_startTx(CANB_BASE, CAN_TX_REQ_PTB);
        }
        else
        {
            errorFlag = 1;
        }

        //
        // Delay 1 second before continuing
        //
        DEVICE_DELAY_US(1000000);

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
    }
}

//
// CAN ISR - The interrupt service routine called when a CAN interrupt is
//           triggered.  It checks for the cause of the interrupt, and
//           maintains a count of all messages that have been transmitted.
//
__interrupt void
canbISR(void)
{
    if (CAN_getStatus(CANB_BASE, CAN_FLAG_PTB_TX) == SET)
    {
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

    if (CAN_getStatus(CANB_BASE, CAN_FLAG_RX))
    {
        CAN_readMessage(CANB_BASE, rxMsgData);
        //
        // Increment the counter after a message has been received.
        //
        rxMsgCount++;

        //
        // Since the message was received, clear any error flags.
        //
        errorFlag = 0;

        //
        // Verify that the sent and received data are identical
        //
        verify_data_byte(txMsgData, rxMsgData, 4);
    }

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

//
// End of File
//
