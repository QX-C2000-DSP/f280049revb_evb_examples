#ifndef F28004X_SCI_H
#define F28004X_SCI_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// SCI Individual Register Bit Definitions:

struct SCICCR_BITS
{                             // bits description
    Uint32 SCICHAR       : 3; // 2:0 Character length control
    Uint32 ADDRIDLE_MODE : 1; // 3 ADDR/IDLE Mode control
    Uint32 LOOPBKENA     : 1; // 4 Loop Back enable
    Uint32 PARITYENA     : 1; // 5 Parity enable
    Uint32 PARITY        : 1; // 6 Even or Odd Parity
    Uint32 STOPBITS      : 1; // 7 Number of Stop Bits
    Uint32 rsvd1         : 8; // 15:8 Reserved
};

union SCICCR_REG
{
    Uint32 all;
    struct SCICCR_BITS bit;
};

struct SCICTL1_BITS
{                           // bits description
    Uint32 RXENA       : 1; // 0 SCI receiver enable
    Uint32 TXENA       : 1; // 1 SCI transmitter enable
    Uint32 SLEEP       : 1; // 2 SCI sleep
    Uint32 TXWAKE      : 1; // 3 Transmitter wakeup method
    Uint32 rsvd1       : 1; // 4 Reserved
    Uint32 SWRESET     : 1; // 5 Software reset
    Uint32 RXERRINTENA : 1; // 6 Receive error interrupt enable
    Uint32 rsvd2       : 9; // 15:7 Reserved
};

union SCICTL1_REG
{
    Uint32 all;
    struct SCICTL1_BITS bit;
};

struct SCIHBAUD_BITS
{                     // bits description
    Uint32 BAUD  : 8; // 7:0 SCI 16-bit baud selection Registers SCIHBAUD
    Uint32 rsvd1 : 8; // 15:8 Reserved
};

union SCIHBAUD_REG
{
    Uint32 all;
    struct SCIHBAUD_BITS bit;
};

struct SCILBAUD_BITS
{                     // bits description
    Uint32 BAUD  : 8; // 7:0 SCI 16-bit baud selection Registers SCILBAUD
    Uint32 rsvd1 : 8; // 15:8 Reserved
};

union SCILBAUD_REG
{
    Uint32 all;
    struct SCILBAUD_BITS bit;
};

struct SCICTL2_BITS
{                          // bits description
    Uint32 TXINTENA   : 1; // 0 Transmit __interrupt enable
    Uint32 RXBKINTENA : 1; // 1 Receiver-buffer break enable
    Uint32 rsvd1      : 4; // 5:2 Reserved
    Uint32 TXEMPTY    : 1; // 6 Transmitter empty flag
    Uint32 TXRDY      : 1; // 7 Transmitter ready flag
    Uint32 rsvd2      : 8; // 15:8 Reserved
};

union SCICTL2_REG
{
    Uint32 all;
    struct SCICTL2_BITS bit;
};

struct SCIRXST_BITS
{                       // bits description
    Uint32 rsvd1   : 1; // 0 Reserved
    Uint32 RXWAKE  : 1; // 1 Receiver wakeup detect flag
    Uint32 PE      : 1; // 2 Parity error flag
    Uint32 OE      : 1; // 3 Overrun error flag
    Uint32 FE      : 1; // 4 Framing error flag
    Uint32 BRKDT   : 1; // 5 Break-detect flag
    Uint32 RXRDY   : 1; // 6 Receiver ready flag
    Uint32 RXERROR : 1; // 7 Receiver error flag
    Uint32 rsvd2   : 8; // 15:8 Reserved
};

union SCIRXST_REG
{
    Uint32 all;
    struct SCIRXST_BITS bit;
};

struct SCIRXEMU_BITS
{                     // bits description
    Uint32 ERXDT : 8; // 7:0 Receive emulation buffer data
    Uint32 rsvd1 : 8; // 15:8 Reserved
};

union SCIRXEMU_REG
{
    Uint32 all;
    struct SCIRXEMU_BITS bit;
};

struct SCIRXBUF_BITS
{                       // bits description
    Uint32 SAR     : 8; // 7:0 Receive Character bits
    Uint32 rsvd1   : 6; // 13:8 Reserved
    Uint32 SCIFFPE : 1; // 14 Receiver error flag
    Uint32 SCIFFFE : 1; // 15 Receiver error flag
};

union SCIRXBUF_REG
{
    Uint32 all;
    struct SCIRXBUF_BITS bit;
};

struct SCITOCTL_BITS
{                        // bits description
    Uint32 TIMEOUT  : 8; // 7:0 Timeout Interrupt Cycles Count
    Uint32 rsvd1    : 7; // 14:8 Reserved
    Uint32 TOINTENA : 1; // 15 Timeout Interrupt enable
};

union SCITOCTL_REG
{
    Uint32 all;
    struct SCITOCTL_BITS bit;
};

struct SCITXBUF_BITS
{                     // bits description
    Uint32 TXDT  : 8; // 7:0 Transmit data buffer
    Uint32 rsvd1 : 8; // 15:8 Reserved
};

union SCITXBUF_REG
{
    Uint32 all;
    struct SCITXBUF_BITS bit;
};

