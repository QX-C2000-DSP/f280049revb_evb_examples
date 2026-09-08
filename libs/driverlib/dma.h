#ifndef DMA_H
#define DMA_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup dma_api DMA
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_dma.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#include "f28004x_device.h"

typedef enum
{
    DMA_M2M_DMA = 0x0,
    DMA_M2P_DMA = 0x1,
    DMA_P2M_DMA = 0x2,
    DMA_P2P_DMA = 0x3,
} DMA_TtFc;

typedef enum
{
    DMA_TRANS_WIDTH_8  = 0x0,
    DMA_TRANS_WIDTH_16 = 0x1,
    DMA_TRANS_WIDTH_32 = 0x2,
} DMA_TransferWidth;

typedef enum
{
    DMA_MSIZE_1  = 0x0,
    DMA_MSIZE_4  = 0x1,
    DMA_MSIZE_8  = 0x2,
    DMA_MSIZE_16 = 0x3,
} DMA_BurstLength;

typedef enum
{
    DMA_INC_TYPE_INCREMENT = 0,
    DMA_INC_TYPE_NO_CHANGE = 1
} DMA_IncrementType;

typedef enum
{
    DMA_MBLK_TYPE_CONTIGUOUS = 0,
    DMA_MBLK_TYPE_RELOAD     = 1,
    DMA_MBLK_TYPE_LL         = 3
} DMA_MultBlockType;

typedef enum
{
    DMA_IRQ_CH1_ACTIVE    = 0x01,
    DMA_IRQ_CH2_ACTIVE    = 0x02,
    DMA_IRQ_CH3_ACTIVE    = 0x04,
    DMA_IRQ_CH4_ACTIVE    = 0x08,
    DMA_IRQ_CH5_ACTIVE    = 0x10,
    DMA_IRQ_CH6_ACTIVE    = 0x20,
    DMA_IRQ_COMMON_ACTIVE = 0x10000
} DMA_IrqStatus;

typedef enum
{
    DMA_COMM_IRQ_NONE      = 0x00,
    DMA_SLVIF_DEC_ERR      = 0x01,
    DMA_SLVIF_WR2RO_ERR    = 0x02,
    DMA_SLVIF_RD2WO_ERR    = 0x04,
    DMA_SLVIF_DRONHOLD_ERR = 0x08,
    DMA_SLVIF_WRPARITY_ERR = 0x80,
    DMA_SLVIF_OF_DEC_ERR   = 0x100
} DMA_CommIrq;

typedef enum
{
    DMA_IRQ_NONE             = 0x0,
    DMA_IRQ_BLOCK_TRF        = 0x1,
    DMA_IRQ_DMA_TRF          = 0x2,
    DMA_IRQ_SRC_TRAN         = 0x8,
    DMA_IRQ_DST_TRAN         = 0x10,
    DMA_IRQ_SRC_DEC_ERR      = 0x20,
    DMA_IRQ_DST_DEC_ERR      = 0x40,
    DMA_IRQ_SRC_SLV_ERR      = 0x80,
    DMA_IRQ_DST_SLV_ERR      = 0x100,
    DMA_IRQ_LLI_RD_DEC_ERR   = 0x200,
    DMA_IRQ_LLI_WR_DEC_ERR   = 0x400,
    DMA_IRQ_LLI_RD_SLV_ERR   = 0x800,
    DMA_IRQ_LLI_WR_SLV_ERR   = 0x1000,
    DMA_IRQ_INVALID_ERR      = 0x2000,
    DMA_IRQ_MULTIBLKTYPE_ERR = 0x4000,
    DMA_IRQ_DEC_ERR          = 0x10000,
    DMA_IRQ_WR2RO_ERR        = 0x20000,
    DMA_IRQ_RD2RWO_ERR       = 0x40000,
    DMA_IRQ_WRONCHEN_ERR     = 0x80000,
    DMA_IRQ_WRONHOLD_ERR     = 0x200000,
    DMA_IRQ_LOCK_CLEARED     = 0x8000000,
    DMA_IRQ_SRC_SUSPENDED    = 0x10000000,
    DMA_IRQ_SUSPENDED        = 0x20000000,
    DMA_IRQ_DISABLED         = 0x40000000,
    DMA_IRQ_ABORTED          = 0x80000000,
    DMA_IRQ_ALL_ERR          = 0x3FFFFF0,
    DMA_IRQ_ALL              = 0xFFFFFFFFUL
} DMA_ChIrq;

