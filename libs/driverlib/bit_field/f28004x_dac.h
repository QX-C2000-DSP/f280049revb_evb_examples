#ifndef F28004X_DAC_H
#define F28004X_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// DAC Individual Register Bit Definitions:

struct DACREV_BITS
{                     // bits description
    Uint32 REV   : 8; // 7:0 DAC Revision Register
    Uint32 rsvd1 : 8; // 15:8 Reserved
};

union DACREV_REG
{
    Uint32 all;
    struct DACREV_BITS bit;
};

struct DACCTL_BITS
{                         // bits description
    Uint32 DACREFSEL : 2; // 1:0 DAC Reference Select
    Uint32 VREF_MD   : 1; // 2 VREF_MD Select
    Uint32 LOADMODE  : 1; // 3 DACVALA Load Mode
    Uint32 SYNCSEL   : 4; // 7:4 DAC EPWMSYNCPER Select
    Uint32 MODE      : 2; // 9:8 DAC Mode Select
    Uint32 rsvd1     : 6; // 15:10 Reserved
    Uint32 PRESCALE  : 8; // 23:16 DAC frequency division
    Uint32 rsvd4     : 8; // 31:24 Reserved
};

union DACCTL_REG
{
    Uint32 all;
    struct DACCTL_BITS bit;
};

struct DACVALA_BITS
{                        // bits description
    Uint32 DACVALA : 12; // 11:0 DAC Active Output Code
    Uint32 rsvd1   : 4;  // 15:12 Reserved
};

union DACVALA_REG
{
    Uint32 all;
    struct DACVALA_BITS bit;
};

struct DACVALS_BITS
{                        // bits description
    Uint32 DACVALS : 12; // 11:0 DAC Shadow Output Code
    Uint32 rsvd1   : 4;  // 15:12 Reserved
};

union DACVALS_REG
{
    Uint32 all;
    struct DACVALS_BITS bit;
};

struct DACOUTEN_BITS
{                         // bits description
    Uint32 DACOUTEN : 1;  // 0 DAC Output Code
    Uint32 rsvd1    : 15; // 15:1 Reserved
};

union DACOUTEN_REG
{
    Uint32 all;
    struct DACOUTEN_BITS bit;
};

struct DACLOCK_BITS
{                        // bits description
    Uint32 DACCTL   : 1; // 0 DAC Control Register Lock
    Uint32 DACVAL   : 1; // 1 DAC Value Register Lock
    Uint32 DACOUTEN : 1; // 2 DAC Output Enable Register Lock
    Uint32 rsvd1    : 9; // 11:3 Reserved
    Uint32 KEY      : 4; // 15:12 DAC Register Lock Key
};

union DACLOCK_REG
{
    Uint32 all;
    struct DACLOCK_BITS bit;
};

struct DACTRIM_BITS
{                           // bits description
    Uint32 OFFSET_TRIM : 8; // 7:0 DAC Offset Trim
    Uint32 rsvd1       : 4; // 11:8 Reserved
    Uint32 rsvd2       : 4; // 15:12 Reserved
};

union DACTRIM_REG
{
    Uint32 all;
    struct DACTRIM_BITS bit;
};

struct DAC_REGS
{
    union DACREV_REG DACREV;     // DAC Revision Register
    union DACCTL_REG DACCTL;     // DAC Control Register
    union DACVALA_REG DACVALA;   // DAC Value Register - Active
    union DACVALS_REG DACVALS;   // DAC Value Register - Shadow
    union DACOUTEN_REG DACOUTEN; // DAC Output Enable Register
    union DACLOCK_REG DACLOCK;   // DAC Lock Register
    union DACTRIM_REG DACTRIM;   // DAC Trim Register
};

//---------------------------------------------------------------------------
// DAC External References & Function Declarations:
//
extern volatile struct DAC_REGS DacaRegs;
extern volatile struct DAC_REGS DacbRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
