#include "driverlib.h"

//*****************************************************************************
//
// CANFD_initModule
//
//*****************************************************************************
void CAN_initModule(uint32_t base, const CAN_Init_Config *ptrCanInit)
{
    if (ptrCanInit != NULL)
    {
        CAN_initParameterCheck(base, ptrCanInit);

        //
        // Enable or disable STB priority mode.
        //
        ((volatile struct CAN_REGS *)base)->TCTRL.bit.TSMODE = ptrCanInit->STBPrioMode;

        //
        // Configures CAN-FD if needed.
        //
        if ((ptrCanInit->ptrCanFd != NULL) && (ptrCanInit->canFDControl == CAN_FD_ENABLE))
        {
            CANFD_config(base, ptrCanInit->ptrCanFd);
            //
            // canfd frame
            //
            HWREG(CPUSYS_BASE + 0x190) = 0x3U;
        }
        else
        {
            //
            // can frame
            //
            HWREG(CPUSYS_BASE + 0x190) = 0x0U;
        }
    }
}

//*****************************************************************************
//
// CAN_structInit
//
//*****************************************************************************
void CAN_structInit(CAN_Init_Config *ptrCanInit)
{

    if (ptrCanInit != NULL)
    {
        ptrCanInit->STBPrioMode  = CAN_STB_PRIO_MD_DISABLE;
        ptrCanInit->canFDControl = CAN_FD_DISABLE;
        ptrCanInit->ptrCanFd     = NULL;
    }
}

//*****************************************************************************
//
// CANFD_structInit
//
//*****************************************************************************
void CANFD_structInit(CANFD_Config *ptrCanFd)
{
    if (ptrCanFd != NULL)
    {
        ptrCanFd->mode      = CAN_FD_MD_ISO;
        ptrCanFd->TDC       = CAN_FD_TDC_DISABLE;
        ptrCanFd->SSPOffset = 16U;
    }
}

//*****************************************************************************
//
// CAN_setBitTimingSlow
//
//*****************************************************************************
void CAN_setBitTimingSlow(
    uint32_t base, uint16_t s_prescale, uint16_t s_seg1, uint16_t s_seg2, uint16_t s_sjw)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((s_prescale <= 256U) && (s_prescale >= 1U));
    ASSERT((((s_seg1) >= 2U) && ((s_seg1) <= 65U)) && (((s_seg2) >= 1U) && ((s_seg2) <= 32U))
           && (((s_sjw) >= 1U) && ((s_sjw) <= 16U)) && ((s_seg1) >= ((s_seg2) + 1U))
           && ((s_seg2) >= (s_sjw)));

    //
    // To set the bit timing register.
    //

    ((volatile struct CAN_REGS *)base)->S_PRESC.bit.SPRESC = s_prescale;
    ((volatile struct CAN_REGS *)base)->S_SJW.bit.SSJW     = s_sjw;
    ((volatile struct CAN_REGS *)base)->S_Seg_1.bit.SSeg1  = s_seg1;
    ((volatile struct CAN_REGS *)base)->S_Seg_2.bit.SSeg2  = s_seg2;
}

//*****************************************************************************
//
// CAN_setBitRateSlow
//
//*****************************************************************************
void CAN_setBitRateSlow(uint32_t base, uint32_t clockFreq, uint32_t bitRate, uint16_t bitTime)
{
    uint16_t brp;
    uint16_t tSeg1;
    uint16_t tSeg2;
    uint16_t sjw;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((bitTime > 7U) && (bitTime < 100U));
    ASSERT(bitRate <= 1000000U);
    ASSERT((bitRate * bitTime) <= clockFreq);

    //
    // Calculate bit timing values
    //
    brp   = (uint16_t)(clockFreq / (bitRate * bitTime));
    tSeg1 = (bitTime * 0.8);
    tSeg2 = bitTime - tSeg1;
    sjw   = tSeg2;

    //
    // Set the calculated timing parameters
    //
    CAN_setBitTimingSlow(base, brp - 1, tSeg1 - 2, tSeg2 - 1, sjw - 1);
}

