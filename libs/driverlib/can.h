#ifndef CANFD_H
#define CANFD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup canfd_api CANFD
//! @{
//
//*****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_adc.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#include "f28004x_device.h"

//*****************************************************************************
//
// Bit definition for CAN_ACF register
//
//*****************************************************************************
#define CAN_ACF_ACODEORAMASK_POS (0U)
#define CAN_ACF_ACODEORAMASK     (0x1FFFFFFFUL)
#define CAN_ACF_AIDE_POS         (29U)
#define CAN_ACF_AIDE             (0x20000000UL)
#define CAN_ACF_AIDEE_POS        (30U)
#define CAN_ACF_AIDEE            (0x40000000UL)

//*****************************************************************************
//
// CAN ID mask
//
//*****************************************************************************
#define CAN_STANDARD_IDMASK (0x7FFUL)
#define CAN_EXTEND_IDMASK   (0x1FFFFFFFUL)

//*****************************************************************************
//
// Format of frames received by the filter
// CAN_ID_Type CAN Identifier Type
//
//*****************************************************************************
//! Acceptance filter accept frames with both standard ID and extended ID.
#define CAN_ID_STD_EXT (0x0U)
//! Acceptance filter accept frames with only standard ID.
#define CAN_ID_STD (CAN_ACF_AIDEE)
//! Acceptance filter accept frames with only extended ID.
#define CAN_ID_EXT (CAN_ACF_AIDEE | CAN_ACF_AIDE)

//*****************************************************************************
//
// Control the TDC function
//
//*****************************************************************************
//! ENABLE Transmitter Delay Compensation.
#define CANFD_ENABLE_TDCEN (0x01U)

//*****************************************************************************
//
// CAN_Acceptance_Filter CAN Acceptance Filter
//
//*****************************************************************************
#define CAN_ACF1  (0U)
#define CAN_ACF2  (1U)
#define CAN_ACF3  (2U)
#define CAN_ACF4  (3U)
#define CAN_ACF5  (4U)
#define CAN_ACF6  (5U)
#define CAN_ACF7  (6U)
#define CAN_ACF8  (7U)
#define CAN_ACF9  (8U)
#define CAN_ACF10 (9U)
#define CAN_ACF11 (10U)
#define CAN_ACF12 (11U)
#define CAN_ACF13 (12U)
#define CAN_ACF14 (13U)
#define CAN_ACF15 (14U)
#define CAN_ACF16 (15U)

//*****************************************************************************
//
// Bit definition for CAN_ACFEN register
//
//*****************************************************************************
//! Acceptance filter 1 enable select bit.
#define CAN_ACFEN_AE_1 (0x0001U)
//! Acceptance filter 2 enable select bit.
#define CAN_ACFEN_AE_2 (0x0002U)
//! Acceptance filter 3 enable select bit.
#define CAN_ACFEN_AE_3 (0x0004U)
//! Acceptance filter 4 enable select bit.
#define CAN_ACFEN_AE_4 (0x0008U)
//! Acceptance filter 5 enable select bit.
#define CAN_ACFEN_AE_5 (0x0010U)
//! Acceptance filter 6 enable select bit.
#define CAN_ACFEN_AE_6 (0x0020U)
//! Acceptance filter 7 enable select bit.
#define CAN_ACFEN_AE_7 (0x0040U)
//! Acceptance filter 8 enable select bit.
#define CAN_ACFEN_AE_8 (0x0080U)
//! Acceptance filter 9 enable select bit.
#define CAN_ACFEN_AE_9 (0x0100U)
//! Acceptance filter 10 enable select bit.
#define CAN_ACFEN_AE_10 (0x0200U)
//! Acceptance filter 11 enable select bit.
#define CAN_ACFEN_AE_11 (0x0400U)
//! Acceptance filter 12 enable select bit.
#define CAN_ACFEN_AE_12 (0x0800U)
//! Acceptance filter 13 enable select bit.
#define CAN_ACFEN_AE_13 (0x1000U)
//! Acceptance filter 14 enable select bit.
#define CAN_ACFEN_AE_14 (0x2000U)
//! Acceptance filter 15 enable select bit.
#define CAN_ACFEN_AE_15 (0x4000U)
//! Acceptance filter 16 enable select bit.
#define CAN_ACFEN_AE_16 (0x8000U)

//*****************************************************************************
//
// Bit definition for CAN_ERRINT register
//
//*****************************************************************************
#define CAN_ERRINT_BEIF_POS  (0U)
#define CAN_ERRINT_BEIF      (0x01U)
#define CAN_ERRINT_BEIE_POS  (1U)
#define CAN_ERRINT_BEIE      (0x02U)
#define CAN_ERRINT_ALIF_POS  (2U)
#define CAN_ERRINT_ALIF      (0x04U)
#define CAN_ERRINT_ALIE_POS  (3U)
#define CAN_ERRINT_ALIE      (0x08U)
#define CAN_ERRINT_EPIF_POS  (4U)
#define CAN_ERRINT_EPIF      (0x10U)
#define CAN_ERRINT_EPIE_POS  (5U)
#define CAN_ERRINT_EPIE      (0x20U)
#define CAN_ERRINT_EPASS_POS (6U)
#define CAN_ERRINT_EPASS     (0x40U)
#define CAN_ERRINT_EWARN_POS (7U)
#define CAN_ERRINT_EWARN     (0x80U)

//*****************************************************************************
//
// CAN_Status_Flag
//
//*****************************************************************************

//! Register bit CFG_STAT.BUSOFF. CAN bus off.
#define CAN_FLAG_BUS_OFF (1UL << 0U)

//! Register bit CFG_STAT.TACTIVE. CAN bus is transmitting.
#define CAN_FLAG_TX_GOING (1UL << 1U)

//! Register bit CFG_STAT.RACTIVE. CAN bus is receiving.
#define CAN_FLAG_RX_GOING (1UL << 2U)

//! Register bit RCTRL.ROV. Receive buffer is full and there is a further bit to be stored. At least
//! one frame will be lost.
#define CAN_FLAG_RX_BUF_OVF (1UL << 5U)

