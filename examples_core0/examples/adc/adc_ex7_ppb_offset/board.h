#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
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

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define myADC0_BASE                ADCA_BASE
#define myADC0_RESULT_BASE         ADCARESULT_BASE
#define myADC0_SOC0                ADC_SOC_NUMBER0
#define myADC0_FORCE_SOC0          ADC_FORCE_SOC0
#define myADC0_SAMPLE_WINDOW_SOC0  80
#define myADC0_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_SW_ONLY
#define myADC0_CHANNEL_SOC0        ADC_CH_ADCIN2
#define myADC0_SOC1                ADC_SOC_NUMBER1
#define myADC0_FORCE_SOC1          ADC_FORCE_SOC1
#define myADC0_SAMPLE_WINDOW_SOC1  80
#define myADC0_TRIGGER_SOURCE_SOC1 ADC_TRIGGER_SW_ONLY
#define myADC0_CHANNEL_SOC1        ADC_CH_ADCIN2
#define myADC0_PPB1                ADC_PPB_NUMBER1
#define myADC0_SOC_PPB1            ADC_SOC_NUMBER1
void myADC0_init();

#define myADC1_BASE                ADCC_BASE
#define myADC1_RESULT_BASE         ADCCRESULT_BASE
#define myADC1_SOC0                ADC_SOC_NUMBER0
#define myADC1_FORCE_SOC0          ADC_FORCE_SOC0
#define myADC1_SAMPLE_WINDOW_SOC0  80
#define myADC1_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_SW_ONLY
#define myADC1_CHANNEL_SOC0        ADC_CH_ADCIN2
#define myADC1_SOC1                ADC_SOC_NUMBER1
#define myADC1_FORCE_SOC1          ADC_FORCE_SOC1
#define myADC1_SAMPLE_WINDOW_SOC1  80
#define myADC1_TRIGGER_SOURCE_SOC1 ADC_TRIGGER_SW_ONLY
#define myADC1_CHANNEL_SOC1        ADC_CH_ADCIN2
#define myADC1_PPB1                ADC_PPB_NUMBER1
#define myADC1_SOC_PPB1            ADC_SOC_NUMBER1
void myADC1_init();

//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void Board_init();
void ADC_init();
void ASYSCTL_init();
void PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
