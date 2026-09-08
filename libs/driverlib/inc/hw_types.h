#ifndef HW_TYPES_H
#define HW_TYPES_H

//*****************************************************************************
//
// Macros for hardware access
//
//*****************************************************************************
#define HWREG(x)  (*((volatile uint32_t *)(x)))
#define HWREGH(x) (*((volatile uint16_t *)(x)))
#define HWREGB(x) (*((volatile uint8_t *)(x)))

//*****************************************************************************
//
// SUCCESS and FAILURE for API return value
//
//*****************************************************************************
#define STATUS_S_SUCCESS (0)
#define STATUS_E_FAILURE (-1)

//****************************************************************************
//
// For checking NULL pointers
//
//****************************************************************************
#ifndef NULL
#define NULL ((void *)0x0)
#endif

//
// C++ Bool Compatibility
//
#if defined(__cplusplus)
typedef bool _Bool;
#endif

/* To fix Misra-C errors */
#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef float float32_t;
typedef double float64_t;

typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned long long vu64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/* simulation of __byte() Intrinsic, refer to SPRU514Z, table 7-6 */
static inline uint16_t __byte(int16_t *array, uint16_t byte_index)
{
    return ((uint8_t *)array)[byte_index];
}

#endif // HW_TYPES_H
