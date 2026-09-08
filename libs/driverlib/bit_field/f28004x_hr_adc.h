#ifndef F28004X_HR_ADC_H
#define F28004X_HR_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

struct HR_ADCCTL1_BITS
{
    Uint32 rsvd2         : 2;  /* 1:0 */
    Uint32 INTPULSEPOS   : 1;  /* 2 */
    Uint32 DISLVL        : 1;  /* 3 */
    Uint32 ENLDO         : 1;  /* 4 */
    Uint32 STARTCAL_P    : 1;  /* 5 */
    Uint32 RESETZ_P      : 1;  /* 6 */
    Uint32 ADC_EN_P      : 1;  /* 7 */
    Uint32 ADC_BUSYCHAN  : 4;  /* 11:8 */
    Uint32 rsvd1         : 1;  /* 12 */
    Uint32 ADCBSY        : 1;  /* 13 */
    Uint32 SELRANGE_LDO  : 1;  /* 14 */
    Uint32 STARTVOSCAL_P : 1;  /* 15 */
    Uint32 rsvd0         : 16; /* 31:16 */
};

union HR_ADCCTL1_REG
{
    Uint32 all;
    struct HR_ADCCTL1_BITS bit;
};

struct HR_ADCCTL2_BITS
{
    Uint32 PRESCALE : 5;  /* 4:0 */
    Uint32 SELRES   : 2;  /* 6:5 */
    Uint32 SELDIFF  : 1;  /* 7 */
    Uint32 rsvd     : 24; /* 31:8 */
};

union HR_ADCCTL2_REG
{
    /* data */
    Uint32 all;
    struct HR_ADCCTL2_BITS bit;
};

struct HR_ADCINTFLG_BITS
{
    Uint32 ADCINT1 : 1;  /* 0 */
    Uint32 ADCINT2 : 1;  /* 1 */
    Uint32 ADCINT3 : 1;  /* 2 */
    Uint32 ADCINT4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTFLG_REG
{
    Uint32 all;
    struct HR_ADCINTFLG_BITS bit;
};

struct HR_ADCINTFLGCLR_BITS
{
    Uint32 ADCINT1 : 1;  /* 0 */
    Uint32 ADCINT2 : 1;  /* 1 */
    Uint32 ADCINT3 : 1;  /* 2 */
    Uint32 ADCINT4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTFLGCLR_REG
{
    Uint32 all;
    struct HR_ADCINTFLGCLR_BITS bit;
};

struct HR_ADCINTOVF_BITS
{
    Uint32 ADCINT1 : 1;  /* 0 */
    Uint32 ADCINT2 : 1;  /* 1 */
    Uint32 ADCINT3 : 1;  /* 2 */
    Uint32 ADCINT4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTOVF_REG
{
    Uint32 all;
    struct HR_ADCINTOVF_BITS bit;
};

struct HR_ADCINTOVFCLR_BITS
{
    Uint32 ADCINT1 : 1;  /* 0 */
    Uint32 ADCINT2 : 1;  /* 1 */
    Uint32 ADCINT3 : 1;  /* 2 */
    Uint32 ADCINT4 : 1;  /* 3 */
    Uint32 rsvd    : 28; /* 31:4 */
};

union HR_ADCINTOVFCLR_REG
{
    Uint32 all;
    struct HR_ADCINTOVFCLR_BITS bit;
};

struct HR_ADCINTSELINT_BITS
{
    Uint32 INT1SEL  : 4; /* 3:0 */
    Uint32 RSVD0    : 1; /* 4 */
    Uint32 INT1EN   : 1; /* 5 */
    Uint32 INT1CONT : 1; /* 6 */
    Uint32 RSVD1    : 1; /* 7 */
    Uint32 INT2SEL  : 4; /* 11:8 */
    Uint32 RSVD2    : 1; /* 12 */
    Uint32 INT2EN   : 1; /* 13 */
    Uint32 INT2CONT : 1; /* 14 */
    Uint32 RSVD3    : 1; /* 15 */
    Uint32 INT3SEL  : 4; /* 19:16 */
    Uint32 RSVD4    : 1; /* 20 */
    Uint32 INT3EN   : 1; /* 21 */
    Uint32 INT3CONT : 1; /* 22 */
    Uint32 RSVD5    : 1; /* 23 */
    Uint32 INT4SEL  : 4; /* 27:24*/
    Uint32 RSVD6    : 1; /* 28 */
    Uint32 INT4EN   : 1; /* 29 */
    Uint32 INT4CONT : 1; /* 30 */
    Uint32 RSVD7    : 1; /* 31 */
};

union HR_ADCINTSELINT_REG
{
    Uint32 all;
    struct HR_ADCINTSELINT_BITS bit;
};

struct HR_ADCSOCPRICTL_BITS
{
    Uint32 SOCPRIORITY : 5;  /* 4:0 */
    Uint32 RRPOINT     : 5;  /* 9:5 */
    Uint32 rsvd        : 22; /* 31:10 */
};

union HR_ADCSOCPRICTL_REG
{
    Uint32 all;
    struct HR_ADCSOCPRICTL_BITS bit;
};

struct HR_ADCSOCFLG_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};

union HR_ADCSOCFLG_REG
{
    Uint32 all;
    struct HR_ADCSOCFLG_BITS bit;
};

struct HR_ADCSOCFRC_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};
union HR_ADCSOCFRC_REG
{
    Uint32 all;
    struct HR_ADCSOCFRC_BITS bit;
};

struct HR_ADCSOCOVF_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};
union HR_ADCSOCOVF_REG
{
    Uint32 all;
    struct HR_ADCSOCOVF_BITS bit;
};

