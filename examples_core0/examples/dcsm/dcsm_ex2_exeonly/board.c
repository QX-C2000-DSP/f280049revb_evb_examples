#include "board.h"

//*****************************************************************************
//
// DCSM Configurations
//
//*****************************************************************************
uint32_t read_flash(u32 flash_addr)
{
    u32 regval;
    HWREG(0x01001000 + 0x220) = flash_addr;
    HWREG(0x01001000 + 0x224) = 0x1;
    while (1)
    {
        if (HWREG(0x01001000 + 0x234) == 0x07)
        {
            regval = HWREG(0x01001000 + 0x228);
            //            printf("flash read data : %x\n",regval);
            HWREG(0x01001000 + 0x250) = 0x10000;
            break;
        }
    }
    return regval;
}

//*****************************************************************************
//
// 通过配置B0Z1_csmkey寄存器进行解锁，此寄存器可以反复读写
//
//*****************************************************************************
void DCSM_unlockZone1(const DCSM_CSMPasswordKey *const psCMDKey)
{
    DCSM_setConfig(B0Z1_csmkey0, psCMDKey->csmKey0);
    DCSM_setConfig(B0Z1_csmkey1, psCMDKey->csmKey1);
    DCSM_setConfig(B0Z1_csmkey2, psCMDKey->csmKey2);
    DCSM_setConfig(B0Z1_csmkey3, psCMDKey->csmKey3);
}

//*****************************************************************************
//
// 通过配置B0Z1_csmkey寄存器进行上锁，此寄存器可以反复读写
//
//*****************************************************************************
void DCSM_lockZone1(void)
{
    DCSM_setConfig(B0Z1_csmkey0, 0x00000000); // 配置密钥为0 同时用户密钥不应设置为0
    DCSM_setConfig(B0Z1_csmkey1, 0x00000000); //_csmkey寄存器可反复读写，因此本步骤可逆
    DCSM_setConfig(B0Z1_csmkey2, 0x00000000); // 相当于清空密钥区
    DCSM_setConfig(B0Z1_csmkey3, 0x00000000);
}
