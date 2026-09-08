#ifndef F28004X_FLASH_H
#define F28004X_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// FLASH Individual Register Bit Definitions:

struct CONFIG_BITS
{                    // bits description
    Uint32 SRP1 : 1; // 0 Status Register Protection
    Uint32 QE   : 1; // 1 QSPI Enable
    Uint32 LB0  : 1; // 2 Security Register Lock
    Uint32 LB1  : 1; // 3 Security Register Lock
    Uint32 DC   : 1; // 4 Dummy Configuration
    Uint32 rsvd : 1; // 5 reserved
    Uint32 CMP  : 1; // 6 Complement Protect
    Uint32 SUS  : 1; // 7 Suspend
};

union CONFIG_REG
{
    Uint32 all;
    struct CONFIG_BITS bit;
};

struct STATUS_BITS
{                    // bits description
    Uint32 WIP  : 1; // 0 Erase/Write In Progress
    Uint32 WEL  : 1; // 1 Write Enable Latch
    Uint32 BP0  : 1; // 2 Block 0 Protect
    Uint32 BP1  : 1; // 3 Block 1 Protect
    Uint32 BP2  : 1; // 4 Block 2 Protect
    Uint32 BP3  : 1; // 5 Block 3 Protect
    Uint32 BP4  : 1; // 6 Block 4 Protect
    Uint32 SRP0 : 1; // 7 Status Register Protection
};

union STATUS_REG
{
    Uint32 all;
    struct STATUS_BITS bit;
};

struct FLASH_CTRL_REGS
{
    Uint32 ERASE;            // Flash Erase Register
    union CONFIG_REG CONFIG; // Flash Config Register
    union STATUS_REG STATUS; // Flash Status Register
};

//---------------------------------------------------------------------------
// FLASH External References & Function Declarations:
//
extern volatile struct FLASH_CTRL_REGS Flash0CtrlRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
