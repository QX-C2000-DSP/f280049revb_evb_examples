#ifndef HW_MEMMAP_H
#define HW_MEMMAP_H

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals.
//
//*****************************************************************************
#define SRAM_DATA_BASE    0x00000000U
#define IPC_CPU1_MEM_BASE 0x00100000U
#define IPC_CPU2_MEM_BASE 0x00101000U
#define SRAM_INST_BASE    0x00200000U
#define SRAM_BOOT_BASE    0x00280000U

#define PIECTRL_BASE       0x007F0100U
#define DEBUG_BASE         0x007F0200U
#define CPUTIMER0_BASE     0x007F0300U
#define CPUTIMER1_BASE     0x007F0320U
#define CPUTIMER2_BASE     0x007F0340U
#define CR_BASE            0x007F0400U
#define GR_BASE            0x007F0500U
#define MOB_BASE           0x007F0600U
#define EXP_BASE           0x007F0700U
#define WD_BASE            0x007F0800U
#define IPC_REG_BASE       0x007F0900U
#define IPC_CMD_BASE       0x007F0A00U
#define VCU_BASE           0x007F0B00U
#define TRACE_BUFFER_BASE  0x007F0C00U
#define WATCH_POINT_BASE   0x007F0D00U
#define ECC_BASE           0x007F0E00U
#define ERAD_GLOBAL_BASE   0x007F0F00U
#define ERAD_HWBP1_BASE    0x007F1000U
#define ERAD_HWBP2_BASE    0x007F1100U
#define ERAD_HWBP3_BASE    0x007F1200U
#define ERAD_HWBP4_BASE    0x007F1300U
#define ERAD_HWBP5_BASE    0x007F1400U
#define ERAD_HWBP6_BASE    0x007F1500U
#define ERAD_HWBP7_BASE    0x007F1600U
#define ERAD_HWBP8_BASE    0x007F1700U
#define ERAD_COUNTER1_BASE 0x007F1800U
#define ERAD_COUNTER2_BASE 0x007F1900U
#define ERAD_COUNTER3_BASE 0x007F1A00U
#define ERAD_COUNTER4_BASE 0x007F1B00U

