#ifndef F28004X_ADC_H
#define F28004X_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// ADC Individual Register Bit Definitions:

struct ADCCTL1_BITS
{                           // bits description
    Uint32 SELDO_HS_LU : 1; // 0
    Uint32 SELVI_HD_LS : 1; // 1
    Uint32 INTPULSEPOS : 1; // 2 ADC Interrupt Pulse Position
    Uint32 rsvd1       : 1; // 3 enldo
    Uint32 BIAS_C      : 3; // 6:4 bias_c
    Uint32 ADCPWDNZ    : 1; // 7 resetz_p
    Uint32 ADCBSYCHN   : 5; // 12:8 ADC Busy Channel
    Uint32 ADCBSY      : 1; // 13 ADC Busy
    Uint32 MD_ADC      : 2; // 15:14 selrange_ldo
    Uint32 CLK_DLY_SEL : 2; // 17:16 startvoscal_p
    Uint32 rsvd5       : 1; // 16 power gate
};

union ADCCTL1_REG
{
    Uint32 all;
    struct ADCCTL1_BITS bit;
};

struct ADCCTL2_BITS
{                         // bits description
    Uint32 PRESCALE : 5;  // 4:0 ADC Clock Prescaler
    Uint32 rsvd1    : 1;  // 5 Reserved
    Uint32 rsvd2    : 1;  // 6 Reserved
    Uint32 rsvd3    : 1;  // 7 Reserved
    Uint32 rsvd4    : 4;  // 12:8 Reserved
    Uint32 rsvd5    : 3;  // 15:13 Reserved
    Uint32 rsvd6    : 16; // 31:16 Reserved
};

union ADCCTL2_REG
{
    Uint32 all;
    struct ADCCTL2_BITS bit;
};

struct ADCBURSTCTL_BITS
{                             // bits description
    Uint32 BURSTTRIGSEL : 6;  // 5:0 SOC Burst Trigger Source Select
    Uint32 rsvd1        : 2;  // 7:6 Reserved
    Uint32 BURSTSIZE    : 4;  // 11:8 SOC Burst Size Select
    Uint32 rsvd2        : 3;  // 14:12 Reserved
    Uint32 BURSTEN      : 1;  // 15 SOC Burst Mode Enable
    Uint32 rsvd3        : 16; // 31:16 Reserved
};

union ADCBURSTCTL_REG
{
    Uint32 all;
    struct ADCBURSTCTL_BITS bit;
};

