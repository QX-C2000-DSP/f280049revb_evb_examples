#ifndef F28004X_CMPSS_H
#define F28004X_CMPSS_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// CMPSS Individual Register Bit Definitions:

struct COMPCTL_BITS
{                            // bits description
    Uint32 COMPHSOURCE  : 1; // 0 High Comparator Source Select
    Uint32 COMPHINV     : 1; // 1 High Comparator Invert Select
    Uint32 CTRIPHSEL    : 2; // 3:2 High Comparator Trip Select
    Uint32 CTRIPOUTHSEL : 2; // 5:4 High Comparator Trip Output Select
    Uint32 ASYNCHEN     : 1; // 6 High Comparator Asynchronous Path Enable
    Uint32 rsvd1        : 1; // 7 Reserved
    Uint32 COMPLSOURCE  : 1; // 8 Low Comparator Source Select
    Uint32 COMPLINV     : 1; // 9 Low Comparator Invert Select
    Uint32 CTRIPLSEL    : 2; // 11:10 Low Comparator Trip Select
    Uint32 CTRIPOUTLSEL : 2; // 13:12 Low Comparator Trip Output Select
    Uint32 ASYNCLEN     : 1; // 14 Low Comparator Asynchronous Path Enable
    Uint32 COMPDACE     : 1; // 15 Comparator/DAC Enable
};

union COMPCTL_REG
{
    Uint32 all;
    struct COMPCTL_BITS bit;
};

struct COMPHYSCTL_BITS
{ // bits description
    Uint32 COMPHYS : 3;
};

union COMPHYSCTL_REG
{
    Uint32 all;
    struct COMPHYSCTL_BITS bit;
};

struct COMPSTS_BITS
{                          // bits description
    Uint32 COMPHSTS   : 1; // 0 High Comparator Status
    Uint32 COMPHLATCH : 1; // 1 High Comparator Latched Status
    Uint32 rsvd1      : 6; // 7:2 Reserved
    Uint32 COMPLSTS   : 1; // 8 Low Comparator Status
    Uint32 COMPLLATCH : 1; // 9 Low Comparator Latched Status
    Uint32 rsvd2      : 6; // 15:10 Reserved
};

union COMPSTS_REG
{
    Uint32 all;
    struct COMPSTS_BITS bit;
};

struct COMPSTSCLR_BITS
{                          // bits description
    Uint32 rsvd1      : 1; // 0 Reserved
    Uint32 HLATCHCLR  : 1; // 1 High Comparator Latched Status Clear
    Uint32 HSYNCCLREN : 1; // 2 High Comparator EPWMSYNCPER Clear Enable
    Uint32 rsvd2      : 6; // 8:3 Reserved
    Uint32 LLATCHCLR  : 1; // 9 Low Comparator Latched Status Clear
    Uint32 LSYNCCLREN : 1; // 10 Low Comparator EPWMSYNCPER Clear Enable
    Uint32 rsvd3      : 5; // 15:11 Reserved
};

union COMPSTSCLR_REG
{
    Uint32 all;
    struct COMPSTSCLR_BITS bit;
};

struct COMPDACCTL_BITS
{                           // bits description
    Uint32 DACSOURCE   : 1; // 0 DAC Source Control
    Uint32 RAMPSOURCE  : 4; // 4:1 Ramp Generator Source Control
    Uint32 SELREF      : 1; // 5 DAC Reference Select
    Uint32 RAMPLOADSEL : 1; // 6 Ramp Load Select
    Uint32 SWLOADSEL   : 1; // 7 Software Load Select
    Uint32 BLANKSOURCE : 4; // 11:8 EPWMBLANK Source Select
    Uint32 BLANKEN     : 1; // 12 EPWMBLANK Enable
    Uint32 rsvd1       : 1; // 13 Reserved
    Uint32 FREESOFT    : 2; // 15:14 Free/Soft Emulation Bits
};

union COMPDACCTL_REG
{
    Uint32 all;
    struct COMPDACCTL_BITS bit;
};

