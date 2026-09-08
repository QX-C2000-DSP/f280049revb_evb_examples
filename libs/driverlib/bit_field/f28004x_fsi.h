#ifndef F28004X_FSI_H
#define F28004X_FSI_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// FSI Individual Register Bit Definitions:

struct TX_MASTER_CTRL_BITS
{                        // bits description
    Uint32 CORE_RST : 1; // 0 Transmitter Main Core Reset
    Uint32 FLUSH    : 1; // 1 Flush Operation Start
    Uint32 rsvd1    : 6; // 7:2 Reserved
    Uint32 KEY      : 8; // 15:8 Write Key
};

union TX_MASTER_CTRL_REG
{
    Uint32 all;
    struct TX_MASTER_CTRL_BITS bit;
};

struct TX_CLK_CTRL_BITS
{                            // bits description
    Uint32 CLK_RST      : 1; // 0 Soft Reset for the Clock Divider
    Uint32 CLK_EN       : 1; // 1 Clock Divider Enable
    Uint32 PRESCALE_VAL : 8; // 9:2 Prescale value
    Uint32 rsvd1        : 6; // 15:10 Reserved
};

union TX_CLK_CTRL_REG
{
    Uint32 all;
    struct TX_CLK_CTRL_BITS bit;
};

struct TX_OPER_CTRL_LO_BITS
{                            // bits description
    Uint32 DATA_WIDTH   : 2; // 1:0 Transmit Data width
    Uint32 SPI_MODE     : 1; // 2 SPI Mode Select
    Uint32 START_MODE   : 3; // 5:3 Transmission Start Mode Select
    Uint32 SW_CRC       : 1; // 6 CRC Source Select
    Uint32 PING_TO_MODE : 1; // 7 Ping Counter Reset Mode Select
    Uint32 SEL_PLLCLK   : 1; // 8 Input Clock Select
    Uint32 rsvd1        : 7; // 15:9 Reserved
};

union TX_OPER_CTRL_LO_REG
{
    Uint32 all;
    struct TX_OPER_CTRL_LO_BITS bit;
};

struct TX_OPER_CTRL_HI_BITS
{                            // bits description
    Uint32 EXT_TRIG_SEL : 5; // 4:0 External Trigger Select
    Uint32 FORCE_ERR    : 1; // 5 Error Frame Force
    Uint32 ECC_SEL      : 1; // 6 ECC Data Width Select
    Uint32 rsvd1        : 9; // 15:7 Reserved
};

union TX_OPER_CTRL_HI_REG
{
    Uint32 all;
    struct TX_OPER_CTRL_HI_BITS bit;
};

struct TX_FRAME_CTRL_BITS
{                          // bits description
    Uint32 FRAME_TYPE : 4; // 3:0 Transmit Frame Type
    Uint32 N_WORDS    : 4; // 7:4 Number of Words to be Transmitted
    Uint32 rsvd1      : 7; // 14:8 Reserved
    Uint32 START      : 1; // 15 Start Transmission
};

union TX_FRAME_CTRL_REG
{
    Uint32 all;
    struct TX_FRAME_CTRL_BITS bit;
};

struct TX_FRAME_TAG_UDATA_BITS
{                         // bits description
    Uint32 FRAME_TAG : 4; // 3:0 Frame Tag
    Uint32 rsvd1     : 4; // 7:4 Reserved
    Uint32 USER_DATA : 8; // 15:8 User Data
};

union TX_FRAME_TAG_UDATA_REG
{
    Uint32 all;
    struct TX_FRAME_TAG_UDATA_BITS bit;
};

struct TX_BUF_PTR_LOAD_BITS
{                             // bits description
    Uint32 BUF_PTR_LOAD : 4;  // 3:0 Buffer Pointer Force Load
    Uint32 rsvd1        : 12; // 15:4 Reserved
};

union TX_BUF_PTR_LOAD_REG
{
    Uint32 all;
    struct TX_BUF_PTR_LOAD_BITS bit;
};

struct TX_BUF_PTR_STS_BITS
{                             // bits description
    Uint32 CURR_BUF_PTR  : 4; // 3:0 Current Buffer Pointer Index
    Uint32 rsvd1         : 4; // 7:4 Reserved
    Uint32 CURR_WORD_CNT : 5; // 12:8 Remaining Words in Buffer
    Uint32 rsvd2         : 3; // 15:13 Reserved
};

