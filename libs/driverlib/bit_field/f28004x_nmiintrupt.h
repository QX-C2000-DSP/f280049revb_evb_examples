#ifndef F28004X_NMIINTRUPT_H
#define F28004X_NMIINTRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// NMIINTRUPT Individual Register Bit Definitions:

struct NMICFG_BITS
{                      // bits description
    Uint32 NMIE  : 1;  // 0 Global NMI Enable
    Uint32 rsvd1 : 15; // 15:1 Reserved
};

union NMICFG_REG
{
    Uint32 all;
    struct NMICFG_BITS bit;
};

struct NMIFLG_BITS
{                          // bits description
    Uint32 NMIINT     : 1; // 0 NMI Interrupt Flag
    Uint32 CLOCKFAIL  : 1; // 1 Clock Fail Interrupt Flag
    Uint32 rsvd0      : 5; // 6:2 Reserved
    Uint32 RAMUNCERR  : 1; // 7 Data RAM Uncorrectable ERROR
    Uint32 FLUNCERR   : 1; // 8 Flash Uncorrectable ERROR
    Uint32 IRAMUNCERR : 1; // 9 Inst RAM memory ERROR
    Uint32 rsvd1      : 3; // 12:10 Reserved
    Uint32 SWERR      : 1; // 13 SW Error Force NMI Flag
};

union NMIFLG_REG
{
    Uint32 all;
    struct NMIFLG_BITS bit;
};

struct NMIFLGCLR_BITS
{                          // bits description
    Uint32 NMIINT     : 1; // 0 NMI Interrupt Flag
    Uint32 CLOCKFAIL  : 1; // 1 Clock Fail Interrupt Flag
    Uint32 rsvd0      : 5; // 6:2 Reserved
    Uint32 RAMUNCERR  : 1; // 7 Data RAM Uncorrectable ERROR
    Uint32 FLUNCERR   : 1; // 8 Flash Uncorrectable ERROR
    Uint32 IRAMUNCERR : 1; // 9 Inst RAM memory ERROR
    Uint32 rsvd1      : 3; // 12:10 Reserved
    Uint32 SWERR      : 1; // 13 SW Error Force NMI Flag
};

union NMIFLGCLR_REG
{
    Uint32 all;
    struct NMIFLGCLR_BITS bit;
};

struct NMIFLGFRC_BITS
{                          // bits description
    Uint32 rsvd0      : 1; // 0 NMI Interrupt Flag
    Uint32 CLOCKFAIL  : 1; // 1 Clock Fail Interrupt Flag
    Uint32 rsvd1      : 5; // 6:2 Reserved
    Uint32 RAMUNCERR  : 1; // 7 Data RAM Uncorrectable ERROR
    Uint32 FLUNCERR   : 1; // 8 Flash Uncorrectable ERROR
    Uint32 IRAMUNCERR : 1; // 9 Inst RAM memory ERROR
    Uint32 rsvd2      : 3; // 12:10 Reserved
    Uint32 SWERR      : 1; // 13 SW Error Force NMI Flag
};

union NMIFLGFRC_REG
{
    Uint32 all;
    struct NMIFLGFRC_BITS bit;
};

struct NMISHDFLG_BITS
{                          // bits description
    Uint32 rsvd0      : 1; // 0 NMI Interrupt Flag
    Uint32 CLOCKFAIL  : 1; // 1 Clock Fail Interrupt Flag
    Uint32 rsvd1      : 5; // 6:2 Reserved
    Uint32 RAMUNCERR  : 1; // 7 Data RAM Uncorrectable ERROR
    Uint32 FLUNCERR   : 1; // 8 Flash Uncorrectable ERROR
    Uint32 IRAMUNCERR : 1; // 9 Inst RAM memory ERROR
    Uint32 rsvd2      : 3; // 12:10 Reserved
    Uint32 SWERR      : 1; // 13 SW Error Force NMI Flag
};

union NMISHDFLG_REG
{
    Uint32 all;
    struct NMISHDFLG_BITS bit;
};

struct NMI_INTRUPT_REGS
{
    union NMICFG_REG NMICFG;       // NMI Configuration Register
    union NMIFLG_REG NMIFLG;       // NMI Flag Register (SYSRsn Clear)
    union NMIFLGCLR_REG NMIFLGCLR; // NMI Flag Clear Register
    union NMIFLGFRC_REG NMIFLGFRC; // NMI Flag Force Register
    Uint32 NMIWDCNT;               // NMI Watchdog Counter Register
    Uint32 NMIWDPRD;               // NMI Watchdog Period Register
    union NMISHDFLG_REG NMISHDFLG; // NMI Shadow Flag Register
};

//---------------------------------------------------------------------------
// NMIINTRUPT External References & Function Declarations:
//
extern volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
