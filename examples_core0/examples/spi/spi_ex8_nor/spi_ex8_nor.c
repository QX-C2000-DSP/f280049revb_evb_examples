//#############################################################################
//
// FILE:   spi_ex8_nor.c
//
// TITLE:  SPI EEPROM
//
//! \addtogroup driver_example_list
//! <h1>SPI EEPROM</h1>
//!
//! This program will write 8 bytes to EEPROM and read them back. The device
//! communicates with the EEPROM via SPI and specific opcodes. This example is
//! written to work with the SPI Serial EEPROM AT25128/256.
//! Note: SPI character length is configured to 8 bits in SysConfig, and not
//! changed throughout the execution of the program. Runtime updation of
//! character length when CS pin is not controlled by the SPI module can lead
//! to unpredictable behaviour
//!
//! \b External \b Connections \n
//!  - Connect external SPI EEPROM
//!  - Connect GPIO16 (PICO) to external EEPROM SI pin
//!  - Connect GPIO17 (POCI) to external EEPROM SO pin
//!  - Connect GPIO56 (CLK) to external EEPROM SCK pin
//!  - Connect GPIO11 (CS) to external EEPROM CS pin
//!  - Connect the external EEPROM VCC and GND pins
//!
//! \b Watch \b Variables \n
//!  - writeBuffer - Data that is written to external EEPROM
//!  - readBuffer  - Data that is read back from EEPROM
//!  - error       - Error count
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 STARRYSTONETECH - http://www.starrystonetech.com//
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
#include "w25q64.h"

//
// Defines for Chip Select toggle.
//


#define TEST_DATA_COUNT   256

uint8_t spi_send_data[TEST_DATA_COUNT];
uint8_t spi_rcv_data[TEST_DATA_COUNT];

//
// Main
//
int main(void)
{
	uint32_t jedec_id = 0;
    uint16_t i;
	uint16_t succes_count = 0;
	uint16_t fail_count = 0;
	
    for (i = 0; i < TEST_DATA_COUNT; i++)
    {
    	spi_send_data[i] = i;
    	spi_rcv_data[i] = 0;
    }
	

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Board initialization
    //
    Board_init();

	jedec_id = w25q64_read_jedec_id();
	
	w25q64_erase(SPIB_BASE, 0, 0x10000);
    w25q64_write(SPIB_BASE, 0, TEST_DATA_COUNT, spi_send_data);
    w25q64_read(SPIB_BASE, 0, TEST_DATA_COUNT, spi_rcv_data);
	
    for (i = 0; i < TEST_DATA_COUNT; i++)
    {
        if (spi_rcv_data[i] ==  spi_send_data[i])
        {
            succes_count++;
        }
		else
		{
            fail_count++;
		}
    }

    while(1);
}


