// #############################################################################
//
//  Copyright (C) 2024 STARRYSTONETECH - http://www.starrystonetech.com/
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of STARRYSTONETECH nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// #############################################################################

#include "device.h"
#include "driverlib.h"
#include <string.h>
#include "board.h"
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

int main(void)
{
    Device_init();

    StdOutInit(&ScibRegs, 921600, 12, GPIO_12_SCIB_TX);

    printf("test DCSM LOCK test \r\n");

    DCSM_SecurityStatus status1;
    uint32_t rdata;


    DCSM_setConfig(B0Z1_grabsect, CONFIGURED_GARBSECT_ONE);

    // grabsect表示对flash操作 最后两位置0表示控制第一小块0x30000000~0x3000FFFF
    // 本例只将flash第一块内存配置为Zone1
    DCSM_setConfig(B0Z1_csmpswd0, 0xF0F0F0F0);
    DCSM_setConfig(B0Z1_csmpswd1, 0xF0F0F0F0);
    DCSM_setConfig(B0Z1_csmpswd2, 0xF0F0F0F0); // 密钥 密钥不应为全F 全F无法上锁
    DCSM_setConfig(B0Z1_csmpswd3, 0xF0F0F0F0); // 同时密钥不应为全0 以作规范

    rdata = HWREG(DCSM_LINK_LOCATION); // 此处为link寄存器值
    if (rdata != 0)
    {
        printf("link configure error rdata:%x\r\n", rdata);
    }

    rdata = HWREG(DCSM_GRABSECT_LOCATION); // 此处为grabsect寄存器值
    if (rdata != 0)
    {
        printf("grabsect configure error rdata:%x\r\n", rdata);
    }
    else
    {
        printf("lock over \r\n");
    }



    DCSM_CSMPasswordKey csmK;
    csmK.csmKey0 = 0xF0F0F0F0;
    csmK.csmKey1 = 0xF0F0F0F0;
    csmK.csmKey2 = 0xF0F0F0F0;
    csmK.csmKey3 = 0xF0F0F0F0;

    DCSM_unlockZone1(&csmK); // 解锁

    rdata = HWREG(DCSM_LINK_LOCATION);
    if (rdata != UNCONFIGURED_LINK_VALUE)
    {
        printf("Read link with unlock error\r\n");
    }

    rdata = HWREG(DCSM_GRABSECT_LOCATION);
    if (rdata != CONFIGURED_GARBSECT_ONE)
    {
        printf("Read grabsect with unlock error\r\n");
    }
    else
    {
        printf("unlock over \r\n");
    }

    DCSM_lockZone1(); // 通过更改B0Z1_csmkey值进行重新上锁
                      // 若想直接更改密钥值需要配置link寄存器以重新获得权限更改密钥
                      // 但不同的是配置link是一次性编程

    rdata = HWREG(DCSM_LINK_LOCATION);
    if (rdata == 0)
    {
        printf("Re-lock over\r\n");
    }
    else
    {
        printf("Re-lock error:%x\r\n", rdata);
    }

    printf("test over\r\n");

    return 0;
}
