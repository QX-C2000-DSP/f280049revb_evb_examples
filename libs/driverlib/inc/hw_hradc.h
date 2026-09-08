#ifndef HW_HRADC_H
#define HW_HRADC_H

// ####
//*************************************************************************************************
//
//  The following are defines for the HR_ADC register offsets
//
//*************************************************************************************************
#define HR_ADC_O_CTL1       0x00U // HR_ADC Control Register
#define HR_ADC_O_CTL2       0x04U // HR_ADC Control Register
#define HR_ADC_O_INTFLG     0x08U // HR_ADC Interrupt Flag Register
#define HR_ADC_O_INTFLGCLR  0x0cU // HR_ADC Interrupt Flag Clear Register
#define HR_ADC_O_INTOVF     0x10U // HR_ADC Interrupt Overflow Register
#define HR_ADC_O_INTOVFCLR  0x14U // HR_ADC Interrupt Overflow Clear Register
#define HR_ADC_O_INTSEL1N2  0x18U // HR_ADC Interrupt Selection Register
#define HR_ADC_O_SOCPRICTL  0x1cU // HR_ADC Interrupt Selection Register
#define HR_ADC_O_SOCFLG1    0x20U // HR_ADC Interrupt Selection Register
#define HR_ADC_O_SOCFRC1    0x24U // HR_ADC Interrupt Selection Register
#define HR_ADC_O_SOCOVF1    0x28U // HR_ADC Interrupt Selection Register
#define HR_ADC_O_SOCOVFCLR1 0x2cU // HR_ADC Interrupt Selection Register
#define HR_ADC_O_SOC0CTL    0x30U // HR_ADC SOC0 Control Register
#define HR_ADC_O_SOC1CTL    0x34U // HR_ADC SOC1 Control Register
#define HR_ADC_O_SOC2CTL    0x38U // HR_ADC SOC2 Control Register
#define HR_ADC_O_SOC3CTL    0x3cU // HR_ADC SOC3 Control Register
#define HR_ADC_O_SOC4CTL    0x40U // HR_ADC SOC4 Control Register
#define HR_ADC_O_SOC5CTL    0x44U // HR_ADC SOC5 Control Register
#define HR_ADC_O_SOC6CTL    0x48U // HR_ADC SOC6 Control Register
#define HR_ADC_O_SOC7CTL    0x4cU // HR_ADC SOC7 Control Register
#define HR_ADC_O_SOC8CTL    0x50U // HR_ADC SOC8 Control Register
#define HR_ADC_O_SOC9CTL    0x54U // HR_ADC SOC9 Control Register
#define HR_ADC_O_SOC10CTL   0x58U // HR_ADC SOC10 Control Register
#define HR_ADC_O_SOC11CTL   0x5cU // HR_ADC SOC11 Control Register
#define HR_ADC_O_SOC12CTL   0x60U // HR_ADC SOC12 Control Register
#define HR_ADC_O_SOC13CTL   0x64U // HR_ADC SOC13 Control Register
#define HR_ADC_O_SOC14CTL   0x68U // HR_ADC SOC14 Control Register
#define HR_ADC_O_SOC15CTL   0x6cU // HR_ADC SOC15 Control Register
#define HR_ADC_O_EVTSTAT    0x70U // HR_ADC Event Status Register
#define HR_ADC_O_EVTCLR     0x74U // HR_ADC Event Clear Register
#define HR_ADC_O_EVTSEL     0x78U // HR_ADC Event Selection Register
#define HR_ADC_O_EVTINTSEL  0x7cU // HR_ADC Event Interrupt Selection Register
#define HR_ADC_O_COUNTER    0x80U // HR_ADC Counter Register
#define HR_ADC_O_REV        0x84U // HR_ADC Revision Register
#define HR_ADC_O_PPB1CONFIG 0x88U // HR_ADC PPB1 Configuration Register
#define HR_ADC_O_PPB1STAMP  0x8cU // HR_ADC PPB1 Sample Delay Time Stamp Register
#define HR_ADC_O_PPB1OFFCAL 0x90U // HR_ADC PPB1 Offset Calibration Register
#define HR_ADC_O_PPB1OFFREF 0x94U // HR_ADC PPB1 Offset Reference Register
#define HR_ADC_O_PPB1TRIPHI 0x98U // HR_ADC PPB1 Trip High Register
#define HR_ADC_O_PPB1TRIPLO 0x9cU // HR_ADC PPB1 Trip Low Register
#define HR_ADC_O_PPB2CONFIG 0xa0U // HR_ADC PPB2 Configuration Register
#define HR_ADC_O_PPB2STAMP  0xa4U // HR_ADC PPB2 Sample Delay Time Stamp Register
#define HR_ADC_O_PPB2OFFCAL 0xa8U // HR_ADC PPB2 Offset Calibration Register
#define HR_ADC_O_PPB2OFFREF 0xacU // HR_ADC PPB2 Offset Reference Register
#define HR_ADC_O_PPB2TRIPHI 0xb0U // HR_ADC PPB2 Trip High Register
#define HR_ADC_O_PPB2TRIPLO 0xb4U // HR_ADC PPB2 Trip Low Register
#define HR_ADC_O_PPB3CONFIG 0xb8U // HR_ADC PPB3 Configuration Register
#define HR_ADC_O_PPB3STAMP  0xbcU // HR_ADC PPB3 Sample Delay Time Stamp Register
#define HR_ADC_O_PPB3OFFCAL 0xc0U // HR_ADC PPB3 Offset Calibration Register
#define HR_ADC_O_PPB3OFFREF 0xc4U // HR_ADC PPB3 Offset Reference Register
#define HR_ADC_O_PPB3TRIPHI 0xc8U // HR_ADC PPB3 Trip High Register
#define HR_ADC_O_PPB3TRIPLO 0xccU // HR_ADC PPB3 Trip Low Register
#define HR_ADC_O_PPB4CONFIG 0xd0U // HR_ADC PPB4 Configuration Register
#define HR_ADC_O_PPB4STAMP  0xd4U // HR_ADC PPB4 Sample Delay Time Stamp Register
#define HR_ADC_O_PPB4OFFCAL 0xd8U // HR_ADC PPB4 Offset Calibration Register
#define HR_ADC_O_PPB4OFFREF 0xdcU // HR_ADC PPB4 Offset Reference Register
#define HR_ADC_O_PPB4TRIPHI 0xe0U // HR_ADC PPB4 Trip High Register
#define HR_ADC_O_PPB4TRIPLO 0xe4U // HR_ADC PPB4 Trip Low Register
#define HR_ADC_O_BURSTCTL   0xe8U // HR_ADC Burst Register
#define HR_ADC_O_INTSOCSEL  0xecU // HR_ADC INTSOCSEL Register