typedef enum
{
    DMA_HS_HARDWARE = 0,
    DMA_HS_SOFTWARE = 1
} DMA_HandShakeType;

typedef enum
{
    DMA_TRIGGER_NONE       = 0,
    DMA_TRIGGER_MEM        = 0,
    DMA_TRIGGER_ADCA1      = 1,
    DMA_TRIGGER_HRADCA1    = 1,
    DMA_TRIGGER_ADCA2      = 2,
    DMA_TRIGGER_HRADCA2    = 2,
    DMA_TRIGGER_ADCA3      = 3,
    DMA_TRIGGER_HRADCA3    = 3,
    DMA_TRIGGER_ADCA4      = 4,
    DMA_TRIGGER_HRADCA4    = 4,
    DMA_TRIGGER_ADCAEVT    = 5,
    DMA_TRIGGER_HRADCAEVT  = 5,
    DMA_TRIGGER_ADCB1      = 6,
    DMA_TRIGGER_HRADCB1    = 6,
    DMA_TRIGGER_ADCB2      = 7,
    DMA_TRIGGER_HRADCB2    = 7,
    DMA_TRIGGER_ADCB3      = 8,
    DMA_TRIGGER_HRADCB3    = 8,
    DMA_TRIGGER_ADCB4      = 9,
    DMA_TRIGGER_HRADCB4    = 9,
    DMA_TRIGGER_ADCBEVT    = 10,
    DMA_TRIGGER_HRADCBEVT  = 10,
    DMA_TRIGGER_ADCC1      = 11,
    DMA_TRIGGER_HRADCC1    = 11,
    DMA_TRIGGER_ADCC2      = 12,
    DMA_TRIGGER_HRADCC2    = 12,
    DMA_TRIGGER_ADCC3      = 13,
    DMA_TRIGGER_HRADCC3    = 13,
    DMA_TRIGGER_ADCC4      = 14,
    DMA_TRIGGER_HRADCC4    = 14,
    DMA_TRIGGER_ADCCEVT    = 15,
    DMA_TRIGGER_HRADCCEVT  = 15,
    DMA_TRIGGER_XINT1      = 16,
    DMA_TRIGGER_XINT2      = 17,
    DMA_TRIGGER_XINT3      = 18,
    DMA_TRIGGER_XINT4      = 19,
    DMA_TRIGGER_XINT5      = 20,
    DMA_TRIGGER_EPWM1SOCA  = 21,
    DMA_TRIGGER_EPWM1SOCB  = 22,
    DMA_TRIGGER_EPWM2SOCA  = 23,
    DMA_TRIGGER_EPWM2SOCB  = 24,
    DMA_TRIGGER_EPWM3SOCA  = 25,
    DMA_TRIGGER_EPWM3SOCB  = 26,
    DMA_TRIGGER_EPWM4SOCA  = 27,
    DMA_TRIGGER_EPWM4SOCB  = 28,
    DMA_TRIGGER_EPWM5SOCA  = 29,
    DMA_TRIGGER_EPWM5SOCB  = 30,
    DMA_TRIGGER_EPWM6SOCA  = 31,
    DMA_TRIGGER_EPWM6SOCB  = 32,
    DMA_TRIGGER_EPWM7SOCA  = 33,
    DMA_TRIGGER_EPWM7SOCB  = 34,
    DMA_TRIGGER_CPU2TINT0  = 34,
    DMA_TRIGGER_EPWM8SOCA  = 35,
    DMA_TRIGGER_CPU2TINT1  = 35,
    DMA_TRIGGER_EPWM8SOCB  = 36,
    DMA_TRIGGER_CPU2TINT2  = 36,
    DMA_TRIGGER_TINT0      = 37,
    DMA_TRIGGER_TINT1      = 38,
    DMA_TRIGGER_TINT2      = 39,
    DMA_TRIGGER_ECAP1      = 40,
    DMA_TRIGGER_ECAP2      = 41,
    DMA_TRIGGER_ECAP3      = 42,
    DMA_TRIGGER_ECAP4      = 43,
    DMA_TRIGGER_ECAP5      = 44,
    DMA_TRIGGER_ECAP6      = 45,
    DMA_TRIGGER_ECAP7      = 46,
    DMA_TRIGGER_SDFM1FLT1  = 47,
    DMA_TRIGGER_I2CATX     = 47,
    DMA_TRIGGER_SDFM1FLT2  = 48,
    DMA_TRIGGER_I2CARX     = 48,
    DMA_TRIGGER_SDFM1FLT3  = 49,
    DMA_TRIGGER_SDFM1FLT4  = 50,
    DMA_TRIGGER_SPIA_TX    = 51,
    DMA_TRIGGER_ADCG1      = 51,
    DMA_TRIGGER_SPIA_RX    = 52,
    DMA_TRIGGER_ADCG2      = 52,
    DMA_TRIGGER_SPIB_TX    = 53,
    DMA_TRIGGER_ADCG3      = 53,
    DMA_TRIGGER_SPIB_RX    = 54,
    DMA_TRIGGER_ADCG4      = 54,
    DMA_TRIGGER_EPWM9SOCA  = 55,
    DMA_TRIGGER_ADCGEVT    = 55,
    DMA_TRIGGER_EPWM9SOCB  = 56,
    DMA_TRIGGER_ADCH1      = 56,
    DMA_TRIGGER_EPWM10SOCA = 57,
    DMA_TRIGGER_ADCH2      = 57,
    DMA_TRIGGER_EPWM10SOCB = 58,
    DMA_TRIGGER_ADCH3      = 58,
    DMA_TRIGGER_EPWM11SOCA = 59,
    DMA_TRIGGER_ADCH4      = 59,
    DMA_TRIGGER_EPWM11SOCB = 60,
    DMA_TRIGGER_ADCHEVT    = 60,
    DMA_TRIGGER_EPWM12SOCA = 61,
    DMA_TRIGGER_SCIATX     = 61,
    DMA_TRIGGER_SCIBTX     = 61,
    DMA_TRIGGER_SCICTX     = 61,
    DMA_TRIGGER_EPWM12SOCB = 62,
    DMA_TRIGGER_SCIARX     = 62,
    DMA_TRIGGER_SCIBRX     = 62,
    DMA_TRIGGER_SCICRX     = 62,
    DMA_TRIGGER_FSITXA     = 63,
    DMA_TRIGGER_FSIRXA     = 63
} DMA_Trigger;

