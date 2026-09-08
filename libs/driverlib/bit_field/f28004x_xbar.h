#ifndef F28004X_XBAR_H
#define F28004X_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// XBAR Individual Register Bit Definitions:

struct XBARFLG1_BITS
{                                // bits description
    Uint32 CMPSS1_CTRIPL    : 1; // 0 Input Flag for CMPSS1.CTRIPL Signal
    Uint32 CMPSS1_CTRIPH    : 1; // 1 Input Flag for CMPSS1.CTRIPH Signal
    Uint32 CMPSS2_CTRIPL    : 1; // 2 Input Flag for CMPSS2.CTRIPL Signal
    Uint32 CMPSS2_CTRIPH    : 1; // 3 Input Flag for CMPSS2.CTRIPH Signal
    Uint32 CMPSS3_CTRIPL    : 1; // 4 Input Flag for CMPSS3.CTRIPL Signal
    Uint32 CMPSS3_CTRIPH    : 1; // 5 Input Flag for CMPSS3.CTRIPH Signal
    Uint32 CMPSS4_CTRIPL    : 1; // 6 Input Flag for CMPSS4.CTRIPL Signal
    Uint32 CMPSS4_CTRIPH    : 1; // 7 Input Flag for CMPSS4.CTRIPH Signal
    Uint32 CMPSS5_CTRIPL    : 1; // 8 Input Flag for CMPSS5.CTRIPL Signal
    Uint32 CMPSS5_CTRIPH    : 1; // 9 Input Flag for CMPSS5.CTRIPH Signal
    Uint32 CMPSS6_CTRIPL    : 1; // 10 Input Flag for CMPSS6.CTRIPL Signal
    Uint32 CMPSS6_CTRIPH    : 1; // 11 Input Flag for CMPSS6.CTRIPH Signal
    Uint32 CMPSS7_CTRIPL    : 1; // 12 Input Flag for CMPSS7.CTRIPL Signal
    Uint32 CMPSS7_CTRIPH    : 1; // 13 Input Flag for CMPSS7.CTRIPH Signal
    Uint32 rsvd1            : 2; // 14-15 Reserved
    Uint32 CMPSS1_CTRIPOUTL : 1; // 16 Input Flag for CMPSS1.CTRIPOUTL Signal
    Uint32 CMPSS1_CTRIPOUTH : 1; // 17 Input Flag for CMPSS1.CTRIPOUTH Signal
    Uint32 CMPSS2_CTRIPOUTL : 1; // 18 Input Flag for CMPSS2.CTRIPOUTL Signal
    Uint32 CMPSS2_CTRIPOUTH : 1; // 19 Input Flag for CMPSS2.CTRIPOUTH Signal
    Uint32 CMPSS3_CTRIPOUTL : 1; // 20 Input Flag for CMPSS3.CTRIPOUTL Signal
    Uint32 CMPSS3_CTRIPOUTH : 1; // 21 Input Flag for CMPSS3.CTRIPOUTH Signal
    Uint32 CMPSS4_CTRIPOUTL : 1; // 22 Input Flag for CMPSS4.CTRIPOUTL Signal
    Uint32 CMPSS4_CTRIPOUTH : 1; // 23 Input Flag for CMPSS4.CTRIPOUTH Signal
    Uint32 CMPSS5_CTRIPOUTL : 1; // 24 Input Flag for CMPSS5.CTRIPOUTL Signal
    Uint32 CMPSS5_CTRIPOUTH : 1; // 25 Input Flag for CMPSS5.CTRIPOUTH Signal
    Uint32 CMPSS6_CTRIPOUTL : 1; // 26 Input Flag for CMPSS6.CTRIPOUTL Signal
    Uint32 CMPSS6_CTRIPOUTH : 1; // 27 Input Flag for CMPSS6.CTRIPOUTH Signal
    Uint32 CMPSS7_CTRIPOUTL : 1; // 28 Input Flag for CMPSS7.CTRIPOUTL Signal
    Uint32 CMPSS7_CTRIPOUTH : 1; // 29 Input Flag for CMPSS7.CTRIPOUTH Signal
    Uint32 rsvd2            : 2; // 30-31 Reserved
};

union XBARFLG1_REG
{
    Uint32 all;
    struct XBARFLG1_BITS bit;
};