//*****************************************************************************
//
// CANFD_setBitTimingFast
//
//*****************************************************************************
void CANFD_setBitTimingFast(
    uint32_t base, uint16_t f_prescale, uint16_t f_seg1, uint16_t f_seg2, uint16_t f_sjw)
{

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((f_prescale <= 256U) && (f_prescale >= 1U));
    ASSERT((((f_seg1) >= 2U) && ((f_seg1) <= 17U)) && (((f_seg2) >= 1U) && ((f_seg2) <= 8U))
           && (((f_sjw) >= 1U) && ((f_sjw) <= 8U)) && ((f_seg1) >= ((f_seg2) + 1U))
           && ((f_seg2) >= (f_sjw)));

    //
    // To set the bit timing register.
    //
    ((volatile struct CAN_REGS *)base)->F_PRESC.bit.FPRESC = f_prescale;
    ((volatile struct CAN_REGS *)base)->F_SJW.bit.FSJW     = f_sjw;
    ((volatile struct CAN_REGS *)base)->F_Seg_1.bit.FSeg1  = f_seg1;
    ((volatile struct CAN_REGS *)base)->F_Seg_2.bit.FSeg2  = f_seg2;
}

//*****************************************************************************
//
// CANFD_setBitRateFast
//
//*****************************************************************************
void CANFD_setBitRateFast(uint32_t base, uint32_t clockFreq, uint32_t bitRate, uint16_t bitTime)
{
    uint16_t brp;
    uint16_t tSeg1;
    uint16_t tSeg2;
    uint16_t sjw;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((bitTime > 7U) && (bitTime < 100U));
    ASSERT(bitRate <= 8000000U);
    ASSERT((bitRate * bitTime) <= clockFreq);

    //
    // Calculate bit timing values
    //
    if (bitRate == 5000000U)
    {
        tSeg1 = (bitTime * 0.75);
    }
    else
    {
        tSeg1 = (bitTime * 0.8);
    }

    brp   = (uint16_t)(clockFreq / (bitRate * bitTime));
    tSeg2 = bitTime - tSeg1;
    sjw   = tSeg2;

    //
    // Set the calculated timing parameters
    //
    CANFD_setBitTimingFast(base, brp - 1, tSeg1 - 2, tSeg2 - 1, sjw - 1);
}

//*****************************************************************************
//
// CAN_setAcceptFilter
//
//*****************************************************************************
void CAN_setAcceptFilter(
    uint32_t base, uint16_t acfSelect, uint32_t idType, uint32_t idCode, uint32_t idMask)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((idType == CAN_ID_STD_EXT) || (idType == CAN_ID_STD) || (idType == CAN_ID_EXT));
    ASSERT(((idMask) | 0x1FFFFFFFUL) == 0x1FFFFFFFUL);
    ASSERT((acfSelect >= 0u) && (acfSelect <= 15u));

    //
    // Check the filter.
    //
    ((volatile struct CAN_REGS *)base)->ACFCTRL.bit.ACFADR = acfSelect;
    //
    // Specify Filter Code.
    //
    ((volatile struct CAN_REGS *)base)->ACFCTRL.bit.SELMASK = 0u;
    ((volatile struct CAN_REGS *)base)->ACF.all             = idCode;
    //
    // Specify Filter Mask.
    //
    ((volatile struct CAN_REGS *)base)->ACFCTRL.bit.SELMASK = 1u;
    ((volatile struct CAN_REGS *)base)->ACF.all             = idMask | idType;

    //
    // enable the filter.
    //
    CAN_filterCmd(base, acfSelect, ENABLE);
}

//*****************************************************************************
//
// CANFD_FilterCmd
//
//*****************************************************************************
void CAN_filterCmd(uint32_t base, uint16_t acfSelect, EN_Functional_Status enFilterState)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((enFilterState == ENABLE) || (enFilterState == DISABLE));

    if (enFilterState == ENABLE)
    {
        (*((volatile uint16_t *)(base + 0xB6))) |= (1 << acfSelect);
    }
    else
    {
        (*((volatile uint16_t *)(base + 0xB6))) &= ~(1 << acfSelect);
    }
}

//*****************************************************************************
//
// CANFD_getStatus
//
//*****************************************************************************
EN_Flag_Status CAN_getStatus(uint32_t base, uint32_t flag)
{
    uint8_t CFGSTAT;
    uint8_t RCTRL;
    uint8_t RTIE;
    uint8_t RTIF;
    uint8_t ERRINT;
    EN_Flag_Status enStatus = RESET;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((((flag) != 0U) && (((flag) | (CAN_FLAG_ALL)) == (CAN_FLAG_ALL))));

    CFGSTAT = (uint8_t)(flag & 0x7UL);
    RCTRL   = (uint8_t)(flag & CAN_FLAG_RX_BUF_OVF);
    RTIE    = (uint8_t)(flag >> 8U);
    RTIF    = (uint8_t)(flag >> 16U);
    ERRINT  = (uint8_t)(flag >> 24U);

    CFGSTAT = (((volatile struct CAN_REGS *)base)->CFGSTAT.all) & CFGSTAT;
    RCTRL   = (((volatile struct CAN_REGS *)base)->RCTRL.all) & RCTRL;
    RTIE    = (((volatile struct CAN_REGS *)base)->RTIE.all) & RTIE;
    RTIF    = (((volatile struct CAN_REGS *)base)->RTIF.all) & RTIF;
    ERRINT  = (((volatile struct CAN_REGS *)base)->ERRINT.all) & ERRINT;

    if ((CFGSTAT != 0U) || (RCTRL != 0U) || (RTIE != 0U) || (RTIF != 0U) || (ERRINT != 0U))
    {
        enStatus = SET;
    }

    return enStatus;
}

//*****************************************************************************
//
// CAN_clearInterruptStatus
//
//*****************************************************************************
void CAN_clearInterruptStatus(uint32_t base, uint32_t flag)
{
    uint8_t RTIF;
    uint8_t ERRINT;
    uint8_t reg;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((((flag) != 0U) && (((flag) | (CAN_FLAG_ALL)) == (CAN_FLAG_ALL))));

    flag &= CAN_FLAG_CLR_ALL;
    RTIF   = (uint8_t)(flag >> 16U);
    ERRINT = (uint8_t)(flag >> 24U);

    ((volatile struct CAN_REGS *)base)->RTIF.all = RTIF;

    reg = ((volatile struct CAN_REGS *)base)->ERRINT.all;
    reg &= (uint8_t)(~CAN_ERRINT_FLAG_MASK);
    reg |= ERRINT;
    ((volatile struct CAN_REGS *)base)->ERRINT.all = reg;
}

//*****************************************************************************
//
// CAN_getTxBufStatus
//
//*****************************************************************************
uint8_t CAN_getTxBufStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    return (((volatile struct CAN_REGS *)base)->TCTRL.bit.TSSTAT);
}

//*****************************************************************************
//
// CAN_getRxBufStatus
//
//*****************************************************************************
uint8_t CAN_getRxBufStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    return (((volatile struct CAN_REGS *)base)->RCTRL.bit.RSTAT);
}

//*****************************************************************************
//
// CAN_getErrorInfo
//
//*****************************************************************************
bool CAN_getErrorInfo(uint32_t base, CAN_Error_Info *ptrErr)
{

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));

    if (ptrErr != NULL)
    {
        ptrErr->arbitrLostPos = ((volatile struct CAN_REGS *)base)->EALCAP.bit.ALC;
        ptrErr->errorType     = ((volatile struct CAN_REGS *)base)->EALCAP.bit.KOER;
        ptrErr->rxErrorCount  = ((volatile struct CAN_REGS *)base)->RECNT.all;
        ptrErr->txErrorCount  = ((volatile struct CAN_REGS *)base)->TECNT.all;
    }
    return ((bool)((((volatile struct CAN_REGS *)base)->ERRINT.bit.EWARN) != 0U));
}

//*****************************************************************************
//
// CAN_setRxWarnLimit
//
//*****************************************************************************
void CAN_setRxWarnLimit(uint32_t base, uint8_t rxWarnLimit)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((rxWarnLimit >= CAN_RX_WARN_MIN) && (rxWarnLimit <= CAN_RX_WARN_MAX));
    ((volatile struct CAN_REGS *)base)->LIMIT.bit.AFWL = rxWarnLimit;
}

//*****************************************************************************
//
// CAN_setErrorWarnLimit
//
//*****************************************************************************
void CAN_setErrorWarnLimit(uint32_t base, uint8_t errorWarnLimit)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT(errorWarnLimit < 16u);
    ((volatile struct CAN_REGS *)base)->LIMIT.bit.EWL = errorWarnLimit;
}

//*****************************************************************************
//
// CAN_startTx
//
//*****************************************************************************
void CAN_startTx(uint32_t base, uint8_t txRequest)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((txRequest == CAN_TX_REQ_STB_ONE) || (txRequest == CAN_TX_REQ_STB_ALL)
           || (txRequest == CAN_TX_REQ_PTB));
    ((volatile struct CAN_REGS *)base)->TCMD.all |= txRequest;
}

