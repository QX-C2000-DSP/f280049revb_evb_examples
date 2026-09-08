
#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************
//
// GPIO2 - GPIO Settings
//
#define myGPIO0_GPIO_PIN_CONFIG GPIO_2_GPIO2

//
// OTHER -> myOTHER0 Pinmux
//
//
// XCLKOUT - GPIO Settings
//
#define GPIO_PIN_XCLKOUT 16
#define myOTHER0_XCLKOUT_GPIO 16
#define myOTHER0_XCLKOUT_PIN_CONFIG GPIO_16_XCLKOUT

//*****************************************************************************
//
// ECAP Configurations
//
//*****************************************************************************
#define myECAP0_BASE ECAP7_BASE
#define myECAP0_HR_BASE HRCAP7_BASE
#define myECAP0_SIGNAL_MUNIT_BASE ECAP7SIGNALMONITORING_BASE

#define HRCALCAL_STATUS_DONE_ISR    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT )

#define HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR                               \
                                    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT |      \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCALCAL_CALIBRATION_FLAGS  (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCAPCAL_OVERFLOW           4294967295.0f
#define HRCAPCAL_INV_OVERFLOW       (float32_t)(1.0f / HRCAPCAL_OVERFLOW)

typedef struct
{
    uint32_t hrclkCount;    // High resolution clock count
    uint32_t sysclkcount;   // System clock count
    float32_t scaleFactor;  // Scale factor
    bool calDone;           // Calibration done flag
} HRCAPCAL_CalResultObj;

void myECAP0_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define myGPIO0 2
void myGPIO0_init();

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
#define myINPUTXBARINPUT0_SOURCE 2
#define myINPUTXBARINPUT0_INPUT XBAR_INPUT7
void myINPUTXBARINPUT0_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_myECAP0
// ISR need to be defined for the registered interrupts
#define INT_myECAP0 INT_ECAP7
#define INT_myECAP0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP4
extern __interrupt void INT_myECAP0_ISR(void);

// Interrupt Settings for INT_myECAP0_HR
// ISR need to be defined for the registered interrupts
#define INT_myECAP0_HR INT_ECAP7_2
#define INT_myECAP0_HR_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP4
extern __interrupt void INT_myECAP0_HR_ISR(void);

//*****************************************************************************
//
// OTHER Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    ECAP_init();
void    GPIO_init();
void    INPUTXBAR_init();
void    INTERRUPT_init();
void    OTHER_init();
void    SYNC_init();
void    PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