typedef struct
{
    u32 srcAddr;
    u32 destAddr;
    u32 blockSize;
    DMA_TransferWidth srcWidth;
    DMA_TransferWidth destWidth;
    DMA_BurstLength srcMsize;
    DMA_BurstLength destMsize;
    DMA_Trigger srcHSInterface;
    DMA_Trigger destHSInterface;
    DMA_IncrementType srcInc;
    DMA_IncrementType destInc;
    DMA_MultBlockType srcMultblk;
    DMA_MultBlockType destMultblk;
} DMA_ConfigParams;

typedef struct
{
    uint32_t SAR;
    uint32_t rsvd1;
    uint32_t DSR;
    uint32_t rsvd2;
    uint32_t BLOCK_TS;
    uint32_t rsvd3;
    union LLP_REG LLP;
    uint32_t rsvd4;
    union CTL_L_REG CTL_L;
    union CTL_H_REG CTL_H;
} __attribute__((aligned(64))) DMA_LLI;

#ifdef DEBUG
static inline bool DMA_isBaseValid(uint32_t base)
{
    return ((base == DMA_BASE || base == DMA_CH1_BASE) || (base == DMA_CH2_BASE)
            || (base == DMA_CH3_BASE) || (base == DMA_CH4_BASE) || (base == DMA_CH5_BASE)
            || (base == DMA_CH6_BASE));
}
#endif