struct HR_ADCSOCOVFCLR_BITS
{
    Uint32 SOC0  : 1;  /* 0 */
    Uint32 SOC1  : 1;  /* 1 */
    Uint32 SOC2  : 1;  /* 2 */
    Uint32 SOC3  : 1;  /* 3 */
    Uint32 SOC4  : 1;  /* 4 */
    Uint32 SOC5  : 1;  /* 5 */
    Uint32 SOC6  : 1;  /* 6 */
    Uint32 SOC7  : 1;  /* 7 */
    Uint32 SOC8  : 1;  /* 8 */
    Uint32 SOC9  : 1;  /* 9 */
    Uint32 SOC10 : 1;  /* 10 */
    Uint32 SOC11 : 1;  /* 11 */
    Uint32 SOC12 : 1;  /* 12 */
    Uint32 SOC13 : 1;  /* 13 */
    Uint32 SOC14 : 1;  /* 14 */
    Uint32 SOC15 : 1;  /* 15 */
    Uint32 rsvd  : 16; /* 31:16 */
};
union HR_ADCSOCOVFCLR_REG
{
    Uint32 all;
    struct HR_ADCSOCOVFCLR_BITS bit;
};

struct HR_ADCSOCCTL_BITS
{
    Uint32 rsvd0   : 15; /* 2:0 */
    Uint32 CHSEL   : 4;  /* 7:3 */
    Uint32 rsvd1   : 1;  /* 11:8 */
    Uint32 TRIGSEL : 5;  /* 14:12 */
    Uint32 rsvd2   : 7;  /* 31:15 */
};
union HR_ADCSOCCTL_REG
{
    Uint32 all;
    struct HR_ADCSOCCTL_BITS bit;
};

struct HR_ADCEVTSTAT_BITS
{
    Uint32 PPB1TRIPHI : 1;  /* 0 */
    Uint32 PPB1TRIPLO : 1;  /* 1 */
    Uint32 PPB1ZERO   : 1;  /* 2 */
    Uint32 PPB2TRIPHI : 1;  /* 3 */
    Uint32 PPB2TRIPLO : 1;  /* 4 */
    Uint32 PPB2ZERO   : 1;  /* 5 */
    Uint32 PPB3TRIPHI : 1;  /* 6 */
    Uint32 PPB3TRIPLO : 1;  /* 7 */
    Uint32 PPB3ZERO   : 1;  /* 8 */
    Uint32 PPB4TRIPHI : 1;  /* 9 */
    Uint32 PPB4TRIPLO : 1;  /* 10 */
    Uint32 PPB4ZERO   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};

