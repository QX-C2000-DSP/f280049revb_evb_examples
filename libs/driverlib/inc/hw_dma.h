#ifndef HW_DMA_H
#define HW_DMA_H

/* IP defines */
#define DMA_NUM_CHANNELS  6
#define DMA_NUM_HS_IF     64
#define DMA_HAS_LLI_PARAM 0
#define DMA_M_DATA_WIDTH  32
#define DMA_MAX_MSIZE     8
#define DMA_MAX_BLOCK_TS  512

#define COMMON_REG_LEN 0x100
#define CH_REG_LEN     0x100
#define DMA_ch_BASE    (DMA_BASE + COMMON_REG_LEN)
#define DMA_COMM_BASE  DMA_BASE

/* Common registers offset */
#define DMAC_ID                   0x000 /* R DMAC ID */
#define DMAC_COMPVER              0x008 /* R DMAC Component Version */
#define DMAC_CFG                  0x010 /* R/W DMAC Configuration */
#define DMAC_CHEN                 0x018 /* R/W DMAC Chnel Enable */
#define DMAC_CHEN_L               0x018 /* R/W DMAC Chnel Enable 00-31 */
#define DMAC_CHEN_H               0x01C /* R/W DMAC Chnel Enable 32-63 */
#define DMAC_CHANNELSUSPREG       0x020 /* R/W DMAC Chnel Suspend */
#define DMAC_CHABORTREG           0x028 /* R/W DMAC Chnel Abort */
#define DMAC_INTSTATUS            0x030 /* R DMAC Interrupt Status */
#define DMAC_COMMON_INTCLEAR      0x038 /* W DMAC Interrupt Clear */
#define DMAC_COMMON_INTSTATUS_ENA 0x040 /* R DMAC Interrupt Status Enable */
#define DMAC_COMMON_INTSIGNAL_ENA 0x048 /* R/W DMAC Interrupt Signal Enable */
#define DMAC_COMMON_INTSTATUS     0x050 /* R DMAC Interrupt Status */
#define DMAC_RESET                0x058 /* R DMAC Reset Register1 */

/* DMA channel registers offset */
#define CH_SAR_L             0x000 /* R/W channel Source Low Address */
#define CH_SAR_H             0x004 /* R/W channel Source High Address */
#define CH_DAR_L             0x008 /* R/W channel Destination Low Address */
#define CH_DAR_H             0x00C /* R/W channel Destination High Address */
#define CH_BLOCK_TS          0x010 /* R/W channel Block Transfer Size */
#define CH_CTL               0x018 /* R/W channel Control */
#define CH_CTL_L             0x018 /* R/W channel Control 00-31 */
#define CH_CTL_H             0x01C /* R/W channel Control 32-63 */
#define CH_CFG               0x020 /* R/W channel Configuration */
#define CH_CFG_L             0x020 /* R/W channel Configuration 00-31 */
#define CH_CFG_H             0x024 /* R/W channel Configuration 32-63 */
#define CH_LLP               0x028 /* R/W channel Linked List Pointer */
#define CH_STATUS            0x030 /* R channel Status */
#define CH_SWHSSRC           0x038 /* R/W channel SW Handshake Source */
#define CH_SWHSDST           0x040 /* R/W channel SW Handshake Destination */
#define CH_BLK_TFR_RESUMEREQ 0x048 /* W channel Block Transfer Resume Req */
#define CH_AXI_ID            0x050 /* R/W channel AXI ID */
#define CH_AXI_QOS           0x058 /* R/W channel AXI QOS */
#define CH_SSTAT             0x060 /* R channel Source Status */
#define CH_DSTAT             0x068 /* R channel Destination Status */
#define CH_SSTATAR           0x070 /* R/W channel Source Status Fetch Addr */
#define CH_DSTATAR           0x078 /* R/W channel Destination Status Fetch Addr */
#define CH_INTSTATUS_ENA     0x080 /* R/W channel Interrupt Status Enable */
#define CH_INTSTATUS         0x088 /* R/W channel Interrupt Status */
#define CH_INTSIGNAL_ENA     0x090 /* R/W channel Interrupt Signal Enable */
#define CH_INTCLEAR          0x098 /* W channel Interrupt Clear */

#define UNUSED_CH               0x3F   /* Set unused DMA channel to 0x3F */
#define DMA_APB_HS_SEL_BIT_SIZE 0x08   /* HW handshake bits per channel */
#define DMA_APB_HS_SEL_MASK     0xFF   /* HW handshake select masks */
#define MAX_BLOCK_SIZE          0x1000 /* 1024 blocks * 4 bytes data width */
#define DMA_REGS_MAP_CH_REF     0x08   /* Chnel count to choose register map */

/* DMAC_CFG */
#define DMAC_EN_POS  0
#define DMAC_EN_MASK BIT(DMAC_EN_POS)

#define INT_EN_POS  1
#define INT_EN_MASK BIT(INT_EN_POS)

/* DMAC_CHEN */
#define DMAC_ch_EN_SHIFT    0
#define DMAC_ch_EN_WE_SHIFT 8

#define DMAC_ch_SUSP_SHIFT    16
#define DMAC_ch_SUSP_WE_SHIFT 24

/* DMAC_CHEN2 */
#define DMAC_ch_EN2_WE_SHIFT 16

/* DMAC_CHANNELSUSP */
#define DMAC_ch_SUSP2_SHIFT    0
#define DMAC_ch_SUSP2_WE_SHIFT 16

/* CH_CTL_H */

#define CH_CTL_H_ARLEN_EN      BIT(6)
#define CH_CTL_H_ARLEN_POS     7
#define CH_CTL_H_AWLEN_EN      BIT(15)
#define CH_CTL_H_AWLEN_POS     16
#define CH_CTL_L_DST_WIDTH_POS 11
#define CH_CTL_L_SRC_WIDTH_POS 8

#define CH_CTL_L_DST_INC_POS   6
#define CH_CTL_L_SRC_INC_POS   4
#define CH_CTL_L_LAST_WRITE_EN BIT(30)

#define CH_CTL_L_DST_MSIZE_POS 18
#define CH_CTL_L_SRC_MSIZE_POS 14
#define CH_CTL_H_LLI_LAST      BIT(30)
#define CH_CTL_H_LLI_VALID     BIT(31)

/* CH_CFG_L */
#define CH_CTL_L_DST_MAST             BIT(2)
#define CH_CTL_L_SRC_MAST             BIT(0)
#define CH_CFG_L_DST_MULTBLK_TYPE_POS 2
#define CH_CFG_L_SRC_MULTBLK_TYPE_POS 0

/* CH_CFG_H */
#define CH_CFG_H_TT_FC_POS      0
#define CH_CFG_H_PRIORITY_POS   17
#define CH_CFG_H_DST_PER_POS    12
#define CH_CFG_H_SRC_PER_POS    7
#define CH_CFG_H_HS_SEL_DST_POS 4
#define CH_CFG_H_HS_SEL_SRC_POS 3

/* CH_CFG2 */
#define CH_CFG2_L_SRC_PER_POS 4
#define CH_CFG2_L_DST_PER_POS 11

#define CH_CFG2_H_TT_FC_POS      0
#define CH_CFG2_H_HS_SEL_SRC_POS 3
#define CH_CFG2_H_HS_SEL_DST_POS 4
#define CH_CFG2_H_PRIORITY_POS   20

#endif
