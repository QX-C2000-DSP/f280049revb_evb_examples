#ifndef F28004X_SYSCTRL_H
#define F28004X_SYSCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// DEV_CFG Register Bit Definitions:
//---------------------------------------------------------------------------

struct SOFTPRES0_BITS
{
    Uint32 CPU2 : 1; // [0]
};

union SOFTPRES0_REG
{
    Uint32 all;
    struct SOFTPRES0_BITS bit;
};

struct SOFTPRES2_BITS
{
    Uint32 EPWM1  : 1;  // [0]
    Uint32 EPWM2  : 1;  // [1]
    Uint32 EPWM3  : 1;  // [2]
    Uint32 EPWM4  : 1;  // [3]
    Uint32 EPWM5  : 1;  // [4]
    Uint32 EPWM6  : 1;  // [5]
    Uint32 EPWM7  : 1;  // [6]
    Uint32 EPWM8  : 1;  // [7]
    Uint32 EPWM9  : 1;  // [8]
    Uint32 EPWM10 : 1;  // [9]
    Uint32 EPWM11 : 1;  // [10]
    Uint32 rsvd4  : 1;  // 11 Reserved
    Uint32 rsvd5  : 1;  // 12 Reserved
    Uint32 rsvd6  : 1;  // 13 Reserved
    Uint32 rsvd7  : 1;  // 14 Reserved
    Uint32 rsvd8  : 1;  // 15 Reserved
    Uint32 rsvd9  : 16; // 31:16 Reserved
};

union SOFTPRES2_REG
{
    Uint32 all;
    struct SOFTPRES2_BITS bit;
};

struct SOFTPRES3_BITS
{                      // bits description
    Uint32 ECAP1 : 1;  // 0 ECAP1 software reset bit
    Uint32 ECAP2 : 1;  // 1 ECAP2 software reset bit
    Uint32 ECAP3 : 1;  // 2 ECAP3 software reset bit
    Uint32 ECAP4 : 1;  // 3 ECAP4 software reset bit
    Uint32 ECAP5 : 1;  // 4 ECAP5 software reset bit
    Uint32 ECAP6 : 1;  // 5 ECAP6 software reset bit
    Uint32 ECAP7 : 1;  // 6 ECAP7 software reset bit
    Uint32 rsvd1 : 1;  // 7 Reserved
    Uint32 rsvd2 : 8;  // 15:8 Reserved
    Uint32 rsvd3 : 16; // 31:16 Reserved
};

union SOFTPRES3_REG
{
    Uint32 all;
    struct SOFTPRES3_BITS bit;
};

struct SOFTPRES4_BITS
{                      // bits description
    Uint32 EQEP1 : 1;  // 0 EQEP1 software reset bit
    Uint32 EQEP2 : 1;  // 1 EQEP2 software reset bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 16; // 31:16 Reserved
};

union SOFTPRES4_REG
{
    Uint32 all;
    struct SOFTPRES4_BITS bit;
};

struct SOFTPRES6_BITS
{                      // bits description
    Uint32 SD1   : 1;  // 0 SD1 software reset bit
    Uint32 rsvd1 : 1;  // 1 Reserved
    Uint32 rsvd2 : 1;  // 2 Reserved
    Uint32 rsvd3 : 1;  // 3 Reserved
    Uint32 rsvd4 : 1;  // 4 Reserved
    Uint32 rsvd5 : 1;  // 5 Reserved
    Uint32 rsvd6 : 1;  // 6 Reserved
    Uint32 rsvd7 : 1;  // 7 Reserved
    Uint32 rsvd8 : 8;  // 15:8 Reserved
    Uint32 rsvd9 : 16; // 31:16 Reserved
};

union SOFTPRES6_REG
{
    Uint32 all;
    struct SOFTPRES6_BITS bit;
};

struct SOFTPRES7_BITS
{                      // bits description
    Uint32 SCI_A : 1;  // 0 SCI_A software reset bit
    Uint32 SCI_B : 1;  // 1 SCI_B software reset bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 16; // 31:16 Reserved
};

union SOFTPRES7_REG
{
    Uint32 all;
    struct SOFTPRES7_BITS bit;
};

struct SOFTPRES8_BITS
{                      // bits description
    Uint32 SPI_A : 1;  // 0 SPI_A software reset bit
    Uint32 SPI_B : 1;  // 1 SPI_B software reset bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 1;  // 16 Reserved
    Uint32 rsvd5 : 1;  // 17 Reserved
    Uint32 rsvd6 : 14; // 31:18 Reserved
};

union SOFTPRES8_REG
{
    Uint32 all;
    struct SOFTPRES8_BITS bit;
};

struct SOFTPRES9_BITS
{                        // bits description
    Uint32 I2C_A   : 1;  // 0 I2C_A software reset bit
    Uint32 PMBUS_A : 1;  // 1 PMBUS_A software reset bit
    Uint32 rsvd2   : 14; // 15:2 Reserved
    Uint32 rsvd3   : 16; // 31:16 Reserved
};

union SOFTPRES9_REG
{
    Uint32 all;
    struct SOFTPRES9_BITS bit;
};

struct SOFTPRES10_BITS
{                      // bits description
    Uint32 CAN_A : 1;  // 0 CAN_A software reset bit
    Uint32 CAN_B : 1;  // 1 CAN_B software reset bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 16; // 31:16 Reserved
};

union SOFTPRES10_REG
{
    Uint32 all;
    struct SOFTPRES10_BITS bit;
};

struct SOFTPRES13_BITS
{
    Uint32 ADC_A    : 1; // [0]
    Uint32 ADC_B    : 1; // [1]
    Uint32 ADC_C    : 1; // [2]
    Uint32 ADC_G    : 1; // [3]
    Uint32 ADC_H    : 1; // [4]
    Uint32 rsvd     : 1; // [5]
    Uint32 ADC_A_HR : 1; // [6]
    Uint32 ADC_B_HR : 1; // [7]
    Uint32 ADC_C_HR : 1; // [8]
};

union SOFTPRES13_REG
{
    Uint32 all;
    struct SOFTPRES13_BITS bit;
};

struct SOFTPRES14_BITS
{                       // bits description
    Uint32 CMPSS1 : 1;  // 0 CMPSS1 software reset bit
    Uint32 CMPSS2 : 1;  // 1 CMPSS2 software reset bit
    Uint32 CMPSS3 : 1;  // 2 CMPSS3 software reset bit
    Uint32 CMPSS4 : 1;  // 3 CMPSS4 software reset bit
    Uint32 CMPSS5 : 1;  // 4 CMPSS5 software reset bit
    Uint32 CMPSS6 : 1;  // 5 CMPSS6 software reset bit
    Uint32 CMPSS7 : 1;  // 6 CMPSS7 software reset bit
    Uint32 rsvd1  : 1;  // 7 Reserved
    Uint32 rsvd2  : 8;  // 15:8 Reserved
    Uint32 rsvd3  : 16; // 31:16 Reserved
};

union SOFTPRES14_REG
{
    Uint32 all;
    struct SOFTPRES14_BITS bit;
};

struct SOFTPRES15_BITS
{                      // bits description
    Uint32 PGA1  : 1;  // 0 PGA1 software reset bit
    Uint32 PGA2  : 1;  // 1 PGA2 software reset bit
    Uint32 PGA3  : 1;  // 2 PGA3 software reset bit
    Uint32 PGA4  : 1;  // 3 PGA4 software reset bit
    Uint32 PGA5  : 1;  // 4 PGA5 software reset bit
    Uint32 PGA6  : 1;  // 5 PGA6 software reset bit
    Uint32 PGA7  : 1;  // 6 PGA7 software reset bit
    Uint32 rsvd1 : 1;  // 7 Reserved
    Uint32 rsvd2 : 8;  // 15:8 Reserved
    Uint32 rsvd3 : 16; // 31:16 Reserved
};

union SOFTPRES15_REG
{
    Uint32 all;
    struct SOFTPRES15_BITS bit;
};

struct SOFTPRES16_BITS
{
    Uint32 DAC_A : 1; // [0]
    Uint32 DAC_B : 1; // [1]
};