struct XBARFLG2_BITS
{                          // bits description
    Uint32 INPUT1     : 1; // 0 Input Flag for INPUT1 Signal
    Uint32 INPUT2     : 1; // 1 Input Flag for INPUT2 Signal
    Uint32 INPUT3     : 1; // 2 Input Flag for INPUT3 Signal
    Uint32 INPUT4     : 1; // 3 Input Flag for INPUT4 Signal
    Uint32 INPUT5     : 1; // 4 Input Flag for INPUT5 Signal
    Uint32 INPUT6     : 1; // 5 Input Flag for INPUT6 Signal
    Uint32 ADCSOCA    : 1; // 6 Input Flag for ADCSOCA Signal
    Uint32 ADCSOCB    : 1; // 7 Input Flag for ADCSOCB Signal
    Uint32 INPUT7     : 1; // 8 Input Flag for INPUT7 Signal
    Uint32 INPUT8     : 1; // 9 Input Flag for INPUT8 Signal
    Uint32 INPUT9     : 1; // 10 Input Flag for INPUT9 Signal
    Uint32 INPUT10    : 1; // 11 Input Flag for INPUT10\ Signal
    Uint32 INPUT11    : 1; // 12 Input Flag for INPUT11 Signal
    Uint32 INPUT12    : 1; // 13 Input Flag for INPUT12 Signal
    Uint32 INPUT13    : 1; // 14 Input Flag for INPUT13 Signal
    Uint32 INPUT14    : 1; // 15 Input Flag for INPUT14 Signal
    Uint32 ECAP1_OUT  : 1; // 16 Input Flag for ECAP1.OUT Signal
    Uint32 ECAP2_OUT  : 1; // 17 Input Flag for ECAP2.OUT Signal
    Uint32 ECAP3_OUT  : 1; // 18 Input Flag for ECAP3.OUT Signal
    Uint32 ECAP4_OUT  : 1; // 19 Input Flag for ECAP4.OUT Signal
    Uint32 ECAP5_OUT  : 1; // 20 Input Flag for ECAP5.OUT Signal
    Uint32 ECAP6_OUT  : 1; // 21 Input Flag for ECAP6.OUT Signal
    Uint32 EXTSYNCOUT : 1; // 22 Input Flag for EXTSYNCOUT Signal
    Uint32 ADCAEVT1   : 1; // 23 Input Flag for ADCAEVT1 Signal
    Uint32 ADCAEVT2   : 1; // 24 Input Flag for ADCAEVT2 Signal
    Uint32 ADCAEVT3   : 1; // 25 Input Flag for ADCAEVT3 Signal
    Uint32 ADCAEVT4   : 1; // 26 Input Flag for ADCAEVT4 Signal
    Uint32 ADCBEVT1   : 1; // 27 Input Flag for ADCBEVT1 Signal
    Uint32 ADCBEVT2   : 1; // 28 Input Flag for ADCBEVT2 Signal
    Uint32 ADCBEVT3   : 1; // 29 Input Flag for ADCBEVT3 Signal
    Uint32 ADCBEVT4   : 1; // 30 Input Flag for ADCBEVT4 Signal
    Uint32 ADCCEVT1   : 1; // 31 Input Flag for ADCCEVT1 Signal
};

union XBARFLG2_REG
{
    Uint32 all;
    struct XBARFLG2_BITS bit;
};

struct XBARFLG3_BITS
{                             // bits description
    Uint32 ADCCEVT2      : 1; // 0 Input Flag for ADCCEVT2 Signal
    Uint32 ADCCEVT3      : 1; // 1 Input Flag for ADCCEVT3 Signal
    Uint32 ADCCEVT4      : 1; // 2 Input Flag for ADCCEVT4 Signal
    Uint32 rsvd1         : 1; // 3 Reserved
    Uint32 rsvd2         : 1; // 4 Reserved
    Uint32 rsvd3         : 1; // 5 Reserved
    Uint32 rsvd4         : 1; // 6 Reserved
    Uint32 SD1FLT1_COMPL : 1; // 7 Input Flag for SD1FLT1.COMPL Signal
    Uint32 SD1FLT1_COMPH : 1; // 8 Input Flag for SD1FLT1.COMPH Signal
    Uint32 SD1FLT2_COMPL : 1; // 9 Input Flag for SD1FLT2.COMPL Signal
    Uint32 SD1FLT2_COMPH : 1; // 10 Input Flag for SD1FLT2.COMPH Signal
    Uint32 SD1FLT3_COMPL : 1; // 11 Input Flag for SD1FLT3.COMPL Signal
    Uint32 SD1FLT3_COMPH : 1; // 12 Input Flag for SD1FLT3.COMPH Signal
    Uint32 SD1FLT4_COMPL : 1; // 13 Input Flag for SD1FLT4.COMPL Signal
    Uint32 SD1FLT4_COMPH : 1; // 14 Input Flag for SD1FLT4.COMPH Signal
    Uint32 rsvd5         : 8; // 15-22 Reserved
    Uint32 ECAP7_OUT     : 1; // 23 Input Flag for ECAP7.OUT Signal
    Uint32 SD1FLT1_COMPZ : 1; // 24 Input Flag for SD1FLT1.COMPZ Signal
    Uint32 SD1FLT1_DRINT : 1; // 25 Input Flag for SD1FLT1.DRINT Signal
    Uint32 SD1FLT2_COMPZ : 1; // 26 Input Flag for SD1FLT2.COMPZ Signal
    Uint32 SD1FLT2_DRINT : 1; // 27 Input Flag for SD1FLT2.DRINT Signal
    Uint32 SD1FLT3_COMPZ : 1; // 28 Input Flag for SD1FLT3.COMPZ Signal
    Uint32 SD1FLT3_DRINT : 1; // 29 Input Flag for SD1FLT3.DRINT Signal
    Uint32 SD1FLT4_COMPZ : 1; // 30 Input Flag for SD1FLT4.COMPZ Signal
    Uint32 SD1FLT4_DRINT : 1; // 31 Input Flag for SD1FLT4.DRINT Signal
};

