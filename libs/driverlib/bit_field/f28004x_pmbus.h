#ifndef F28004X_PMBUS_H
#define F28004X_PMBUS_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// PMBUS Individual Register Bit Definitions:

typedef struct
{
    Uint32 MASTER_MODE                  : 1; /* [0] */
    Uint32 SPEED                        : 2; /* [2:1] */
    Uint32 IC_10BITADDR_SLAVE           : 1; /* [3] */
    Uint32 IC_10BITADDR_MASTER          : 1; /* [4] */
    Uint32 IC_RESTART_EN                : 1; /* [5] */
    Uint32 IC_SLAVE_DISABLE             : 1; /* [6] */
    Uint32 STOP_DET_IFADDRESSED         : 1; /* [7] */
    Uint32 TX_EMPTY_CTRL                : 1; /* [8] */
    Uint32 RX_FIFO_FULL_HLD_CTRL        : 1; /* [9] */
    Uint32 STOP_DET_IF_MASTER_ACTIVE    : 1; /* [10] */
    Uint32 BUS_CLEAR_FEATURE_CTRL       : 1; /* [11] */
    Uint32 RSVD_IC_CON_1                : 4; /* [15:12] */
    Uint32 OPTIONAL_SAR_CTRL            : 1; /* [16] */
    Uint32 SMBUS_SLAVE_QUICK_EN         : 1; /* [17] */
    Uint32 SMBUS_ARP_EN                 : 1; /* [18] */
    Uint32 SMBUS_PERSISTANT_SLV_ADDR_EN : 1; /* [19] */
} PMB_CON_BIT;

union PMB_CON_REG
{
    Uint32 all;
    PMB_CON_BIT bit;
};

typedef struct
{
    Uint32 TAR                 : 10; /* [9:0] */
    Uint32 GC_OR_START         : 1;  /* [10] */
    Uint32 SPECIAL             : 1;  /* [11] */
    Uint32 IC_10BITADDR_MASTER : 1;  /* [12] */
    Uint32 Device_ID           : 1;  /* [13] */
    Uint32 RSVD_IC_TAR_1       : 2;  /* [15:14] */
    Uint32 SMBUS_QUICK_CMD     : 1;  /* [16] */
    Uint32 RSVD_IC_TAR_2       : 15; /* [31:17] */
} PMB_TAR_BIT;

union PMB_TAR_REG
{
    Uint32 all;
    PMB_TAR_BIT bit;
};

typedef struct
{
    Uint32 IC_SAR   : 10; /* [9:0] */
    Uint32 Reserved : 22; /* [31:10] */
} PMB_SAR_BIT;

union PMB_SAR_REG
{
    Uint32 all;
    PMB_SAR_BIT bit;
};

typedef struct
{
    Uint32 DATA            : 8;  /* [7:0] */
    Uint32 CMD             : 1;  /* [8] */
    Uint32 STOP            : 1;  /* [9] */
    Uint32 RESTART         : 1;  /* [10] */
    Uint32 FIRST_DATA_BYTE : 1;  /* [11] */
    Uint32 Reserved        : 20; /* [31:12] */
} PMB_DATA_CMD_BIT;

union PMB_DATA_CMD_REG
{
    Uint32 all;
    PMB_DATA_CMD_BIT bit;
};

typedef struct
{
    Uint32 SS_SCL_HCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
} SS_SCL_HCNT_BIT;

union SS_SCL_HCNT_REG
{
    Uint32 all;
    SS_SCL_HCNT_BIT bit;
};

typedef struct
{
    Uint32 SS_SCL_LCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
} SS_SCL_LCNT_BIT;

union SS_SCL_LCNT_REG
{
    Uint32 all;
    SS_SCL_LCNT_BIT bit;
};

typedef struct
{
    Uint32 FS_SCL_HCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
} FS_SCL_HCNT_BIT;

union FS_SCL_HCNT_REG
{
    Uint32 all;
    FS_SCL_HCNT_BIT bit;
};

typedef struct
{
    Uint32 FS_SCL_LCNT : 16; /* [15:0] */
    Uint32 Reserved    : 16; /* [31:16] */
} FS_SCL_LCNT_BIT;

union FS_SCL_LCNT_REG
{
    Uint32 all;
    FS_SCL_LCNT_BIT bit;
};

