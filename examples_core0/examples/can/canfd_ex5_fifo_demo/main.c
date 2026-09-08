
//#############################################################################
//
// FILE:   can_ex5_fifo_demo.c
//
// TITLE:  CAN FIFO Mode Demo - Show 16-slot STB/RB Hardware FIFO Usage
//
//! \addtogroup driver_example_list
//! <h1> CAN FIFO Mode Demo </h1>
//!
//! This example demonstrates the hardware FIFO functionality of the CAN module
//! with 16-slot STB (Secondary Transmit Buffer) and 16-slot RB (Receive Buffer).
//!
//! The CAN module is configured in FIFO mode (TSMODE = 0), which means frames
//! are transmitted in the order they were filled (first-in-first-out), rather
//! than by priority (ID order).
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!  - Another CAN node (or loopback mode for single board test)
//!
//! \b Example \b Features \n
//!  - Shows how to fill 16-slot STB FIFO and transmit all at once
//!  - Shows how to read 16-slot RB FIFO in interrupt handler
//!  - Uses FIFO mode (not priority mode) for transmit
//!
//! \b Watch \b Variables \n
//!  - txMsgCount   - Number of messages successfully transmitted
//!  - rxMsgCount   - Number of messages received
//!  - txMsgData    - Transmit data buffer
//!  - rxMsgData    - Receive data buffer
//!  - errorFlag    - Error indicator flag
//!
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
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
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
// Defines
//
#define MSG_ID_TX           0x200       // Transmit message ID (standard)
#define MSG_ID_RX           0x100       // Receive filter base ID
#define MSG_DATA_LEN        8           // CAN data length (8 bytes)
#define BATCH_TX_COUNT      16          // Number of frames to batch transmit

//
// Globals
//
volatile uint32_t txMsgCount = 0;       // Transmit success counter
volatile uint32_t rxMsgCount = 0;       // Receive counter
volatile uint32_t errorFlag = 0;        // Error flag

uint8_t txSeqNumber = 0;                // Sequence number for batch transmit

uint8_t rxMsgData[MSG_DATA_LEN];        // Receive data buffer

//
// Function Prototypes
//
__interrupt void canbISR(void);
static void fillAndSendBatchMessages(void);
static void sendSingleMessage(void);

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
    // Note: CAN_init() configures STB in FIFO mode (CAN_STB_PRIO_MD_DISABLE)
    //
    Board_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;
    //
    // Batch Mode: Fill all 16 STB slots and transmit at once
    // This demonstrates the hardware FIFO capability
    //
    while(1)
    {
        //
        // Fill 16 STB slots with sequential data
        //
        fillAndSendBatchMessages();

        //
        // Wait for all 16 messages to be transmitted (interrupt driven)
        // txMsgCount is incremented in ISR
        //
        while(txMsgCount < BATCH_TX_COUNT);

        //
        // Delay before next batch
        //
        DEVICE_DELAY_US(1000000);

        //
        // Reset counter for next batch
        //
        txMsgCount = 0;

        //
        // Increment sequence number for next batch
        //
        txSeqNumber++;
    }
}

