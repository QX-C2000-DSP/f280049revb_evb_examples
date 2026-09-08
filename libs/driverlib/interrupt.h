#ifndef INTERRUPT_H
#define INTERRUPT_H

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
//! \addtogroup interrupt_api Interrupt
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_pie.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#include "f28004x_device.h"

#ifndef DOXYGEN_PDF_IGNORE

//*****************************************************************************
// IER  BIT Numbers define
//*****************************************************************************

#define PIC_GROUP1  0x0001
#define PIC_GROUP2  0x0002
#define PIC_GROUP3  0x0004
#define PIC_GROUP4  0x0008
#define PIC_GROUP5  0x0010
#define PIC_GROUP6  0x0020
#define PIC_GROUP7  0x0040
#define PIC_GROUP8  0x0080
#define PIC_GROUP9  0x0100
#define PIC_GROUP10 0x0200
#define PIC_GROUP11 0x0400
#define PIC_GROUP12 0x0800
#define PIC_TIMER1  0x1000
#define PIC_TIMER2  0x2000

//*****************************************************************************
// PIEIER  BIT Numbers define
//*****************************************************************************

// Lower PIE Group 1
#define PIE_BIT_RTOS     0x0001 // 1.1 - RTOS Interrupt
#define PIE_BIT_TRACE    0x0002 // 1.2 - Debug Trace Interrupt
#define PIE_BIT_WP       0x0004 // 1.3 - Debug WatchPoint Interrupt
#define PIE_BIT_ADCA1    0x0008 // 1.4 - ADCA Interrupt 1
#define PIE_BIT_ADCB1    0x0010 // 1.5 - ADCB Interrupt 1
#define PIE_BIT_ADCC1    0x0020 // 1.6 - ADCC Interrupt 1
#define PIE_BIT_XINT1    0x0040 // 1.7 - XINT1 Interrupt
#define PIE_BIT_XINT2    0x0080 // 1.8 - XINT2 Interrupt
#define PIE_BIT_TIMER0   0x0200 // 1.10 - Timer 0 Interrupt
#define PIE_BIT_WAKE     0x0400 // 1.11 - Halt Wakeup/Watchdog Interrupt
#define PIE_BIT_ADCA1_HR 0x2000 // 1.14 - ADCA_HR Interrupt 1
#define PIE_BIT_ADCB1_HR 0x4000 // 1.15 - ADCB_HR Interrupt 1
#define PIE_BIT_ADCC1_HR 0x8000 // 1.16 - ADCC_HR Interrupt 1

// Lower PIE Group 2
#define PIE_BIT_EPWM1_TZ  0x0001 // 2.1 - ePWM1 Trip Zone Interrupt
#define PIE_BIT_EPWM2_TZ  0x0002 // 2.2 - ePWM2 Trip Zone Interrupt
#define PIE_BIT_EPWM3_TZ  0x0004 // 2.3 - ePWM3 Trip Zone Interrupt
#define PIE_BIT_EPWM4_TZ  0x0008 // 2.4 - ePWM4 Trip Zone Interrupt
#define PIE_BIT_EPWM5_TZ  0x0010 // 2.5 - ePWM5 Trip Zone Interrupt
#define PIE_BIT_EPWM6_TZ  0x0020 // 2.6 - ePWM6 Trip Zone Interrupt
#define PIE_BIT_EPWM7_TZ  0x0040 // 2.7 - ePWM7 Trip Zone Interrupt
#define PIE_BIT_EPWM8_TZ  0x0080 // 2.8 - ePWM8 Trip Zone Interrupt
#define PIE_BIT_EPWM9_TZ  0x0100 // 2.9 - ePWM9 Trip Zone Interrupt
#define PIE_BIT_EPWM10_TZ 0x0200 // 2.10 - ePWM10 Trip Zone Interrupt
#define PIE_BIT_EPWM11_TZ 0x0400 // 2.11 - ePWM11 Trip Zone Interrupt
#define PIE_BIT_EPWM12_TZ 0x0800 // 2.12 - ePWM12 Trip Zone Interrupt

