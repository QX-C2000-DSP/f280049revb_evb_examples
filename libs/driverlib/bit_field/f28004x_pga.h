#ifndef F28004X_PGA_H
#define F28004X_PGA_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// PGA Individual Register Bit Definitions:

struct PGACTL_BITS
{                          // bits description
    Uint32 PGAEN      : 1; // 0 PGA Enable
    Uint32 FILTRESSEL : 4; // 4:1 Filter Resistor Select
    Uint32 GAIN       : 3; // 7:5 PGA gain setting
    Uint32 rsvd1      : 1; // 8 Reserved
    Uint32 rsvd2      : 1; // 9 Reserved
    Uint32 FILTREEN   : 1; // 10 Filter enable
    Uint32 rsvd3      : 1; // 11 Reserved
    Uint32 rsvd4      : 1; // 12 Reserved
    Uint32 rsvd5      : 1; // 13 Reserved
    Uint32 rsvd6      : 7; // 20:14 Reserved
};

union PGACTL_REG
{
    Uint32 all;
    struct PGACTL_BITS bit;
};

struct PGALOCK_BITS
{                             // bits description
    Uint32 PGACTL        : 1; // 0 Lock bit for PGACTL.
    Uint32 rsvd1         : 1; // 1 Reserved
    Uint32 PGAGAIN3TRIM  : 1; // 2 Lock bit for PGAGAIN3TRIM.
    Uint32 PGAGAIN6TRIM  : 1; // 3 Lock bit for PGAGAIN6TRIM.
    Uint32 PGAGAIN12TRIM : 1; // 4 Lock bit for PGAGAIN12TRIM.
    Uint32 PGAGAIN24TRIM : 1; // 5 Lock bit for PGAGAIN24TRIM.
    Uint32 PGAGAIN48TRIM : 1; // 6 Lock bit for PGAGAIN24TRIM.
    Uint32 rsvd3         : 1; // 7 Reserved
    Uint32 rsvd4         : 8; // 15:8 Reserved
};

union PGALOCK_REG
{
    Uint32 all;
    struct PGALOCK_BITS bit;
};

struct PGAGAIN3TRIM_BITS
{                          // bits description
    Uint32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 3
    Uint32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 3
};

union PGAGAIN3TRIM_REG
{
    Uint32 all;
    struct PGAGAIN3TRIM_BITS bit;
};

struct PGAGAIN6TRIM_BITS
{                          // bits description
    Uint32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 6
    Uint32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 6
};

union PGAGAIN6TRIM_REG
{
    Uint32 all;
    struct PGAGAIN6TRIM_BITS bit;
};

struct PGAGAIN12TRIM_BITS
{                          // bits description
    Uint32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 12
    Uint32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 12
};

union PGAGAIN12TRIM_REG
{
    Uint32 all;
    struct PGAGAIN12TRIM_BITS bit;
};

struct PGAGAIN24TRIM_BITS
{                          // bits description
    Uint32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 24
    Uint32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 24
};

union PGAGAIN24TRIM_REG
{
    Uint32 all;
    struct PGAGAIN24TRIM_BITS bit;
};

struct PGAGAIN48TRIM_BITS
{                          // bits description
    Uint32 GAINTRIM   : 8; // 7:0 Gain TRIM value, when gain setting is 48
    Uint32 OFFSETTRIM : 8; // 15:8 OFFSET TRIM value, when Gain setting is 48
};

union PGAGAIN48TRIM_REG
{
    Uint32 all;
    struct PGAGAIN48TRIM_BITS bit;
};

struct PGATYPE_BITS
{                    // bits description
    Uint32 REV  : 8; // 7:0 PGA Revision Field
    Uint32 TYPE : 8; // 15:8 PGA Type Field
};

union PGATYPE_REG
{
    Uint32 all;
    struct PGATYPE_BITS bit;
};

struct PGA_REGS
{
    union PGACTL_REG PGACTL;               // PGA Control Register
    union PGALOCK_REG PGALOCK;             // PGA Lock Register
    union PGAGAIN3TRIM_REG PGAGAIN3TRIM;   // PGA Gain Trim Register for a gain setting of 3
    union PGAGAIN6TRIM_REG PGAGAIN6TRIM;   // PGA Gain Trim Register for a gain setting of 6
    union PGAGAIN12TRIM_REG PGAGAIN12TRIM; // PGA Gain Trim Register for a gain setting of 12
    union PGAGAIN24TRIM_REG PGAGAIN24TRIM; // PGA Gain Trim Register for a gain setting of 24
    union PGAGAIN48TRIM_REG PGAGAIN48TRIM; // PGA Gain Trim Register for a gain setting of 48
    union PGATYPE_REG PGATYPE;             // PGA Type Register
};

//---------------------------------------------------------------------------
// PGA External References & Function Declarations:
//
extern volatile struct PGA_REGS Pga1Regs;
extern volatile struct PGA_REGS Pga2Regs;
extern volatile struct PGA_REGS Pga3Regs;
extern volatile struct PGA_REGS Pga4Regs;
extern volatile struct PGA_REGS Pga5Regs;
extern volatile struct PGA_REGS Pga6Regs;
extern volatile struct PGA_REGS Pga7Regs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