typedef struct
{
    Uint32 RX_UNDER         : 1;  /* [0] */
    Uint32 RX_OVER          : 1;  /* [1] */
    Uint32 RX_FULL          : 1;  /* [2] */
    Uint32 TX_OVER          : 1;  /* [3] */
    Uint32 TX_EMPTY         : 1;  /* [4] */
    Uint32 RD_REQ           : 1;  /* [5] */
    Uint32 TX_ABRT          : 1;  /* [6] */
    Uint32 RX_DONE          : 1;  /* [7] */
    Uint32 ACTIVITY         : 1;  /* [8] */
    Uint32 STOP_DET         : 1;  /* [9] */
    Uint32 START_DET        : 1;  /* [10] */
    Uint32 GEN_CALL         : 1;  /* [11] */
    Uint32 RESTART_DET      : 1;  /* [12] */
    Uint32 MST_ON_HOLD      : 1;  /* [13] */
    Uint32 SCL_STUCK_AT_LOW : 1;  /* [14] */
    Uint32 WR_REQ           : 1;  /* [15] */
    Uint32 SLV_ADDR1_TAG    : 1;  /* [16] */
    Uint32 SLV_ADDR2_TAG    : 1;  /* [17] */
    Uint32 SLV_ADDR3_TAG    : 1;  /* [18] */
    Uint32 SLV_ADDR4_TAG    : 1;  /* [19] */
    Uint32 Reserved         : 12; /* [31:20 */
} PMB_INTR_STAT_BIT;

union PMB_INTR_STAT_REG
{
    Uint32 all;
    PMB_INTR_STAT_BIT bit;
};

typedef struct
{
    Uint32 RX_UNDER         : 1;  /* [0] */
    Uint32 RX_OVER          : 1;  /* [1] */
    Uint32 RX_FULL          : 1;  /* [2] */
    Uint32 TX_OVER          : 1;  /* [3] */
    Uint32 TX_EMPTY         : 1;  /* [4] */
    Uint32 RD_REQ           : 1;  /* [5] */
    Uint32 TX_ABRT          : 1;  /* [6] */
    Uint32 RX_DONE          : 1;  /* [7] */
    Uint32 ACTIVITY         : 1;  /* [8] */
    Uint32 STOP_DET         : 1;  /* [9] */
    Uint32 START_DET        : 1;  /* [10] */
    Uint32 GEN_CALL         : 1;  /* [11] */
    Uint32 RESTART_DET      : 1;  /* [12] */
    Uint32 MST_ON_HOLD      : 1;  /* [13] */
    Uint32 SCL_STUCK_AT_LOW : 1;  /* [14] */
    Uint32 WR_REQ           : 1;  /* [15] */
    Uint32 SLV_ADDR1_TAG    : 1;  /* [16] */
    Uint32 SLV_ADDR2_TAG    : 1;  /* [17] */
    Uint32 SLV_ADDR3_TAG    : 1;  /* [18] */
    Uint32 SLV_ADDR4_TAG    : 1;  /* [19] */
    Uint32 Reserved         : 12; /* [31:20 */
} PMB_INTR_MASK_BIT;

union PMB_INTR_MASK_REG
{
    Uint32 all;
    PMB_INTR_MASK_BIT bit;
};

typedef struct
{
    Uint32 R_RX_UNDER         : 1;  /* [0] */
    Uint32 R_RX_OVER          : 1;  /* [1] */
    Uint32 R_RX_FULL          : 1;  /* [2] */
    Uint32 R_TX_OVER          : 1;  /* [3] */
    Uint32 R_TX_EMPTY         : 1;  /* [4] */
    Uint32 R_RD_REQ           : 1;  /* [5] */
    Uint32 R_TX_ABRT          : 1;  /* [6] */
    Uint32 R_RX_DONE          : 1;  /* [7] */
    Uint32 R_ACTIVITY         : 1;  /* [8] */
    Uint32 R_STOP_DET         : 1;  /* [9] */
    Uint32 R_START_DET        : 1;  /* [10] */
    Uint32 R_GEN_CALL         : 1;  /* [11] */
    Uint32 R_RESTART_DET      : 1;  /* [12] */
    Uint32 R_MST_ON_HOLD      : 1;  /* [13] */
    Uint32 R_SCL_STUCK_AT_LOW : 1;  /* [14] */
    Uint32 R_WR_REQ           : 1;  /* [15] */
    Uint32 R_SLV_ADDR1_TAG    : 1;  /* [16] */
    Uint32 R_SLV_ADDR2_TAG    : 1;  /* [17] */
    Uint32 R_SLV_ADDR3_TAG    : 1;  /* [18] */
    Uint32 R_SLV_ADDR4_TAG    : 1;  /* [19] */
    Uint32 Reserved           : 12; /* [31:20 */
} PMB_RAW_INTR_STAT_BIT;

