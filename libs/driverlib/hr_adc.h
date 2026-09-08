#ifndef HR_ADC_H
#define HR_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup hr_adc_api HR_ADC
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_hradc.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"

#include "f28004x_device.h"

//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************

typedef enum
{
    HR_ADC_SAMPLE_WINDOW_1  = 0U,  //!< Set HR_ADC acquisition window duration to 1
    HR_ADC_SAMPLE_WINDOW_2  = 1U,  //!< Set HR_ADC acquisition window duration to 2
    HR_ADC_SAMPLE_WINDOW_3  = 2U,  //!< Set HR_ADC acquisition window duration to 3
    HR_ADC_SAMPLE_WINDOW_4  = 3U,  //!< Set HR_ADC acquisition window duration to 4
    HR_ADC_SAMPLE_WINDOW_5  = 4U,  //!< Set HR_ADC acquisition window duration to 5
    HR_ADC_SAMPLE_WINDOW_6  = 5U,  //!< Set HR_ADC acquisition window duration to 6
    HR_ADC_SAMPLE_WINDOW_7  = 6U,  //!< Set HR_ADC acquisition window duration to 7
    HR_ADC_SAMPLE_WINDOW_8  = 7U,  //!< Set HR_ADC acquisition window duration to 8
    HR_ADC_SAMPLE_WINDOW_10 = 8U,  //!< Set HR_ADC acquisition window duration to 10
    HR_ADC_SAMPLE_WINDOW_20 = 9U,  //!< Set HR_ADC acquisition window duration to 20
    HR_ADC_SAMPLE_WINDOW_30 = 10U, //!< Set HR_ADC acquisition window duration to 30
    HR_ADC_SAMPLE_WINDOW_40 = 11U, //!< Set HR_ADC acquisition window duration to 40
    HR_ADC_SAMPLE_WINDOW_50 = 12U, //!< Set HR_ADC acquisition window duration to 50
    HR_ADC_SAMPLE_WINDOW_60 = 13U, //!< Set HR_ADC acquisition window duration to 60
    HR_ADC_SAMPLE_WINDOW_70 = 14U, //!< Set HR_ADC acquisition window duration to 70
    HR_ADC_SAMPLE_WINDOW_80 = 15U, //!< Set HR_ADC acquisition window duration to 80
} HR_ADC_SampleWindow;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setPrescaler() as the \e clkPrescale
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_CLK_DIV_1_0  = 1U,  //!< HR_ADCCLK = (input clock) / 1.0
    HR_ADC_CLK_DIV_2_0  = 2U,  //!< HR_ADCCLK = (input clock) / 2.0
    HR_ADC_CLK_DIV_3_0  = 3U,  //!< HR_ADCCLK = (input clock) / 3.0
    HR_ADC_CLK_DIV_4_0  = 3U,  //!< HR_ADCCLK = (input clock) / 4.0
    HR_ADC_CLK_DIV_5_0  = 5U,  //!< HR_ADCCLK = (input clock) / 5.0
    HR_ADC_CLK_DIV_6_0  = 4U,  //!< HR_ADCCLK = (input clock) / 6.0
    HR_ADC_CLK_DIV_7_0  = 7U,  //!< HR_ADCCLK = (input clock) / 7.0
    HR_ADC_CLK_DIV_8_0  = 8U,  //!< HR_ADCCLK = (input clock) / 8.0
    HR_ADC_CLK_DIV_9_0  = 9U,  //!< HR_ADCCLK = (input clock) / 9.0
    HR_ADC_CLK_DIV_10_0 = 10U, //!< HR_ADCCLK = (input clock) / 10.0
    HR_ADC_CLK_DIV_11_0 = 11U, //!< HR_ADCCLK = (input clock) / 11.0
    HR_ADC_CLK_DIV_12_0 = 12U, //!< HR_ADCCLK = (input clock) / 12.0
    HR_ADC_CLK_DIV_13_0 = 13U, //!< HR_ADCCLK = (input clock) / 13.0
    HR_ADC_CLK_DIV_14_0 = 14U, //!< HR_ADCCLK = (input clock) / 14.0
    HR_ADC_CLK_DIV_15_0 = 15U, //!< HR_ADCCLK = (input clock) / 15.0
    HR_ADC_CLK_DIV_16_0 = 16U, //!< HR_ADCCLK = (input clock) / 16.0
    HR_ADC_CLK_DIV_17_0 = 17U, //!< HR_ADCCLK = (input clock) / 17.0
    HR_ADC_CLK_DIV_18_0 = 18U, //!< HR_ADCCLK = (input clock) / 18.0
    HR_ADC_CLK_DIV_19_0 = 19U, //!< HR_ADCCLK = (input clock) / 19.0
    HR_ADC_CLK_DIV_20_0 = 20U, //!< HR_ADCCLK = (input clock) / 20.0
    HR_ADC_CLK_DIV_21_0 = 21U, //!< HR_ADCCLK = (input clock) / 21.0
    HR_ADC_CLK_DIV_22_0 = 22U, //!< HR_ADCCLK = (input clock) / 22.0
    HR_ADC_CLK_DIV_23_0 = 23U, //!< HR_ADCCLK = (input clock) / 23.0
    HR_ADC_CLK_DIV_24_0 = 24U, //!< HR_ADCCLK = (input clock) / 24.0
    HR_ADC_CLK_DIV_25_0 = 25U, //!< HR_ADCCLK = (input clock) / 25.0
    HR_ADC_CLK_DIV_26_0 = 26U, //!< HR_ADCCLK = (input clock) / 26.0
    HR_ADC_CLK_DIV_27_0 = 27U, //!< HR_ADCCLK = (input clock) / 27.0
    HR_ADC_CLK_DIV_28_0 = 28U, //!< HR_ADCCLK = (input clock) / 28.0
    HR_ADC_CLK_DIV_29_0 = 29U, //!< HR_ADCCLK = (input clock) / 29.0
    HR_ADC_CLK_DIV_30_0 = 30U, //!< HR_ADCCLK = (input clock) / 30.0
    HR_ADC_CLK_DIV_31_0 = 31U, //!< HR_ADCCLK = (input clock) / 31.0
} HR_ADC_ClkPrescale;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setMode() as the \e resolution
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_RESOLUTION_12BIT = 0x0U, //!< 12-bit conversion resolution
    HR_ADC_RESOLUTION_16BIT = 0x1U, //!< 16-bit conversion resolution
} HR_ADC_Resolution;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setMode() as the \e signalMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_MODE_SINGLE_ENDED = 0x0U, //!< Sample on single pin with VREFLO
    HR_ADC_MODE_DIFFERENTIAL = 0x1U  //!< Sample on pair of pins
} HR_ADC_SignalMode;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setupSOC() as the \e trigger
//! parameter to specify the event that will trigger a conversion to start.
//! It is also used with HR_ADC_setBurstModeConfig() and
//! HR_ADC_triggerRepeaterSelect().
//
//*****************************************************************************
typedef enum
{
    HR_ADC_TRIGGER_SW_ONLY     = 0U,  //!< Software only
    HR_ADC_TRIGGER_CPU1_TINT0  = 1U,  //!< CPU1 Timer 0, TINT0
    HR_ADC_TRIGGER_CPU1_TINT1  = 2U,  //!< CPU1 Timer 1, TINT1
    HR_ADC_TRIGGER_CPU1_TINT2  = 3U,  //!< CPU1 Timer 2, TINT2
    HR_ADC_TRIGGER_GPIO        = 4U,  //!< GPIO, HR_ADCEXTSOC
    HR_ADC_TRIGGER_EPWM1_SOCA  = 5U,  //!< ePWM1, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM1_SOCB  = 6U,  //!< ePWM1, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM2_SOCA  = 7U,  //!< ePWM2, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM2_SOCB  = 8U,  //!< ePWM2, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM3_SOCA  = 9U,  //!< ePWM3, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM3_SOCB  = 10U, //!< ePWM3, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM4_SOCA  = 11U, //!< ePWM4, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM4_SOCB  = 12U, //!< ePWM4, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM5_SOCA  = 13U, //!< ePWM5, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM5_SOCB  = 14U, //!< ePWM5, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM6_SOCA  = 15U, //!< ePWM6, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM6_SOCB  = 16U, //!< ePWM6, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM7_SOCA  = 17U, //!< ePWM7, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM7_SOCB  = 18U, //!< ePWM7, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM8_SOCA  = 19U, //!< ePWM8, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM8_SOCB  = 20U, //!< ePWM8, HR_ADCSOCB
    HR_ADC_TRIGGER_CPU2_TINT0  = 21U, //!< CPU2 Timer 0, TINT0
    HR_ADC_TRIGGER_CPU2_TINT1  = 22U, //!< CPU2 Timer 1, TINT1
    HR_ADC_TRIGGER_CPU2_TINT2  = 23U, //!< CPU2 Timer 2, TINT2
    HR_ADC_TRIGGER_EPWM9_SOCA  = 24U, //!< ePWM9, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM9_SOCB  = 25U, //!< ePWM9, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM10_SOCA = 26U, //!< ePWM10, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM10_SOCB = 27U, //!< ePWM10, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM11_SOCA = 28U, //!< ePWM11, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM11_SOCB = 29U, //!< ePWM11, HR_ADCSOCB
    HR_ADC_TRIGGER_EPWM12_SOCA = 30U, //!< ePWM12, HR_ADCSOCA
    HR_ADC_TRIGGER_EPWM12_SOCB = 31U, //!< ePWM12, HR_ADCSOCB

} HR_ADC_Trigger;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setupSOC() as the \e channel
//! parameter. This is the input pin on which the signal to be converted is
//! located.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_CH_ADCIN0          = 0U,  //!< single-ended, HR_ADCIN0
    HR_ADC_CH_ADCIN1          = 1U,  //!< single-ended, HR_ADCIN1
    HR_ADC_CH_ADCIN2          = 2U,  //!< single-ended, HR_ADCIN2
    HR_ADC_CH_ADCIN3          = 3U,  //!< single-ended, HR_ADCIN3
    HR_ADC_CH_ADCIN4          = 4U,  //!< single-ended, HR_ADCIN4
    HR_ADC_CH_ADCIN5          = 5U,  //!< single-ended, HR_ADCIN5
    HR_ADC_CH_ADCIN6          = 6U,  //!< single-ended, HR_ADCIN6
    HR_ADC_CH_ADCIN7          = 7U,  //!< single-ended, HR_ADCIN7
    HR_ADC_CH_ADCIN8          = 8U,  //!< single-ended, HR_ADCIN8
    HR_ADC_CH_ADCIN9          = 9U,  //!< single-ended, HR_ADCIN9
    HR_ADC_CH_ADCIN10         = 10U, //!< single-ended, HR_ADCIN10
    HR_ADC_CH_ADCIN11         = 11U, //!< single-ended, HR_ADCIN11
    HR_ADC_CH_ADCIN12         = 12U, //!< single-ended, HR_ADCIN12
    HR_ADC_CH_ADCIN13         = 13U, //!< single-ended, HR_ADCIN13
    HR_ADC_CH_ADCIN14         = 14U, //!< single-ended, HR_ADCIN14
    HR_ADC_CH_ADCIN15         = 15U, //!< single-ended, HR_ADCIN15
    HR_ADC_CH_ADCIN0_ADCIN1   = 0U,  //!< differential, HR_ADCIN0 and HR_ADCIN1
    HR_ADC_CH_ADCIN2_ADCIN3   = 2U,  //!< differential, HR_ADCIN2 and HR_ADCIN3
    HR_ADC_CH_ADCIN4_ADCIN5   = 4U,  //!< differential, HR_ADCIN4 and HR_ADCIN5
    HR_ADC_CH_ADCIN6_ADCIN7   = 6U,  //!< differential, HR_ADCIN6 and HR_ADCIN7
    HR_ADC_CH_ADCIN8_ADCIN9   = 8U,  //!< differential, HR_ADCIN8 and HR_ADCIN9
    HR_ADC_CH_ADCIN10_ADCIN11 = 10U, //!< differential, HR_ADCIN10 and HR_ADCIN11
    HR_ADC_CH_ADCIN12_ADCIN13 = 12U, //!< differential, HR_ADCIN12 and HR_ADCIN13
    HR_ADC_CH_ADCIN14_ADCIN15 = 14U, //!< differential, HR_ADCIN14 and HR_ADCIN15
} HR_ADC_Channel;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setInterruptPulseMode() as the
//! \e pulseMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Occurs at the end of the acquisition window
    HR_ADC_PULSE_END_OF_ACQ_WIN = 0x00U,
    //! Occurs at the end of the conversion
    HR_ADC_PULSE_END_OF_CONV = 0x04U
} HR_ADC_PulseMode;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_enableInterrupt(), HR_ADC_disableInterrupt(),
//! and HR_ADC_getInterruptStatus() as the \e HR_ADCIntNum parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_INT_NUMBER1 = 0U, //!< HR_ADCINT1 Interrupt
    HR_ADC_INT_NUMBER2 = 1U, //!< HR_ADCINT2 Interrupt
    HR_ADC_INT_NUMBER3 = 2U, //!< HR_ADCINT3 Interrupt
    HR_ADC_INT_NUMBER4 = 3U  //!< HR_ADCINT4 Interrupt
} HR_ADC_IntNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e ppbNumber parameter for several
//! functions.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_PPB_NUMBER1 = 0U, //!< Post-processing block 1
    HR_ADC_PPB_NUMBER2 = 1U, //!< Post-processing block 2
    HR_ADC_PPB_NUMBER3 = 2U, //!< Post-processing block 3
    HR_ADC_PPB_NUMBER4 = 3U  //!< Post-processing block 4
} HR_ADC_PPBNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e socNumber parameter for several
//! functions. This value identifies the start-of-conversion (SOC) that a
//! function is configuring or accessing. Note that in some cases (for example,
//! HR_ADC_setInterruptSource()) \e socNumber is used to refer to the
//! corresponding end-of-conversion (EOC).
//
//*****************************************************************************
typedef enum
{
    HR_ADC_SOC_NUMBER0  = 0U,  //!< SOC/EOC number 0
    HR_ADC_SOC_NUMBER1  = 1U,  //!< SOC/EOC number 1
    HR_ADC_SOC_NUMBER2  = 2U,  //!< SOC/EOC number 2
    HR_ADC_SOC_NUMBER3  = 3U,  //!< SOC/EOC number 3
    HR_ADC_SOC_NUMBER4  = 4U,  //!< SOC/EOC number 4
    HR_ADC_SOC_NUMBER5  = 5U,  //!< SOC/EOC number 5
    HR_ADC_SOC_NUMBER6  = 6U,  //!< SOC/EOC number 6
    HR_ADC_SOC_NUMBER7  = 7U,  //!< SOC/EOC number 7
    HR_ADC_SOC_NUMBER8  = 8U,  //!< SOC/EOC number 8
    HR_ADC_SOC_NUMBER9  = 9U,  //!< SOC/EOC number 9
    HR_ADC_SOC_NUMBER10 = 10U, //!< SOC/EOC number 10
    HR_ADC_SOC_NUMBER11 = 11U, //!< SOC/EOC number 11
    HR_ADC_SOC_NUMBER12 = 12U, //!< SOC/EOC number 12
    HR_ADC_SOC_NUMBER13 = 13U, //!< SOC/EOC number 13
    HR_ADC_SOC_NUMBER14 = 14U, //!< SOC/EOC number 14
    HR_ADC_SOC_NUMBER15 = 15U  //!< SOC/EOC number 15
} HR_ADC_SOCNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e trigger parameter for the
//! HR_ADC_setInterruptSOCTrigger() function.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_INT_SOC_TRIGGER_NONE    = 0U, //!< No HR_ADCINT will trigger the SOC
    HR_ADC_INT_SOC_TRIGGER_ADCINT1 = 1U, //!< HR_ADCINT1 will trigger the SOC
    HR_ADC_INT_SOC_TRIGGER_ADCINT2 = 2U  //!< HR_ADCINT2 will trigger the SOC
} HR_ADC_IntSOCTrigger;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setSOCPriority() as the \e priMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_PRI_ALL_ROUND_ROBIN  = 0U,  //!< Round robin mode is used for all
    HR_ADC_PRI_SOC0_HIPRI       = 1U,  //!< SOC 0 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC1_HIPRI  = 2U,  //!< SOC 0-1 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC2_HIPRI  = 3U,  //!< SOC 0-2 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC3_HIPRI  = 4U,  //!< SOC 0-3 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC4_HIPRI  = 5U,  //!< SOC 0-4 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC5_HIPRI  = 6U,  //!< SOC 0-5 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC6_HIPRI  = 7U,  //!< SOC 0-6 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC7_HIPRI  = 8U,  //!< SOC 0-7 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC8_HIPRI  = 9U,  //!< SOC 0-8 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC9_HIPRI  = 10U, //!< SOC 0-9 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC10_HIPRI = 11U, //!< SOC 0-10 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC11_HIPRI = 12U, //!< SOC 0-11 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC12_HIPRI = 13U, //!< SOC 0-12 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC13_HIPRI = 14U, //!< SOC 0-13 hi pri, others in round robin
    HR_ADC_PRI_THRU_SOC14_HIPRI = 15U, //!< SOC 0-14 hi pri, SOC15 in round robin
    HR_ADC_PRI_ALL_HIPRI        = 16U  //!< All priorities based on SOC number
} HR_ADC_PriorityMode;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_getTemperatureC(), HR_ADC_getTemperatureK(),
//! HR_ADC_setVREF() and HR_ADC_setOffsetTrimAll() as the \e refMode parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_REFERENCE_INTERNAL = 0U,
    HR_ADC_REFERENCE_EXTERNAL = 1U
} HR_ADC_ReferenceMode;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setVREF() and HR_ADC_setOffsetTrimAll() as the
//! \e refVoltage parameter.
//!
//
//*****************************************************************************
typedef enum
{
    HR_ADC_REFERENCE_3_3V = 0U,
    HR_ADC_REFERENCE_2_5V = 1U
} HR_ADC_ReferenceVoltage;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_configOSDetectMode() as the \e modeVal
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_OSDETECT_MODE_DISABLED = 0x0U,            //!< Open/Shorts detection cir-
                                                     //!< cuit(O/S DC) is disabled
    HR_ADC_OSDETECT_MODE_VSSA = 0x1U,                //!< O/S DC is enabled at zero
                                                     //!< scale
    HR_ADC_OSDETECT_MODE_VDDA = 0x2U,                //!< O/S DC is enabled at full
                                                     //!< scale
    HR_ADC_OSDETECT_MODE_5BY12_VDDA = 0x3U,          //!< O/S DC is enabled at 5/12
                                                     //!< scale
    HR_ADC_OSDETECT_MODE_7BY12_VDDA = 0x4U,          //!< O/S DC is enabled at 7/12
                                                     //!< scale
    HR_ADC_OSDETECT_MODE_5K_PULLDOWN_TO_VSSA = 0x5U, //!< O/S DC is enabled at 5K
                                                     //!< pulldown to VSSA
    HR_ADC_OSDETECT_MODE_5K_PULLUP_TO_VDDA = 0x6U,   //!< O/S DC is enabled at 5K
                                                     //!< pullup to VDDA
    HR_ADC_OSDETECT_MODE_7K_PULLDOWN_TO_VSSA = 0x7U  //!< O/S DC is enabled at 7K
                                                     //!< pulldown to VSSA
} HR_ADC_OSDetectMode;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_selectOffsetTrimMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_OFFSET_TRIM_COMMON = 0x0000U,    //!< Common Trim register for all
                                            //!< HR_ADC modes
    HR_ADC_OFFSET_TRIM_INDIVIDUAL = 0x0100U //!< Individual Trim registers for
                                            //!< different HR_ADC modes
} HR_ADC_OffsetTrim;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setupSOCRefloChannel() as the
//! \e channelType parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_CHANNEL_ODD  = 0U, //!< HR_ADC Odd Channel
    HR_ADC_CHANNEL_EVEN = 1U  //!< HR_ADC Even Channel
} HR_ADC_ChannelType;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_selectPPBSyncInput() and
//! HR_ADC_triggerRepeaterSyncIn() as the \e syncInput parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_SYNCIN_DISABLE          = 0x00U, //!< HR_ADC Syncin is disabled
    HR_ADC_SYNCIN_EPWM1SYNCOUT     = 0x01U, //!< HR_ADC Syncin is EPWM1SYNCOUT
    HR_ADC_SYNCIN_EPWM2SYNCOUT     = 0x02U, //!< HR_ADC Syncin is EPWM2SYNCOUT
    HR_ADC_SYNCIN_EPWM3SYNCOUT     = 0x03U, //!< HR_ADC Syncin is EPWM3SYNCOUT
    HR_ADC_SYNCIN_EPWM4SYNCOUT     = 0x04U, //!< HR_ADC Syncin is EPWM4SYNCOUT
    HR_ADC_SYNCIN_EPWM5SYNCOUT     = 0x05U, //!< HR_ADC Syncin is EPWM5SYNCOUT
    HR_ADC_SYNCIN_EPWM6SYNCOUT     = 0x06U, //!< HR_ADC Syncin is EPWM6SYNCOUT
    HR_ADC_SYNCIN_EPWM7SYNCOUT     = 0x07U, //!< HR_ADC Syncin is EPWM7SYNCOUT
    HR_ADC_SYNCIN_EPWM8SYNCOUT     = 0x08U, //!< HR_ADC Syncin is EPWM8SYNCOUT
    HR_ADC_SYNCIN_EPWM9SYNCOUT     = 0x09U, //!< HR_ADC Syncin is EPWM9SYNCOUT
    HR_ADC_SYNCIN_EPWM10SYNCOUT    = 0x0AU, //!< HR_ADC Syncin is EPWM10SYNCOUT
    HR_ADC_SYNCIN_EPWM11SYNCOUT    = 0x0BU, //!< HR_ADC Syncin is EPWM11SYNCOUT
    HR_ADC_SYNCIN_EPWM12SYNCOUT    = 0x0CU, //!< HR_ADC Syncin is EPWM12SYNCOUT
    HR_ADC_SYNCIN_EPWM13SYNCOUT    = 0x0DU, //!< HR_ADC Syncin is EPWM13SYNCOUT
    HR_ADC_SYNCIN_EPWM14SYNCOUT    = 0x0EU, //!< HR_ADC Syncin is EPWM14SYNCOUT
    HR_ADC_SYNCIN_EPWM15SYNCOUT    = 0x0FU, //!< HR_ADC Syncin is EPWM15SYNCOUT
    HR_ADC_SYNCIN_EPWM16SYNCOUT    = 0x10U, //!< HR_ADC Syncin is EPWM16SYNCOUT
    HR_ADC_SYNCIN_EPWM17SYNCOUT    = 0x11U, //!< HR_ADC Syncin is EPWM17SYNCOUT
    HR_ADC_SYNCIN_EPWM18SYNCOUT    = 0x12U, //!< HR_ADC Syncin is EPWM18SYNCOUT
    HR_ADC_SYNCIN_ECAP1YNCOUT      = 0x13U, //!< HR_ADC Syncin is ECAP1YNCOUT
    HR_ADC_SYNCIN_ECAP2SYNCOUT     = 0x14U, //!< HR_ADC Syncin is ECAP2SYNCOUT
    HR_ADC_SYNCIN_ECAP3SYNCOUT     = 0x15U, //!< HR_ADC Syncin is ECAP3SYNCOUT
    HR_ADC_SYNCIN_ECAP4SYNCOUT     = 0x16U, //!< HR_ADC Syncin is ECAP4SYNCOUT
    HR_ADC_SYNCIN_ECAP5SYNCOUT     = 0x17U, //!< HR_ADC Syncin is ECAP5SYNCOUT
    HR_ADC_SYNCIN_ECAP6SYNCOUT     = 0x18U, //!< HR_ADC Syncin is ECAP6SYNCOUT
    HR_ADC_SYNCIN_ECAP7SYNCOUT     = 0x19U, //!< HR_ADC Syncin is ECAP7SYNCOUT
    HR_ADC_SYNCIN_INPUTXBAROUTPUT5 = 0x1AU, //!< HR_ADC Syncin is INPUTXBAROUTPUT5
    HR_ADC_SYNCIN_INPUTXBAROUTPUT6 = 0x1BU, //!< HR_ADC Syncin is INPUTXBAROUTPUT6
    HR_ADC_SYNCIN_EtherCATSYNC0    = 0x1CU, //!< HR_ADC Syncin is EtherCATSYNC0
    HR_ADC_SYNCIN_EtherCATSYNC1    = 0x1DU  //!< HR_ADC Syncin is EtherCATSYNC1
} HR_ADC_SyncInput;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_selectSOCExtChannel() as the \e extChannel
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_CH_HR_ADCINX_0  = 0x0U, //!< HR_ADCINX.0 is converted
    HR_ADC_CH_HR_ADCINX_1  = 0x1U, //!< HR_ADCINX.1 is converted
    HR_ADC_CH_HR_ADCINX_2  = 0x2U, //!< HR_ADCINX.2 is converted
    HR_ADC_CH_HR_ADCINX_3  = 0x3U, //!< HR_ADCINX.3 is converted
    HR_ADC_CH_HR_ADCINX_4  = 0x4U, //!< HR_ADCINX.4 is converted
    HR_ADC_CH_HR_ADCINX_5  = 0x5U, //!< HR_ADCINX.5 is converted
    HR_ADC_CH_HR_ADCINX_6  = 0x6U, //!< HR_ADCINX.6 is converted
    HR_ADC_CH_HR_ADCINX_7  = 0x7U, //!< HR_ADCINX.7 is converted
    HR_ADC_CH_HR_ADCINX_8  = 0x8U, //!< HR_ADCINX.8 is converted
    HR_ADC_CH_HR_ADCINX_9  = 0x9U, //!< HR_ADCINX.9 is converted
    HR_ADC_CH_HR_ADCINX_10 = 0xAU, //!< HR_ADCINX.10 is converted
    HR_ADC_CH_HR_ADCINX_11 = 0xBU, //!< HR_ADCINX.11 is converted
    HR_ADC_CH_HR_ADCINX_12 = 0xCU, //!< HR_ADCINX.12 is converted
    HR_ADC_CH_HR_ADCINX_13 = 0xDU, //!< HR_ADCINX.13 is converted
    HR_ADC_CH_HR_ADCINX_14 = 0xEU, //!< HR_ADCINX.14 is converted
    HR_ADC_CH_HR_ADCINX_15 = 0xFU  //!< HR_ADCINX.15 is converted
} HR_ADC_ExtChannel;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_setInterruptSource() as the \e intTrigger
//! parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_INT_TRIGGER_EOC0  = 0U,  //!< SOC/EOC0
    HR_ADC_INT_TRIGGER_EOC1  = 1U,  //!< SOC/EOC1
    HR_ADC_INT_TRIGGER_EOC2  = 2U,  //!< SOC/EOC2
    HR_ADC_INT_TRIGGER_EOC3  = 3U,  //!< SOC/EOC3
    HR_ADC_INT_TRIGGER_EOC4  = 4U,  //!< SOC/EOC4
    HR_ADC_INT_TRIGGER_EOC5  = 5U,  //!< SOC/EOC5
    HR_ADC_INT_TRIGGER_EOC6  = 6U,  //!< SOC/EOC6
    HR_ADC_INT_TRIGGER_EOC7  = 7U,  //!< SOC/EOC7
    HR_ADC_INT_TRIGGER_EOC8  = 8U,  //!< SOC/EOC8
    HR_ADC_INT_TRIGGER_EOC9  = 9U,  //!< SOC/EOC9
    HR_ADC_INT_TRIGGER_EOC10 = 10U, //!< SOC/EOC10
    HR_ADC_INT_TRIGGER_EOC11 = 11U, //!< SOC/EOC11
    HR_ADC_INT_TRIGGER_EOC12 = 12U, //!< SOC/EOC12
    HR_ADC_INT_TRIGGER_EOC13 = 13U, //!< SOC/EOC13
    HR_ADC_INT_TRIGGER_EOC14 = 14U, //!< SOC/EOC14
    HR_ADC_INT_TRIGGER_EOC15 = 15U, //!< SOC/EOC15
} HR_ADC_IntTrigger;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_configureSafetyChecker() as the
//! \e HR_ADCInst parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_A = 0U, //!< Select HR_ADCA instance
    HR_ADC_B = 1U, //!< Select HR_ADCB instance
    HR_ADC_C = 2U  //!< Select HR_ADCC instance
} HR_ADC_Select;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_configureSafetyChecker() as the
//! \e HR_ADCResultInst parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADCRESULT0  = 0U,  //!< Select HR_ADC Result 0
    HR_ADCRESULT1  = 1U,  //!< Select HR_ADC Result 1
    HR_ADCRESULT2  = 2U,  //!< Select HR_ADC Result 2
    HR_ADCRESULT3  = 3U,  //!< Select HR_ADC Result 3
    HR_ADCRESULT4  = 4U,  //!< Select HR_ADC Result 4
    HR_ADCRESULT5  = 5U,  //!< Select HR_ADC Result 5
    HR_ADCRESULT6  = 6U,  //!< Select HR_ADC Result 6
    HR_ADCRESULT7  = 7U,  //!< Select HR_ADC Result 7
    HR_ADCRESULT8  = 8U,  //!< Select HR_ADC Result 8
    HR_ADCRESULT9  = 9U,  //!< Select HR_ADC Result 9
    HR_ADCRESULT10 = 10U, //!< Select HR_ADC Result 10
    HR_ADCRESULT11 = 11U, //!< Select HR_ADC Result 11
    HR_ADCRESULT12 = 12U, //!< Select HR_ADC Result 12
    HR_ADCRESULT13 = 13U, //!< Select HR_ADC Result 13
    HR_ADCRESULT14 = 14U, //!< Select HR_ADC Result 14
    HR_ADCRESULT15 = 15U  //!< Select HR_ADC Result 15
} HR_ADC_ResultSelect;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_getSafetyCheckerResult() as
//! \e checkInst parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_SAFETY_CHECK1 = 0x0U, //!< Safety Check Result 1
    HR_ADC_SAFETY_CHECK2 = 0x2U  //!< Safety Check Result 2
} HR_ADC_SafetyCheckInst;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_enableSafetyCheckEvt() and
//! HR_ADC_disableSafetyCheckEvt() as \e checkEvent parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_SAFETY_CHECK_EVENT1 = 0U,  //!< Safety Check Event 1
    HR_ADC_SAFETY_CHECK_EVENT2 = 8U,  //!< Safety Check Event 2
    HR_ADC_SAFETY_CHECK_EVENT3 = 16U, //!< Safety Check Event 3
    HR_ADC_SAFETY_CHECK_EVENT4 = 24U  //!< Safety Check Event 4
} HR_ADC_SafetyCheckEvent;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_enableSafetyCheckEvt(),
//! HR_ADC_disableSafetyCheckEvt(), HR_ADC_enableSafetyCheckInt() and
//! HR_ADC_disableSafetyCheckInt() as \e checkResult parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_SAFETY_CHECK_RES1OVF = 0U, //!< Safety Check Result1 Overflow
    HR_ADC_SAFETY_CHECK_RES2OVF = 2U, //!< Safety Check Result2 Overflow
    HR_ADC_SAFETY_CHECK_OOT     = 4U  //!< Safety Check OOT
} HR_ADC_SafetyCheckResult;

