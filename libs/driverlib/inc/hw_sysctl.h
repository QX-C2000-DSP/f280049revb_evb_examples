#ifndef HW_SYSCTL_H
#define HW_SYSCTL_H

//*************************************************************************************************
//
// The following are defines for the SYSCTL register offsets
//
//*************************************************************************************************
/* DEV_CFG_REGS */
#define SYSCTL_O_SOFTPRES0  0x40U // Processing Block Software Reset register
#define SYSCTL_O_SOFTPRES2  0x44U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES3  0x48U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES4  0x4CU // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES6  0x50U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES7  0x54U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES8  0x58U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES9  0x5CU // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES10 0x60U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES13 0x64U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES14 0x68U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES15 0x6CU // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES16 0x70U // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES19 0x74U // Peripheral Software Reset register

#define SYSCTL_O_HARDWARERES0  0x140U // Processing Block Hardware Reset register
#define SYSCTL_O_HARDWARERES2  0x144U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES3  0x148U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES4  0x14CU // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES6  0x150U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES7  0x154U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES8  0x158U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES9  0x15CU // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES10 0x160U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES13 0x164U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES14 0x168U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES15 0x16CU // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES16 0x170U // Peripheral Hardware Reset register
#define SYSCTL_O_HARDWARERES19 0x174U // Peripheral Hardware Reset register

#define SYSCTL_O_CANFD                      0x190 // Canfd Enable Register
#define SYSCTL_O_FLASHCLKDIV                0x1A0 // Flash Clock Divider Register
#define SYSCTL_O_EMU_SUSPEND                0x1AC // Emulation Suspend Register
#define SYSCTL_O_GSRAM_SEL                  0x320 // GS RAM Select Register
#define SYSCTL_O_FARRAM_SEL                 0x324 // FAR RAM Select Register
#define SYSCTL_O_CPU1FARRAM_CTRL            0x328 // CPU1 FAR RAM Control Register
#define SYSCTL_O_CPU2FARRAM_CTRL            0x32C // CPU2 FAR RAM Control Register
#define SYSCTL_O_NMAVFLAG                   0x330 // Non-Master Access Violation Flag Register
#define SYSCTL_O_NMAVSET                    0x334 // Non-Master Access Violation Flag Set Register
#define SYSCTL_O_NMAVCLR                    0x338 // Non-Master Access Violation Flag Clear Register
#define SYSCTL_O_NMAVINTEN                  0x33C // Non-Master Access Violation Interrupt Enable Register
#define SYSCTL_O_NMCPU1WRAVADDR             0x340 // CPU1 Non-Master Read Access Violation Address
#define SYSCTL_O_NMCPU2WRAVADDR             0x344 // CPU2 Non-Master Read Access Violation Address
#define SYSCTL_O_DMA_CH1_BLK_DONE_INT_COUNT 0x348 // DMA Channel 1 Interrupt Counter Register
#define SYSCTL_O_DMA_CH2_BLK_DONE_INT_COUNT 0x34C // DMA Channel 2 Interrupt Counter Register
#define SYSCTL_O_DMA_CH3_BLK_DONE_INT_COUNT 0x350 // DMA Channel 3 Interrupt Counter Register
#define SYSCTL_O_DMA_CH4_BLK_DONE_INT_COUNT 0x354 // DMA Channel 4 Interrupt Counter Register
#define SYSCTL_O_DMA_CH5_BLK_DONE_INT_COUNT 0x358 // DMA Channel 5 Interrupt Counter Register
#define SYSCTL_O_DMA_CH6_BLK_DONE_INT_COUNT 0x35C // DMA Channel 6 Interrupt Counter Register

/* CLK_CFG_REGS */
#define SYSCTL_O_CLKSRCCTL1     0x00U // Clock Source Control register-1
#define SYSCTL_O_CLKSRCCTL2     0x04U // Clock Source Control register-2
#define SYSCTL_O_CLKSRCCTL3     0x08U // Clock Source Control register-3
#define SYSCTL_O_SYSPLLCTL1     0x0CU // SYSPLL Control register-1
#define SYSCTL_O_SYSPLLMULT     0x10U // SYSPLL Multiplier register
#define SYSCTL_O_SYSPLL_IMULT_L 0x14U // SYSPLL SYSPLL_IMULT_L register
#define SYSCTL_O_SYSPLL_IMULT_H 0x18U // SYSPLL SYSPLL_IMULT_H register
#define SYSCTL_O_SYSPLL_ODIV    0x1CU // SYSPLL SYSPLL_ODIV register
#define SYSCTL_O_SYSPLLSTS      0x20U // SYSPLL Status register
#define SYSCTL_O_SYSCLKDIVSEL   0x24U // System Clock Divider Select register
#define SYSCTL_O_XCLKOUTDIVSEL  0x28U // XCLKOUT Divider Select register
#define SYSCTL_O_LOSPCP         0x2CU // Low Speed Clock Source Prescalar
#define SYSCTL_O_MCDCR          0x30U // Missing Clock Detect Control Register
#define SYSCTL_O_X1CNT          0x34U // 10-bit Counter on X1 Clock
#define SYSCTL_O_XTALCR         0x38U // XTAL Control Register
#define SYSCTL_O_CLKSTATUS      0x3CU // CLK Status Register

