#ifndef HW_LIN_H
#define HW_LIN_H

//*************************************************************************************************
//
// The following are defines for the LIN register offsets
//
//*************************************************************************************************

#define LIN_O_LBUF 0x00U
#define LIN_O_LSEL 0x01U
#define LIN_O_LID  0x02U
#define LIN_O_LER  0x03U
#define LIN_O_LIE  0x04U
#define LIN_O_LSR  0x05U
#define LIN_O_LCR  0x05U
#define LIN_O_DLL  0x06U
#define LIN_O_DLH  0x07U
#define LIN_O_HDRL 0x08U
#define LIN_O_HDRH 0x09U
#define LIN_O_HDP  0x0AU
#define LIN_O_LBS  0x0BU
#define LIN_O_WURT 0x0CU
#define LIN_O_IDTL 0x0DU
#define LIN_O_IDTH 0x0EU

//*************************************************************************************************
//
// The following are defines for the bit fields in the LBUF register
//
//*************************************************************************************************
#define LIN_LBUF_LBUF_S 0x0U  // Data buffer register
#define LIN_LBUF_LBUF_M 0xFFU //
//*************************************************************************************************
//
// The following are defines for the bit fields in the LSEL register
//
//*************************************************************************************************
#define LIN_LSEL_INDEX_S 0x0U
#define LIN_LSEL_INDEX_M 0x1FU

#define LIN_LSEL_DLY_A 0x0U
#define LIN_LSEL_DLY_B 0x20U
#define LIN_LSEL_DLY_C 0x40U
#define LIN_LSEL_DLY_D 0x60U
#define LIN_LSEL_AINC  0x80U

//*************************************************************************************************
//
// The following are defines for the bit fields in the LID register
//
//*************************************************************************************************
#define LIN_LID_ID_2 0x1U
#define LIN_LID_ID_4 0x2U
#define LIN_LID_ID_8 0x3U

//*************************************************************************************************
//
// The following are defines for the bit fields in the LER register
//
//*************************************************************************************************
#define LIN_LER_FER    0x1U
#define LIN_LER_BITER  0x2U
#define LIN_LER_PER    0x4U
#define LIN_LER_CHKSER 0x8U
#define LIN_LER_TOVER  0x10U
#define LIN_LER_SYNCER 0x20U
#define LIN_LER_OVER   0x40U
#define LIN_LER_WAKEER 0x80U

//*************************************************************************************************
//
// The following are defines for the bit fields in the LIE register
//
//*************************************************************************************************
#define LIN_LIE_LIDE   0x1U
#define LIN_LIE_RDYE   0x2U
#define LIN_LIE_ERRE   0x4U
#define LIN_LIE_ABORTE 0x8U
#define LIN_LIE_SLEEPE 0x10U
#define LIN_LIE_WAKEE  0x20U

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSR register
//
//*************************************************************************************************
#define LIN_LSR_LID   0x1U
#define LIN_LSR_RDY   0x2U
#define LIN_LSR_ERR   0x4U
#define LIN_LSR_ABORT 0x8U
// #define LIN_LSR_LOGSIZE_S      0x8U

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCR register
//
//*************************************************************************************************
#define LIN_LCR_CMD_ABORT     0x0U
#define LIN_LCR_CMD_SHEAD     0x1U
#define LIN_LCR_CMD_SWAKE     0x1U
#define LIN_LCR_CMD_SAUTO     0x1U
#define LIN_LCR_CMD_TX        0x2U
#define LIN_LCR_CMD_RX        0x3U
#define LIN_LCR_SIZE_AUTOBDEC 0x30U
#define LIN_LCR_SIZE_WAKMOD   0x34U
#define LIN_LCR_SIZE_STLMOD   0x38U
#define LIN_LCR_SIZE_STLID    0x3CU
#define LIN_LCR_LIN13         0x40U
#define LIN_LCR_MODE          0x80U

//*************************************************************************************************
//
// The following are defines for the bit fields in the DLL register
//
//*************************************************************************************************
#define LIN_DLL_DLL_S 0x0U
#define LIN_DLL_DLL_M 0xFFU

//*************************************************************************************************
//
// The following are defines for the bit fields in the DLH register
//
//*************************************************************************************************
#define LIN_DLH_DLH_S  0x0U
#define LIN_DLH_DLH_M  0x7FU
#define LIN_DLH_SYNCER 0x80U

//*************************************************************************************************
//
// The following are defines for the bit fields in the HDR register
//
//*************************************************************************************************
#define LIN_HDR_HDRL_S 0x0U
#define LIN_HDR_HDRL_M 0xFFU
#define LIN_HDR_HDRH_S 0x0U
#define LIN_HDR_HDRH_M 0xFFU

//*************************************************************************************************
//
// The following are defines for the bit fields in the HDP register
//
//*************************************************************************************************
#define LIN_HDP_HDP_S 0x0U
#define LIN_HDP_HDP_M 0x3FU

//*************************************************************************************************
//
// The following are defines for the bit fields in the LBS register
//
//*************************************************************************************************
#define LIN_LBS_SLEEPM 0x1U
#define LIN_LBS_WAKEUP 0x2U
#define LIN_LBS_SLEEP  0x4U

//*************************************************************************************************
//
// The following are defines for the bit fields in the LBS register
//
//*************************************************************************************************
#define LIN_WURT_WURT_S 0x0U
#define LIN_WURT_WURT_M 0xFFU

//*************************************************************************************************
//
// The following are defines for the bit fields in the IDT register
//
//*************************************************************************************************
#define LIN_IDT_IDTL_S      0x0U
#define LIN_IDT_IDTL_M      0xFFU
#define LIN_IDT_IDTH_S      0x0U
#define LIN_IDT_IDTH_M      0x1FU
#define LIN_IDT_IDTH_IDTRUN 0x80U

#endif