union SOFTPRES16_REG
{
    Uint32 all;
    struct SOFTPRES16_BITS bit;
};

struct SOFTPRES19_BITS
{
    Uint32 LIN_A : 1; // [0]
    Uint32 EMIF  : 1; // [1]
};

union SOFTPRES19_REG
{
    Uint32 all;
    struct SOFTPRES19_BITS bit;
};

struct HARDWARERES0_BITS
{
    Uint32 reserve1 : 32; // [0]
};

union HARDWARERES0_REG
{
    Uint32 all;
    struct HARDWARERES0_BITS bit;
};

struct HARDWARERES2_BITS
{
    Uint32 EPWM1_EALLOW  : 1; // [0]
    Uint32 EPWM2_EALLOW  : 1; // [1]
    Uint32 EPWM3_EALLOW  : 1; // [2]
    Uint32 EPWM4_EALLOW  : 1; // [3]
    Uint32 EPWM5_EALLOW  : 1; // [4]
    Uint32 EPWM6_EALLOW  : 1; // [5]
    Uint32 EPWM7_EALLOW  : 1; // [6]
    Uint32 EPWM8_EALLOW  : 1; // [7]
    Uint32 EPWM9_EALLOW  : 1; // [8]
    Uint32 EPWM10_EALLOW : 1; // [9]
    Uint32 EPWM11_EALLOW : 1; // [10]
    Uint32 EPWM12_EALLOW : 1; // [11]
};

union HARDWARERES2_REG
{
    Uint32 all;
    struct HARDWARERES2_BITS bit;
};

struct HARDWARERES3_BITS
{
    Uint32 ECAP1_EALLOW : 1; // [0]
    Uint32 ECAP2_EALLOW : 1; // [1]
    Uint32 ECAP3_EALLOW : 1; // [2]
    Uint32 ECAP4_EALLOW : 1; // [3]
    Uint32 ECAP5_EALLOW : 1; // [4]
    Uint32 ECAP6_EALLOW : 1; // [5]
    Uint32 ECAP7_EALLOW : 1; // [6]
};

union HARDWARERES3_REG
{
    Uint32 all;
    struct HARDWARERES3_BITS bit;
};

struct HARDWARERES4_BITS
{
    Uint32 EQEP1 : 1; // [0]
    Uint32 EQEP2 : 1; // [1]
};

union HARDWARERES4_REG
{
    Uint32 all;
    struct HARDWARERES4_BITS bit;
};

struct HARDWARERES6_BITS
{
    Uint32 SD1_EALLOW : 1; // [0]
};

union HARDWARERES6_REG
{
    Uint32 all;
    struct HARDWARERES6_BITS bit;
};

struct HARDWARERES7_BITS
{
    Uint32 SCI_A : 1; // [0]
    Uint32 SCI_B : 1; // [1]
};

union HARDWARERES7_REG
{
    Uint32 all;
    struct HARDWARERES7_BITS bit;
};

struct HARDWARERES8_BITS
{
    Uint32 SPI_A : 1; // [0]
    Uint32 SPI_B : 1; // [1]
};

union HARDWARERES8_REG
{
    Uint32 all;
    struct HARDWARERES8_BITS bit;
};

struct HARDWARERES9_BITS
{
    Uint32 I2C_A   : 1; // [0]
    Uint32 PMBUS_A : 1; // [1]
};

union HARDWARERES9_REG
{
    Uint32 all;
    struct HARDWARERES9_BITS bit;
};

struct HARDWARERES10_BITS
{
    Uint32 CAN_A : 1; // [0]
    Uint32 CAN_B : 1; // [1]
};

union HARDWARERES10_REG
{
    Uint32 all;
    struct HARDWARERES10_BITS bit;
};

struct HARDWARERES13_BITS
{
    Uint32 ADC_A_EALLOW    : 1; // [0]
    Uint32 ADC_B_EALLOW    : 1; // [1]
    Uint32 ADC_C_EALLOW    : 1; // [2]
    Uint32 ADC_G_EALLOW    : 1; // [3]
    Uint32 ADC_H_EALLOW    : 1; // [4]
    Uint32 rsvd            : 1; // [5]
    Uint32 ADC_A_HR_EALLOW : 1; // [6]
    Uint32 ADC_B_HR_EALLOW : 1; // [7]
    Uint32 ADC_C_HR_EALLOW : 1; // [8]
};

union HARDWARERES13_REG
{
    Uint32 all;
    struct HARDWARERES13_BITS bit;
};

struct HARDWARERES14_BITS
{
    Uint32 CMPSS1_EALLOW : 1; // [0]
    Uint32 CMPSS2_EALLOW : 1; // [1]
    Uint32 CMPSS3_EALLOW : 1; // [2]
    Uint32 CMPSS4_EALLOW : 1; // [3]
    Uint32 CMPSS5_EALLOW : 1; // [4]
    Uint32 CMPSS6_EALLOW : 1; // [5]
    Uint32 CMPSS7_EALLOW : 1; // [6]
};

union HARDWARERES14_REG
{
    Uint32 all;
    struct HARDWARERES14_BITS bit;
};

struct HARDWARERES15_BITS
{
    Uint32 PGA1_EALLOW : 1; // [0]
    Uint32 PGA2_EALLOW : 1; // [1]
    Uint32 PGA3_EALLOW : 1; // [2]
    Uint32 PGA4_EALLOW : 1; // [3]
    Uint32 PGA5_EALLOW : 1; // [4]
    Uint32 PGA6_EALLOW : 1; // [5]
    Uint32 PGA7_EALLOW : 1; // [6]
};

union HARDWARERES15_REG
{
    Uint32 all;
    struct HARDWARERES15_BITS bit;
};

struct HARDWARERES16_BITS
{
    Uint32 DAC_A_EALLOW : 1; // [0]
    Uint32 DAC_B_EALLOW : 1; // [1]
};

union HARDWARERES16_REG
{
    Uint32 all;
    struct HARDWARERES16_BITS bit;
};

struct HARDWARERES19_BITS
{
    Uint32 LIN_A               : 1; // [0]
    Uint32 EMIF                : 1; // [1]
    Uint32 FSI_EALLOW          : 1; // [2]
    Uint32 ANALOGSUBSYS_EALLOW : 1; // [3]
    Uint32 INPUTBAR_EALLOW     : 1; // [4]
    Uint32 EPWMBAR_EALLOW      : 1; // [5]
    Uint32 OUTPUTBAR_EALLOW    : 1; // [6]
    Uint32 SYSCTRL_EALLOW      : 1; // [7]
    Uint32 GPIOCTRL_EALLOW     : 1; // [8]
};

union HARDWARERES19_REG
{
    Uint32 all;
    struct HARDWARERES19_BITS bit;
};

struct CANFD_BITS
{
    Uint32 CANFD_A : 1; // [0]
    Uint32 CANFD_B : 1; // [1]
};

union CANFD_REG
{
    Uint32 all;
    struct CANFD_BITS bit;
};

struct FLASHREADY_BITS
{
    Uint32 FLASH_WR_READY : 1; // [0]
    Uint32 FLASH_RD_READY : 1; // [1]
};

union FLASHREADY_REG
{
    Uint32 all;
    struct FLASHREADY_BITS bit;
};

struct FLASHCLKDIV_BITS
{
    Uint32 CLK_FLASH_DIV : 16; // [0]
};

union FLASHCLKDIV_REG
{
    Uint32 all;
    struct FLASHCLKDIV_BITS bit;
};