union XBARFLG3_REG
{
    Uint32 all;
    struct XBARFLG3_BITS bit;
};

struct XBARFLG4_BITS
{                         // bits description
    Uint32 rsvd1    : 28; // 0-27  Reserved
    Uint32 ERRORSTS : 1;  // 28 Reserved
    Uint32 rsvd2    : 3;  // 31-29  Reserved
};

union XBARFLG4_REG
{
    Uint32 all;
    struct XBARFLG4_BITS bit;
};

struct XBARCLR1_BITS
{                                // bits description
    Uint32 CMPSS1_CTRIPL    : 1; // 0 Input Flag for CMPSS1.CTRIPL Signal
    Uint32 CMPSS1_CTRIPH    : 1; // 1 Input Flag for CMPSS1.CTRIPH Signal
    Uint32 CMPSS2_CTRIPL    : 1; // 2 Input Flag for CMPSS2.CTRIPL Signal
    Uint32 CMPSS2_CTRIPH    : 1; // 3 Input Flag for CMPSS2.CTRIPH Signal
    Uint32 CMPSS3_CTRIPL    : 1; // 4 Input Flag for CMPSS3.CTRIPL Signal
    Uint32 CMPSS3_CTRIPH    : 1; // 5 Input Flag for CMPSS3.CTRIPH Signal
    Uint32 CMPSS4_CTRIPL    : 1; // 6 Input Flag for CMPSS4.CTRIPL Signal
    Uint32 CMPSS4_CTRIPH    : 1; // 7 Input Flag for CMPSS4.CTRIPH Signal
    Uint32 CMPSS5_CTRIPL    : 1; // 8 Input Flag for CMPSS5.CTRIPL Signal
    Uint32 CMPSS5_CTRIPH    : 1; // 9 Input Flag for CMPSS5.CTRIPH Signal
    Uint32 CMPSS6_CTRIPL    : 1; // 10 Input Flag for CMPSS6.CTRIPL Signal
    Uint32 CMPSS6_CTRIPH    : 1; // 11 Input Flag for CMPSS6.CTRIPH Signal
    Uint32 CMPSS7_CTRIPL    : 1; // 12 Input Flag for CMPSS7.CTRIPL Signal
    Uint32 CMPSS7_CTRIPH    : 1; // 13 Input Flag for CMPSS7.CTRIPH Signal
    Uint32 rsvd1            : 2; // 14-15 Reserved
    Uint32 CMPSS1_CTRIPOUTL : 1; // 16 Input Flag for CMPSS1.CTRIPOUTL Signal
    Uint32 CMPSS1_CTRIPOUTH : 1; // 17 Input Flag for CMPSS1.CTRIPOUTH Signal
    Uint32 CMPSS2_CTRIPOUTL : 1; // 18 Input Flag for CMPSS2.CTRIPOUTL Signal
    Uint32 CMPSS2_CTRIPOUTH : 1; // 19 Input Flag for CMPSS2.CTRIPOUTH Signal
    Uint32 CMPSS3_CTRIPOUTL : 1; // 20 Input Flag for CMPSS3.CTRIPOUTL Signal
    Uint32 CMPSS3_CTRIPOUTH : 1; // 21 Input Flag for CMPSS3.CTRIPOUTH Signal
    Uint32 CMPSS4_CTRIPOUTL : 1; // 22 Input Flag for CMPSS4.CTRIPOUTL Signal
    Uint32 CMPSS4_CTRIPOUTH : 1; // 23 Input Flag for CMPSS4.CTRIPOUTH Signal
    Uint32 CMPSS5_CTRIPOUTL : 1; // 24 Input Flag for CMPSS5.CTRIPOUTL Signal
    Uint32 CMPSS5_CTRIPOUTH : 1; // 25 Input Flag for CMPSS5.CTRIPOUTH Signal
    Uint32 CMPSS6_CTRIPOUTL : 1; // 26 Input Flag for CMPSS6.CTRIPOUTL Signal
    Uint32 CMPSS6_CTRIPOUTH : 1; // 27 Input Flag for CMPSS6.CTRIPOUTH Signal
    Uint32 CMPSS7_CTRIPOUTL : 1; // 28 Input Flag for CMPSS7.CTRIPOUTL Signal
    Uint32 CMPSS7_CTRIPOUTH : 1; // 29 Input Flag for CMPSS7.CTRIPOUTH Signal
    Uint32 rsvd2            : 2; // 30-31 Reserved
};