union PMB_RAW_INTR_STAT_REG
{
    Uint32 all;
    PMB_RAW_INTR_STAT_BIT bit;
};

typedef struct
{
    Uint32 RX_TL    : 8;  /* [7:0] */
    Uint32 Reserved : 24; /* [31:8] */
} PMB_RX_TL_BIT;

union PMB_RX_TL_REG
{
    Uint32 all;
    PMB_RX_TL_BIT bit;
};

typedef struct
{
    Uint32 TX_TL    : 8;  /* [7:0] */
    Uint32 Reserved : 24; /* [31:8] */
} PMB_TX_TL_BIT;

union PMB_TX_TL_REG
{
    Uint32 all;
    PMB_TX_TL_BIT bit;
};

typedef struct
{
    Uint32 ENABLE                    : 1;  /* [0] */
    Uint32 ABORT                     : 1;  /* [1] */
    Uint32 TX_CMD_BLOCK              : 1;  /* [2] */
    Uint32 SDA_STUCK_RECOVERY_ENABLE : 1;  /* [3] */
    Uint32 Reserved1                 : 12; /* [15:4] */
    Uint32 SMBUS_CLK_RESET           : 1;  /* [16] */
    Uint32 SMBUS_SUSPEND_EN          : 1;  /* [17] */
    Uint32 SMBUS_ALERT_EN            : 1;  /* [18] */
    Uint32 IC_SAR_EN                 : 1;  /* [19] */
    Uint32 IC_SAR2_EN                : 1;  /* [20] */
    Uint32 IC_SAR3_EN                : 1;  /* [21] */
    Uint32 IC_SAR4_EN                : 1;  /* [22] */
    Uint32 Reserved2                 : 9;  /* [31:23] */
} PMB_ENABLE_BIT;

union PMB_ENABLE_REG
{
    Uint32 all;
    PMB_ENABLE_BIT bit;
};

typedef struct
{
    Uint32 ACTIVITY                     : 1; /* [0] */
    Uint32 TFNF                         : 1; /* [1] */
    Uint32 TFE                          : 1; /* [2] */
    Uint32 RFNE                         : 1; /* [3] */
    Uint32 RFF                          : 1; /* [4] */
    Uint32 MST_ACTIVITY                 : 1; /* [5] */
    Uint32 SLV_ACTIVITY                 : 1; /* [6] */
    Uint32 MST_HOLD_TX_FIFO_EMPTY       : 1; /* [7] */
    Uint32 MST_HOLD_RX_FIFO_FULL        : 1; /* [8] */
    Uint32 SLV_HOLD_TX_FIFO_EMPTY       : 1; /* [9] */
    Uint32 SLV_HOLD_RX_FIFO_FULL        : 1; /* [10] */
    Uint32 SDA_STUCK_NOT_RECOVERED      : 1; /* [11] */
    Uint32 SLV_ISO_SAR_DATA_CLK_STRETCH : 1; /* [12] */
    Uint32 Reserved1                    : 3; /* [15:13] */
    Uint32 SMBUS_QUICK_CMD_BIT          : 1; /* [16] */
    Uint32 SMBUS_SLAVE_ADDR_VALID       : 1; /* [17] */
    Uint32 SMBUS_SLAVE_ADDR_RESOLVED    : 1; /* [18] */
    Uint32 SMBUS_SUSPEND_STATUS         : 1; /* [19] */
    Uint32 SMBUS_ALERT_STATUS           : 1; /* [20] */
    Uint32 SMBUS_SLAVE_ADDR2_VALID      : 1; /* [21] */
    Uint32 SMBUS_SLAVE_ADDR2_RESOLVED   : 1; /* [22] */
    Uint32 SMBUS_SLAVE_ADDR3_VALID      : 1; /* [23] */
    Uint32 SMBUS_SLAVE_ADDR3_RESOLVED   : 1; /* [24] */
    Uint32 SMBUS_SLAVE_ADDR4_VALID      : 1; /* [25] */
    Uint32 SMBUS_SLAVE_ADDR4_RESOLVED   : 1; /* [26] */
    Uint32 Reserved2                    : 5; /* [31:27] */
} PMB_STATUS_BIT;