struct EMU_SUSPEND_BITS
{
    Uint32 ADCA_EMU_SUSPEND  : 1; // [0]
    Uint32 ADCB_EMU_SUSPEND  : 1; // [1]
    Uint32 ADCC_EMU_SUSPEND  : 1; // [2]
    Uint32 EPWM1_EMU_SUPEND  : 1; // [3]
    Uint32 EPWM2_EMU_SUPEND  : 1; // [4]
    Uint32 EPWM3_EMU_SUPEND  : 1; // [5]
    Uint32 EPWM4_EMU_SUPEND  : 1; // [6]
    Uint32 EPWM5_EMU_SUPEND  : 1; // [7]
    Uint32 EPWM6_EMU_SUPEND  : 1; // [7]
    Uint32 EPWM7_EMU_SUPEND  : 1; // [9]
    Uint32 EPWM8_EMU_SUPEND  : 1; // [10]
    Uint32 EPWM9_EMU_SUPEND  : 1; // [11]
    Uint32 EPWM10_EMU_SUPEND : 1; // [12]
    Uint32 EPWM11_EMU_SUPEND : 1; // [13]
    Uint32 EPWM12_EMU_SUPEND : 1; // [14]
    Uint32 ECAP1_EMU_SUPEND  : 1; // [15]
    Uint32 ECAP2_EMU_SUPEND  : 1; // [16]
    Uint32 ECAP3_EMU_SUPEND  : 1; // [17]
    Uint32 ECAP4_EMU_SUPEND  : 1; // [18]
    Uint32 ECAP5_EMU_SUPEND  : 1; // [19]
    Uint32 ECAP6_EMU_SUPEND  : 1; // [20]
    Uint32 ECAP7_EMU_SUPEND  : 1; // [21]
    Uint32 EQEP0_EMU_SUPEND  : 1; // [22]
    Uint32 EQEP1_EMU_SUPEND  : 1; // [23]
};

union EMU_SUSPEND_REG
{
    Uint32 all;
    struct EMU_SUSPEND_BITS bit;
};

struct GSRAM_SEL_BITS
{
    Uint32 BANK0_SEL  : 1; // [0]
    Uint32 BANK1_SEL  : 1; // [1]
    Uint32 BANK2_SEL  : 1; // [2]
    Uint32 BANK3_SEL  : 1; // [3]
    Uint32 BANK4_SEL  : 1; // [4]
    Uint32 BANK5_SEL  : 1; // [5]
    Uint32 BANK6_SEL  : 1; // [6]
    Uint32 BANK7_SEL  : 1; // [7]
    Uint32 BANK8_SEL  : 1; // [8]
    Uint32 BANK9_SEL  : 1; // [9]
    Uint32 BANK10_SEL : 1; // [10]
    Uint32 BANK11_SEL : 1; // [11]
    Uint32 BANK12_SEL : 1; // [12]
    Uint32 BANK13_SEL : 1; // [13]
    Uint32 BANK14_SEL : 1; // [14]
    Uint32 BANK15_SEL : 1; // [15]
};

union GSRAM_SEL_REG
{
    Uint32 all;
    struct GSRAM_SEL_BITS bit;
};

struct FARRAM_SEL_BITS
{
    Uint32 BANK0_SEL : 1; // [0]
    Uint32 BANK1_SEL : 1; // [1]
    Uint32 BANK2_SEL : 1; // [2]
    Uint32 BANK3_SEL : 1; // [3]
    Uint32 BANK4_SEL : 1; // [4]
    Uint32 BANK5_SEL : 1; // [5]
    Uint32 BANK6_SEL : 1; // [6]
    Uint32 BANK7_SEL : 1; // [7]
};

union FARRAM_SEL_REG
{
    Uint32 all;
    struct FARRAM_SEL_BITS bit;
};

struct CPUFARRAM_CTR_BITS
{
    Uint32 PREFETCH_CTRL : 1;  // [0]
    Uint32 CLEAR_CTRL    : 1;  // [1]
    Uint32 RSV           : 30; // [32:2]
};

union CPUFARRAM_CTR_REG
{
    Uint32 all;
    struct CPUFARRAM_CTR_BITS bit;
};

struct DEV_CFG_REGS
{
    Uint32 rsvd0[16];                       // offset:0x0 ~ 0x40
    union SOFTPRES0_REG SOFTPRES0;          // offset:0x40
    union SOFTPRES2_REG SOFTPRES2;          // offset:0x44
    union SOFTPRES3_REG SOFTPRES3;          // offset:0x48
    union SOFTPRES4_REG SOFTPRES4;          // offset:0x4C
    union SOFTPRES6_REG SOFTPRES6;          // offset:0x50
    union SOFTPRES7_REG SOFTPRES7;          // offset:0x54
    union SOFTPRES8_REG SOFTPRES8;          // offset:0x58
    union SOFTPRES9_REG SOFTPRES9;          // offset:0x5C
    union SOFTPRES10_REG SOFTPRES10;        // offset:0x60
    union SOFTPRES13_REG SOFTPRES13;        // offset:0x64
    union SOFTPRES14_REG SOFTPRES14;        // offset:0x68
    union SOFTPRES15_REG SOFTPRES15;        // offset:0x6C
    union SOFTPRES16_REG SOFTPRES16;        // offset:0x70
    union SOFTPRES19_REG SOFTPRES19;        // offset:0x74
    Uint32 rsvd1[50];                       // offset:0x13C~0x78
    union HARDWARERES0_REG HARDWARERES0;    // offset:0x140
    union HARDWARERES2_REG HARDWARERES2;    // offset:0x144
    union HARDWARERES3_REG HARDWARERES3;    // offset:0x148
    union HARDWARERES4_REG HARDWARERES4;    // offset:0x14C
    union HARDWARERES6_REG HARDWARERES6;    // offset:0x150
    union HARDWARERES7_REG HARDWARERES7;    // offset:0x154
    union HARDWARERES8_REG HARDWARERES8;    // offset:0x158
    union HARDWARERES9_REG HARDWARERES9;    // offset:0x15C
    union HARDWARERES10_REG HARDWARERES10;  // offset:0x160
    union HARDWARERES13_REG HARDWARERES13;  // offset:0x164
    union HARDWARERES14_REG HARDWARERES14;  // offset:0x168
    union HARDWARERES15_REG HARDWARERES15;  // offset:0x16C
    union HARDWARERES16_REG HARDWARERES16;  // offset:0x170
    union HARDWARERES19_REG HARDWARERES19;  // offset:0x174
    Uint32 rsvd2[6];                        // offset:0x178~0x18C
    union CANFD_REG CANFD;                  // offset:0x190
    Uint32 rsvd3[3];                        // offset:0x194~0x19C
    union FLASHCLKDIV_REG FLASHCLKDIV;      // offset:0x1A0
    Uint32 rsvd4[2];                        // offset:0x1A4~0x1A8
    union EMU_SUSPEND_REG EMU_SUSPEND;      // offset:0x1AC
    Uint32 rsvd5[44];                       // offset:0x1B0~0x25C
    Uint32 rsvd6[6];                        // offset:0x260~0x274
    Uint32 rsvd7[34];                       // offset:0x278~0x2FC
    Uint32 rsvd8[8];                        // offset:0x300~0x31C
    union GSRAM_SEL_REG GSRAM_SEL;          // offset:0x320
    union FARRAM_SEL_REG FARRAM_SEL;        // offset:0x324
    union CPUFARRAM_CTR_REG CPU1FARRAM_CTR; // offset:0x328
    union CPUFARRAM_CTR_REG CPU2FARRAM_CTR; // offset:0x32C
    Uint32 rsvd9[6];
    Uint32 DMA_CH1_BLK_DONE_INT_COUNT; // offset:0x348;
    Uint32 DMA_CH2_BLK_DONE_INT_COUNT; // offset:0x34C;
    Uint32 DMA_CH3_BLK_DONE_INT_COUNT; // offset:0x350;
    Uint32 DMA_CH4_BLK_DONE_INT_COUNT; // offset:0x354;
    Uint32 DMA_CH5_BLK_DONE_INT_COUNT; // offset:0x358;
    Uint32 DMA_CH6_BLK_DONE_INT_COUNT; // offset:0x35C;
};

//---------------------------------------------------------------------------
// CLK_CFG Register Bit Definitions:
//---------------------------------------------------------------------------

struct CLKSRCCTL1_BITS
{                             // bits description
    Uint32 OSCCLKSRCSEL : 2;  // 1:0 OSCCLK Source Select Bit
    Uint32 rsvd1        : 1;  // 2 Reserved
    Uint32 INTOSC2OFF   : 1;  // 3 Internal Oscillator 2 Off Bit
    Uint32 rsvd2        : 1;  // 4 Reserved
    Uint32 WDHALTI      : 1;  // 5 Watchdog HALT Mode Ignore Bit
    Uint32 rsvd3        : 10; // 15:6 Reserved
    Uint32 rsvd4        : 16; // 31:16 Reserved
};

