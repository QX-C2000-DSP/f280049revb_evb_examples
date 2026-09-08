//#############################################################################
//
// FILE:   canfd_ex1_external_transmit.c
//
// TITLE:   CAN External Transmit Example
//
//! \addtogroup driver_example_list
//! <h1> CAN-A to CAN-B External Transmit </h1>
//!
//! This example initializes CAN module A and CAN module B for external
//! communication. CAN-A module is setup to transmit number of times to
//! the CAN-B module.
//! CAN-B module is setup to trigger an interrupt service routine (ISR) when
//! data is received. An error flag will be set if the transmitted data doesn't
//! match the received data.
//!
//! \note Both CAN modules on the device need to be connected to each other
//!       via CAN transceivers.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with two CAN transceivers
//!
//! \b External \b Connections \n
//!  - ControlCARD CANA is on DEVICE_GPIO_PIN_CANTXA (CANTXA)
//!  - and DEVICE_GPIO_PIN_CANRXA (CANRXA)
//!  - ControlCARD CANB is on DEVICE_GPIO_PIN_CANTXB (CANTXB)
//!  - and DEVICE_GPIO_PIN_CANRXB (CANRXB)
//!
//! \b Watch \b Variables \n
//!  - TXCOUNT - Adjust to set the number of messages to be transmitted
//!  - txMsgCount - A counter for the number of messages sent
//!  - rxMsgCount - A counter for the number of messages received
//!  - send_buf - An array with the data being sent
//!  - recv_buf - An array with the data that was received
//!  - errorFlag - A flag that indicates an error has occurred
//!  - canTestFinishFlag - A flag that indicates the test is over.
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
#include "string.h"

//
// Defines
//
#define TXCOUNT  100

//
// Globals
//
volatile unsigned long i;
volatile uint32_t txMsgCount = 0;
volatile uint32_t rxMsgCount = 0;
uint8_t recv_buf[64] = { 0 };
uint8_t send_buf[64] = { 'c', 'a', 'n',' ', 't', 'e', 's', 't'};
uint8_t errorFlag = 0;
uint8_t canTestFinishFlag = 0;

//
// Function Prototypes
//
__interrupt void canbISR(void);

int main(void)
{

    CAN_TBUF_Ctrl tx1Ctrl;
    tx1Ctrl.TTSEN = CAN_TTSEN_DISABLE;
    tx1Ctrl.BRS = CANFD_BRS_FAST;
    tx1Ctrl.DLC = CAN_DLC8;
    tx1Ctrl.FDF = CAN_FDF_CANFD;
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

    for(i = 0; i < TXCOUNT; i++)
    {

        //
        // Verify that the number of transmitted messages equal the number of
        // messages received before sending a new message
        //
        if(txMsgCount == rxMsgCount)
        {

            memset(recv_buf, 0, sizeof(recv_buf));
            CAN_fillMessage(CANA_BASE, CAN_TX_BUF_PTB, 0x222, &tx1Ctrl, send_buf);
            CAN_startTx(CANA_BASE, CAN_TX_REQ_PTB);
            txMsgCount++;
            while(txMsgCount != rxMsgCount);
            //
            // Verify that the sent and received data are identical
            //
            verify_data_byte(send_buf, recv_buf, 8);

        }
        else
        {
            errorFlag = 1;
            break;
        }

        //
        // Delay 0.25 second before continuing
        //
        DEVICE_DELAY_US(250000);
    }

    if(txMsgCount == rxMsgCount)
    {
        //
        // Test Finish!
        //
        canTestFinishFlag = 1;
    }

    return 0;
}


//
// canbISR
//
__interrupt void canbISR(void)
{
    if (CAN_getStatus(CANB_BASE, CAN_FLAG_RX))
    {
        CAN_readMessage(CANB_BASE, recv_buf);
        rxMsgCount++;
    }
    CAN_clearInterruptStatus(CANB_BASE, CAN_FLAG_CLR_ALL);

}