union PMB_STATUS_REG
{
    Uint32 all;
    PMB_STATUS_BIT bit;
};

typedef struct
{
    Uint32 IC_SDA_TX_HOLD : 16; /* [15:0] */
    Uint32 IC_SDA_RX_HOLD : 8;  /* [23:16] */
    Uint32 Reserved       : 8;  /* [31:24] */
} PMB_SDA_HOLD_BIT;

union PMB_SDA_HOLD_REG
{
    Uint32 all;
    PMB_SDA_HOLD_BIT bit;
};

typedef struct
{
    Uint32 ABRT_7B_ADDR_NOACK        : 1; /* [0] */
    Uint32 ABRT_10ADDR1_NOACK        : 1; /* [1] */
    Uint32 ABRT_10ADDR2_NOACK        : 1; /* [2] */
    Uint32 ABRT_TXDATA_NOACK         : 1; /* [3] */
    Uint32 ABRT_GCALL_NOACK          : 1; /* [4] */
    Uint32 ABRT_GCALL_READ           : 1; /* [5] */
    Uint32 ABRT_HS_ACKDET            : 1; /* [6] */
    Uint32 ABRT_SBYTE_ACKDET         : 1; /* [7] */
    Uint32 ABRT_HS_NORSTRT           : 1; /* [8] */
    Uint32 ABRT_SBYTE_NORSTRT        : 1; /* [9] */
    Uint32 ABRT_10B_RD_NORSTRT       : 1; /* [10] */
    Uint32 ABRT_MASTER_DIS           : 1; /* [11] */
    Uint32 ARB_LOST                  : 1; /* [12] */
    Uint32 ABRT_SLVFLUSH_TXFIFO      : 1; /* [13] */
    Uint32 ABRT_SLV_ARBLOST          : 1; /* [14] */
    Uint32 ABRT_SLVRD_INTX           : 1; /* [15] */
    Uint32 ABRT_USER_ABRT            : 1; /* [16] */
    Uint32 ABRT_SDA_STUCK_AT_LOW     : 1; /* [17] */
    Uint32 ABRT_DEVICE_NOACK         : 1; /* [18] */
    Uint32 ABRT_DEVICE_SLVADDR_NOACK : 1; /* [19] */
    Uint32 ABRT_DEVICE_WRITE         : 1; /* [20] */
    Uint32 RSVD_IC_TX_ABRT_SOURCE    : 2; /* [22:21] */
    Uint32 TX_FLUSH_CNT              : 2; /* [24:23] */
} PMB_TX_ABRT_SOURCE_BIT;

union PMB_TX_ABRT_SOURCE_REG
{
    Uint32 all;
    PMB_TX_ABRT_SOURCE_BIT bit;
};

typedef struct
{
    Uint32 RDMAE    : 1;  /* [0] */
    Uint32 TDMAE    : 1;  /* [1] */
    Uint32 Reserved : 30; /* [31:2] */
} PMB_DMA_CR_BIT;

union PMB_DMA_CR_REG
{
    Uint32 all;
    PMB_DMA_CR_BIT bit;
};

typedef struct
{
    Uint32 SDA_SETUP : 8;  /* [7:0] */
    Uint32 Reserved  : 24; /* [31:8] */
} PMB_SDA_SETUP_BIT;

union PMB_SDA_SETUP_REG
{
    Uint32 all;
    PMB_SDA_SETUP_BIT bit;
};

typedef struct
{
    Uint32 UFM_SPKLEN : 8;  /* [7:0] */
    Uint32 Reserved   : 24; /* [31:8] */
} PMB_UFM_SPKLEN_BIT;

union PMB_UFM_SPKLEN_REG
{
    Uint32 all;
    PMB_UFM_SPKLEN_BIT bit;
};

typedef struct
{
    Uint32 HS_SPKLEN : 8;  /* [7:0] */
    Uint32 Reserved  : 24; /* [31:8] */
} PMB_HS_SPKLEN_BIT;