union CLKSRCCTL1_REG
{
    Uint32 all;
    struct CLKSRCCTL1_BITS bit;
};

struct CLKSRCCTL2_BITS
{                            // bits description
    Uint32 rsvd1       : 2;  // 1:0 Reserved
    Uint32 CANABCLKSEL : 2;  // 3:2 CANA Bit Clock Source Select Bit
    Uint32 CANBBCLKSEL : 2;  // 5:4 CANB Bit Clock Source Select Bit
    Uint32 rsvd2       : 2;  // 7:6 Reserved
    Uint32 rsvd3       : 2;  // 9:8 Reserved
    Uint32 rsvd4       : 6;  // 15:10 Reserved
    Uint32 rsvd5       : 16; // 31:16 Reserved
};

union CLKSRCCTL2_REG
{
    Uint32 all;
    struct CLKSRCCTL2_BITS bit;
};

struct CLKSRCCTL3_BITS
{                           // bits description
    Uint32 XCLKOUTSEL : 3;  // 2:0 XCLKOUT Source Select Bit
    Uint32 rsvd1      : 13; // 15:3 Reserved
    Uint32 rsvd2      : 16; // 31:16 Reserved
};

union CLKSRCCTL3_REG
{
    Uint32 all;
    struct CLKSRCCTL3_BITS bit;
};

struct SYSPLLCTL1_BITS
{                         // bits description
    Uint32 PLLEN    : 1;  // 0 SYSPLL enable/disable bit
    Uint32 PLLCLKEN : 1;  // 1 SYSPLL bypassed or included in the PLLSYSCLK path
    Uint32 rsvd1    : 14; // 15:2 Reserved
    Uint32 rsvd2    : 16; // 31:16 Reserved
};

union SYSPLLCTL1_REG
{
    Uint32 all;
    struct SYSPLLCTL1_BITS bit;
};

struct SYSPLLMULT_BITS
{                      // bits description
    Uint32 IDIV  : 4;  // 3:0 PLL Input Divider Paramenter
    Uint32 rsvd0 : 23; // 26:4 reserve
    Uint32 RST   : 1;  // 27 enable Reset Mode
};

union SYSPLLMULT_REG
{
    Uint32 all;
    struct SYSPLLMULT_BITS bit;
};

struct SYSPLLSTS_BITS
{                      // bits description
    Uint32 LOCKS : 1;  // 0 SYSPLL Lock Status Bit
    Uint32 SLIPS : 1;  // 1 SYSPLL Slip Status Bit
    Uint32 rsvd1 : 14; // 15:2 Reserved
    Uint32 rsvd2 : 16; // 31:16 Reserved
};

union SYSPLLSTS_REG
{
    Uint32 all;
    struct SYSPLLSTS_BITS bit;
};

struct SYSCLKDIVSEL_BITS
{                             // bits description
    Uint32 PLLSYSCLKDIV : 6;  // 5:0 PLLSYSCLK Divide Select
    Uint32 rsvd1        : 10; // 15:6 Reserved
    Uint32 rsvd2        : 16; // 31:16 Reserved
};

union SYSCLKDIVSEL_REG
{
    Uint32 all;
    struct SYSCLKDIVSEL_BITS bit;
};

struct XCLKOUTDIVSEL_BITS
{                           // bits description
    Uint32 XCLKOUTDIV : 2;  // 1:0 XCLKOUT Divide Select
    Uint32 rsvd1      : 14; // 15:2 Reserved
    Uint32 rsvd2      : 16; // 31:16 Reserved
};

union XCLKOUTDIVSEL_REG
{
    Uint32 all;
    struct XCLKOUTDIVSEL_BITS bit;
};

struct LOSPCP_BITS
{                          // bits description
    Uint32 LSPCLKDIV : 3;  // 2:0 LSPCLK Divide Select
    Uint32 rsvd1     : 13; // 15:3 Reserved
    Uint32 rsvd2     : 16; // 31:16 Reserved
};

union LOSPCP_REG
{
    Uint32 all;
    struct LOSPCP_BITS bit;
};

struct MCDCR_BITS
{                        // bits description
    Uint32 MCLKSTS : 1;  // 0 Missing Clock Status Bit
    Uint32 MCLKCLR : 1;  // 1 Missing Clock Clear Bit
    Uint32 MCLKOFF : 1;  // 2 Missing Clock Detect Off Bit
    Uint32 OSCOFF  : 1;  // 3 Oscillator Clock Off Bit
    Uint32 rsvd1   : 12; // 15:4 Reserved
    Uint32 rsvd2   : 16; // 31:16 Reserved
};

union MCDCR_REG
{
    Uint32 all;
    struct MCDCR_BITS bit;
};

struct X1CNT_BITS
{                      // bits description
    Uint32 X1CNT : 10; // 9:0 X1 Counter
    Uint32 rsvd1 : 6;  // 15:10 Reserved
    Uint32 CLR   : 1;  // 16 X1 Counter Clear
    Uint32 rsvd2 : 15; // 31:17 Reserved
};

union X1CNT_REG
{
    Uint32 all;
    struct X1CNT_BITS bit;
};

struct XTALCR_BITS
{                       // bits description
    Uint32 OSCOFF : 1;  // 0 XTAL Oscillator powered-down
    Uint32 SE     : 1;  // 1 XTAL Oscilator in Single-Ended mode
    Uint32 rsvd1  : 1;  // 2 Reserved
    Uint32 rsvd2  : 13; // 15:3 Reserved
    Uint32 rsvd3  : 16; // 31:16 Reserved
};

union XTALCR_REG
{
    Uint32 all;
    struct XTALCR_BITS bit;
};

struct CLKSTATUS_REG_BITS
{
    Uint32 OSC1READLY : 1;
    Uint32 OSC2READLY : 1;
    Uint32 X1READLY   : 1;
};

union CLKSTATUS_REG
{
    Uint32 all;
    struct CLKSTATUS_REG_BITS bit;
};

struct CLK_CFG_REGS
{
    union CLKSRCCTL1_REG CLKSRCCTL1; // offset:0x00 Clock Source Control register-1
    union CLKSRCCTL2_REG CLKSRCCTL2; // offset:0x04 Clock Source Control register-2
    union CLKSRCCTL3_REG CLKSRCCTL3; // offset:0x08 Clock Source Control register-3
    union SYSPLLCTL1_REG SYSPLLCTL1; // offset:0x0C SYSPLL Control register-1
    union SYSPLLMULT_REG SYSPLLMULT; // offset:0x10 SYSPLL Multiplier register
    Uint32 SYSPLL_IMULT_L;           // offset:0x14 PLL Mult Paramenter, LOW 32 bit(bit set style)
    Uint32 SYSPLL_IMULT_H;           // offset:0x18 PLL Mult Paramenter, HIGH 32 bit(bit set style)
    Uint32 SYSPLL_ODIV;              // offset:0x1C PLL Output Divider Paramenter (bit set style)
    union SYSPLLSTS_REG SYSPLLSTS;   // offest:0x20 SYSPLL Status register
    union SYSCLKDIVSEL_REG SYSCLKDIVSEL;   // offset:0x24 System Clock Divider Select register
    union XCLKOUTDIVSEL_REG XCLKOUTDIVSEL; // offset:0x28 XCLKOUT Divider Select register
    union LOSPCP_REG LOSPCP;               // offset:0x2C Low Speed Clock Source Prescalar
    union MCDCR_REG MCDCR;                 // offset:0x30 Missing Clock Detect Control Register
    union X1CNT_REG X1CNT;                 // offset:0x34 10-bit Counter on X1 Clock
    union XTALCR_REG XTALCR;               // offset:0x38 XTAL Control Register
    union CLKSTATUS_REG CLKSTATUS;         // offset:0x3C CLK Status Register
};