//! Register bit RTIE.TSFF. Transmit buffers are all full.
//! TTCFG.TTEN == 0 or TCTRL.TTTEM == 0: ALL STB slots are filled.
//! TTCFG.TTEN == 1 and TCTRL.TTTEM == 1: Transmit buffer that pointed by TBSLOT.TBPTR is filled.
#define CAN_FLAG_TX_BUF_FULL (1UL << 8U)

//! Register bit RTIF.AIF. Transmit messages requested via TCMD.TPA and TCMD.TSA were successfully
//! canceled.
#define CAN_FLAG_TX_ABORTED (1UL << 16U)

//! Register bit RTIF.EIF. The interrupt RTIF.EIF will be set if enabled by RTIE.EIE under the
//! following conditions: The border of the error warning limit has been crossed in either direction
//! by RECNT or TECNT or the BUSOFF bit has been changed in either direction.
#define CAN_FLAG_ERR_INT (1UL << 17U)

//! Register bit RTIF.TSIF. STB was transmitted.
#define CAN_FLAG_STB_TX (1UL << 18U)

//! Register bit RTIF.TPIF. PTB was transmitted.
#define CAN_FLAG_PTB_TX (1UL << 19U)

//! Register bit RTIF.RAFIF. The number of filled RB slot is greater than or equal to the LIMIT.AFWL
//! setting value.
#define CAN_FLAG_RX_BUF_WARN (1UL << 20U)

//! Register bit RTIF.RFIF. The FIFO of receive buffer is full.
#define CAN_FLAG_RX_BUF_FULL (1UL << 21U)

//! Register bit RTIF.ROIF. Receive buffers are all full and there is a further message to be
//! stored.
#define CAN_FLAG_RX_OVERRUN (1UL << 22U)

//! Register bit RTIF.RIF. Received a valid data frame or remote frame.
#define CAN_FLAG_RX (1UL << 23U)

//! Register bit ERRINT.BEIF. Each of the error defined by EALCAP.KOER can make this flag set.
#define CAN_FLAG_BUS_ERR (1UL << 24U)

//! Register bit ERRINT.ALIF. Arbitration lost.
#define CAN_FLAG_ARBITR_LOST (1UL << 26U)

//! Register bit ERRINT.EPIF. A change from error-passive to error-active or error-active to
//! error-passive has occurred.
#define CAN_FLAG_ERR_PASSIVE (1UL << 28U)

//! Register bit ERRINT.EPASS. The node is an error-passive node.
#define CAN_FLAG_ERR_PASSIVE_NODE (1UL << 30U)

//! Register bit ERRINT.EWARN. REC or TEC is greater than or equal to the LIMIT.EWL setting value.
#define CAN_FLAG_TEC_REC_WARN (1UL << 31U)

#define CAN_FLAG_ALL                                                                          \
    (CAN_FLAG_BUS_OFF | CAN_FLAG_TX_GOING | CAN_FLAG_RX_GOING | CAN_FLAG_RX_BUF_OVF           \
        | CAN_FLAG_TX_BUF_FULL | CAN_FLAG_TX_ABORTED | CAN_FLAG_ERR_INT | CAN_FLAG_STB_TX     \
        | CAN_FLAG_PTB_TX | CAN_FLAG_RX_BUF_WARN | CAN_FLAG_RX_BUF_FULL | CAN_FLAG_RX_OVERRUN \
        | CAN_FLAG_RX | CAN_FLAG_BUS_ERR | CAN_FLAG_ARBITR_LOST | CAN_FLAG_ERR_PASSIVE        \
        | CAN_FLAG_ERR_PASSIVE_NODE | CAN_FLAG_TEC_REC_WARN)

#define CAN_FLAG_CLR_ALL                                                                  \
    (CAN_FLAG_TX_ABORTED | CAN_FLAG_ERR_INT | CAN_FLAG_STB_TX | CAN_FLAG_PTB_TX           \
        | CAN_FLAG_RX_BUF_WARN | CAN_FLAG_RX_BUF_FULL | CAN_FLAG_RX_OVERRUN | CAN_FLAG_RX \
        | CAN_FLAG_BUS_ERR | CAN_FLAG_ARBITR_LOST | CAN_FLAG_ERR_PASSIVE)

//*****************************************************************************
//
// CAN_Tx_Request CAN Transmission Request
//
//*****************************************************************************

//! Transmit one STB frame.
#define CAN_TX_REQ_STB_ONE (CAN_CMD_TSONE)

//! Transmit all STB frames.
#define CAN_TX_REQ_STB_ALL (CAN_CMD_TSALL)

//! Transmit PTB frame.
#define CAN_TX_REQ_PTB (CAN_CMD_TPE)

//*****************************************************************************
//
// CAN_Miscellaneous_Macros CAN Miscellaneous Macros
//
//*****************************************************************************
#define CAN_RX_BUF_NUM (16U)

#define CAN_RX_WARN_MIN (1U)
#define CAN_RX_WARN_MAX (CAN_RX_BUF_NUM)

#define CAN_ERRINT_FLAG_MASK (CAN_ERRINT_BEIF | CAN_ERRINT_ALIF | CAN_ERRINT_EPIF)

//*****************************************************************************
//
// CAN_Err_Type CAN Error Type
//
//*****************************************************************************

//! No error.
#define CAN_ERR_NONE (0U)
//! Error is bit error.
#define CAN_ERR_BIT (0x1U)
//! Error is form error.
#define CAN_ERR_FORM (0x2U)
//! Error is stuff error.
#define CAN_ERR_STUFF (0x3U)
//! Error is ACK error.
#define CAN_ERR_ACK (0x4U)
//! Error is CRC error.
#define CAN_ERR_CRC (0x5U)
//! Error is other error.
//! Dominant bits after own error flag, received active Error Flag too long,
//! dominant bit during Passive-Error-Flag after ACK error.
#define CAN_ERR_OTHER (0x6U)

//*****************************************************************************
//
// PTB_SingleShot_Tx_En PTB Single Shot Transmission Function Control
//
//*****************************************************************************

//! Primary transmit buffer auto retransmit.
#define CAN_PTB_SINGLESHOT_TX_DISABLE (0x0U)
//! Primary transmit buffer single short transmit.
#define CAN_PTB_SINGLESHOT_TX_ENABLE (0x1U)

//*****************************************************************************
//
// STB_SingleShot_Tx_En STB Single Shot Transmission Function Control
//
//*****************************************************************************