union TX_BUF_PTR_STS_REG
{
    Uint32 all;
    struct TX_BUF_PTR_STS_BITS bit;
};

struct TX_PING_CTRL_BITS
{                            // bits description
    Uint32 CNT_RST      : 1; // 0 Ping Counter Reset
    Uint32 TIMER_EN     : 1; // 1 Ping Counter Enable
    Uint32 EXT_TRIG_EN  : 1; // 2 External Trigger Enable
    Uint32 EXT_TRIG_SEL : 5; // 7:3 External Trigger Select
    Uint32 rsvd1        : 8; // 15:8 Reserved
};

union TX_PING_CTRL_REG
{
    Uint32 all;
    struct TX_PING_CTRL_BITS bit;
};

struct TX_PING_TO_REF_BIT
{                               // bits description
    Uint32 TX_PING_TO_REF : 32; // 0 Ping Counter Reset
};
union TX_PING_TO_REF_REG
{
    Uint32 all;
    struct TX_PING_TO_REF_BIT bit;
};

struct TX_PING_TAG_BITS
{                      // bits description
    Uint32 TAG   : 4;  // 3:0 Ping Frame Tag
    Uint32 rsvd1 : 12; // 15:4 Reserved
};

union TX_PING_TAG_REG
{
    Uint32 all;
    struct TX_PING_TAG_BITS bit;
};

struct TX_INT_CTRL_BITS
{                                    // bits description
    Uint32 INT1_EN_FRAME_DONE   : 1; // 0 Enable Frame Done Interrupt to INT1
    Uint32 INT1_EN_BUF_UNDERRUN : 1; // 1 Enable Buffer Underrun Interrupt to INT1
    Uint32 INT1_EN_BUF_OVERRUN  : 1; // 2 Enable Buffer Overrun Interrupt to INT1
    Uint32 INT1_EN_PING_TO      : 1; // 3 Enable Ping Timer Interrupt to INT1
    Uint32 rsvd1                : 4; // 7:4 Reserved
    Uint32 INT2_EN_FRAME_DONE   : 1; // 8 Enable Frame Done Interrupt to INT2
    Uint32 INT2_EN_BUF_UNDERRUN : 1; // 9 Enable Buffer Underrun Interrupt to INT2
    Uint32 INT2_EN_BUF_OVERRUN  : 1; // 10 Enable Buffer Overrun Interrupt to INT2
    Uint32 INT2_EN_PING_TO      : 1; // 11 Enable Ping Timer Interrupt to INT2
    Uint32 rsvd2                : 4; // 15:12 Reserved
};

union TX_INT_CTRL_REG
{
    Uint32 all;
    struct TX_INT_CTRL_BITS bit;
};

struct TX_DMA_CTRL_BITS
{                           // bits description
    Uint32 DMA_EVT_EN : 1;  // 0 DMA Event Enable
    Uint32 rsvd1      : 15; // 15:1 Reserved
};

union TX_DMA_CTRL_REG
{
    Uint32 all;
    struct TX_DMA_CTRL_BITS bit;
};

struct TX_LOCK_CTRL_BITS
{                     // bits description
    Uint32 LOCK  : 1; // 0 Control Register Lock Enable
    Uint32 rsvd1 : 7; // 7:1 Reserved
    Uint32 KEY   : 8; // 15:8 Write Key
};

union TX_LOCK_CTRL_REG
{
    Uint32 all;
    struct TX_LOCK_CTRL_BITS bit;
};

struct TX_EVT_STS_BITS
{                               // bits description
    Uint32 FRAME_DONE     : 1;  // 0 Frame Done Flag
    Uint32 BUF_UNDERRUN   : 1;  // 1 Buffer Underrun Flag
    Uint32 BUF_OVERRUN    : 1;  // 2 Buffer Overrun Flag
    Uint32 PING_TRIGGERED : 1;  // 3 Ping Frame Triggered Flag
    Uint32 rsvd1          : 12; // 15:4 Reserved
};