#define HR_ADC_O_RESULT0  0x00U // HR_ADC Result 0 Register
#define HR_ADC_O_RESULT1  0x04U // HR_ADC Result 1 Register
#define HR_ADC_O_RESULT2  0x08U // HR_ADC Result 2 Register
#define HR_ADC_O_RESULT3  0x0cU // HR_ADC Result 3 Register
#define HR_ADC_O_RESULT4  0x10U // HR_ADC Result 4 Register
#define HR_ADC_O_RESULT5  0x14U // HR_ADC Result 5 Register
#define HR_ADC_O_RESULT6  0x18U // HR_ADC Result 6 Register
#define HR_ADC_O_RESULT7  0x1cU // HR_ADC Result 7 Register
#define HR_ADC_O_RESULT8  0x20U // HR_ADC Result 8 Register
#define HR_ADC_O_RESULT9  0x24U // HR_ADC Result 9 Register
#define HR_ADC_O_RESULT10 0x28U // HR_ADC Result 10 Register
#define HR_ADC_O_RESULT11 0x2cU // HR_ADC Result 11 Register
#define HR_ADC_O_RESULT12 0x30U // HR_ADC Result 12 Register
#define HR_ADC_O_RESULT13 0x34U // HR_ADC Result 13 Register
#define HR_ADC_O_RESULT14 0x38U // HR_ADC Result 14 Register
#define HR_ADC_O_RESULT15 0x3cU // HR_ADC Result 15 Register

#define HR_ADC_O_PPB1RESULT 0x150U // HR_ADC PPB1 Result Register
#define HR_ADC_O_PPB2RESULT 0x154U // HR_ADC PPB2 Result Register
#define HR_ADC_O_PPB3RESULT 0x158U // HR_ADC PPB3 Result Register
#define HR_ADC_O_PPB4RESULT 0x15cU // HR_ADC PPB4 Result Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCCTL1 register
//
//*************************************************************************************************
#define HR_ADC_CTL1_RESTART_P      0x2U
#define HR_ADC_CTL1_INTPULSEPOS    0x4U
#define HR_ADC_CTL1_DISLVL         0x8U
#define HR_ADC_CTL1_ENLDO          0x10U
#define HR_ADC_CTL1_STARTCAL_P     0x20U
#define HR_ADC_CTL1_RESERZ_P       0x40U
#define HR_ADC_CTL1_ADC_EN_P       0x80U
#define HR_ADC_CTL1_ADC_BUSYCHAN_S 8U
#define HR_ADC_CTL1_ADC_BUSYCHAN_M 0xf00U
#define HR_ADC_CTL1_SELREF_LDO     0x1000U
#define HR_ADC_CTL1_ADCBSY         0x2000U
#define HR_ADC_CTL1_SELRANGE_LDO   0x4000U
#define HR_ADC_CTL1_STARTOSCAL_P   0x8000U
#define HR_ADC_CTL1_PG             0x10000U
#define HR_ADC_CTL1_ADCRDY         0x20000U
#define HR_ADC_CTL1_REARM_CNTREF_S 17U
#define HR_ADC_CTL1_PRESCALE_M     0x7ffc0000U

//*************************************************************************************************

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCCTL2 register
//
//*************************************************************************************************

#define HR_ADC_CTL2_PRESCALE_M     0x1FU
#define HR_ADC_CTL2_SELRES_S       5U
#define HR_ADC_CTL2_SELRES_M       0x60U
#define HR_ADC_CTL2_SELDIFF        0x80U
#define HR_ADC_CTL2_PRESCALEPCLK_M 0x1F00U

//*************************************************************************************************