//! Secondary transmit buffer auto retransmit.
#define CAN_STB_SINGLESHOT_TX_DISABLE (0x0U)
//! Secondary transmit buffer single short transmit.
#define CAN_STB_SINGLESHOT_TX_ENABLE (0x1U)

//*****************************************************************************
//
// CAN_STB_Prio_Mode_En CAN STB Priority Mode Function Control
// frame in the PTB has always the highest priority regardless of the ID.
//
//*****************************************************************************

//! The frame first in will first be transmitted.
#define CAN_STB_PRIO_MD_DISABLE (0x0U)
//! The frame with lower ID will first be transmitted.
#define CAN_STB_PRIO_MD_ENABLE (0x1U)

//*****************************************************************************
//
// CAN_Rx_All_En CAN Receive All Frames
//
//*****************************************************************************

//! Only receives correct frames.
#define CAN_RX_ALL_FRAME_DISABLE (0x0U)
//! Receives all frames, including frames with error.
#define CAN_RX_ALL_FRAME_ENABLE (0x1U)

//*****************************************************************************
//
// CAN_Rx_Ovf_Mode CAN Receive Buffer Overflow Mode
//
//*****************************************************************************
//! Saves the newly received data and the oldest frame will be overwritten.
#define CAN_RX_OVF_SAVE_NEW (0x0U)
//! Discard the newly received data.
#define CAN_RX_OVF_DISCARD_NEW (0x1U)

//*****************************************************************************
//
// CAN_Self_ACK_En CAN Self-ACK Function Control
//
//*****************************************************************************
//! Disable self-acknowledge.
#define CAN_SELF_ACK_DISABLE (0x0U)
//! Enable self-acknowledge.
#define CAN_SELF_ACK_ENABLE (0x1U)

//*****************************************************************************
//
// CAN_FD enable
//
//*****************************************************************************
#define CAN_FD_DISABLE (0x0U)
#define CAN_FD_ENABLE  (0x1U)

//*****************************************************************************
//
// CAN_FD_Mode CAN-FD Mode
//
//*****************************************************************************
//! Bosch CAN FD (non-ISO) mode.
#define CAN_FD_MD_BOSCH (0x0U)
//! ISO CAN FD mode (ISO 11898-1:2015).
#define CAN_FD_MD_ISO (0x1U)

//*****************************************************************************
//
// CAN_FD_TDC_En CAN-FD TDC Function Control
//
//*****************************************************************************
//! Disable transmitter delay compensation.
#define CAN_FD_TDC_DISABLE (0x0U)
//! Enable transmitter delay compensation.
#define CAN_FD_TDC_ENABLE (0x1U)

//*****************************************************************************
//
// CAN_Tx_Buf_Type CAN Transmit Buffer Type
//
//*****************************************************************************
//! Primary transmit buffer.
#define CAN_TX_BUF_PTB (0U)
//! Secondary transmit buffer.
#define CAN_TX_BUF_STB (1U)

//*****************************************************************************
//
// CAN_Data_Length_Code CAN Data Length Code
//
//*****************************************************************************
//! CAN2.0 and CAN FD: the size of data field is 0 bytes.
#define CAN_DLC0 (0x0U)

//! CAN2.0 and CAN FD: the size of data field is 1 bytes.
#define CAN_DLC1 (0x1U)

//! CAN2.0 and CAN FD: the size of data field is 2 bytes.
#define CAN_DLC2 (0x2U)

//! CAN2.0 and CAN FD: the size of data field is 3 bytes.
#define CAN_DLC3 (0x3U)

//! CAN2.0 and CAN FD: the size of data field is 4 bytes.
#define CAN_DLC4 (0x4U)

//! CAN2.0 and CAN FD: the size of data field is 5 bytes.
#define CAN_DLC5 (0x5U)

//! CAN2.0 and CAN FD: the size of data field is 6 bytes.
#define CAN_DLC6 (0x6U)

//! CAN2.0 and CAN FD: the size of data field is 7 bytes.
#define CAN_DLC7 (0x7U)

//! CAN2.0 and CAN FD: the size of data field is 8 bytes.
#define CAN_DLC8 (0x8U)

//! CAN FD: the size of data field is 12 bytes.
#define CAN_DLC12 (0x9U)

//! CAN FD: the size of data field is 16 bytes.
#define CAN_DLC16 (0xAU)

//! CAN FD: the size of data field is 20 bytes.
#define CAN_DLC20 (0xBU)

//! CAN FD: the size of data field is 24 bytes.
#define CAN_DLC24 (0xCU)

//! CAN FD: the size of data field is 32 bytes.
#define CAN_DLC32 (0xDU)

//! CAN FD: the size of data field is 48 bytes.
#define CAN_DLC48 (0xEU)

//! CAN FD: the size of data field is 64 bytes.
#define CAN_DLC64 (0xFU)

//*****************************************************************************
//
// CAN_Rx_Buf_Status CAN Receive Buffer Status
//
//*****************************************************************************
//! Receive buffer is empty.
#define CAN_RX_BUF_EMPTY (0x0U)
//! Receive buffer is not empty, but is less than almost full warning limit.
#define CAN_RX_BUF_NOT_WARN (0x1U)
//! Receive buffer is not full and not overflow, but is more than or equal to almost full warning
//! limit.
#define CAN_RX_BUF_WARN (0x2U)
//! Receive buffer is full.
#define CAN_RX_BUF_FULL (0x3U)

//*****************************************************************************
//
// CAN error information structure.
//
//*****************************************************************************
typedef struct
{
    uint8_t arbitrLostPos; //!< Bit position in the frame where the arbitration has been lost.
    uint8_t errorType;     //!< CAN error type. This parameter can be a value of @ref CAN_Err_Type
    uint8_t rxErrorCount;  //!< Receive error count.
    uint8_t txErrorCount;  //!< Transmit error count.
} CAN_Error_Info;

//*****************************************************************************
//
// CANFD configure structure.
//
//*****************************************************************************
typedef struct
{

    uint8_t mode;      //!< CAN-FD mode, Bosch CAN-FD or ISO 11898-1:2015 CAN-FD.
                       //!< This parameter can be a value of @ref CAN_FD_Mode */
    uint8_t TDC;       //!< Enable or disable Transmitter Delay Compensation.
                       //!< This parameter can be a value of @ref CAN_FD_TDC_En */
    uint8_t SSPOffset; //!< Specifies Secondary Sample Point offset.
                       //!< The transmitter delay plus u8SSPOffset defines the time of the secondary
                       //!< sample point for TDC.
                       //!< u8SSPOffset is given as a number of TQ. Range is [0, 127]
} CANFD_Config;