union TX_EVT_STS_REG
{
    Uint32 all;
    struct TX_EVT_STS_BITS bit;
};

struct TX_EVT_CLR_BITS
{                               // bits description
    Uint32 FRAME_DONE     : 1;  // 0 Frame Done Flag Clear
    Uint32 BUF_UNDERRUN   : 1;  // 1 Buffer Underrun Flag Clear
    Uint32 BUF_OVERRUN    : 1;  // 2 Buffer Overrun Flag Clear
    Uint32 PING_TRIGGERED : 1;  // 3 Ping Frame Triggered Flag Clear
    Uint32 rsvd1          : 12; // 15:4 Reserved
};

union TX_EVT_CLR_REG
{
    Uint32 all;
    struct TX_EVT_CLR_BITS bit;
};

struct TX_EVT_FRC_BITS
{                               // bits description
    Uint32 FRAME_DONE     : 1;  // 0 Frame Done Flag Force
    Uint32 BUF_UNDERRUN   : 1;  // 1 Buffer Underrun Flag Force
    Uint32 BUF_OVERRUN    : 1;  // 2 Buffer Overrun Flag Force
    Uint32 PING_TRIGGERED : 1;  // 3 Ping Frame Triggered Flag Force
    Uint32 rsvd1          : 12; // 15:4 Reserved
};

union TX_EVT_FRC_REG
{
    Uint32 all;
    struct TX_EVT_FRC_BITS bit;
};

struct TX_USER_CRC_BITS
{                        // bits description
    Uint32 USER_CRC : 8; // 7:0 User-defined CRC
    Uint32 rsvd1    : 8; // 15:8 Reserved
};

union TX_USER_CRC_REG
{
    Uint32 all;
    struct TX_USER_CRC_BITS bit;
};

struct TX_ECC_DATA_BITS
{                          // bits description
    Uint32 DATA_LOW  : 16; // 15:0 ECC Data Lower 16 Bits
    Uint32 DATA_HIGH : 16; // 31:16 ECC Data Upper 16 Bits
};

union TX_ECC_DATA_REG
{
    Uint32 all;
    struct TX_ECC_DATA_BITS bit;
};

struct TX_ECC_VAL_BITS
{                       // bits description
    Uint32 ECC_VAL : 7; // 6:0 Computed ECC Value
    Uint32 rsvd1   : 9; // 15:7 Reserved
};

union TX_ECC_VAL_REG
{
    Uint32 all;
    struct TX_ECC_VAL_BITS bit;
};

struct FSI_TX_REGS
{
    union TX_MASTER_CTRL_REG TX_MASTER_CTRL;   // 0x00 Transmit master control register
    union TX_CLK_CTRL_REG TX_CLK_CTRL;         // 0x04 Transmit clock control register
    union TX_OPER_CTRL_LO_REG TX_OPER_CTRL_LO; // 0x08 Transmit operation control register low
    union TX_OPER_CTRL_HI_REG TX_OPER_CTRL_HI; // 0x0c Transmit operation control register high
    union TX_FRAME_CTRL_REG TX_FRAME_CTRL;     // 0x10 Transmit frame control register
    union TX_FRAME_TAG_UDATA_REG
        TX_FRAME_TAG_UDATA;                    // 0x14 Transmit frame tag and user data register
    union TX_BUF_PTR_LOAD_REG TX_BUF_PTR_LOAD; // 0x18 Transmit buffer pointer control load register
    union TX_BUF_PTR_STS_REG TX_BUF_PTR_STS; // 0x1c Transmit buffer pointer control status register
    union TX_PING_CTRL_REG TX_PING_CTRL;     // 0x20 Transmit ping control register
    union TX_PING_TO_REF_REG TX_PING_TO_REF; // 0x24 Transmit ping timeout counter reference
    Uint32 TX_PING_TO_CNT;                   // 0x28 Transmit ping timeout current count
    union TX_INT_CTRL_REG TX_INT_CTRL;       // 0x2c Transmit interrupt event control register
    union TX_LOCK_CTRL_REG TX_LOCK_CTRL;     // 0x30 Transmit lock control register
    union TX_EVT_STS_REG TX_EVT_STS;         // 0x34 Transmit event and error status flag register
    union TX_EVT_CLR_REG TX_EVT_CLR;         // 0x38 Transmit event and error clear register
    union TX_EVT_FRC_REG TX_EVT_FRC;         // 0x3C Transmit event and error flag force register
    union TX_USER_CRC_REG TX_USER_CRC;       // 0x40 Transmit user-defined CRC register // Reserved
    Uint32 TX_BUF_BASE[16];                  // 0x44-0x80 Base address for transmit buffer
    Uint32 TX_DMA_CTRL;                      // 0x84	 TX_DMA_CTR
    union TX_PING_TAG_REG TX_PING_TAG;       // 0x88  Transmit ping tag register
};

