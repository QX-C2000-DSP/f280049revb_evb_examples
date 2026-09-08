
//#############################################################################
//
// FILE:   can_ex3_loopback.c
//
// TITLE:   CAN External Loopback Example
//
//! \addtogroup driver_example_list
//! <h1> CAN External Loopback </h1>
//!
//! This example shows the basic setup of CAN in order to transmit and receive
//! messages on the CAN bus.  The CAN peripheral is configured to transmit
//! messages with a specific CAN ID.  A message is then transmitted once per
//! second, using a simple delay loop for timing.  The message that is sent is
//! a 2 byte message that contains an incrementing pattern.
//!
//! This example sets up the CAN controller in External Loopback test mode.
//! Data transmitted is visible on the CANTXA pin and is received internally
//! back to the CAN Core. Please refer to details of the External Loopback
//! Test Mode in the CAN Chapter in the Technical Reference Manual.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - msgCount - A counter for the number of successful messages received
//!  - txMsgData - An array with the data being sent
//!  - rxMsgData - An array with the data that was received
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

#include "driverlib.h"
#include "device.h"
#include "board.h"


uint8_t errorFlag = 0U;
uint8_t msgCount = 0U;
uint8_t txMsgData[2], rxMsgData[2];

int main(void) {

    CAN_TBUF_Ctrl tx1Ctrl;
    tx1Ctrl.TTSEN = CAN_TTSEN_DISABLE;
    tx1Ctrl.BRS = CANFD_BRS_SLOW;
    tx1Ctrl.DLC = CAN_DLC2;
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
    // Setup send and receive buffers
    //
    txMsgData[0] = 0x01U;
    txMsgData[1] = 0x02U;
    rxMsgData[0] = 0x0U;
    rxMsgData[1] = 0x0U;

    for(;;)
    {
        //
        // Send CAN message data
        //
        CAN_fillMessage(CANB_BASE, CAN_TX_BUF_PTB, 0x111, &tx1Ctrl, txMsgData);
        CAN_startTx(CANB_BASE, CAN_TX_REQ_PTB);

        //
        // Delay before receiving the data
        //
        DEVICE_DELAY_US(500000);

        //
        // Read CAN message
        //
        if (CAN_readMessage(CANB_BASE, rxMsgData))
        {
            //
            // Check that received data matches sent data.
            // Device will halt here during debug if data doesn't match.
            //
            if((txMsgData[0] != rxMsgData[0]) ||
               (txMsgData[1] != rxMsgData[1]))
            {
                errorFlag = 1U;
            }
            else
            {
                //
                // Increment message received counter
                //
                msgCount++;
            }
        }
        else
        {
            //
            // Device will halt here during debug if no new data was received.
            //
            errorFlag = 1U;
        }

        //
        // Increment the value in the transmitted message data.
        //
        txMsgData[0] += 0x01U;
        txMsgData[1] += 0x01U;

        //
        // Reset data if exceeds a byte
        //
        if(txMsgData[0] > 0xFFU)
        {
            txMsgData[0] = 0U;
        }
        if(txMsgData[1] > 0xFFU)
        {
            txMsgData[1] = 0U;
        }
    }
}
