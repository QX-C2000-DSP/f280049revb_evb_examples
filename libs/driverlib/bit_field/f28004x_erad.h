#ifndef F28004X_ERAD_H
#define F28004X_ERAD_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// ERAD Individual Register Bit Definitions:

struct GLBL_EVENT_STAT_BITS
{                     // bits description
    Uint32 HWBP1 : 1; // 0 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 HWBP2 : 1; // 1 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 HWBP3 : 1; // 2 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 HWBP4 : 1; // 3 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 HWBP5 : 1; // 4 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 HWBP6 : 1; // 5 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 HWBP7 : 1; // 6 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 HWBP8 : 1; // 7 Enhanced Bus Comparator (EBC) Module Event Status
    Uint32 CTM1  : 1; // 8 Counter Module Event Status
    Uint32 CTM2  : 1; // 9 Counter Module Event Status
    Uint32 CTM3  : 1; // 10 Counter Module Event Status
    Uint32 CTM4  : 1; // 11 Counter Module Event Status
    Uint32 rsvd1 : 4; // 15:12 Reserved
};

union GLBL_EVENT_STAT_REG
{
    Uint32 all;
    struct GLBL_EVENT_STAT_BITS bit;
};

struct GLBL_HALT_STAT_BITS
{                     // bits description
    Uint32 HWBP1 : 1; // 0 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 HWBP2 : 1; // 1 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 HWBP3 : 1; // 2 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 HWBP4 : 1; // 3 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 HWBP5 : 1; // 4 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 HWBP6 : 1; // 5 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 HWBP7 : 1; // 6 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 HWBP8 : 1; // 7 Enhanced Bus Comparator (EBC) Module Halt Status
    Uint32 CTM1  : 1; // 8 Counter Module Halt Status
    Uint32 CTM2  : 1; // 9 Counter Module Halt Status
    Uint32 CTM3  : 1; // 10 Counter Module Halt Status
    Uint32 CTM4  : 1; // 11 Counter Module Halt Status
    Uint32 rsvd1 : 4; // 15:12 Reserved
};

union GLBL_HALT_STAT_REG
{
    Uint32 all;
    struct GLBL_HALT_STAT_BITS bit;
};

struct GLBL_ENABLE_BITS
{                     // bits description
    Uint32 HWBP1 : 1; // 0 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 HWBP2 : 1; // 1 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 HWBP3 : 1; // 2 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 HWBP4 : 1; // 3 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 HWBP5 : 1; // 4 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 HWBP6 : 1; // 5 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 HWBP7 : 1; // 6 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 HWBP8 : 1; // 7 Enhanced Bus Comparator (EBC) Module Global Enable
    Uint32 CTM1  : 1; // 8 Counter Module Global Enable
    Uint32 CTM2  : 1; // 9 Counter Module Global Enable
    Uint32 CTM3  : 1; // 10 Counter Module Global Enable
    Uint32 CTM4  : 1; // 11 Counter Module Global Enable
    Uint32 rsvd1 : 4; // 15:12 Reserved
};

union GLBL_ENABLE_REG
{
    Uint32 all;
    struct GLBL_ENABLE_BITS bit;
};

struct GLBL_CTM_RESET_BITS
{                      // bits description
    Uint32 CTM1  : 1;  // 0 Global Reset for the counters
    Uint32 CTM2  : 1;  // 1 Global Reset for the counters
    Uint32 CTM3  : 1;  // 2 Global Reset for the counters
    Uint32 CTM4  : 1;  // 3 Global Reset for the counters
    Uint32 rsvd1 : 12; // 15:4 Reserved
};

union GLBL_CTM_RESET_REG
{
    Uint32 all;
    struct GLBL_CTM_RESET_BITS bit;
};

struct GLBL_OWNER_BITS
{                      // bits description
    Uint32 OWNER : 2;  // 1:0 Global Ownership Bits
    Uint32 rsvd1 : 14; // 15:2 Reserved
};

union GLBL_OWNER_REG
{
    Uint32 all;
    struct GLBL_OWNER_BITS bit;
};

struct ERAD_GLOBAL_REGS
{
    union GLBL_EVENT_STAT_REG GLBL_EVENT_STAT; // Global Event Status Register, offset: 0x00
    union GLBL_HALT_STAT_REG GLBL_HALT_STAT;   // Global Halt Status Register, offset: 0x04
    union GLBL_ENABLE_REG GLBL_ENABLE;         // Global Enable Register, offset: 0x08
    union GLBL_CTM_RESET_REG GLBL_CTM_RESET;   // Global Counter Reset, offset: 0xC
    union GLBL_OWNER_REG GLBL_OWNER;           // Global Ownership, offset: 0x10
};

struct HWBP_CLEAR_BITS
{                          // bits description
    Uint32 EVENT_CLR : 1;  // 0 Event Clear register
    Uint32 rsvd1     : 15; // 15:1 Reserved
};

union HWBP_CLEAR_REG
{
    Uint32 all;
    struct HWBP_CLEAR_BITS bit;
};