union HR_ADCEVTSTAT_REG
{
    Uint32 all;
    struct HR_ADCEVTSTAT_BITS bit;
};

struct HR_ADCEVTCLR_BITS
{
    Uint32 PPB1TRIPHI : 1;  /* 0 */
    Uint32 PPB1TRIPLO : 1;  /* 1 */
    Uint32 PPB1ZERO   : 1;  /* 2 */
    Uint32 PPB2TRIPHI : 1;  /* 3 */
    Uint32 PPB2TRIPLO : 1;  /* 4 */
    Uint32 PPB2ZERO   : 1;  /* 5 */
    Uint32 PPB3TRIPHI : 1;  /* 6 */
    Uint32 PPB3TRIPLO : 1;  /* 7 */
    Uint32 PPB3ZERO   : 1;  /* 8 */
    Uint32 PPB4TRIPHI : 1;  /* 9 */
    Uint32 PPB4TRIPLO : 1;  /* 10 */
    Uint32 PPB4ZERO   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};
union HR_ADCEVTCLR_REG
{
    Uint32 all;
    struct HR_ADCEVTCLR_BITS bit;
};

struct HR_ADCEVTSEL_BITS
{
    Uint32 PPB1TRIPHI : 1;  /* 0 */
    Uint32 PPB1TRIPLO : 1;  /* 1 */
    Uint32 PPB1ZERO   : 1;  /* 2 */
    Uint32 PPB2TRIPHI : 1;  /* 3 */
    Uint32 PPB2TRIPLO : 1;  /* 4 */
    Uint32 PPB2ZERO   : 1;  /* 5 */
    Uint32 PPB3TRIPHI : 1;  /* 6 */
    Uint32 PPB3TRIPLO : 1;  /* 7 */
    Uint32 PPB3ZERO   : 1;  /* 8 */
    Uint32 PPB4TRIPHI : 1;  /* 9 */
    Uint32 PPB4TRIPLO : 1;  /* 10 */
    Uint32 PPB4ZERO   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};
union HR_ADCEVTSEL_REG
{
    Uint32 all;
    struct HR_ADCEVTSEL_BITS bit;
};

struct HR_ADCEVTINTSEL_BITS
{
    Uint32 PPB1TRIPHI : 1;  /* 0 */
    Uint32 PPB1TRIPLO : 1;  /* 1 */
    Uint32 PPB1ZERO   : 1;  /* 2 */
    Uint32 PPB2TRIPHI : 1;  /* 3 */
    Uint32 PPB2TRIPLO : 1;  /* 4 */
    Uint32 PPB2ZERO   : 1;  /* 5 */
    Uint32 PPB3TRIPHI : 1;  /* 6 */
    Uint32 PPB3TRIPLO : 1;  /* 7 */
    Uint32 PPB3ZERO   : 1;  /* 8 */
    Uint32 PPB4TRIPHI : 1;  /* 9 */
    Uint32 PPB4TRIPLO : 1;  /* 10 */
    Uint32 PPB4ZERO   : 1;  /* 11 */
    Uint32 rsvd       : 20; /* 31:12 */
};
union HR_ADCEVTINTSEL_REG
{
    Uint32 all;
    struct HR_ADCEVTINTSEL_BITS bit;
};

struct HR_ADCCOUNT_BITS
{
    Uint32 FREECOUNT : 12; /* 11:0*/
    Uint32 rsvd      : 20; /* 31:12 */
};
union HR_ADCCOUNT_REG
{
    Uint32 all;
    struct HR_ADCCOUNT_BITS bit;
};

