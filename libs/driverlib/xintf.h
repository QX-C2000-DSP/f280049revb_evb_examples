#ifndef XINTF_H
#define XINTF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#define ZONE0_BASE 0x20004000U
#define ZONE6_BASE 0x20100000U
#define ZONE7_BASE 0x20300000U

#ifdef __cplusplus
}
#endif

#endif