struct DACHVALS_BITS
{                       // bits description
    Uint32 DACVAL : 12; // 11:0 DAC Value Control
    Uint32 rsvd1  : 4;  // 15:12 Reserved
};

union DACHVALS_REG
{
    Uint32 all;
    struct DACHVALS_BITS bit;
};

struct DACHVALA_BITS
{                       // bits description
    Uint32 DACVAL : 12; // 11:0 DAC Value Control
    Uint32 rsvd1  : 4;  // 15:12 Reserved
};

union DACHVALA_REG
{
    Uint32 all;
    struct DACHVALA_BITS bit;
};

struct DACLVALS_BITS
{                       // bits description
    Uint32 DACVAL : 12; // 11:0 DAC Value Control
    Uint32 rsvd1  : 4;  // 15:12 Reserved
};

union DACLVALS_REG
{
    Uint32 all;
    struct DACLVALS_BITS bit;
};

struct DACLVALA_BITS
{                       // bits description
    Uint32 DACVAL : 12; // 11:0 DAC Value Control
    Uint32 rsvd1  : 4;  // 15:12 Reserved
};

union DACLVALA_REG
{
    Uint32 all;
    struct DACLVALA_BITS bit;
};

struct RAMPDLYA_BITS
{                      // bits description
    Uint32 DELAY : 13; // 12:0 Ramp Delay Value
    Uint32 rsvd1 : 3;  // 15:13 Reserved
};

union RAMPDLYA_REG
{
    Uint32 all;
    struct RAMPDLYA_BITS bit;
};

struct RAMPDLYS_BITS
{                      // bits description
    Uint32 DELAY : 13; // 12:0 Ramp Delay Value
    Uint32 rsvd1 : 3;  // 15:13 Reserved
};

union RAMPDLYS_REG
{
    Uint32 all;
    struct RAMPDLYS_BITS bit;
};

struct CTRIPLFILCTL_BITS
{                       // bits description
    Uint32 rsvd1   : 4; // 3:0 Reserved
    Uint32 SAMPWIN : 5; // 8:4 Sample Window
    Uint32 THRESH  : 5; // 13:9 Majority Voting Threshold
    Uint32 rsvd2   : 1; // 14 Reserved
    Uint32 FILINIT : 1; // 15 Filter Initialization Bit
};

union CTRIPLFILCTL_REG
{
    Uint32 all;
    struct CTRIPLFILCTL_BITS bit;
};

struct CTRIPLFILCLKCTL_BITS
{                            // bits description
    Uint32 CLKPRESCALE : 10; // 9:0 Sample Clock Prescale
    Uint32 rsvd1       : 6;  // 15:10 Reserved
};

union CTRIPLFILCLKCTL_REG
{
    Uint32 all;
    struct CTRIPLFILCLKCTL_BITS bit;
};

struct CTRIPHFILCTL_BITS
{                       // bits description
    Uint32 rsvd1   : 4; // 3:0 Reserved
    Uint32 SAMPWIN : 5; // 8:4 Sample Window
    Uint32 THRESH  : 5; // 13:9 Majority Voting Threshold
    Uint32 rsvd2   : 1; // 14 Reserved
    Uint32 FILINIT : 1; // 15 Filter Initialization Bit
};

union CTRIPHFILCTL_REG
{
    Uint32 all;
    struct CTRIPHFILCTL_BITS bit;
};

struct CTRIPHFILCLKCTL_BITS
{                            // bits description
    Uint32 CLKPRESCALE : 10; // 9:0 Sample Clock Prescale
    Uint32 rsvd1       : 6;  // 15:10 Reserved
};

union CTRIPHFILCLKCTL_REG
{
    Uint32 all;
    struct CTRIPHFILCLKCTL_BITS bit;
};