/* CPU_SYS_REGS */
#define SYSCTL_O_PCLKCR0      0x00U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR2      0x04U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR3      0x08U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR4      0x0CU // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR6      0x10U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR7      0x14U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR8      0x18U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR9      0x1CU // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR10     0x20U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR13     0x24U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR14     0x28U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR15     0x2CU // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR16     0x30U // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR19     0x34U // Peripheral Clock Gating Registers
#define SYSCTL_O_CPU1EXPSTART 0x38U // CPU1 exception vector Start Address Register
#define SYSCTL_O_CPU2EXPSTART 0x3CU // CPU2 exception vector Start Address Register
#define SYSCTL_O_LPMCR        0x78U // LPM Control Register
#define SYSCTL_O_HHRPWM       0x7CU // HHRPWM enable Register
#define SYSCTL_O_TMR2CLKCTL   0x80U // Timer2 Clock Measurement functionality control register
#define SYSCTL_O_GPIOLPMSEL0  0x84U // GPIO LPM Wakeup select registers
#define SYSCTL_O_GPIOLPMSEL1  0x88U // GPIO LPM Wakeup select registers
#define SYSCTL_O_RESCCLR      0x8CU // Reset Cause Clear Register
#define SYSCTL_O_RESC         0x90U // Reset Cause register

#define SYSCTL_O_SCSR   0x00U // System Control & Status Register
#define SYSCTL_O_WDCNTR 0x04U // Watchdog Counter Register
#define SYSCTL_O_WDKEY  0x08U // Watchdog Reset Key Register
#define SYSCTL_O_WDCR   0x0CU // Watchdog Control Register
#define SYSCTL_O_WDWCR  0x10U // Watchdog Windowed Control Register