struct SCIFFTX_BITS
{                           // bits description
    Uint32 TXFFIL      : 5; // 4:0 Interrupt level
    Uint32 TXFFIENA    : 1; // 5 Interrupt enable
    Uint32 TXFFINTCLR  : 1; // 6 Clear INT flag
    Uint32 TXFFINT     : 1; // 7 INT flag
    Uint32 TXFFST      : 5; // 12:8 FIFO status
    Uint32 TXFIFORESET : 1; // 13 FIFO reset
    Uint32 SCIFFENA    : 1; // 14 Enhancement enable
    Uint32 SCIRST      : 1; // 15 SCI reset rx/tx channels
};

union SCIFFTX_REG
{
    Uint32 all;
    struct SCIFFTX_BITS bit;
};

struct SCIFFRX_BITS
{                           // bits description
    Uint32 RXFFIL      : 5; // 4:0 Interrupt level
    Uint32 RXFFIENA    : 1; // 5 Interrupt enable
    Uint32 RXFFINTCLR  : 1; // 6 Clear INT flag
    Uint32 RXFFINT     : 1; // 7 INT flag
    Uint32 RXFFST      : 5; // 12:8 FIFO status
    Uint32 RXFIFORESET : 1; // 13 FIFO reset
    Uint32 RXFFOVRCLR  : 1; // 14 Clear overflow
    Uint32 RXFFOVF     : 1; // 15 FIFO overflow
};

union SCIFFRX_REG
{
    Uint32 all;
    struct SCIFFRX_BITS bit;
};

struct SCIFFCT_BITS
{                       // bits description
    Uint32 FFTXDLY : 8; // 7:0 FIFO transmit delay
    Uint32 rsvd1   : 5; // 12:8 Reserved
    Uint32 CDC     : 1; // 13 Auto baud mode enable
    Uint32 ABDCLR  : 1; // 14 Auto baud clear
    Uint32 ABD     : 1; // 15 Auto baud detect
};

union SCIFFCT_REG
{
    Uint32 all;
    struct SCIFFCT_BITS bit;
};

struct SCIDMACTL_BITS
{                         // bits description
    Uint32 DMA_RX_EN : 1; // 0 DMA RX enable
    Uint32 DMA_TX_EN : 1; // 1 DMA TX enable
};

union SCIDMACTL_REG
{
    Uint32 all;
    struct SCIDMACTL_BITS bit;
};

struct SCIPRI_BITS
{                            // bits description
    Uint32 rsvd1        : 3; // 2:0 Reserved
    Uint32 FREESOFT     : 2; // 4:3 Emulation modes
    Uint32 rsvd2        : 2; // 6:5 Reserved
    Uint32 WAKEUPINTDIS : 1; // 7 Wakeup interrupt disable
    Uint32 rsvd3        : 8; // 15:8 Reserved
};

union SCIPRI_REG
{
    Uint32 all;
    struct SCIPRI_BITS bit;
};

struct SCIFBAUD_BITS
{                            // bits description
    Uint32 BUAD_FRAC    : 4; // 3:0 fractional baudrate set
    Uint32 rsvd         : 3; // 6:4 Reserved
    Uint32 BUAD_FRAC_EN : 1; // 7 fractional baudrate function enable
};

union SCIFBAUD_REG
{
    Uint32 all;
    struct SCIFBAUD_BITS bit;
};

struct SCI_REGS
{
    union SCICCR_REG SCICCR;       // Communications control registeroffset: 0x00
    union SCICTL1_REG SCICTL1;     // Control register 1offset: 0x04
    union SCIHBAUD_REG SCIHBAUD;   // Baud rate (high) registeroffset: 0x08
    union SCILBAUD_REG SCILBAUD;   // Baud rate (low) registeroffset: 0x0C
    union SCICTL2_REG SCICTL2;     // Control register 2offset: 0x10
    union SCIRXST_REG SCIRXST;     // Receive status registeroffset: 0x14
    union SCIRXEMU_REG SCIRXEMU;   // Receive emulation buffer registeroffset: 0x18
    union SCIRXBUF_REG SCIRXBUF;   // Receive data bufferoffset: 0x1C
    union SCITOCTL_REG SCITOCTL;   // Timeout(IDLE) Interrupt Control: 0x20
    union SCITXBUF_REG SCITXBUF;   // Transmit data bufferoffset: 0x24
    union SCIFFTX_REG SCIFFTX;     // FIFO transmit registeroffset: 0x28
    union SCIFFRX_REG SCIFFRX;     // FIFO receive registeroffset: 0x2C
    union SCIFFCT_REG SCIFFCT;     // FIFO control registeroffset: 0x30
    union SCIDMACTL_REG SCIDMACTL; // DMA control registeroffset: 0x34
    union SCIFBAUD_REG SCIFBAUD;   // Baudrate of fractional mode: 0x38
    union SCIPRI_REG SCIPRI;       // SCI priority controloffset: 0x3C
};

//---------------------------------------------------------------------------
// SCI External References & Function Declarations:
//
extern volatile struct SCI_REGS SciaRegs;
extern volatile struct SCI_REGS ScibRegs;
extern volatile struct SCI_REGS ScicRegs;
#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