//---------------------------------------------------------------------------
// CPU_SYS Register Bit Definitions:
//---------------------------------------------------------------------------

struct PCLKCR0_BITS
{
    Uint32 CPU2       : 1; // [0]
    Uint32 rsvd1      : 1; // [1]
    Uint32 DMA        : 1; // [2]
    Uint32 rsvd2      : 2; // [4:3]
    Uint32 CPUTIMER0  : 1; // [5]
    Uint32 CPUTIMER1  : 1; // [6]
    Uint32 CPUTIMER2  : 1; // [7]
    Uint32 CPU2TIMER0 : 1; // [8]
    Uint32 CPU2TIMER1 : 1; // [9]
    Uint32 CPU2TIMER2 : 1; // [10]
    Uint32 rsvd3      : 6; // [16:11]
    Uint32 HRPWM      : 1; // [17] (no use, just for  compatible TI)
    Uint32 TBCLKSYNC  : 1; // [18]
};

union PCLKCR0_REG
{
    Uint32 all;
    struct PCLKCR0_BITS bit;
};

struct PCLKCR2_BITS
{
    Uint32 EPWM1  : 1;  // [0]
    Uint32 EPWM2  : 1;  // [1]
    Uint32 EPWM3  : 1;  // [2]
    Uint32 EPWM4  : 1;  // [3]
    Uint32 EPWM5  : 1;  // [4]
    Uint32 EPWM6  : 1;  // [5]
    Uint32 EPWM7  : 1;  // [6]
    Uint32 EPWM8  : 1;  // [7]
    Uint32 EPWM9  : 1;  // [8]
    Uint32 EPWM10 : 1;  // [9]
    Uint32 EPWM11 : 1;  // [10]
    Uint32 EPWM12 : 1;  // [11]
    Uint32 rsvd5  : 1;  // 12 Reserved
    Uint32 rsvd6  : 1;  // 13 Reserved
    Uint32 rsvd7  : 1;  // 14 Reserved
    Uint32 rsvd8  : 1;  // 15 Reserved
    Uint32 rsvd9  : 16; // 31:16 Reserved
};

union PCLKCR2_REG
{
    Uint32 all;
    struct PCLKCR2_BITS bit;
};

struct PCLKCR3_BITS
{                      // bits description
    Uint32 ECAP1 : 1;  // 0 ECAP1 Clock Enable bit
    Uint32 ECAP2 : 1;  // 1 ECAP2 Clock Enable bit
    Uint32 ECAP3 : 1;  // 2 ECAP3 Clock Enable bit
    Uint32 ECAP4 : 1;  // 3 ECAP4 Clock Enable bit
    Uint32 ECAP5 : 1;  // 4 ECAP5 Clock Enable bit
    Uint32 ECAP6 : 1;  // 5 ECAP6 Clock Enable bit
    Uint32 ECAP7 : 1;  // 6 ECAP7 Clock Enable bit
    Uint32 rsvd1 : 1;  // 7 Reserved
    Uint32 rsvd2 : 8;  // 15:8 Reserved
    Uint32 rsvd3 : 16; // 31:16 Reserved
};

union PCLKCR3_REG
{
    Uint32 all;
    struct PCLKCR3_BITS bit;
};

struct PCLKCR4_BITS
{                      // bits description
    Uint32 EQEP1 : 1;  // 0 EQEP1 Clock Enable bit
    Uint32 EQEP2 : 1;  // 1 EQEP2 Clock Enable bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 16; // 31:16 Reserved
};

union PCLKCR4_REG
{
    Uint32 all;
    struct PCLKCR4_BITS bit;
};

struct PCLKCR6_BITS
{                      // bits description
    Uint32 SD1   : 1;  // 0 SD1 Clock Enable bit
    Uint32 rsvd1 : 1;  // 1 Reserved
    Uint32 rsvd2 : 1;  // 2 Reserved
    Uint32 rsvd3 : 1;  // 3 Reserved
    Uint32 rsvd4 : 1;  // 4 Reserved
    Uint32 rsvd5 : 1;  // 5 Reserved
    Uint32 rsvd6 : 1;  // 6 Reserved
    Uint32 rsvd7 : 1;  // 7 Reserved
    Uint32 rsvd8 : 8;  // 15:8 Reserved
    Uint32 rsvd9 : 16; // 31:16 Reserved
};

union PCLKCR6_REG
{
    Uint32 all;
    struct PCLKCR6_BITS bit;
};

struct PCLKCR7_BITS
{                      // bits description
    Uint32 SCI_A : 1;  // 0 SCI_A Clock Enable bit
    Uint32 SCI_B : 1;  // 1 SCI_B Clock Enable bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 16; // 31:16 Reserved
};

union PCLKCR7_REG
{
    Uint32 all;
    struct PCLKCR7_BITS bit;
};

struct PCLKCR8_BITS
{                      // bits description
    Uint32 SPI_A : 1;  // 0 SPI_A Clock Enable bit
    Uint32 SPI_B : 1;  // 1 SPI_B Clock Enable bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 1;  // 16 Reserved
    Uint32 rsvd5 : 1;  // 17 Reserved
    Uint32 rsvd6 : 14; // 31:18 Reserved
};

union PCLKCR8_REG
{
    Uint32 all;
    struct PCLKCR8_BITS bit;
};

struct PCLKCR9_BITS
{
    Uint32 I2C_A   : 1;  // [0]
    Uint32 PMBUS_A : 1;  // [1]
    Uint32 rsvd2   : 14; // 15:2 Reserved
    Uint32 rsvd3   : 16; // 31:16 Reserved
};

union PCLKCR9_REG
{
    Uint32 all;
    struct PCLKCR9_BITS bit;
};

struct PCLKCR10_BITS
{                      // bits description
    Uint32 CAN_A : 1;  // 0 CAN_A Clock Enable bit
    Uint32 CAN_B : 1;  // 1 CAN_B Clock Enable bit
    Uint32 rsvd1 : 1;  // 2 Reserved
    Uint32 rsvd2 : 1;  // 3 Reserved
    Uint32 rsvd3 : 12; // 15:4 Reserved
    Uint32 rsvd4 : 16; // 31:16 Reserved
};

union PCLKCR10_REG
{
    Uint32 all;
    struct PCLKCR10_BITS bit;
};

struct PCLKCR13_BITS
{
    Uint32 ADC_A    : 1; // [0]
    Uint32 ADC_B    : 1; // [1]
    Uint32 ADC_C    : 1; // [2]
    Uint32 ADC_G    : 1; // [3]
    Uint32 ADC_H    : 1; // [4]
    Uint32 rsvd     : 1; // [5]
    Uint32 ADC_A_HR : 1; // [6]
    Uint32 ADC_B_HR : 1; // [7]
    Uint32 ADC_C_HR : 1; // [8]
};

union PCLKCR13_REG
{
    Uint32 all;
    struct PCLKCR13_BITS bit;
};

struct PCLKCR14_BITS
{                       // bits description
    Uint32 CMPSS1 : 1;  // 0 CMPSS1 Clock Enable bit
    Uint32 CMPSS2 : 1;  // 1 CMPSS2 Clock Enable bit
    Uint32 CMPSS3 : 1;  // 2 CMPSS3 Clock Enable bit
    Uint32 CMPSS4 : 1;  // 3 CMPSS4 Clock Enable bit
    Uint32 CMPSS5 : 1;  // 4 CMPSS5 Clock Enable bit
    Uint32 CMPSS6 : 1;  // 5 CMPSS6 Clock Enable bit
    Uint32 CMPSS7 : 1;  // 6 CMPSS7 Clock Enable bit
    Uint32 rsvd1  : 1;  // 7 Reserved
    Uint32 rsvd2  : 8;  // 15:8 Reserved
    Uint32 rsvd3  : 16; // 31:16 Reserved
};

union PCLKCR14_REG
{
    Uint32 all;
    struct PCLKCR14_BITS bit;
};

