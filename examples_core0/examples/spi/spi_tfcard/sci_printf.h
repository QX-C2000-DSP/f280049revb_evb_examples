#ifndef QX_COMMON_H
#define QX_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "driverlib.h"
#include "device.h"
#include "string.h"

// 自实现putchar puts和printf函数
void putchar(char c);
void puts(const char *str);
int printf(const char *str, ...);

// 串口打印初始化函数和仿真自动结束函数
void StdOutInit(volatile struct SCI_REGS *sci, int baudrate, uint32_t pin, uint32_t pin_mux);
void EndSimulation(void);

// 一些验证常用的通用函数库封装
void simple_delay(u32 count);
void verify_data_byte(void *buf1, void *buf2, u32 len);
void buf_dump(const char *head, const char *buf, int len);

void chipAutotestCaseStart();
void chipAutotestCaseEnd();

extern void fast_interrupt_initvectortable(Uint32, Uint32);

#ifdef __CORE1__
void tests_core1();
#else
void tests_core0();
#endif

#ifdef __cplusplus
}
#endif

#endif