union XBARCLR1_REG
{
    Uint32 all;
    struct XBARCLR1_BITS bit;
};

struct XBARCLR2_BITS
{                          // bits description
    Uint32 INPUT1     : 1; // 0 Input Flag Clear for INPUT1 Signal
    Uint32 INPUT2     : 1; // 1 Input Flag Clear for INPUT2 Signal
    Uint32 INPUT3     : 1; // 2 Input Flag Clear for INPUT3 Signal
    Uint32 INPUT4     : 1; // 3 Input Flag Clear for INPUT4 Signal
    Uint32 INPUT5     : 1; // 4 Input Flag Clear for INPUT5 Signal
    Uint32 INPUT6     : 1; // 5 Input Flag Clear for INPUT6 Signal
    Uint32 ADCSOCA    : 1; // 6 Input Flag Clear for ADCSOCA Signal
    Uint32 ADCSOCB    : 1; // 7 Input Flag Clear for ADCSOCB Signal
    Uint32 INPUT7     : 1; // 8 Input Flag Clear for INPUT7 Signal
    Uint32 INPUT8     : 1; // 9 Input Flag Clear for INPUT8 Signal
    Uint32 INPUT9     : 1; // 10 Input Flag Clear for INPUT9 Signal
    Uint32 INPUT10    : 1; // 11 Input Flag Clear for INPUT10 Signal
    Uint32 INPUT11    : 1; // 12 Input Flag Clear for INPUT11 Signal
    Uint32 INPUT12    : 1; // 13 Input Flag Clear for INPUT12 Signal
    Uint32 INPUT13    : 1; // 14 Input Flag Clear for INPUT13 Signal
    Uint32 INPUT14    : 1; // 15 Input Flag Clear for INPUT14 Signal
    Uint32 ECAP1_OUT  : 1; // 16 Input Flag Clear for ECAP1.OUT Signal
    Uint32 ECAP2_OUT  : 1; // 17 Input Flag Clear for ECAP2.OUT Signal
    Uint32 ECAP3_OUT  : 1; // 18 Input Flag Clear for ECAP3.OUT Signal
    Uint32 ECAP4_OUT  : 1; // 19 Input Flag Clear for ECAP4.OUT Signal
    Uint32 ECAP5_OUT  : 1; // 20 Input Flag Clear for ECAP5.OUT Signal
    Uint32 ECAP6_OUT  : 1; // 21 Input Flag Clear for ECAP6.OUT Signal
    Uint32 EXTSYNCOUT : 1; // 22 Input Flag Clear for EXTSYNCOUT Signal
    Uint32 ADCAEVT1   : 1; // 23 Input Flag Clear for ADCAEVT1 Signal
    Uint32 ADCAEVT2   : 1; // 24 Input Flag Clear for ADCAEVT2 Signal
    Uint32 ADCAEVT3   : 1; // 25 Input Flag Clear for ADCAEVT3 Signal
    Uint32 ADCAEVT4   : 1; // 26 Input Flag Clear for ADCAEVT4 Signal
    Uint32 ADCBEVT1   : 1; // 27 Input Flag Clear for ADCBEVT1 Signal
    Uint32 ADCBEVT2   : 1; // 28 Input Flag Clear for ADCBEVT2 Signal
    Uint32 ADCBEVT3   : 1; // 29 Input Flag Clear for ADCBEVT3 Signal
    Uint32 ADCBEVT4   : 1; // 30 Input Flag Clear for ADCBEVT4 Signal
    Uint32 ADCCEVT1   : 1; // 31 Input Flag Clear for ADCCEVT1 Signal
};

