#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

//
// Included Files
//
#include "driverlib.h"

//*****************************************************************************
//
// Defines for pin numbers and other GPIO configuration
//
//*****************************************************************************
//*****************************************************************************
//
// Defines related to clock configuration
//
//*****************************************************************************
//
// WARNNING:If use internal OSC1/OSC2 clock, here need change to 10000000U (mean 10Mhz clock)
// WARNNING:If use external X1 clock, here need change to X1 clock frequency (X1 clock need in 8 ~
// 16Mhz)
#define DEVICE_OSCSRC_FREQ 10000000U

#define IMULT_VAL       40 // WARNNING: DEVICE_OSCSRC_FREQ * IMULT_VAL must >= 40 & <= 63
#define ODIV_VAL        4 // WARNNING: ODIV_VAL must >= 0 & <=15, ODIV is 0=1, 1=1, ..., 15=15 div
#define LSPCLK_PRESCALE SYSCTL_LSPCLK_PRESCALE_1

//
// Define to pass to SysCtl_setClock(). Will configure the clock as follows:
// PLLSYSCLK = (XTAL/OSC1/OSC2 CLK) * IMULT_VAL / IDIV / ODIV_VAL / SYSDIV
//
#define DEVICE_SETCLOCK_CFG                                                                \
    (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(IMULT_VAL) | SYSCTL_IDIV(1) | SYSCTL_ODIV(ODIV_VAL) \
        | SYSCTL_SYSDIV(1) | SYSCTL_PLL_ENABLE)

//
// SYSCLK frequency based on the above DEVICE_SETCLOCK_CFG. Update the
// code below if a different clock configuration is used!
//
#define DEVICE_SYSCLK_FREQ (((DEVICE_OSCSRC_FREQ * IMULT_VAL / 1) / ODIV_VAL) / 1)

//
// LSPCLK frequency based on the above DEVICE_SYSCLK_FREQ and LSPCLK_PRESCALE
//
#define LSPCLK_PRESCALE_VAL \
    ((LSPCLK_PRESCALE == SYSCTL_LSPCLK_PRESCALE_1) ? 1 : (LSPCLK_PRESCALE * 2))
#define DEVICE_LSPCLK_FREQ (DEVICE_SYSCLK_FREQ / LSPCLK_PRESCALE_VAL)

//*****************************************************************************
//
// Macro to call SysCtl_delay() to achieve a delay in microseconds. The macro
// will convert the desired delay in microseconds to the count value expected
// by the function. \b x is the number of microseconds to delay.
//
// The loop in qx_precise_delay takes 8 cycles per iteration plus 8 cycles of
// overhead (5 cycles of passing argument and executing call, and 3 cycles of
// function return).
//
//*****************************************************************************
#define DEVICE_DELAY_US(x) \
    qx_precise_delay(      \
        ((((long double)(x)) / (1000000.0L / (long double)DEVICE_SYSCLK_FREQ)) - 8.0L) / 8.0L)

//*****************************************************************************
//  Defines for setting FSI clock speeds in normal FSI mode (SPI_MODE == 0)
//*****************************************************************************
//
//  TXCLKIN = INPUT_CLOCK / PRESCALE_VAL
//  TXCLK (in FSI mode) = TXCLKIN / 2
//  TXCLK (in SPI mode) = TXCLKIN
//
//  Below assumes INPUT_CLOCK == 200 MHz (PLLRAWCLK, SEL_PLLCLK == 1)
//
#define FSI_PRESCALE_50MHZ 2U
#define FSI_PRESCALE_25MHZ 4U
#define FSI_PRESCALE_10MHZ 10U
#define FSI_PRESCALE_5MHZ  20U

//*****************************************************************************
//
// Function Prototypes
//
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//
//! \addtogroup device_api
//! @{
//
//***
//*****************************************************************************
//
//! @brief Function to initialize the device. Primarily initializes system control to a
//! known state by disabling the watchdog, setting up the SYSCLKOUT frequency,
//! and enabling the clocks to the peripherals.
//! The function also configures the GPIO pins 22 and 23 in digital mode.
//! To configure these pins as analog pins, use the function GPIO_setAnalogMode
//!
//! \return None
//
//*****************************************************************************
extern void Device_init(void);

//*****************************************************************************
//
//!
//! @brief Function to verify the XTAL frequency
//! \param freq is the XTAL frequency in MHz
//! \return The function return true if the the actual XTAL frequency matches with the
//! input value
//
//*****************************************************************************
extern bool Device_verifyXTAL(float freq);

//*****************************************************************************
//!
//!
//! @brief Function to turn on all peripherals, enabling reads and writes to the
//! peripherals' registers.
//!
//! Note that to reduce power, unused peripherals should be disabled.
//!
//! \return None
//
//*****************************************************************************
extern void Device_enableAllPeripherals(void);

//*****************************************************************************
//!
//!
//! @brief Function to disable pin locks and enable pullups on GPIOs.
//!
//! \return None
//
//*****************************************************************************
extern void Device_initGPIO(void);

//*****************************************************************************
//!
//! @brief Error handling function to be called when an ASSERT is violated
//!
//! \param *filename File name in which the error has occurred
//! \param line Line number within the file
//! \return None
//
//*****************************************************************************
extern void __error__(const char *filename, uint32_t line);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif // __DEVICE_H__