//
// The following are defines for the bit fields in the HR_ADCBURSTCTL register
//
//*************************************************************************************************
#define HR_ADC_BURSTCTL_BURSTTRIGSEL_S 0U
#define HR_ADC_BURSTCTL_BURSTTRIGSEL_M 0x3FU // SOC Burst Trigger Source Select
#define HR_ADC_BURSTCTL_BURSTSIZE_S    8U
#define HR_ADC_BURSTCTL_BURSTSIZE_M    0xF00U  // SOC Burst Size Select
#define HR_ADC_BURSTCTL_BURSTEN        0x8000U // SOC Burst Mode Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCINTSOCSEL register
//
//*************************************************************************************************
#define HR_ADC_INTSOCSEL1_SOC0_S  0U
#define HR_ADC_INTSOCSEL1_SOC0_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC1_S  2U
#define HR_ADC_INTSOCSEL1_SOC1_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC2_S  4U
#define HR_ADC_INTSOCSEL1_SOC2_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC3_S  6U
#define HR_ADC_INTSOCSEL1_SOC3_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC4_S  8U
#define HR_ADC_INTSOCSEL1_SOC4_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC5_S  10U
#define HR_ADC_INTSOCSEL1_SOC5_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC6_S  12U
#define HR_ADC_INTSOCSEL1_SOC6_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC7_S  14U
#define HR_ADC_INTSOCSEL1_SOC7_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC8_S  16U
#define HR_ADC_INTSOCSEL1_SOC8_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC9_S  18U
#define HR_ADC_INTSOCSEL1_SOC9_M  0x3U
#define HR_ADC_INTSOCSEL1_SOC10_S 20U
#define HR_ADC_INTSOCSEL1_SOC10_M 0x3U
#define HR_ADC_INTSOCSEL1_SOC11_S 22U
#define HR_ADC_INTSOCSEL1_SOC11_M 0x3U
#define HR_ADC_INTSOCSEL1_SOC12_S 24U
#define HR_ADC_INTSOCSEL1_SOC12_M 0x3U
#define HR_ADC_INTSOCSEL1_SOC13_S 26U
#define HR_ADC_INTSOCSEL1_SOC13_M 0x3U
#define HR_ADC_INTSOCSEL1_SOC14_S 28U
#define HR_ADC_INTSOCSEL1_SOC14_M 0x3U
#define HR_ADC_INTSOCSEL1_SOC15_S 30U
#define HR_ADC_INTSOCSEL1_SOC15_M 0x3U
//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOCPRICTL register
//
//*************************************************************************************************
#define HR_ADCSOCPRICTL_SOCPRIORITY_M 0x1FU // HR_ADC SOCPRIORITY
#define HR_ADCSOCPRICTL_RRPOINTER_S   5U    // HR_ADC RRPOINTER start bit
#define HR_ADCSOCPRICTL_RRPOINTER_M   0x3eU // HR_ADC RRPOINTER mask

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCINTFLG register
//
//*************************************************************************************************
#define HR_ADC_INTFLG_ADCINT1 0x1U // HR_ADC Interrupt 1 Flag
#define HR_ADC_INTFLG_ADCINT2 0x2U // HR_ADC Interrupt 2 Flag
#define HR_ADC_INTFLG_ADCINT3 0x4U // HR_ADC Interrupt 3 Flag
#define HR_ADC_INTFLG_ADCINT4 0x8U // HR_ADC Interrupt 4 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCINTFLGCLR register
//
//*************************************************************************************************
#define HR_ADC_INTFLGCLR_ADCINT1 0x1U // HR_ADC Interrupt 1 Flag Clear
#define HR_ADC_INTFLGCLR_ADCINT2 0x2U // HR_ADC Interrupt 2 Flag Clear
#define HR_ADC_INTFLGCLR_ADCINT3 0x4U // HR_ADC Interrupt 3 Flag Clear
#define HR_ADC_INTFLGCLR_ADCINT4 0x8U // HR_ADC Interrupt 4 Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCINTOVF register
//
//*************************************************************************************************
#define HR_ADC_INTOVF_ADCINT1 0x1U // HR_ADC Interrupt 1 Overflow Flags
#define HR_ADC_INTOVF_ADCINT2 0x2U // HR_ADC Interrupt 2 Overflow Flags
#define HR_ADC_INTOVF_ADCINT3 0x4U // HR_ADC Interrupt 3 Overflow Flags
#define HR_ADC_INTOVF_ADCINT4 0x8U // HR_ADC Interrupt 4 Overflow Flags

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCINTOVFCLR register
//
//*************************************************************************************************
#define HR_ADC_INTOVFCLR_ADCINT1 0x1U // HR_ADC Interrupt 1 Overflow Clear Bits
#define HR_ADC_INTOVFCLR_ADCINT2 0x2U // HR_ADC Interrupt 2 Overflow Clear Bits
#define HR_ADC_INTOVFCLR_ADCINT3 0x4U // HR_ADC Interrupt 3 Overflow Clear Bits
#define HR_ADC_INTOVFCLR_ADCINT4 0x8U // HR_ADC Interrupt 4 Overflow Clear Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCINTSEL register
//
//*************************************************************************************************
#define HR_ADC_INTSEL1N2_INT1SEL_S 0U
#define HR_ADC_INTSEL1N2_INT1SEL_M 0x1fU // HR_ADCINT1 EOC Source Select
#define HR_ADC_INTSEL1N2_INT1E     0x20U // HR_ADCINT1 Interrupt Enable
#define HR_ADC_INTSEL1N2_INT1CONT  0x40U // HR_ADCINT1 Continue to Interrupt Mode
#define HR_ADC_INTSEL1N2_INT2SEL_S 8U
#define HR_ADC_INTSEL1N2_INT2SEL_M 0x1f00U // HR_ADCINT2 EOC Source Select
#define HR_ADC_INTSEL1N2_INT2E     0x2000U // HR_ADCINT2 Interrupt Enable
#define HR_ADC_INTSEL1N2_INT2CONT  0x4000U // HR_ADCINT2 Continue to Interrupt Mode
#define HR_ADC_INTSEL1N2_INT3SEL_S 16U
#define HR_ADC_INTSEL1N2_INT3SEL_M 0x1f0000U // HR_ADCINT1 EOC Source Select
#define HR_ADC_INTSEL1N2_INT3E     0x200000U // HR_ADCINT1 Interrupt Enable
#define HR_ADC_INTSEL1N2_INT3CONT  0x400000U // HR_ADCINT1 Continue to Interrupt Mode
#define HR_ADC_INTSEL1N2_INT4SEL_S 24U
#define HR_ADC_INTSEL1N2_INT4SEL_M 0x1f000000U // HR_ADCINT2 EOC Source Select
#define HR_ADC_INTSEL1N2_INT4E     0x20000000U // HR_ADCINT2 Interrupt Enable
#define HR_ADC_INTSEL1N2_INT4CONT  0x40000000U // HR_ADCINT2 Continue to Interrupt Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC0CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC0CTL_CHSEL_S   15U
#define HR_ADC_SOC0CTL_CHSEL_M   0x78000U // SOC0 Channel Select
#define HR_ADC_SOC0CTL_TRIGSEL_S 20U
#define HR_ADC_SOC0CTL_TRIGSEL_M 0x1f00000U // SOC0 Trigger Source Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC1CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC1CTL_CHSEL_S   12U
#define HR_ADC_SOC1CTL_CHSEL_M   0x1f000U // SOC1 Channel Select
#define HR_ADC_SOC1CTL_TRIGSEL_S 3U
#define HR_ADC_SOC1CTL_TRIGSEL_M 0xF8U // SOC1 Trigger Source Select
#define HR_ADC_SOC1CTL_ACQPS_S   8U
#define HR_ADC_SOC1CTL_ACQPS_M   0xF00U // SOC1 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC2CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC2CTL_CHSEL_S   12U
#define HR_ADC_SOC2CTL_CHSEL_M   0x1f000U // SOC2 Channel Select
#define HR_ADC_SOC2CTL_TRIGSEL_S 3U
#define HR_ADC_SOC2CTL_TRIGSEL_M 0xF8U // SOC2 Trigger Source Select
#define HR_ADC_SOC2CTL_ACQPS_S   8U
#define HR_ADC_SOC2CTL_ACQPS_M   0xF00U // SOC2 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC3CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC3CTL_CHSEL_S   12U
#define HR_ADC_SOC3CTL_CHSEL_M   0x1f000U // SOC3 Channel Select
#define HR_ADC_SOC3CTL_TRIGSEL_S 3U
#define HR_ADC_SOC3CTL_TRIGSEL_M 0xF8U // SOC3 Trigger Source Select
#define HR_ADC_SOC3CTL_ACQPS_S   8U
#define HR_ADC_SOC3CTL_ACQPS_M   0xF00U // SOC3 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC4CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC4CTL_CHSEL_S   12U
#define HR_ADC_SOC4CTL_CHSEL_M   0x1f000U // SOC4 Channel Select
#define HR_ADC_SOC4CTL_TRIGSEL_S 3U
#define HR_ADC_SOC4CTL_TRIGSEL_M 0xF8U // SOC4 Trigger Source Select
#define HR_ADC_SOC4CTL_ACQPS_S   8U
#define HR_ADC_SOC4CTL_ACQPS_M   0xF00U // SOC4 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC5CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC5CTL_CHSEL_S   12U
#define HR_ADC_SOC5CTL_CHSEL_M   0x1f000U // SOC5 Channel Select
#define HR_ADC_SOC5CTL_TRIGSEL_S 3U
#define HR_ADC_SOC5CTL_TRIGSEL_M 0xF8U // SOC5 Trigger Source Select
#define HR_ADC_SOC5CTL_ACQPS_S   8U
#define HR_ADC_SOC5CTL_ACQPS_M   0xF00U // SOC5 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC6CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC6CTL_CHSEL_S   12U
#define HR_ADC_SOC6CTL_CHSEL_M   0x1f000U // SOC6 Channel Select
#define HR_ADC_SOC6CTL_TRIGSEL_S 3U
#define HR_ADC_SOC6CTL_TRIGSEL_M 0xF8U // SOC6 Trigger Source Select
#define HR_ADC_SOC6CTL_ACQPS_S   8U
#define HR_ADC_SOC6CTL_ACQPS_M   0xF00U // SOC6 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC7CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC7CTL_CHSEL_S   12U
#define HR_ADC_SOC7CTL_CHSEL_M   0x1f000U // SOC7 Channel Select
#define HR_ADC_SOC7CTL_TRIGSEL_S 3U
#define HR_ADC_SOC7CTL_TRIGSEL_M 0xF8U // SOC7 Trigger Source Select
#define HR_ADC_SOC7CTL_ACQPS_S   8U
#define HR_ADC_SOC7CTL_ACQPS_M   0xF00U // SOC7 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC8CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC8CTL_CHSEL_S   12U
#define HR_ADC_SOC8CTL_CHSEL_M   0x1f000U // SOC8 Channel Select
#define HR_ADC_SOC8CTL_TRIGSEL_S 3U
#define HR_ADC_SOC8CTL_TRIGSEL_M 0xF8U // SOC8 Trigger Source Select
#define HR_ADC_SOC8CTL_ACQPS_S   8U
#define HR_ADC_SOC8CTL_ACQPS_M   0xF00U // SOC8 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC9CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC9CTL_CHSEL_S   12U
#define HR_ADC_SOC9CTL_CHSEL_M   0x1f000U // SOC9 Channel Select
#define HR_ADC_SOC9CTL_TRIGSEL_S 3U
#define HR_ADC_SOC9CTL_TRIGSEL_M 0xF8U // SOC9 Trigger Source Select
#define HR_ADC_SOC9CTL_ACQPS_S   8U
#define HR_ADC_SOC9CTL_ACQPS_M   0xF00U // SOC9 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC10CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC10CTL_CHSEL_S   12U
#define HR_ADC_SOC10CTL_CHSEL_M   0x1f000U // SOC10 Channel Select
#define HR_ADC_SOC10CTL_TRIGSEL_S 3U
#define HR_ADC_SOC10CTL_TRIGSEL_M 0xF8U // SOC10 Trigger Source Select
#define HR_ADC_SOC10CTL_ACQPS_S   8U
#define HR_ADC_SOC10CTL_ACQPS_M   0xF00U // SOC10 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC11CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC11CTL_CHSEL_S   12U
#define HR_ADC_SOC11CTL_CHSEL_M   0x1f000U // SOC11 Channel Select
#define HR_ADC_SOC11CTL_TRIGSEL_S 3U
#define HR_ADC_SOC11CTL_TRIGSEL_M 0xF8U // SOC11 Trigger Source Select
#define HR_ADC_SOC11CTL_ACQPS_S   8U
#define HR_ADC_SOC11CTL_ACQPS_M   0xF00U // SOC11 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC12CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC12CTL_CHSEL_S   12U
#define HR_ADC_SOC12CTL_CHSEL_M   0x1f000U // SOC12 Channel Select
#define HR_ADC_SOC12CTL_TRIGSEL_S 3U
#define HR_ADC_SOC12CTL_TRIGSEL_M 0xF8U // SOC12 Trigger Source Select
#define HR_ADC_SOC12CTL_ACQPS_S   8U
#define HR_ADC_SOC12CTL_ACQPS_M   0xF00U // SOC12 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC13CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC13CTL_CHSEL_S   12U
#define HR_ADC_SOC13CTL_CHSEL_M   0x1f000U // SOC13 Channel Select
#define HR_ADC_SOC13CTL_TRIGSEL_S 3U
#define HR_ADC_SOC13CTL_TRIGSEL_M 0xF8U // SOC13 Trigger Source Select
#define HR_ADC_SOC13CTL_ACQPS_S   8U
#define HR_ADC_SOC13CTL_ACQPS_M   0xF00U // SOC13 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC14CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC14CTL_CHSEL_S   12U
#define HR_ADC_SOC14CTL_CHSEL_M   0x1f000U // SOC14 Channel Select
#define HR_ADC_SOC14CTL_TRIGSEL_S 3U
#define HR_ADC_SOC14CTL_TRIGSEL_M 0xF8U // SOC14 Trigger Source Select
#define HR_ADC_SOC14CTL_ACQPS_S   8U
#define HR_ADC_SOC14CTL_ACQPS_M   0xF00U // SOC14 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC15CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC15CTL_CHSEL_S   12U
#define HR_ADC_SOC15CTL_CHSEL_M   0x1f000U // SOC15 Channel Select
#define HR_ADC_SOC15CTL_TRIGSEL_S 3U
#define HR_ADC_SOC15CTL_TRIGSEL_M 0xF8U // SOC15 Trigger Source Select
#define HR_ADC_SOC15CTL_ACQPS_S   8U
#define HR_ADC_SOC15CTL_ACQPS_M   0xF00U // SOC15 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC16CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC16CTL_CHSEL_S   12U
#define HR_ADC_SOC16CTL_CHSEL_M   0x1f000U // SOC16 Channel Select
#define HR_ADC_SOC16CTL_TRIGSEL_S 3U
#define HR_ADC_SOC16CTL_TRIGSEL_M 0xF8U // SOC16 Trigger Source Select
#define HR_ADC_SOC16CTL_ACQPS_S   8U
#define HR_ADC_SOC16CTL_ACQPS_M   0xF00U // SOC16 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC17CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC17CTL_CHSEL_S   12U
#define HR_ADC_SOC17CTL_CHSEL_M   0x1f000U // SOC17 Channel Select
#define HR_ADC_SOC17CTL_TRIGSEL_S 3U
#define HR_ADC_SOC17CTL_TRIGSEL_M 0xF8U // SOC17 Trigger Source Select
#define HR_ADC_SOC17CTL_ACQPS_S   8U
#define HR_ADC_SOC17CTL_ACQPS_M   0xF00U // SOC17 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC18CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC18CTL_CHSEL_S   12U
#define HR_ADC_SOC18CTL_CHSEL_M   0x1f000U // SOC18 Channel Select
#define HR_ADC_SOC18CTL_TRIGSEL_S 3U
#define HR_ADC_SOC18CTL_TRIGSEL_M 0xF8U // SOC18 Trigger Source Select
#define HR_ADC_SOC18CTL_ACQPS_S   8U
#define HR_ADC_SOC18CTL_ACQPS_M   0xF00U // SOC18 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOC19CTL register
//
//*************************************************************************************************
#define HR_ADC_SOC19CTL_CHSEL_S   12U
#define HR_ADC_SOC19CTL_CHSEL_M   0x1f000U // SOC19 Channel Select
#define HR_ADC_SOC19CTL_TRIGSEL_S 3U
#define HR_ADC_SOC19CTL_TRIGSEL_M 0xF8U // SOC19 Trigger Source Select
#define HR_ADC_SOC19CTL_ACQPS_S   8U
#define HR_ADC_SOC19CTL_ACQPS_M   0xF00U // SOC19 Acquisition Prescale

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCEVTSTAT register
//
//*************************************************************************************************
#define HR_ADC_EVTSTAT_PPB1TRIPHI 0x1U   // Post Processing Block 1 Trip High Flag
#define HR_ADC_EVTSTAT_PPB1TRIPLO 0x2U   // Post Processing Block 1 Trip Low Flag
#define HR_ADC_EVTSTAT_PPB1ZERO   0x4U   // Post Processing Block 1 Zero Crossing Flag
#define HR_ADC_EVTSTAT_PPB2TRIPHI 0x8U   // Post Processing Block 2 Trip High Flag
#define HR_ADC_EVTSTAT_PPB2TRIPLO 0x10U  // Post Processing Block 2 Trip Low Flag
#define HR_ADC_EVTSTAT_PPB2ZERO   0x20U  // Post Processing Block 2 Zero Crossing Flag
#define HR_ADC_EVTSTAT_PPB3TRIPHI 0x40U  // Post Processing Block 3 Trip High Flag
#define HR_ADC_EVTSTAT_PPB3TRIPLO 0x80U  // Post Processing Block 3 Trip Low Flag
#define HR_ADC_EVTSTAT_PPB3ZERO   0x100U // Post Processing Block 3 Zero Crossing Flag
#define HR_ADC_EVTSTAT_PPB4TRIPHI 0x200U // Post Processing Block 4 Trip High Flag
#define HR_ADC_EVTSTAT_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag
#define HR_ADC_EVTSTAT_PPB4ZERO   0x800U // Post Processing Block 4 Zero Crossing Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCEVTCLR register
//
//*************************************************************************************************
#define HR_ADC_EVTCLR_PPB1TRIPHI 0x1U   // Post Processing Block 1 Trip High Flag Clear
#define HR_ADC_EVTCLR_PPB1TRIPLO 0x2U   // Post Processing Block 1 Trip Low Flag Clear
#define HR_ADC_EVTCLR_PPB1ZERO   0x4U   // Post Processing Block 1 Zero Crossing Flag Clear
#define HR_ADC_EVTCLR_PPB2TRIPHI 0x8U   // Post Processing Block 2 Trip High Flag Clear
#define HR_ADC_EVTCLR_PPB2TRIPLO 0x10U  // Post Processing Block 2 Trip Low Flag Clear
#define HR_ADC_EVTCLR_PPB2ZERO   0x20U  // Post Processing Block 2 Zero Crossing Flag Clear
#define HR_ADC_EVTCLR_PPB3TRIPHI 0x40U  // Post Processing Block 3 Trip High Flag Clear
#define HR_ADC_EVTCLR_PPB3TRIPLO 0x80U  // Post Processing Block 3 Trip Low Flag Clear
#define HR_ADC_EVTCLR_PPB3ZERO   0x100U // Post Processing Block 3 Zero Crossing Flag Clear
#define HR_ADC_EVTCLR_PPB4TRIPHI 0x200U // Post Processing Block 4 Trip High Flag Clear
#define HR_ADC_EVTCLR_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag Clear
#define HR_ADC_EVTCLR_PPB4ZERO   0x800U // Post Processing Block 4 Zero Crossing Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCEVTSEL register
//
//*************************************************************************************************
#define HR_ADC_EVTSEL_PPB1TRIPHI 0x1U   // Post Processing Block 1 Trip High Flag Select
#define HR_ADC_EVTSEL_PPB1TRIPLO 0x2U   // Post Processing Block 1 Trip Low Flag Select
#define HR_ADC_EVTSEL_PPB1ZERO   0x4U   // Post Processing Block 1 Zero Crossing Flag Select
#define HR_ADC_EVTSEL_PPB2TRIPHI 0x8U   // Post Processing Block 2 Trip High Flag Select
#define HR_ADC_EVTSEL_PPB2TRIPLO 0x10U  // Post Processing Block 2 Trip Low Flag Select
#define HR_ADC_EVTSEL_PPB2ZERO   0x20U  // Post Processing Block 2 Zero Crossing Flag Select
#define HR_ADC_EVTSEL_PPB3TRIPHI 0x40U  // Post Processing Block 3 Trip High Flag Select
#define HR_ADC_EVTSEL_PPB3TRIPLO 0x80U  // Post Processing Block 3 Trip Low Flag Select
#define HR_ADC_EVTSEL_PPB3ZERO   0x100U // Post Processing Block 3 Zero Crossing Flag Select
#define HR_ADC_EVTSEL_PPB4TRIPHI 0x200U // Post Processing Block 4 Trip High Flag Select
#define HR_ADC_EVTSEL_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag Select
#define HR_ADC_EVTSEL_PPB4ZERO   0x800U // Post Processing Block 4 Zero Crossing Flag Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCEVTINTSEL register
//
//*************************************************************************************************
#define HR_ADC_EVTINTSEL_PPB1TRIPHI 0x1U // Post Processing Block 1 Trip High Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB1TRIPLO 0x2U // Post Processing Block 1 Trip Low Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB1ZERO \
    0x4U // Post Processing Block 1 Zero Crossing Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB2TRIPHI 0x8U  // Post Processing Block 2 Trip High Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB2TRIPLO 0x10U // Post Processing Block 2 Trip Low Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB2ZERO \
    0x20U // Post Processing Block 2 Zero Crossing Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB3TRIPHI 0x40U // Post Processing Block 3 Trip High Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB3TRIPLO 0x80U // Post Processing Block 3 Trip Low Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB3ZERO \
    0x100U // Post Processing Block 3 Zero Crossing Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB4TRIPHI \
    0x200U // Post Processing Block 4 Trip High Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB4TRIPLO 0x400U // Post Processing Block 4 Trip Low Flag Interrupt Select