struct RX_MASTER_CTRL_BITS
{                            // bits description
    Uint32 CORE_RST     : 1; // 0 Receiver Main Core Reset
    Uint32 INT_LOOPBACK : 1; // 1 Internal Loopback Enable
    Uint32 SPI_PAIRING  : 1; // 2 Clock Pairing for SPI-like Behaviour
    Uint32 rsvd1        : 5; // 7:3 Reserved
    Uint32 KEY          : 8; // 15:8 Write Key
};

union RX_MASTER_CTRL_REG
{
    Uint32 all;
    struct RX_MASTER_CTRL_BITS bit;
};

struct RX_OPER_CTRL_BITS
{                                // bits description
    Uint32 DATA_WIDTH       : 2; // 1:0 Receive Data Width Select
    Uint32 SPI_MODE         : 1; // 2 SPI Mode Enable
    Uint32 N_WORDS          : 4; // 6:3 Number of Words to be Received
    Uint32 ECC_SEL          : 1; // 7 ECC Data Width Select
    Uint32 PING_WD_RST_MODE : 1; // 8 Ping Watchdog Timeout Mode Select
    Uint32 rsvd1            : 7; // 15:9 Reserved
};

union RX_OPER_CTRL_REG
{
    Uint32 all;
    struct RX_OPER_CTRL_BITS bit;
};

struct RX_FRAME_INFO_BITS
{                           // bits description
    Uint32 FRAME_TYPE : 4;  // 3:0 Received Frame Type
    Uint32 rsvd1      : 12; // 15:4 Reserved
};

union RX_FRAME_INFO_REG
{
    Uint32 all;
    struct RX_FRAME_INFO_BITS bit;
};

struct RX_FRAME_TAG_UDATA_BITS
{                         // bits description
    Uint32 rsvd1     : 1; // 0 Reserved
    Uint32 FRAME_TAG : 4; // 4:1 Received Frame Tag
    Uint32 rsvd2     : 3; // 7:5 Reserved
    Uint32 USER_DATA : 8; // 15:8 Received User Data
};

union RX_FRAME_TAG_UDATA_REG
{
    Uint32 all;
    struct RX_FRAME_TAG_UDATA_BITS bit;
};

struct RX_DMA_CTRL_BITS
{                           // bits description
    Uint32 DMA_EVT_EN : 1;  // 0 DMA Event Enable
    Uint32 rsvd1      : 15; // 15:1 Reserved
};

union RX_DMA_CTRL_REG
{
    Uint32 all;
    struct RX_DMA_CTRL_BITS bit;
};

struct RX_EVT_STS_BITS
{                             // bits description
    Uint32 PING_WD_TO    : 1; // 0 Ping Watchdog Timeout Flag
    Uint32 FRAME_WD_TO   : 1; // 1 Frame Watchdog Timeout Flag.
    Uint32 CRC_ERR       : 1; // 2 CRC Error Flag
    Uint32 TYPE_ERR      : 1; // 3 Frame Type Error Flag
    Uint32 EOF_ERR       : 1; // 4 End-of-Frame Error Flag
    Uint32 BUF_OVERRUN   : 1; // 5 Receive Buffer Overrun Flag
    Uint32 FRAME_DONE    : 1; // 6 Frame Done Flag
    Uint32 BUF_UNDERRUN  : 1; // 7 Receive Buffer Underrun Flag
    Uint32 ERR_FRAME     : 1; // 8 Error Frame Received Flag
    Uint32 PING_FRAME    : 1; // 9 Ping Frame Received Flag
    Uint32 FRAME_OVERRUN : 1; // 10 Frame Overrun Flag
    Uint32 DATA_FRAME    : 1; // 11 Data Frame Received Flag
    Uint32 rsvd1         : 4; // 15:12 Reserved
};