struct HR_ADCREV_BITS
{
    Uint32 ADC_TYPE : 8;  /* 7:0 */
    Uint32 REV      : 8;  /* 15:8 */
    Uint32 rsvd     : 16; /* 31:16 */
};
union HR_ADCREV_REG
{
    Uint32 all;
    struct HR_ADCREV_BITS bit;
};

struct HR_ADCPPBCONFIG_BITS
{
    Uint32 CONFIG     : 5;  /* 4:0 */
    Uint32 TWOSCOMPEN : 1;  /* 1 */
    Uint32 CBCEN      : 1;  /* 1 */
    Uint32 rsvd       : 25; /* 31:7 */
};
union HR_ADCPPBCONFIG_REG
{
    Uint32 all;
    struct HR_ADCPPBCONFIG_BITS bit;
};

struct HR_ADCPPBSTAMP_BITS
{
    Uint32 DLYSTAMP : 12; /* 11:0  */
    Uint32 rsvd     : 20; /* 31:12 */
};
union HR_ADCPPBSTAMP_REG
{
    Uint32 all;
    struct HR_ADCPPBSTAMP_BITS bit;
};

struct HR_ADCPPBOFFCAL_BITS
{
    Uint32 OFFCAL : 10; /* 9:0 */
    Uint32 rsvd   : 22; /* 31:10 */
};
union HR_ADCPPBOFFCAL_REG
{
    Uint32 all;
    struct HR_ADCPPBOFFCAL_BITS bit;
};

struct HR_ADCPPBOFFREF_BITS
{
    Uint32 OFFREF : 14; /* 15:0 */
    Uint32 rsvd   : 18; /* 31:16 */
};
union HR_ADCPPBOFFREF_REG
{
    Uint32 all;
    struct HR_ADCPPBOFFREF_BITS bit;
};

struct HR_ADCPPBTRIPHI_BITS
{
    Uint32 LIMITHI : 14; /* 13:0 */
    Uint32 HSIGN   : 1;  /* 14 */
    Uint32 rsvd    : 17; /* 31:15 */
};
union HR_ADCPPBTRIPHI_REG
{
    Uint32 all;
    struct HR_ADCPPBTRIPHI_BITS bit;
};

struct HR_ADCPPBTRIPLO_BITS
{
    Uint32 LIMITHI : 14; /* 13:0 */
    Uint32 HSIGN   : 1;  /* 1 */
    Uint32 rsvd    : 17; /* 31:15 */
};
union HR_ADCPPBTRIPLO_REG
{
    Uint32 all;
    struct HR_ADCPPBTRIPLO_BITS bit;
};

struct HR_ADCRESULT_BITS
{
    Uint32 RESULT : 14; /* 13:0 */
    Uint32 rsvd   : 18; /* 31:14*/
};
union HR_ADCRESULT_REG
{
    Uint32 all;
    struct HR_ADCRESULT_BITS bit;
};

struct HR_ADCPPBRESULT_BITS
{
    Uint32 PPBRESULT : 16; /* 15:0 */
    Uint32 SIGN      : 16; /* 31:16 */
};
union HR_ADCPPBRESULT_REG
{
    Uint32 all;
    struct HR_ADCPPBRESULT_BITS bit;
};