#define HR_ADC_EVTINTSEL_PPB4ZERO \
    0x800U // Post Processing Block 4 Zero Crossing Flag Interrupt Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCCOUNTER register
//
//*************************************************************************************************
#define HR_ADC_COUNTER_FREECOUNT_S 0U
#define HR_ADC_COUNTER_FREECOUNT_M 0xFFFU // HR_ADC Free Running Counter Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCREV register
//
//*************************************************************************************************
#define HR_ADC_REV_TYPE_S 0U
#define HR_ADC_REV_TYPE_M 0xFFU // HR_ADC Type
#define HR_ADC_REV_REV_S  8U
#define HR_ADC_REV_REV_M  0xFF00U // HR_ADC Revision

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBCONFIG register
//
//*************************************************************************************************
#define HR_ADC_PPB1CONFIG_CONFIG_S   0U
#define HR_ADC_PPB1CONFIG_CONFIG_M   0x1fU // HR_ADC Post Processing Block 1 Configuration
#define HR_ADC_PPB1CONFIG_TWOSCOMPEN 0x20U // HR_ADC Post Processing Block 1 Two's Complement Enable
#define HR_ADC_PPB1CONFIG_CBCEN      0x40U // HR_ADC Post Processing Block 1 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBSTAMP register
//
//*************************************************************************************************
#define HR_ADC_PPB1STAMP_DLYSTAMP_S 0U
#define HR_ADC_PPB1STAMP_DLYSTAMP_M 0xFFFU // HR_ADC Post Processing Block 1 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFREF register
//
//*************************************************************************************************
#define HR_ADC_PPB1OFFREF_OFFREF_S 0U
#define HR_ADC_PPB1OFFREF_OFFREF_M 0xFFFFU // HR_ADC Post Processing Block 1 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPHI register
//
//*************************************************************************************************
#define HR_ADC_PPB1TRIPHI_LIMITHI_S 0U
#define HR_ADC_PPB1TRIPHI_LIMITHI_M 0xFFFU  // HR_ADC Post Processing Block 1 Trip High Limit
#define HR_ADC_PPB1TRIPHI_HSIGN     0x1000U // HR_ADC Post Processing Block 1 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPLO register
//
//*************************************************************************************************
#define HR_ADC_PPB1TRIPLO_LIMITLO_S  0U
#define HR_ADC_PPB1TRIPLO_LIMITLO_M  0xFFFU  // HR_ADC Post Processing Block 1 Trip Low Limit
#define HR_ADC_PPB1TRIPLO_LSIGN      0x1000U // HR_ADC Post Processing Block 1 Low Limit Sign Bit
#define HR_ADC_PPB1TRIPLO_REQSTAMP_S 20U
#define HR_ADC_PPB1TRIPLO_REQSTAMP_M \
    0xFFF00000U // HR_ADC Post Processing Block 1 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFCAL register