//*****************************************************************************
//
// CAN initialization structure..
//
//*****************************************************************************
typedef struct
{
    uint8_t STBPrioMode; //!< Enable or disable the priority decision mode of STB.
                         //!< This parameter can be a value of @ref CAN_STB_Prio_Mode_En
                         //!< NOTE: A frame in the PTB has always the highest priority regardless of
                         //!< the ID. */
    uint8_t canFDControl;
    CANFD_Config *ptrCanFd; //!< Pointer to a CAN-FD configuration structure. @ref
                            //!< stc_canfd_config_t Set it to NULL if not needed CAN-FD. */
} CAN_Init_Config;

//*****************************************************************************
//
// CAN TBUF control structure.
//
//*****************************************************************************
typedef struct
{
    uint8_t TTSEN;
    union
    {
        uint32_t u32TBUFCtrlAll;
        struct
        {
            uint32_t DLC : 4; //!< Data length code. Length of the data segment of data frame.
                              //!< It should be zero while the frame is remote frame.
                              //!< This parameter can be a value of @ref CAN_Data_Length_Code */
            uint32_t BRS : 1; //!< Bit rate switch. */
            uint32_t FDF : 1; //!< CAN FD frame. */
            uint32_t
                RTR : 1; //!< Remote transmission request bit.
                         //!< It is used to distinguish between data frames and remote frames. */
            uint32_t IDE : 1;   //!< Identifier extension flag.
                                //!< It is used to distinguish between standard format and extended
                                //!< format. This parameter can be a 1 or 0. */
            uint32_t RSVD : 24; //!< Reserved bits. */
        };
    };
} CAN_TBUF_Ctrl;

//*****************************************************************************
//
// CAN RBUF control structure.
//
//*****************************************************************************
typedef struct
{
    union
    {
        uint32_t u32RBUFCtrlAll;
        struct
        {
            uint32_t DLC : 4; //!< Data length code. Length of the data segment of data frame.
                              //!< It should be zero while the frame is remote frame.
                              //!< This parameter can be a value of @ref CAN_Data_Length_Code */
            uint32_t BRS : 1; //!< Bit rate switch. */
            uint32_t FDF : 1; //!< CAN FD frame. */
            uint32_t
                RTR : 1; //!< Remote transmission request bit.
                         //!< It is used to distinguish between data frames and remote frames. */
            uint32_t IDE : 1;  //!< Identifier extension flag.
                               //!< It is used to distinguish between standard format and extended
                               //!< format. This parameter can be 1 or 0. */
            uint32_t RSVD : 4; //!< Reserved bits. */
            uint32_t TX   : 1; //!< This bit is set to 1 when receiving self-transmitted data in
                               //!< loopback mode. */
            uint32_t ERRT       : 3;  //!< Error type. */
            uint32_t CYCLE_TIME : 16; //!< Cycle time of time-triggered communication(TTC). */
        };
    };
} CAN_RBUF_Ctrl;

//*****************************************************************************
//
// Functional state
//
//*****************************************************************************
typedef enum
{
    DISABLE = 0U,
    ENABLE  = 1U,
} EN_Functional_Status;

//*****************************************************************************
//
// Flag status
//
//*****************************************************************************
typedef enum
{
    RESET = 0U,
    SET   = 1U,
} EN_Flag_Status;

//*****************************************************************************
//
// CAN mode type
//
//*****************************************************************************
typedef enum
{
    CAN_WORK_MD_NORMAL,     //!< Normal work mode. */
    CAN_WORK_MD_SILENT,     //!< Silent work mode. Prohibit data transmission. */
    CAN_WORK_MD_ILB,        //!< Internal loop back mode, just for self-test while developing. */
    CAN_WORK_MD_ELB,        //!< External loop back mode, just for self-test while developing. */
    CAN_WORK_MD_ELB_SILENT, //!< External loop back silent mode, just for self-test while
                            //!< developing. It is forbidden to respond to received frames and error
                            //!< frames, but data can be transmitted. */
} CAN_ModeType;

//*****************************************************************************
//
// CAN command type
//
//*****************************************************************************
typedef enum
{
    CAN_CMD_TSA   = 0x01U, //!< Transmit Secondary Abort.
    CAN_CMD_TSALL = 0x02U, //!< Transmit Secondary ALL frame.
    CAN_CMD_TSONE = 0x04U, //!< Transmit Secondary ONE frame.
    CAN_CMD_TPA   = 0x08U, //!< Transmit Primary Abort.
    CAN_CMD_TPE   = 0x10U, //!< Transmit Primary Enable.
    CAN_CMD_STBY  = 0x20U, //!< Transceiver standby mode.
    CAN_CMD_LOM   = 0x40U, //!< Listen Only Mode.
    CAN_CMD_TBSEL = 0x80U, //!< Transmit Buffer Select.
    CAN_CMD_NO    = 0x00U,
} CAN_CmdType;

//*****************************************************************************
//
// CAN  sending timestamps enable
//
//*****************************************************************************
typedef enum
{
    CAN_TTSEN_DISABLE = 0x0U,
    CAN_TTSEN_ENABLE  = 0x1U,
} CAN_TTSEN;

//*****************************************************************************
//
// CAN  IDentifier Extension
//
//*****************************************************************************
typedef enum
{
    CAN_IDE_STANDARD = 0x0U, //!< standard ID.
    CAN_IDE_EXTEND   = 0x1U, //!< extended ID.
} CAN_IDE;

//*****************************************************************************
//
// CAN remote transmit request
//
//*****************************************************************************
typedef enum
{
    CAN_RTR_DATA   = 0x0U, //!< DATA frame.
    CAN_RTR_REMOTE = 0x1U, //!< remote frame.
} CAN_RTR;

//*****************************************************************************
//
// CANFD frame
//
//*****************************************************************************
typedef enum
{
    CAN_FDF_CAN20 = 0x0U, //!< CAN 2.0 frame.
    CAN_FDF_CANFD = 0x1U, //!< CANFD frame.
} CAN_FDF;