struct HR_ADC_REGS
{
    union HR_ADCCTL1_REG ADCCTL1;           /* 0x00 */
    union HR_ADCCTL2_REG ADCCTL2;           /* 0x04 */
    union HR_ADCINTFLG_REG ADCINTFLG;       /* 0x08 */
    union HR_ADCINTFLGCLR_REG ADCINTFLGCLR; /* 0x0c */
    union HR_ADCINTOVF_REG ADCINTOVF;       /* 0x10 */
    union HR_ADCINTOVFCLR_REG ADCINTOVFCLR; /* 0x14 */
    union HR_ADCINTSELINT_REG ADCINTSELINT; /* 0x18 */
    union HR_ADCSOCPRICTL_REG ADCSOCPRICTL; /* 0x1c */
    union HR_ADCSOCFLG_REG ADCSOCFLG;       /* 0x20 */
    union HR_ADCSOCFRC_REG ADCSOCFRC;       /* 0x24 */
    union HR_ADCSOCOVF_REG ADCSOCOVF;       /* 0x28 */
    union HR_ADCSOCOVFCLR_REG ADCSOCOVFCLR; /* 0x2c */
    union HR_ADCSOCCTL_REG ADCSOC0CTL;      /* 0x30 */
    union HR_ADCSOCCTL_REG ADCSOC1CTL;      /* 0x34 */
    union HR_ADCSOCCTL_REG ADCSOC2CTL;      /* 0x38 */
    union HR_ADCSOCCTL_REG ADCSOC3CTL;      /* 0x3c */
    union HR_ADCSOCCTL_REG ADCSOC4CTL;      /* 0x40 */
    union HR_ADCSOCCTL_REG ADCSOC5CTL;      /* 0x44 */
    union HR_ADCSOCCTL_REG ADCSOC6CTL;      /* 0x48 */
    union HR_ADCSOCCTL_REG ADCSOC7CTL;      /* 0x4c */
    union HR_ADCSOCCTL_REG ADCSOC8CTL;      /* 0x50 */
    union HR_ADCSOCCTL_REG ADCSOC9CTL;      /* 0x54 */
    union HR_ADCSOCCTL_REG ADCSOC10CTL;     /* 0x58 */
    union HR_ADCSOCCTL_REG ADCSOC11CTL;     /* 0x5c */
    union HR_ADCSOCCTL_REG ADCSOC12CTL;     /* 0x60 */
    union HR_ADCSOCCTL_REG ADCSOC13CTL;     /* 0x64 */
    union HR_ADCSOCCTL_REG ADCSOC14CTL;     /* 0x68 */
    union HR_ADCSOCCTL_REG ADCSOC15CTL;     /* 0x6c */
    union HR_ADCEVTSTAT_REG ADCEVTSTAT;     /* 0x70 */
    union HR_ADCEVTCLR_REG ADCEVTCLR;       /* 0x74 */
    union HR_ADCEVTSEL_REG ADCEVTSEL;       /* 0x78 */
    union HR_ADCEVTINTSEL_REG ADCEVTINTSEL; /* 0x7c */
    union HR_ADCCOUNT_REG ADCCOUNTER;       /* 0x80 */
    union HR_ADCREV_REG ADCREV;             /* 0x84 */

    union HR_ADCPPBCONFIG_REG ADCPPB1CONFIG; /* 0x88 */
    union HR_ADCPPBSTAMP_REG ADCPPB1STAMP;   /* 0x8c */
    union HR_ADCPPBOFFCAL_REG ADCPPB1OFFCAL; /* 0x90 */
    union HR_ADCPPBOFFREF_REG ADCPPB1OFFREF; /* 0x94 */
    union HR_ADCPPBTRIPHI_REG ADCPPB1TRIPHI; /* 0x98 */
    union HR_ADCPPBTRIPLO_REG ADCPPB1TRIPLO; /* 0x9c */

    union HR_ADCPPBCONFIG_REG ADCPPB2CONFIG; /* 0xa0 */
    union HR_ADCPPBSTAMP_REG ADCPPB2STAMP;   /* 0xa4 */
    union HR_ADCPPBOFFCAL_REG ADCPPB2OFFCAL; /* 0xa8 */
    union HR_ADCPPBOFFREF_REG ADCPPB2OFFREF; /* 0xac */
    union HR_ADCPPBTRIPHI_REG ADCPPB2TRIPHI; /* 0xb0 */
    union HR_ADCPPBTRIPLO_REG ADCPPB2TRIPLO; /* 0xb4 */