//
//*************************************************************************************************
#define HR_ADC_PPB1OFFCAL_OFFCAL_S 0U
#define HR_ADC_PPB1OFFCAL_OFFCAL_M 0x3FFU // HR_ADC Post Processing Block 1 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBCONFIG register
//
//*************************************************************************************************
#define HR_ADC_PPB2CONFIG_CONFIG_S   0U
#define HR_ADC_PPB2CONFIG_CONFIG_M   0x1fU // HR_ADC Post Processing Block 2 Configuration
#define HR_ADC_PPB2CONFIG_TWOSCOMPEN 0x20U // HR_ADC Post Processing Block 2 Two's Complement Enable
#define HR_ADC_PPB2CONFIG_CBCEN      0x40U // HR_ADC Post Processing Block 2 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBSTAMP register
//
//*************************************************************************************************
#define HR_ADC_PPB2STAMP_DLYSTAMP_S 0U
#define HR_ADC_PPB2STAMP_DLYSTAMP_M 0xFFFU // HR_ADC Post Processing Block 2 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFREF register
//
//*************************************************************************************************
#define HR_ADC_PPB2OFFREF_OFFREF_S 0U
#define HR_ADC_PPB2OFFREF_OFFREF_M 0xFFFFU // HR_ADC Post Processing Block 2 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPHI register
//
//*************************************************************************************************
#define HR_ADC_PPB2TRIPHI_LIMITHI_S 0U
#define HR_ADC_PPB2TRIPHI_LIMITHI_M 0xFFFU  // HR_ADC Post Processing Block 2 Trip High Limit
#define HR_ADC_PPB2TRIPHI_HSIGN     0x1000U // HR_ADC Post Processing Block 2 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPLO register
//
//*************************************************************************************************
#define HR_ADC_PPB2TRIPLO_LIMITLO_S  0U
#define HR_ADC_PPB2TRIPLO_LIMITLO_M  0xFFFU  // HR_ADC Post Processing Block 2 Trip Low Limit
#define HR_ADC_PPB2TRIPLO_LSIGN      0x1000U // HR_ADC Post Processing Block 2 Low Limit Sign Bit
#define HR_ADC_PPB2TRIPLO_REQSTAMP_S 20U
#define HR_ADC_PPB2TRIPLO_REQSTAMP_M \
    0xFFF00000U // HR_ADC Post Processing Block 2 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFCAL register