//*****************************************************************************
//
//! Values that can be passed to HR_ADC_enableSafetyCheckEvt(),
//! HR_ADC_disableSafetyCheckEvt(), HR_ADC_enableSafetyCheckInt(),
//! HR_ADC_disableSafetyCheckInt(), HR_ADC_getSafetyCheckStatus(),
//! HR_ADC_clearSafetyCheckStatus(), HR_ADC_getSafetyCheckIntStatus() and
//! HR_ADC_clearSafetyCheckIntStatus() as \e checkerNumber parameter.
//
//*****************************************************************************
typedef enum
{
    HR_ADC_SAFETY_CHECKER1 = 0U, //!< Safety Checker1
    HR_ADC_SAFETY_CHECKER2 = 1U, //!< Safety Checker2
    HR_ADC_SAFETY_CHECKER3 = 2U, //!< Safety Checker3
    HR_ADC_SAFETY_CHECKER4 = 3U, //!< Safety Checker4
    HR_ADC_SAFETY_CHECKER5 = 4U, //!< Safety Checker5
    HR_ADC_SAFETY_CHECKER6 = 5U, //!< Safety Checker6
    HR_ADC_SAFETY_CHECKER7 = 6U, //!< Safety Checker7
    HR_ADC_SAFETY_CHECKER8 = 7U  //!< Safety Checker8
} HR_ADC_Checker;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an HR_ADC base address.
//!
//! \param base specifies the HR_ADC module base address.
//!
//! This function determines if a HR_ADC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool HR_ADC_isBaseValid(uint32_t base)
{
    return ((base == HR_ADCA_BASE) || (base == HR_ADCB_BASE) || (base == HR_ADCC_BASE));
}
#endif