union RX_EVT_STS_REG
{
    Uint32 all;
    struct RX_EVT_STS_BITS bit;
};

struct RX_CRC_INFO_BITS
{                        // bits description
    Uint32 RX_CRC   : 8; // 7:0 Received CRC Value
    Uint32 CALC_CRC : 8; // 15:8 Hardware Calculated CRC
};

union RX_CRC_INFO_REG
{
    Uint32 all;
    struct RX_CRC_INFO_BITS bit;
};

struct RX_EVT_CLR_BITS
{                             // bits description
    Uint32 PING_WD_TO    : 1; // 0 Ping Watchdog Timeout Flag Clear
    Uint32 FRAME_WD_TO   : 1; // 1 Frame Watchdog Timeout Flag Clear
    Uint32 CRC_ERR       : 1; // 2 CRC Error Flag Clear
    Uint32 TYPE_ERR      : 1; // 3 Frame Type Error Flag Clear
    Uint32 EOF_ERR       : 1; // 4 End-of-Frame Error Flag Clear
    Uint32 BUF_OVERRUN   : 1; // 5 Receive Buffer Overrun Flag Clear
    Uint32 FRAME_DONE    : 1; // 6 Frame Done Flag Clear
    Uint32 BUF_UNDERRUN  : 1; // 7 Receive Buffer Underrun Flag Clear
    Uint32 ERR_FRAME     : 1; // 8 Error Frame Received Flag Clear
    Uint32 PING_FRAME    : 1; // 9 PING Frame Received Flag Clear
    Uint32 FRAME_OVERRUN : 1; // 10 Frame Overrun Flag Clear
    Uint32 DATA_FRAME    : 1; // 11 Data Frame Received Flag Clear
    Uint32 rsvd1         : 4; // 15:12 Reserved
};

union RX_EVT_CLR_REG
{
    Uint32 all;
    struct RX_EVT_CLR_BITS bit;
};

struct RX_EVT_FRC_BITS
{                             // bits description
    Uint32 PING_WD_TO    : 1; // 0 Ping Watchdog Timeout Flag Force
    Uint32 FRAME_WD_TO   : 1; // 1 Frame Watchdog Timeout Flag Force
    Uint32 CRC_ERR       : 1; // 2 CRC Error Flag Force
    Uint32 TYPE_ERR      : 1; // 3 Frame Type Error Flag Force
    Uint32 EOF_ERR       : 1; // 4 End-of-Frame Error Flag Force
    Uint32 BUF_OVERRUN   : 1; // 5 Receive Buffer Overrun Flag Force
    Uint32 FRAME_DONE    : 1; // 6 Frame Done Flag Force
    Uint32 BUF_UNDERRUN  : 1; // 7 Receive Buffer Underrun Flag Force
    Uint32 ERR_FRAME     : 1; // 8 Error Frame Received Flag Force
    Uint32 PING_FRAME    : 1; // 9 Ping Frame Received Flag Force
    Uint32 FRAME_OVERRUN : 1; // 10 Frame Overrun Flag Force
    Uint32 DATA_FRAME    : 1; // 11 Data Frame Received Flag Force
    Uint32 rsvd1         : 4; // 15:12 Reserved
};

union RX_EVT_FRC_REG
{
    Uint32 all;
    struct RX_EVT_FRC_BITS bit;
};

struct RX_BUF_PTR_LOAD_BITS
{                             // bits description
    Uint32 BUF_PTR_LOAD : 4;  // 3:0 Load value for receive buffer pointer
    Uint32 rsvd1        : 12; // 15:4 Reserved
};

union RX_BUF_PTR_LOAD_REG
{
    Uint32 all;
    struct RX_BUF_PTR_LOAD_BITS bit;
};

struct RX_BUF_PTR_STS_BITS
{                             // bits description
    Uint32 CURR_BUF_PTR  : 4; // 3:0 Current Buffer Pointer Index
    Uint32 rsvd1         : 4; // 7:4 Reserved
    Uint32 CURR_WORD_CNT : 5; // 12:8 Available Words in Buffer
    Uint32 rsvd2         : 3; // 15:13 Reserved
};

union RX_BUF_PTR_STS_REG
{
    Uint32 all;
    struct RX_BUF_PTR_STS_BITS bit;
};

struct RX_FRAME_WD_CTRL_BITS
{                                 // bits description
    Uint32 FRAME_WD_CNT_RST : 1;  // 0 Frame Watchdog Counter Reset
    Uint32 FRAME_WD_EN      : 1;  // 1 Frame Watchdog Counter Enable
    Uint32 rsvd1            : 14; // 15:2 Reserved
};

union RX_FRAME_WD_CTRL_REG
{
    Uint32 all;
    struct RX_FRAME_WD_CTRL_BITS bit;
};

struct RX_PING_WD_CTRL_BITS
{                            // bits description
    Uint32 PING_WD_RST : 1;  // 0 Ping Watchdog Counter Reset
    Uint32 PING_WD_EN  : 1;  // 1 Ping Watchdog Counter Enable
    Uint32 rsvd1       : 14; // 15:2 Reserved
};

union RX_PING_WD_CTRL_REG
{
    Uint32 all;
    struct RX_PING_WD_CTRL_BITS bit;
};

struct RX_PING_TAG_BITS
{                         // bits description
    Uint32 rsvd1    : 1;  // 0 Reserved
    Uint32 PING_TAG : 4;  // 4:1 Ping Frame Tag
    Uint32 rsvd2    : 11; // 15:5 Reserved
};

union RX_PING_TAG_REG
{
    Uint32 all;
    struct RX_PING_TAG_BITS bit;
};

struct RX_INT1_CTRL_BITS
{                                     // bits description
    Uint32 INT1_EN_PING_WD_TO    : 1; // 0 Enable Ping Watchdog Timeout Interrupt to INT1
    Uint32 INT1_EN_FRAME_WD_TO   : 1; // 1 Enable Frame Watchdog Timeout Interrupt to INT1
    Uint32 INT1_EN_CRC_ERR       : 1; // 2 Enable CRC Error Interrupt to INT1
    Uint32 INT1_EN_TYPE_ERR      : 1; // 3 Enable Frame Type Error Interrupt to INT1
    Uint32 INT1_EN_EOF_ERR       : 1; // 4 Enable End-of-Frame Error Interrupt to INT1
    Uint32 INT1_EN_OVERRUN       : 1; // 5 Enable Receive Buffer Overrun Interrupt to INT1
    Uint32 INT1_EN_FRAME_DONE    : 1; // 6 Enable Frame Done Interrupt to INT1
    Uint32 INT1_EN_UNDERRUN      : 1; // 7 Enable Buffer Underrun Interrupt to INT1
    Uint32 INT1_EN_ERR_FRAME     : 1; // 8 Enable Error Frame Received Interrupt to INT1
    Uint32 INT1_EN_PING_FRAME    : 1; // 9 Enable Ping Frame Received Interrupt to INT1
    Uint32 INT1_EN_FRAME_OVERRUN : 1; // 10 Enable Frame Overrun Interrupt to INT1
    Uint32 INT1_EN_DATA_FRAME    : 1; // 11 Enable Data Frame Received Interrupt to INT1
    Uint32 rsvd1                 : 4; // 15:12 Reserved
    Uint32 INT2_EN_PING_WD_TO    : 1; // 16 Enable Ping Watchdog Timeout Interrupt to INT2
    Uint32 INT2_EN_FRAME_WD_TO   : 1; // 17 Enable Frame Watchdog Timeout Interrupt to INT2
    Uint32 INT2_EN_CRC_ERR       : 1; // 18 Enable CRC Errror Interrupt to INT2
    Uint32 INT2_EN_TYPE_ERR      : 1; // 19 Enable Frame Type Error Interrupt to INT2
    Uint32 INT2_EN_EOF_ERR       : 1; // 20 Enable End-of-Frame Error Interrupt to INT2
    Uint32 INT2_EN_OVERRUN       : 1; // 21 Enable Buffer Overrun Interrupt to INT2
    Uint32 INT2_EN_FRAME_DONE    : 1; // 22 Enable Frame Done Interrupt to INT2
    Uint32 INT2_EN_UNDERRUN      : 1; // 23 Enable Buffer Underrun Interrupt to INT2
    Uint32 INT2_EN_ERR_FRAME     : 1; // 24 Enable Error Frame Received Interrupt to INT2
    Uint32 INT2_EN_PING_FRAME    : 1; // 25 Enable Ping Frame Received Interrupt to INT2
    Uint32 INT2_EN_FRAME_OVERRUN : 1; // 26 Enable Frame Overrun Interrupt to INT2
    Uint32 INT2_EN_DATA_FRAME    : 1; // 27 Enable Data Frame Received Interrupt to INT2
    Uint32 rsvd2                 : 4; // 31:28 Reserved
};