struct PCLKCR15_BITS
{                      // bits description
    Uint32 PGA1  : 1;  // 0 PGA1 Clock Enable bit
    Uint32 PGA2  : 1;  // 1 PGA2 Clock Enable bit
    Uint32 PGA3  : 1;  // 2 PGA3 Clock Enable bit
    Uint32 PGA4  : 1;  // 3 PGA4 Clock Enable bit
    Uint32 PGA5  : 1;  // 4 PGA5 Clock Enable bit
    Uint32 PGA6  : 1;  // 5 PGA6 Clock Enable bit
    Uint32 PGA7  : 1;  // 6 PGA7 Clock Enable bit
    Uint32 rsvd1 : 1;  // 7 Reserved
    Uint32 rsvd2 : 8;  // 15:8 Reserved
    Uint32 rsvd3 : 16; // 31:16 Reserved
};

union PCLKCR15_REG
{
    Uint32 all;
    struct PCLKCR15_BITS bit;
};

struct PCLKCR16_BITS
{
    Uint32 DAC_A : 1; // [0]
    Uint32 DAC_B : 1; // [1]
};

union PCLKCR16_REG
{
    Uint32 all;
    struct PCLKCR16_BITS bit;
};

struct PCLKCR19_BITS
{
    Uint32 LIN_A : 1; // [0]
    Uint32 EMIF  : 1; // [1]
};

union PCLKCR19_REG
{
    Uint32 all;
    struct PCLKCR19_BITS bit;
};

struct CPUEXPSTART_BITS
{
    Uint32 EXPSTART : 4; // [2:0]
};

union CPU1EXPSTART_REG
{
    Uint32 all;
    struct CPUEXPSTART_BITS bit;
};

union CPU2EXPSTART_REG
{
    Uint32 all;
    struct CPUEXPSTART_BITS bit;
};

struct LPMCR_BITS
{                         // bits description
    Uint32 LPM       : 2; // 1:0 Low Power Mode setting
    Uint32 WDINTE    : 1; // 2 watchdog interrupt enable
    Uint32 GPIOLPSEL : 1; // 3 gpio low power select
};

union LPMCR_REG
{
    Uint32 all;
    struct LPMCR_BITS bit;
};

struct TMR2CLKCTL_BITS
{                                   // bits description
    Uint32 CPUTMR2CLKSRCSEL    : 2; // 1:0 CPU Timer 2 Clock Source Select Bit
    Uint32 rsvd0               : 1; // 2
    Uint32 CPUTMR2CLKPRESCALE  : 3; // 5:3 CPU Timer 2 Clock Pre-Scale Value
    Uint32 rsvd1               : 2; // 7:6
    Uint32 CPU2TMR2CLKSRCSEL   : 2; // 9:8 CPU2 Timer 2 Clock Source Select Bit
    Uint32 rsvd3               : 1; // 10
    Uint32 CPU2TMR2CLKPRESCALE : 3; // 13:11 CPU2 Timer 2 Clock Pre-Scale Value
};

union TMR2CLKCTL_REG
{
    Uint32 all;
    struct TMR2CLKCTL_BITS bit;
};

struct GPIOLPMSEL0_BITS
{                      // bits description
    Uint32 GPIO0  : 1; // 0 GPIO0 Enable for LPM Wakeup
    Uint32 GPIO1  : 1; // 1 GPIO1 Enable for LPM Wakeup
    Uint32 GPIO2  : 1; // 2 GPIO2 Enable for LPM Wakeup
    Uint32 GPIO3  : 1; // 3 GPIO3 Enable for LPM Wakeup
    Uint32 GPIO4  : 1; // 4 GPIO4 Enable for LPM Wakeup
    Uint32 GPIO5  : 1; // 5 GPIO5 Enable for LPM Wakeup
    Uint32 GPIO6  : 1; // 6 GPIO6 Enable for LPM Wakeup
    Uint32 GPIO7  : 1; // 7 GPIO7 Enable for LPM Wakeup
    Uint32 GPIO8  : 1; // 8 GPIO8 Enable for LPM Wakeup
    Uint32 GPIO9  : 1; // 9 GPIO9 Enable for LPM Wakeup
    Uint32 GPIO10 : 1; // 10 GPIO10 Enable for LPM Wakeup
    Uint32 GPIO11 : 1; // 11 GPIO11 Enable for LPM Wakeup
    Uint32 GPIO12 : 1; // 12 GPIO12 Enable for LPM Wakeup
    Uint32 GPIO13 : 1; // 13 GPIO13 Enable for LPM Wakeup
    Uint32 GPIO14 : 1; // 14 GPIO14 Enable for LPM Wakeup
    Uint32 GPIO15 : 1; // 15 GPIO15 Enable for LPM Wakeup
    Uint32 GPIO16 : 1; // 16 GPIO16 Enable for LPM Wakeup
    Uint32 GPIO17 : 1; // 17 GPIO17 Enable for LPM Wakeup
    Uint32 GPIO18 : 1; // 18 GPIO18 Enable for LPM Wakeup
    Uint32 GPIO19 : 1; // 19 GPIO19 Enable for LPM Wakeup
    Uint32 GPIO20 : 1; // 20 GPIO20 Enable for LPM Wakeup
    Uint32 GPIO21 : 1; // 21 GPIO21 Enable for LPM Wakeup
    Uint32 GPIO22 : 1; // 22 GPIO22 Enable for LPM Wakeup
    Uint32 GPIO23 : 1; // 23 GPIO23 Enable for LPM Wakeup
    Uint32 GPIO24 : 1; // 24 GPIO24 Enable for LPM Wakeup
    Uint32 GPIO25 : 1; // 25 GPIO25 Enable for LPM Wakeup
    Uint32 GPIO26 : 1; // 26 GPIO26 Enable for LPM Wakeup
    Uint32 GPIO27 : 1; // 27 GPIO27 Enable for LPM Wakeup
    Uint32 GPIO28 : 1; // 28 GPIO28 Enable for LPM Wakeup
    Uint32 GPIO29 : 1; // 29 GPIO29 Enable for LPM Wakeup
    Uint32 GPIO30 : 1; // 30 GPIO30 Enable for LPM Wakeup
    Uint32 GPIO31 : 1; // 31 GPIO31 Enable for LPM Wakeup
};

union GPIOLPMSEL0_REG
{
    Uint32 all;
    struct GPIOLPMSEL0_BITS bit;
};

struct GPIOLPMSEL1_BITS
{                      // bits description
    Uint32 GPIO32 : 1; // 0 GPIO32 Enable for LPM Wakeup
    Uint32 GPIO33 : 1; // 1 GPIO33 Enable for LPM Wakeup
    Uint32 GPIO34 : 1; // 2 GPIO34 Enable for LPM Wakeup
    Uint32 GPIO35 : 1; // 3 GPIO35 Enable for LPM Wakeup
    Uint32 GPIO36 : 1; // 4 GPIO36 Enable for LPM Wakeup
    Uint32 GPIO37 : 1; // 5 GPIO37 Enable for LPM Wakeup
    Uint32 GPIO38 : 1; // 6 GPIO38 Enable for LPM Wakeup
    Uint32 GPIO39 : 1; // 7 GPIO39 Enable for LPM Wakeup
    Uint32 GPIO40 : 1; // 8 GPIO40 Enable for LPM Wakeup
    Uint32 GPIO41 : 1; // 9 GPIO41 Enable for LPM Wakeup
    Uint32 GPIO42 : 1; // 10 GPIO42 Enable for LPM Wakeup
    Uint32 GPIO43 : 1; // 11 GPIO43 Enable for LPM Wakeup
    Uint32 GPIO44 : 1; // 12 GPIO44 Enable for LPM Wakeup
    Uint32 GPIO45 : 1; // 13 GPIO45 Enable for LPM Wakeup
    Uint32 GPIO46 : 1; // 14 GPIO46 Enable for LPM Wakeup
    Uint32 GPIO47 : 1; // 15 GPIO47 Enable for LPM Wakeup
    Uint32 GPIO48 : 1; // 16 GPIO48 Enable for LPM Wakeup
    Uint32 GPIO49 : 1; // 17 GPIO49 Enable for LPM Wakeup
    Uint32 GPIO50 : 1; // 18 GPIO50 Enable for LPM Wakeup
    Uint32 GPIO51 : 1; // 19 GPIO51 Enable for LPM Wakeup
    Uint32 GPIO52 : 1; // 20 GPIO52 Enable for LPM Wakeup
    Uint32 GPIO53 : 1; // 21 GPIO53 Enable for LPM Wakeup
    Uint32 GPIO54 : 1; // 22 GPIO54 Enable for LPM Wakeup
    Uint32 GPIO55 : 1; // 23 GPIO55 Enable for LPM Wakeup
    Uint32 GPIO56 : 1; // 24 GPIO56 Enable for LPM Wakeup
    Uint32 GPIO57 : 1; // 25 GPIO57 Enable for LPM Wakeup
    Uint32 GPIO58 : 1; // 26 GPIO58 Enable for LPM Wakeup
    Uint32 GPIO59 : 1; // 27 GPIO59 Enable for LPM Wakeup
    Uint32 GPIO60 : 1; // 28 GPIO60 Enable for LPM Wakeup
    Uint32 GPIO61 : 1; // 29 GPIO61 Enable for LPM Wakeup
    Uint32 GPIO62 : 1; // 30 GPIO62 Enable for LPM Wakeup
    Uint32 GPIO63 : 1; // 31 GPIO63 Enable for LPM Wakeup
};

