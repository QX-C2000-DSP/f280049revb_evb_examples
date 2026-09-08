/*
 * bspadc.c
 *
 *  Created on: 2024 Aug 22
 *      Author: QX2000
 */
#include "board.h"

static void AdcIsrIoInitial(void);
static void AdcSocSwInitial(void);
static void AdcSocTimerInitial(void);
static void AdcTimerInitial(void);
static void AdcSocEpwmInitial(void);
static void AdcEpwmInitial(void);

__interrupt void adca1_isr(void);

void AdcInitial(void)
{
    AdcIsrIoInitial();
#if defined(ADCSOCSOFTWARE)
    AdcSocSwInitial();
#elif defined(ADCSOCTIMER)
    AdcSocTimerInitial();
    AdcTimerInitial();
#elif defined(ADCSOCEPWM)
    AdcSocEpwmInitial();
    AdcEpwmInitial();
#endif
}

static void AdcIsrIoInitial(void)
{
    GPIO_setPinConfig(0);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(0, GPIO_QUAL_ASYNC);
    GPIO_writePin(0, 1);
}

static void AdcSocSwInitial(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);

    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIA);
    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIB);
    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(500);
    ADC_setPrescaler(ADCA_BASE, 0x02);
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setupSOC(
        ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_10);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, 0x00);
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);
    Interrupt_enable(INT_ADCA1);
    Interrupt_register(INT_ADCA1, adca1_isr);
}

static void AdcSocTimerInitial(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);

    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIA);
    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIB);
    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(500);
    ADC_setPrescaler(ADCA_BASE, 0x02);
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setupSOC(
        ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_CPU1_TINT0, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_10);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, 0x00);
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);
    Interrupt_enable(INT_ADCA1);
    Interrupt_register(INT_ADCA1, adca1_isr);
}

static void AdcTimerInitial(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);

    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_setPeriod(CPUTIMER0_BASE, ADCTIMERPERIOD);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_startTimer(CPUTIMER0_BASE);
}

static void AdcSocEpwmInitial(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);

    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIA);
    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIB);
    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(500);
    ADC_setPrescaler(ADCA_BASE, 0x02);
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setupSOC(
        ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, ADC_SAMPLE_WINDOW_10);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, 0x00);
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);
    Interrupt_enable(INT_ADCA1);
    Interrupt_register(INT_ADCA1, adca1_isr);
}

static void AdcEpwmInitial(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    EPWM_setTimeBasePeriod(EPWM1_BASE, ADCEPWMPERIOD);
    EPWM_setPhaseShift(EPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(EPWM1_BASE);

    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_PERIOD);
    // EPWM_enableInterrupt(EPWM1_BASE);
    EPWM_setInterruptEventCount(EPWM1_BASE, 1U);
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
    // Interrupt_enable(INT_EPWM1);

    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_PERIOD);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

__interrupt void adca1_isr(void)
{
    uint32_t adcData = 0x00;

    GPIO_togglePin(0);
    if (ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
        adcData = (uint32_t)((struct ADC_RESULT_REGS *)ADCARESULT_BASE)->ADCRESULT0 & 0xFFFF;
    }
    if (ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2))
    {
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);
    }
    if (ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3))
    {
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3);
    }
    if (ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4))
    {
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4);
    }
}