//
//*************************************************************************************************
#define HR_ADC_PPB2OFFCAL_OFFCAL_S 0U
#define HR_ADC_PPB2OFFCAL_OFFCAL_M 0x3FFU // HR_ADC Post Processing Block 2 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBCONFIG register
//
//*************************************************************************************************
#define HR_ADC_PPB3CONFIG_CONFIG_S   0U
#define HR_ADC_PPB3CONFIG_CONFIG_M   0x1fU // HR_ADC Post Processing Block 3 Configuration
#define HR_ADC_PPB3CONFIG_TWOSCOMPEN 0x20U // HR_ADC Post Processing Block 3 Two's Complement Enable
#define HR_ADC_PPB3CONFIG_CBCEN      0x40U // HR_ADC Post Processing Block 3 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBSTAMP register
//
//*************************************************************************************************
#define HR_ADC_PPB3STAMP_DLYSTAMP_S 0U
#define HR_ADC_PPB3STAMP_DLYSTAMP_M 0xFFFU // HR_ADC Post Processing Block 3 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFREF register
//
//*************************************************************************************************
#define HR_ADC_PPB3OFFREF_OFFREF_S 0U
#define HR_ADC_PPB3OFFREF_OFFREF_M 0xFFFFU // HR_ADC Post Processing Block 3 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPHI register
//
//*************************************************************************************************
#define HR_ADC_PPB3TRIPHI_LIMITHI_S 0U
#define HR_ADC_PPB3TRIPHI_LIMITHI_M 0xFFFU  // HR_ADC Post Processing Block 3 Trip High Limit
#define HR_ADC_PPB3TRIPHI_HSIGN     0x1000U // HR_ADC Post Processing Block 3 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPLO register
//
//*************************************************************************************************
#define HR_ADC_PPB3TRIPLO_LIMITLO_S  0U
#define HR_ADC_PPB3TRIPLO_LIMITLO_M  0xFFFU  // HR_ADC Post Processing Block 3 Trip Low Limit
#define HR_ADC_PPB3TRIPLO_LSIGN      0x1000U // HR_ADC Post Processing Block 3 Low Limit Sign Bit
#define HR_ADC_PPB3TRIPLO_REQSTAMP_S 20U
#define HR_ADC_PPB3TRIPLO_REQSTAMP_M \
    0xFFF00000U // HR_ADC Post Processing Block 3 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFCAL register
