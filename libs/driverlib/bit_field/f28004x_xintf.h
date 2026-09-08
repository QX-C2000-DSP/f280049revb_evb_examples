#ifndef F28004X_XINTF_H
#define F28004X_XINTF_H

#ifdef __cplusplus
extern "C" {
#endif

// XINTF timing register bit definitions
struct XTIMING_BITS_ASYNC
{                         // bits  description
    Uint32 XWRTRAIL  : 2; // 1:0   Write access trail timing
    Uint32 XWRACTIVE : 3; // 4:2   Write access active timing
    Uint32 XWRLEAD   : 2; // 6:5   Write access lead timing
    Uint32 XRDTRAIL  : 2; // 8:7   Read access trail timing
    Uint32 XRDACTIVE : 3; // 11:9  Read access active timing
    Uint32 XRDLEAD   : 2; // 13:12 Read access lead timing
    Uint32 USEREADY  : 1; // 14    Extend access using HW waitstates
    Uint32 READYMODE : 1; // 15    Ready mode
    Uint32 XSIZE     : 2; // 17:16 XINTF bus width - must be written as 11b
    Uint32 rsvd1     : 4; // 21:18 reserved
    Uint32 X2TIMING  : 1; // 22    Double lead/active/trail timing
    Uint32 rsvd3     : 9; // 31:23 reserved
};

struct XTIMING_BITS_SYNC
{                         // bits  description
    Uint32 rsvd1    : 2;  // 1:0   reserved
    Uint32 R_LTNCY  : 2;  // 3:2   Extend access using HW waitstates
    Uint32 rsvd2    : 2;  // 5:4   Ready mode
    Uint32 W_LTNCY  : 2;  // 7:6   Write access delay
    Uint32 R_ENABLE : 1;  // 8     Read enable control SADS/SRE action
    Uint32 CE_EXT   : 1;  // 9     External CS signa
    Uint32 RD_BE_EN : 1;  // 10    Byte read enable
    Uint32 rsvd3    : 5;  // 15:11  reserved
    Uint32 SIZE     : 2;  // 17:16 data size
    Uint32 rsvd4    : 13; // 30:18 reserved
    Uint32 SSEL     : 1;  // 31    choose sync or async
};

union XTIMING_REG
{
    Uint32 all;
    struct XTIMING_BITS_ASYNC bit;
    struct XTIMING_BITS_SYNC bit2;
};

// XINTF control register bit definitions
struct XINTCNF2_BITS
{                        // bits  description
    Uint32 WRBUFF  : 2;  // 1:0   Write buffer depth
    Uint32 CLKMODE : 1;  // 2     Ratio for XCLKOUT with respect to XTIMCLK
    Uint32 CLKOFF  : 1;  // 3     Disable XCLKOUT
    Uint32 rsvd1   : 2;  // 5:4   reserved
    Uint32 WLEVEL  : 2;  // 7:6   Current level of the write buffer
    Uint32 rsvd2   : 1;  // 8     reserved
    Uint32 HOLD    : 1;  // 9     Hold enable/disable
    Uint32 HOLDS   : 1;  // 10    Current state of HOLDn input
    Uint32 HOLDAS  : 1;  // 11    Current state of HOLDAn output
    Uint32 rsvd3   : 4;  // 15:12 reserved
    Uint32 XTIMCLK : 3;  // 18:16 Ratio for XTIMCLK
    Uint32 rsvd4   : 13; // 31:19 reserved
};

union XINTCNF2_REG
{
    Uint32 all;
    struct XINTCNF2_BITS bit;
};

// XINTF bank switching register bit definitions
struct XBANK_BITS
{                     // bits  description
    Uint32 BANK : 3;  // 2:0   Zone for which banking is enabled
    Uint32 BCYC : 3;  // 5:3   XTIMCLK cycles to add
    Uint32 rsvd : 10; // 15:6  reserved
};

union XBANK_REG
{
    Uint32 all;
    struct XBANK_BITS bit;
};

struct XRESET_BITS
{
    Uint32 XHARDRESET : 1;
    Uint32 rsvd1      : 31;
};

union XRESET_REG
{
    Uint32 all;
    struct XRESET_BITS bit;
};
// EMIF Async Wait Cycle Config Register
struct ASYNC_WCCR_BITS
{                            // bits  description
    Uint32 MAX_EXT_WAIT : 8; // 7:0   The EMIF will wait for (max_ext_wait + 1) * 16 clock cycles
                             // before an extended asynchronous cycle is terminated.
    Uint32 rsvd1 : 20;       // 27:8  reserved
    Uint32 WP0   : 1;        // 28    Defines the polarity of the EMxWAIT port
    Uint32 rsvd2 : 3;        // 31:29 reserved
};

union ASYNC_WCCR_REG
{
    Uint32 all;
    struct ASYNC_WCCR_BITS bit;
};

// EMIF Interrupt Raw Register
struct INT_RAW_BITS
{                     // bits  description
    Uint32 AT   : 1;  // 0    Asynchronous Timeout.
    Uint32 LT   : 1;  // 1    Line Trap.
    Uint32 WR   : 1;  // 2    Wait Rise.
    Uint32 rsvd : 29; // 31:3 reserved
};

union INT_RAW_REG
{
    Uint32 all;
    struct INT_RAW_BITS bit;
};

// EMIF Interrupt Masked Register
struct INT_MSK_BITS
{                          // bits  description
    Uint32 AT_MASKED : 1;  // 0    Masked Asynchronous Timeout.
    Uint32 LT_MASKED : 1;  // 1    Masked Line Trap.
    Uint32 WR_MASKED : 1;  // 2    Masked Wait Rise.
    Uint32 rsvd      : 29; // 31:3 reserved
};

union INT_MSK_REG
{
    Uint32 all;
    struct INT_MSK_BITS bit;
};

// EMIF Interrupt Mask Set Register
struct INT_MSK_SET_BITS
{                              // bits  description
    Uint32 AT_MASKED_SET : 1;  // 0    Mask set for at_masked bit in the Interrupt Masked Register.
    Uint32 LT_MASKED_SET : 1;  // 1    Mask set for lt_masked bit in the Interrupt Masked Register.
    Uint32 WR_MASKED_SET : 1;  // 2    Mask set for wr_masked bits in the Interrupt Masked Register.
    Uint32 rsvd          : 29; // 31:3 reserved
};

union INT_MSK_SET_REG
{
    Uint32 all;
    struct INT_MSK_SET_BITS bit;
};

// EMIF Interrupt Mask Clear Register
struct INT_MSK_CLR_BITS
{                             // bits  description
    Uint32 AT_MASKED_CLR : 1; // 0    Mask clear for at_masked bit in the Interrupt Masked Register.
    Uint32 LT_MASKED_CLR : 1; // 1    Mask clear for lt_masked bit in the Interrupt Masked Register.
    Uint32
        WR_MASKED_CLR : 1;  // 2    Mask clear for wr_masked bits in the Interrupt Masked Register.
    Uint32 rsvd       : 29; // 31:3 reserved
};

union INT_MSK_CLR_REG
{
    Uint32 all;
    struct INT_MSK_CLR_BITS bit;
};

// XINTF Register File
struct XINTF_REGS
{
    union XTIMING_REG XTIMING0;
    union XTIMING_REG XTIMING6;
    union XTIMING_REG XTIMING7;
    union XINTCNF2_REG XINTCNF2;
    union XBANK_REG XBANK;
    Uint32 XREVISION;
    union XRESET_REG XRESET;
    union ASYNC_WCCR_REG ASYNC_WCCR;
    union INT_RAW_REG INT_RAW;
    union INT_MSK_REG INT_MSK;
    union INT_MSK_SET_REG INT_MSK_SET;
    union INT_MSK_CLR_REG INT_MSK_CLR;
};

// XINTF External References & Function Declarations
extern volatile struct XINTF_REGS XintfaRegs;
// extern volatile struct XINTF_REGS XintfbRegs;
// extern volatile struct XINTF_REGS XintfcRegs;

#ifdef __cplusplus
}
#endif

#endif
