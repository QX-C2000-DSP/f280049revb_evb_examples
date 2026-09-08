#ifndef F28004X_DEVICE_H
#define F28004X_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Define to enable interrupts
//
#ifndef EINT
#define EINT                                                         \
    do                                                               \
    {                                                                \
        __asm__ volatile("nop||\n nop||\n jmp 2||\n nop||\n nop||"); \
        ExpRegs.INTM = 0;                                            \
    } while (0)
#endif

//
// Define to disable interrupts
//
#ifndef DINT
#define DINT __asm volatile("SETCINTM||")
#endif

//
// Define to enable debug events
//
#ifndef ERTM
#define ERTM // __asm(" clrc DBGM")
#endif

//
// Define to disable debug events
//
#ifndef DRTM
#define DRTM // __asm(" setc DBGM")
#endif

//
// Define to allow writes to protected registers
//
#ifndef EALLOW
#define EALLOW __asm("EALLOW||")
#endif

//
// Define to disable writes to protected registers
//
#ifndef EDIS
#define EDIS __asm("EDIS||")
#endif

//
// Define for emulation stop
//
#ifndef ESTOP0
#define ESTOP0 // __asm(" ESTOP0")
#endif

//
// Define for emulation stop
//
#ifndef ESTOP1
#define ESTOP1 // __asm(" ESTOP1")
#endif

//
// Define for no operation
//
#ifndef NOP
#define NOP __asm("NOP||")
#endif

//
// Define for putting processor into a low-power mode
//
#ifndef IDLE
#define IDLE __asm("IDLE||")
#endif

//
// Define for data area that will be hold during reset
//
#ifndef __noinit_data
#define __noinit_data __attribute__((section(".noinit_data")))
#endif

// clang-format off
//
// Define for helper symbols specifying range of XINTF data and text
//
#ifndef __QX_XINTF_ZONE_START
#define __QX_XINTF_ZONE_START _Pragma("clang section text=\".xintf_text\" rodata=\".xintf_rodata\" data=\".xintf_data\" bss=\".xintf_bss\"")
#endif

#ifndef __QX_XINTF_ZONE_END
#define __QX_XINTF_ZONE_END _Pragma("clang section text=\"\" rodata=\"\" data=\"\" bss=\"\"")
#endif
// clang-format on

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0  0x00000001
#define BIT1  0x00000002
#define BIT2  0x00000004
#define BIT3  0x00000008
#define BIT4  0x00000010
#define BIT5  0x00000020
#define BIT6  0x00000040
#define BIT7  0x00000080
#define BIT8  0x00000100
#define BIT9  0x00000200
#define BIT10 0x00000400
#define BIT11 0x00000800
#define BIT12 0x00001000
#define BIT13 0x00002000
#define BIT14 0x00004000
#define BIT15 0x00008000
#define BIT16 0x00010000
#define BIT17 0x00020000
#define BIT18 0x00040000
#define BIT19 0x00080000
#define BIT20 0x00100000
#define BIT21 0x00200000
#define BIT22 0x00400000
#define BIT23 0x00800000
#define BIT24 0x01000000
#define BIT25 0x02000000
#define BIT26 0x04000000
#define BIT27 0x08000000
#define BIT28 0x10000000
#define BIT29 0x20000000
#define BIT30 0x40000000
#define BIT31 0x80000000

//
// For Portability, User Is Recommended To Use the C99 Standard integer types
//
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//
// C++ Bool Compatibility
//
#if defined(__cplusplus)
typedef bool _Bool;
#endif

//
// C99 defines boolean type to be _Bool, but this doesn't match the format of
// the other standard integer types.  bool_t has been defined to fill this gap.
//
typedef _Bool bool_t;

//
// Used for a bool function return status
//
typedef _Bool status_t;

#ifndef SUCCESS
#define SUCCESS true
#endif

#ifndef FAIL
#define FAIL false
#endif

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;
typedef unsigned long long Uint64;
typedef float float32;
typedef long double float64;

typedef unsigned short bp_16;
typedef unsigned int bp_32;

#ifndef __interrupt
#define __interrupt __attribute__((interrupt)) __attribute__((section(".text.interrupt.routine")))
#endif

//
// Include All Peripheral Header Files:
//
#include "f28004x_adc.h"
#include "f28004x_analogsubsys.h"
#include "f28004x_cmpss.h"
#include "f28004x_cputimer.h"
#include "f28004x_dac.h"
#include "f28004x_dcsm.h"
#include "f28004x_dma.h"
#include "f28004x_ecap.h"
#include "f28004x_epwm.h"
#include "f28004x_epwm_xbar.h"
#include "f28004x_eqep.h"
#include "f28004x_erad.h"
#include "f28004x_flash.h"
#include "f28004x_fsi.h"
#include "f28004x_gpio.h"
#include "f28004x_i2c.h"
#include "f28004x_input_xbar.h"
#include "f28004x_nmiintrupt.h"
#include "f28004x_output_xbar.h"
#include "f28004x_pga.h"
#include "f28004x_piectrl.h"
#include "f28004x_pievect.h"
#include "f28004x_pmbus.h"
#include "f28004x_sci.h"
#include "f28004x_sdfm.h"
#include "f28004x_spi.h"
#include "f28004x_sysctrl.h"
#include "f28004x_xbar.h"
#include "f28004x_xint.h"
#include "f28004x_can.h"
#include "f28004x_dcc.h"
#include "f28004x_lin.h"
#include "f28004x_ipc.h"
#include "f28004x_tracebuffer.h"
#include "f28004x_watchpoint.h"
#include "f28004x_hr_adc.h"
#include "f28004x_xintf.h"

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // end of F28004X_DEVICE_H definition

//===========================================================================
// End of file.
//===========================================================================