// Lower PIE Group 3
#define PIE_BIT_EPWM1  0x0001 // 3.1 - ePWM1 Interrupt
#define PIE_BIT_EPWM2  0x0002 // 3.2 - ePWM2 Interrupt
#define PIE_BIT_EPWM3  0x0004 // 3.3 - ePWM3 Interrupt
#define PIE_BIT_EPWM4  0x0008 // 3.4 - ePWM4 Interrupt
#define PIE_BIT_EPWM5  0x0010 // 3.5 - ePWM5 Interrupt
#define PIE_BIT_EPWM6  0x0020 // 3.6 - ePWM6 Interrupt
#define PIE_BIT_EPWM7  0x0040 // 3.7 - ePWM7 Interrupt
#define PIE_BIT_EPWM8  0x0080 // 3.8 - ePWM8 Interrupt
#define PIE_BIT_EPWM9  0x0100 // 3.9 - ePWM9 Interrupt
#define PIE_BIT_EPWM10 0x0200 // 3.10 - ePWM10 Interrupt
#define PIE_BIT_EPWM11 0x0400 // 3.11 - ePWM11 Interrupt
#define PIE_BIT_EPWM12 0x0800 // 3.12 - ePWM12 Interrupt

// Lower PIE Group 4
#define PIE_BIT_ECAP1   0x0001 // 4.1 - eCAP1 Interrupt
#define PIE_BIT_ECAP2   0x0002 // 4.2 - eCAP2 Interrupt
#define PIE_BIT_ECAP3   0x0004 // 4.3 - eCAP3 Interrupt
#define PIE_BIT_ECAP4   0x0008 // 4.4 - eCAP4 Interrupt
#define PIE_BIT_ECAP5   0x0010 // 4.5 - eCAP5 Interrupt
#define PIE_BIT_ECAP6   0x0020 // 4.6 - eCAP6 Interrupt
#define PIE_BIT_ECAP7   0x0040 // 4.7 - eCAP7 Interrupt
#define PIE_BIT_ECAP6_2 0x2000 // 4.14 - eCAP6_2 (HRCAL) Interrupt
#define PIE_BIT_ECAP7_2 0x4000 // 4.15 - eCAP7_2 (HRCAL) Interrupt

// Lower PIE Group 5
#define PIE_BIT_EQEP1    0x0001 // 5.1 - eQEP1 Interrupt
#define PIE_BIT_EQEP2    0x0002 // 5.2 - eQEP2 Interrupt
#define PIE_BIT_SDFM1    0x0100 // 5.9 - SDFM1 Interrupt
#define PIE_BIT_SDFM1DR1 0x1000 // 5.13 - SDFM1DR1 Interrupt
#define PIE_BIT_SDFM1DR2 0x2000 // 5.14 - SDFM1DR2 Interrupt
#define PIE_BIT_SDFM1DR3 0x4000 // 5.15 - SDFM1DR3 Interrupt
#define PIE_BIT_SDFM1DR4 0x8000 // 5.16 - SDFM1DR4 Interrupt

// Lower PIE Group 6
#define PIE_BIT_SPIA_RX 0x0001 // 6.1 - SPIA Receive Interrupt
#define PIE_BIT_SPIA_TX 0x0002 // 6.2 - SPIA Transmit Interrupt
#define PIE_BIT_SPIB_RX 0x0004 // 6.3 - SPIB Receive Interrupt
#define PIE_BIT_SPIB_TX 0x0008 // 6.4 - SPIB Transmit Interrupt