//*****************************************************************************
//
// CAN_abortTx
//
//*****************************************************************************
void CAN_abortTx(uint32_t base, uint8_t txBufType)
{
    uint8_t txAbort[] = { CAN_CMD_TPA, CAN_CMD_TSA };
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((txBufType == CAN_TX_BUF_PTB) || (txBufType == CAN_TX_BUF_STB));
    ((volatile struct CAN_REGS *)base)->TCMD.all |= txAbort[txBufType];
}

//*****************************************************************************
//
// CAN_fillMessage
//
//*****************************************************************************
void CAN_fillMessage(uint32_t base, uint8_t txBufType, const uint32_t msgID,
    const CAN_TBUF_Ctrl *ptrTBUFCtrl, const void *msgData)
{

    uint8_t stbBuffFull = 0u;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((txBufType == CAN_TX_BUF_PTB) || (txBufType == CAN_TX_BUF_STB));
    ASSERT((((ptrTBUFCtrl->IDE) == CAN_IDE_EXTEND) && (((msgID) | 0x1FFFFFFFUL) == 0x1FFFFFFFUL))
           || (((ptrTBUFCtrl->IDE) == CAN_IDE_STANDARD) && (((msgID) | 0x7FFUL) == 0x7FFUL)));

    if ((ptrTBUFCtrl != NULL) || (msgData != NULL))
    {
        if (txBufType == CAN_TX_BUF_STB)
        {
            if ((((volatile struct CAN_REGS *)base)->RTIE.bit.TSFF)
                || (((volatile struct CAN_REGS *)base)->TCTRL.bit.TSSTAT) == 3U)
            {
                //
                // All STBs are filled.
                //
                stbBuffFull = 1u;
            }
            else
            {
                stbBuffFull = 0u;
            }
        }

        if ((stbBuffFull != 1u) || (txBufType == CAN_TX_BUF_PTB))
        {
            //
            // Wait for busy bit to clear
            //
            while (CAN_isTransmitterBusy(base))
                ;

            //
            // Specifies the transmit buffer, PTB or STB.
            //
            if (txBufType == CAN_TX_BUF_STB)
            {
                ((volatile struct CAN_REGS *)base)->TCMD.bit.TBSEL = 1U;
            }
            else
            {
                ((volatile struct CAN_REGS *)base)->TCMD.bit.TBSEL = 0U;
            }

            //
            // fill tx buff.
            //
            CAN_writeDataReg(base, msgID, ptrTBUFCtrl, msgData);

            if (txBufType == CAN_TX_BUF_STB)
            {
                //
                // After writes the data in transmit buffer(TB), sets the TSNEXT bit to indicate
                // that the current STB slot has been filled, so that the hardware will point TB to
                // the next STB slot.
                //
                ((volatile struct CAN_REGS *)base)->TCTRL.bit.TSNEXT = 1U;
            }
        }
    }
}

//*****************************************************************************
//
// CAN_fillRemoteRequestMessage
//
//*****************************************************************************
void CAN_fillRemoteRequestMessage(
    uint32_t base, uint8_t txBufType, const uint32_t msgID, const CAN_TBUF_Ctrl *ptrTBUFCtrl)
{

    uint8_t stbBuffFull           = 0u;
    volatile struct CAN_REGS *can = (volatile struct CAN_REGS *)base;

    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((txBufType == CAN_TX_BUF_PTB) || (txBufType == CAN_TX_BUF_STB));
    ASSERT((((ptrTBUFCtrl->IDE) == CAN_IDE_EXTEND) && (((msgID) | 0x1FFFFFFFUL) == 0x1FFFFFFFUL))
           || (((ptrTBUFCtrl->IDE) == CAN_IDE_STANDARD) && (((msgID) | 0x7FFUL) == 0x7FFUL)));
    ASSERT((txBufType == CAN_TX_BUF_PTB) || (txBufType == CAN_TX_BUF_STB));
    ASSERT((ptrTBUFCtrl->RTR == CAN_RTR_REMOTE) && (ptrTBUFCtrl->FDF == CAN_FDF_CAN20)
           && (ptrTBUFCtrl->BRS == CANFD_BRS_SLOW));

    if ((ptrTBUFCtrl != NULL))
    {
        if (txBufType == CAN_TX_BUF_STB)
        {
            if ((((volatile struct CAN_REGS *)base)->RTIE.bit.TSFF)
                || (((volatile struct CAN_REGS *)base)->TCTRL.bit.TSSTAT) != 0U)
            {
                //
                // All STBs are filled.
                //
                stbBuffFull = 1u;
            }
            else
            {
                stbBuffFull = 0u;
            }
        }

        if ((stbBuffFull != 1u) || (txBufType == CAN_TX_BUF_PTB))
        {
            //
            // Wait for busy bit to clear
            //
            while (CAN_isTransmitterBusy(base))
                ;

            //
            // Specifies the transmit buffer, PTB or STB.
            //
            if (txBufType == CAN_TX_BUF_STB)
            {
                ((volatile struct CAN_REGS *)base)->TCMD.bit.TBSEL = 1U;
            }
            else
            {
                ((volatile struct CAN_REGS *)base)->TCMD.bit.TBSEL = 0U;
            }

            //
            // fill tx buff.
            //
            can->TBUF[0U] = msgID;
            can->TBUF[0U] |= ptrTBUFCtrl->TTSEN << 31U;
            can->TBUF[1U] = ptrTBUFCtrl->u32TBUFCtrlAll;

            if (txBufType == CAN_TX_BUF_STB)
            {
                //
                // After writes the data in transmit buffer(TB), sets the TSNEXT bit to indicate
                // that the current STB slot has been filled, so that the hardware will point TB to
                // the next STB slot.
                //
                ((volatile struct CAN_REGS *)base)->TCTRL.bit.TSNEXT = 1U;
            }
        }
    }
}