//*****************************************************************************
//
//! Configures the analog-to-digital converter module prescaler.
//!
//! \param base is the base address of the HR_ADC module.
//! \param clkPrescale is the HR_ADC clock prescaler.
//!
//! This function configures the HR_ADC module's HR_ADCCLK.
//!
//! The \e clkPrescale parameter specifies the value by which the input clock
//! is divided to make the HR_ADCCLK.  The clkPrescale value can be specified with
//! any of the following enum values:
//! \b HR_ADC_CLK_DIV_1_0, \b HR_ADC_CLK_DIV_2_0, \b HR_ADC_CLK_DIV_2_5, ...,
//! \b HR_ADC_CLK_DIV_7_5, \b HR_ADC_CLK_DIV_8_0, or \b HR_ADC_CLK_DIV_8_5.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setPrescaler(uint32_t base, HR_ADC_ClkPrescale clkPrescale)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Set the configuration of the HR_ADC module prescaler.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_CTL2)
        = (HWREG(base + HR_ADC_O_CTL2) & ~HR_ADC_CTL2_PRESCALE_M) | (uint32_t)clkPrescale;
    EDIS;
}

//*****************************************************************************
//
//! Configures a start-of-conversion (SOC) in the HR_ADC.
//!
//! \param base is the base address of the HR_ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param trigger the source that will cause the SOC.
//! \param channel is the number associated with the input signal.
//! \param sampleWindow is the acquisition window duration.
//!
//! This function configures the a start-of-conversion (SOC) in the HR_ADC module.
//!
//! The \e socNumber number is a value \b HR_ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the HR_ADC module
//! specified by \e base.
//!
//! The \e trigger specifies the event that causes the SOC such as software, a
//! timer interrupt, an ePWM event, or an HR_ADC interrupt. It should be a value
//! in the format of \b HR_ADC_TRIGGER_XXXX where XXXX is the event such as
//! \b HR_ADC_TRIGGER_SW_ONLY, \b HR_ADC_TRIGGER_CPU1_TINT0, \b HR_ADC_TRIGGER_GPIO,
//! \b HR_ADC_TRIGGER_EPWM1_SOCA, and so on.
//!
//! The \e channel parameter specifies the channel to be converted. In
//! single-ended mode this is a single pin given by \b HR_ADC_CH_HR_ADCINx where x is
//! the number identifying the pin between 0 and 31 inclusive. In differential
//! mode, two pins are used as inputs and are passed in the \e channel
//! parameter as \b HR_ADC_CH_HR_ADCIN0_HR_ADCIN1, \b HR_ADC_CH_HR_ADCIN2_HR_ADCIN3, ..., or
//! \b HR_ADC_CH_HR_ADCIN14_HR_ADCIN15.
//!
//! The \e sampleWindow parameter is the acquisition window duration in SYSCLK
//! cycles. It should be a value between 1 and 512 cycles inclusive. The
//! selected duration must be at least as long as one HR_ADCCLK cycle. Also, the
//! datasheet will specify a minimum window duration requirement in
//! nanoseconds.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setupSOC(uint32_t base, HR_ADC_SOCNumber socNumber,
    HR_ADC_Trigger trigger, HR_ADC_Channel channel, uint32_t sampleWindow)
{
    uint32_t ctlRegAddr, mask;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 512U));

    mask = (HR_ADC_SOC0CTL_CHSEL_M | HR_ADC_SOC0CTL_TRIGSEL_M);

    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + HR_ADC_SOCxCTL_OFFSET_BASE + ((uint32_t)socNumber * 4U);

    //
    // Set the configuration of the specified SOC.
    //
    EALLOW;

    HWREG(ctlRegAddr) = (HWREG(ctlRegAddr) & ~(mask))
                        | ((uint32_t)channel << HR_ADC_SOC0CTL_CHSEL_S)
                        | ((uint32_t)trigger << HR_ADC_SOC0CTL_TRIGSEL_S) | sampleWindow;

    EDIS;
}