union PMB_HS_SPKLEN_REG
{
    Uint32 all;
    PMB_HS_SPKLEN_BIT bit;
};

typedef struct
{
    Uint32 CLR_RESTART_DET : 1;  /* [0] */
    Uint32 Reserved        : 31; /* [31:1] */
} PMB_CLR_RESTART_DET_BIT;

union PMB_CLR_RESTART_DET_REG
{
    Uint32 all;
    PMB_CLR_RESTART_DET_BIT bit;
};

typedef struct
{
    Uint32 SCL_STUCK_LOW_TIMEOUT : 32; /* [31:0] */
} PMB_SCL_STUCK_AT_LOW_TIMEOUT_BIT;

union PMB_SCL_STUCK_AT_LOW_TIMEOUT_REG
{
    Uint32 all;
    PMB_SCL_STUCK_AT_LOW_TIMEOUT_BIT bit;
};

typedef struct
{
    Uint32 SDA_STUCK_LOW_TIMEOUT : 32; /* [31:0] */
} PMB_SDA_STUCK_AT_LOW_TIMEOUT_BIT;

union PMB_SDA_STUCK_AT_LOW_TIMEOUT_REG
{
    Uint32 all;
    PMB_SDA_STUCK_AT_LOW_TIMEOUT_BIT bit;
};

typedef struct
{
    Uint32 CLR_SCL_STUCK_DET : 1;  /* [0] */
    Uint32 Reserved          : 31; /* [31:1] */
} PMB_CLR_SCL_STUCK_DET_BIT;

union PMB_CLR_SCL_STUCK_DET_REG
{
    Uint32 all;
    PMB_CLR_SCL_STUCK_DET_BIT bit;
};

typedef struct
{
    Uint32 DEVICE_ID : 24; /* [23:0] */
    Uint32 Reserved  : 8;  /* [31:24] */
} PMB_DEVICE_ID_BIT;

union PMB_DEVICE_ID_REG
{
    Uint32 all;
    PMB_DEVICE_ID_BIT bit;
};

typedef struct
{
    Uint32 SMBUS_CLK_LOW_SEXT_TIMEOUT : 32; /* [31:0] */
} PMB_SMBUS_CLK_LOW_SEXT_BIT;

union PMB_SMBUS_CLK_LOW_SEXT_REG
{
    Uint32 all;
    PMB_SMBUS_CLK_LOW_SEXT_BIT bit;
};

typedef struct
{
    Uint32 SMBUS_CLK_LOW_MEXT_TIMEOUT : 32; /* [31:0] */
} PMB_SMBUS_CLK_LOW_MEXT_BIT;

union PMB_SMBUS_CLK_LOW_MEXT_REG
{
    Uint32 all;
    PMB_SMBUS_CLK_LOW_MEXT_BIT bit;
};

typedef struct
{
    Uint32 SMBUS_THIGH_MAX_BUS_IDLE_CNT : 16; /* [15:0] */
    Uint32 Reserved                     : 16; /* [31:16] */
} SMBUS_THIGH_MAX_BUS_IDLE_CNT_BIT;

union SMBUS_THIGH_MAX_BUS_IDLE_CNT_REG
{
    Uint32 all;
    SMBUS_THIGH_MAX_BUS_IDLE_CNT_BIT bit;
};

typedef struct
{
    Uint32 SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    Uint32 MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    Uint32 QUICK_CMD_DET           : 1;  /* [2] */
    Uint32 HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    Uint32 ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    Uint32 ARP_RST_CMD_DET         : 1;  /* [5] */
    Uint32 ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    Uint32 ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    Uint32 SLV_RX_PEC_NACK         : 1;  /* [8] */
    Uint32 SMBUS_SUSPEND_DET       : 1;  /* [9] */
    Uint32 SMBUS_ALERT_DET         : 1;  /* [10] */
    Uint32 Reserved                : 21; /* [31:11] */
} SMBUS_INTR_STAT_BIT;

union SMBUS_INTR_STAT_REG
{
    Uint32 all;
    SMBUS_INTR_STAT_BIT bit;
};

