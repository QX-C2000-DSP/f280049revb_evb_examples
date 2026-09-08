/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "board.h"
#include "TFdriver.h"
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
    SPI_init();

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

    //
    // SPIB -> mySPI1 Pinmux
    //
    GPIO_MuxConfig(GPIO_PIN_SPIB_SIMO, mySPI1_SPISIMO_PIN_CONFIG, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(GPIO_PIN_SPIB_SOMI, mySPI1_SPISOMI_PIN_CONFIG, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(GPIO_PIN_SPIB_CLK, mySPI1_SPICLK_PIN_CONFIG, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_29_GPIO29);
    GPIO_setPadConfig(GPIO_PIN_SPIB_STE, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(GPIO_PIN_SPIB_STE, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(GPIO_PIN_SPIB_STE, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// SPI Configurations
//
//*****************************************************************************
void SPI_init()
{
    mySPI0_init();
    mySPI1_init();
}

/**
  * @brief  Initializes the SPI0 module with specified configuration.
  * @retval None
  *
  * This function configures the SPI0 module by disabling it, setting its configuration
  * (clock polarity, phase, mode, bitrate, and data width), setting the PTE signal polarity,
  * and then enabling the SPI0 module.
  */
void mySPI0_init()
{
    // Disable the SPI0 module before configuring
    SPI_disableModule(mySPI0_BASE);

    // Set the SPI0 configuration (LSPCLK frequency, polarity, phase, mode, bitrate, data width)
    SPI_setConfig(mySPI0_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0, SPI_MODE_CONTROLLER,
        mySPI0_BITRATE, mySPI0_DATAWIDTH);

    // Set the polarity for the PTE signal (active low)
    SPI_setPTESignalPolarity(mySPI0_BASE, SPI_PTE_ACTIVE_LOW);

    // Enable the SPI0 module after configuration
    SPI_enableModule(mySPI0_BASE);
}


/**
  * @brief  Initializes the SPI1 module with specified configuration.
  * @retval None
  *
  * This function enables the SPI1 peripheral clock, disables the SPI1 module before configuring,
  * sets its configuration (clock polarity, phase, mode, bitrate, and data width), and then
  * enables the SPI1 module.
  * Additionally, the Chip Select (CS) pin is set to high to prevent accidental chip operation
  * after power-up.
  */
void mySPI1_init()
{
    // Enable the clock for the SPI1 peripheral
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);

    // Disable the SPI1 module before configuring
    SPI_disableModule(mySPI1_BASE);

    // Set the SPI1 configuration (LSPCLK frequency, polarity, phase, mode, bitrate, data width)
    SPI_setConfig(mySPI1_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA1, SPI_MODE_CONTROLLER,
        mySPI1_BITRATE, mySPI1_DATAWIDTH);

    // Enable the SPI1 module after configuration
    SPI_enableModule(mySPI1_BASE);

    // Set the Chip Select (CS) pin to high to prevent accidental operation after power-up
    SPI_CS_HIGH();
}