union RX_INT1_CTRL_REG
{
    Uint32 all;
    struct RX_INT1_CTRL_BITS bit;
};

// struct RX_INT2_CTRL_BITS
//{                                   // bits description
//     Uint32 INT2_EN_PING_WD_TO    : 1; // 0 Enable Ping Watchdog Timeout Interrupt to INT2
//     Uint32 INT2_EN_FRAME_WD_TO   : 1; // 1 Enable Frame Watchdog Timeout Interrupt to INT2
//     Uint32 INT2_EN_CRC_ERR       : 1; // 2 Enable CRC Errror Interrupt to INT2
//     Uint32 INT2_EN_TYPE_ERR      : 1; // 3 Enable Frame Type Error Interrupt to INT2
//     Uint32 INT2_EN_EOF_ERR       : 1; // 4 Enable End-of-Frame Error Interrupt to INT2
//     Uint32 INT2_EN_OVERRUN       : 1; // 5 Enable Buffer Overrun Interrupt to INT2
//     Uint32 INT2_EN_FRAME_DONE    : 1; // 6 Enable Frame Done Interrupt to INT2
//     Uint32 INT2_EN_UNDERRUN      : 1; // 7 Enable Buffer Underrun Interrupt to INT2
//     Uint32 INT2_EN_ERR_FRAME     : 1; // 8 Enable Error Frame Received Interrupt to INT2
//     Uint32 INT2_EN_PING_FRAME    : 1; // 9 Enable Ping Frame Received Interrupt to INT2
//     Uint32 INT2_EN_FRAME_OVERRUN : 1; // 10 Enable Frame Overrun Interrupt to INT2
//     Uint32 INT2_EN_DATA_FRAME    : 1; // 11 Enable Data Frame Received Interrupt to INT2
//     Uint32 rsvd1                 : 4; // 15:12 Reserved
// };
//
// union RX_INT2_CTRL_REG
//{
//     Uint32 all;
//     struct RX_INT2_CTRL_BITS bit;
// };

struct RX_LOCK_CTRL_BITS
{                     // bits description
    Uint32 LOCK  : 1; // 0 Control Register Lock Enable
    Uint32 rsvd1 : 7; // 7:1 Reserved
    Uint32 KEY   : 8; // 15:8 Write Key
};

union RX_LOCK_CTRL_REG
{
    Uint32 all;
    struct RX_LOCK_CTRL_BITS bit;
};

// struct RX_ECC_DATA_BITS
//{                        // bits description
//     Uint32 DATA_LOW  : 16; // 15:0 ECC Data Lower 16 Bits
//     Uint32 DATA_HIGH : 16; // 31:16 ECC Data Upper 16 Bits
// };
//
// union RX_ECC_DATA_REG
//{
//     Uint32 all;
//     struct RX_ECC_DATA_BITS bit;
// };

// struct RX_ECC_VAL_BITS
//{                     // bits description
//     Uint32 ECC_VAL : 7; // 6:0 Computed ECC Value
//     Uint32 rsvd1   : 9; // 15:7 Reserved
// };
//
// union RX_ECC_VAL_REG
//{
//     Uint32 all;
//     struct RX_ECC_VAL_BITS bit;
// };