typedef struct
{
    Uint32 SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    Uint32 MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    Uint32 QUICK_CMD_DET           : 1;  /* [2] */
    Uint32 HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    Uint32 ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    Uint32 ARP_RST_CMD_DET         : 1;  /* [5] */
    Uint32 ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    Uint32 ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    Uint32 SLV_RX_PEC_NACK         : 1;  /* [8] */
    Uint32 SMBUS_SUSPEND_DET       : 1;  /* [9] */
    Uint32 SMBUS_ALERT_DET         : 1;  /* [10] */
    Uint32 Reserved                : 21; /* [31:11] */
} SMBUS_INTR_MASK_BIT;

union SMBUS_INTR_MASK_REG
{
    Uint32 all;
    SMBUS_INTR_MASK_BIT bit;
};

typedef struct
{
    Uint32 SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    Uint32 MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    Uint32 QUICK_CMD_DET           : 1;  /* [2] */
    Uint32 HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    Uint32 ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    Uint32 ARP_RST_CMD_DET         : 1;  /* [5] */
    Uint32 ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    Uint32 ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    Uint32 SLV_RX_PEC_NACK         : 1;  /* [8] */
    Uint32 SMBUS_SUSPEND_DET       : 1;  /* [9] */
    Uint32 SMBUS_ALERT_DET         : 1;  /* [10] */
    Uint32 Reserved                : 21; /* [31:11] */
} SMBUS_RAW_INTR_STAT_BIT;

union SMBUS_RAW_INTR_STAT_REG
{
    Uint32 all;
    SMBUS_RAW_INTR_STAT_BIT bit;
};

typedef struct
{
    Uint32 CLR_SLV_CLOCK_EXTND_TIMEOUT : 1;  /* [0] */
    Uint32 CLR_MST_CLOCK_EXTND_TIMEOUT : 1;  /* [1] */
    Uint32 CLR_QUICK_CMD_DET           : 1;  /* [2] */
    Uint32 CLR_HOST_NOTIFY_MST_DET     : 1;  /* [3] */
    Uint32 CLR_ARP_PREPARE_CMD_DET     : 1;  /* [4] */
    Uint32 CLR_ARP_RST_CMD_DET         : 1;  /* [5] */
    Uint32 CLR_ARP_GET_UDID_CMD_DET    : 1;  /* [6] */
    Uint32 CLR_ARP_ASSGN_ADDR_CMD_DET  : 1;  /* [7] */
    Uint32 CLR_SLV_RX_PEC_NACK         : 1;  /* [8] */
    Uint32 CLR_SMBUS_SUSPEND_DET       : 1;  /* [9] */
    Uint32 CLR_SMBUS_ALERT_DET         : 1;  /* [10] */
    Uint32 Reserved                    : 21; /* [31:11] */
} CLR_SMBUS_INTR_BIT;

union CLR_SMBUS_INTR_REG
{
    Uint32 all;
    CLR_SMBUS_INTR_BIT bit;
};

typedef struct
{
    Uint32 REG_TIMEOUT_RST_rw : 10; /* [9:0] */
    Uint32 REG_TIMEOUT_RST_ro : 10; /* [19:10] */
    Uint32 Reserved           : 12; /* [31:20] */
} PMB_REG_TIMEOUT_RST_BIT;

union PMB_REG_TIMEOUT_RST_REG
{
    Uint32 all;
    PMB_REG_TIMEOUT_RST_BIT bit;
};

typedef struct
{
    Uint32 APB_DATA_WIDTH     : 2; /* [1:0] */
    Uint32 MAX_SPEED_MODE     : 2; /* [3:2] */
    Uint32 HC_COUNT_VALUES    : 1; /* [4] */
    Uint32 INTR_IO            : 1; /* [5] */
    Uint32 HAS_DMA            : 1; /* [6] */
    Uint32 ADD_ENCODED_PARAMS : 1; /* [7] */
    Uint32 RX_BUFFER_DEPTH    : 8; /* [15:8] */
    Uint32 TX_BUFFER_DEPTH    : 8; /* [23:16] */
    Uint32 Reserved           : 8; /* [31:24] */
} PMB_COMP_PARAM1_BIT;

union PMB_COMP_PARAM1_REG
{
    Uint32 all;
    PMB_COMP_PARAM1_BIT bit;
};

