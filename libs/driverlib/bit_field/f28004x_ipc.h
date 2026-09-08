#ifndef F28004X_IPC_H
#define F28004X_IPC_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Watchdog Register Bit Definitions:
//---------------------------------------------------------------------------
struct IPC_EVENT_BITS
{
    Uint32 IPC_EVENT0  : 1;
    Uint32 IPC_EVENT1  : 1;
    Uint32 IPC_EVENT2  : 1;
    Uint32 IPC_EVENT3  : 1;
    Uint32 IPC_EVENT4  : 1;
    Uint32 IPC_EVENT5  : 1;
    Uint32 IPC_EVENT6  : 1;
    Uint32 IPC_EVENT7  : 1;
    Uint32 IPC_EVENT8  : 1;
    Uint32 IPC_EVENT9  : 1;
    Uint32 IPC_EVENT10 : 1;
    Uint32 IPC_EVENT11 : 1;
    Uint32 IPC_EVENT12 : 1;
    Uint32 IPC_EVENT13 : 1;
    Uint32 IPC_EVENT14 : 1;
    Uint32 IPC_EVENT15 : 1;
    Uint32 IPC_EVENT16 : 1;
    Uint32 IPC_EVENT17 : 1;
    Uint32 IPC_EVENT18 : 1;
    Uint32 IPC_EVENT19 : 1;
    Uint32 IPC_EVENT20 : 1;
    Uint32 IPC_EVENT21 : 1;
    Uint32 IPC_EVENT22 : 1;
    Uint32 IPC_EVENT23 : 1;
    Uint32 IPC_EVENT24 : 1;
    Uint32 IPC_EVENT25 : 1;
    Uint32 IPC_EVENT26 : 1;
    Uint32 IPC_EVENT27 : 1;
    Uint32 IPC_EVENT28 : 1;
    Uint32 IPC_EVENT29 : 1;
    Uint32 IPC_EVENT30 : 1;
    Uint32 IPC_EVENT31 : 1;
};

union IPC_EVENT_REG
{
    Uint32 all;
    struct IPC_EVENT_BITS bit;
};

struct IPC_EVENT_REGS
{
    union IPC_EVENT_REG IPC_SET; // offset: 0x00
    union IPC_EVENT_REG IPC_CLR; // offset: 0x04
    union IPC_EVENT_REG IPC_FLG; // offset: 0x08
    union IPC_EVENT_REG IPC_STS; // offset: 0x0C
    union IPC_EVENT_REG IPC_ACK; // offset: 0x10
    Uint32 IPCCOUNTERL;          // offset: 0x14
    Uint32 IPCCOUNTERH;          // offset: 0x18
};

struct IPC_CMD_REGS
{
    Uint32 IPC_SEND_COM;    // offset: 0x00
    Uint32 IPC_SEND_ADDR;   // offset: 0x04
    Uint32 IPC_SEND_DATA;   // offset: 0x08
    Uint32 IPC_LOCAL_REPLY; // offset: 0x0C

    Uint32 IPC_RECV_COM;     // offset: 0x10
    Uint32 IPC_RECV_ADDR;    // offset: 0x14
    Uint32 IPC_RECV_DATA;    // offset: 0x18
    Uint32 IPC_REMOTE_REPLY; // offset: 0x1C
};

extern volatile struct IPC_EVENT_REGS IpcEventRegs;
extern volatile struct IPC_CMD_REGS IpcCmdRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
