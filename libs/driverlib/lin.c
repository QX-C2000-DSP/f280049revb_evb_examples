#include "driverlib.h"

void LIN_sendCommand(uint32_t base, LIN_Cmd cmd, u8 ms, u8 lin13, u8 len)
{
    u8 tmp = 0x00;
    switch (cmd)
    {
        case CMD_ABORT:
            tmp = (ms) ? 0x80 : 0x00;                              // set master/slave mode
            tmp |= (lin13) ? 1 << 6 : 0 << 6;                      // LIN13 Checksum
            tmp |= (len & 0xF) << 2;                               // set size
            tmp |= CMD_ABORT;                                      // set response type
            ((volatile struct LIN_REGS *)base)->LSR_LCR.all = tmp; // write to LCR register
            break;

        case CMD_SEND_HEADER:
            if (ms)
            {
                tmp = 0x81;                                 // master mode, Send header command
                tmp |= (lin13) ? 1 << 6 : 0 << 6;           // LIN13 Checksum
                tmp |= (lin13) ? 0x3C : ((len & 0xF) << 2); // set size
                ((volatile struct LIN_REGS *)base)->LSR_LCR.all = tmp; // write to LCR register
            }
            break;

        case CMD_RESPONSE_TX:
            tmp = (ms) ? 0x80 : 0x00;                              // set master/slave mode
            tmp |= (lin13) ? 1 << 6 : 0 << 6;                      // LIN13 Checksum
            tmp |= (len & 0xF) << 2;                               // set size
            tmp |= CMD_RESPONSE_TX;                                // set response type
            ((volatile struct LIN_REGS *)base)->LSR_LCR.all = tmp; // write to LCR register
            break;

        case CMD_RESPONSE_RX:
            tmp = (ms) ? 0x80 : 0x00;                              // set master/slave mode
            tmp |= (lin13) ? 1 << 6 : 0 << 6;                      // LIN13 Checksum
            tmp |= (len & 0xF) << 2;                               // set size
            tmp |= CMD_RESPONSE_RX;                                // set response type
            ((volatile struct LIN_REGS *)base)->LSR_LCR.all = tmp; // write to LCR register
            break;

        case CMD_WAKEUP:
            tmp = (ms) ? 0x80 : 0x00;                              // set master/slave mode
            tmp |= (lin13) ? 1 << 6 : 0 << 6;                      // LIN13 Checksum
            tmp |= 0x35;                                           // switch to wake-up mode
            ((volatile struct LIN_REGS *)base)->LSR_LCR.all = tmp; // write to LCR register
            break;

        default:
            break;
    }
}

void LIN_writeLSEL(uint32_t base, LIN_CmdDelay cmd_delay, u8 ainc, u8 index)
{
    struct LIN_LSEL_BITS lsel_state;
    *((u8 *)&lsel_state)                         = 0x00;
    lsel_state.AINC                              = ainc;
    lsel_state.INDEX                             = index & 0xF;
    lsel_state.DLY                               = cmd_delay;
    ((volatile struct LIN_REGS *)base)->LSEL.all = *((u8 *)&lsel_state);
}

void LIN_writeBuffer(uint32_t base, u8 *dat, u8 len)
{
    while (len--)
    {
        ((volatile struct LIN_REGS *)base)->LBUF = *dat++;
    }
}

void LIN_readBuffer(uint32_t base, u8 *dat, u8 len)
{
    while (len--)
    {
        *dat++ = LIN_getLBUF(base);
    }
}

struct LIN_LSR_BITS LIN_waitForHeader(uint32_t base)
{
    struct LIN_LSR_BITS status;
    do
    {
        *((u8 *)&status) = LIN_getLSR(base);
    } while (status.LID == 0);
    return status;
}

struct LIN_LSR_BITS LIN_waitForReady(uint32_t base)
{
    struct LIN_LSR_BITS status;
    do
    {
        *((u8 *)&status) = LIN_getLSR(base);
    } while (status.RDY == 0);
    return status;
}