#define CLKCFG_BASE        0x01000000U
#define CPUSYS_BASE        0x01001000U
#define DEVCFG_BASE        0x01001000U
#define XINT_BASE          0x010011B0U
#define NMI_BASE           0x01001200U
#define DCC0_BASE          0x01002000U
#define DMA_BASE           0x01003000U
#define DMA_CH1_BASE       0x01003100U
#define DMA_CH2_BASE       0x01003200U
#define DMA_CH3_BASE       0x01003300U
#define DMA_CH4_BASE       0x01003400U
#define DMA_CH5_BASE       0x01003500U
#define DMA_CH6_BASE       0x01003600U
#define ANALOGSUBSYS_BASE  0x01004000U
#define REGFILE_BASE       0x01005000U
#define DCSMBANK0_Z1_BASE  0x01006000U
#define DCSMBANK0_Z2_BASE  0x01006800U
#define DCSMCOMMON_BASE    0x01007000U
#define DCSMBANK1_Z1_BASE  0x01008000U
#define DCSMBANK1_Z2_BASE  0x01008800U
#define DCSM1_BASE         0x01006000U
#define DCSM2_BASE         0x01007000U
#define DCSM3_BASE         0x01008000U
#define ECAP1_BASE         0x01010000U
#define ECAP2_BASE         0x01010080U
#define ECAP3_BASE         0x01010100U
#define ECAP4_BASE         0x01010180U
#define ECAP5_BASE         0x01010200U
#define ECAP6_BASE         0x01010280U
#define ECAP7_BASE         0x01010300U
#define HRCAP6_BASE        0x010102C0U
#define HRCAP7_BASE        0x01010340U
#define SYNCSOC_BASE       0x01010380U
#define SFO_BASE           0x01010400U
#define SFOHHR_BASE        0x01010480U
#define EPWM1_BASE         0x01012000U
#define EPWM2_BASE         0x01012200U
#define EPWM3_BASE         0x01012400U
#define EPWM4_BASE         0x01012600U
#define EPWM5_BASE         0x01012800U
#define EPWM6_BASE         0x01012A00U
#define EPWM7_BASE         0x01012C00U
#define EPWM8_BASE         0x01012E00U
#define EPWM9_BASE         0x01013000U
#define EPWM10_BASE        0x01013200U
#define EPWM11_BASE        0x01013400U
#define EPWM12_BASE        0x01013600U
#define EQEP1_BASE         0x01014000U
#define EQEP2_BASE         0x01014800U
#define PGA1_BASE          0x01016000U
#define PGA2_BASE          0x01016020U
#define PGA3_BASE          0x01016040U
#define PGA4_BASE          0x01016060U
#define PGA5_BASE          0x01016080U
#define PGA6_BASE          0x010160A0U
#define PGA7_BASE          0x010160C0U
#define DACA_BASE          0x01018000U
#define DACB_BASE          0x01018040U
#define CMPSS1_BASE        0x0101A000U
#define CMPSS2_BASE        0x0101A100U
#define CMPSS3_BASE        0x0101A200U
#define CMPSS4_BASE        0x0101A300U
#define CMPSS5_BASE        0x0101A400U
#define CMPSS6_BASE        0x0101A500U
#define CMPSS7_BASE        0x0101A600U
#define ADCARESULT_BASE    0x01020110U
#define ADCBRESULT_BASE    0x01020310U
#define ADCCRESULT_BASE    0x01020510U
#define ADCGRESULT_BASE    0x01020710U
#define ADCHRESULT_BASE    0x01020910U
#define HR_ADCARESULT_BASE 0x01022100U
#define HR_ADCBRESULT_BASE 0x01022500U
#define HR_ADCCRESULT_BASE 0x01022900U
#define ADCA_BASE          0x01030000U
#define ADCB_BASE          0x01030200U
#define ADCC_BASE          0x01030400U
#define ADCG_BASE          0x01030600U
#define ADCH_BASE          0x01030800U
#define HR_ADCA_BASE       0x01032000U
#define HR_ADCB_BASE       0x01032400U
#define HR_ADCC_BASE       0x01032800U
#define GPIODATA_BASE      0x01040000U
#define GPIOCTRL_BASE      0x01050000U
#define INPUTXBAR_BASE     0x01051000U
#define OUTPUTXBAR_BASE    0x01052000U
#define EPWMXBAR_BASE      0x01053000U
#define XBAR_BASE          0x01054000U
#define SPIA_BASE          0x01060000U
#define SPIB_BASE          0x01061000U
#define PMBUSA_BASE        0x01062000U
#define FSIRXA_BASE        0x01063000U
#define FSITXA_BASE        0x01064000U
#define LINA_BASE          0x01070000U
#define SCIC_BASE          0x01070000U
#define SCIA_BASE          0x01080000U
#define SCIB_BASE          0x01081000U
#define I2CA_BASE          0x01082000U
#define CANA_BASE          0x01090000U
#define CANB_BASE          0x01091000U
#define SDFM1_BASE         0x010A0000U

#define XINTF_BASE       0x20000000U
#define XINTF_ZONE0_BASE 0x20004000U
#define XINTF_ZONE6_BASE 0x20100000U
#define XINTF_ZONE7_BASE 0x20300000U

#define FLASH0CTRL_BASE 0x010B0000U
#define FLASH0DATA_BASE 0x30000000U
#define FLASH0OTP1_BASE 0x30200000U
#define FLASH0OTP2_BASE 0x30201000U

#define DCSMBANK0_Z1OTP_BASE 0x30004000U
#define DCSMBANK0_Z2OTP_BASE 0x30004400U
#define DCSMBANK1_Z1OTP_BASE 0x30004800U
#define DCSMBANK1_Z2OTP_BASE 0x30004C00U

#define DCSMBANK_BASE        DCSMBANK0_Z1OTP_BASE
#define DCSMBANK_SIZE        0x1000U
#define DCSMBANK_SECTOR_NUM  4

#endif