//*****************************************************************************
//
//! Configures the interrupt SOC trigger of an SOC.
//!
//! \param base is the base address of the HR_ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param trigger the interrupt source that will cause the SOC.
//!
//! This function configures the interrupt start-of-conversion trigger in
//! the HR_ADC module.
//!
//! The \e socNumber number is a value \b HR_ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the HR_ADC module
//! specified by \e base.
//!
//! The \e trigger specifies the interrupt that causes a start of conversion or
//! none. It should be one of the following values.
//!
//! - \b HR_ADC_INT_SOC_TRIGGER_NONE
//! - \b HR_ADC_INT_SOC_TRIGGER_HR_ADCINT1
//! - \b HR_ADC_INT_SOC_TRIGGER_HR_ADCINT2
//!
//! This functionality is useful for creating continuous conversions.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setInterruptSOCTrigger(
    uint32_t base, HR_ADC_SOCNumber socNumber, HR_ADC_IntSOCTrigger trigger)
{
    uint32_t shiftVal;
    uint32_t intRegAddr;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Each SOC has a 2-bit field in this register.
    //
    if ((uint32_t)socNumber <= 7)
    {
        shiftVal   = (uint32_t)socNumber << 1U;
        intRegAddr = base + HR_ADC_O_INTSEL1N2;
    }
    else
    {
        shiftVal   = ((uint32_t)socNumber - 8U) << 1U;
        intRegAddr = base + HR_ADC_O_INTSEL1N2 + 4U;
    }
    //
    // Set the configuration of the specified SOC. Not that we're treating
    // HR_ADCINTSOCSEL1 and HR_ADCINTSOCSEL2 as one 32-bit register here.
    //
    EALLOW;
    HWREG(intRegAddr) = (HWREG(intRegAddr) & ~((uint32_t)HR_ADC_INTSOCSEL1_SOC0_M << shiftVal))
                        | ((uint32_t)trigger << shiftVal);
    EDIS;
}