// struct RX_ECC_LOG_BITS
//{                    // bits description
//     Uint32 SBE   : 1;  // 0 Single Bit Error Detected
//     Uint32 MBE   : 1;  // 1 Multiple Bit Errors Detected
//     Uint32 rsvd1 : 14; // 15:2 Reserved
// };
//
// union RX_ECC_LOG_REG
//{
//     Uint32 all;
//     struct RX_ECC_LOG_BITS bit;
// };

struct RX_DLYLINE_CTRL_BITS
{                         // bits description
    Uint32 RXCLK_DLY : 5; // 4:0 Delay Line Tap Select for RXCLK
    Uint32 RXD0_DLY  : 5; // 9:5 Delay Line Tap Select for RXD0
    Uint32 RXD1_DLY  : 5; // 14:10 Delay Line Tap Select for RXD1
    Uint32 rsvd1     : 1; // 15 Reserved
};

union RX_DLYLINE_CTRL_REG
{
    Uint32 all;
    struct RX_DLYLINE_CTRL_BITS bit;
};

struct RX_VIS_1_BITS
{                            // bits description
    Uint32 rsvd1       : 3;  // 2:0 Reserved
    Uint32 RX_CORE_STS : 1;  // 3 Receiver Core Status
    Uint32 rsvd2       : 12; // 15:4 Reserved
    Uint32 rsvd3       : 16; // 31:16 Reserved
};

union RX_VIS_1_REG
{
    Uint32 all;
    struct RX_VIS_1_BITS bit;
};

struct FSI_RX_REGS
{
    union RX_MASTER_CTRL_REG RX_MASTER_CTRL; // 0x00 Receive master control register
    union RX_OPER_CTRL_REG RX_OPER_CTRL;     // 0x04 Receive operation control register
    union RX_FRAME_INFO_REG RX_FRAME_INFO;   // 0x08 Receive frame control register
    union RX_FRAME_TAG_UDATA_REG
        RX_FRAME_TAG_UDATA;                    // 0x0c Receive frame tag and user data register
    union RX_EVT_STS_REG RX_EVT_STS;           // 0x10 Receive event and error status flag register
    union RX_CRC_INFO_REG RX_CRC_INFO;         // 0x14 Receive CRC info of received and computed CRC
    union RX_EVT_CLR_REG RX_EVT_CLR;           // 0x18 Receive event and error clear registers
    union RX_EVT_FRC_REG RX_EVT_FRC;           // 0x1c Receive event and error flag force register
    union RX_BUF_PTR_LOAD_REG RX_BUF_PTR_LOAD; // 0x20 Receive buffer pointer load register
    union RX_BUF_PTR_STS_REG RX_BUF_PTR_STS;   // 0x24 Receive buffer pointer status register
    union RX_FRAME_WD_CTRL_REG RX_FRAME_WD_CTRL; // 0x28 Receive frame watchdog control register
    Uint32 RX_FRAME_WD_REF;                      // 0x2c Receive frame watchdog counter reference
    Uint32 RX_FRAME_WD_CNT;                      // 0x30 Receive frame watchdog current count
    union RX_PING_WD_CTRL_REG RX_PING_WD_CTRL;   // 0x34 Receive ping watchdog control register
    Uint32 RX_PING_WD_REF;                       // 0x38 Receive ping watchdog counter reference
    Uint32 RX_PING_WD_CNT;                       // 0x3c Receive pingwatchdog current count
    union RX_INT1_CTRL_REG RX_INT1_CTRL; // 0x40 Receive interrupt control register for RX_INT1
    union RX_LOCK_CTRL_REG RX_LOCK_CTRL; // 0x44 Receive lock control register
    union RX_DLYLINE_CTRL_REG RX_DLYLINE_CTRL; // 0x48 Receive delay line control register
    union RX_VIS_1_REG RX_VIS_1;               // 0x4c Receive debug visibility register 1
    Uint32 RX_BUF_BASE[16];                    // 0x50 address for receive data buffer
    union RX_DMA_CTRL_REG RX_DMA_CTRL;         // 0x90 DMA_EVT
};

//---------------------------------------------------------------------------
// FSI External References & Function Declarations:
//
extern volatile struct FSI_TX_REGS FsiTxaRegs;
extern volatile struct FSI_RX_REGS FsiRxaRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