    union HR_ADCPPBCONFIG_REG ADCPPB3CONFIG; /* 0xb8 */
    union HR_ADCPPBSTAMP_REG ADCPPB3STAMP;   /* 0xbc */
    union HR_ADCPPBOFFCAL_REG ADCPPB3OFFCAL; /* 0xc0 */
    union HR_ADCPPBOFFREF_REG ADCPPB3OFFREF; /* 0xc4 */
    union HR_ADCPPBTRIPHI_REG ADCPPB3TRIPHI; /* 0xc8 */
    union HR_ADCPPBTRIPLO_REG ADCPPB3TRIPLO; /* 0xcc */

    union HR_ADCPPBCONFIG_REG ADCPPB4CONFIG; /* 0xd0 */
    union HR_ADCPPBSTAMP_REG ADCPPB4STAMP;   /* 0xd4 */
    union HR_ADCPPBOFFCAL_REG ADCPPB4OFFCAL; /* 0xd8 */
    union HR_ADCPPBOFFREF_REG ADCPPB4OFFREF; /* 0xdc */
    union HR_ADCPPBTRIPHI_REG ADCPPB4TRIPHI; /* 0xe0 */
    union HR_ADCPPBTRIPLO_REG ADCPPB4TRIPLO; /* 0xe4 */
};

struct HR_ADC_RESULT_REGS
{
    union HR_ADCRESULT_REG ADCRESULT0;  /* 0x100 */
    union HR_ADCRESULT_REG ADCRESULT1;  /* 0x104 */
    union HR_ADCRESULT_REG ADCRESULT2;  /* 0x108 */
    union HR_ADCRESULT_REG ADCRESULT3;  /* 0x10c */
    union HR_ADCRESULT_REG ADCRESULT4;  /* 0x110 */
    union HR_ADCRESULT_REG ADCRESULT5;  /* 0x114 */
    union HR_ADCRESULT_REG ADCRESULT6;  /* 0x118 */
    union HR_ADCRESULT_REG ADCRESULT7;  /* 0x11c */
    union HR_ADCRESULT_REG ADCRESULT8;  /* 0x120 */
    union HR_ADCRESULT_REG ADCRESULT9;  /* 0x124 */
    union HR_ADCRESULT_REG ADCRESULT10; /* 0x128 */
    union HR_ADCRESULT_REG ADCRESULT11; /* 0x12c */
    union HR_ADCRESULT_REG ADCRESULT12; /* 0x130 */
    union HR_ADCRESULT_REG ADCRESULT13; /* 0x134 */
    union HR_ADCRESULT_REG ADCRESULT14; /* 0x138 */
    union HR_ADCRESULT_REG ADCRESULT15; /* 0x13c */
};

struct HR_ADC_PPBRESULT_REGS
{
    union HR_ADCPPBRESULT_REG ADCPPB1RESULT; /* 0x150 */
    union HR_ADCPPBRESULT_REG ADCPPB2RESULT; /* 0x154 */
    union HR_ADCPPBRESULT_REG ADCPPB3RESULT; /* 0x158 */
    union HR_ADCPPBRESULT_REG ADCPPB4RESULT; /* 0x15c */
};

#if 0
struct I_APB_ADDR_BITS
{
    /* data */
    Uint32  addr            : 8  ;          /* 7:0 */
    Uint32  rsvd            : 24 ;          /* 31:8 */
};
union I_APB_ADDR_REG{
    Uint32  all;
    struct  I_APB_ADDR_BITS bit;
};


struct I_APB_DATA_BITS
{
    /* data */
    Uint32  data           : 8  ;           /* 7:0 */
    Uint32  rsvd           : 24 ;           /* 31:8 */
};
union I_APB_DATA_REG{
    Uint32  all;
    struct  I_APB_DATA_BITS bit;
};

struct I_APB_CTRL_BITS
{
    /* data */
    Uint32  validity       : 1 ;            /* 0 */
    Uint32  rsvd           : 31 ;           /* 31:1 */
};
union I_APB_CTRL_REG{
    Uint32   all;
    struct  I_APB_CTRL_BITS bit;
};

struct I_COEF_CTRL_BITS
{
    /* data */
    Uint32  latch_coef         : 1 ;        /* 0 */
    Uint32  capture_coe        : 1 ;        /* 1 */
    Uint32  rsvd               : 30 ;       /* 31:2 */
};
union I_COEF_CTRL_REG{
    Uint8   all;
    struct  I_COEF_CTRL_BITS bit;
};

struct I_COEF_BITS
{
    /* data */
    Uint32  calibration         : 8  ;      /* 7:0 */
    Uint32  rsvd                : 24 ;      /* 31:8 */
};
union I_COEF_REG{
    Uint32   all;
    struct  I_COEF_BITS bit;
};

struct I_COEFS_RO_BITS
{
    /* data */
    Uint32  inter_calibration   : 8  ;       /* 7:0 */
    Uint32  rsvd                : 24 ;       /* 31:0 */
};
union I_COEFS_RO_REG{
    Uint32  all;
    struct  I_COEFS_RO_BITS bit;
};


struct APB_REGS{
    union   I_APB_ADDR_REG      i_apb_addr;             /* 0x200 */
    union   I_APB_DATA_REG      i_apb_data;             /* 0x204 */
    union   I_APB_CTRL_REG      i_apb_ctrl;             /* 0x208 */
    union   I_COEF_CTRL_REG     i_coef_ctrl;            /* 0x20c */
};

struct APB_COEFS_REGS{
    union   I_COEFS_REG         i_coefs_8;              /* 0x220 */
    union   I_COEFS_REG         i_coefs_9;              /* 0x224 */
    union   I_COEFS_REG         i_coefs_a;              /* 0x228 */
    union   I_COEFS_REG         i_coefs_b;              /* 0x22c */
    union   I_COEFS_REG         i_coefs_c;              /* 0x230 */
    union   I_COEFS_REG         i_coefs_d;              /* 0x234 */
    union   I_COEFS_REG         i_coefs_e;              /* 0x238 */
    union   I_COEFS_REG         i_coefs_f;              /* 0x23c */
    union   I_COEFS_REG         i_coefs_10;              /* 0x240 */
    union   I_COEFS_REG         i_coefs_11;              /* 0x244 */
    union   I_COEFS_REG         i_coefs_12;              /* 0x248 */
    union   I_COEFS_REG         i_coefs_13;              /* 0x24c */
    union   I_COEFS_REG         i_coefs_14;              /* 0x250 */
    union   I_COEFS_REG         i_coefs_15;              /* 0x254 */
    union   I_COEFS_REG         i_coefs_16;              /* 0x258 */
    union   I_COEFS_REG         i_coefs_17;              /* 0x25c */
    union   I_COEFS_REG         i_coefs_18;              /* 0x260 */
    union   I_COEFS_REG         i_coefs_19;              /* 0x264 */
    union   I_COEFS_REG         i_coefs_1a;              /* 0x268 */
    union   I_COEFS_REG         i_coefs_1b;              /* 0x26c */
    union   I_COEFS_REG         i_coefs_1c;              /* 0x270 */
    union   I_COEFS_REG         i_coefs_1d;              /* 0x274 */
    union   I_COEFS_REG         i_coefs_1e;              /* 0x278 */
    union   I_COEFS_REG         i_coefs_1f;              /* 0x27c */
    union   I_COEFS_REG         i_coefs_20;              /* 0x280 */
    union   I_COEFS_REG         i_coefs_21;              /* 0x284 */
    union   I_COEFS_REG         i_coefs_22;              /* 0x288 */
    union   I_COEFS_REG         i_coefs_23;              /* 0x28c */
    union   I_COEFS_REG         i_coefs_24;              /* 0x290 */
    union   I_COEFS_REG         i_coefs_25;              /* 0x294 */
    union   I_COEFS_REG         i_coefs_26;              /* 0x298 */
};