struct PMBUS_REGS
{
    union PMB_CON_REG IC_CON;                                             /* offset:0x00 */
    union PMB_TAR_REG IC_TAR;                                             /* offset:0x04 */
    union PMB_SAR_REG IC_SAR;                                             /* offset:0x08 */
    Uint32 Reserved1;                                                     /* offset:0x0C */
    union PMB_DATA_CMD_REG IC_DATA_CMD;                                   /* offset:0x10 */
    union SS_SCL_HCNT_REG IC_SS_SCL_HCNT;                                 /* offset:0x14 */
    union SS_SCL_LCNT_REG IC_SS_SCL_LCNT;                                 /* offset:0x18 */
    union FS_SCL_HCNT_REG IC_FS_SCL_HCNT;                                 /* offset:0x1C */
    union FS_SCL_LCNT_REG IC_FS_SCL_LCNT;                                 /* offset:0x20 */
    Uint32 Reserved2;                                                     /* offset:0x24 */
    Uint32 Reserved3;                                                     /* offset:0x28 */
    union PMB_INTR_STAT_REG IC_INTR_STAT;                                 /* offset:0x2C */
    union PMB_INTR_MASK_REG IC_INTR_MASK;                                 /* offset:0x30 */
    union PMB_RAW_INTR_STAT_REG IC_RAW_INTR_STAT;                         /* offset:0x34 */
    union PMB_RX_TL_REG IC_RX_TL;                                         /* offset:0x38 */
    union PMB_TX_TL_REG IC_TX_TL;                                         /* offset:0x3C */
    Uint32 IC_CLR_INTR;                                                   /* offset:0x40 */
    Uint32 IC_CLR_RX_UNDER;                                               /* offset:0x44 */
    Uint32 IC_CLR_RX_OVER;                                                /* offset:0x48 */
    Uint32 IC_CLR_TX_OVER;                                                /* offset:0x4C */
    Uint32 IC_CLR_RD_REQ;                                                 /* offset:0x50 */
    Uint32 IC_CLR_TX_ABRT;                                                /* offset:0x54 */
    Uint32 IC_CLR_RX_DONE;                                                /* offset:0x58 */
    Uint32 IC_CLR_ACTIVITY;                                               /* offset:0x5C */
    Uint32 IC_CLR_STOP_DET;                                               /* offset:0x60 */
    Uint32 IC_CLR_START_DET;                                              /* offset:0x64 */
    Uint32 IC_CLR_GEN_CALL;                                               /* offset:0x68 */
    union PMB_ENABLE_REG IC_ENABLE;                                       /* offset:0x6C */
    union PMB_STATUS_REG IC_STATUS;                                       /* offset:0x70 */
    Uint32 IC_TXFLR;                                                      /* offset:0x74 */
    Uint32 IC_RXFLR;                                                      /* offset:0x78 */
    union PMB_SDA_HOLD_REG IC_SDA_HOLD;                                   /* offset:0x7C */
    union PMB_TX_ABRT_SOURCE_REG IC_TX_ABRT_SOURCE;                       /* offset:0x80 */
    Uint32 IC_SLV_DATA_NACK_ONLY;                                         /* offset:0x84 */
    union PMB_DMA_CR_REG IC_DMA_CR;                                       /* offset:0x88 */
    Uint32 IC_DMA_TDLR;                                                   /* offset:0x8C */
    Uint32 IC_DMA_RDLR;                                                   /* offset:0x90 */
    union PMB_SDA_SETUP_REG IC_SDA_SETUP;                                 /* offset:0x94 */
    Uint32 IC_ACK_GENERAL_CALL;                                           /* offset:0x98 */
    Uint32 IC_ENABLE_STATUS;                                              /* offset:0x9C */
    union PMB_UFM_SPKLEN_REG IC_UFM_SPKLEN;                               /* offset:0xA0 */
    union PMB_HS_SPKLEN_REG IC_HS_SPKLEN;                                 /* offset:0xA4 */
    union PMB_CLR_RESTART_DET_REG CLR_RESTART_DET;                        /* offset:0xA8 */
    union PMB_SCL_STUCK_AT_LOW_TIMEOUT_REG IC_SCL_STUCK_AT_LOW_TIMEOUT;   /* offset:0xAC */
    union PMB_SDA_STUCK_AT_LOW_TIMEOUT_REG IC_SDA_STUCK_AT_LOW_TIMEOUT;   /* offset:0xB0 */
    union PMB_CLR_SCL_STUCK_DET_REG IC_CLR_SCL_STUCK_DET;                 /* offset:0xB4 */
    union PMB_DEVICE_ID_REG IC_DEVICE_ID;                                 /* offset:0xB8 */
    union PMB_SMBUS_CLK_LOW_SEXT_REG IC_SMBUS_CLK_LOW_SEXT;               /* offset:0xBC */
    union PMB_SMBUS_CLK_LOW_MEXT_REG IC_SMBUS_CLK_LOW_MEXT;               /* offset:0xC0 */
    union SMBUS_THIGH_MAX_BUS_IDLE_CNT_REG IC_SMBUS_THIGH_MAX_IDLE_COUNT; /* offset:0xC4 */
    union SMBUS_INTR_STAT_REG IC_SMBUS_INTR_STAT;                         /* offset:0xC8 */
    union SMBUS_INTR_MASK_REG IC_SMBUS_INTR_MASK;                         /* offset:0xCC */
    union SMBUS_RAW_INTR_STAT_REG IC_SMBUS_RAW_INTR_STAT;                 /* offset:0xd0 */
    union CLR_SMBUS_INTR_REG IC_CLR_SMBUS_INTR;                           /* offset:0xd4 */
    Uint32 IC_OPTIONAL_SAR;                                               /* offset:0xd8 */
    Uint32 IC_SMBUS_UDID_LSB;                                             /* offset:0xdc */
    Uint32 IC_SMBUS_UDID_WORD1;                                           /* offset:0xe0 */
    Uint32 IC_SMBUS_UDID_WORD2;                                           /* offset:0xe4 */
    Uint32 IC_SMBUS_UDID_WORD3;                                           /* offset:0xe8 */
    union PMB_REG_TIMEOUT_RST_REG REG_TIMEOUT_RST;                        /* offset:0xf0 */
    union PMB_COMP_PARAM1_REG IC_COMP_PARAM1;                             /* offset:0xf4 */
    Uint32 IC_COMP_VERSION;                                               /* offset:0xf8 */
    Uint32 IC_COMP_TYPE;                                                  /* offset:0xfC */
    Uint32 IC_SAR2;                                                       /* offset:0x100 */
    Uint32 IC_SAR3;                                                       /* offset:0x104 */
    Uint32 IC_SAR4;                                                       /* offset:0x108 */
    Uint32 Reserved_0x10c;                                                /* offset:0x10c */
    Uint32 Reserved_0x110;                                                /* offset:0x110 */
    Uint32 Reserved_0x114;                                                /* offset:0x114 */
    Uint32 Reserved_0x118;                                                /* offset:0x118 */
    Uint32 CLR_WR_REQ;                                                    /* offset:0x11c */
    Uint32 CLR_SLV_ADDR_TAG;                                              /* offset:0x120 */
    Uint32 IC_SAR2_SMBUS_UDID_WORD0;                                      /* offset:0x124 */
    Uint32 IC_SAR2_SMBUS_UDID_WORD1;                                      /* offset:0x128 */
    Uint32 IC_SAR2_SMBUS_UDID_WORD2;                                      /* offset:0x12C */
    Uint32 IC_SAR2_SMBUS_UDID_WORD3;                                      /* offset:0x130 */
    Uint32 IC_SAR3_SMBUS_UDID_WORD0;                                      /* offset:0x134 */
    Uint32 IC_SAR3_SMBUS_UDID_WORD1;                                      /* offset:0x138 */
    Uint32 IC_SAR3_SMBUS_UDID_WORD2;                                      /* offset:0x13C */
    Uint32 IC_SAR3_SMBUS_UDID_WORD3;                                      /* offset:0x140 */
    Uint32 IC_SAR4_SMBUS_UDID_WORD0;                                      /* offset:0x144 */
    Uint32 IC_SAR4_SMBUS_UDID_WORD1;                                      /* offset:0x148 */
    Uint32 IC_SAR4_SMBUS_UDID_WORD2;                                      /* offset:0x14C */
    Uint32 IC_SAR4_SMBUS_UDID_WORD3;                                      /* offset:0x150 */
};

//---------------------------------------------------------------------------
// PMBUS External References & Function Declarations:
//
extern volatile struct PMBUS_REGS PmbusaRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