//*****************************************************************************
//
//! Sets the timing of the end-of-conversion pulse
//!
//! \param base is the base address of the HR_ADC module.
//! \param pulseMode is the generation mode of the EOC pulse.
//!
//! This function configures the end-of-conversion (EOC) pulse generated by HR_ADC.
//! This pulse will be generated either at the end of the acquisition window
//! plus a number of SYSCLK cycles configured by HR_ADC_setInterruptCycleOffset()
//! (pass \b HR_ADC_PULSE_END_OF_ACQ_WIN into \e pulseMode) or at the end of the
//! voltage conversion, one cycle prior to the HR_ADC result latching into it's
//! result register (pass \b HR_ADC_PULSE_END_OF_CONV into \e pulseMode).
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setInterruptPulseMode(uint32_t base, HR_ADC_PulseMode pulseMode)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Set the position of the pulse.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_CTL1)
        = (HWREG(base + HR_ADC_O_CTL1) & ~HR_ADC_CTL1_INTPULSEPOS) | (uint32_t)pulseMode;
    EDIS;
}

//*****************************************************************************
//
//! Gets the result ready status for HR_ADC interrupt.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function returns the result ready status associated with the selected
//! interrupt number within the HR_ADC wrapper.
//!
//! \e HR_ADCIntNum takes a one of the values
//! \b HR_ADC_INT_NUMBER1, \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3
//! or \b HR_ADC_INT_NUMBER4 to get the result ready status for the conversions
//! associated with the given interrupt number.
//!
//! \return \b true if the result is available for the selected interrupt
//! and \b false if it is not.
//
//*****************************************************************************
static inline bool HR_ADC_getIntResultStatus(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the specified HR_ADC interrupt result ready status.
    //
    return ((HWREG(base + HR_ADC_O_INTFLG) & (1U << ((uint32_t)HR_ADCIntNum + 4U))) != 0U);
}

//*****************************************************************************
//
//! Powers up the analog-to-digital converter core.
//!
//! \param base is the base address of the HR_ADC module.
//!
//! This function powers up the analog circuitry inside the analog core.
//!
//! \note Allow at least a 500us delay before sampling after calling this API.
//! If you enable multiple HR_ADCs, you can delay after they all have begun
//! powering up.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_enableConverter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Set the bit that powers up the analog circuitry.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_CTL1) |= HR_ADC_CTL1_ADC_EN_P;
    EDIS;
}

//*****************************************************************************
//
//! Powers down the analog-to-digital converter module.
//!
//! \param base is the base address of the HR_ADC module.
//!
//! This function powers down the analog circuitry inside the analog core.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_disableConverter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Clear the bit that powers down the analog circuitry.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_CTL1) &= ~HR_ADC_CTL1_ADC_EN_P;
    EDIS;
}

//*****************************************************************************
//
//! Forces a SOC flag to a 1 in the analog-to-digital converter.
//!
//! \param base is the base address of the HR_ADC module.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function forces the SOC flag associated with the SOC specified by
//! \e socNumber. This initiates a conversion once that SOC is given
//! priority. This software trigger can be used whether or not the SOC has been
//! configured to accept some other specific trigger.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_forceSOC(uint32_t base, HR_ADC_SOCNumber socNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    EALLOW;
    //
    // Write to the register that will force a 1 to the corresponding SOC flag
    //
    HWREG(base + HR_ADC_O_SOCFRC1) = ((uint32_t)1U << (uint32_t)socNumber);
}

//*****************************************************************************
//
//! Forces multiple SOC flags to 1 in the analog-to-digital converter.
//!
//! \param base is the base address of the HR_ADC module.
//! \param socMask is the SOCs to be forced through software
//!
//! This function forces the SOCFRC1 flags associated with the SOCs specified
//! by \e socMask. This initiates a conversion once the desired SOCs are given
//! priority. This software trigger can be used whether or not the SOC has been
//! configured to accept some other specific trigger.
//! Valid values for \e socMask parameter can be any of the individual
//! HR_ADC_FORCE_SOCx values or any of their OR'd combination to trigger multiple
//! SOCs.
//!
//! \note To trigger SOC0, SOC1 and SOC2, value (HR_ADC_FORCE_SOC0 |
//! HR_ADC_FORCE_SOC1 | HR_ADC_FORCE_SOC2) should be passed as socMask.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_forceMultipleSOC(uint32_t base, uint32_t socMask)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Write to the register that will force a 1 to desired SOCs
    //
    HWREG(base + HR_ADC_O_SOCFRC1) = socMask;
}

//*****************************************************************************
//
//! Gets the current HR_ADC interrupt status.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function returns the interrupt status for the analog-to-digital
//! converter.
//!
//! \e HR_ADCIntNum takes a one of the values \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to get
//! the interrupt status for the given interrupt number of the HR_ADC module.
//!
//! \return \b true if the interrupt flag for the specified interrupt number is
//! set and \b false if it is not.
//
//*****************************************************************************
static inline bool HR_ADC_getInterruptStatus(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    //
    // Get the specified HR_ADC interrupt status.
    //
    return ((HWREG(base + HR_ADC_O_INTFLG) & (1U << (uint32_t)HR_ADCIntNum)) != 0U);
}

