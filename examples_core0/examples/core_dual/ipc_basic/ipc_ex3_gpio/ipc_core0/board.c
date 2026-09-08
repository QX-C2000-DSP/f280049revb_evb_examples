// #############################################################################
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
// #############################################################################

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
    EALLOW;

    PinMux_init();
    GPIO_init();

    EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    //
    // PinMux for modules assigned to CPU1
    //

    // GPIO31 -> CPU1_LED Pinmux
    GPIO_setPinConfig(GPIO_31_GPIO31);
    // GPIO34 -> CPU2_LED Pinmux
    GPIO_setPinConfig(GPIO_34_GPIO34);
    // GPIO10 -> myGPIO10 Pinmux
    GPIO_setPinConfig(GPIO_10_GPIO10);
    // GPIO11 -> myGPIO11 Pinmux
    GPIO_setPinConfig(GPIO_11_GPIO11);
    // GPIO14 -> myGPIO14 Pinmux
    GPIO_setPinConfig(GPIO_14_GPIO14);
    // GPIO15 -> myGPIO15 Pinmux
    GPIO_setPinConfig(GPIO_15_GPIO15);
    //
    // PinMux for modules assigned to CPU2
    //
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init()
{
    CPU1_LED_init();
    CPU2_LED_init();
    myGPIO10_init();
    myGPIO11_init();
    myGPIO14_init();
    myGPIO15_init();
}

void CPU1_LED_init()
{
    GPIO_setPadConfig(CPU1_LED, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(CPU1_LED, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(CPU1_LED, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(CPU1_LED, GPIO_CORE_CPU1);
}
void CPU2_LED_init()
{
    GPIO_setPadConfig(CPU2_LED, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(CPU2_LED, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(CPU2_LED, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(CPU2_LED, GPIO_CORE_CPU1_CLA1);
}
void myGPIO10_init()
{
    GPIO_setPadConfig(myGPIO10, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myGPIO10, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIO10, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(myGPIO10, GPIO_CORE_CPU1_CLA1);
}
void myGPIO11_init()
{
    GPIO_setPadConfig(myGPIO11, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myGPIO11, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIO11, GPIO_DIR_MODE_IN);
    GPIO_setControllerCore(myGPIO11, GPIO_CORE_CPU1_CLA1);
}
void myGPIO14_init()
{
    GPIO_setPadConfig(myGPIO14, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myGPIO14, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIO14, GPIO_DIR_MODE_IN);
    GPIO_setControllerCore(myGPIO14, GPIO_CORE_CPU1);
}
void myGPIO15_init()
{
    GPIO_setPadConfig(myGPIO15, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myGPIO15, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(myGPIO15, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(myGPIO15, GPIO_CORE_CPU1);
}