//
// Fill 16 STB slots and transmit all at once (FIFO mode demo)
//
static void fillAndSendBatchMessages(void)
{
    CAN_TBUF_Ctrl txCtrl;
    uint8_t msgData[MSG_DATA_LEN];
    uint16_t i;

    //
    // Configure TBUF control word for all frames
    //
    txCtrl.TTSEN = CAN_TTSEN_DISABLE;
    txCtrl.BRS = CANFD_BRS_SLOW;        // Use slow bit rate
    txCtrl.DLC = CAN_DLC8;              // 8 bytes data
    txCtrl.FDF = CAN_FDF_CAN20;         // Classic CAN frame
    txCtrl.IDE = CAN_IDE_STANDARD;      // Standard ID (11-bit)
    txCtrl.RTR = CAN_RTR_DATA;          // Data frame

    //
    // Fill all 16 STB slots with sequential frames
    // In FIFO mode, frames are sent in the order they are filled
    //
    for(i = 0; i < BATCH_TX_COUNT; i++)
    {
        //
        // Prepare message data
        // Byte 0: Sequence number of this batch
        // Byte 1: Frame index (0-15)
        // Bytes 2-7: Fixed pattern
        //
        msgData[0] = txSeqNumber;
        msgData[1] = (uint8_t)i;
        msgData[2] = 0xAA;
        msgData[3] = 0xBB;
        msgData[4] = 0xCC;
        msgData[5] = 0xDD;
        msgData[6] = 0xEE;
        msgData[7] = 0xFF;

        //
        // Fill STB slot
        // CAN_fillMessage automatically advances to next STB slot after write
        // When all 16 slots are filled, TSFF flag is set
        //
        CAN_fillMessage(CANB_BASE, CAN_TX_BUF_STB, MSG_ID_TX, &txCtrl, msgData);
    }

    //
    // Start transmission of all STB frames at once
    // TSSTAT will show transmission progress (0=empty, 3=full)
    //
    CAN_startTx(CANB_BASE, CAN_TX_REQ_STB_ALL);
}

//
// CAN B ISR - The interrupt service routine called when a CAN interrupt is
//             triggered on CAN module B.
//
// In this example, we handle:
// 1. STB transmit complete (TSIF) - increments txMsgCount
// 2. Receive complete (RIF) - reads all available RB slots
// 3. Error interrupts
//
__interrupt void canbISR(void)
{
    //
    // Check for STB transmit complete (TSIF)
    // This fires when STB transmission completes successfully
    //
    if(CAN_getStatus(CANB_BASE, CAN_FLAG_STB_TX) == SET)
    {
        //
        // Increment transmit counter
        // In batch mode, this will count up to BATCH_TX_COUNT
        //
        txMsgCount++;
    }

    //
    // Check for receive interrupt (RIF)
    // When RFIF fires, we should read all available RB slots
    // RB is 16-slot FIFO, RSTAT shows how many frames are pending
    //
    if(CAN_getStatus(CANB_BASE, CAN_FLAG_RX) == SET)
    {
        //
        // Read all available messages from RB FIFO
        // RSTAT: 0=empty, 1=less than warning limit, 2=warning, 3=full
        //
        while(CAN_getRxBufStatus(CANB_BASE) != CAN_RX_BUF_EMPTY)
        {
            //
            // Read message from RB
            // CAN_readMessage automatically releases RB slot (sets RREL)
            // and advances to next slot
            //
            if(CAN_readMessage(CANB_BASE, rxMsgData))
            {
                rxMsgCount++;
            }
        }
    }

    //
    // Check for receive buffer warning (RAFIF)
    // Filled RB slots >= warning limit (configured in LIMIT.AFWL)
    //
    if(CAN_getStatus(CANB_BASE, CAN_FLAG_RX_BUF_WARN) == SET)
    {
        //
        // RB is filling up - application should read messages soon
        // This is a warning before RB becomes full
        //
    }

    //
    // Check for receive buffer full (RFIF)
    //
    if(CAN_getStatus(CANB_BASE, CAN_FLAG_RX_BUF_FULL) == SET)
    {
        //
        // RB is completely full (16/16 slots)
        // Next received frame may be lost if not read quickly
        //
    }

    //
    // Check for receive overrun (ROIF)
    // Frame lost because RB was full
    //
    if(CAN_getStatus(CANB_BASE, CAN_FLAG_RX_OVERRUN) == SET)
    {
        //
        // Frame lost due to RB overflow
        //
        errorFlag = 1;
    }

    //
    // Check for error interrupts
    //
    if((CAN_getStatus(CANB_BASE, CAN_FLAG_ERR_INT) == SET) ||
       (CAN_getStatus(CANB_BASE, CAN_FLAG_BUS_ERR) == SET) ||
       (CAN_getStatus(CANB_BASE, CAN_FLAG_ERR_PASSIVE) == SET))
    {
        errorFlag = 1;
    }

    //
    // Clear all interrupt flags
    //
    CAN_clearInterruptStatus(CANB_BASE, CAN_FLAG_CLR_ALL);
}