//
//*************************************************************************************************
#define HR_ADC_PPB3OFFCAL_OFFCAL_S 0U
#define HR_ADC_PPB3OFFCAL_OFFCAL_M 0x3FFU // HR_ADC Post Processing Block 3 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBCONFIG register
//
//*************************************************************************************************
#define HR_ADC_PPB4CONFIG_CONFIG_S   0U
#define HR_ADC_PPB4CONFIG_CONFIG_M   0x1fU // HR_ADC Post Processing Block 4 Configuration
#define HR_ADC_PPB4CONFIG_TWOSCOMPEN 0x20U // HR_ADC Post Processing Block 4 Two's Complement Enable
#define HR_ADC_PPB4CONFIG_CBCEN      0x40U // HR_ADC Post Processing Block 4 Cycle By Cycle Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBSTAMP register
//
//*************************************************************************************************
#define HR_ADC_PPB4STAMP_DLYSTAMP_S 0U
#define HR_ADC_PPB4STAMP_DLYSTAMP_M 0xFFFU // HR_ADC Post Processing Block 4 Delay Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFREF register
//
//*************************************************************************************************
#define HR_ADC_PPB4OFFREF_OFFREF_S 0U
#define HR_ADC_PPB4OFFREF_OFFREF_M 0xFFFFU // HR_ADC Post Processing Block 4 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPHI register
//
//*************************************************************************************************
#define HR_ADC_PPB4TRIPHI_LIMITHI_S 0U
#define HR_ADC_PPB4TRIPHI_LIMITHI_M 0xFFFU  // HR_ADC Post Processing Block 4 Trip High Limit
#define HR_ADC_PPB4TRIPHI_HSIGN     0x1000U // HR_ADC Post Processing Block 4 High Limit Sign Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBTRIPLO register
//
//*************************************************************************************************
#define HR_ADC_PPB4TRIPLO_LIMITLO_S  0U
#define HR_ADC_PPB4TRIPLO_LIMITLO_M  0xFFFU  // HR_ADC Post Processing Block 4 Trip Low Limit
#define HR_ADC_PPB4TRIPLO_LSIGN      0x1000U // HR_ADC Post Processing Block 4 Low Limit Sign Bit
#define HR_ADC_PPB4TRIPLO_REQSTAMP_S 20U
#define HR_ADC_PPB4TRIPLO_REQSTAMP_M \
    0xFFF00000U // HR_ADC Post Processing Block 4 Request Time Stamp

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPBOFFCAL register
//
//*************************************************************************************************
#define HR_ADC_PPB4OFFCAL_OFFCAL_S 0U
#define HR_ADC_PPB4OFFCAL_OFFCAL_M 0x3FFU // HR_ADC Post Processing Block 4 Offset Correction

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPB1RESULT register
//
//*************************************************************************************************
#define HR_ADC_PPB1RESULT_PPBRESULT_S 0U
#define HR_ADC_PPB1RESULT_PPBRESULT_M 0xFFFU // HR_ADC Post Processing Block 1 Result
#define HR_ADC_PPB1RESULT_SIGN_S      12U
#define HR_ADC_PPB1RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPB2RESULT register
//
//*************************************************************************************************
#define HR_ADC_PPB2RESULT_PPBRESULT_S 0U
#define HR_ADC_PPB2RESULT_PPBRESULT_M 0xFFFU // HR_ADC Post Processing Block 2 Result
#define HR_ADC_PPB2RESULT_SIGN_S      12U
#define HR_ADC_PPB2RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPB3RESULT register
//
//*************************************************************************************************
#define HR_ADC_PPB3RESULT_PPBRESULT_S 0U
#define HR_ADC_PPB3RESULT_PPBRESULT_M 0xFFFU // HR_ADC Post Processing Block 3 Result
#define HR_ADC_PPB3RESULT_SIGN_S      12U
#define HR_ADC_PPB3RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCPPB4RESULT register
//
//*************************************************************************************************
#define HR_ADC_PPB4RESULT_PPBRESULT_S 0U
#define HR_ADC_PPB4RESULT_PPBRESULT_M 0xFFFU // HR_ADC Post Processing Block 4 Result
#define HR_ADC_PPB4RESULT_SIGN_S      12U
#define HR_ADC_PPB4RESULT_SIGN_M      0xFFFFF000U // Sign Extended Bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the HR_ADCSOCFRC1 register
//
//*************************************************************************************************
#define HR_ADC_SOCFRC1_SOC0  0x1U     // SOC0 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC1  0x2U     // SOC1 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC2  0x4U     // SOC2 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC3  0x8U     // SOC3 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC4  0x10U    // SOC4 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC5  0x20U    // SOC5 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC6  0x40U    // SOC6 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC7  0x80U    // SOC7 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC8  0x100U   // SOC8 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC9  0x200U   // SOC9 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC10 0x400U   // SOC10 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC11 0x800U   // SOC11 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC12 0x1000U  // SOC12 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC13 0x2000U  // SOC13 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC14 0x4000U  // SOC14 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC15 0x8000U  // SOC15 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC16 0x10000U // SOC16 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC17 0x20000U // SOC17 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC18 0x40000U // SOC18 Force Start of Conversion Bit
#define HR_ADC_SOCFRC1_SOC19 0x80000U // SOC19 Force Start of Conversion Bit
//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define HR_ADC_NUM_INTERRUPTS 1U