union GPIOLPMSEL1_REG
{
    Uint32 all;
    struct GPIOLPMSEL1_BITS bit;
};

struct RESCCLR_BITS
{                             // bits description
    Uint32 POR           : 1; // 0 CPU1 POR Reset Cause Clear Bit
    Uint32 XRSn          : 1; // 1 CPU1 XRSn Reset Cause Clear Bit
    Uint32 WDRSn         : 1; // 2 CPU1 WDRSn Reset Cause Clear Bit
    Uint32 NMIWDRSn      : 1; // 3 CPU1 NMIWDRSn Reset Cause Clear Bit
    Uint32 CPU2_POR      : 1; // 4 CPU2 POR Reset Cause Clear Bit
    Uint32 CPU2_XRSn     : 1; // 5 CPU2 XRSn Reset Cause Clear Bit
    Uint32 CPU2_WDRSn    : 1; // 6 CPU2 WDRSn Reset Cause Clear Bit
    Uint32 CPU2_NMIWDRSn : 1; // 7 CPU2 NMIWDRSn Reset Cause Clear Bit
    Uint32 DBGRSn        : 1; // 8 CPU1 Debug Reset Cause Clear Bit
    Uint32 CPU2_DBGRSn   : 1; // 9 CPU2 Debug Reset Cause Clear Bit
};

union RESCCLR_REG
{
    Uint32 all;
    struct RESCCLR_BITS bit;
};

struct RESC_BITS
{                                // bits description
    Uint32 POR             : 1;  // 0 CPU1 POR Reset Cause Indication Bit
    Uint32 XRSn            : 1;  // 1 CPU1 XRSn Reset Cause Indication Bit
    Uint32 WDRSn           : 1;  // 2 CPU1 WDRSn Reset Cause Indication Bit
    Uint32 NMIWDRSn        : 1;  // 3 CPU1 NMIWDRSn Reset Cause Indication Bit
    Uint32 CPU2_POR        : 1;  // 4 CPU2 POR Reset Cause Indication Bit
    Uint32 CPU2_XRSn       : 1;  // 5 CPU2 XRSn Reset Cause Indication Bit
    Uint32 CPU2_WDRSn      : 1;  // 6 CPU2 WDRSn Reset Cause Indication Bit
    Uint32 CPU2_NMIWDRSn   : 1;  // 7 CPU2 NMIWDRSn Reset Cause Indication Bit
    Uint32 DBGRSn          : 1;  // 8 CPU1 Debug Reset Cause Indication Bit
    Uint32 CPU2_DBGRSn     : 1;  // 9 CPU2 Debug Reset Cause Indication Bit
    Uint32 rsvd0           : 19; // 28:10 reserved
    Uint32 XRSn_PIN_STATUS : 1;  // 29 XRSn Current Pin Status
    Uint32 DCON            : 1;  // 30 CPU1 Debug Connect Status Bit
    Uint32 CPU2_DCON       : 1;  // 31 CPu2 Debug Connect Status Bit
};

union RESC_REG
{
    Uint32 all;
    struct RESC_BITS bit;
};

struct CPU_SYS_REGS
{
    union PCLKCR0_REG PCLKCR0;           // offset:0x00
    union PCLKCR2_REG PCLKCR2;           // offset:0x04
    union PCLKCR3_REG PCLKCR3;           // offset:0x08
    union PCLKCR4_REG PCLKCR4;           // offset:0x0C
    union PCLKCR6_REG PCLKCR6;           // offset:0x10
    union PCLKCR7_REG PCLKCR7;           // offset:0x14
    union PCLKCR8_REG PCLKCR8;           // offset:0x18
    union PCLKCR9_REG PCLKCR9;           // offset:0x1C
    union PCLKCR10_REG PCLKCR10;         // offset:0x20
    union PCLKCR13_REG PCLKCR13;         // offset:0x24
    union PCLKCR14_REG PCLKCR14;         // offset:0x28
    union PCLKCR15_REG PCLKCR15;         // offset:0x2C
    union PCLKCR16_REG PCLKCR16;         // offset:0x30
    union PCLKCR19_REG PCLKCR19;         // offset:0x34
    union CPU1EXPSTART_REG CPU1EXPSTART; // offset:0x38
    union CPU2EXPSTART_REG CPU2EXPSTART; // offset:0x3c
    Uint32 reserve1[14];                 // offset:0x40 ~ 0x74
    union LPMCR_REG LPMCR;               // offset:0x78 LPM Control Register
    Uint32 HHRPWM;                       // offset:0x7C
    union TMR2CLKCTL_REG TMR2CLKCTL;     // offset:0x80
    union GPIOLPMSEL0_REG GPIOLPMSEL0;   // GPIO LPM Wakeup select registers, offset:0x84
    union GPIOLPMSEL1_REG GPIOLPMSEL1;   // GPIO LPM Wakeup select registers, offset:0x88
    union RESCCLR_REG RESCCLR;           // Reset Cause Clear Register, offset:0x8C
    union RESC_REG RESC;                 // Reset Cause register, offset:0x90
};

struct SCSR_BITS
{                           // bits description
    Uint32 WDOVERRIDE : 1;  // 0 WD Override for WDDIS bit
    Uint32 WDENINT    : 1;  // 1 WD Interrupt Enable
    Uint32 WDINTS     : 1;  // 2 WD Interrupt Status
    Uint32 rsvd1      : 13; // 15:3 Reserved
};

union SCSR_REG
{
    Uint32 all;
    struct SCSR_BITS bit;
};

struct WDCNTR_BITS
{                      // bits description
    Uint32 WDCNTR : 8; // 7:0 WD Counter
    Uint32 rsvd1  : 8; // 15:8 Reserved
};

union WDCNTR_REG
{
    Uint32 all;
    struct WDCNTR_BITS bit;
};

struct WDKEY_BITS
{                     // bits description
    Uint32 WDKEY : 8; // 7:0 Key to pet the watchdog timer.
    Uint32 rsvd1 : 8; // 15:8 Reserved
};

union WDKEY_REG
{
    Uint32 all;
    struct WDKEY_BITS bit;
};

struct WDCR_BITS
{                           // bits description
    Uint32 WDPS        : 3; // 2:0 WD Clock Prescalar
    Uint32 WDCHK       : 3; // 5:3 WD Check Bits
    Uint32 WDDIS       : 1; // 6 WD Disable
    Uint32 rsvd1       : 1; // 7 Reserved
    Uint32 WDPRECLKDIV : 4; // 11:8 WD Pre Clock Divider
    Uint32 rsvd2       : 4; // 15:12 Reserved
};

union WDCR_REG
{
    Uint32 all;
    struct WDCR_BITS bit;
};

struct WDWCR_BITS
{                     // bits description
    Uint32 MIN   : 8; // 7:0 WD Min Threshold setting for Windowed Watchdog functionality
    Uint32 rsvd1 : 1; // 8 Reserved
    Uint32 rsvd2 : 7; // 15:9 Reserved
};

