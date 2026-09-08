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

    puts("test DCSM LINK test \r\n");

    DCSM_SecurityStatus status1;
    uint32_t rdata;

    // grabsect表示对flash操作 最后两位置0表示控制第一小块0x30000000~0x3000FFFF
    DCSM_setConfig(B0Z1_grabsect, CONFIGURED_GARBSECT_ONE);

    // 密钥
    DCSM_setConfig(B0Z1_csmpswd0, 0xF0F0F0F0);
    DCSM_setConfig(B0Z1_csmpswd1, 0xF0F0F0F0);
    DCSM_setConfig(B0Z1_csmpswd2, 0xF0F0F0F0);
    DCSM_setConfig(B0Z1_csmpswd3, 0xF0F0F0F0);

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
        printf("lock over the first time\r\n");
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
        printf("unlock over the first time\r\n");
    }

    // configure lock parameter
    DCSM_setConfig(B0Z1_link1, CONFIGURED_LINK_VALUE);     // 操作link寄存器可以重新上一次锁
    DCSM_setConfig(B0Z1_link2, CONFIGURED_LINK_VALUE);     // 三个link需要相同 作为一种校验措施 这里只修改最后一位将1改为0即可
    DCSM_setConfig(B0Z1_link3, CONFIGURED_LINK_VALUE);     // 修改link以使用不同的Z1配置

    DCSM_setConfig(B0Z1_grabsect, CONFIGURED_GARBSECT_ONE);
    DCSM_setConfig(B0Z1_csmpswd0, 0xF0F0F0F1); /*第二次密码若和第一次相同会保持解锁，
                                                 因为key寄存器里的值与第二次上锁值匹配*/

    DCSM_setConfig(B0Z1_csmpswd1, 0xF0F0F0F1);
    DCSM_setConfig(B0Z1_csmpswd2, 0xF0F0F0F1);
    DCSM_setConfig(B0Z1_csmpswd3, 0xF0F0F0F1);

    rdata = HWREG(DCSM_LINK_LOCATION);
    if (rdata != 0)
    {
        printf("link configure error rdata the second time:%x\r\n", rdata);
    }

    rdata = HWREG(DCSM_GRABSECT_LOCATION);
    if (rdata != 0)
    {
        printf("grabsect configure error rdata the second time:%x\r\n", rdata);
    }
    else
    {
        printf("lock over the second time\r\n");
    }

    // unlock twice
    DCSM_CSMPasswordKey csmK1;
    csmK1.csmKey0 = 0xF0F0F0F1;
    csmK1.csmKey1 = 0xF0F0F0F1;
    csmK1.csmKey2 = 0xF0F0F0F1;
    csmK1.csmKey3 = 0xF0F0F0F1;
    
    // unlock
    DCSM_unlockZone1(&csmK1); // 解锁  密码与第二次设置相同

    rdata = HWREG(DCSM_LINK_LOCATION);
    if (rdata != CONFIGURED_LINK_VALUE)
    {
        printf("Read link with unlock error the second time:%x\r\n", rdata);
    }
    else
    {
        printf("Link configuration successful\r\n");
    }

    rdata = HWREG(DCSM_GRABSECT_LOCATION);
    if (rdata != CONFIGURED_GARBSECT_ONE)
    {
        printf("Read grabsect with unlock error the second time:%x\r\n", rdata);
    }
    else
    {
        printf("unlock over the second time\r\n");
    }

    printf("test over\r\n");

    return 0;
}