union XBARCLR2_REG
{
    Uint32 all;
    struct XBARCLR2_BITS bit;
};

struct XBARCLR3_BITS
{                             // bits description
    Uint32 ADCCEVT2      : 1; // 0 Input Flag Clear for ADCCEVT2 Signal
    Uint32 ADCCEVT3      : 1; // 1 Input Flag Clear for ADCCEVT3 Signal
    Uint32 ADCCEVT4      : 1; // 2 Input Flag Clear for ADCCEVT4 Signal
    Uint32 rsvd1         : 1; // 3 Reserved
    Uint32 rsvd2         : 1; // 4 Reserved
    Uint32 rsvd3         : 1; // 5 Reserved
    Uint32 rsvd4         : 1; // 6 Reserved
    Uint32 SD1FLT1_COMPL : 1; // 7 Input Flag Clear for SD1FLT1.COMPL Signal
    Uint32 SD1FLT1_COMPH : 1; // 8 Input Flag Clear for SD1FLT1.COMPH Signal
    Uint32 SD1FLT2_COMPL : 1; // 9 Input Flag Clear for SD1FLT2.COMPL Signal
    Uint32 SD1FLT2_COMPH : 1; // 10 Input Flag Clear for SD1FLT2.COMPH Signal
    Uint32 SD1FLT3_COMPL : 1; // 11 Input Flag Clear for SD1FLT3.COMPL Signal
    Uint32 SD1FLT3_COMPH : 1; // 12 Input Flag Clear for SD1FLT3.COMPH Signal
    Uint32 SD1FLT4_COMPL : 1; // 13 Input Flag Clear for SD1FLT4.COMPL Signal
    Uint32 SD1FLT4_COMPH : 1; // 14 Input Flag Clear for SD1FLT4.COMPH Signal
    Uint32 rsvd5         : 8; // 15-22 Reserved
    Uint32 ECAP7_OUT     : 1; // 23 Input Flag clear for ECAP7.OUT Signal
    Uint32 SD1FLT1_COMPZ : 1; // 24 Input Flag clear for SD1FLT1.COMPZ Signal
    Uint32 SD1FLT1_DRINT : 1; // 25 Input Flag clear for SD1FLT1.DRINT Signal
    Uint32 SD1FLT2_COMPZ : 1; // 26 Input Flag clear for SD1FLT2.COMPZ Signal
    Uint32 SD1FLT2_DRINT : 1; // 27 Input Flag clear for SD1FLT2.DRINT Signal
    Uint32 SD1FLT3_COMPZ : 1; // 28 Input Flag clear for SD1FLT3.COMPZ Signal
    Uint32 SD1FLT3_DRINT : 1; // 29 Input Flag clear for SD1FLT3.DRINT Signal
    Uint32 SD1FLT4_COMPZ : 1; // 30 Input Flag clear for SD1FLT4.COMPZ Signal
    Uint32 SD1FLT4_DRINT : 1; // 31 Input Flag clear for SD1FLT4.DRINT Signal
};

union XBARCLR3_REG
{
    Uint32 all;
    struct XBARCLR3_BITS bit;
};

struct XBARCLR4_BITS
{                         // bits description
    Uint32 rsvd1    : 28; // 0-27  Reserved
    Uint32 ERRORSTS : 1;  // 28 Reserved
    Uint32 rsvd2    : 3;  // 31-29  Reserved
};

union XBARCLR4_REG
{
    Uint32 all;
    struct XBARCLR4_BITS bit;
};

struct XBAR_REGS
{
    union XBARFLG1_REG XBARFLG1; // X-Bar Input Flag Register 1
    union XBARFLG2_REG XBARFLG2; // X-Bar Input Flag Register 2
    union XBARFLG3_REG XBARFLG3; // X-Bar Input Flag Register 3
    union XBARFLG4_REG XBARFLG4; // X-Bar Input Flag Register 4
    union XBARCLR1_REG XBARCLR1; // X-Bar Input Flag Clear Register 1
    union XBARCLR2_REG XBARCLR2; // X-Bar Input Flag Clear Register 2
    union XBARCLR3_REG XBARCLR3; // X-Bar Input Flag Clear Register 3
    union XBARCLR4_REG XBARCLR4; // X-Bar Input Flag Clear Register 4
};

//---------------------------------------------------------------------------
// XBAR External References & Function Declarations:
//
extern volatile struct XBAR_REGS XbarRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