union WDWCR_REG
{
    Uint32 all;
    struct WDWCR_BITS bit;
};

struct WD_REGS
{
    union SCSR_REG SCSR;     // System Control & Status Register
    union WDCNTR_REG WDCNTR; // Watchdog Counter Register
    union WDKEY_REG WDKEY;   // Watchdog Reset Key Register
    union WDCR_REG WDCR;     // Watchdog Control Register
    union WDWCR_REG WDWCR;   // Watchdog Windowed Control Register
};

struct SYNCSELECT_BITS
{                            // bits description
    Uint32 EPWM4SYNCIN  : 3; // 2:0 Selects Sync Input Source for EPWM4
    Uint32 EPWM7SYNCIN  : 3; // 5:3 Selects Sync Input Source for EPWM7
    Uint32 EPWM10SYNCIN : 3; // 8:6 Selects Sync Input Source for EPWM10
    Uint32 ECAP1SYNCIN  : 3; // 11:9 Selects Sync Input Source for ECAP1
    Uint32 ECAP4SYNCIN  : 3; // 14:12 Selects Sync Input Source for ECAP4
    Uint32 ECAP6SYNCIN  : 3; // 17:15 Selects Sync Input Source for ECAP6
    Uint32 rsvd2        : 9; // 26:18 Reserved
    Uint32 SYNCOUT      : 2; // 28:27 Select Syncout Source
    Uint32 EPWM1SYNCIN  : 3; // 31:29 Selects Sync Input Source for EPWM1
};

union SYNCSELECT_REG
{
    Uint32 all;
    struct SYNCSELECT_BITS bit;
};

struct ADCSOCOUTSELECT_BITS
{                           // bits description
    Uint32 PWM1SOCAEN  : 1; // 0 PWM1SOCAEN Enable for ADCSOCAOn
    Uint32 PWM2SOCAEN  : 1; // 1 PWM2SOCAEN Enable for ADCSOCAOn
    Uint32 PWM3SOCAEN  : 1; // 2 PWM3SOCAEN Enable for ADCSOCAOn
    Uint32 PWM4SOCAEN  : 1; // 3 PWM4SOCAEN Enable for ADCSOCAOn
    Uint32 PWM5SOCAEN  : 1; // 4 PWM5SOCAEN Enable for ADCSOCAOn
    Uint32 PWM6SOCAEN  : 1; // 5 PWM6SOCAEN Enable for ADCSOCAOn
    Uint32 PWM7SOCAEN  : 1; // 6 PWM7SOCAEN Enable for ADCSOCAOn
    Uint32 PWM8SOCAEN  : 1; // 7 PWM8SOCAEN Enable for ADCSOCAOn
    Uint32 PWM9SOCAEN  : 1; // 8 PWM9SOCAEN Enable for ADCSOCAOn
    Uint32 PWM10SOCAEN : 1; // 9 PWM10SOCAEN Enable for ADCSOCAOn
    Uint32 PWM11SOCAEN : 1; // 10 PWM11SOCAEN Enable for ADCSOCAOn
    Uint32 PWM12SOCAEN : 1; // 11 PWM12SOCAEN Enable for ADCSOCAOn
    Uint32 rsvd5       : 4; // 15:12 Reserved
    Uint32 PWM1SOCBEN  : 1; // 16 PWM1SOCBEN Enable for ADCSOCBOn
    Uint32 PWM2SOCBEN  : 1; // 17 PWM2SOCBEN Enable for ADCSOCBOn
    Uint32 PWM3SOCBEN  : 1; // 18 PWM3SOCBEN Enable for ADCSOCBOn
    Uint32 PWM4SOCBEN  : 1; // 19 PWM4SOCBEN Enable for ADCSOCBOn
    Uint32 PWM5SOCBEN  : 1; // 20 PWM5SOCBEN Enable for ADCSOCBOn
    Uint32 PWM6SOCBEN  : 1; // 21 PWM6SOCBEN Enable for ADCSOCBOn
    Uint32 PWM7SOCBEN  : 1; // 22 PWM7SOCBEN Enable for ADCSOCBOn
    Uint32 PWM8SOCBEN  : 1; // 23 PWM8SOCBEN Enable for ADCSOCBOn
    Uint32 PWM9SOCBEN  : 1; // 24 PWM9SOCBEN Enable for ADCSOCBOn
    Uint32 PWM10SOCBEN : 1; // 25 PWM10SOCBEN Enable for ADCSOCBOn
    Uint32 PWM11SOCBEN : 1; // 26 PWM11SOCBEN Enable for ADCSOCBOn
    Uint32 PWM12SOCBEN : 1; // 27 PWM12SOCBEN Enable for ADCSOCBOn
    Uint32 rsvd10      : 4; // 31:28 Reserved
};

union ADCSOCOUTSELECT_REG
{
    Uint32 all;
    struct ADCSOCOUTSELECT_BITS bit;
};

struct SYNCSOCLOCK_BITS
{                                // bits description
    Uint32 SYNCSELECT      : 1;  // 0 SYNCSEL Register Lock bit
    Uint32 ADCSOCOUTSELECT : 1;  // 1 ADCSOCOUTSELECT Register Lock bit
    Uint32 rsvd1           : 14; // 15:2 Reserved
    Uint32 rsvd2           : 16; // 31:16 Reserved
};

union SYNCSOCLOCK_REG
{
    Uint32 all;
    struct SYNCSOCLOCK_BITS bit;
};

struct SYNC_SOC_REGS
{
    union SYNCSELECT_REG SYNCSELECT;           // Sync Input and Output Select Register
    union ADCSOCOUTSELECT_REG ADCSOCOUTSELECT; // External ADCSOC Select Register
    union SYNCSOCLOCK_REG SYNCSOCLOCK;         // SYNCSEL and EXTADCSOC Select Lock register
};

//---------------------------------------------------------------------------
// ECC Register Bit Definitions:
//---------------------------------------------------------------------------
struct MEM_PARITY_CTRL_BITS
{
    Uint32 CHECK_MODE : 1; // [0] 0 = disable Parity Check
                           //     1 = enable  Parity Check
    Uint32 rsvd : 31;      // [31:1]
};

struct MEM_ECC_CTRL_BITS
{
    Uint32 CHECK_MODE : 2; // [ 1:0] 1 = Parity Check
                           //        2 = Hamming Code error correction
                           //        others = disable check
    Uint32 rsvd : 30;      // [31:1]
};

struct FLASH_CRC_CTRL_BITS
{
    Uint32 ENABLE : 1; // [0] 0 = disable FLASH to RAM CRC-32 check
                       //     1 = enable FLASH to RAM CRC-32 check
    Uint32 START : 1;  // [1] 1 = start check
    Uint32 END   : 1;  // [2] 1 = end check
    Uint32 rsvd  : 29; // [31:3]
};

union MEM_PARITY_CTRL_REG
{
    Uint32 all;
    struct MEM_PARITY_CTRL_BITS bit;
};

union MEM_ECC_CTRL_REG
{
    Uint32 all;
    struct MEM_ECC_CTRL_BITS bit;
};

union FLASH_CRC_CTRL_REG
{
    Uint32 all;
    struct FLASH_CRC_CTRL_BITS bit;
};

struct ECC_REGS
{
    union MEM_PARITY_CTRL_REG MEM_PARITY_CTRL; // offset: 0x00
    union MEM_ECC_CTRL_REG MEM_ECC_CTRL;       // offset: 0x04
    union FLASH_CRC_CTRL_REG FLASH_CRC_CTRL;   // offset: 0x08
};

//---------------------------------------------------------------------------

extern volatile struct WD_REGS WdRegs;
extern volatile struct DEV_CFG_REGS DevCfgRegs;
extern volatile struct CLK_CFG_REGS ClkCfgRegs;
extern volatile struct CPU_SYS_REGS CpuSysRegs;
extern volatile struct SYNC_SOC_REGS SyncSocRegs;
extern volatile struct ECC_REGS EccRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