//*****************************************************************************
//
//! Clears HR_ADC interrupt sources.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function clears the specified HR_ADC interrupt sources so that they no
//! longer assert. If not in continuous mode, this function must be called
//! before any further interrupt pulses may occur.
//!
//! \e HR_ADCIntNum takes a one of the values \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to express
//! which of the four interrupts of the HR_ADC module should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_clearInterruptStatus(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Clear the specified interrupt.
    //
    HWREG(base + HR_ADC_O_INTFLGCLR) = (uint32_t)1U << (uint32_t)HR_ADCIntNum;
}

//*****************************************************************************
//
//! Gets the current HR_ADC interrupt overflow status.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function returns the interrupt overflow status for the
//! analog-to-digital converter. An overflow condition is generated
//! irrespective of the continuous mode.
//!
//! \e HR_ADCIntNum takes a one of the values \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to get
//! the interrupt overflow status for the given interrupt number.
//!
//! \return \b true if the interrupt overflow flag for the specified interrupt
//! number is set and \b false if it is not.
//
//*****************************************************************************
static inline bool HR_ADC_getInterruptOverflowStatus(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the specified HR_ADC interrupt status.
    //
    return ((HWREG(base + HR_ADC_O_INTOVF) & (1U << (uint32_t)HR_ADCIntNum)) != 0U);
}

//*****************************************************************************
//
//! Clears HR_ADC interrupt overflow sources.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function clears the specified HR_ADC interrupt overflow sources so that
//! they no longer assert. If software tries to clear the overflow in the same
//! cycle that hardware tries to set the overflow, then hardware has priority.
//!
//! \e HR_ADCIntNum takes a one of the values \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to express
//! which of the four interrupt overflow status of the HR_ADC module
//! should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_clearInterruptOverflowStatus(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Clear the specified interrupt overflow bit.
    //
    HWREG(base + HR_ADC_O_INTOVFCLR) = (uint32_t)1U << (uint32_t)HR_ADCIntNum;
}

//*****************************************************************************
//
//! Reads the conversion result.
//!
//! \param resultBase is the base address of the HR_ADC results.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function returns the conversion result that corresponds to the base
//! address passed into \e resultBase and the SOC passed into \e socNumber.
//!
//! The \e socNumber number is a value \b HR_ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC's result is to be read.
//!
//! \note Take care that you are using a base address for the result registers
//! (HR_ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the conversion result.
//
//*****************************************************************************
static inline uint32_t HR_ADC_readResult(uint32_t resultBase, HR_ADC_SOCNumber socNumber)
{
    //
    // Check the arguments.
    //
    ASSERT((resultBase == HR_ADCARESULT_BASE) || (resultBase == HR_ADCBRESULT_BASE)
           || (resultBase == HR_ADCCRESULT_BASE));
    //
    // Return the HR_ADC result for the selected SOC.
    //
    return (HWREG(resultBase + (uint32_t)socNumber * 4U));
}

//*****************************************************************************
//
//! Determines whether the HR_ADC is busy or not.
//!
//! \param base is the base address of the HR_ADC.
//!
//! This function allows the caller to determine whether or not the HR_ADC is
//! busy and can sample another channel.
//!
//! \return Returns \b true if the HR_ADC is sampling or \b false if all
//! samples are complete.
//
//*****************************************************************************
static inline bool HR_ADC_isBusy(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Determine if the HR_ADC is busy.
    //
    return ((HWREG(base + HR_ADC_O_CTL1) & HR_ADC_CTL1_ADCBSY) != 0U);
}

//*****************************************************************************
//
//! Set SOC burst mode.
//!
//! \param base is the base address of the HR_ADC.
//! \param trigger the source that will cause the burst conversion sequence.
//! \param burstSize is the number of SOCs converted during a burst sequence.
//!
//! This function configures the burst trigger and burstSize of an HR_ADC module.
//! Burst mode allows a single trigger to walk through the round-robin SOCs one
//! or more at a time. When burst mode is enabled, the trigger selected by the
//! HR_ADC_setupSOC() API will no longer have an effect on the SOCs in round-robin
//! mode. Instead, the source specified through the \e trigger parameter will
//! cause a burst of \e burstSize conversions to occur.
//!
//! The \e trigger parameter takes the same values as the HR_ADC_setupSOC() API
//! The \e burstSize parameter should be a value between 1 and 16 inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setBurstModeConfig(
    uint32_t base, HR_ADC_Trigger trigger, uint32_t burstSize)
{
    uint32_t regValue;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT(((uint32_t)trigger & ~((uint32_t)0x1FU)) == 0U);
    ASSERT((burstSize >= 1U) && (burstSize <= 16U));

    //
    // Write the burst mode configuration to the register.
    //
    EALLOW;

    regValue = (uint32_t)trigger | ((burstSize - 1U) << HR_ADC_BURSTCTL_BURSTSIZE_S);

    HWREG(base + HR_ADC_O_BURSTCTL)
        = (HWREG(base + HR_ADC_O_BURSTCTL)
              & ~((uint32_t)HR_ADC_BURSTCTL_BURSTTRIGSEL_M | HR_ADC_BURSTCTL_BURSTSIZE_M))
          | regValue;

    EDIS;
}

//*****************************************************************************
//
//! Enables SOC burst mode.
//!
//! \param base is the base address of the HR_ADC.
//!
//! This function enables SOC burst mode operation of the HR_ADC. Burst mode
//! allows a single trigger to walk through the round-robin SOCs one or more at
//! a time. When burst mode is enabled, the trigger selected by the
//! HR_ADC_setupSOC() API will no longer have an effect on the SOCs in round-robin
//! mode. Use HR_ADC_setBurstMode() to configure the burst trigger and size.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_enableBurstMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Enable burst mode.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_BURSTCTL) |= HR_ADC_BURSTCTL_BURSTEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables SOC burst mode.
//!
//! \param base is the base address of the HR_ADC.
//!
//! This function disables SOC burst mode operation of the HR_ADC. SOCs in
//! round-robin mode will be triggered by the trigger configured using the
//! HR_ADC_setupSOC() API.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_disableBurstMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Disable burst mode.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_BURSTCTL) &= ~HR_ADC_BURSTCTL_BURSTEN;
    EDIS;
}

//*****************************************************************************
//
//! Sets the priority mode of the SOCs.
//!
//! \param base is the base address of the HR_ADC.
//! \param priMode is the priority mode of the SOCs.
//!
//! This function sets the priority mode of the SOCs. There are three main
//! modes that can be passed in the \e priMode parameter
//!
//! - All SOCs are in round-robin mode. This means no SOC has an inherent
//! higher priority over another. This is selected by passing in the value
//! \b HR_ADC_PRI_ALL_ROUND_ROBIN.
//! - All priorities are in high priority mode. This means that the priority of
//! the SOC is determined by its SOC number. This option is selected by passing
//! in the value \b HR_ADC_PRI_ALL_HIPRI.
//! - A range of SOCs are assigned high priority, with all others in round
//! robin mode. High priority mode means that an SOC with high priority will
//! interrupt the round robin wheel and insert itself as the next conversion.
//! Passing in the value \b HR_ADC_PRI_SOC0_HIPRI will make SOC0 highest priority,
//! \b HR_ADC_PRI_THRU_SOC1_HIPRI will put SOC0 and SOC 1 in high priority, and so
//! on up to \b HR_ADC_PRI_THRU_SOC14_HIPRI where SOCs 0 through 14 are in high
//! priority.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setSOCPriority(uint32_t base, HR_ADC_PriorityMode priMode)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    EALLOW;

    HWREG(base + HR_ADC_O_SOCPRICTL)
        = (HWREG(base + HR_ADC_O_SOCPRICTL) & ~HR_ADCSOCPRICTL_SOCPRIORITY_M) | (uint32_t)priMode;

    EDIS;
}

//*****************************************************************************
//
//! Configures a post-processing block (PPB) in the HR_ADC.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function associates a post-processing block with a SOC.
//!
//! The \e ppbNumber is a value \b HR_ADC_PPB_NUMBERX where X is a value from 1 to
//! 4 inclusive that identifies a PPB to be configured.  The \e socNumber
//! number is a value \b HR_ADC_SOC_NUMBERX where X is a number from 0 to 15
//! specifying which SOC is to be configured on the HR_ADC module specified by
//! \e base.
//!
//! \note You can have more that one PPB associated with the same SOC, but a
//! PPB can only be configured to correspond to one SOC at a time. Also note
//! that when you have multiple PPBs for the same SOC, the calibration offset
//! that actually gets applied will be that of the PPB with the highest number.
//! Since SOC0 is the default for all PPBs, look out for unintentional
//! overwriting of a lower numbered PPB's offset.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setupPPB(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, HR_ADC_SOCNumber socNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (HR_ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + HR_ADC_O_PPB1CONFIG;

    //
    // Write the configuration to the register.
    //
    EALLOW;
    HWREG(base + ppbOffset) = (HWREG(base + ppbOffset) & ~HR_ADC_PPB1CONFIG_CONFIG_M)
                              | ((uint32_t)socNumber & HR_ADC_PPB1CONFIG_CONFIG_M);
    EDIS;
}