#define HR_ADC_SOCxCTL_OFFSET_BASE    HR_ADC_O_SOC0CTL
#define HR_ADC_RESULTx_OFFSET_BASE    HR_ADC_O_RESULT0
#define HR_ADC_INTSELxNy_OFFSET_BASE  HR_ADC_O_INTSEL1N2
#define HR_ADC_PPBxRESULT_OFFSET_BASE (HR_ADC_O_PPB2RESULT - HR_ADC_O_PPB1RESULT)

#define HR_ADC_PPBxCONFIG_STEP (HR_ADC_O_PPB2CONFIG - HR_ADC_O_PPB1CONFIG)
#define HR_ADC_PPBxTRIPHI_STEP (HR_ADC_O_PPB2TRIPHI - HR_ADC_O_PPB1TRIPHI)
#define HR_ADC_PPBxTRIPLO_STEP (HR_ADC_O_PPB2TRIPLO - HR_ADC_O_PPB1TRIPLO)
#define HR_ADC_PPBxSTAMP_STEP  (HR_ADC_O_PPB2STAMP - HR_ADC_O_PPB1STAMP)
#define HR_ADC_PPBxOFFCAL_STEP (HR_ADC_O_PPB2OFFCAL - HR_ADC_O_PPB1OFFCAL)
#define HR_ADC_PPBxOFFREF_STEP (HR_ADC_O_PPB2OFFREF - HR_ADC_O_PPB1OFFREF)

#define HR_ADC_PPBTRIP_MASK \
    ((uint32_t)HR_ADC_PPB1TRIPHI_LIMITHI_M | (uint32_t)HR_ADC_PPB1TRIPHI_HSIGN)
// #define HR_ADC_INT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x710D5))
// #define HR_ADC_INT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x710D6))
// #define HR_ADC_EXT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x710D3))
// #define HR_ADC_EXT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x710D4))

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Values that can be passed to HR_ADC_enablePPBEvent(), HR_ADC_disablePPBEvent(),
// HR_ADC_enablePPBEventInterrupt(), HR_ADC_disablePPBEventInterrupt(), and
// HR_ADC_clearPPBEventStatus() as the intFlags and evtFlags parameters. They also
// make up the enumerated bit field returned by HR_ADC_getPPBEventStatus().
//
//*****************************************************************************
#define HR_ADC_EVT_TRIPHI 0x0001U //!< Trip High Event
#define HR_ADC_EVT_TRIPLO 0x0002U //!< Trip Low Event
#define HR_ADC_EVT_ZERO   0x0004U //!< Zero Crossing Event

//*****************************************************************************
//
// Values that can be passed to HR_ADC_forceMultipleSOC() as socMask parameter.
// These values can be OR'd together to trigger multiple SOCs at a time.
//
//*****************************************************************************
#define HR_ADC_FORCE_SOC0  0x0001U  //!< SW trigger HR_ADC SOC 0
#define HR_ADC_FORCE_SOC1  0x0002U  //!< SW trigger HR_ADC SOC 1
#define HR_ADC_FORCE_SOC2  0x0004U  //!< SW trigger HR_ADC SOC 2
#define HR_ADC_FORCE_SOC3  0x0008U  //!< SW trigger HR_ADC SOC 3
#define HR_ADC_FORCE_SOC4  0x0010U  //!< SW trigger HR_ADC SOC 4
#define HR_ADC_FORCE_SOC5  0x0020U  //!< SW trigger HR_ADC SOC 5
#define HR_ADC_FORCE_SOC6  0x0040U  //!< SW trigger HR_ADC SOC 6
#define HR_ADC_FORCE_SOC7  0x0080U  //!< SW trigger HR_ADC SOC 7
#define HR_ADC_FORCE_SOC8  0x0100U  //!< SW trigger HR_ADC SOC 8
#define HR_ADC_FORCE_SOC9  0x0200U  //!< SW trigger HR_ADC SOC 9
#define HR_ADC_FORCE_SOC10 0x0400U  //!< SW trigger HR_ADC SOC 10
#define HR_ADC_FORCE_SOC11 0x0800U  //!< SW trigger HR_ADC SOC 11
#define HR_ADC_FORCE_SOC12 0x1000U  //!< SW trigger HR_ADC SOC 12
#define HR_ADC_FORCE_SOC13 0x2000U  //!< SW trigger HR_ADC SOC 13
#define HR_ADC_FORCE_SOC14 0x4000U  //!< SW trigger HR_ADC SOC 14
#define HR_ADC_FORCE_SOC15 0x8000U  //!< SW trigger HR_ADC SOC 15
#define HR_ADC_FORCE_SOC16 0x10000U //!< SW trigger HR_ADC SOC 16
#define HR_ADC_FORCE_SOC17 0x20000U //!< SW trigger HR_ADC SOC 17
#define HR_ADC_FORCE_SOC18 0x40000U //!< SW trigger HR_ADC SOC 18
#define HR_ADC_FORCE_SOC19 0x80000U //!< SW trigger HR_ADC SOC 19

#endif
// ####
#endif
