#include "ipc.h"
#include "interrupt.h"

//
// Macros internal to the IPC driver
//

#define IPC_ADDR_OFFSET_NOCHANGE 2U
#define IPC_ADDR_OFFSET_MUL2     4U
#define IPC_ADDR_OFFSET_DIV2     1U

#define IPC_ADDR_OFFSET_CORR(addr, corr) (((addr) * (corr)) / 2U)

#if IPC_MSGQ_SUPPORT == 1U

//
// Global Circular Buffer Definitions
//

//
// IPC_CPU1_To_CPU2_PutBuffer acts as IPC_CPU2_To_CPU1_GetBuffer and
// IPC_CPU1_To_CPU2_GetBuffer acts as IPC_CPU2_To_CPU1_PutBuffer
//
extern struct IPC_PutBuffer_t IPC_CPU1_To_CPU2_PutBuffer;
extern struct IPC_GetBuffer_t IPC_CPU1_To_CPU2_GetBuffer;
#endif

const IPC_Instance_t IPC_Instance[IPC_TOTAL_NUM] = {

    /* IPC_CPU1_L_CPU2_R */
    { .IPC_Flag_Ctr_Reg  = (volatile IPC_Flag_Ctr_Reg_t *)IPC_REG_BASE,
        .IPC_SendCmd_Reg = (volatile IPC_SendCmd_Reg_t *)(IPC_REG_BASE + 0x100U),
        .IPC_RecvCmd_Reg = (volatile IPC_RecvCmd_Reg_t *)(IPC_REG_BASE + 0x110U),
        //      .IPC_Boot_Pump_Reg  = (volatile IPC_Boot_Pump_Reg_t *)
        //                            (IPC_BASE + 0x20U),
        .IPC_IntNum      = { INT_IPC0, INT_IPC1, INT_IPC2, INT_IPC3, 0U, 0U, 0U, 0U },
        .IPC_MsgRam_LtoR = IPC_CPU1_MEM_BASE,
        .IPC_MsgRam_RtoL = IPC_CPU2_MEM_BASE,
        .IPC_Offset_Corr = IPC_ADDR_OFFSET_NOCHANGE
#if IPC_MSGQ_SUPPORT == 1U
        ,
        .IPC_PutBuffer = &IPC_CPU1_To_CPU2_PutBuffer,
        .IPC_GetBuffer = &IPC_CPU1_To_CPU2_GetBuffer
#endif
    },

    /* IPC_CPU2_L_CPU1_R */
    { .IPC_Flag_Ctr_Reg  = (volatile IPC_Flag_Ctr_Reg_t *)IPC_REG_BASE,
        .IPC_SendCmd_Reg = (volatile IPC_SendCmd_Reg_t *)(IPC_REG_BASE + 0x100U),
        .IPC_RecvCmd_Reg = (volatile IPC_RecvCmd_Reg_t *)(IPC_REG_BASE + 0x110U),
        //      .IPC_Boot_Pump_Reg  = (volatile IPC_Boot_Pump_Reg_t *)
        //                            (IPC_BASE + 0x20U),
        .IPC_IntNum      = { INT_IPC0, INT_IPC1, INT_IPC2, INT_IPC3, 0U, 0U, 0U, 0U },
        .IPC_MsgRam_LtoR = IPC_CPU2_MEM_BASE,
        .IPC_MsgRam_RtoL = IPC_CPU1_MEM_BASE,
        .IPC_Offset_Corr = IPC_ADDR_OFFSET_NOCHANGE
#if IPC_MSGQ_SUPPORT == 1U
        ,
        .IPC_PutBuffer = (struct IPC_PutBuffer_t *)&IPC_CPU1_To_CPU2_GetBuffer,
        .IPC_GetBuffer = (struct IPC_GetBuffer_t *)&IPC_CPU1_To_CPU2_PutBuffer
#endif
    }
};