// Lower PIE Group 7
#define PIE_BIT_DMA_CH1     0x0001 // 7.1 - DMA Channel 1 Interrupt
#define PIE_BIT_DMA_CH2     0x0002 // 7.2 - DMA Channel 2 Interrupt
#define PIE_BIT_DMA_CH3     0x0004 // 7.3 - DMA Channel 3 Interrupt
#define PIE_BIT_DMA_CH4     0x0008 // 7.4 - DMA Channel 4 Interrupt
#define PIE_BIT_DMA_CH5     0x0010 // 7.5 - DMA Channel 5 Interrupt
#define PIE_BIT_DMA_CH6     0x0020 // 7.6 - DMA Channel 6 Interrupt
#define PIE_BIT_FSITXA_INT1 0x0400 // 7.11 - FSITXA_INT1 Interrupt
#define PIE_BIT_FSITXA_INT2 0x0800 // 7.12 - FSITXA_INT2 Interrupt
#define PIE_BIT_FSIRXA_INT1 0x1000 // 7.13 - FSIRXA_INT1 Interrupt
#define PIE_BIT_FSIRXA_INT2 0x2000 // 7.14 - FSIRXA_INT2 Interrupt
#define PIE_BIT_DCC         0x8000 // 7.16 - DCC Interrupt

// Lower PIE Group 8
#define PIE_BIT_I2CA   0x0001 // 8.1 - I2CA Interrupt 1
#define PIE_BIT_LINA   0x0100 // 8.9 - LINA Interrupt0
#define PIE_BIT_PMBUSA 0x1000 // 8.13 - PMBUSA Interrupt

// Lower PIE Group 9
#define PIE_BIT_SCIA 0x0001 // 9.1 - SCIA Interrupt
#define PIE_BIT_SCIB 0x0002 // 9.2 - SCIB Interrupt
#define PIE_BIT_CANA 0x0010 // 9.5 - CANA Interrupt
#define PIE_BIT_CANB 0x0020 // 9.6 - CANB Interrupt

// Lower PIE Group 10
#define PIE_BIT_ADCA_EVT 0x0001 // 10.1 - ADCA Event Interrupt
#define PIE_BIT_ADCA2    0x0002 // 10.2 - ADCA Interrupt 2
#define PIE_BIT_ADCA3    0x0004 // 10.3 - ADCA Interrupt 3
#define PIE_BIT_ADCA4    0x0008 // 10.4 - ADCA Interrupt 4
#define PIE_BIT_ADCB_EVT 0x0010 // 10.5 - ADCB Event Interrupt
#define PIE_BIT_ADCB2    0x0020 // 10.6 - ADCB Interrupt 2
#define PIE_BIT_ADCB3    0x0040 // 10.7 - ADCB Interrupt 3
#define PIE_BIT_ADCB4    0x0080 // 10.8 - ADCB Interrupt 4
#define PIE_BIT_ADCC_EVT 0x0100 // 10.9 - ADCC Event Interrupt
#define PIE_BIT_ADCC2    0x0200 // 10.10 - ADCC Interrupt 2
#define PIE_BIT_ADCC3    0x0400 // 10.11 - ADCC Interrupt 3
#define PIE_BIT_ADCC4    0x0800 // 10.12 - ADCC Interrupt 4

// Lower PIE Group 11
#define PIE_BIT_IPC0 0x0001 // 11.1 - IPC interrupts0
#define PIE_BIT_IPC1 0x0002 // 11.2 - IPC interrupts1
#define PIE_BIT_IPC2 0x0004 // 11.3 - IPC interrupts2
#define PIE_BIT_IPC3 0x0008 // 11.4 - IPC interrupts3

