#ifndef F28004X_LIN_H
#define F28004X_LIN_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// LIN Individual Register Bit Definitions:

struct LIN_LSEL_BITS
{
    Uint32 INDEX : 5;
    Uint32 DLY   : 2;
    Uint32 AINC  : 1;
    Uint32 rsvd1 : 8;
    Uint32 rsvd2 : 8;
    Uint32 rsvd3 : 8;
};

union LIN_LSEL_REG
{
    Uint32 all;
    struct LIN_LSEL_BITS bit;
};

struct LIN_LID_BITS
{
    Uint32 LID  : 6;
    Uint32 rsvd : 2;
};

union LIN_LID_REG
{
    Uint32 all;
    struct LIN_LID_BITS bit;
};

struct LIN_LER_BITS
{
    Uint32 FER    : 1;
    Uint32 BITER  : 1;
    Uint32 PER    : 1;
    Uint32 CHKSER : 1;
    Uint32 TOVER  : 1;
    Uint32 SYNCER : 1;
    Uint32 OVER   : 1;
    Uint32 WAKEER : 1;
};

union LIN_LER_REG
{
    Uint32 all;
    struct LIN_LER_BITS bit;
};

struct LIN_LIE_BITS
{
    Uint32 LIDE   : 1;
    Uint32 RDYE   : 1;
    Uint32 ERRE   : 1;
    Uint32 ABORTE : 1;
    Uint32 SLEEPE : 1;
    Uint32 WAKEE  : 1;
    Uint32 rsvd   : 2;
};

union LIN_LIE_REG
{
    Uint32 all;
    struct LIN_LIE_BITS bit;
};

struct LIN_LSR_BITS
{
    Uint32 LID      : 1;
    Uint32 RDY      : 1;
    Uint32 ERR      : 1;
    Uint32 ABORT    : 1;
    Uint32 LOG_SIZE : 4;
};

struct LIN_LCR_BITS
{
    Uint32 CMD  : 2;  /**< Execute command */
    Uint32 SIZE : 4;  /**< Length of message, this option is valid only LIN2.1 mode is selected
                       (lin13  parameter is 0) */
    Uint32 LIN13 : 1; /**< Checksum selector: 1 - classic checksum compatible with LIN 1.3; 0 -
                      Enhanced checksum compatible with LIN 2.1 specification */
    Uint32 MODE : 1;  /**< Master/Slave mode select */
};

union LIN_LSR_LCR_REG
{
    Uint32 all;
    struct LIN_LSR_BITS lsr;
    struct LIN_LCR_BITS lcr;
};

struct LIN_DLL_BITS
{
    Uint32 DLL0 : 1;
    Uint32 DLL1 : 1;
    Uint32 DLL2 : 1;
    Uint32 DLL3 : 1;
    Uint32 DLL4 : 1;
    Uint32 DLL5 : 1;
    Uint32 DLL6 : 1;
    Uint32 DLL7 : 1;
};
union LIN_DLL_REG
{
    Uint32 all;
    struct LIN_DLL_BITS bit;
};

struct LIN_DLH_BITS // 0x07
{
    Uint32 DLH0 : 1;
    Uint32 DLH1 : 1;
    Uint32 DLH2 : 1;
    Uint32 DLH3 : 1;
    Uint32 DLH4 : 1;
    Uint32 DLH5 : 1;
    Uint32 DLH6 : 1;
    Uint32 SYNC : 1;
};

union LIN_DLH_REG
{
    Uint32 all;
    struct LIN_DLH_BITS bit;
};

struct LIN_HDRL_BITS
{
    Uint32 HDR0 : 1;
    Uint32 HDR1 : 1;
    Uint32 HDR2 : 1;
    Uint32 HDR3 : 1;
    Uint32 HDR4 : 1;
    Uint32 HDR5 : 1;
    Uint32 HDR6 : 1;
    Uint32 HDR7 : 1;
};

union LIN_HDRL_REG
{
    Uint32 all;
    struct LIN_HDRL_BITS bit;
};

struct LIN_HDRH_BITS
{
    Uint32 HDR8  : 1;
    Uint32 HDR9  : 1;
    Uint32 HDR10 : 1;
    Uint32 HDR11 : 1;
    Uint32 HDR12 : 1;
    Uint32 HDR13 : 1;
    Uint32 HDR14 : 1;
    Uint32 HDR15 : 1;
};

union LIN_HDRH_REG
{
    Uint32 all;
    struct LIN_HDRH_BITS bit;
};

struct LIN_HDP_BITS
{
    Uint32 HDP0  : 1;
    Uint32 HDP1  : 1;
    Uint32 HDP2  : 1;
    Uint32 HDP3  : 1;
    Uint32 HDP4  : 1;
    Uint32 HDP5  : 1;
    Uint32 rsvd1 : 1;
    Uint32 rsvd2 : 1;
};

union LIN_HDP_REG
{
    Uint32 all;
    struct LIN_HDP_BITS bit;
};

struct LIN_LBS_BITS
{
    Uint32 SLEEPM : 1;
    Uint32 WAKEUP : 1;
    Uint32 SLEEP  : 1;
    Uint32 rsvd1  : 1;
    Uint32 rsvd2  : 1;
    Uint32 rsvd3  : 1;
    Uint32 rsvd4  : 1;
    Uint32 rsvd5  : 1;
};

union LIN_LBS_REG
{
    Uint32 all;
    struct LIN_LBS_BITS bit;
};

struct LIN_IDTH_BITS
{
    Uint32 IDT    : 5;
    Uint32 rsvd1  : 1;
    Uint32 rsvd2  : 1;
    Uint32 IDTRUN : 1;
};

union LIN_IDTH_REG
{
    Uint32 all;
    struct LIN_IDTH_BITS bit;
};

struct LIN_REGS
{
    Uint32 LBUF;                   // 0x00
    union LIN_LSEL_REG LSEL;       // 0x04
    union LIN_LID_REG LID;         // 0x08
    union LIN_LER_REG LER;         // 0x0c
    union LIN_LIE_REG LIE;         // 0x10
    union LIN_LSR_LCR_REG LSR_LCR; // 0x14
    union LIN_DLL_REG DLL;         // 0x18
    union LIN_DLH_REG DLH;         // 0x1c
    union LIN_HDRL_REG HDRL;       // 0x20
    union LIN_HDRH_REG HDRH;       // 0x24
    union LIN_HDP_REG HDP;         // 0x28
    union LIN_LBS_REG LBS;         // 0x2c
    Uint32 WURT;                   // 0x30
    Uint32 IDTL;                   // 0x34
    union LIN_IDTH_REG IDTH;       // 0x38
};

//---------------------------------------------------------------------------
// LIN External References & Function Declarations:
//
extern volatile struct LIN_REGS LinaRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