//*****************************************************************************
//
// CAN bit rate switch
//
//*****************************************************************************
typedef enum
{
    CANFD_BRS_SLOW = 0x0U, //!< All frame is slow bit rate
    CANFD_BRS_FAST = 0x1U, //!< DATA and CRC domain:fast bit rate
} CANFD_BRS;

//*****************************************************************************
//
// CAN_Interrupt_Type CAN Interrupt Type
//
//*****************************************************************************
typedef enum
{
    CAN_INT_NONE  = 0x00U,
    CAN_INT_EIE   = 0x02U, //!< Register bit RTIE.EIE. Error interrupt.
    CAN_INT_TSIE  = 0x04U, //!< Register bit RTIE.TSIE. STB was transmitted successfully.
    CAN_INT_TPIE  = 0x08U, //!< Register bit RTIE.TPIE. PTB was transmitted successfully.
    CAN_INT_RAFIE = 0x10U, //!< Register bit RTIE.RAFIE. The number of filled RB slot is greater
                           //!< than or equal to the LIMIT.AFWL setting value.
    CAN_INT_RFIE = 0x20U,  //!< Register bit RTIE.RFIE. The FIFO of receive buffer is full.
    CAN_INT_ROIE = 0x40U,  //!< Register bit RTIE.ROIE. Receive buffers are full and there is a
                           //!< further message to be stored.
    CAN_INT_RIE = 0x80U,   //!< Register bit RTIE.RIE. Received a valid data frame or remote frame.
    CAN_INT_ERROR_BEIE = 0x200U,  //!< Register bit ERRINT.BEIE. Arbitration lost caused bus error
    CAN_INT_ERROR_ALIE = 0x800U,  //!< Register bit ERRINT.ALIE. Arbitration lost.
    CAN_INT_ERROR_EPIE = 0x2000U, //!< Register bit ERRINT.EPIE. A change from error-passive to
                                  //!< error-active or error-active to error-passive has occurred.
    CAN_INT_ALL
    = (CAN_INT_EIE | CAN_INT_TSIE | CAN_INT_TPIE | CAN_INT_RAFIE | CAN_INT_RFIE | CAN_INT_ROIE
        | CAN_INT_RIE | CAN_INT_ERROR_BEIE | CAN_INT_ERROR_ALIE | CAN_INT_ERROR_EPIE)

} CAN_IntType;

//*****************************************************************************
//
// CAN_Local_Variables CAN Local Variables.
//
//*****************************************************************************
const static uint8_t myDLC2Size[16U]
    = { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U };

//*****************************************************************************
//
//! \internal
//!
//! Checks a CAN base address.
//!
//! \param base is the base address of the CAN controller.
//!
//! This function determines if a CAN controller base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool CAN_isBaseValid(uint32_t base)
{
    return ((base == CANA_BASE) || (base == CANB_BASE));
}
#endif

//*****************************************************************************
//
//! Initializes the specified CAN peripheral according to the specified parameters
//! in the structure pstcCanInit.
//!
//! \param base is the base address of the CAN module.
//! \param ptrCanInit is the Initializes configuration of the CAN module.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAN_initParameterCheck(uint32_t base, const CAN_Init_Config *ptrCanInit)
{

    CANFD_Config *ptrCanFd = ptrCanInit->ptrCanFd;
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((ptrCanInit->STBPrioMode == CAN_STB_PRIO_MD_DISABLE)
           || (ptrCanInit->STBPrioMode == CAN_STB_PRIO_MD_ENABLE));
    ASSERT((ptrCanInit->canFDControl == CAN_FD_DISABLE)
           || (ptrCanInit->canFDControl == CAN_FD_ENABLE));
    if (ptrCanFd != NULL)
    {
        ASSERT((ptrCanFd->mode == CAN_FD_MD_BOSCH) || (ptrCanFd->mode == CAN_FD_MD_ISO));
        ASSERT((ptrCanFd->TDC == CAN_FD_TDC_DISABLE) || (ptrCanFd->TDC == CAN_FD_TDC_ENABLE));
        ASSERT((ptrCanFd->SSPOffset) < 128U);
    }
}

//*****************************************************************************
//
//! Specifies work mode for the specified CAN unit.
//!
//! \param base is the base address of the CAN module.
//! \param u8WorkMode is the  Work mode of CAN.It should be one of the following values.
//!
//!  - \b  CAN_WORK_MD_NORMAL:          Normal work mode.
//!  - \b  CAN_WORK_MD_SILENT:          Silent work mode. Prohibit data transmission.
//!  - \b  CAN_WORK_MD_ILB:             Internal loop back mode, just for self-test while
//!  developing.
//!  - \b  CAN_WORK_MD_ELB:             External loop back mode, just for self-test while
//!  developing.
//!  - \b CAN_WORK_MD_ELB_SILENT:       External lopp back silent mode, just for self-test while
//!  developing.
//!                                     It is forbidden to respond to received frames and error
//!                                     frames, but data can be transmitted.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAN_setWorkMode(uint32_t base, CAN_ModeType workMode)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    switch (workMode)
    {
        case CAN_WORK_MD_SILENT:
            ((volatile struct CAN_REGS *)base)->TCMD.bit.LOM = 1u;
            break;
        case CAN_WORK_MD_ILB:
            ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.LBMI = 1u;
            break;
        case CAN_WORK_MD_ELB:
            ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.LBME = 1u;
            break;
        case CAN_WORK_MD_ELB_SILENT:
            ((volatile struct CAN_REGS *)base)->TCMD.bit.LOM     = 1u;
            ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.LBME = 1u;
            break;
        case CAN_WORK_MD_NORMAL:
        default:
            break;
    }
}

