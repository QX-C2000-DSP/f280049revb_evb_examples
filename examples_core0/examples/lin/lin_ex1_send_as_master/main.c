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

#include "device.h"
#include "driverlib.h"
#include <string.h>
#include <stdio.h>

#define LIN_BAUDRATE 20000     // 20k
#define LIN_CLOCK    100000000 // 100Mhz

uint8_t send_buf[8] = { 0 };
uint8_t lin_id = 0x12;

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

void test_send()
{
    LIN_setIDByte(LINA_BASE, lin_id);                                           // 作为主机设置发送ID
    LIN_setBaudrate(LINA_BASE, LIN_CLOCK, LIN_BAUDRATE);                        // 设置波特率

    LIN_setHeaderDelay(LINA_BASE, 0);                                           // 设置在LIN总线上发送帧头部之前的额外延迟
    LIN_sendCommand(LINA_BASE, CMD_SEND_HEADER, MODE_MASTER, 0, SIZE_0_BYTES);  // 作为主机发送帧头
    LIN_waitForReady(LINA_BASE);

    LIN_writeLSEL(LINA_BASE, 0, AINC_EN, 0);                                    // 设置自动递增FIFO索引 设置写入控制寄存器的延迟

    LIN_writeBuffer(LINA_BASE, send_buf, SIZE_8_BYTES);
    LIN_sendCommand(LINA_BASE, CMD_RESPONSE_TX, MODE_MASTER, 0, SIZE_8_BYTES);  // 作为主机发送数据

    LIN_waitForReady(LINA_BASE);
    LIN_clearPendingFlags(LINA_BASE);
}

int main(void)
{
    Device_init();

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
    Interrupt_enable(INT_LINA);

    StdOutInit(&ScibRegs, 921600, 12, GPIO_12_SCIB_TX);

    GPIO_MuxConfig(28, GPIO_28_LINA_TX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(29, GPIO_29_LINA_RX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    printf("send test begin\r\n");
    DEVICE_DELAY_US(100000);

    for (int k = 0; k < 10; k++)
    {
        lin_id = k + 0x12;
        for (int i = 0; i < sizeof(send_buf); i++)
        {
            send_buf[i] = i + k;
        }

        test_send();
        printf("No.%d   LIN_ID=%x   ", k, lin_id);

        for (int j = 0; j < sizeof(send_buf); j++)
        {
            printf("%x ", send_buf[j]);
        }

        printf("\r\n");
        DEVICE_DELAY_US(100000);
    }

    return 0;
}