static inline void DMA_initController(void)
{
    DmaRegs.CFG.bit.DMA_EN = 1;
    DmaRegs.CFG.bit.INT_EN = 1;
}

static inline void DMA_Reset(void)
{
    DmaRegs.RESET = 0x1;
}

static inline bool DMA_getTransferStatusFlag(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    return ((volatile struct DMA_CH_REGS *)base)->INTSTATUS & 0x2U;
}

static inline bool DMA_getBurstStatusFlag(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    return ((volatile struct DMA_CH_REGS *)base)->INTSTATUS & 0x1U;
}

static inline bool DMA_getRunStatusFlag(uint32_t base)
{
    ASSERT(DMA_isBaseValid(base));
    return DmaRegs.CHEN & (1 << ((base - DMA_CH1_BASE) / 0x100));
}

static inline void DMA_startChannel(u8 channel)
{
    DmaRegs.CHEN = (0x101 << (channel - 1));
}

static inline void DMA_stopChannel(u8 channel)
{
    DmaRegs.CHEN = (0x100 << (channel - 1));
}

static inline u32 DMA_getInterruptStatus(uint32_t base)
{
    return ((volatile struct DMA_CH_REGS *)(base))->INTSTATUS;
}

static inline void DMA_enableInterrupt(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSIGNAL_EN |= flag;
}

static inline void DMA_disableInterrupt(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTSIGNAL_EN &= (~flag);
}

static inline void DMA_clearErrorFlag(uint32_t base, u32 flag)
{
    ((volatile struct DMA_CH_REGS *)(base))->INTCLEAR = flag;
}

static inline void DMA_setPriorityMode(bool ch1IsHighPri)
{
    if (ch1IsHighPri)
        ((volatile struct DMA_CH_REGS *)(DMA_CH1_BASE))->CFG_H.bit.CH_PRIOR = 5;
    else
        ((volatile struct DMA_CH_REGS *)(DMA_CH1_BASE))->CFG_H.bit.CH_PRIOR = 0;
}

static inline void DMA_configSourceAddress(uint32_t base, const void *srcAddr)
{
    ASSERT(DMA_isBaseValid(base));
    ((volatile struct DMA_CH_REGS *)base)->SAR = *(u32 *)srcAddr;
}

static inline void DMA_configDestAddress(uint32_t base, const void *destAddr)
{
    ASSERT(DMA_isBaseValid(base));
    ((volatile struct DMA_CH_REGS *)base)->DAR = *(u32 *)destAddr;
}

extern void DMA_configChannel(uint32_t base, const DMA_ConfigParams *config);

extern void DMA_configAddress(uint32_t base, const void *destAddr, const void *srcAddr);

extern void DMA_configBurst(uint32_t base, int16_t srcStep, int16_t destStep);

extern void DMA_configTransfer(
    uint32_t base, uint32_t transferSize, int16_t srcStep, int16_t destStep);

extern void DMA_configMode(uint32_t base, DMA_Trigger srcTrigger, DMA_Trigger destTrigger);

extern void DMA_configIncrementMode(
    uint32_t base, DMA_IncrementType src_inc, DMA_IncrementType dst_inc);

extern void DMA_configMultBlkMode(
    uint32_t base, DMA_MultBlockType src_type, DMA_MultBlockType dst_type);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