//*****************************************************************************
//
//! Configures the specified CAN FD according to the specified parameters
//!
//! \param base is the base address of the CAN module.
//! \param ptrCanFd Pointer to a @ref CANFD_Config structure.
//!
//!  - \b  CAN_WORK_MD_NORMAL:          Normal work mode.
//!  - \b  CAN_WORK_MD_SILENT:          Silent work mode. Prohibit data transmission.
//!  - \b  CAN_WORK_MD_ILB:             Internal loop back mode, just for self-test while
//!  developing.
//!  - \b  CAN_WORK_MD_ELB:             External loop back mode, just for self-test while
//!  developing.
//!  - \b CAN_WORK_MD_ELB_SILENT:       External lopp back silent mode, just for self-test while
//!  developing.
//!                                     It is forbidden to respond to received frames and error
//!                                     frames, but data can be transmitted.
//!
//! \return None.
//
//*****************************************************************************
static inline void CANFD_config(uint32_t base, const CANFD_Config *ptrCanFd)
{

    //
    // Specifies CAN FD ISO mode.
    //
    ((volatile struct CAN_REGS *)base)->TCTRL.bit.FD_ISO = ptrCanFd->mode;

    //
    // Specifies the secondary sample point. Number of TQ.Enable or disable TDC.
    //
    ((volatile struct CAN_REGS *)base)->TDC.bit.TDCEN  = ptrCanFd->TDC;
    ((volatile struct CAN_REGS *)base)->TDC.bit.SSPOFF = ptrCanFd->SSPOffset;
}

//*****************************************************************************
//
//! Write TX buffer register in bytes.
//!
//! \param base is the base address of the CAN module.
//! \param msgID is the message ID of the CAN data frame.
//! \param ptrTBUFCtrl Pointer to a @ref CAN_TBUF_Ctrl structure.
//! \param msgData Pointer to the message data of the CAN data frame.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAN_writeDataReg(
    uint32_t base, const uint32_t msgID, const CAN_TBUF_Ctrl *ptrTBUFCtrl, const void *msgData)
{
    uint8_t i;
    uint8_t tempBuf[64U] = { 0U };

    volatile uint32_t *reg32TBUF
        = (volatile uint32_t *)((uint32_t) & ((volatile struct CAN_REGS *)base)->TBUF[0U]);

    reg32TBUF[0U] = msgID;
    reg32TBUF[0U] |= ptrTBUFCtrl->TTSEN << 31U;
    reg32TBUF[1U] = ptrTBUFCtrl->u32TBUFCtrlAll;

    for (int i = 0U; i < myDLC2Size[ptrTBUFCtrl->DLC]; i++)
    {
        tempBuf[i] = *((uint8_t *)msgData + i);
    }

    if (ptrTBUFCtrl->DLC != 0u)
    {
        for (i = 0U; i < (myDLC2Size[ptrTBUFCtrl->DLC] + 3U) / 4U; i++)
        {
            reg32TBUF[2U + i] = *((uint32_t *)(&tempBuf[i * 4]));
        }
    }
}

//*****************************************************************************
//
//! Read RX buffer register in bytes.
//! Only read the data of CAN RX buffer
//!
//! \param base is the base address of the CAN module.
//! \param msgData Pointer to the message data of the CAN data frame.
//!
//! \return None.
//
//*****************************************************************************
static inline void CAN_readDataReg(uint32_t base, void *msgData)
{
    uint8_t myDLC;
    volatile struct CAN_REGS *can  = (volatile struct CAN_REGS *)base;
    volatile uint8_t *reg8RBUFData = (volatile uint8_t *)(&can->RBUF[2U]);

    myDLC = myDLC2Size[can->RBUF[1] & 0xFU];

    for (uint8_t i = 0; i < myDLC; i++)
    {
        *((uint8_t *)msgData + i) = *(reg8RBUFData + i);
    }
}

//*****************************************************************************
//
//! Read the value of the SBT register.
//!
//! \param base is the base address of the CAN module.
//!
//! \return the value of the SBT register.
//
//*****************************************************************************
static inline uint32_t CAN_getBitTimingSlow(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Read and return SBT register
    //
    return (*((volatile uint32_t *)(base + 0xA8)));
}

//*****************************************************************************
//
//! Read the value of the FBT register.
//!
//! \param base is the base address of the CAN module.
//!
//! \return the value of the FBT register.
//
//*****************************************************************************
static inline uint32_t CAN_getBitTimingFast(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    //
    // Read and return FBT register
    //
    return (*((volatile uint32_t *)(base + 0xAC)));
}

//*****************************************************************************
//
//! Read whether the CAN module is in the sending busy state
//!
//! \param base is the base address of the CAN module.
//!
//! \return Returns \b 1 if the CAN module is in the sending busy state
//! , and \b 0 if the CAN module is not busy
//
//*****************************************************************************
static inline uint32_t CAN_isTransmitterBusy(uint32_t base)
{
    return ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.TACTIVE;
}

//*****************************************************************************
//
//! Enable the CAN module enter reset state.
//!
//! \param base is the base address of the CAN module.
//!
//! \return None
//
//*****************************************************************************
static inline void CAN_enableStatReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    //
    // Software reset.
    //
    ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.RESET = ENABLE;
}

//*****************************************************************************
//
//! Enable the CAN module enter normal communication mode.
//!
//! \param base is the base address of the CAN module.
//!
//! \return None
//
//*****************************************************************************
static inline void CAN_disableStatReset(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    //
    // CAN enters normal communication mode.
    //
    ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.RESET = DISABLE;
}

//*****************************************************************************
//
//! Enable the CAN module Primary transmit buffer single short transmit..
//!
//! \param base is the base address of the CAN module.
//!
//! \return None
//
//*****************************************************************************
static inline void CAN_enableTPSS(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.TPSS = ENABLE;
}

//*****************************************************************************
//
//! Disable the CAN module Primary transmit buffer single short transmit..
//!
//! \param base is the base address of the CAN module.
//!
//! \return None
//
//*****************************************************************************
static inline void CAN_disableTPSS(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.TPSS = DISABLE;
}

//*****************************************************************************
//
//! Enable the CAN module Secondary transmit buffer single short transmit.
//!
//! \param base is the base address of the CAN module.
//!
//! \return None
//
//*****************************************************************************
static inline void CAN_enableTSSS(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.TSSS = ENABLE;
}

//*****************************************************************************
//
//! Disable the CAN module Secondary transmit buffer single short transmit.
//!
//! \param base is the base address of the CAN module.
//!
//! \return None
//
//*****************************************************************************
static inline void CAN_disableTSSS(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ((volatile struct CAN_REGS *)base)->CFGSTAT.bit.TSSS = DISABLE;
}

