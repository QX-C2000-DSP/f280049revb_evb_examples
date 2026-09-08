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
#include <stdio.h>

volatile struct SCI_REGS *dbg_uart; // 调试使用的串口

// 用户层重载putchar回调函数
int putchar(int c)
{
    while (!dbg_uart->SCICTL2.bit.TXEMPTY)
        ;
    dbg_uart->SCITXBUF.all = c;
    while (!dbg_uart->SCICTL2.bit.TXEMPTY)
        ;

    return c;
}

// 使用打印SCI的串口初始化流程
void StdOutInit(volatile struct SCI_REGS *sci, int baudrate, uint32_t pin, uint32_t pin_mux)
{
    dbg_uart = sci;

    if (sci == &SciaRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    else if (sci == &ScibRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    else if (sci == &ScicRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIC);

    float tmp = (float)DEVICE_LSPCLK_FREQ / 8 / baudrate;
    if ((tmp - (int)tmp) >= 0.5)
        tmp = tmp + 1;
    int val = (int)tmp - 1;

    sci->SCICCR.bit.SCICHAR  = 7;
    sci->SCILBAUD.all        = val & 0xFF;
    sci->SCIHBAUD.all        = val >> 8;
    sci->SCICTL1.bit.SWRESET = 1;
    sci->SCICTL1.bit.TXENA   = 1;

    GPIO_setPinConfig(pin_mux);
    GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
}

#define BORAD_LED_GPIO 5

void board_led_init()
{
    GPIO_setDirectionMode(BORAD_LED_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_writePin(BORAD_LED_GPIO, 0);
}

void board_led_blink_fast()
{
    while (1)
    {
        GPIO_writePin(BORAD_LED_GPIO, 1);
        DEVICE_DELAY_US(200000);
        GPIO_writePin(BORAD_LED_GPIO, 0);
        DEVICE_DELAY_US(200000);
    }
}


void flash_test(uint32_t sectors_count)
{
    puts("flash test");
    Flash_initModule(1, 1);

    int i, sector, base, val;

    for (sector = 0; sector < sectors_count; sector++)
    {
        if (sector == 4)
        {
            continue;
        }
        base = FLASH0DATA_BASE + 4096 * sector;

        printf("sector %d test...\n", sector);
        Flash_eraseSector(sector);
        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != 0xFFFFFFFF)
            {
                printf("erase check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
                board_led_blink_fast();
            }
        }

        for (i = 0; i < 1024; i++)
            Flash_writeWord(base + i * 4, sector * i);

        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != sector * i)
            {
                printf("flash write check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
                board_led_blink_fast();
            }
        }

        Flash_eraseSector(sector); // 最后记得要重新擦除一下
        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != 0xFFFFFFFF)
            {
                printf("erase check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
                board_led_blink_fast();
            }
        }
    }

    puts("flash test pass!");
}

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
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    board_led_init();

    // remap printf: SCIB - GPIO12, baudrate = 921600
    StdOutInit(&ScibRegs, 921600, 12, GPIO_12_SCIB_TX);

    // 注意:flash最大时钟133Mhz, 默认使用sysclk且不分频, PLL时钟大于133Mhz时需要先配置flash分频
    Flash_setClkDiv(4);
    flash_test(256);

    while(1)
    {

    }
}

//
// End of File
//
