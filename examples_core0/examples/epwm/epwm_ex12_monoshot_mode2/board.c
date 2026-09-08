
#include "board.h"

//*****************************************************************************
//
// Board Configurations
// 功能：EPWM边沿触发100ns脉冲生成
// - GPIO0 (EPWM1A): EPWM4A上升沿触发100ns脉冲
// - GPIO2 (EPWM2A): EPWM4A下降沿触发100ns脉冲
// - GPIO6 (EPWM4A): 触发信号源
// - GPIO3 (OUTPUTXBAR2): 调试用反相信号输出
//
//*****************************************************************************
void Board_init()
{
    EALLOW;

    PinMux_init();
    INPUTXBAR_init();
    OUTPUTXBAR_init();
    EPWMXBAR_init();
    EPWM_init();

    EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
// 引脚复用配置
//
//*****************************************************************************
void PinMux_init()
{
    //
    // GPIO0 (EPWM1A) - Rising edge 100ns pulse output
    //
    GPIO_setPinConfig(GPIO_0_EPWM1_A);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

    //
    // GPIO2 (EPWM2A) - Falling edge 100ns pulse output
    //
    GPIO_setPinConfig(GPIO_2_EPWM2_A);
    GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);

    //
    // GPIO6 (EPWM4A) - Trigger signal output
    //
//    GPIO_setPinConfig(GPIO_6_EPWM4_A);
//    GPIO_setDirectionMode(6, GPIO_DIR_MODE_OUT);
//    GPIO_setPadConfig(6, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_6_GPIO6);
    GPIO_setDirectionMode(6, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(6, GPIO_PIN_TYPE_STD);

    //
    // GPIO3 - OUTPUTXBAR2 for debugging (inverted INPUTXBAR5)
    //
    GPIO_setPinConfig(GPIO_3_OUTPUTXBAR2);
    GPIO_setDirectionMode(3, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
}

//*****************************************************************************
//
// EPWM Configurations
// EPWM模块配置：EPWM1/EPWM2输出100ns脉冲，EPWM4产生触发信号
//
//*****************************************************************************
void EPWM_init()
{

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);

    //
    // EPWM1配置：EPWM4A上升沿触发100ns脉冲输出到GPIO0
    // SYNCIN源：EPWM4 SYNCOUT (SEL=24)
    // TBPRD=9 (100MHz时钟下100ns = 10个时钟周期 - 1)
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 9);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 9); // Start at PERIOD (stopped)
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setActionQualifierT1TriggerSource(EPWM1_BASE, EPWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN);
    EPWM_enablePhaseShiftLoad(EPWM1_BASE);
    EPWM_setPhaseShift(EPWM1_BASE, 0);

    EALLOW;

    EPwm1Regs.EPWMSYNCINSEL.bit.SEL = 24;
    EDIS;

    //
    // EPWM1A动作限定器配置
    // T1事件(SYNCIN上升沿): 输出HIGH
    // PERIOD事件: 输出LOW
    //
    EPWM_setActionQualifierAction(
        EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(
        EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);

    //
    // EPWM2配置：EPWM4A下降沿触发100ns脉冲输出到GPIO2
    // SYNCIN源：EXTSYNCIN2 (SEL=25)，连接到GPIO3（反相后的EPWM4A）
    // 反相信号的上升沿 = 原始信号的下降沿
    //
    EPWM_setClockPrescaler(EPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM2_BASE,  13);
    EPWM_setTimeBaseCounter(EPWM2_BASE, 13);
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setActionQualifierT1TriggerSource(EPWM2_BASE, EPWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN);
    EPWM_enablePhaseShiftLoad(EPWM2_BASE);
    EPWM_setPhaseShift(EPWM2_BASE, 0);

    //
    // EPWM2 SYNCIN源配置：EXTSYNCIN2 (SEL=25)
    // 信号路径：GPIO3 -> INPUTXBAR6 -> EXTSYNCIN2 -> EPWM2 SYNCIN
    //
    EALLOW;
    EPwm2Regs.EPWMSYNCINSEL.bit.SEL = 25;  // EXTSYNCIN2
    EDIS;

    //
    // EPWM2A动作限定器配置
    // T1事件(SYNCIN上升沿): 输出HIGH
    // PERIOD事件: 输出LOW
    //
    EPWM_setActionQualifierAction(
        EPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(
        EPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_T1_COUNT_UP);

//    EPWM_setClockPrescaler(EPWM4_BASE, EPWM_CLOCK_DIVIDER_64, EPWM_HSCLOCK_DIVIDER_1);
//    EPWM_setTimeBasePeriod(EPWM4_BASE, 1560);
//    EPWM_setTimeBaseCounter(EPWM4_BASE, 0); // Start at PERIOD (stopped)
//    EPWM_setTimeBaseCounterMode(EPWM4_BASE, EPWM_COUNTER_MODE_UP);
//    EPWM_setCounterCompareValue(EPWM4_BASE, EPWM_COUNTER_COMPARE_A, 16);
//    EPWM_setCounterCompareShadowLoadMode(
//        EPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
//
//    // EPWM4A动作限定器：ZERO时HIGH，CMPA时LOW
//
//    EPWM_setActionQualifierAction(
//        EPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
//    EPWM_setActionQualifierAction(
//        EPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
//    EPWM_setActionQualifierAction(
//        EPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
// 输入交叉开关配置
//
//*****************************************************************************
void INPUTXBAR_init()
{
    // INPUTXBAR5: GPIO6 (EPWM4A) -> EXTSYNCIN1
    XBAR_setInputPin(XBAR_INPUT5, 6);

    // INPUTXBAR6: GPIO3 (反相EPWM4A) -> EXTSYNCIN2
    XBAR_setInputPin(XBAR_INPUT6, 3);
}

//*****************************************************************************
//
// OUTPUTXBAR Configurations
// 输出交叉开关配置：将反相的EPWM4A信号输出到GPIO3
//
//*****************************************************************************
void OUTPUTXBAR_init()
{
    // OUTPUTXBAR2: INPUTXBAR5反相后输出到GPIO3
    // GPIO3信号用于EXTSYNCIN2，实现下降沿检测
    XBAR_setOutputMuxConfig(XBAR_OUTPUT2, XBAR_OUT_MUX09_INPUTXBAR5);
    XBAR_enableOutputMux(XBAR_OUTPUT2, XBAR_MUX09);
    XBAR_invertOutputSignal(XBAR_OUTPUT2, true);
}

//*****************************************************************************
//
// EPWM XBAR Configurations
// EPWM交叉开关配置（预留，当前未使用）
//
//*****************************************************************************
void EPWMXBAR_init()
{
    // TRIP5: INPUTXBAR5反相（预留配置）
    XBAR_setEPWMMuxConfig(XBAR_TRIP5, XBAR_EPWM_MUX09_INPUTXBAR5);
    XBAR_enableEPWMMux(XBAR_TRIP5, XBAR_MUX09);
    XBAR_invertEPWMSignal(XBAR_TRIP5, true);
}