//*****************************************************************************
//
//! Configure the CAN module RCTRL register.
//!
//! \param base is the base address of the CAN module.
//! \param rxOvfMode is Receive buffer overflow mode. In case of a full receive buffer when a new
//! frame is received.
//!     This parameter can be a value of @ref CAN_Rx_Ovf_Mode */
//! \param is Enable or disable receive all frames(includes frames with error).
//!     This parameter can be a value of @ref CAN_Rx_All_En */
//! \param is Enable or disable self-acknowledge.
//!     his parameter can be a value of @ref CAN_Self_ACK_En */
//!
//! \return None
//
//*****************************************************************************
static inline void CAN_setRCTRL(
    uint32_t base, uint8_t rxOvfMode, uint8_t rxAllFrame, uint8_t selfAck)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((rxOvfMode == CAN_RX_OVF_SAVE_NEW) || (rxOvfMode == CAN_RX_OVF_DISCARD_NEW));
    ASSERT((rxAllFrame == CAN_RX_ALL_FRAME_DISABLE) || (rxAllFrame == CAN_RX_ALL_FRAME_ENABLE));
    ASSERT((selfAck == CAN_SELF_ACK_DISABLE) || (selfAck == CAN_SELF_ACK_ENABLE));
    //
    // Enable or disable RX all frames(include frames with error).
    // Specifies receive overflow mode. In case of a full rx buffer when a new message is received.
    // Enable or disable self-acknowledge.
    //
    ((volatile struct CAN_REGS *)base)->RCTRL.bit.RBALL = rxAllFrame;
    ((volatile struct CAN_REGS *)base)->RCTRL.bit.ROM   = rxOvfMode;
    ((volatile struct CAN_REGS *)base)->RCTRL.bit.SACK  = selfAck;
}

//*****************************************************************************
//
//! Initializes the specified CAN peripheral according to the specified parameters
//! in the structure ptrCanInit.
//!
//! \param base is the base address of the CAN module.
//! \param ptrCanInit Pointer to a @ref CAN_Init_Config structure value that
//!        contains the configuration information for the CAN.
//!
//! \return None
//
//*****************************************************************************
extern void CAN_initModule(uint32_t base, const CAN_Init_Config *ptrCanInit);

//*****************************************************************************
//
//! Set each @ref CAN_Init_Config field to a default value.
//!
//! \param ptrCanInit Pointer to a @ref CAN_Init_Config structure
//!        whose fields will be set to default values.
//!
//! \return None
//
//*****************************************************************************
extern void CAN_structInit(CAN_Init_Config *ptrCanInit);

//*****************************************************************************
//
//! Set each @ref CANFD_Config field to a default value.
//!
//! \param ptrCanFd Pointer to a @ref CANFD_Config structure
//!        whose fields will be set to default values.
//!
//! \return None
//
//*****************************************************************************
extern void CANFD_structInit(CANFD_Config *ptrCanFd);

//*****************************************************************************
//
//! Set slow bit rate.
//!
//! \param base is the base address of the CAN module.
//! \param s_prescale is the prescaler of CAN clock, [1, 256].
//! \param s_seg1 Specifies the number of time quanta in Bit Segment 1.
//!  s_seg1 Contains synchronization segment,
//!  propagation time segment and phase buffer segment 1
//! \param s_seg2 Specifies the number of time quanta in Bit Segment 2.
//!  Phase buffer segment 2.
//! \param s_sjw Synchronization Jump Width.
//!  Specifies the maximum number of time quanta the CAN hardware
//!  is allowed to lengthen or shorten a bit to perform resynchronization.
//!
//! \return None
//
//*****************************************************************************
extern void CAN_setBitTimingSlow(
    uint32_t base, uint16_t s_prescale, uint16_t s_seg1, uint16_t s_seg2, uint16_t s_sjw);

//*****************************************************************************
//
//! Auto Set slow bit rate.
//!
//! \param base is the base address of the CAN module.
//! \param clockFreq is the CPU sys clock.
//! \param bitRate is can slow bit rate
//! \param bitTime is the number of all time quanta .
//!
//! \return None
//
//*****************************************************************************
extern void CAN_setBitRateSlow(
    uint32_t base, uint32_t clockFreq, uint32_t bitRate, uint16_t bitTime);

//*****************************************************************************
//
//! Set fast bit rate.
//!
//! \param base is the base address of the CAN module.
//! \param f_prescale is the prescaler of CAN clock, [1, 256].
//! \param f_seg1 Specifies the number of time quanta in Bit Segment 1.
//!  f_seg1 Contains synchronization segment,
//!  propagation time segment and phase buffer segment 1
//! \param f_seg2 Specifies the number of time quanta in Bit Segment 2.
//!  Phase buffer segment 2.
//! \param f_sjw Synchronization Jump Width.
//!  Specifies the maximum number of time quanta the CAN hardware
//!  is allowed to lengthen or shorten a bit to perform resynchronization.
//!
//! \return None
//
//*****************************************************************************
extern void CANFD_setBitTimingFast(
    uint32_t base, uint16_t f_prescale, uint16_t f_seg1, uint16_t f_seg2, uint16_t f_sjw);

//*****************************************************************************
//
//! Auto Set fast bit rate.
//!
//! \param base is the base address of the CAN module.
//! \param clockFreq is the CPU sys clock.
//! \param bitRate is can fast bit rate
//! \param bitTime is the number of all time quanta .
//!
//! \return None
//
//*****************************************************************************
extern void CANFD_setBitRateFast(
    uint32_t base, uint32_t clockFreq, uint32_t bitRate, uint16_t bitTime);

//*****************************************************************************
//
//! Set Acceptance filters
//!
//! \param base is the base address of the CAN module.
//! \param acfSelect Acceptance filters selection.
//!        This parameter can be values of @ref CAN_Acceptance_Filter
//! \param idType Specifies the identifier(ID) type. This parameter can be a value of @ref
//! CAN_ID_Type \param idCode Specifies the identifier(ID). 11 bits standard ID or 29 bits extended
//! ID, depending on IDE. \param idMask Specifies the identifier(ID) mask. The mask bits of ID will
//! be ignored by the acceptance filter.
//!
//! \return None
//
//*****************************************************************************
extern void CAN_setAcceptFilter(
    uint32_t base, uint16_t acfSelect, uint32_t idType, uint32_t idCode, uint32_t idMask);

