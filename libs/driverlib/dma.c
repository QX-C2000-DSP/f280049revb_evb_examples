#include "driverlib.h"

void DMA_configChannel(uint32_t base, const DMA_ConfigParams *config)
{
    // must set multblk type first
    DMA_configMultBlkMode(base, config->srcMultblk, config->destMultblk);
    DMA_configAddress(base, &config->destAddr, &config->srcAddr);
    DMA_configTransfer(base, config->blockSize, config->srcWidth, config->destWidth);
    DMA_configBurst(base, config->srcMsize, config->destMsize);
    DMA_configIncrementMode(base, config->srcInc, config->destInc);
    DMA_configMode(base, config->srcHSInterface, config->destHSInterface);
}

void DMA_configAddress(uint32_t base, const void *destAddr, const void *srcAddr)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->SAR = *(u32 *)srcAddr;
    ch_reg->DAR = *(u32 *)destAddr;
}

void DMA_configBurst(uint32_t base, int16_t srcStep, int16_t destStep)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->CTL_L.bit.SRC_MSIZE = srcStep;
    ch_reg->CTL_L.bit.DST_MSIZE = destStep;
}

void DMA_configTransfer(uint32_t base, uint32_t transferSize, int16_t srcStep, int16_t destStep)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    if (transferSize > DMA_MAX_BLOCK_TS)
        transferSize = DMA_MAX_BLOCK_TS;

    ch_reg->BLOCK_TS            = transferSize;
    ch_reg->CTL_L.bit.SRC_WIDTH = srcStep;
    ch_reg->CTL_L.bit.DST_WIDTH = destStep;
}

void DMA_configMode(uint32_t base, DMA_Trigger srcTrigger, DMA_Trigger destTrigger)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->CFG_H.bit.HS_SEL_SRC = DMA_HS_HARDWARE;
    ch_reg->CFG_L.bit.SRC_PER    = srcTrigger;
    ch_reg->CFG_H.bit.HS_SEL_DST = DMA_HS_HARDWARE;
    ch_reg->CFG_L.bit.DST_PER    = destTrigger;
    if ((srcTrigger == 0) && (destTrigger == 0))
        ch_reg->CFG_H.bit.TT_FC = DMA_M2M_DMA;
    else if ((srcTrigger == 0) && (destTrigger != 0))
        ch_reg->CFG_H.bit.TT_FC = DMA_M2P_DMA;
    else if ((srcTrigger != 0) && (destTrigger == 0))
        ch_reg->CFG_H.bit.TT_FC = DMA_P2M_DMA;
    else
        ch_reg->CFG_H.bit.TT_FC = DMA_P2P_DMA;
}

void DMA_configIncrementMode(uint32_t base, DMA_IncrementType src_inc, DMA_IncrementType dst_inc)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->CTL_L.bit.SINC = src_inc;
    ch_reg->CTL_L.bit.DINC = dst_inc;
}

void DMA_configMultBlkMode(uint32_t base, DMA_MultBlockType src_type, DMA_MultBlockType dst_type)
{
    volatile struct DMA_CH_REGS *ch_reg = (volatile struct DMA_CH_REGS *)base;

    ch_reg->CFG_L.bit.SRC_MULTBLK_TYPE = src_type;
    ch_reg->CFG_L.bit.DST_MULTBLK_TYPE = dst_type;
}