//*****************************************************************************
//
// IPC_sendCommand
//
//*****************************************************************************
bool IPC_sendCommand(IPC_Type_t ipcType, uint32_t flags, bool addrCorrEnable, uint32_t command,
    uint32_t addr, uint32_t data)
{
    bool ret;

    //
    // Check whether the flags are not busy
    //
    if ((IPC_Instance[ipcType].IPC_Flag_Ctr_Reg->IPC_FLG & flags) == 0U)
    {
        ret = true;

        if (addrCorrEnable)
        {
            //
            // Update the command registers. ADDR register holds the offset
            // from the base address of the MSG RAM
            //
            IPC_Instance[ipcType].IPC_SendCmd_Reg->IPC_SENDCOM  = command;
            IPC_Instance[ipcType].IPC_SendCmd_Reg->IPC_SENDDATA = data;
            IPC_Instance[ipcType].IPC_SendCmd_Reg->IPC_SENDADDR
                = addr - IPC_Instance[ipcType].IPC_MsgRam_LtoR;
        }
        else
        {
            //
            // Update the command registers. addr param remains as is.
            //
            IPC_Instance[ipcType].IPC_SendCmd_Reg->IPC_SENDCOM  = command;
            IPC_Instance[ipcType].IPC_SendCmd_Reg->IPC_SENDDATA = data;
            IPC_Instance[ipcType].IPC_SendCmd_Reg->IPC_SENDADDR = addr;
        }

        //
        // Set the flags to indicate the remote core
        //
        IPC_Instance[ipcType].IPC_Flag_Ctr_Reg->IPC_SET = flags;
    }
    else
    {
        ret = false;
    }

    return (ret);
}

//*****************************************************************************
//
// IPC_readCommand
//
//*****************************************************************************
bool IPC_readCommand(IPC_Type_t ipcType, uint32_t flags, bool addrCorrEnable, uint32_t *command,
    uint32_t *addr, uint32_t *data)
{
    bool ret;
    uint32_t addrReg;

    //
    // Check whether the flags are not empty
    //
    if ((IPC_Instance[ipcType].IPC_Flag_Ctr_Reg->IPC_STS & flags) != 0U)
    {
        ret = true;

        //
        // Read the command registers
        //
        *command = IPC_Instance[ipcType].IPC_RecvCmd_Reg->IPC_RECVCOM;
        addrReg  = IPC_Instance[ipcType].IPC_RecvCmd_Reg->IPC_RECVADDR;
        *data    = IPC_Instance[ipcType].IPC_RecvCmd_Reg->IPC_RECVDATA;

        if (addrCorrEnable)
        {
            //
            // Calculate the address form the offset
            //
            *addr = IPC_Instance[ipcType].IPC_MsgRam_RtoL
                    + IPC_ADDR_OFFSET_CORR(addrReg, IPC_Instance[ipcType].IPC_Offset_Corr);
        }
        else
        {
            *addr = addrReg;
        }
    }
    else
    {
        ret = false;
    }

    return (ret);
}

//*****************************************************************************
//
// IPC_registerInterrupt
//
//*****************************************************************************
void IPC_registerInterrupt(IPC_Type_t ipcType, uint32_t ipcInt, void (*pfnHandler)(void))
{
    //
    // Check for arguments
    //

    ASSERT(ipcInt <= IPC_INT3);

    //
    // Get the corresponding interrupt number
    //
    uint32_t intNum = IPC_Instance[ipcType].IPC_IntNum[ipcInt];

    //
    // Register the interrupt handler
    //

    Interrupt_register(intNum, pfnHandler);

    //
    // Enable the interrupt
    //
    Interrupt_enable(intNum);
}

//*****************************************************************************
//
// IPC_unregisterInterrupt
//
//*****************************************************************************
void IPC_unregisterInterrupt(IPC_Type_t ipcType, uint32_t ipcInt)
{
    //
    // Check for arguments
    //

    ASSERT(ipcInt <= IPC_INT3);

    //
    // Get the corresponding interrupt number
    //
    uint32_t intNum = IPC_Instance[ipcType].IPC_IntNum[ipcInt];

    //
    // Disable the interrupt.
    //
    Interrupt_disable(intNum);

    //
    // Unregister the interrupt handler.
    //

    //    Interrupt_unregister(intNum);
}