struct APB_COEFS_RO_REGS
{
    /* data */
    union   I_COEFS_RO_REG      i_coefs_ro_2c;           /* 0x2b0 */
    union   I_COEFS_RO_REG      i_coefs_ro_2d;           /* 0x2b4 */
    union   I_COEFS_RO_REG      i_coefs_ro_2e;           /* 0x2b8 */
    union   I_COEFS_RO_REG      i_coefs_ro_2f;           /* 0x2bc */
    union   I_COEFS_RO_REG      i_coefs_ro_30;           /* 0x2c0 */
    union   I_COEFS_RO_REG      i_coefs_ro_31;           /* 0x2c4 */
    union   I_COEFS_RO_REG      i_coefs_ro_32;           /* 0x2c8 */
    union   I_COEFS_RO_REG      i_coefs_ro_33;           /* 0x2cc */
    union   I_COEFS_RO_REG      i_coefs_ro_34;           /* 0x2d0 */
    union   I_COEFS_RO_REG      i_coefs_ro_35;           /* 0x2d4 */
    union   I_COEFS_RO_REG      i_coefs_ro_36;           /* 0x2d8 */
    union   I_COEFS_RO_REG      i_coefs_ro_37;           /* 0x2dc */
    union   I_COEFS_RO_REG      i_coefs_ro_38;           /* 0x2e0 */
    union   I_COEFS_RO_REG      i_coefs_ro_39;           /* 0x2e4 */
    union   I_COEFS_RO_REG      i_coefs_ro_3a;           /* 0x2e8 */
    union   I_COEFS_RO_REG      i_coefs_ro_3b;           /* 0x2ec */
    union   I_COEFS_RO_REG      i_coefs_ro_3c;           /* 0x2f0 */
    union   I_COEFS_RO_REG      i_coefs_ro_3d;           /* 0x2f4 */
    union   I_COEFS_RO_REG      i_coefs_ro_3e;           /* 0x2f8 */
    union   I_COEFS_RO_REG      i_coefs_ro_3f;           /* 0x2fc */
    union   I_COEFS_RO_REG      i_coefs_ro_40;           /* 0x300 */
    union   I_COEFS_RO_REG      i_coefs_ro_41;           /* 0x304 */
    union   I_COEFS_RO_REG      i_coefs_ro_42;           /* 0x308 */
    union   I_COEFS_RO_REG      i_coefs_ro_43;           /* 0x30c */
    union   I_COEFS_RO_REG      i_coefs_ro_44;           /* 0x310 */
    union   I_COEFS_RO_REG      i_coefs_ro_45;           /* 0x314 */
    union   I_COEFS_RO_REG      i_coefs_ro_46;           /* 0x318 */
    union   I_COEFS_RO_REG      i_coefs_ro_47;           /* 0x31c */
    union   I_COEFS_RO_REG      i_coefs_ro_48;           /* 0x320 */
    union   I_COEFS_RO_REG      i_coefs_ro_49;           /* 0x324 */
    union   I_COEFS_RO_REG      i_coefs_ro_4a;           /* 0x328 */
    union   I_COEFS_RO_REG      i_coefs_ro_4b;           /* 0x32c */
    union   I_COEFS_RO_REG      i_coefs_ro_4c;           /* 0x330 */
    union   I_COEFS_RO_REG      i_coefs_ro_4d;           /* 0x334 */
    union   I_COEFS_RO_REG      i_coefs_ro_4e;           /* 0x338 */
    union   I_COEFS_RO_REG      i_coefs_ro_4f;           /* 0x33c */
};
#endif

//---------------------------------------------------------------------------
// HR_ADC External References & Function Declarations:
//

extern volatile struct HR_ADC_REGS HrAdcaRegs;
extern volatile struct HR_ADC_REGS HrAdcbRegs;
extern volatile struct HR_ADC_REGS HrAdccRegs;

extern volatile struct HR_ADC_RESULT_REGS HrAdcaResultRegs;
extern volatile struct HR_ADC_RESULT_REGS HrAdcbResultRegs;
extern volatile struct HR_ADC_RESULT_REGS HrAdccResultRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