#define SYSCTL_O_SYNCSELECT      0x0U // Sync Input and Output Select Register
#define SYSCTL_O_ADCSOCOUTSELECT 0x4U // External ADCSOC Select Register
#define SYSCTL_O_SYNCSOCLOCK     0x8U // SYNCSEL and EXTADCSOC Select Lock register

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES0 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES0_CPU2 0x1U // CPU2 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES2 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES2_EPWM1  0x1U   // EPWM1 software reset bit
#define SYSCTL_SOFTPRES2_EPWM2  0x2U   // EPWM2 software reset bit
#define SYSCTL_SOFTPRES2_EPWM3  0x4U   // EPWM3 software reset bit
#define SYSCTL_SOFTPRES2_EPWM4  0x8U   // EPWM4 software reset bit
#define SYSCTL_SOFTPRES2_EPWM5  0x10U  // EPWM5 software reset bit
#define SYSCTL_SOFTPRES2_EPWM6  0x20U  // EPWM6 software reset bit
#define SYSCTL_SOFTPRES2_EPWM7  0x40U  // EPWM7 software reset bit
#define SYSCTL_SOFTPRES2_EPWM8  0x80U  // EPWM8 software reset bit
#define SYSCTL_SOFTPRES2_EPWM9  0x100U // EPWM9 software reset bit
#define SYSCTL_SOFTPRES2_EPWM10 0x200U // EPWM10 software reset bit
#define SYSCTL_SOFTPRES2_EPWM11 0x400U // EPWM11 software reset bit
#define SYSCTL_SOFTPRES2_EPWM12 0x800U // EPWM12 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES3 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES3_ECAP1 0x1U  // ECAP1 software reset bit
#define SYSCTL_SOFTPRES3_ECAP2 0x2U  // ECAP2 software reset bit
#define SYSCTL_SOFTPRES3_ECAP3 0x4U  // ECAP3 software reset bit
#define SYSCTL_SOFTPRES3_ECAP4 0x8U  // ECAP4 software reset bit
#define SYSCTL_SOFTPRES3_ECAP5 0x10U // ECAP5 software reset bit
#define SYSCTL_SOFTPRES3_ECAP6 0x20U // ECAP6 software reset bit
#define SYSCTL_SOFTPRES3_ECAP7 0x40U // ECAP7 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES4 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES4_EQEP1 0x1U // EQEP1 software reset bit
#define SYSCTL_SOFTPRES4_EQEP2 0x2U // EQEP2 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES6 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES6_SD1 0x1U // SD1 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES7 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES7_SCI_A 0x1U // SCI_A software reset bit
#define SYSCTL_SOFTPRES7_SCI_B 0x2U // SCI_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES8 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES8_SPI_A 0x1U // SPI_A software reset bit
#define SYSCTL_SOFTPRES8_SPI_B 0x2U // SPI_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES9 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES9_I2C_A 0x1U // I2C_A software reset bit
#define SYSCTL_SOFTPRES9_PMBUS 0x2U // PMBUS software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES10 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES10_CAN_A 0x1U // CAN_A software reset bit
#define SYSCTL_SOFTPRES10_CAN_B 0x2U // CAN_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES13 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES13_ADC_A    0x1U   // ADC_A software reset bit
#define SYSCTL_SOFTPRES13_ADC_B    0x2U   // ADC_B software reset bit
#define SYSCTL_SOFTPRES13_ADC_C    0x4U   // ADC_C software reset bit
#define SYSCTL_SOFTPRES13_ADC_G    0x8U   // ADC_G software reset bit
#define SYSCTL_SOFTPRES13_ADC_H    0x10U  // ADC_H software reset bit
#define SYSCTL_SOFTPRES13_ADC_A_HR 0x40U  // ADC_A_HR software reset bit
#define SYSCTL_SOFTPRES13_ADC_B_HR 0x80U  // ADC_B_HR software reset bit
#define SYSCTL_SOFTPRES13_ADC_C_HR 0x100U // ADC_C_HR software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES14 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES14_CMPSS1 0x1U  // CMPSS1 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS2 0x2U  // CMPSS2 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS3 0x4U  // CMPSS3 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS4 0x8U  // CMPSS4 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS5 0x10U // CMPSS5 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS6 0x20U // CMPSS6 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS7 0x40U // CMPSS7 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES15 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES15_PGA1 0x1U  // PGA1 software reset bit
#define SYSCTL_SOFTPRES15_PGA2 0x2U  // PGA2 software reset bit
#define SYSCTL_SOFTPRES15_PGA3 0x4U  // PGA3 software reset bit
#define SYSCTL_SOFTPRES15_PGA4 0x8U  // PGA4 software reset bit
#define SYSCTL_SOFTPRES15_PGA5 0x10U // PGA5 software reset bit
#define SYSCTL_SOFTPRES15_PGA6 0x20U // PGA6 software reset bit
#define SYSCTL_SOFTPRES15_PGA7 0x40U // PGA7 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES16 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES16_DAC_A 0x10000U // Buffered_DAC_A software reset bit
#define SYSCTL_SOFTPRES16_DAC_B 0x20000U // Buffered_DAC_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES19 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES19_LIN_A 0x1U // LIN_A software reset bit
#define SYSCTL_SOFTPRES19_XINTF 0x2U // XINTF software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES2 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES2_EPWM1_EALLOW  0x1U   // EPWM1 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM2_EALLOW  0x2U   // EPWM2 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM3_EALLOW  0x4U   // EPWM3 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM4_EALLOW  0x8U   // EPWM4 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM5_EALLOW  0x10U  // EPWM5 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM6_EALLOW  0x20U  // EPWM6 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM7_EALLOW  0x40U  // EPWM7 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM8_EALLOW  0x80U  // EPWM8 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM9_EALLOW  0x100U // EPWM9 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM10_EALLOW 0x200U // EPWM10 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM11_EALLOW 0x400U // EPWM11 hardware reset and eallow bit
#define SYSCTL_HARDWARERES2_EPWM12_EALLOW 0x800U // EPWM12 hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES3 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES3_ECAP1_EALLOW 0x1U  // ECAP1 hardware reset and eallow bit
#define SYSCTL_HARDWARERES3_ECAP2_EALLOW 0x2U  // ECAP2 hardware reset and eallow bit
#define SYSCTL_HARDWARERES3_ECAP3_EALLOW 0x4U  // ECAP3 hardware reset and eallow bit
#define SYSCTL_HARDWARERES3_ECAP4_EALLOW 0x8U  // ECAP4 hardware reset and eallow bit
#define SYSCTL_HARDWARERES3_ECAP5_EALLOW 0x10U // ECAP5 hardware reset and eallow bit
#define SYSCTL_HARDWARERES3_ECAP6_EALLOW 0x20U // ECAP6 hardware reset and eallow bit
#define SYSCTL_HARDWARERES3_ECAP7_EALLOW 0x40U // ECAP7 hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES4 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES4_EQEP1_EALLOW 0x1U // EQEP1 hardware reset and eallow bit
#define SYSCTL_HARDWARERES4_EQEP2_EALLOW 0x2U // EQEP2 hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES6 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES6_SD1_EALLOW 0x1U // SD1 hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES7 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES7_SCI_A 0x1U // SCI_A hardware reset bit
#define SYSCTL_HARDWARERES7_SCI_B 0x2U // SCI_B hardware reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES8 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES8_SPI_A 0x1U // SPI_A hardware reset bit
#define SYSCTL_HARDWARERES8_SPI_B 0x2U // SPI_B hardware reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES9 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES9_I2C_A 0x1U // I2C_A hardware reset bit
#define SYSCTL_HARDWARERES9_PMBUS 0x2U // PMBUS hardware reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES10 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES10_CAN_A 0x1U // CAN_A hardware reset bit
#define SYSCTL_HARDWARERES10_CAN_B 0x2U // CAN_B hardware reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES13 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES13_ADC_A_EALLOW    0x1U   // ADC_A hardware reset and eallow bit
#define SYSCTL_HARDWARERES13_ADC_B_EALLOW    0x2U   // ADC_B hardware reset and eallow bit
#define SYSCTL_HARDWARERES13_ADC_C_EALLOW    0x4U   // ADC_C hardware reset and eallow bit
#define SYSCTL_HARDWARERES13_ADC_G_EALLOW    0x8U   // ADC_G hardware reset and eallow bit
#define SYSCTL_HARDWARERES13_ADC_H_EALLOW    0x10U  // ADC_H hardware reset and eallow bit
#define SYSCTL_HARDWARERES13_ADC_A_HR_EALLOW 0x40U  // ADC_A_HR hardware reset and eallow bit
#define SYSCTL_HARDWARERES13_ADC_B_HR_EALLOW 0x80U  // ADC_B_HR hardware reset and eallow bit
#define SYSCTL_HARDWARERES13_ADC_C_HR_EALLOW 0x100U // ADC_C_HR hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES14 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES14_CMPSS1_EALLOW 0x1U  // CMPSS1 hardware reset and eallow bit
#define SYSCTL_HARDWARERES14_CMPSS2_EALLOW 0x2U  // CMPSS2 hardware reset and eallow bit
#define SYSCTL_HARDWARERES14_CMPSS3_EALLOW 0x4U  // CMPSS3 hardware reset and eallow bit
#define SYSCTL_HARDWARERES14_CMPSS4_EALLOW 0x8U  // CMPSS4 hardware reset and eallow bit
#define SYSCTL_HARDWARERES14_CMPSS5_EALLOW 0x10U // CMPSS5 hardware reset and eallow bit
#define SYSCTL_HARDWARERES14_CMPSS6_EALLOW 0x20U // CMPSS6 hardware reset and eallow bit
#define SYSCTL_HARDWARERES14_CMPSS7_EALLOW 0x40U // CMPSS7 hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES15 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES15_PGA1_EALLOW 0x1U  // PGA1 hardware reset and eallow bit
#define SYSCTL_HARDWARERES15_PGA2_EALLOW 0x2U  // PGA2 hardware reset and eallow bit
#define SYSCTL_HARDWARERES15_PGA3_EALLOW 0x4U  // PGA3 hardware reset and eallow bit
#define SYSCTL_HARDWARERES15_PGA4_EALLOW 0x8U  // PGA4 hardware reset and eallow bit
#define SYSCTL_HARDWARERES15_PGA5_EALLOW 0x10U // PGA5 hardware reset and eallow bit
#define SYSCTL_HARDWARERES15_PGA6_EALLOW 0x20U // PGA6 hardware reset and eallow bit
#define SYSCTL_HARDWARERES15_PGA7_EALLOW 0x40U // PGA7 hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES16 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES16_DAC_A_EALLOW 0x10000U // Buffered_DAC_A hardware reset and eallow bit
#define SYSCTL_HARDWARERES16_DAC_B_EALLOW 0x20000U // Buffered_DAC_B hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the HARDWARERES19 register
//
//*************************************************************************************************
#define SYSCTL_HARDWARERES19_LIN_A               0x1U  // LIN_A hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_XINTF               0x2U  // XINTF hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_FSI_EALLOW          0x4U  // FSI hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_ANALOGSUBSYS_EALLOW 0x8U  // ANALOGSUBSYS hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_INPUTBAR_EALLOW     0x10U // INPUTBAR hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_EPWMBAR_EALLOW      0x20U // EPWMBAR hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_OUTPUTBAR_EALLOW    0x40U // OUTPUTBAR hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_SYSCTRL_EALLOW      0x80U // SYSCTRL hardware reset and eallow bit
#define SYSCTL_HARDWARERES19_IOMUX_EALLOW        0x100U // IOMUX hardware reset and eallow bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CANFD register
//
//*************************************************************************************************
#define SYSCTL_CANFD_CANFD0 0x1U // CANFD0 enable bit
#define SYSCTL_CANFD_CANFD1 0x2U // CANFD1 enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the FLASHCLKDIV register
//
//*************************************************************************************************
#define SYSCTL_FLASHCLKDIV_CLK_FLASH_DIV_NUM_S 0U
#define SYSCTL_FLASHCLKDIV_CLK_FLASH_DIV_NUM_M 0xFFFFU // flash moudle clock divides

