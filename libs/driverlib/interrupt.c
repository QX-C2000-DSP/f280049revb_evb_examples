#include "interrupt.h"

//*****************************************************************************
//
//! \internal
//! Clears the IFR flag in the CPU.
//!
//! \param group specifies the interrupt group to be cleared.
//!
//! This function clears the IFR flag.  This switch is needed because the
//! clearing of the IFR can only be done with a constant.
//
//*****************************************************************************
static void Interrupt_clearIFR(uint16_t group)
{
    switch (group)
    {
        case 0x0001U:
            IFR &= ~(uint16_t)0x0001U;
            break;
        case 0x0002U:
            IFR &= ~(uint16_t)0x0002U;
            break;
        case 0x0004U:
            IFR &= ~(uint16_t)0x0004U;
            break;
        case 0x0008U:
            IFR &= ~(uint16_t)0x0008U;
            break;
        case 0x0010U:
            IFR &= ~(uint16_t)0x0010U;
            break;
        case 0x0020U:
            IFR &= ~(uint16_t)0x0020U;
            break;
        case 0x0040U:
            IFR &= ~(uint16_t)0x0040U;
            break;
        case 0x0080U:
            IFR &= ~(uint16_t)0x0080U;
            break;
        case 0x0100U:
            IFR &= ~(uint16_t)0x0100U;
            break;
        case 0x0200U:
            IFR &= ~(uint16_t)0x0200U;
            break;
        case 0x0400U:
            IFR &= ~(uint16_t)0x0400U;
            break;
        case 0x0800U:
            IFR &= ~(uint16_t)0x0800U;
            break;
        case 0x1000U:
            IFR &= ~(uint16_t)0x1000U;
            break;
        case 0x2000U:
            IFR &= ~(uint16_t)0x2000U;
            break;
        case 0x4000U:
            IFR &= ~(uint16_t)0x4000U;
            break;
        case 0x8000U:
            IFR &= ~(uint16_t)0x8000U;
            break;
        default:
            //
            // Invalid group mask.
            //
            ASSERT((bool)false);
            break;
    }
}

//*****************************************************************************
//
// Interrupt_initModule
//
//*****************************************************************************
void Interrupt_initModule(void)
{
    //
    // Disable and clear all interrupts at the CPU
    //
    DINT;
    IER = 0x0000U;
    IFR = 0x0000U;

    //
    // Clear all PIEIER registers
    //
    HWREGH(PIECTRL_BASE + PIE_O_IER)   = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER1)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER2)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER3)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER4)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER5)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER6)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER7)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER8)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER9)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER10) = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER11) = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IER12) = 0U;

    //
    // Clear all PIEIFR registers
    //
    HWREGH(PIECTRL_BASE + PIE_O_IFR1)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR2)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR3)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR4)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR5)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR6)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR7)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR8)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR9)  = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR10) = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR11) = 0U;
    HWREGH(PIECTRL_BASE + PIE_O_IFR12) = 0U;

    EINT;
}

//*****************************************************************************
//
//! The default interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
__interrupt void Interrupt_defaultHandler(void)
{
    //
    // Something has gone wrong. An interrupt without a proper registered
    // handler function has occurred. To help you debug the issue, local
    // variable vectID contains the vector ID of the interrupt that occurred.
    //
    ESTOP0;
    for (;;)
    {
        ;
    }
}

//*****************************************************************************
//
//! The default illegal instruction trap interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
__interrupt void Interrupt_illegalOperationHandler(void)
{
    //
    // Something has gone wrong.  The CPU has tried to execute an illegal
    // instruction, generating an illegal instruction trap (ITRAP).
    //
    ESTOP0;
    for (;;)
    {
        ;
    }
}

//*****************************************************************************
//
//! The default non-maskable interrupt handler.
//!
//! \return None.
//
//*****************************************************************************
__interrupt void Interrupt_nmiHandler(void)
{
    //
    // A non-maskable interrupt has occurred, indicating that a hardware error
    // has occurred in the system.  You can use SysCtl_getNMIFlagStatus() to
    // to read the NMIFLG register and determine what caused the NMI.
    //
    ESTOP0;
    for (;;)
    {
        ;
    }
}

//*****************************************************************************
//
// Interrupt_initVectorTable
//
//*****************************************************************************
void Interrupt_initVectorTable(void)
{
    //
    // We set all entries to default, although, some of them are not connected to interrupt sources
    //
    for (int i = 0; i < 256; ++i)
    {
        HWREG((Uint32)(&PIEVECTTABLE_BASE) + (i << 2)) = (Uint32)(&Interrupt_defaultHandler);
    }
}

//*****************************************************************************
//
// Interrupt_enable
//
//*****************************************************************************
void Interrupt_enable(uint32_t interruptNumber)
{
    int intGroup;

    intGroup = ((interruptNumber & 0xFF00) >> 8) - 1;

    if (intGroup < 12)
        HWREGH((PIECTRL_BASE + PIE_O_IER1 + (intGroup * 8)))
            |= (1 << ((interruptNumber & 0xFF) - 1));

    HWREGH(PIECTRL_BASE + PIE_O_IER) |= (1 << intGroup);
}

//*****************************************************************************
//
// Interrupt_disable
//
//*****************************************************************************
void Interrupt_disable(uint32_t interruptNumber)
{
    int intGroup;

    intGroup = ((interruptNumber & 0xFF00) >> 8) - 1;

    if (intGroup < 12)
        HWREGH((PIECTRL_BASE + PIE_O_IER1 + (intGroup * 8)))
            &= ~(1 << ((interruptNumber & 0xFF) - 1));

    HWREGH(PIECTRL_BASE + PIE_O_IER) &= ~(1 << intGroup);
}
