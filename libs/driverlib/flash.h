#ifndef FLASH_H
#define FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup flash_api FLASH
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#include "f28004x_device.h"

//*****************************************************************************
//
//! Values that can be passed to Flash_setBankPowerMode() as the bank parameter
//
//*****************************************************************************
typedef enum
{
    FLASH_ERASE_SECTOR = 0,
    FLASH_ERASE_BLOCK  = 1,
    FLASH_ERASE_CHIP   = 2,
    FLASH_ERASE_OTP    = 3
} Flash_EraseType;

//*****************************************************************************
//
// Delay instruction that allows for register configuration to complete.
//
//*****************************************************************************
#define FLASH_DELAY_CONFIG // __asm(" RPT #7 || NOP")

//*****************************************************************************
//
//! \internal
//! Checks a flash wrapper base address for the control registers.
//!
//! \param ctrlBase is the base address of the flash wrapper control registers.
//!
//! This function determines if a flash wrapper control base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool Flash_isCtrlBaseValid(uint32_t ctrlBase)
{
    return ((ctrlBase == FLASH0CTRL_BASE));
}
#endif

//*****************************************************************************
//
//! Set flash clock division number.
//!
//! \param div is the flash clock division number, 16 valid bits. 1 on reset.
//!
//! This function sets flash clock division number from SYSCLK. Relationship
//! between actual_SYSCLK_division and div is
//!
//! - actual_SYSCLK_division = 2, if div = [0, 1, 2]
//! - actual_SYSCLK_division = int(Ceiling(div/2.0)) * 2, if div = others
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_setClkDiv(u32 div)
{
    //
    // Check the arguments.
    //
    ASSERT(div <= 65535);

    DevCfgRegs.FLASHCLKDIV.bit.CLK_FLASH_DIV = div;
}

//*****************************************************************************
//
//! Enable flash QSPI mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_enableQspiMode()
{
    Flash0CtrlRegs.CONFIG.bit.QE = 1;
    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
}

//*****************************************************************************
//
//! Disable flash QSPI mode.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_disableQspiMode()
{
    Flash0CtrlRegs.CONFIG.bit.QE = 0;
    while (Flash0CtrlRegs.STATUS.bit.WIP)
        ;
}

//*****************************************************************************
//
//! Read one 32-bit word from flash.
//!
//! \param addr is flash memory address, should be 32-bit aligned.
//!
//! \return Returns the flash data.
//
//*****************************************************************************
static inline vu32 Flash_readWord(u32 addr)
{
    //
    // Check the arguments.
    //
    ASSERT((addr & 0x3) == 0);

    return HWREG(addr);
}

//*****************************************************************************
//
//! Write one 32-bit word to flash.
//!
//! \param addr is flash memory address, should be 32-bit aligned.
//! \param val is data to write to flash.
//!
//! \return None.
//
//*****************************************************************************
static inline void Flash_writeWord(u32 addr, vu32 val)
{
    //
    // Check the arguments.
    //
    ASSERT((addr & 0x3) == 0);

    //
    // DCSM data is not allowed to modify via Flash_* driverlib functions
    //
    if (addr >= DCSMBANK_BASE && addr < (DCSMBANK_BASE + DCSMBANK_SIZE))
        return;

    HWREG(addr) = val;
}

//*****************************************************************************
//
//! Initialize flash module.
//!
//! \param div is the flash clock division number, 16 valid bits.
//! \param qspi_en specifies whether to enable flash QSPI mode. Its value can be
//!
//! - 0      means disable flash QSPI mode.
//! - none-0 means enable flash QSPI mode.
//!
//! This function invokes Flash_setClkDiv() and Flash_enableQspiMode().
//!
//! \return None.
//
//*****************************************************************************
extern void Flash_initModule(u32 div, u32 qspi_en);

//*****************************************************************************
//
//! Erase the whole flash data area.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
extern void Flash_eraseChip(void);

//*****************************************************************************
//
//! Erase one 64KB block in flash data area.
//!
//! \param block_num is the block to erase. For current 1MB flash data,
//! it values range is [0,15]
//!
//! \return None.
//
//*****************************************************************************
extern void Flash_eraseBlock(vu32 block_num);

//*****************************************************************************
//
//! Erase one 4KB sector in flash data area.
//!
//! \param sector_num is the sector to erase. For current 1MB flash data,
//! it values range is [0,255]
//!
//! \return None.
//
//*****************************************************************************
extern void Flash_eraseSector(vu32 sector_num);

//*****************************************************************************
//
//! Erase flash OTP area.
//!
//! \param otp_num is the OTP area to erase. Its values can be
//! - 0 means 1st 1KB of OTP area
//! - 1 means 2nd 1KB of OTP area
//!
//! \return None.
//
//*****************************************************************************
extern void Flash_eraseOTP(vu32 otp_num);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
