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
#define FRAME_ID     0x31      // 接收此帧则作为从机发送数据 用于测试可修改
#define DATA_LEN     8         // 接收长度

uint8_t recv_buf[8] = { 0 };
uint8_t send_buf[8] = { 0 };

uint8_t lin_id;               // 接收lin的id
uint8_t header_status   = 0;  // 指示接受了完整头部
uint8_t data_status     = 0;  // 指示接受了一帧完整数据
uint8_t frame_id_status = 0;  // 指示接受了指定报头
uint8_t status          = 0;  // 指示上一帧接收的是读还是写

void linISR(void);

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

void test_LIN_init()
{
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_LINA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);            // 使能外设

    LIN_setBaudrate(LINA_BASE, LIN_CLOCK, LIN_BAUDRATE);        // 设置波特率

    Interrupt_register(INT_LINA, &linISR);
    Interrupt_enable(INT_LINA);
    LIN_enableInterrupt(LINA_BASE, LIN_INT_LIDE | LIN_INT_RDYE); // 使能头接收和就绪中断

    LIN_writeLSEL(LINA_BASE, 0, AINC_EN, 0);                     // 设置自动递增FIFO索引 设置写入控制寄存器的延迟

    printf("Lin init complete \r\n");
}

__interrupt void linISR(void)
{
    uint16_t source = LIN_getLSR(LINA_BASE);

    if (source & LIN_LSR_LID)                       // 完整帧头部已接收
    {
        lin_id    = (uint8_t)LIN_getLID(LINA_BASE);
        header_status = 1;

        if (lin_id == FRAME_ID)                     // 如果接收到的帧头是指定ID
        {
            if (status == 0)
            {
                memcpy(send_buf, recv_buf, DATA_LEN);
            }

            LIN_writeLSEL(LINA_BASE, 0, AINC_EN, 0); // 作为从机把上次接收到的数据发出去
            LIN_writeBuffer(LINA_BASE, send_buf, SIZE_8_BYTES);
            LIN_sendCommand(LINA_BASE, CMD_RESPONSE_TX, MODE_SLAVE, 0, SIZE_8_BYTES);

            frame_id_status = 1;
            status          = 1;
        }

        else                                        // 作为从机接收数据
        {
            LIN_writeLSEL(LINA_BASE, 0, AINC_EN, 0);
            LIN_sendCommand(LINA_BASE, CMD_RESPONSE_RX, MODE_SLAVE, 0, SIZE_8_BYTES);
            status = 0;
        }

    }

    else if (source & LIN_LSR_RDY)                  // 指示空闲状态，接收完毕
    {
        LIN_readBuffer(LINA_BASE, recv_buf, SIZE_8_BYTES);
        if (status == 0)
        {
            data_status = 1;
        }

    }

    LIN_clearPendingFlags(LINA_BASE);
}

int main(void)
{
    Device_init();

    StdOutInit(&ScibRegs, 921600, 12, GPIO_12_SCIB_TX);

    GPIO_MuxConfig(28, GPIO_28_LINA_TX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(29, GPIO_29_LINA_RX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    printf("receive test begin\r\n");

    test_LIN_init();

    while (1)
    {

        if (header_status == 1)                      // 打印ID
        {
            printf("Header received. ID = %x\r\n", lin_id);
            header_status = 0;
        }

        if (data_status == 1 & lin_id != FRAME_ID)   // 打印数据
        {
            printf("data    ");
            for (uint32_t i = 0; i < sizeof(recv_buf); ++i)
            {
                printf("%x ", recv_buf[i]);
            }

            printf("\r\n");
            data_status = 0;
        }

        if (frame_id_status == 1)                   // 接收到指定ID
        {
            printf("Received the specified ID, sending as the slave device\r\n");
            frame_id_status = 0;
        }

    }

    return 0;
}