struct HWBP_CNTL_BITS
{                         // bits description
    Uint32 rsvd1     : 2; // 1:0 Reserved
    Uint32 BUS_SEL   : 3; // 4:2 Bus select bits
    Uint32 STOP      : 1; // 5 Stop bit (Halt/No Halt of CPU)
    Uint32 RTOSINT   : 1; // 6 RTOSINT bit
    Uint32 COMP_MODE : 3; // 9:7 Compare mode
    Uint32 rsvd2     : 1; // 10 Reserved
    Uint32 rsvd3     : 1; // 11 Reserved
    Uint32 rsvd4     : 4; // 15:12 Reserved
};

union HWBP_CNTL_REG
{
    Uint32 all;
    struct HWBP_CNTL_BITS bit;
};

struct HWBP_STATUS_BITS
{                           // bits description
    Uint32 EVENT_FIRED : 1; // 0 HWBP (EBC) Event Fired bits
    Uint32 rsvd1       : 7; // 7:1 Reserved
    Uint32 MODULE_ID   : 6; // 13:8 Identification bits
    Uint32 STATUS      : 2; // 15:14 Status bits
};

union HWBP_STATUS_REG
{
    Uint32 all;
    struct HWBP_STATUS_BITS bit;
};

struct ERAD_HWBP_REGS
{
    Uint32 HWBP_MASK;                  // HWBP (EBC) Mask Register, offset: 0x00
    Uint32 HWBP_REF;                   // HWBP (EBC) Reference Register, offset: 0x04
    union HWBP_CLEAR_REG HWBP_CLEAR;   // HWBP (EBC) Clear Register, offset: 0x08
    union HWBP_CNTL_REG HWBP_CNTL;     // HWBP (EBC) Control Register, offset: 0x0C
    union HWBP_STATUS_REG HWBP_STATUS; // HWBP (EBC) Status Register, offset: 0x10
};

struct CTM_CNTL_BITS
{                               // bits description
    Uint32 rsvd1           : 2; // 1:0 Reserved
    Uint32 START_STOP_MODE : 1; // 2 Start_stop mode bit
    Uint32 EVENT_MODE      : 1; // 3 Event mode bit
    Uint32 RST_ON_MATCH    : 1; // 4 Reset_on_match bit
    Uint32 rsvd2           : 1; // 5 Reserved
    Uint32 STOP            : 1; // 6 Stop bit (Halt/No Halt of CPU)
    Uint32 RTOSINT         : 1; // 7 RTOSINT bit
    Uint32 rsvd3           : 1; // 8 Reserved
    Uint32 rsvd4           : 1; // 9 Reserved
    Uint32 RST_EN          : 1; // 10 Enable Reset
    Uint32 RST_INP_SEL     : 5; // 15:11 Reset Input select
};

union CTM_CNTL_REG
{
    Uint32 all;
    struct CTM_CNTL_BITS bit;
};

struct CTM_STATUS_BITS
{                            // bits description
    Uint32 EVENT_FIRED : 1;  // 0 Counter Event Fired bits
    Uint32 OVERFLOW    : 1;  // 1 Counter Overflowed
    Uint32 MODULE_ID   : 10; // 11:2 Identification bits
    Uint32 STATUS      : 4;  // 15:12 Status bits
};

union CTM_STATUS_REG
{
    Uint32 all;
    struct CTM_STATUS_BITS bit;
};

struct CTM_INPUT_SEL_BITS
{                              // bits description
    Uint32 CTM_INP_SEL_EN : 1; // 0 Count input select enable
    Uint32 CNT_INP_SEL    : 5; // 5:1 Count input select
    Uint32 STA_INP_SEL    : 5; // 10:6 Start input select
    Uint32 STO_INP_SEL    : 5; // 15:11 Stop input select
};

union CTM_INPUT_SEL_REG
{
    Uint32 all;
    struct CTM_INPUT_SEL_BITS bit;
};

struct CTM_CLEAR_BITS
{                               // bits description
    Uint32 EVENT_CLEAR    : 1;  // 0 Clear EVENT_FIRED
    Uint32 OVERFLOW_CLEAR : 1;  // 1 Clear OVERFLOW
    Uint32 rsvd1          : 14; // 15:2 Reserved
};

union CTM_CLEAR_REG
{
    Uint32 all;
    struct CTM_CLEAR_BITS bit;
};

struct ERAD_COUNTER_REGS
{
    union CTM_CNTL_REG CTM_CNTL;           // Counter Control Register
    union CTM_STATUS_REG CTM_STATUS;       // Counter Status Register
    Uint32 CTM_REF;                        // Counter Reference Register
    Uint32 CTM_COUNT;                      // Counter Current Value Register
    Uint32 CTM_MAX_COUNT;                  // Counter Max Count Value Register
    union CTM_INPUT_SEL_REG CTM_INPUT_SEL; // Counter Input Select Register
    union CTM_CLEAR_REG CTM_CLEAR;         // Counter Clear Register
};

//---------------------------------------------------------------------------
// ERAD External References & Function Declarations:
//
extern volatile struct ERAD_GLOBAL_REGS EradGlobalRegs;
extern volatile struct ERAD_HWBP_REGS EradHWBP1Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP2Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP3Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP4Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP5Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP6Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP7Regs;
extern volatile struct ERAD_HWBP_REGS EradHWBP8Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter1Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter2Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter3Regs;
extern volatile struct ERAD_COUNTER_REGS EradCounter4Regs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