//*************************************************************************************************
//
// The following are defines for the bit fields in the EMU_SUSPEND register
//
//*************************************************************************************************
#define SYSCTL_EMU_SUSPEND_ADCA   0x1U      // Emulation Suspend for ADCA bit
#define SYSCTL_EMU_SUSPEND_ADCB   0x2U      // Emulation Suspend for ADCB bit
#define SYSCTL_EMU_SUSPEND_ADCC   0x4U      // Emulation Suspend for ADCC bit
#define SYSCTL_EMU_SUSPEND_EPWM1  0x8U      // Emulation Suspend for epwm1 bit
#define SYSCTL_EMU_SUSPEND_EPWM2  0x10U     // Emulation Suspend for epwm2 bit
#define SYSCTL_EMU_SUSPEND_EPWM3  0x20U     // Emulation Suspend for epwm3 bit
#define SYSCTL_EMU_SUSPEND_EPWM4  0x40U     // Emulation Suspend for epwm4 bit
#define SYSCTL_EMU_SUSPEND_EPWM5  0x80U     // Emulation Suspend for epwm5 bit
#define SYSCTL_EMU_SUSPEND_EPWM6  0x100U    // Emulation Suspend for epwm6 bit
#define SYSCTL_EMU_SUSPEND_EPWM7  0x200U    // Emulation Suspend for epwm7 bit
#define SYSCTL_EMU_SUSPEND_EPWM8  0x400U    // Emulation Suspend for epwm8 bit
#define SYSCTL_EMU_SUSPEND_EPWM9  0x800U    // Emulation Suspend for epwm9 bit
#define SYSCTL_EMU_SUSPEND_EPWM10 0x1000U   // Emulation Suspend for epwm10 bit
#define SYSCTL_EMU_SUSPEND_EPWM11 0x2000U   // Emulation Suspend for epwm11 bit
#define SYSCTL_EMU_SUSPEND_EPWM12 0x4000U   // Emulation Suspend for epwm12 bit
#define SYSCTL_EMU_SUSPEND_ECAP1  0x8000U   // Emulation Suspend for ecap1 bit
#define SYSCTL_EMU_SUSPEND_ECAP2  0x10000U  // Emulation Suspend for ecap2 bit
#define SYSCTL_EMU_SUSPEND_ECAP3  0x20000U  // Emulation Suspend for ecap3 bit
#define SYSCTL_EMU_SUSPEND_ECAP4  0x40000U  // Emulation Suspend for ecap4 bit
#define SYSCTL_EMU_SUSPEND_ECAP5  0x80000U  // Emulation Suspend for ecap5 bit
#define SYSCTL_EMU_SUSPEND_ECAP6  0x100000U // Emulation Suspend for ecap6 bit
#define SYSCTL_EMU_SUSPEND_ECAP7  0x200000U // Emulation Suspend for ecap7 bit
#define SYSCTL_EMU_SUSPEND_EQEP0  0x400000U // Emulation Suspend for eqep0 bit
#define SYSCTL_EMU_SUSPEND_EQEP1  0x800000U // Emulation Suspend for eqep1 bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL1 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_S 0U
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M 0x3U  // OSCCLK Source Select Bit
#define SYSCTL_CLKSRCCTL1_INTOSC2OFF     0x8U  // Internal Oscillator 2 Off Bit
#define SYSCTL_CLKSRCCTL1_WDHALTI        0x20U // Watchdog HALT Mode Ignore Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL2 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_S 2U
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_M 0xCU // CANA Bit Clock Source Select Bit
#define SYSCTL_CLKSRCCTL2_CANBBCLKSEL_S 4U
#define SYSCTL_CLKSRCCTL2_CANBBCLKSEL_M 0x30U // CANB Bit Clock Source Select Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL3 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_S 0U
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M 0x7U // XCLKOUT Source Select Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSPLLCTL1 register
//
//*************************************************************************************************
#define SYSCTL_SYSPLLCTL1_PLLEN    0x1U // SYSPLL enable/disable bit
#define SYSCTL_SYSPLLCTL1_PLLCLKEN 0x2U // SYSPLL bypassed or included in the PLLSYSCLK path

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSPLLMULT register
//
//*************************************************************************************************
#define SYSCTL_SYSPLLMULT_IDIV_S 0U
#define SYSCTL_SYSPLLMULT_IDIV_M 0x0000FU   // SYSPLL Fractional Multiplier
#define SYSCTL_SYSPLLMULT_RST    0x8000000U // Reset Mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSPLLSTS register
//
//*************************************************************************************************
#define SYSCTL_SYSPLLSTS_LOCKS 0x1U // SYSPLL Lock Status Bit
#define SYSCTL_SYSPLLSTS_SLIPS 0x2U // SYSPLL Slip Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_S 0U
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M 0x3FU // PLLSYSCLK Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCLKOUTDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_S 0U
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_M 0x3U // XCLKOUT Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the LOSPCP register
//
//*************************************************************************************************
#define SYSCTL_LOSPCP_LSPCLKDIV_S 0U
#define SYSCTL_LOSPCP_LSPCLKDIV_M 0x7U // LSPCLK Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCDCR register
//
//*************************************************************************************************
#define SYSCTL_MCDCR_MCLKSTS 0x1U // Missing Clock Status Bit
#define SYSCTL_MCDCR_MCLKCLR 0x2U // Missing Clock Clear Bit
#define SYSCTL_MCDCR_MCLKOFF 0x4U // Missing Clock Detect Off Bit
#define SYSCTL_MCDCR_OSCOFF  0x8U // Oscillator Clock Off Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the X1CNT register
//
//*************************************************************************************************
#define SYSCTL_X1CNT_X1CNT_S 0U
#define SYSCTL_X1CNT_X1CNT_M 0x3FFU   // X1 Counter
#define SYSCTL_X1CNT_CLR     0x10000U // X1 Counter Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the XTALCR register
//
//*************************************************************************************************
#define SYSCTL_XTALCR_OSCOFF 0x1U // XTAL Oscillator powered-down
#define SYSCTL_XTALCR_SE     0x2U // XTAL Oscilator in Single-Ended mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSTATUS register
//
//*************************************************************************************************
#define SYSCTL_CLKSTATUS_OSC1READLY 0x1U // OSC1 Readly
#define SYSCTL_CLKSTATUS_OSC2READLY 0x2U // OSC2 Readly
#define SYSCTL_CLKSTATUS_X1READLY   0x4U // X1 Readly

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR0 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR0_CPU2       0x1U     // CPU2 Clock Enable Bit
#define SYSCTL_PCLKCR0_DMA        0x4U     // DMA Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER0  0x20U    // CPU1 TIMER0 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER1  0x40U    // CPU1 TIMER1 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER2  0x80U    // CPU1 TIMER2 Clock Enable bit
#define SYSCTL_PCLKCR0_CPU2TIMER0 0x100U   // CPU2 TIMER0 Clock Enable bit
#define SYSCTL_PCLKCR0_CPU2TIMER1 0x200U   // CPU2 TIMER1 Clock Enable bit
#define SYSCTL_PCLKCR0_CPU2TIMER2 0x400U   // CPU2 TIMER2 Clock Enable bit
#define SYSCTL_PCLKCR0_HRPWM      0x10000U // HRPWM Clock Enable Bit(just for compatable)
#define SYSCTL_PCLKCR0_TBCLKSYNC  0x40000U // EPWM Time Base Clock sync

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR2 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR2_EPWM1  0x1U   // EPWM1 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM2  0x2U   // EPWM2 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM3  0x4U   // EPWM3 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM4  0x8U   // EPWM4 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM5  0x10U  // EPWM5 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM6  0x20U  // EPWM6 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM7  0x40U  // EPWM7 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM8  0x80U  // EPWM8 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM9  0x100U // EPWM9 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM10 0x200U // EPWM10 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM11 0x400U // EPWM11 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM12 0x800U // EPWM12 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR3 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR3_ECAP1 0x1U  // ECAP1 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP2 0x2U  // ECAP2 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP3 0x4U  // ECAP3 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP4 0x8U  // ECAP4 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP5 0x10U // ECAP5 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP6 0x20U // ECAP6 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP7 0x40U // ECAP7 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR4 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR4_EQEP1 0x1U // EQEP1 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP2 0x2U // EQEP2 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR6 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR6_SD1 0x1U // SD1 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR7 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR7_SCI_A 0x1U // SCI_A Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_B 0x2U // SCI_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR8 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR8_SPI_A 0x1U // SPI_A Clock Enable bit
#define SYSCTL_PCLKCR8_SPI_B 0x2U // SPI_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR9 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR9_I2C_A   0x1U // I2C_A Clock Enable bit
#define SYSCTL_PCLKCR9_PMBUS_A 0x2U // PMBUS Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR10 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR10_CAN_A 0x1U // CAN_A Clock Enable bit
#define SYSCTL_PCLKCR10_CAN_B 0x2U // CAN_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR13 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR13_ADC_A    0x1U   // ADC_A Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_B    0x2U   // ADC_B Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_C    0x4U   // ADC_C Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_G    0x8U   // ADC_G Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_H    0x10U  // ADC_H Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_A_HR 0x40U  // ADC_A_HR software reset bit
#define SYSCTL_PCLKCR13_ADC_B_HR 0x80U  // ADC_B_HR software reset bit
#define SYSCTL_PCLKCR13_ADC_C_HR 0x100U // ADC_C_HR software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR14 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR14_CMPSS1 0x1U  // CMPSS1 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS2 0x2U  // CMPSS2 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS3 0x4U  // CMPSS3 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS4 0x8U  // CMPSS4 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS5 0x10U // CMPSS5 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS6 0x20U // CMPSS6 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS7 0x40U // CMPSS7 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR15 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR15_PGA1 0x1U  // PGA1 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA2 0x2U  // PGA2 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA3 0x4U  // PGA3 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA4 0x8U  // PGA4 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA5 0x10U // PGA5 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA6 0x20U // PGA6 Clock Enable bit
#define SYSCTL_PCLKCR15_PGA7 0x40U // PGA7 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR16 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR16_DAC_A 0x10000U // Buffered_DAC_A Clock Enable Bit
#define SYSCTL_PCLKCR16_DAC_B 0x20000U // Buffered_DAC_B Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR19 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR19_LIN_A 0x1U // LIN_A Clock Enable bit
#define SYSCTL_PCLKCR19_XINTF 0x2U // XINTF Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the LPMCR register
//
//*************************************************************************************************
#define SYSCTL_LPMCR_LPM_S      0U
#define SYSCTL_LPMCR_LPM_M      0x3U // Low Power Mode setting
#define SYSCTL_LPMCR_WDINTE     0x4U // watchdog inttrupt enable
#define SYSCTL_LPMCR_GPIOLSPSEL 0x8U // Gpio low power select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPIOLPMSEL0 register
//
//*************************************************************************************************
#define SYSCTL_GPIOLPMSEL0_GPIO0  0x1U        // GPIO0 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO1  0x2U        // GPIO1 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO2  0x4U        // GPIO2 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO3  0x8U        // GPIO3 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO4  0x10U       // GPIO4 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO5  0x20U       // GPIO5 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO6  0x40U       // GPIO6 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO7  0x80U       // GPIO7 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO8  0x100U      // GPIO8 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO9  0x200U      // GPIO9 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO10 0x400U      // GPIO10 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO11 0x800U      // GPIO11 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO12 0x1000U     // GPIO12 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO13 0x2000U     // GPIO13 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO14 0x4000U     // GPIO14 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO15 0x8000U     // GPIO15 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO16 0x10000U    // GPIO16 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO17 0x20000U    // GPIO17 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO18 0x40000U    // GPIO18 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO19 0x80000U    // GPIO19 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO20 0x100000U   // GPIO20 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO21 0x200000U   // GPIO21 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO22 0x400000U   // GPIO22 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO23 0x800000U   // GPIO23 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO24 0x1000000U  // GPIO24 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO25 0x2000000U  // GPIO25 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO26 0x4000000U  // GPIO26 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO27 0x8000000U  // GPIO27 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO28 0x10000000U // GPIO28 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO29 0x20000000U // GPIO29 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO30 0x40000000U // GPIO30 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO31 0x80000000U // GPIO31 Enable for LPM Wakeup

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPIOLPMSEL1 register
//
//*************************************************************************************************
#define SYSCTL_GPIOLPMSEL1_GPIO32 0x1U        // GPIO32 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO33 0x2U        // GPIO33 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO34 0x4U        // GPIO34 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO35 0x8U        // GPIO35 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO36 0x10U       // GPIO36 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO37 0x20U       // GPIO37 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO38 0x40U       // GPIO38 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO39 0x80U       // GPIO39 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO40 0x100U      // GPIO40 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO41 0x200U      // GPIO41 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO42 0x400U      // GPIO42 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO43 0x800U      // GPIO43 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO44 0x1000U     // GPIO44 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO45 0x2000U     // GPIO45 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO46 0x4000U     // GPIO46 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO47 0x8000U     // GPIO47 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO48 0x10000U    // GPIO48 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO49 0x20000U    // GPIO49 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO50 0x40000U    // GPIO50 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO51 0x80000U    // GPIO51 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO52 0x100000U   // GPIO52 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO53 0x200000U   // GPIO53 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO54 0x400000U   // GPIO54 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO55 0x800000U   // GPIO55 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO56 0x1000000U  // GPIO56 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO57 0x2000000U  // GPIO57 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO58 0x4000000U  // GPIO58 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO59 0x8000000U  // GPIO59 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO60 0x10000000U // GPIO60 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO61 0x20000000U // GPIO61 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO62 0x40000000U // GPIO62 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO63 0x80000000U // GPIO63 Enable for LPM Wakeup