// Lower PIE Group 12
#define PIE_BIT_XINT3   0x0001 // 12.1 - XINT3 Interrupt
#define PIE_BIT_XINT4   0x0002 // 12.2 - XINT4 Interrupt
#define PIE_BIT_XINT5   0x0004 // 12.3 - XINT5 Interrupt
#define PIE_BIT_XINTF   0x0008 // 12.4 - XINTF Interrupt
#define ADCA_HR_EVT_INT 0x0010 // 12.5 - HR ADCA Event Interrupt
#define ADCA2_HR_INT    0x0020 // 12.6 - HR ADCA Interrupt 2
#define ADCA3_HR_INT    0x0040 // 12.7 - HR ADCA Interrupt 3
#define ADCA4_HR_INT    0x0080 // 12.8 - HR ADCA Interrupt 4
#define ADCB_HR_EVT_INT 0x0100 // 12.9 - HR ADCB Event Interrupt
#define ADCB2_HR_INT    0x0200 // 12.10  - HR ADCB Interrupt 2
#define ADCB3_HR_INT    0x0400 // 12.11 - HR ADCB Interrupt 3
#define ADCB4_HR_INT    0x0800 // 12.12 - HR ADCB Interrupt 4
#define ADCC_HR_EVT_INT 0x1000 // 12.13 - HR ADCC Event Interrupt
#define ADCC2_HR_INT    0x2000 // 12.14 - HR ADCC Interrupt 2
#define ADCC3_HR_INT    0x4000 // 12.15 - HR ADCC Interrupt 3
#define ADCC4_HR_INT    0x8000 // 12.16 - HR ADCC Interrupt 4

// for compatable
//*****************************************************************************
//
// The following are values that can be passed to the Interrupt_enableInCPU()
// and Interrupt_disableInCPU() functions as the cpuInterrupt parameter.
//
//*****************************************************************************
#define INTERRUPT_CPU_INT1    0x1U    //!< CPU Interrupt Number 1
#define INTERRUPT_CPU_INT2    0x2U    //!< CPU Interrupt Number 2
#define INTERRUPT_CPU_INT3    0x4U    //!< CPU Interrupt Number 3
#define INTERRUPT_CPU_INT4    0x8U    //!< CPU Interrupt Number 4
#define INTERRUPT_CPU_INT5    0x10U   //!< CPU Interrupt Number 5
#define INTERRUPT_CPU_INT6    0x20U   //!< CPU Interrupt Number 6
#define INTERRUPT_CPU_INT7    0x40U   //!< CPU Interrupt Number 7
#define INTERRUPT_CPU_INT8    0x80U   //!< CPU Interrupt Number 8
#define INTERRUPT_CPU_INT9    0x100U  //!< CPU Interrupt Number 9
#define INTERRUPT_CPU_INT10   0x200U  //!< CPU Interrupt Number 10
#define INTERRUPT_CPU_INT11   0x400U  //!< CPU Interrupt Number 11
#define INTERRUPT_CPU_INT12   0x800U  //!< CPU Interrupt Number 12
#define INTERRUPT_CPU_INT13   0x1000U //!< CPU Interrupt Number 13
#define INTERRUPT_CPU_INT14   0x2000U //!< CPU Interrupt Number 14
#define INTERRUPT_CPU_DLOGINT 0x4000U //!< CPU Data Log Interrupt
#define INTERRUPT_CPU_RTOSINT 0x8000U //!< CPU RTOS Interrupt

// for compatable
//*****************************************************************************
//
// The following are values that can be passed to the Interrupt_clearACKGroup()
// function as the group parameter.
//
//*****************************************************************************
#define INTERRUPT_ACK_GROUP1  0x1U   //!< Acknowledge PIE Interrupt Group 1
#define INTERRUPT_ACK_GROUP2  0x2U   //!< Acknowledge PIE Interrupt Group 2
#define INTERRUPT_ACK_GROUP3  0x4U   //!< Acknowledge PIE Interrupt Group 3
#define INTERRUPT_ACK_GROUP4  0x8U   //!< Acknowledge PIE Interrupt Group 4
#define INTERRUPT_ACK_GROUP5  0x10U  //!< Acknowledge PIE Interrupt Group 5
#define INTERRUPT_ACK_GROUP6  0x20U  //!< Acknowledge PIE Interrupt Group 6
#define INTERRUPT_ACK_GROUP7  0x40U  //!< Acknowledge PIE Interrupt Group 7
#define INTERRUPT_ACK_GROUP8  0x80U  //!< Acknowledge PIE Interrupt Group 8
#define INTERRUPT_ACK_GROUP9  0x100U //!< Acknowledge PIE Interrupt Group 9
#define INTERRUPT_ACK_GROUP10 0x200U //!< Acknowledge PIE Interrupt Group 10
#define INTERRUPT_ACK_GROUP11 0x400U //!< Acknowledge PIE Interrupt Group 11
#define INTERRUPT_ACK_GROUP12 0x800U //!< Acknowledge PIE Interrupt Group 12
#endif

