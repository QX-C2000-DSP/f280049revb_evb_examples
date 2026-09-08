//#############################################################################
//
// FILE:    gpio_ex3_interrupt.c
//
// TITLE:   Device GPIO Interrupt
//
//! \addtogroup driver_example_list
//! <h1> Device GPIO Interrupt </h1>
//!
//! Configures the device GPIOs through the sysconfig file. One GPIO output
//! pin, and one GPIO input pin is configured. The example then configures the
//! GPIO input pin to be the source of an external interrupt which toggles
//! the GPIO output pin.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Hefei Qianxin Technology http://www.starrystonetech.com/
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

#define LED4 5
#define LED5 9

//
// Interrupt Handler
//
__interrupt void gpioInterruptHandler(void);

void my_led_init()
{
	GPIO_setDirectionMode(LED4, GPIO_DIR_MODE_OUT);
	GPIO_setPadConfig(LED4, GPIO_PIN_TYPE_STD);
	GPIO_setControllerCore(LED4, GPIO_CORE_CPU1);
	
	GPIO_setDirectionMode(LED5, GPIO_DIR_MODE_OUT);
	GPIO_setPadConfig(LED5, GPIO_PIN_TYPE_STD);
	GPIO_setControllerCore(LED5, GPIO_CORE_CPU1);
}

//
// Main
//
int main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();

    //
    // Initializes PIE and clear PIE registers. Disables CPU interrupts.
    // and clear all CPU interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board Initialization
    //
    Board_init();

    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_BOTH_EDGES);
    GPIO_setInterruptPin(myGPIOInputInterrupt0, GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    Interrupt_register(INT_XINT1, &gpioInterruptHandler);
    Interrupt_enable(INT_XINT1);

    //
    // Enables CPU interrupts
    //
    Interrupt_enableGlobal();

    my_led_init();

    //
    // Loop.
    //
    for(;;)
    {
        GPIO_togglePin(LED4);
        GPIO_togglePin(LED5);
        DEVICE_DELAY_US(10000000);
    }
}

__interrupt void gpioInterruptHandler(void)
{
    GPIO_togglePin(LED4);
    GPIO_togglePin(LED5);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
    Interrupt_enable(INT_XINT1);
}


//
// End of File
//