//*************************************************************************************************
//
// The following are defines for the bit fields in the TMR2CLKCTL register
//
//*************************************************************************************************
#define SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_S       0U
#define SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_M       0x7U // CPU1 Timer 2 Clock Source Select Bit
#define SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_S     3U
#define SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_M     0x38U // CPU1 Timer 2 Clock Pre-Scale Value
#define SYSCTL_TMR2CLKCTL_CPU2TMR2CLKSRCSEL_S   8U
#define SYSCTL_TMR2CLKCTL_CPU2TMR2CLKSRCSEL_M   0x300U // CPU2 Timer 2 Clock Source Select Bit
#define SYSCTL_TMR2CLKCTL_CPU2TMR2CLKPRESCALE_S 11U
#define SYSCTL_TMR2CLKCTL_CPU2TMR2CLKPRESCALE_M 0x3800U // CPU2 Timer 2 Clock Pre-Scale Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the RESCCLR register
//
//*************************************************************************************************
#define SYSCTL_RESCCLR_POR           0x1U   // CPU1 POR Reset Cause Indication Bit
#define SYSCTL_RESCCLR_XRSN          0x2U   // CPU1 XRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_WDRSN         0x4U   // CPU1 WDRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_NMIWDRSN      0x8U   // CPU1 NMIWDRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_CPU2_POR      0x10U  // CPU2 POR Reset Cause Indication Bit
#define SYSCTL_RESCCLR_CPU2_XRSN     0x20U  // CPU2 XRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_CPU2_WDRSN    0x40U  // CPU2 WDRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_CPU2_NMIWDRSN 0x80U  // CPU2 NMIWDRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_DBGRSN        0x100U // CPU1 Debug Reset Cause Indication Bit
#define SYSCTL_RESCCLR_CPU2_DBGRSN   0x200U // CPU2 Debug Reset Cause Indication Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the RESC register
//
//*************************************************************************************************
#define SYSCTL_RESC_POR             0x1U        // CPU1 POR Reset Cause Indication Bit
#define SYSCTL_RESC_XRSN            0x2U        // CPU1 XRSn Reset Cause Indication Bit
#define SYSCTL_RESC_WDRSN           0x4U        // CPU1 WDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_NMIWDRSN        0x8U        // CPU1 NMIWDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_CPU2_POR        0x10U       // CPU2 POR Reset Cause Indication Bit
#define SYSCTL_RESC_CPU2_XRSN       0x20U       // CPU2 XRSn Reset Cause Indication Bit
#define SYSCTL_RESC_CPU2_WDRSN      0x40U       // CPU2 WDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_CPU2_NMIWDRSN   0x80U       // CPU2 NMIWDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_DBGRSN          0x100U      // CPU1 Debug Reset Cause Indication Bit
#define SYSCTL_RESC_CPU2_DBGRSN     0x200U      // CPU2 Debug Reset Cause Indication Bit
#define SYSCTL_RESC_XRSN_PIN_STATUS 0x20000000U // XRSN Pin Status
#define SYSCTL_RESC_DCON            0x40000000U // CPU1 Debugger conntion status to C28x
#define SYSCTL_RESC_CPU2_DCON       0x80000000U // CPU2 Debugger conntion status to C28x

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCSR register
//
//*************************************************************************************************
#define SYSCTL_SCSR_WDOVERRIDE 0x1U // WD Override for WDDIS bit
#define SYSCTL_SCSR_WDENINT    0x2U // WD Interrupt Enable
#define SYSCTL_SCSR_WDINTS     0x4U // WD Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDCNTR register
//
//*************************************************************************************************
#define SYSCTL_WDCNTR_WDCNTR_S 0U
#define SYSCTL_WDCNTR_WDCNTR_M 0xFFU // WD Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDKEY register
//
//*************************************************************************************************
#define SYSCTL_WDKEY_WDKEY_S 0U
#define SYSCTL_WDKEY_WDKEY_M 0xFFU // Key to pet the watchdog timer.

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDCR register
//
//*************************************************************************************************
#define SYSCTL_WDCR_WDPS_S        0U
#define SYSCTL_WDCR_WDPS_M        0x7U // WD Clock Prescalar
#define SYSCTL_WDCR_WDCHK_S       3U
#define SYSCTL_WDCR_WDCHK_M       0x38U // WD Check Bits
#define SYSCTL_WDCR_WDDIS         0x40U // WD Disable
#define SYSCTL_WDCR_WDPRECLKDIV_S 8U
#define SYSCTL_WDCR_WDPRECLKDIV_M 0xF00U // WD Pre Clock Divider

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDWCR register
//
//*************************************************************************************************
#define SYSCTL_WDWCR_MIN_S 0U
#define SYSCTL_WDWCR_MIN_M \
    0xFFU // WD Min Threshold setting for Windowed Watchdog
          // functionality

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCSELECT register
//
//*************************************************************************************************
#define SYSCTL_SYNCSELECT_EPWM4SYNCIN_S  0U
#define SYSCTL_SYNCSELECT_EPWM4SYNCIN_M  0x7U // Selects Sync Input Source for EPWM4
#define SYSCTL_SYNCSELECT_EPWM7SYNCIN_S  3U
#define SYSCTL_SYNCSELECT_EPWM7SYNCIN_M  0x38U // Selects Sync Input Source for EPWM7
#define SYSCTL_SYNCSELECT_EPWM10SYNCIN_S 6U
#define SYSCTL_SYNCSELECT_EPWM10SYNCIN_M 0x1CU // Selects Sync Input Source for EPWM10
#define SYSCTL_SYNCSELECT_ECAP1SYNCIN_S  9U
#define SYSCTL_SYNCSELECT_ECAP1SYNCIN_M  0xE00U // Selects Sync Input Source for ECAP1
#define SYSCTL_SYNCSELECT_ECAP4SYNCIN_S  12U
#define SYSCTL_SYNCSELECT_ECAP4SYNCIN_M  0x7000U // Selects Sync Input Source for ECAP4
#define SYSCTL_SYNCSELECT_ECAP6SYNCIN_S  15U
#define SYSCTL_SYNCSELECT_ECAP6SYNCIN_M  0x38000U // Selects Sync Input Source for ECAP6
#define SYSCTL_SYNCSELECT_SYNCOUT_S      27U
#define SYSCTL_SYNCSELECT_SYNCOUT_M      0x18000000U // Select Syncout Source
#define SYSCTL_SYNCSELECT_EPWM1SYNCIN_S  29U
#define SYSCTL_SYNCSELECT_EPWM1SYNCIN_M  0xE0000000U // Selects Sync Input Source for EPWM1

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOUTSELECT register
//
//*************************************************************************************************
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCAEN  0x1U       // PWM1SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN  0x2U       // PWM2SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCAEN  0x4U       // PWM3SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCAEN  0x8U       // PWM4SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCAEN  0x10U      // PWM5SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCAEN  0x20U      // PWM6SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCAEN  0x40U      // PWM7SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM8SOCAEN  0x80U      // PWM8SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM9SOCAEN  0x100U     // PWM9SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM10SOCAEN 0x200U     // PWM10SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM11SOCAEN 0x400U     // PWM11SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM12SOCAEN 0x800U     // PWM12SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCBEN  0x10000U   // PWM1SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCBEN  0x20000U   // PWM2SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCBEN  0x40000U   // PWM3SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCBEN  0x80000U   // PWM4SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCBEN  0x100000U  // PWM5SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCBEN  0x200000U  // PWM6SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCBEN  0x400000U  // PWM7SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM8SOCBEN  0x800000U  // PWM8SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM9SOCBEN  0x1000000U // PWM9SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM10SOCBEN 0x2000000U // PWM10SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM11SOCBEN 0x4000000U // PWM11SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM12SOCBEN 0x8000000U // PWM12SOCBEN Enable for ADCSOCBOn

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCSOCLOCK register
//
//*************************************************************************************************
#define SYSCTL_SYNCSOCLOCK_SYNCSELECT      0x1U // SYNCSEL Register Lock bit
#define SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT 0x2U // ADCSOCOUTSELECT Register Lock bit

#endif