//*****************************************************************************
//
//! Enable or disable the specifies acceptance filters
//!
//! \param base is the base address of the CAN module.
//! \param acfSelect Acceptance filters selection.
//!        This parameter can be values of @ref CAN_Acceptance_Filter
//! \param enFilterState /b ENABLE or /b DISABLE
//!
//! \return None
//
//*****************************************************************************
extern void CAN_filterCmd(uint32_t base, uint16_t acfEnSelect, EN_Functional_Status enFilterState);

//*****************************************************************************
//
//! Get the status of specified flag.
//!
//! \param base is the base address of the CAN module.
//! \param flag is CAN status flag.
//!         This parameter can be a value of @ref CAN_Status_Flag
//!
//! \return None
//
//*****************************************************************************
extern EN_Flag_Status CAN_getStatus(uint32_t base, uint32_t flag);

//*****************************************************************************
//
//! clear the status of specified flag.
//!
//! \param base is the base address of the CAN module.
//! \param flag is CAN status flag.
//!         This parameter can be a value of @ref CAN_Status_Flag
//!
//! \return None
//
//*****************************************************************************
extern void CAN_clearInterruptStatus(uint32_t base, uint32_t flag);

//*****************************************************************************
//
//! Get status(full or empty) of transmit buffer.
//!
//! \param base is the base address of the CAN module.
//!
//! \return An uint8_t type value of status of transmit buffer.
//
//*****************************************************************************
extern uint8_t CAN_getTxBufStatus(uint32_t base);

//*****************************************************************************
//
//! Get status(full or empty) of receive buffer.
//!
//! \param base is the base address of the CAN module.
//!
//! \return An uint8_t type value of status of receive buffer.
//
//*****************************************************************************
extern uint8_t CAN_getRxBufStatus(uint32_t base);

//*****************************************************************************
//
//! Get the information of CAN errors.
//!
//! \param base is the base address of the CAN module.
//! \param ptrErr is the Pointer to a @ref CAN_Error_Info structure.
//!
//! \return the error count whether reach the error warning limit .
//
//*****************************************************************************
extern bool CAN_getErrorInfo(uint32_t base, CAN_Error_Info *ptrErr);

//*****************************************************************************
//
//! Set the receive warning limit count.
//!
//! \param base is the base address of the CAN module.
//! \param rxWarnLimit Receive buffer full warning limit.
//!
//! \return none
//
//*****************************************************************************
extern void CAN_setRxWarnLimit(uint32_t base, uint8_t rxWarnLimit);

//*****************************************************************************
//
//! Set error warning limit.
//!
//! \param base is the base address of the CAN module.
//! \param errorWarnLimit Programmable error warning limit. Range is [0, 15].
//!     Error warning limit = (errorWarnLimit + 1) * 8.
//!
//! \return none
//
//*****************************************************************************
extern void CAN_setErrorWarnLimit(uint32_t base, uint8_t errorWarnLimit);

//*****************************************************************************
//
//! Starts transmission.
//!
//! \param base is the base address of the CAN module.
//! \param txRequest The transmit buffer to be transmitted.
//!        This parameter can be values of @ref CAN_Tx_Request
//!
//! \return none
//
//*****************************************************************************
extern void CAN_startTx(uint32_t base, uint8_t txRequest);

//*****************************************************************************
//
//! Abort  transmission.
//!
//! \param base is the base address of the CAN module.
//! \param txBufType The transmit buffer to be aborted.
//!        This parameter can be a value of @ref CAN_Tx_Buf_Type
//!
//! \return none
//
//*****************************************************************************
extern void CAN_abortTx(uint32_t base, uint8_t txBufType);

//*****************************************************************************
//
//! Fill the data frame to be transmit
//!
//! \param base is the base address of the CAN module.
//! \param txBufType The transmit buffer to be aborted.
//!        This parameter can be a value of @ref CAN_Tx_Buf_Type
//! \param msgID is the ID of the data frame
//! \param ptrTBUFCtrl is the Pointer to a @ref CAN_TBUF_Ctrl structure.
//! \param msgData is the Pointer to the data domain
//!
//! \return none
//
//*****************************************************************************
extern void CAN_fillMessage(uint32_t base, uint8_t txBufType, const uint32_t msgID,
    const CAN_TBUF_Ctrl *ptrTBUFCtrl, const void *msgData);

//*****************************************************************************
//
//! Fill the remote request frame to be transmit
//!
//! \param base is the base address of the CAN module.
//! \param txBufType The transmit buffer to be aborted.
//!        This parameter can be a value of @ref CAN_Tx_Buf_Type
//!\param msgID is the ID of the data frame
//!\param ptrTBUFCtrl is the Pointer to a @ref CAN_TBUF_Ctrl structure.
//!
//! \return none
//
//*****************************************************************************
extern void CAN_fillRemoteRequestMessage(
    uint32_t base, uint8_t txBufType, const uint32_t msgID, const CAN_TBUF_Ctrl *ptrTBUFCtrl);

//*****************************************************************************
//
//! Read RX buffer register in bytes.
//! only Read RX buffer data.
//!
//! \param base is the base address of the CAN module.
//! \param msgData is the Pointer to the data domain
//!
//! \return none
//
//*****************************************************************************
extern bool CAN_readMessage(uint32_t base, void *msgData);

//*****************************************************************************
//
//! Read RX buffer register in bytes.
//!
//! \param base is the base address of the CAN module.
//! \param msgData is the Pointer to the data domain
//!
//! \return none
//
//*****************************************************************************
extern bool CAN_readMessageWithID(
    uint32_t base, uint32_t *msgID, CAN_RBUF_Ctrl *ptrRBUFCtrl, void *msgData);

//*****************************************************************************
//
//! Enable the specified CAN interrupt.
//!
//! \param base is the base address of the CAN module.
//! \param ints Interrupt of CAN.
//!        This parameter can be values of @ref CAN_Interrupt_Type
//!
//! \return none
//
//*****************************************************************************
extern void CAN_enableInterrupt(uint32_t base, CAN_IntType ints);

//*****************************************************************************
//
//! Disable the specified CAN interrupt.
//!
//! \param base is the base address of the CAN module.
//! \param ints Interrupt of CAN.
//!        This parameter can be values of @ref CAN_Interrupt_Type
//!
//! \return none
//
//*****************************************************************************
extern void CAN_disableInterrupt(uint32_t base, CAN_IntType ints);

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