//*****************************************************************************
//
//! Enables individual HR_ADC PPB event sources.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param evtFlags is a bit mask of the event sources to be enabled.
//!
//! This function enables the indicated HR_ADC PPB event sources.  This will allow
//! the specified events to propagate through the X-BAR to a pin or to an ePWM
//! module.  The \e evtFlags parameter can be any of the \b HR_ADC_EVT_TRIPHI,
//! \b HR_ADC_EVT_TRIPLO, or \b HR_ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_enablePPBEvent(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, uint32_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Enable the specified event.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_EVTSEL) |= evtFlags << ((uint32_t)ppbNumber * 3U);
    EDIS;
}
//*****************************************************************************
//
//! Enables cycle-by-cycle clear of ADC PPB event flags.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables the automatic cycle-by-cycle clear of ADC PPB event
//! flags. When enabled, the desired PPB event flags are automatically cleared
//! on the next PPBxRESULT load, unless a set condition is also occurring at
//! the same time, in which case the set takes precedence.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_enablePPBEventCBCClear(uint32_t base, HR_ADC_PPBNumber ppbNumber)
{
    uint32_t ppbAddress;
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ppbAddress = base + (0x18U * (uint32_t)ppbNumber) + 0x88U;
    //
    // Set automatic cycle-by-cycle flag clear bit
    //
    EALLOW;
    ((volatile struct HR_ADCPPBCONFIG_BITS *)ppbAddress)->CBCEN = 1;
    EDIS;
}
//*****************************************************************************
//
//! Disables individual HR_ADC PPB event sources.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param evtFlags is a bit mask of the event sources to be enabled.
//!
//! This function disables the indicated HR_ADC PPB event sources.  This will stop
//! the specified events from propagating through the X-BAR to other modules.
//! The \e evtFlags parameter can be any of the \b HR_ADC_EVT_TRIPHI,
//! \b HR_ADC_EVT_TRIPLO, or \b HR_ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_disablePPBEvent(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, uint32_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Disable the specified event.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_EVTSEL) &= ~(evtFlags << ((uint32_t)ppbNumber * 3U));
    EDIS;
}

//*****************************************************************************
//
//! Enables individual HR_ADC PPB event interrupt sources.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated HR_ADC PPB interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.  The \e intFlags
//! parameter can be any of the \b HR_ADC_EVT_TRIPHI, \b HR_ADC_EVT_TRIPLO, or
//! \b HR_ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_enablePPBEventInterrupt(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT((intFlags & ~0x7U) == 0U);

    //
    // Enable the specified event interrupts.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_EVTINTSEL) |= intFlags << ((uint32_t)ppbNumber * 3U);
    EDIS;
}

//*****************************************************************************
//
//! Disables individual HR_ADC PPB event interrupt sources.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param intFlags is a bit mask of the interrupt source to be disabled.
//!
//! This function disables the indicated HR_ADC PPB interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.  The \e intFlags
//! parameter can be any of the \b HR_ADC_EVT_TRIPHI, \b HR_ADC_EVT_TRIPLO, or
//! \b HR_ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_disablePPBEventInterrupt(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, uint32_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT((intFlags & ~0x7U) == 0U);

    //
    // Disable the specified event interrupts.
    //
    EALLOW;
    HWREG(base + HR_ADC_O_EVTINTSEL) &= ~(intFlags << ((uint32_t)ppbNumber * 3U));
    EDIS;
}

//*****************************************************************************
//
//! Gets the current HR_ADC event status.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the event status for the analog-to-digital converter.
//!
//! \return Returns the current event status, enumerated as a bit field of
//! \b HR_ADC_EVT_TRIPHI, \b HR_ADC_EVT_TRIPLO, and \b HR_ADC_EVT_ZERO.
//
//*****************************************************************************
static inline uint32_t HR_ADC_getPPBEventStatus(uint32_t base, HR_ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the event status for the specified post-processing block.
    //
    return ((HWREG(base + HR_ADC_O_EVTSTAT) >> ((uint32_t)ppbNumber * 4U)) & 0x7U);
}

//*****************************************************************************
//
//! Clears HR_ADC event flags.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param evtFlags is a bit mask of the event source to be cleared.
//!
//! This function clears the indicated HR_ADC PPB event flags. After an event
//! occurs this function must be called to allow additional events to be
//! produced. The \e evtFlags parameter can be any of the \b HR_ADC_EVT_TRIPHI,
//! \b HR_ADC_EVT_TRIPLO, or \b HR_ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_clearPPBEventStatus(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, uint32_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Clear the specified event interrupts.
    //
    HWREG(base + HR_ADC_O_EVTCLR) |= evtFlags << ((uint32_t)ppbNumber * 3U);
}

//*****************************************************************************
//
//! Reads the processed conversion result from the PPB.
//!
//! \param resultBase is the base address of the HR_ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the processed conversion result that corresponds to
//! the base address passed into \e resultBase and the PPB passed into
//! \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (HR_ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the signed 32-bit conversion result.
//
//*****************************************************************************
static inline int32_t HR_ADC_readPPBResult(uint32_t resultBase, HR_ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT((resultBase == HR_ADCARESULT_BASE) || (resultBase == HR_ADCBRESULT_BASE)
           || (resultBase == HR_ADCCRESULT_BASE));
    //
    // Return the result of selected PPB.
    //
    return ((int32_t)HWREG(
        resultBase + (uint32_t)HR_ADC_PPBxRESULT_OFFSET_BASE + ((uint32_t)ppbNumber * 4UL)));
}

//*****************************************************************************
//
//! Reads sample delay time stamp from a PPB.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the sample delay time stamp. This delay is the number
//! of system clock cycles between the SOC being triggered and when it began
//! converting.
//!
//! \return Returns the delay time stamp.
//
//*****************************************************************************
static inline uint32_t HR_ADC_getPPBDelayTimeStamp(uint32_t base, HR_ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate delay.
    //
    ppbOffset = (HR_ADC_PPBxSTAMP_STEP * (uint32_t)ppbNumber) + HR_ADC_O_PPB1STAMP;

    //
    // Return the delay time stamp.
    //
    return (HWREG(base + ppbOffset) & HR_ADC_PPB2STAMP_DLYSTAMP_M);
}

//*****************************************************************************
//
//! Sets the post processing block offset correction.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 10-bit signed value subtracted from HR_ADC the output.
//!
//! This function sets the PPB offset correction value.  This value can be used
//! to digitally remove any system-level offset inherent in the HR_ADCIN circuit
//! before it is stored in the appropriate result register. The \e offset
//! parameter is \b subtracted from the HR_ADC output and is a signed value from
//! -512 to 511 inclusive. For example, when \e offset = 1, HR_ADCRESULT = HR_ADC
//! output - 1. When \e offset = -512, HR_ADCRESULT = HR_ADC output - (-512) or HR_ADC
//! output + 512.
//!
//! Passing a zero in to the \e offset parameter will effectively disable the
//! calculation, allowing the raw HR_ADC result to be passed unchanged into the
//! result register.
//!
//! \note If multiple PPBs are applied to the same SOC, the offset that will be
//! applied will be that of the PPB with the highest number.
//!
//! \return None
//
//*****************************************************************************
static inline void HR_ADC_setPPBCalibrationOffset(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, int16_t offset)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate offset register.
    //
    ppbOffset = (HR_ADC_PPBxOFFCAL_STEP * (uint32_t)ppbNumber) + HR_ADC_O_PPB1OFFCAL;

    //
    // Write the offset amount.
    //
    EALLOW;
    HWREG(base + ppbOffset) = (HWREG(base + ppbOffset) & ~HR_ADC_PPB1OFFCAL_OFFCAL_M)
                              | ((uint32_t)offset & HR_ADC_PPB1OFFCAL_OFFCAL_M);
    EDIS;
}

//*****************************************************************************
//
// HR ADC_setPPBTripLimits
//
//*****************************************************************************
void HR_ADC_setPPBTripLimits(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, int32_t tripHiLimit, int32_t tripLoLimit);

//*****************************************************************************
//
//! Sets the post processing block reference offset.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 16-bit unsigned value subtracted from HR_ADC the output.
//!
//! This function sets the PPB reference offset value. This can be used to
//! either calculate the feedback error or convert a unipolar signal to bipolar
//! by subtracting a reference value. The result will be stored in the
//! appropriate PPB result register which can be read using HR_ADC_readPPBResult().
//!
//! Passing a zero in to the \e offset parameter will effectively disable the
//! calculation and will pass the HR_ADC result to the PPB result register
//! unchanged.
//!
//! \note If in 12-bit mode, you may only pass a 12-bit value into the \e offset
//! parameter.
//!
//! \return None
//
//*****************************************************************************
static inline void HR_ADC_setPPBReferenceOffset(
    uint32_t base, HR_ADC_PPBNumber ppbNumber, uint32_t offset)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate offset register.
    //
    ppbOffset = (HR_ADC_PPBxOFFREF_STEP * (uint32_t)ppbNumber) + HR_ADC_O_PPB1OFFREF;

    //
    // Write the offset amount.
    //
    HWREG(base + ppbOffset) = offset;
}