extern uint32_t PIEVECTTABLE_BASE;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! The default interrupt handler.
//!
//! This is the default interrupt handler.  The Interrupt_initVectorTable()
//! function sets all vectors to this function.  Also, when an interrupt is
//! unregistered using the Interrupt_unregister() function, this handler takes
//! its place.  This should never be called during normal operation.
//!
//! The ESTOP0 statement is for debug purposes only. Remove and replace with an
//! appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
extern void Interrupt_defaultHandler(void);

//*****************************************************************************
//
//! \internal
//! The default illegal instruction trap interrupt handler.
//!
//! This is the default interrupt handler for an illegal instruction trap
//! (ITRAP).  The Interrupt_initVectorTable() function sets the appropriate
//! vector to this function.  This should never be called during normal
//! operation.
//!
//! The ESTOP0 statement is for debug purposes only.  Remove and replace with
//! an appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
extern void Interrupt_illegalOperationHandler(void);

//*****************************************************************************
//
//! \internal
//! The default non-maskable interrupt handler.
//!
//! This is the default interrupt handler for a non-maskable interrupt (NMI).
//! The Interrupt_initVectorTable() function sets the appropriate vector to
//! this function.  This should never be called during normal operation.
//!
//! The ESTOP0 statement is for debug purposes only. Remove and replace with an
//! appropriate error handling routine for your program.
//!
//! \return None.
//
//*****************************************************************************
extern void Interrupt_nmiHandler(void);

//*****************************************************************************
//
//! Allows the CPU to process interrupts.
//!
//! This function clears the global interrupt mask bit (INTM) in the CPU,
//! allowing the processor to respond to interrupts.
//!
//! \return Returns \b true if interrupts were disabled when the function was
//! called or \b false if they were initially enabled.
//
//*****************************************************************************
static inline bool Interrupt_enableGlobal(void)
{
    //
    // Enable processor interrupts.
    //
    bool val     = ExpRegs.INTM;
    ExpRegs.INTM = 0;
    return val ? true : false;
}

//*****************************************************************************
//
//! Stops the CPU from processing interrupts.
//!
//! This function sets the global interrupt mask bit (INTM) in the CPU,
//! preventing the processor from receiving maskable interrupts.
//!
//! \return Returns \b true if interrupts were already disabled when the
//! function was called or \b false if they were initially enabled.
//
//*****************************************************************************
static inline bool Interrupt_disableGlobal(void)
{
    //
    // Disable processor interrupts.
    //
    bool val     = ExpRegs.INTM;
    ExpRegs.INTM = 1;
    return val ? true : false;
}

//*****************************************************************************
//
//! Registers a function to be called when an interrupt occurs.
//!
//! \param interruptNumber specifies the interrupt in question.
//! \param handler is a pointer to the function to be called.
//!
//! This function is used to specify the handler function to be called when the
//! given interrupt is asserted to the processor.  When the interrupt occurs,
//! if it is enabled (via Interrupt_enable()), the handler function will be
//! called in interrupt context.  Since the handler function can preempt other
//! code, care must be taken to protect memory or peripherals that are accessed
//! by the handler and other non-handler code.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \note This function assumes that the PIE has been enabled. See
//! Interrupt_initModule().
//!
//! \return None.
//
//*****************************************************************************
static inline void Interrupt_register(uint32_t interruptNumber, void (*handler)(void))
{
    Uint32 tableindex, address;

    //
    // tableindex = interruptNumber[15:8] * 16 + interruptNumber[7:0] - 1
    //
    tableindex = (((interruptNumber >> 8) & 0xFF) << 4) + ((interruptNumber & 0xFF) - 1);
    address    = (Uint32)(&PIEVECTTABLE_BASE) + (tableindex << 2);

    //
    // Copy ISR address into PIE table
    //
    EALLOW;
    HWREG(address) = (uint32_t)handler;
    EDIS;
}

//*****************************************************************************
//
//! Unregisters the function to be called when an interrupt occurs.
//!
//! \param interruptNumber specifies the interrupt in question.
//!
//! This function is used to indicate that a default handler
//! Interrupt_defaultHandler() should be called when the given interrupt is
//! asserted to the processor.  Call Interrupt_disable() to disable
//! the interrupt before calling this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \sa Interrupt_register() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void Interrupt_unregister(uint32_t interruptNumber)
{
    Uint32 tableindex, address;

    //
    // tableindex = interruptNumber[15:8] * 16 + interruptNumber[7:0] - 1
    //
    tableindex = (((interruptNumber >> 8) & 0xFF) << 4) + ((interruptNumber & 0xFF) - 1);
    address    = (Uint32)(&PIEVECTTABLE_BASE) + (tableindex << 2);

    //
    // Copy ISR address into PIE table
    //
    EALLOW;
    HWREG(address) = (Uint32)Interrupt_defaultHandler;
    EDIS;
}

//*****************************************************************************
//

//*****************************************************************************
//
//! Acknowledges PIE Interrupt Group
//!
//! \param group specifies the interrupt group to be acknowledged.
//!
//! The specified interrupt group is acknowledged and clears any interrupt
//! flag within that respective group.
//!
//! The \e group parameter must be a logical OR of the following:
//! \b INTERRUPT_ACK_GROUP1, \b INTERRUPT_ACK_GROUP2, \b INTERRUPT_ACK_GROUP3
//! \b INTERRUPT_ACK_GROUP4, \b INTERRUPT_ACK_GROUP5, \b INTERRUPT_ACK_GROUP6
//! \b INTERRUPT_ACK_GROUP7, \b INTERRUPT_ACK_GROUP8, \b INTERRUPT_ACK_GROUP9
//! \b INTERRUPT_ACK_GROUP10, \b INTERRUPT_ACK_GROUP11,
//! \b INTERRUPT_ACK_GROUP12.
//!
//! \return None.
//
//*****************************************************************************
static inline void Interrupt_clearACKGroup(uint16_t group)
{
    //
    // Set interrupt group acknowledge bits
    //
}

//! Initializes the PIE control registers by setting them to a known state.
//!
//! This function initializes the PIE control registers. After globally
//! disabling interrupts and enabling the PIE, it clears all of the PIE
//! interrupt enable bits and interrupt flags.
//!
//! \return None.
//
//*****************************************************************************
extern void Interrupt_initModule(void);

//*****************************************************************************
//
//! Initializes the PIE vector table by setting all vectors to a default
//! handler function.
//!
//! \return None.
//
//*****************************************************************************
extern void Interrupt_initVectorTable(void);

//*****************************************************************************
//
//! Enables an interrupt.
//!
//! \param interruptNumber specifies the interrupt to be enabled.
//!
//! The specified interrupt is enabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
extern void Interrupt_enable(uint32_t interruptNumber);

//*****************************************************************************
//
//! Disables an interrupt.
//!
//! \param interruptNumber specifies the interrupt to be disabled.
//!
//! The specified interrupt is disabled in the interrupt controller.  Other
//! enables for the interrupt (such as at the peripheral level) are unaffected
//! by this function.
//!
//! The available \e interruptNumber values are supplied in
//! <tt>inc/hw_ints.h</tt>.
//!
//! \return None.
//
//*****************************************************************************
extern void Interrupt_disable(uint32_t interruptNumber);

#ifdef __cplusplus
}
#endif

#endif // INTERRUPT_H
