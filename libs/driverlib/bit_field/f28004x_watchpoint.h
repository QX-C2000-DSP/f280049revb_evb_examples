#ifndef F28004X_WATCHPOINT_H
#define F28004X_WATCHPOINT_H

#ifdef __cplusplus
extern "C" {
#endif

struct WP_CTRL_BITS
{
    Uint32 RANGE_A_DRAM_LOAD_EN  : 1;
    Uint32 RANGE_B_DRAM_LOAD_EN  : 1;
    Uint32 RANGE_A_DRAM_STORE_EN : 1;
    Uint32 RANGE_B_DRAM_STORE_EN : 1;
    Uint32 RANGE_A_PC_EN         : 1;
    Uint32 RANGE_B_PC_EN         : 1;
    Uint32 TO_TRACE_BUFFER_EN    : 1;
    Uint32 TO_EXCEPTION_EN       : 1;
};

union WP_CTRL_REG
{
    Uint32 all;
    // struct WP_CTRL_BITS bit;
};

struct WATCH_POINT_REGS
{
    Uint32 rsvd;               // offset: 0x00
    union WP_CTRL_REG WP_CTRL; // watch point control register, offset: 0x04
    Uint32 WP_ILLADDR;         // detected illegal accessed address, offset: 0x08
    Uint32 WP_DATAA1;          // range A DRAM start address, offset: 0x0C
    Uint32 WP_DATAA2;          // range A DRAM end address  , offset: 0x10
    Uint32 WP_DATAB1;          // range B DRAM start address, offset: 0x14
    Uint32 WP_DATAB2;          // range B DRAM end address  , offset: 0x18
    Uint32 WP_INSNA1;          // range A IRAM start address, offset: 0x1C
    Uint32 WP_INSNA2;          // range A IRAM end address  , offset: 0x20
    Uint32 WP_INSNB1;          // range B IRAM start address, offset: 0x24
    Uint32 WP_INSNB2;          // range B IRAM end address  , offset: 0x28
};

extern volatile struct WATCH_POINT_REGS WatchPointRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