struct COMPLOCK_BITS
{                           // bits description
    Uint32 COMPCTL    : 1;  // 0 COMPCTL Lock
    Uint32 COMPHYSCTL : 1;  // 1 COMPHYSCTL Lock
    Uint32 DACCTL     : 1;  // 2 DACCTL Lock
    Uint32 CTRIP      : 1;  // 3 CTRIP Lock
    Uint32 rsvd1      : 1;  // 4 Reserved
    Uint32 rsvd2      : 11; // 15:5 Reserved
};

union COMPLOCK_REG
{
    Uint32 all;
    struct COMPLOCK_BITS bit;
};

struct COMPDACHCTL_BITS
{                             // bits description
    Uint32 COMPH_HYS     : 3; // 2:0
    Uint32 DACH_MD       : 2; // 4:3
    Uint32 DACH_PRESCALE : 8; // 12:5
};

union COMPDACHCTL_REG
{
    Uint32 all;
    struct COMPDACHCTL_BITS bit;
};

struct COMPDACLCTL_BITS
{                             // bits description
    Uint32 COMPH_HYS     : 3; // 2:0
    Uint32 DACH_MD       : 2; // 4:3
    Uint32 DACH_PRESCALE : 8; // 12:5
};

union COMPDACLCTL_REG
{
    Uint32 all;
    struct COMPDACLCTL_BITS bit;
};

struct CMPSS_REGS
{
    union COMPCTL_REG COMPCTL;                 // CMPSS Comparator Control Register
    union COMPHYSCTL_REG COMPHYSCTL;           // CMPSS Comparator Hysteresis Control Register
    union COMPSTS_REG COMPSTS;                 // CMPSS Comparator Status Register
    union COMPSTSCLR_REG COMPSTSCLR;           // CMPSS Comparator Status Clear Register
    union COMPDACCTL_REG COMPDACCTL;           // CMPSS DAC Control Register
    union DACHVALS_REG DACHVALS;               // CMPSS High DAC Value Shadow Register
    union DACHVALA_REG DACHVALA;               // CMPSS High DAC Value Active Register
    Uint32 RAMPMAXREFA;                        // CMPSS Ramp Max Reference Active Register
    Uint32 RAMPMAXREFS;                        // CMPSS Ramp Max Reference Shadow Register
    Uint32 RAMPDECVALA;                        // CMPSS Ramp Decrement Value Active Register
    Uint32 RAMPDECVALS;                        // CMPSS Ramp Decrement Value Shadow Register
    Uint32 RAMPSTS;                            // CMPSS Ramp Status Register
    union DACLVALS_REG DACLVALS;               // CMPSS Low DAC Value Shadow Register
    union DACLVALA_REG DACLVALA;               // CMPSS Low DAC Value Active Register
    union RAMPDLYA_REG RAMPDLYA;               // CMPSS Ramp Delay Active Register
    union RAMPDLYS_REG RAMPDLYS;               // CMPSS Ramp Delay Shadow Register
    union CTRIPLFILCTL_REG CTRIPLFILCTL;       // CTRIPL Filter Control Register
    union CTRIPLFILCLKCTL_REG CTRIPLFILCLKCTL; // CTRIPL Filter Clock Control Register
    union CTRIPHFILCTL_REG CTRIPHFILCTL;       // CTRIPH Filter Control Register
    union CTRIPHFILCLKCTL_REG CTRIPHFILCLKCTL; // CTRIPH Filter Clock Control Register
    union COMPLOCK_REG COMPLOCK;               // CMPSS Lock Register
    union COMPDACHCTL_REG COMPDACHCTL;
    union COMPDACLCTL_REG COMPDACLCTL;
};

//---------------------------------------------------------------------------
// CMPSS External References & Function Declarations:
//
extern volatile struct CMPSS_REGS Cmpss1Regs;
extern volatile struct CMPSS_REGS Cmpss2Regs;
extern volatile struct CMPSS_REGS Cmpss3Regs;
extern volatile struct CMPSS_REGS Cmpss4Regs;
extern volatile struct CMPSS_REGS Cmpss5Regs;
extern volatile struct CMPSS_REGS Cmpss6Regs;
extern volatile struct CMPSS_REGS Cmpss7Regs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
