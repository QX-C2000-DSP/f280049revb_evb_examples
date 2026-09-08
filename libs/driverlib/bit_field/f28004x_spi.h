#ifndef F28004X_SPI_H
#define F28004X_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// SPI Individual Register Bit Definitions:

struct SPICCR_BITS
{                           // bits description
    Uint32 SPICHAR     : 4; // 3:0 Character Length Control
    Uint32 SPILBK      : 1; // 4 SPI Loopback
    Uint32 HS_MODE     : 1; // 5 High Speed mode control
    Uint32 CLKPOLARITY : 1; // 6 Shift Clock Polarity
    Uint32 SPISWRESET  : 1; // 7 SPI Software Reset
    Uint32 SPI_MODE    : 2; // 9:8 SPI mode
    Uint32 rsvd1       : 6; // 15:10 Reserved
};

union SPICCR_REG
{
    Uint32 all;
    struct SPICCR_BITS bit;
};

struct SPICTL_BITS
{                              // bits description
    Uint32 SPIINTENA     : 1;  // 0 SPI Interupt Enable
    Uint32 TALK          : 1;  // 1 Master/Slave Transmit Enable
    Uint32 MASTER_SLAVE  : 1;  // 2 SPI Network Mode Control
    Uint32 CLK_PHASE     : 1;  // 3 SPI Clock Phase
    Uint32 OVERRUNINTENA : 1;  // 4 Overrun Interrupt Enable
    Uint32 rsvd1         : 11; // 15:5 Reserved
};

union SPICTL_REG
{
    Uint32 all;
    struct SPICTL_BITS bit;
};

struct SPISTS_BITS
{                            // bits description
    Uint32 rsvd1        : 5; // 4:0 Reserved
    Uint32 BUFFULL_FLAG : 1; // 5 SPI Transmit Buffer Full Flag
    Uint32 INT_FLAG     : 1; // 6 SPI Interrupt Flag
    Uint32 OVERRUN_FLAG : 1; // 7 SPI Receiver Overrun Flag
    Uint32 rsvd2        : 8; // 15:8 Reserved
};

union SPISTS_REG
{
    Uint32 all;
    struct SPISTS_BITS bit;
};

struct SPIBRR_BITS
{                            // bits description
    Uint32 SPI_BIT_RATE : 7; // 6:0 SPI Bit Rate Control
    Uint32 rsvd1        : 9; // 15:7 Reserved
};

union SPIBRR_REG
{
    Uint32 all;
    struct SPIBRR_BITS bit;
};

struct SPIFFTX_BITS
{                          // bits description
    Uint32 TXFFIL     : 5; // 4:0 TXFIFO Interrupt Level
    Uint32 TXFFIENA   : 1; // 5 TXFIFO Interrupt Enable
    Uint32 TXFFINTCLR : 1; // 6 TXFIFO Interrupt Clear
    Uint32 TXFFINT    : 1; // 7 TXFIFO Interrupt Flag
    Uint32 TXFFST     : 5; // 12:8 Transmit FIFO Status
    Uint32 TXFIFO     : 1; // 13 TXFIFO Reset
    Uint32 SPIFFENA   : 1; // 14 FIFO Enhancements Enable
    Uint32 SPIRST     : 1; // 15 SPI Reset
};

union SPIFFTX_REG
{
    Uint32 all;
    struct SPIFFTX_BITS bit;
};

struct SPIFFRX_BITS
{                           // bits description
    Uint32 RXFFIL      : 5; // 4:0 RXFIFO Interrupt Level
    Uint32 RXFFIENA    : 1; // 5 RXFIFO Interrupt Enable
    Uint32 RXFFINTCLR  : 1; // 6 RXFIFO Interupt Clear
    Uint32 RXFFINT     : 1; // 7 RXFIFO Interrupt Flag
    Uint32 RXFFST      : 5; // 12:8 Receive FIFO Status
    Uint32 RXFIFORESET : 1; // 13 RXFIFO Reset
    Uint32 RXFFOVFCLR  : 1; // 14 Receive FIFO Overflow Clear
    Uint32 RXFFOVF     : 1; // 15 Receive FIFO Overflow Flag
};

union SPIFFRX_REG
{
    Uint32 all;
    struct SPIFFRX_BITS bit;
};

struct SPIFFCT_BITS
{                     // bits description
    Uint32 TXDLY : 8; // 7:0 FIFO Transmit Delay Bits
    Uint32 rsvd1 : 8; // 15:8 Reserved
};

union SPIFFCT_REG
{
    Uint32 all;
    struct SPIFFCT_BITS bit;
};

struct SPIPRI_BITS
{                       // bits description
    Uint32 TRIWIRE : 1; // 0 3-wire mode select bit
    Uint32 STEINV  : 1; // 1 SPISTE inversion bit
    Uint32 rsvd1   : 2; // 3:2 Reserved
    Uint32 FREE    : 1; // 4 Free emulation mode
    Uint32 SOFT    : 1; // 5 Soft emulation mode
    Uint32 rsvd2   : 1; // 6 Reserved
    Uint32 rsvd3   : 9; // 15:7 Reserved
};

union SPIPRI_REG
{
    Uint32 all;
    struct SPIPRI_BITS bit;
};

struct SPICTRLR0_BITS
{                           // bits description
    Uint32 TRANS_TYPE  : 2; // 1:0 ir bit
    Uint32 ADDR_L      : 4; // 5:2 ir bit
    Uint32 rsvd1       : 2; // 7:6 Reserved
    Uint32 INST_L      : 2; // 9:8 ir bit
    Uint32 rsvd2       : 1; // 10 Reserved
    Uint32 WAIT_CYCLES : 5; // 15:11 ir bit
};

union SPICTRLR0_REG
{
    Uint32 all;
    struct SPICTRLR0_BITS bit;
};

struct MODESEL_BITS
{                     // bits description
    Uint32 TMOD : 2;  // 1:0 ir bit
    Uint32 NDF  : 17; // 18:2 ir bit
};

union MODESEL_REG
{
    Uint32 all;
    struct MODESEL_BITS bit;
};

struct SPI_REGS
{
    union SPICCR_REG SPICCR;       // SPI Configuration Control Register
    union SPICTL_REG SPICTL;       // SPI Operation Control Register
    union SPISTS_REG SPISTS;       // SPI Status Register
    union SPIBRR_REG SPIBRR;       // SPI Baud Rate Register
    Uint32 SPIRXEMU;               // SPI Emulation Buffer Register
    Uint32 SPIRXBUF;               // SPI Serial Input Buffer Register
    Uint32 SPITXBUF;               // SPI Serial Output Buffer Register
    Uint32 SPIDAT;                 // SPI Serial Data Register
    union SPIFFTX_REG SPIFFTX;     // SPI FIFO Transmit Register
    union SPIFFRX_REG SPIFFRX;     // SPI FIFO Receive Register
    union SPIFFCT_REG SPIFFCT;     // SPI FIFO Control Register
    union SPIPRI_REG SPIPRI;       // SPI Priority Control Register
    union SPICTRLR0_REG SPICTRLR0; // SPI Priority Control Register
    union MODESEL_REG MODESEL;     // SPI Priority Control Register
};

//---------------------------------------------------------------------------
// SPI External References & Function Declarations:
//
extern volatile struct SPI_REGS SpiaRegs;
extern volatile struct SPI_REGS SpibRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