//*****************************************************************************
//
//! Enables two's complement capability in the PPB.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables two's complement in the post-processing block
//! specified by the \e ppbNumber parameter. When enabled, a two's complement
//! will be performed on the output of the offset subtraction before it is
//! stored in the appropriate PPB result register. In other words, the PPB
//! result will be the reference offset value minus the the HR_ADC result value
//! (HR_ADCPPBxRESULT = HR_ADCSOCxOFFREF - HR_ADCRESULTx).
//!
//! \return None
//
//*****************************************************************************
static inline void HR_ADC_enablePPBTwosComplement(uint32_t base, HR_ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (HR_ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + HR_ADC_O_PPB1CONFIG;

    //
    // Enable PPB two's complement.
    //
    EALLOW;
    HWREG(base + ppbOffset) |= HR_ADC_PPB1CONFIG_TWOSCOMPEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables two's complement capability in the PPB.
//!
//! \param base is the base address of the HR_ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function disables two's complement in the post-processing block
//! specified by the \e ppbNumber parameter. When disabled, a two's complement
//! will \b NOT be performed on the output of the offset subtraction before it
//! is stored in the appropriate PPB result register. In other words, the PPB
//! result will be the HR_ADC result value minus the reference offset value
//! (HR_ADCPPBxRESULT = HR_ADCRESULTx - HR_ADCSOCxOFFREF).
//!
//! \return None
//
//*****************************************************************************
static inline void HR_ADC_disablePPBTwosComplement(uint32_t base, HR_ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (HR_ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + HR_ADC_O_PPB1CONFIG;

    //
    // Disable PPB two's complement.
    //
    EALLOW;
    HWREG(base + ppbOffset) &= ~HR_ADC_PPB1CONFIG_TWOSCOMPEN;
    EDIS;
}

//*****************************************************************************
//
//! Enables an HR_ADC interrupt source.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function enables the indicated HR_ADC interrupt source.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! \e HR_ADCIntNum can take the value \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to express
//! which of the four interrupts of the HR_ADC module should be enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_enableInterrupt(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    uint32_t intRegAddr;
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    // intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE + (((uint32_t)HR_ADCIntNum >> 1)*4U);
    // shiftVal   = ((uint32_t)HR_ADCIntNum & 0x1U) << 3U;
    intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE;
    shiftVal   = (uint32_t)HR_ADCIntNum << 3U;
    //
    // Enable the specified HR_ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) |= HR_ADC_INTSEL1N2_INT1E << shiftVal;

    EDIS;
}

//*****************************************************************************
//
//! Disables an HR_ADC interrupt source.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function disables the indicated HR_ADC interrupt source.
//! Only the sources that are enabled can be reflected to the processor
//! interrupt. Disabled sources have no effect on the processor.
//!
//! \e HR_ADCIntNum can take the value \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to express
//! which of the four interrupts of the HR_ADC module should be disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_disableInterrupt(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    uint32_t intRegAddr;
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    // intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)HR_ADCIntNum >> 1);
    // shiftVal   = ((uint32_t)HR_ADCIntNum & 0x1U) << 3U;
    intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE;
    shiftVal   = (uint32_t)HR_ADCIntNum << 3U;
    //
    // Disable the specified HR_ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) &= ~(HR_ADC_INTSEL1N2_INT1E << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Sets the source EOC for an analog-to-digital converter interrupt.
//!
//! \param base is the base address of the HR_ADC module.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function sets which conversion is the source of an HR_ADC interrupt.
//!
//! The \e intTrigger number is a value \b HR_ADC_INT_TRIGGER_X where X specifies
//! the interrupt trigger to be configured for the HR_ADC module specified by
//! \e base. Refer \b HR_ADC_IntTrigger enum for valid values for this input.
//!
//! \e HR_ADCIntNum can take the value \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to express
//! which of the four interrupts of the HR_ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_setInterruptSource(
    uint32_t base, HR_ADC_IntNumber HR_ADCIntNum, uint32_t intTrigger)
{
    uint32_t intRegAddr;
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));
    ASSERT(intTrigger < 20U);

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    // intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE + (((uint32_t)HR_ADCIntNum >> 1)*4U);
    // shiftVal   = ((uint32_t)HR_ADCIntNum & 0x1U) << 3U;
    intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE;
    shiftVal   = (uint32_t)HR_ADCIntNum * 8U;

    //
    // Set the specified HR_ADC interrupt source.
    //
    EALLOW;

    HWREG(intRegAddr) = (HWREG(intRegAddr) & ~(HR_ADC_INTSEL1N2_INT1SEL_M << shiftVal))
                        | ((uint32_t)intTrigger << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Enables continuous mode for an HR_ADC interrupt.
//!
//! \param base is the base address of the HR_ADC.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function enables continuous mode for the HR_ADC interrupt passed into
//! \e HR_ADCIntNum. This means that pulses will be generated for the specified
//! HR_ADC interrupt whenever an EOC pulse is generated irrespective of whether or
//! not the flag bit is set.
//!
//! \e HR_ADCIntNum can take the value \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to express
//! which of the four interrupts of the HR_ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_enableContinuousMode(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    uint32_t intRegAddr;
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    // intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE + (((uint32_t)HR_ADCIntNum >> 1)*4U);
    // shiftVal   = ((uint32_t)HR_ADCIntNum & 0x1U) << 3U;
    intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE;
    shiftVal   = (uint32_t)HR_ADCIntNum << 3U;

    //
    // Enable continuous mode for the specified HR_ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) |= HR_ADC_INTSEL1N2_INT1CONT << shiftVal;

    EDIS;
}

//*****************************************************************************
//
//! Disables continuous mode for an HR_ADC interrupt.
//!
//! \param base is the base address of the HR_ADC.
//! \param HR_ADCIntNum is interrupt number within the HR_ADC wrapper.
//!
//! This function disables continuous mode for the HR_ADC interrupt passed into
//! \e HR_ADCIntNum. This means that pulses will not be generated for the
//! specified HR_ADC interrupt until the corresponding interrupt flag for the
//! previous interrupt occurrence has been cleared using
//! HR_ADC_clearInterruptStatus().
//!
//! \e HR_ADCIntNum can take the value \b HR_ADC_INT_NUMBER1,
//! \b HR_ADC_INT_NUMBER2, \b HR_ADC_INT_NUMBER3 or \b HR_ADC_INT_NUMBER4 to express
//! which of the four interrupts of the HR_ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void HR_ADC_disableContinuousMode(uint32_t base, HR_ADC_IntNumber HR_ADCIntNum)
{
    uint32_t intRegAddr;
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(HR_ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    // intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE + (((uint32_t)HR_ADCIntNum >> 1)*4U);
    // shiftVal   = ((uint32_t)HR_ADCIntNum & 0x1U) << 3U;
    intRegAddr = base + HR_ADC_INTSELxNy_OFFSET_BASE;
    shiftVal   = (uint32_t)HR_ADCIntNum << 3U;

    //
    // Disable continuous mode for the specified HR_ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) &= ~(HR_ADC_INTSEL1N2_INT1CONT << shiftVal);

    EDIS;
}

//
// HR_ADC_SAFECHECK_REGS
//*****************************************************************************
//
//! \internal
//! Checks the Safety Checker base address.
//!
//! \param base specifies the HR_ADC Safety Checker module base address.
//!
//! This function determines if a HR_ADC Safety Checker module base address is
//! valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************

// static inline bool HR_ADC_isSafetyCheckerBaseValid(uint32_t base)
//{
//     return ((base == HR_ADCSAFETYCHK1_BASE) || (base == HR_ADCSAFETYCHK2_BASE)
//             || (base == HR_ADCSAFETYCHK3_BASE) || (base == HR_ADCSAFETYCHK4_BASE)
//             || (base == HR_ADCSAFETYCHK5_BASE) || (base == HR_ADCSAFETYCHK6_BASE)
//             || (base == HR_ADCSAFETYCHK7_BASE) || (base == HR_ADCSAFETYCHK8_BASE));
// }
// #endif

//
// HR_ADC_SAFECHECK_INTEVT_REGS
//*****************************************************************************
//
//! \internal
//! Checks the Safety Checker INTEVT base address.
//!
//! \param base specifies the HR_ADC Safety Checker INTEVT module base address.
//!
//! This function determines if a HR_ADC Safety Checker INTEVT module base address
//! is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
// static inline bool HR_ADC_isSafeCheckINTEVTBaseValid(uint32_t base)
//{
//    return ((base == HR_ADCSAFETYINTEVTAGG1_BASE) || (base == HR_ADCSAFETYINTEVTAGG2_BASE));
//}
// #endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif
