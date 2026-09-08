#ifndef F28004X_TRACEBUFFER_H
#define F28004X_TRACEBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

struct TB_MODE1_BITS
{
    Uint32 MODE1_EN : 1;
};

union TB_MODE1_REG
{
    Uint32 all;
    // struct TB_MODE1_BITS bit;
};

struct TB_MODE2_BITS
{
    Uint32 rsvd     : 1;
    Uint32 MODE2_EN : 1;
};

union TB_MODE2_REG
{
    Uint32 all;
    // struct TB_MODE2_BITS bit;
};

struct TB_DISABLE_BITS
{
    Uint32 DISABLE : 16;
};

union TB_DISABLE_REG
{
    Uint32 all;
    // struct TB_DISABLE_BITS bit;
};

struct TRACE_BUFFER_REGS
{
    Uint32 rsvd;                  // offset: 0x00
    union TB_MODE1_REG MODE1;     // offset: 0x04
    union TB_MODE2_REG MODE2;     // offset: 0x08
    union TB_DISABLE_REG DISABLE; // offset: 0x0C
    Uint32 TB_OUT;                // offset: 0x10
};

extern volatile struct TRACE_BUFFER_REGS TraceBufferRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
