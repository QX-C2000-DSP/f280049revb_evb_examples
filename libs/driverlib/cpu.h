#ifndef CPU_H
#define CPU_H

#include "f28004x_device.h"

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __interrupt
#define __interrupt __attribute__((interrupt)) __attribute__((section(".text.interrupt.routine")))
#endif

#ifndef __ipcram_cpu1tocpu2
#define __ipcram_cpu1tocpu2 __attribute__((section("MsgRamCpu1ToCpu2File")))
#endif

#ifndef __ipcram_cpu2tocpu1
#define __ipcram_cpu2tocpu1 __attribute__((section("MsgRamCpu2ToCpu1File")))
#endif

#ifndef CONCAT_SECTION
#define CONCAT_SECTION(sec, num) sec #num
#endif

#ifndef __shared_var_CPU1toCPU2
#define __shared_var_CPU1toCPU2(N) \
    __attribute__((section(CONCAT_SECTION(".shared_var_CPU1toCPU2_sec", N))))
#endif

#ifndef __shared_var_CPU2toCPU1
#define __shared_var_CPU2toCPU1(N) \
    __attribute__((section(CONCAT_SECTION(".shared_var_CPU2toCPU1_sec", N))))
#endif

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // CPU_H