struct ADCINTFLG_BITS
{                        // bits description
    Uint32 ADCINT1 : 1;  // 0 ADC Interrupt 1 Flag
    Uint32 ADCINT2 : 1;  // 1 ADC Interrupt 2 Flag
    Uint32 ADCINT3 : 1;  // 2 ADC Interrupt 3 Flag
    Uint32 ADCINT4 : 1;  // 3 ADC Interrupt 4 Flag
    Uint32 rsvd1   : 12; // 15:4 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union ADCINTFLG_REG
{
    Uint32 all;
    struct ADCINTFLG_BITS bit;
};

struct ADCINTFLGCLR_BITS
{                        // bits description
    Uint32 ADCINT1 : 1;  // 0 ADC Interrupt 1 Flag Clear
    Uint32 ADCINT2 : 1;  // 1 ADC Interrupt 2 Flag Clear
    Uint32 ADCINT3 : 1;  // 2 ADC Interrupt 3 Flag Clear
    Uint32 ADCINT4 : 1;  // 3 ADC Interrupt 4 Flag Clear
    Uint32 rsvd1   : 12; // 15:4 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union ADCINTFLGCLR_REG
{
    Uint32 all;
    struct ADCINTFLGCLR_BITS bit;
};

struct ADCINTOVF_BITS
{                        // bits description
    Uint32 ADCINT1 : 1;  // 0 ADC Interrupt 1 Overflow Flags
    Uint32 ADCINT2 : 1;  // 1 ADC Interrupt 2 Overflow Flags
    Uint32 ADCINT3 : 1;  // 2 ADC Interrupt 3 Overflow Flags
    Uint32 ADCINT4 : 1;  // 3 ADC Interrupt 4 Overflow Flags
    Uint32 rsvd1   : 12; // 15:4 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union ADCINTOVF_REG
{
    Uint32 all;
    struct ADCINTOVF_BITS bit;
};

struct ADCINTOVFCLR_BITS
{                        // bits description
    Uint32 ADCINT1 : 1;  // 0 ADC Interrupt 1 Overflow Clear Bits
    Uint32 ADCINT2 : 1;  // 1 ADC Interrupt 2 Overflow Clear Bits
    Uint32 ADCINT3 : 1;  // 2 ADC Interrupt 3 Overflow Clear Bits
    Uint32 ADCINT4 : 1;  // 3 ADC Interrupt 4 Overflow Clear Bits
    Uint32 rsvd1   : 12; // 15:4 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union ADCINTOVFCLR_REG
{
    Uint32 all;
    struct ADCINTOVFCLR_BITS bit;
};

struct ADCINTSEL1N2_BITS
{                         // bits description
    Uint32 INT1SEL  : 5;  // 4:0 ADCINT1 EOC Source Select
    Uint32 INT1E    : 1;  // 5 ADCINT1 Interrupt Enable
    Uint32 INT1CONT : 1;  // 6 ADCINT1 Continue to Interrupt Mode
    Uint32 rsvd1    : 1;  // 7 Reserved
    Uint32 INT2SEL  : 5;  // 12:8 ADCINT2 EOC Source Select
    Uint32 INT2E    : 1;  // 13 ADCINT2 Interrupt Enable
    Uint32 INT2CONT : 1;  // 14 ADCINT2 Continue to Interrupt Mode
    Uint32 rsvd2    : 1;  // 15 Reserved
    Uint32 rsvd3    : 16; // 31:16 Reserved
};

union ADCINTSEL1N2_REG
{
    Uint32 all;
    struct ADCINTSEL1N2_BITS bit;
};

struct ADCINTSEL3N4_BITS
{                         // bits description
    Uint32 INT3SEL  : 5;  // 4:0 ADCINT3 EOC Source Select
    Uint32 INT3E    : 1;  // 5 ADCINT3 Interrupt Enable
    Uint32 INT3CONT : 1;  // 6 ADCINT3 Continue to Interrupt Mode
    Uint32 rsvd1    : 1;  // 7 Reserved
    Uint32 INT4SEL  : 5;  // 12:8 ADCINT4 EOC Source Select
    Uint32 INT4E    : 1;  // 13 ADCINT4 Interrupt Enable
    Uint32 INT4CONT : 1;  // 14 ADCINT4 Continue to Interrupt Mode
    Uint32 rsvd2    : 1;  // 15 Reserved
    Uint32 rsvd3    : 16; // 31:16 Reserved
};

union ADCINTSEL3N4_REG
{
    Uint32 all;
    struct ADCINTSEL3N4_BITS bit;
};

struct ADCSOCPRICTL_BITS
{                            // bits description
    Uint32 SOCPRIORITY : 5;  // 4:0 SOC Priority
    Uint32 RRPOINTER   : 5;  // 9:5 Round Robin Pointer
    Uint32 rsvd1       : 6;  // 15:10 Reserved
    Uint32 rsvd2       : 16; // 31:16 Reserved
};

union ADCSOCPRICTL_REG
{
    Uint32 all;
    struct ADCSOCPRICTL_BITS bit;
};

struct ADCINTSOCSEL1_BITS
{                      // bits description
    Uint32 SOC0  : 2;  // 1:0 SOC0 ADC Interrupt Trigger Select
    Uint32 SOC1  : 2;  // 3:2 SOC1 ADC Interrupt Trigger Select
    Uint32 SOC2  : 2;  // 5:4 SOC2 ADC Interrupt Trigger Select
    Uint32 SOC3  : 2;  // 7:6 SOC3 ADC Interrupt Trigger Select
    Uint32 SOC4  : 2;  // 9:8 SOC4 ADC Interrupt Trigger Select
    Uint32 SOC5  : 2;  // 11:10 SOC5 ADC Interrupt Trigger Select
    Uint32 SOC6  : 2;  // 13:12 SOC6 ADC Interrupt Trigger Select
    Uint32 SOC7  : 2;  // 15:14 SOC7 ADC Interrupt Trigger Select
    Uint32 rsvd1 : 16; // 31:16 Reserved
};

union ADCINTSOCSEL1_REG
{
    Uint32 all;
    struct ADCINTSOCSEL1_BITS bit;
};

struct ADCINTSOCSEL2_BITS
{                      // bits description
    Uint32 SOC8  : 2;  // 1:0 SOC8 ADC Interrupt Trigger Select
    Uint32 SOC9  : 2;  // 3:2 SOC9 ADC Interrupt Trigger Select
    Uint32 SOC10 : 2;  // 5:4 SOC10 ADC Interrupt Trigger Select
    Uint32 SOC11 : 2;  // 7:6 SOC11 ADC Interrupt Trigger Select
    Uint32 SOC12 : 2;  // 9:8 SOC12 ADC Interrupt Trigger Select
    Uint32 SOC13 : 2;  // 11:10 SOC13 ADC Interrupt Trigger Select
    Uint32 SOC14 : 2;  // 13:12 SOC14 ADC Interrupt Trigger Select
    Uint32 SOC15 : 2;  // 15:14 SOC15 ADC Interrupt Trigger Select
    Uint32 rsvd1 : 16; // 31:16 Reserved
};

union ADCINTSOCSEL2_REG
{
    Uint32 all;
    struct ADCINTSOCSEL2_BITS bit;
};

struct ADCSOCFLG1_BITS
{                      // bits description
    Uint32 SOC0  : 1;  // 0 SOC0 Start of Conversion Flag
    Uint32 SOC1  : 1;  // 1 SOC1 Start of Conversion Flag
    Uint32 SOC2  : 1;  // 2 SOC2 Start of Conversion Flag
    Uint32 SOC3  : 1;  // 3 SOC3 Start of Conversion Flag
    Uint32 SOC4  : 1;  // 4 SOC4 Start of Conversion Flag
    Uint32 SOC5  : 1;  // 5 SOC5 Start of Conversion Flag
    Uint32 SOC6  : 1;  // 6 SOC6 Start of Conversion Flag
    Uint32 SOC7  : 1;  // 7 SOC7 Start of Conversion Flag
    Uint32 SOC8  : 1;  // 8 SOC8 Start of Conversion Flag
    Uint32 SOC9  : 1;  // 9 SOC9 Start of Conversion Flag
    Uint32 SOC10 : 1;  // 10 SOC10 Start of Conversion Flag
    Uint32 SOC11 : 1;  // 11 SOC11 Start of Conversion Flag
    Uint32 SOC12 : 1;  // 12 SOC12 Start of Conversion Flag
    Uint32 SOC13 : 1;  // 13 SOC13 Start of Conversion Flag
    Uint32 SOC14 : 1;  // 14 SOC14 Start of Conversion Flag
    Uint32 SOC15 : 1;  // 15 SOC15 Start of Conversion Flag
    Uint32 rsvd1 : 16; // 31:16 Reserved
};

union ADCSOCFLG1_REG
{
    Uint32 all;
    struct ADCSOCFLG1_BITS bit;
};

struct ADCSOCFRC1_BITS
{                      // bits description
    Uint32 SOC0  : 1;  // 0 SOC0 Force Start of Conversion Bit
    Uint32 SOC1  : 1;  // 1 SOC1 Force Start of Conversion Bit
    Uint32 SOC2  : 1;  // 2 SOC2 Force Start of Conversion Bit
    Uint32 SOC3  : 1;  // 3 SOC3 Force Start of Conversion Bit
    Uint32 SOC4  : 1;  // 4 SOC4 Force Start of Conversion Bit
    Uint32 SOC5  : 1;  // 5 SOC5 Force Start of Conversion Bit
    Uint32 SOC6  : 1;  // 6 SOC6 Force Start of Conversion Bit
    Uint32 SOC7  : 1;  // 7 SOC7 Force Start of Conversion Bit
    Uint32 SOC8  : 1;  // 8 SOC8 Force Start of Conversion Bit
    Uint32 SOC9  : 1;  // 9 SOC9 Force Start of Conversion Bit
    Uint32 SOC10 : 1;  // 10 SOC10 Force Start of Conversion Bit
    Uint32 SOC11 : 1;  // 11 SOC11 Force Start of Conversion Bit
    Uint32 SOC12 : 1;  // 12 SOC12 Force Start of Conversion Bit
    Uint32 SOC13 : 1;  // 13 SOC13 Force Start of Conversion Bit
    Uint32 SOC14 : 1;  // 14 SOC14 Force Start of Conversion Bit
    Uint32 SOC15 : 1;  // 15 SOC15 Force Start of Conversion Bit
    Uint32 rsvd1 : 16; // 31:16 Reserved
};

union ADCSOCFRC1_REG
{
    Uint32 all;
    struct ADCSOCFRC1_BITS bit;
};

struct ADCSOCOVF1_BITS
{                      // bits description
    Uint32 SOC0  : 1;  // 0 SOC0 Start of Conversion Overflow Flag
    Uint32 SOC1  : 1;  // 1 SOC1 Start of Conversion Overflow Flag
    Uint32 SOC2  : 1;  // 2 SOC2 Start of Conversion Overflow Flag
    Uint32 SOC3  : 1;  // 3 SOC3 Start of Conversion Overflow Flag
    Uint32 SOC4  : 1;  // 4 SOC4 Start of Conversion Overflow Flag
    Uint32 SOC5  : 1;  // 5 SOC5 Start of Conversion Overflow Flag
    Uint32 SOC6  : 1;  // 6 SOC6 Start of Conversion Overflow Flag
    Uint32 SOC7  : 1;  // 7 SOC7 Start of Conversion Overflow Flag
    Uint32 SOC8  : 1;  // 8 SOC8 Start of Conversion Overflow Flag
    Uint32 SOC9  : 1;  // 9 SOC9 Start of Conversion Overflow Flag
    Uint32 SOC10 : 1;  // 10 SOC10 Start of Conversion Overflow Flag
    Uint32 SOC11 : 1;  // 11 SOC11 Start of Conversion Overflow Flag
    Uint32 SOC12 : 1;  // 12 SOC12 Start of Conversion Overflow Flag
    Uint32 SOC13 : 1;  // 13 SOC13 Start of Conversion Overflow Flag
    Uint32 SOC14 : 1;  // 14 SOC14 Start of Conversion Overflow Flag
    Uint32 SOC15 : 1;  // 15 SOC15 Start of Conversion Overflow Flag
    Uint32 rsvd1 : 16; // 31:16 Reserved
};

union ADCSOCOVF1_REG
{
    Uint32 all;
    struct ADCSOCOVF1_BITS bit;
};

struct ADCSOCOVFCLR1_BITS
{                      // bits description
    Uint32 SOC0  : 1;  // 0 SOC0 Clear Start of Conversion Overflow Bit
    Uint32 SOC1  : 1;  // 1 SOC1 Clear Start of Conversion Overflow Bit
    Uint32 SOC2  : 1;  // 2 SOC2 Clear Start of Conversion Overflow Bit
    Uint32 SOC3  : 1;  // 3 SOC3 Clear Start of Conversion Overflow Bit
    Uint32 SOC4  : 1;  // 4 SOC4 Clear Start of Conversion Overflow Bit
    Uint32 SOC5  : 1;  // 5 SOC5 Clear Start of Conversion Overflow Bit
    Uint32 SOC6  : 1;  // 6 SOC6 Clear Start of Conversion Overflow Bit
    Uint32 SOC7  : 1;  // 7 SOC7 Clear Start of Conversion Overflow Bit
    Uint32 SOC8  : 1;  // 8 SOC8 Clear Start of Conversion Overflow Bit
    Uint32 SOC9  : 1;  // 9 SOC9 Clear Start of Conversion Overflow Bit
    Uint32 SOC10 : 1;  // 10 SOC10 Clear Start of Conversion Overflow Bit
    Uint32 SOC11 : 1;  // 11 SOC11 Clear Start of Conversion Overflow Bit
    Uint32 SOC12 : 1;  // 12 SOC12 Clear Start of Conversion Overflow Bit
    Uint32 SOC13 : 1;  // 13 SOC13 Clear Start of Conversion Overflow Bit
    Uint32 SOC14 : 1;  // 14 SOC14 Clear Start of Conversion Overflow Bit
    Uint32 SOC15 : 1;  // 15 SOC15 Clear Start of Conversion Overflow Bit
    Uint32 rsvd1 : 16; // 31:16 Reserved
};

union ADCSOCOVFCLR1_REG
{
    Uint32 all;
    struct ADCSOCOVFCLR1_BITS bit;
};

struct ADCSOC0CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC0 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC0 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC0 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC0CTL_REG
{
    Uint32 all;
    struct ADCSOC0CTL_BITS bit;
};

struct ADCSOC1CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC1 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC1 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC1 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC1CTL_REG
{
    Uint32 all;
    struct ADCSOC1CTL_BITS bit;
};

struct ADCSOC2CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC2 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC2 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC2 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC2CTL_REG
{
    Uint32 all;
    struct ADCSOC2CTL_BITS bit;
};

struct ADCSOC3CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC3 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC3 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC3 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC3CTL_REG
{
    Uint32 all;
    struct ADCSOC3CTL_BITS bit;
};

struct ADCSOC4CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC4 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC4 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC4 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC4CTL_REG
{
    Uint32 all;
    struct ADCSOC4CTL_BITS bit;
};

struct ADCSOC5CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC5 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC5 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC5 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC5CTL_REG
{
    Uint32 all;
    struct ADCSOC5CTL_BITS bit;
};

struct ADCSOC6CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC6 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC6 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC6 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC6CTL_REG
{
    Uint32 all;
    struct ADCSOC6CTL_BITS bit;
};

struct ADCSOC7CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC7 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC7 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC7 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC7CTL_REG
{
    Uint32 all;
    struct ADCSOC7CTL_BITS bit;
};

struct ADCSOC8CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC8 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC8 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC8 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC8CTL_REG
{
    Uint32 all;
    struct ADCSOC8CTL_BITS bit;
};

struct ADCSOC9CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC9 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC9 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC9 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC9CTL_REG
{
    Uint32 all;
    struct ADCSOC9CTL_BITS bit;
};

struct ADCSOC10CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC10 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC10 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC10 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC10CTL_REG
{
    Uint32 all;
    struct ADCSOC10CTL_BITS bit;
};

struct ADCSOC11CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC11 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC11 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC11 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC11CTL_REG
{
    Uint32 all;
    struct ADCSOC11CTL_BITS bit;
};

struct ADCSOC12CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC12 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC12 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC12 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC12CTL_REG
{
    Uint32 all;
    struct ADCSOC12CTL_BITS bit;
};

struct ADCSOC13CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC13 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC13 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC13 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC13CTL_REG
{
    Uint32 all;
    struct ADCSOC13CTL_BITS bit;
};

struct ADCSOC14CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC14 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC14 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC14 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC14CTL_REG
{
    Uint32 all;
    struct ADCSOC14CTL_BITS bit;
};

struct ADCSOC15CTL_BITS
{                       // bits description
    Uint32 ACQPS   : 9; // 8:0 SOC15 Acquisition Prescale
    Uint32 rsvd1   : 1; // 9 Reserved
    Uint32 rsvd2   : 2; // 11:10 Reserved
    Uint32 rsvd3   : 3; // 14:12 Reserved
    Uint32 CHSEL   : 5; // 19:15 SOC15 Channel Select
    Uint32 TRIGSEL : 7; // 26:20 SOC15 Trigger Source Select
    Uint32 rsvd4   : 1; // 27 Reserved
    Uint32 rsvd5   : 4; // 31:28 Reserved
};

union ADCSOC15CTL_REG
{
    Uint32 all;
    struct ADCSOC15CTL_BITS bit;
};

struct ADCEVTSTAT_BITS
{                           // bits description
    Uint32 PPB1TRIPHI : 1;  // 0 Post Processing Block 1 Trip High Flag
    Uint32 PPB1TRIPLO : 1;  // 1 Post Processing Block 1 Trip Low Flag
    Uint32 PPB1ZERO   : 1;  // 2 Post Processing Block 1 Zero Crossing Flag
    Uint32 rsvd1      : 1;  // 3 Reserved
    Uint32 PPB2TRIPHI : 1;  // 4 Post Processing Block 2 Trip High Flag
    Uint32 PPB2TRIPLO : 1;  // 5 Post Processing Block 2 Trip Low Flag
    Uint32 PPB2ZERO   : 1;  // 6 Post Processing Block 2 Zero Crossing Flag
    Uint32 rsvd2      : 1;  // 7 Reserved
    Uint32 PPB3TRIPHI : 1;  // 8 Post Processing Block 3 Trip High Flag
    Uint32 PPB3TRIPLO : 1;  // 9 Post Processing Block 3 Trip Low Flag
    Uint32 PPB3ZERO   : 1;  // 10 Post Processing Block 3 Zero Crossing Flag
    Uint32 rsvd3      : 1;  // 11 Reserved
    Uint32 PPB4TRIPHI : 1;  // 12 Post Processing Block 4 Trip High Flag
    Uint32 PPB4TRIPLO : 1;  // 13 Post Processing Block 4 Trip Low Flag
    Uint32 PPB4ZERO   : 1;  // 14 Post Processing Block 4 Zero Crossing Flag
    Uint32 rsvd4      : 1;  // 15 Reserved
    Uint32 rsvd5      : 16; // 31:16 Reserved
};

union ADCEVTSTAT_REG
{
    Uint32 all;
    struct ADCEVTSTAT_BITS bit;
};

struct ADCEVTCLR_BITS
{                           // bits description
    Uint32 PPB1TRIPHI : 1;  // 0 Post Processing Block 1 Trip High Clear
    Uint32 PPB1TRIPLO : 1;  // 1 Post Processing Block 1 Trip Low Clear
    Uint32 PPB1ZERO   : 1;  // 2 Post Processing Block 1 Zero Crossing Clear
    Uint32 rsvd1      : 1;  // 3 Reserved
    Uint32 PPB2TRIPHI : 1;  // 4 Post Processing Block 2 Trip High Clear
    Uint32 PPB2TRIPLO : 1;  // 5 Post Processing Block 2 Trip Low Clear
    Uint32 PPB2ZERO   : 1;  // 6 Post Processing Block 2 Zero Crossing Clear
    Uint32 rsvd2      : 1;  // 7 Reserved
    Uint32 PPB3TRIPHI : 1;  // 8 Post Processing Block 3 Trip High Clear
    Uint32 PPB3TRIPLO : 1;  // 9 Post Processing Block 3 Trip Low Clear
    Uint32 PPB3ZERO   : 1;  // 10 Post Processing Block 3 Zero Crossing Clear
    Uint32 rsvd3      : 1;  // 11 Reserved
    Uint32 PPB4TRIPHI : 1;  // 12 Post Processing Block 4 Trip High Clear
    Uint32 PPB4TRIPLO : 1;  // 13 Post Processing Block 4 Trip Low Clear
    Uint32 PPB4ZERO   : 1;  // 14 Post Processing Block 4 Zero Crossing Clear
    Uint32 rsvd4      : 1;  // 15 Reserved
    Uint32 rsvd5      : 16; // 31:16 Reserved
};

union ADCEVTCLR_REG
{
    Uint32 all;
    struct ADCEVTCLR_BITS bit;
};

struct ADCEVTSEL_BITS
{                           // bits description
    Uint32 PPB1TRIPHI : 1;  // 0 Post Processing Block 1 Trip High Event Enable
    Uint32 PPB1TRIPLO : 1;  // 1 Post Processing Block 1 Trip Low Event Enable
    Uint32 PPB1ZERO   : 1;  // 2 Post Processing Block 1 Zero Crossing Event Enable
    Uint32 rsvd1      : 1;  // 3 Reserved
    Uint32 PPB2TRIPHI : 1;  // 4 Post Processing Block 2 Trip High Event Enable
    Uint32 PPB2TRIPLO : 1;  // 5 Post Processing Block 2 Trip Low Event Enable
    Uint32 PPB2ZERO   : 1;  // 6 Post Processing Block 2 Zero Crossing Event Enable
    Uint32 rsvd2      : 1;  // 7 Reserved
    Uint32 PPB3TRIPHI : 1;  // 8 Post Processing Block 3 Trip High Event Enable
    Uint32 PPB3TRIPLO : 1;  // 9 Post Processing Block 3 Trip Low Event Enable
    Uint32 PPB3ZERO   : 1;  // 10 Post Processing Block 3 Zero Crossing Event Enable
    Uint32 rsvd3      : 1;  // 11 Reserved
    Uint32 PPB4TRIPHI : 1;  // 12 Post Processing Block 4 Trip High Event Enable
    Uint32 PPB4TRIPLO : 1;  // 13 Post Processing Block 4 Trip Low Event Enable
    Uint32 PPB4ZERO   : 1;  // 14 Post Processing Block 4 Zero Crossing Event Enable
    Uint32 rsvd4      : 1;  // 15 Reserved
    Uint32 rsvd5      : 16; // 31:16 Reserved
};

union ADCEVTSEL_REG
{
    Uint32 all;
    struct ADCEVTSEL_BITS bit;
};

struct ADCEVTINTSEL_BITS
{                           // bits description
    Uint32 PPB1TRIPHI : 1;  // 0 Post Processing Block 1 Trip High Interrupt Enable
    Uint32 PPB1TRIPLO : 1;  // 1 Post Processing Block 1 Trip Low Interrupt Enable
    Uint32 PPB1ZERO   : 1;  // 2 Post Processing Block 1 Zero Crossing Interrupt Enable
    Uint32 rsvd1      : 1;  // 3 Reserved
    Uint32 PPB2TRIPHI : 1;  // 4 Post Processing Block 2 Trip High Interrupt Enable
    Uint32 PPB2TRIPLO : 1;  // 5 Post Processing Block 2 Trip Low Interrupt Enable
    Uint32 PPB2ZERO   : 1;  // 6 Post Processing Block 2 Zero Crossing Interrupt Enable
    Uint32 rsvd2      : 1;  // 7 Reserved
    Uint32 PPB3TRIPHI : 1;  // 8 Post Processing Block 3 Trip High Interrupt Enable
    Uint32 PPB3TRIPLO : 1;  // 9 Post Processing Block 3 Trip Low Interrupt Enable
    Uint32 PPB3ZERO   : 1;  // 10 Post Processing Block 3 Zero Crossing Interrupt Enable
    Uint32 rsvd3      : 1;  // 11 Reserved
    Uint32 PPB4TRIPHI : 1;  // 12 Post Processing Block 4 Trip High Interrupt Enable
    Uint32 PPB4TRIPLO : 1;  // 13 Post Processing Block 4 Trip Low Interrupt Enable
    Uint32 PPB4ZERO   : 1;  // 14 Post Processing Block 4 Zero Crossing Interrupt Enable
    Uint32 rsvd4      : 1;  // 15 Reserved
    Uint32 rsvd5      : 16; // 31:16 Reserved
};

union ADCEVTINTSEL_REG
{
    Uint32 all;
    struct ADCEVTINTSEL_BITS bit;
};

struct ADCOSDETECT_BITS
{                          // bits description
    Uint32 DETECTCFG : 3;  // 2:0 ADC Opens and Shorts Detect Configuration
    Uint32 rsvd1     : 13; // 15:3 Reserved
    Uint32 rsvd2     : 16; // 31:16 Reserved
};

union ADCOSDETECT_REG
{
    Uint32 all;
    struct ADCOSDETECT_BITS bit;
};

struct ADCCOUNTER_BITS
{                          // bits description
    Uint32 FREECOUNT : 12; // 11:0 ADC Free Running Counter Value
    Uint32 rsvd1     : 4;  // 15:12 Reserved
    Uint32 rsvd2     : 16; // 31:16 Reserved
};

union ADCCOUNTER_REG
{
    Uint32 all;
    struct ADCCOUNTER_BITS bit;
};

struct ADCREV_BITS
{                      // bits description
    Uint32 TYPE  : 8;  // 7:0 ADC Type
    Uint32 REV   : 8;  // 15:8 ADC Revision
    Uint32 rsvd1 : 16; // 31:16 Reserved
};

union ADCREV_REG
{
    Uint32 all;
    struct ADCREV_BITS bit;
};

struct ADCPPB1CONFIG_BITS
{                           // bits description
    Uint32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 1 Configuration
    Uint32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 1 Two's Complement Enable
    Uint32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    Uint32 rsvd1      : 25; // 31:7 Reserved
};

union ADCPPB1CONFIG_REG
{
    Uint32 all;
    struct ADCPPB1CONFIG_BITS bit;
};

struct ADCPPB1STAMP_BITS
{                         // bits description
    Uint32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 1 Delay Time Stamp
    Uint32 rsvd1    : 4;  // 15:12 Reserved
    Uint32 rsvd2    : 16; // 31:16 Reserved
};

union ADCPPB1STAMP_REG
{
    Uint32 all;
    struct ADCPPB1STAMP_BITS bit;
};

struct ADCPPB1OFFREF_BITS
{                       // bits description
    Uint32 OFFREF : 12; // 11:0 ADC Post Processing Block offset correction
    Uint32 rsvd1  : 4;  // 15:12 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union ADCPPB1OFFREF_REG
{
    Uint32 all;
    struct ADCPPB1OFFREF_BITS bit;
};

struct ADCPPB1OFFCAL_BITS
{                       // bits description
    Uint32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    Uint32 rsvd1  : 6;  // 15:10 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union ADCPPB1OFFCAL_REG
{
    Uint32 all;
    struct ADCPPB1OFFCAL_BITS bit;
};

struct ADCPPB1TRIPHI_BITS
{                        // bits description
    Uint32 LIMITHI : 12; // 11:0 ADC Post Processing Block 1 Trip High Limit
    Uint32 HSIGN   : 1;  // 12 High Limit Sign Bit
    Uint32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB1TRIPHI_REG
{
    Uint32 all;
    struct ADCPPB1TRIPHI_BITS bit;
};

struct ADCPPB1TRIPLO_BITS
{                         // bits description
    Uint32 LIMITLO  : 12; // 11:0 ADC Post Processing Block 1 Trip Low Limit
    Uint32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    Uint32 rsvd1    : 8;  // 19:13 Reserved
    Uint32 REQSTAMP : 12; // 31:20 ADC Post Processing Block 1 Request Time Stamp
};

union ADCPPB1TRIPLO_REG
{
    Uint32 all;
    struct ADCPPB1TRIPLO_BITS bit;
};

struct ADCPPB2CONFIG_BITS
{                           // bits description
    Uint32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 2 Configuration
    Uint32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 2 Two's Complement Enable
    Uint32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    Uint32 rsvd1      : 25; // 31:7 Reserved
};

union ADCPPB2CONFIG_REG
{
    Uint32 all;
    struct ADCPPB2CONFIG_BITS bit;
};

struct ADCPPB2STAMP_BITS
{                         // bits description
    Uint32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 2 Delay Time Stamp
    Uint32 rsvd1    : 4;  // 15:12 Reserved
    Uint32 rsvd2    : 16; // 31:16 Reserved
};

union ADCPPB2STAMP_REG
{
    Uint32 all;
    struct ADCPPB2STAMP_BITS bit;
};

struct ADCPPB2OFFREF_BITS
{                       // bits description
    Uint32 OFFREF : 12; // 11:0 ADC Post Processing Block offset correction
    Uint32 rsvd1  : 4;  // 15:12 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union ADCPPB2OFFREF_REG
{
    Uint32 all;
    struct ADCPPB2OFFREF_BITS bit;
};

struct ADCPPB2OFFCAL_BITS
{                       // bits description
    Uint32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    Uint32 rsvd1  : 6;  // 15:10 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};
union ADCPPB2OFFCAL_REG
{
    Uint32 all;
    struct ADCPPB2OFFCAL_BITS bit;
};

struct ADCPPB2TRIPHI_BITS
{                        // bits description
    Uint32 LIMITHI : 12; // 11:0 ADC Post Processing Block 2 Trip High Limit
    Uint32 HSIGN   : 1;  // 12 High Limit Sign Bit
    Uint32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB2TRIPHI_REG
{
    Uint32 all;
    struct ADCPPB2TRIPHI_BITS bit;
};

struct ADCPPB2TRIPLO_BITS
{                         // bits description
    Uint32 LIMITLO  : 12; // 11:0 ADC Post Processing Block 2 Trip Low Limit
    Uint32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    Uint32 rsvd1    : 8;  // 19:13 Reserved
    Uint32 REQSTAMP : 12; // 31:20 ADC Post Processing Block 2 Request Time Stamp
};

union ADCPPB2TRIPLO_REG
{
    Uint32 all;
    struct ADCPPB2TRIPLO_BITS bit;
};

struct ADCPPB3CONFIG_BITS
{                           // bits description
    Uint32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 3 Configuration
    Uint32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 3 Two's Complement Enable
    Uint32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    Uint32 rsvd1      : 25; // 31:7 Reserved
};

union ADCPPB3CONFIG_REG
{
    Uint32 all;
    struct ADCPPB3CONFIG_BITS bit;
};

struct ADCPPB3STAMP_BITS
{                         // bits description
    Uint32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 3 Delay Time Stamp
    Uint32 rsvd1    : 4;  // 15:12 Reserved
    Uint32 rsvd2    : 16; // 31:16 Reserved
};
union ADCPPB3STAMP_REG
{
    Uint32 all;
    struct ADCPPB3STAMP_BITS bit;
};

struct ADCPPB3OFFREF_BITS
{                       // bits description
    Uint32 OFFREF : 12; // 11:0 ADC Post Processing Block offset correction
    Uint32 rsvd1  : 4;  // 15:12 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union ADCPPB3OFFREF_REG
{
    Uint32 all;
    struct ADCPPB3OFFREF_BITS bit;
};

struct ADCPPB3OFFCAL_BITS
{                       // bits description
    Uint32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    Uint32 rsvd1  : 6;  // 15:10 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union ADCPPB3OFFCAL_REG
{
    Uint32 all;
    struct ADCPPB2OFFCAL_BITS bit;
};

struct ADCPPB3TRIPHI_BITS
{                        // bits description
    Uint32 LIMITHI : 12; // 11:0 ADC Post Processing Block 2 Trip High Limit
    Uint32 HSIGN   : 1;  // 12 High Limit Sign Bit
    Uint32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB3TRIPHI_REG
{
    Uint32 all;
    struct ADCPPB3TRIPHI_BITS bit;
};

struct ADCPPB3TRIPLO_BITS
{                         // bits description
    Uint32 LIMITLO  : 12; // 11:0 ADC Post Processing Block 2 Trip Low Limit
    Uint32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    Uint32 rsvd1    : 8;  // 19:13 Reserved
    Uint32 REQSTAMP : 12; // 31:20 ADC Post Processing Block 2 Request Time Stamp
};

union ADCPPB3TRIPLO_REG
{
    Uint32 all;
    struct ADCPPB3TRIPLO_BITS bit;
};

struct ADCPPB4CONFIG_BITS
{                           // bits description
    Uint32 CONFIG     : 5;  // 4:0 ADC Post Processing Block 3 Configuration
    Uint32 TWOSCOMPEN : 1;  // 5 ADC Post Processing Block 3 Two's Complement Enable
    Uint32 CBCEN      : 1;  // 6 Cycle By Cycle Enable
    Uint32 rsvd1      : 25; // 31:7 Reserved
};

union ADCPPB4CONFIG_REG
{
    Uint32 all;
    struct ADCPPB4CONFIG_BITS bit;
};

struct ADCPPB4STAMP_BITS
{                         // bits description
    Uint32 DLYSTAMP : 12; // 11:0 ADC Post Processing Block 4 Delay Time Stamp
    Uint32 rsvd1    : 4;  // 15:12 Reserved
    Uint32 rsvd2    : 16; // 31:16 Reserved
};
union ADCPPB4STAMP_REG
{
    Uint32 all;
    struct ADCPPB4STAMP_BITS bit;
};

struct ADCPPB4OFFREF_BITS
{                       // bits description
    Uint32 OFFREF : 12; // 11:0 ADC Post Processing Block offset correction
    Uint32 rsvd1  : 4;  // 15:12 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union ADCPPB4OFFREF_REG
{
    Uint32 all;
    struct ADCPPB4OFFREF_BITS bit;
};

struct ADCPPB4OFFCAL_BITS
{                       // bits description
    Uint32 OFFCAL : 10; // 9:0 ADC Post Processing Block Offset Correction
    Uint32 rsvd1  : 6;  // 15:10 Reserved
    Uint32 rsvd2  : 16; // 31:16 Reserved
};

union ADCPPB4OFFCAL_REG
{
    Uint32 all;
    struct ADCPPB4OFFCAL_BITS bit;
};

struct ADCPPB4TRIPHI_BITS
{                        // bits description
    Uint32 LIMITHI : 12; // 11:0 ADC Post Processing Block 2 Trip High Limit
    Uint32 HSIGN   : 1;  // 12 High Limit Sign Bit
    Uint32 rsvd1   : 19; // 31:13 Reserved
};

union ADCPPB4TRIPHI_REG
{
    Uint32 all;
    struct ADCPPB4TRIPHI_BITS bit;
};

struct ADCPPB4TRIPLO_BITS
{                         // bits description
    Uint32 LIMITLO  : 12; // 11:0 ADC Post Processing Block 2 Trip Low Limit
    Uint32 LSIGN    : 1;  // 12 Low Limit Sign Bit
    Uint32 rsvd1    : 8;  // 19:13 Reserved
    Uint32 REQSTAMP : 12; // 31:20 ADC Post Processing Block 2 Request Time Stamp
};

union ADCPPB4TRIPLO_REG
{
    Uint32 all;
    struct ADCPPB4TRIPLO_BITS bit;
};

struct ADC_REGS
{
    union ADCCTL1_REG ADCCTL1;             // 0x0 ADC Control 1 Register
    union ADCCTL2_REG ADCCTL2;             // 0x4 ADC Control 2 Register
    union ADCBURSTCTL_REG ADCBURSTCTL;     // 0x8 ADC Burst Control Register
    union ADCINTFLG_REG ADCINTFLG;         // 0xc ADC Interrupt Flag Register
    union ADCINTFLGCLR_REG ADCINTFLGCLR;   // 0x10ADC Interrupt Flag Clear Register
    union ADCINTOVF_REG ADCINTOVF;         // ADC Interrupt Overflow Register
    union ADCINTOVFCLR_REG ADCINTOVFCLR;   // ADC Interrupt Overflow Clear Register
    union ADCINTSEL1N2_REG ADCINTSEL1N2;   // ADC Interrupt 1 and 2 Selection Register
    union ADCINTSEL3N4_REG ADCINTSEL3N4;   // 0x20ADC Interrupt 3 and 4 Selection Register
    union ADCSOCPRICTL_REG ADCSOCPRICTL;   // ADC SOC Priority Control Register
    union ADCINTSOCSEL1_REG ADCINTSOCSEL1; // ADC Interrupt SOC Selection 1 Register
    union ADCINTSOCSEL2_REG ADCINTSOCSEL2; // ADC Interrupt SOC Selection 2 Register
    union ADCSOCFLG1_REG ADCSOCFLG1;       // 0x30ADC SOC Flag 1 Register
    union ADCSOCFRC1_REG ADCSOCFRC1;       // ADC SOC Force 1 Register
    union ADCSOCOVF1_REG ADCSOCOVF1;       // ADC SOC Overflow 1 Register
    union ADCSOCOVFCLR1_REG ADCSOCOVFCLR1; // ADC SOC Overflow Clear 1 Register
    union ADCSOC0CTL_REG ADCSOC0CTL;       // 0x40ADC SOC0 Control Register
    union ADCSOC1CTL_REG ADCSOC1CTL;       // ADC SOC1 Control Register
    union ADCSOC2CTL_REG ADCSOC2CTL;       // ADC SOC2 Control Register
    union ADCSOC3CTL_REG ADCSOC3CTL;       // ADC SOC3 Control Register
    union ADCSOC4CTL_REG ADCSOC4CTL;       // 0x50ADC SOC4 Control Register
    union ADCSOC5CTL_REG ADCSOC5CTL;       // ADC SOC5 Control Register
    union ADCSOC6CTL_REG ADCSOC6CTL;       // ADC SOC6 Control Register
    union ADCSOC7CTL_REG ADCSOC7CTL;       // ADC SOC7 Control Register
    union ADCSOC8CTL_REG ADCSOC8CTL;       // 0x60ADC SOC8 Control Register
    union ADCSOC9CTL_REG ADCSOC9CTL;       // ADC SOC9 Control Register
    union ADCSOC10CTL_REG ADCSOC10CTL;     // ADC SOC10 Control Register
    union ADCSOC11CTL_REG ADCSOC11CTL;     // ADC SOC11 Control Register
    union ADCSOC12CTL_REG ADCSOC12CTL;     // 0x70ADC SOC12 Control Register
    union ADCSOC13CTL_REG ADCSOC13CTL;     // ADC SOC13 Control Register
    union ADCSOC14CTL_REG ADCSOC14CTL;     // ADC SOC14 Control Register
    union ADCSOC15CTL_REG ADCSOC15CTL;     // ADC SOC15 Control Register
    union ADCEVTSTAT_REG ADCEVTSTAT;       // 0x80ADC Event Status Register
    union ADCEVTCLR_REG ADCEVTCLR;         // ADC Event Clear Register
    union ADCEVTSEL_REG ADCEVTSEL;         // ADC Event Selection Register
    union ADCEVTINTSEL_REG ADCEVTINTSEL;   // ADC Event Interrupt Selection Register
    Uint32 rsvd1;                          // 0x90Reserved
    union ADCCOUNTER_REG ADCCOUNTER;       // ADC Counter Register
    union ADCREV_REG ADCREV;               // ADC Revision Register
    Uint32 rsvd2;                          // Reserved
    union ADCPPB1CONFIG_REG ADCPPB1CONFIG; // 0xa0ADC PPB1 Config Register
    union ADCPPB1STAMP_REG ADCPPB1STAMP;   // ADC PPB1 Sample Delay Time Stamp Register
    union ADCPPB1OFFCAL_REG ADCPPB1OFFCAL; // ADC PPB1 Offset Calibration Register
    union ADCPPB1OFFREF_REG ADCPPB1OFFREF; // ADC PPB1 Offset Reference Register
    union ADCPPB1TRIPHI_REG ADCPPB1TRIPHI; // 0xb0ADC PPB1 Trip High Register
    union ADCPPB1TRIPLO_REG ADCPPB1TRIPLO; // ADC PPB1 Trip Low/Trigger Time Stamp Register
    union ADCPPB2CONFIG_REG ADCPPB2CONFIG; // ADC PPB2 Config Register
    union ADCPPB2STAMP_REG ADCPPB2STAMP;   // ADC PPB2 Sample Delay Time Stamp Register
    union ADCPPB2OFFCAL_REG ADCPPB2OFFCAL; // 0xc0ADC PPB2 Offset Calibration Register
    union ADCPPB2OFFREF_REG ADCPPB2OFFREF; // ADC PPB2 Offset Reference Register
    union ADCPPB2TRIPHI_REG ADCPPB2TRIPHI; // ADC PPB2 Trip High Register
    union ADCPPB2TRIPLO_REG ADCPPB2TRIPLO; // ADC PPB2 Trip Low/Trigger Time Stamp Register
    union ADCPPB3CONFIG_REG ADCPPB3CONFIG; // 0xd0ADC PPB3 Config Register
    union ADCPPB3STAMP_REG ADCPPB3STAMP;   // ADC PPB3 Sample Delay Time Stamp Register
    union ADCPPB3OFFCAL_REG ADCPPB3OFFCAL; // ADC PPB3 Offset Calibration Register
    union ADCPPB3OFFREF_REG ADCPPB3OFFREF; // ADC PPB3 Offset Reference Register
    union ADCPPB3TRIPHI_REG ADCPPB3TRIPHI; // 0xe0ADC PPB3 Trip High Register
    union ADCPPB3TRIPLO_REG ADCPPB3TRIPLO; // ADC PPB3 Trip Low/Trigger Time Stamp Register
    union ADCPPB4CONFIG_REG ADCPPB4CONFIG; // ADC PPB4 Config Register
    union ADCPPB4STAMP_REG ADCPPB4STAMP;   // ADC PPB4 Sample Delay Time Stamp Register
    union ADCPPB4OFFCAL_REG ADCPPB4OFFCAL; // 0xf0ADC PPB4 Offset Calibration Register
    union ADCPPB4OFFREF_REG ADCPPB4OFFREF; // ADC PPB4 Offset Reference Register
    union ADCPPB4TRIPHI_REG ADCPPB4TRIPHI; // ADC PPB4 Trip High Register
    union ADCPPB4TRIPLO_REG ADCPPB4TRIPLO; // ADC PPB4 Trip Low/Trigger Time Stamp Register
    Uint32 ADCINTCYCLE;                    // 0x100ADC Early Interrupt Generation Cycle
    Uint32 ADCINLTRIM1;                    // ADC Linearity Trim 1 Register
    Uint32 ADCINLTRIM2;                    // ADC Linearity Trim 2 Register
};

struct ADCPPB1RESULT_BITS
{                          // bits description
    Uint32 PPBRESULT : 13; // 12:0 ADC Post Processing Block Result
    Uint32 SIGN      : 19; // 31:13 Sign Extended Bits
};

union ADCPPB1RESULT_REG
{
    Uint32 all;
    struct ADCPPB1RESULT_BITS bit;
};

struct ADCPPB2RESULT_BITS
{                          // bits description
    Uint32 PPBRESULT : 13; // 12:0 ADC Post Processing Block Result
    Uint32 SIGN      : 19; // 31:13 Sign Extended Bits
};

union ADCPPB2RESULT_REG
{
    Uint32 all;
    struct ADCPPB2RESULT_BITS bit;
};

struct ADCPPB3RESULT_BITS
{                          // bits description
    Uint32 PPBRESULT : 13; // 12:0 ADC Post Processing Block Result
    Uint32 SIGN      : 19; // 31:13 Sign Extended Bits
};

union ADCPPB3RESULT_REG
{
    Uint32 all;
    struct ADCPPB3RESULT_BITS bit;
};

struct ADCPPB4RESULT_BITS
{                          // bits description
    Uint32 PPBRESULT : 13; // 12:0 ADC Post Processing Block Result
    Uint32 SIGN      : 19; // 31:13 Sign Extended Bits
};

union ADCPPB4RESULT_REG
{
    Uint32 all;
    struct ADCPPB4RESULT_BITS bit;
};

struct ADC_RESULT_REGS
{
    Uint32 ADCRESULT0;                     // ADC Result 0 Register
    Uint32 ADCRESULT1;                     // ADC Result 1 Register
    Uint32 ADCRESULT2;                     // ADC Result 2 Register
    Uint32 ADCRESULT3;                     // ADC Result 3 Register
    Uint32 ADCRESULT4;                     // ADC Result 4 Register
    Uint32 ADCRESULT5;                     // ADC Result 5 Register
    Uint32 ADCRESULT6;                     // ADC Result 6 Register
    Uint32 ADCRESULT7;                     // ADC Result 7 Register
    Uint32 ADCRESULT8;                     // ADC Result 8 Register
    Uint32 ADCRESULT9;                     // ADC Result 9 Register
    Uint32 ADCRESULT10;                    // ADC Result 10 Register
    Uint32 ADCRESULT11;                    // ADC Result 11 Register
    Uint32 ADCRESULT12;                    // ADC Result 12 Register
    Uint32 ADCRESULT13;                    // ADC Result 13 Register
    Uint32 ADCRESULT14;                    // ADC Result 14 Register
    Uint32 ADCRESULT15;                    // ADC Result 15 Register
    union ADCPPB1RESULT_REG ADCPPB1RESULT; // ADC Post Processing Block 1 Result Register
    union ADCPPB2RESULT_REG ADCPPB2RESULT; // ADC Post Processing Block 2 Result Register
    union ADCPPB3RESULT_REG ADCPPB3RESULT; // ADC Post Processing Block 3 Result Register
    union ADCPPB4RESULT_REG ADCPPB4RESULT; // ADC Post Processing Block 4 Result Register
};

//---------------------------------------------------------------------------
// ADC External References & Function Declarations:
//
extern volatile struct ADC_RESULT_REGS AdcaResultRegs;
extern volatile struct ADC_RESULT_REGS AdcbResultRegs;
extern volatile struct ADC_RESULT_REGS AdccResultRegs;
extern volatile struct ADC_RESULT_REGS AdcgResultRegs;
extern volatile struct ADC_RESULT_REGS AdchResultRegs;
extern volatile struct ADC_REGS AdcaRegs;
extern volatile struct ADC_REGS AdcbRegs;
extern volatile struct ADC_REGS AdccRegs;
extern volatile struct ADC_REGS AdcgRegs;
extern volatile struct ADC_REGS AdchRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