#if IPC_MSGQ_SUPPORT == 1U
//*****************************************************************************
//
// IPCinitMessageQueue
//
//*****************************************************************************
void IPC_initMessageQueue(
    IPC_Type_t ipcType, volatile IPC_MessageQueue_t *msgQueue, uint32_t ipcInt_L, uint32_t ipcInt_R)
{
    //
    // Check for arguments
    //
    ASSERT(msgQueue != NULL);
    ASSERT(ipcInt_L < IPC_NUM_OF_INTERRUPTS);
    ASSERT(ipcInt_R < IPC_NUM_OF_INTERRUPTS);

    struct IPC_PutBuffer_t *putBuffer = IPC_Instance[ipcType].IPC_PutBuffer;
    struct IPC_GetBuffer_t *getBuffer = IPC_Instance[ipcType].IPC_GetBuffer;

    //
    // L->R Put Buffer and Index Initialization
    //
    msgQueue->PutBuffer     = putBuffer->Buffer[ipcInt_R];
    msgQueue->PutWriteIndex = &(putBuffer->PutWriteIndex[ipcInt_R]);
    msgQueue->GetReadIndex  = &(putBuffer->GetReadIndex[ipcInt_L]);
    msgQueue->PutFlag       = (uint32_t)1U << ipcInt_R;

    //
    // L->R Get Buffer and Index Initialization
    //
    msgQueue->GetBuffer     = getBuffer->Buffer[ipcInt_L];
    msgQueue->GetWriteIndex = &(getBuffer->GetWriteIndex[ipcInt_L]);
    msgQueue->PutReadIndex  = &(getBuffer->PutReadIndex[ipcInt_R]);

    //
    // Initialize PutBuffer WriteIndex = 0 and GetBuffer ReadIndex = 0
    //
    *(msgQueue->PutWriteIndex) = 0U;
    *(msgQueue->GetReadIndex)  = 0U;
}

//*****************************************************************************
//
// IPC_sendMessageToQueue
//
//*****************************************************************************
bool IPC_sendMessageToQueue(IPC_Type_t ipcType, volatile IPC_MessageQueue_t *msgQueue,
    bool addrCorrEnable, IPC_Message_t *msg, bool block)
{
    //
    // Check for arguments
    //
    ASSERT(msgQueue != NULL);
    ASSERT(msg != NULL);

    uint16_t writeIndex;
    uint16_t readIndex;
    bool ret = true;

    writeIndex = *(msgQueue->PutWriteIndex);
    readIndex  = *(msgQueue->PutReadIndex);

    //
    // Wait until Put Buffer slot is free
    //
    while (((writeIndex + 1U) & IPC_MAX_BUFFER_INDEX) == readIndex)
    {
        //
        // If designated as a "Blocking" function, and Put buffer is full,
        // return immediately with fail status.
        //
        if (!block)
        {
            ret = false;
            break;
        }

        readIndex = *(msgQueue->PutReadIndex);
    }

    if (ret != false)
    {
        //
        // When slot is free, Write Message to PutBuffer, update PutWriteIndex,
        // and set the CPU IPC INT Flag
        //
        msgQueue->PutBuffer[writeIndex] = *msg;

        if (addrCorrEnable)
        {
            msgQueue->PutBuffer[writeIndex].address -= IPC_Instance[ipcType].IPC_MsgRam_LtoR;
        }

        writeIndex                 = (writeIndex + 1U) & IPC_MAX_BUFFER_INDEX;
        *(msgQueue->PutWriteIndex) = writeIndex;

        IPC_setFlagLtoR(ipcType, msgQueue->PutFlag);
    }

    return (ret);
}

//*****************************************************************************
//
// IPC_readMessageFromQueue
//
//*****************************************************************************
bool IPC_readMessageFromQueue(IPC_Type_t ipcType, volatile IPC_MessageQueue_t *msgQueue,
    bool addrCorrEnable, IPC_Message_t *msg, bool block)
{
    //
    // Check for arguments
    //
    ASSERT(msgQueue != NULL);
    ASSERT(msg != NULL);

    uint16_t writeIndex;
    uint16_t readIndex;
    bool ret = true;

    writeIndex = *(msgQueue->GetWriteIndex);
    readIndex  = *(msgQueue->GetReadIndex);

    //
    // Loop while GetBuffer is empty
    //
    while (writeIndex == readIndex)
    {
        //
        // If designated as a "Blocking" function, and Get buffer is empty,
        // return immediately with fail status.
        //
        if (!block)
        {
            ret = false;
            break;
        }

        writeIndex = *(msgQueue->GetWriteIndex);
    }

    if (ret != false)
    {
        //
        // If there is a message in GetBuffer, Read Message and update
        // the ReadIndex
        //
        *msg = msgQueue->GetBuffer[readIndex];
        if (addrCorrEnable)
        {
            msg->address
                = IPC_Instance[ipcType].IPC_MsgRam_RtoL
                  + IPC_ADDR_OFFSET_CORR(msg->address, IPC_Instance[ipcType].IPC_Offset_Corr);
        }

        readIndex                 = (readIndex + 1U) & IPC_MAX_BUFFER_INDEX;
        *(msgQueue->GetReadIndex) = readIndex;
    }

    return (ret);
}
#endif
