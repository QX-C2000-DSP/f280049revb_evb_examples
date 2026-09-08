#include "driverlib.h"

void Flash_initModule(u32 div, u32 qspi_en)
{
    Flash_setClkDiv(div);
    if (qspi_en)
        Flash_enableQspiMode();
    else
        Flash_disableQspiMode();
}

/* GD25Q80E Flash One Sector = 4K */
void Flash_eraseSector(vu32 sector_num)
{
    //
    // Check the arguments.
    //
    ASSERT(sector_num <= 255);

    // DCSM data is not allowed to modify via Flash_* driverlib functions
    if (DCSMBANK_SECTOR_NUM == sector_num)
        return;

    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
    while (Flash0CtrlRegs.ERASE & 0x20000000) // wait NO BUSY
        ;
    /* ERASE register need write with 32 bit by once */
    Flash0CtrlRegs.ERASE = 0x90000000 | sector_num << 12 | FLASH_ERASE_SECTOR << 25;
    while (Flash0CtrlRegs.ERASE & 0x80000000) // wait ERASE Finish
        ;
}

/* GD25Q80E Flash One Block = 64K */
void Flash_eraseBlock(vu32 block_num)
{
    //
    // Check the arguments.
    //
    ASSERT(block_num <= 15);

    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
    while (Flash0CtrlRegs.ERASE & 0x20000000) // wait NO BUSY
        ;
    /* ERASE register need write with 32 bit by once */
    Flash0CtrlRegs.ERASE = 0x90000000 | block_num << 16 | FLASH_ERASE_BLOCK << 25;
    while (Flash0CtrlRegs.ERASE & 0x80000000) // wait ERASE Finish
        ;
}

void Flash_eraseChip(void)
{
    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
    while (Flash0CtrlRegs.ERASE & 0x20000000) // wait NO BUSY
        ;
    /* ERASE register need write with 32 bit by once */
    Flash0CtrlRegs.ERASE = 0x90000000 | FLASH_ERASE_CHIP << 25;
    while (Flash0CtrlRegs.ERASE & 0x80000000) // wait ERASE Finish
        ;
}

void Flash_eraseOTP(vu32 otp_num)
{
    //
    // Check the arguments.
    //
    ASSERT((0 == otp_num) || (1 == otp_num));

    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
    while (Flash0CtrlRegs.ERASE & 0x20000000) // wait NO BUSY
        ;
    /* ERASE register need write with 32 bit by once */
    Flash0CtrlRegs.ERASE = 0x90000000 | FLASH_ERASE_OTP << 25 | otp_num << 12;
    while (Flash0CtrlRegs.ERASE & 0x80000000) // wait ERASE Finish
        ;
}