//*****************************************************************************
//
// CAN_readMessage
//
//*****************************************************************************
bool CAN_readMessage(uint32_t base, void *msgData)
{

    bool status;
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT(msgData != NULL);

    if (((volatile struct CAN_REGS *)base)->RCTRL.bit.RSTAT != CAN_RX_BUF_EMPTY)
    {
        CAN_readDataReg(base, msgData);

        //
        // Set RB to point to the next RB slot.
        //
        ((volatile struct CAN_REGS *)base)->RCTRL.bit.RREL = 1u;

        status = TRUE;
    }
    else
    {
        status = FALSE;
    }

    return status;
}

//*****************************************************************************
//
// CAN_readMessageWithID
//
//*****************************************************************************
bool CAN_readMessageWithID(
    uint32_t base, uint32_t *msgID, CAN_RBUF_Ctrl *ptrRBUFCtrl, void *msgData)
{
    bool status;
    volatile struct CAN_REGS *can = (volatile struct CAN_REGS *)base;
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT(ptrRBUFCtrl != NULL);
    ASSERT(msgData != NULL);

    if (can->RCTRL.bit.RSTAT != CAN_RX_BUF_EMPTY)
    {
        //
        // Read RBUF data.
        //
        CAN_readDataReg(base, msgData);

        //
        // Read RBUF IDE and ID.
        //
        if (can->RBUF[1U] & 0x80U)
        {
            *msgID = can->RBUF[0U] & CAN_EXTEND_IDMASK;
        }
        else
        {
            *msgID = can->RBUF[0U] & CAN_STANDARD_IDMASK;
        }

        //
        // Read RBUF control.
        //
        ptrRBUFCtrl->u32RBUFCtrlAll = can->RBUF[1U];

        //
        // Set RB to point to the next RB slot.
        //
        ((volatile struct CAN_REGS *)base)->RCTRL.bit.RREL = 1u;

        status = TRUE;
    }
    else
    {
        status = FALSE;
    }
    return status;
}

//*****************************************************************************
//
// CAN_enableInterrupt
//
//*****************************************************************************
void CAN_enableInterrupt(uint32_t base, CAN_IntType ints)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((((ints) != 0U) && (((ints) | (CAN_INT_ALL)) == (CAN_INT_ALL))));
    ((volatile struct CAN_REGS *)base)->RTIE.all   = (uint8_t)ints;
    ((volatile struct CAN_REGS *)base)->ERRINT.all = (uint8_t)(ints >> 8U);
}

//*****************************************************************************
//
// CAN_disableInterrupt
//
//*****************************************************************************
void CAN_disableInterrupt(uint32_t base, CAN_IntType ints)
{
    //
    // Check the arguments.
    //
    ASSERT(CAN_isBaseValid(base));
    ASSERT((((ints) != 0U) && (((ints) | (CAN_INT_ALL)) == (CAN_INT_ALL))));
    ((volatile struct CAN_REGS *)base)->RTIE.all &= ((uint8_t)(~(uint8_t)ints));
    ((volatile struct CAN_REGS *)base)->ERRINT.all &= ((uint8_t)(~(uint8_t)(ints >> 8U)));
}
