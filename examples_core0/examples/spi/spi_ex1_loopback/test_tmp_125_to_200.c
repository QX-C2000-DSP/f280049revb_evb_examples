#include "subcommon.h"

//SPI IO CFG
#define SPIA_PIN_CSn    5
#define SPIA_PIN_SCK    9
#define SPIA_PIN_MOSI   16
#define SPIA_PIN_MISO   17

#define SPIA_CFG_CSn    GPIO_5_GPIO5
#define SPIA_CFG_SCK    GPIO_9_SPIA_CLK
#define SPIA_CFG_MOSI   GPIO_16_SPIA_SIMO
#define SPIA_CFG_MISO   GPIO_17_SPIA_SOMI

#define SPIA_CS(val)    GPIO_writePin(SPIA_PIN_CSn, val)

//SPI CFG
//#define SPIA_BASE       (u32) & SpiaRegs
#define SPIA_RATE       10000000
#define SPIA_DATAWIDTH  16

#define EPWM_NUM 12// 定义EPWM通道总是数量

#define EPWM_BASE(x) (EPWM1_BASE + (x)*0x200)
uint16_t i=0;
void SPI_BUS_init(void)
{
    //enable SPIA clock
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

        // IO MUX
        //GPIO_MuxConfig(SPIA_PIN_CSn,  SPIA_CFG_CSn,  GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
        GPIO_MuxConfig(SPIA_PIN_SCK,  SPIA_CFG_SCK,  GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
        GPIO_MuxConfig(SPIA_PIN_MOSI, SPIA_CFG_MOSI, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
        GPIO_MuxConfig(SPIA_PIN_MISO, SPIA_CFG_MISO, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

        GPIO_setPinConfig(SPIA_CFG_CSn);
        GPIO_setPadConfig(SPIA_PIN_CSn, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(SPIA_PIN_CSn, GPIO_QUAL_ASYNC);
        GPIO_setDirectionMode(SPIA_PIN_CSn, GPIO_DIR_MODE_OUT);

        // SPI CFG
          // Disable the SPI0 module before configuring
        SPI_disableModule(SPIA_BASE);

        // Set the SPI0 configuration (LSPCLK frequency, polarity, phase, mode, bitrate, data width)
        SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL1PHA0, SPI_MODE_CONTROLLER,
                SPIA_RATE, SPIA_DATAWIDTH);

        // Set the polarity for the PTE signal (active low)
        SPI_setPTESignalPolarity(SPIA_BASE, SPI_PTE_ACTIVE_LOW);

        SPI_enableFIFO(SPIA_BASE);
        HWREGH(SPIA_BASE + SPI_O_FFRX) = (HWREGH(SPIA_BASE + SPI_O_FFRX) & (~SPI_FFRX_RXFFIL_M)) | 1;
        HWREGH(SPIA_BASE + SPI_O_FFRX) |= SPI_FFRX_RXFFIENA;
        HWREGH(SPIA_BASE + SPI_O_FFRX) |= SPI_FFRX_RXFFINTCLR;

        SPI_disableLoopback(SPIA_BASE);

        // Enable the SPI0 module after configuration
        SPI_enableModule(SPIA_BASE);

        SPIA_CS(1);
}

void SPI_BUS_write(unsigned short ADR,unsigned short DAT)
{
    SPIA_CS(0);

    while (SPI_getTxFIFOStatus(SPIA_BASE) != SPI_FIFO_TXEMPTY);
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = ADR | 0x8000;
    while ((HWREGH(SPIA_BASE + SPI_O_FFRX) & SPI_FFRX_RXFFINT) == 0);
    HWREGH(SPIA_BASE + SPI_O_RXBUF);
    HWREGH(SPIA_BASE + SPI_O_FFRX) |= SPI_FFRX_RXFFINTCLR;


    while (SPI_getTxFIFOStatus(SPIA_BASE) != SPI_FIFO_TXEMPTY);
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = DAT;
    while ((HWREGH(SPIA_BASE + SPI_O_FFRX) & SPI_FFRX_RXFFINT) == 0);
    HWREGH(SPIA_BASE + SPI_O_RXBUF);
    HWREGH(SPIA_BASE + SPI_O_FFRX) |= SPI_FFRX_RXFFINTCLR;

    SPIA_CS(1);
}

void SPI_BUS_read(unsigned short ADR,unsigned short DAT)
{
    SPIA_CS(0);

    while (SPI_getTxFIFOStatus(SPIA_BASE) != SPI_FIFO_TXEMPTY);
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = ADR & 0x7FFF;
    while ((HWREGH(SPIA_BASE + SPI_O_FFRX) & SPI_FFRX_RXFFINT) == 0);
    HWREGH(SPIA_BASE + SPI_O_RXBUF);
    HWREGH(SPIA_BASE + SPI_O_FFRX) |= SPI_FFRX_RXFFINTCLR;

    while (SPI_getTxFIFOStatus(SPIA_BASE) != SPI_FIFO_TXEMPTY);
    HWREGH(SPIA_BASE + SPI_O_TXBUF) = 0x0000;
    while ((HWREGH(SPIA_BASE + SPI_O_FFRX) & SPI_FFRX_RXFFINT) == 0);
    DAT = HWREGH(SPIA_BASE + SPI_O_RXBUF);
    HWREGH(SPIA_BASE + SPI_O_FFRX) |= SPI_FFRX_RXFFINTCLR;

    SPIA_CS(1);
}
// ==============================================================================================
// 注: TBCLK = SYSTEM_OUT_CLK/( (2 * HSPCLKDIV) * (2^CLKDIV))
// 默认TBPRD的影子寄存器功能会启用且PRDLDSYNC=0(在TBCTR=0时重载)
// PHSDIR只在上下计数模式下有效, 默认为在上下计数的向下计数方向上载入相移值
// SYNCSEL默认为0, 表示模块的同步输出信号同步于EPWMxSYNCI/SWFSYNC
void pwm_tb_cfg(
    u8 ch, EPWM_TimeBaseCountMode ctrmode, u16 tbprd, u8 clkdiv, u8 hsclkdiv, u8 phsen, u16 tbphs)
{
#ifdef USE_BIT_FIELD
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)EPWM_BASE(ch);

    epwm->TBCTL.bit.CTRMODE   = ctrmode;
    epwm->TBPRD               = tbprd;
    epwm->TBCTL.bit.CLKDIV    = clkdiv;
    epwm->TBCTL.bit.HSPCLKDIV = hsclkdiv;
    epwm->TBCTR               = 0;
    epwm->TBPHS.bit.TBPHS     = tbphs;
    epwm->TBCTL.bit.PHSEN     = phsen;
#else
    uint32_t epwm_base = EPWM_BASE(ch);

    EPWM_setTimeBaseCounterMode(epwm_base, ctrmode);     // 计数模式
    EPWM_setTimeBasePeriod(epwm_base, tbprd);            // 时基周期设置
    EPWM_setClockPrescaler(epwm_base, clkdiv, hsclkdiv); // 设置TB的分频系数
    EPWM_setTimeBaseCounter(epwm_base, 0);               // 清零时基计数寄存器
    EPWM_setPhaseShift(epwm_base, tbphs);                // 相位偏移
    if (phsen)
        EPWM_enablePhaseShiftLoad(epwm_base);
    else
        EPWM_disablePhaseShiftLoad(epwm_base);
#endif
}

void pwm_cc_cfg(u8 ch, u16 cmpa, u16 cmpb, u16 cmpc, u16 cmpd, EPWM_CounterCompareLoadMode modea,
    EPWM_CounterCompareLoadMode modeb, EPWM_CounterCompareLoadMode modec,
    EPWM_CounterCompareLoadMode moded)
{
#ifdef USE_BIT_FIELD
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)EPWM_BASE(ch);

    epwm->CMPCTL.bit.LOADAMODE  = modea & 3;
    epwm->CMPCTL.bit.LOADASYNC  = modea >> 2;
    epwm->CMPCTL.bit.LOADBMODE  = modeb & 3;
    epwm->CMPCTL.bit.LOADBSYNC  = modeb >> 2;
    epwm->CMPCTL2.bit.LOADCMODE = modec & 3;
    epwm->CMPCTL2.bit.LOADCSYNC = modec >> 2;
    epwm->CMPCTL2.bit.LOADDMODE = moded & 3;
    epwm->CMPCTL2.bit.LOADCSYNC = moded >> 2;
    epwm->CMPA.bit.CMPA         = cmpa;
    epwm->CMPB.bit.CMPB         = cmpb;
    epwm->CMPC                  = cmpc;
    epwm->CMPD                  = cmpd;
#else
    uint32_t epwm_base = EPWM_BASE(ch);

    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_A, modea);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_B, modeb);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_C, modec);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_D, moded);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, cmpa);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_B, cmpb);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_C, cmpc);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_D, cmpd);
#endif
}

// a_cau: 当CTR=CMPA且增计数时，EPWM1A输出动作, a_cad: 当CTR=CMPA且减计数时，EPWM1A输出动作
// b_cau: 当CTR=CMPA且增计数时，EPWM1B输出动作, b_cad: 当CTR=CMPA且减计数时，EPWM1B输出动作
void pwm_aq_cmpa_cfg(u8 ch, EPWM_ActionQualifierOutput a_cau, EPWM_ActionQualifierOutput a_cad,
    EPWM_ActionQualifierOutput b_cau, EPWM_ActionQualifierOutput b_cad)
{
#ifdef USE_BIT_FIELD
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)EPWM_BASE(ch);

    epwm->AQCTLA.bit.CAU = a_cau;
    epwm->AQCTLA.bit.CAD = a_cad;
    epwm->AQCTLB.bit.CAU = b_cau;
    epwm->AQCTLB.bit.CAD = b_cad;
#else
    uint32_t epwm_base = EPWM_BASE(ch);

    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, a_cau, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, a_cad, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, b_cau, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, b_cad, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
#endif
}

// a_cbu: 当CTR=CMPA且增计数时，EPWM1A输出动作, a_cbd: 当CTR=CMPA且减计数时，EPWM1A输出动作
// b_cbu: 当CTR=CMPA且增计数时，EPWM1B输出动作, b_cbd: 当CTR=CMPA且减计数时，EPWM1B输出动作
void pwm_aq_cmpb_cfg(u8 ch, EPWM_ActionQualifierOutput a_cbu, EPWM_ActionQualifierOutput a_cbd,
    EPWM_ActionQualifierOutput b_cbu, EPWM_ActionQualifierOutput b_cbd)
{
#ifdef USE_BIT_FIELD
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)EPWM_BASE(ch);

    epwm->AQCTLA.bit.CBU = a_cbu;
    epwm->AQCTLA.bit.CBD = a_cbd;
    epwm->AQCTLB.bit.CBU = b_cbu;
    epwm->AQCTLB.bit.CBD = b_cbd;
#else
    uint32_t epwm_base = EPWM_BASE(ch);

    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, a_cbu, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, a_cbd, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, b_cbu, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, b_cbd, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
#endif
}

// 只配置EPWMxA输出动作
// zro/prd/cau/cad/cbu/cbd值: 0-不变；1-拉低；2-拉高；3-翻转
// 上升下降模式下优先级：SOFT>T1U>T2U>CBU>CAU>ZRO>T1D>T2D>CBD>CAD
// 上升模式下优先级：SOFT>PRD>T1U>T2U>CBU>CAU>ZRO
// 下降模式下优先级：SOFT>ZRO>T1D>T2D>CBD>CAD>PRD
void pwm_aq_only_cmpa_cfg(u8 ch, EPWM_ActionQualifierOutput zro, EPWM_ActionQualifierOutput prd,
    EPWM_ActionQualifierOutput cau, EPWM_ActionQualifierOutput cad, EPWM_ActionQualifierOutput cbu,
    EPWM_ActionQualifierOutput cbd)
{
#ifdef USE_BIT_FIELD
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)EPWM_BASE(ch);

    epwm->AQCTLA.bit.ZRO = zro;
    epwm->AQCTLA.bit.PRD = prd;
    epwm->AQCTLA.bit.CAU = cau;
    epwm->AQCTLA.bit.CAD = cad;
    epwm->AQCTLA.bit.CBU = cbu;
    epwm->AQCTLA.bit.CBD = cbd;
#else
    uint32_t epwm_base = EPWM_BASE(ch);

    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, zro, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, prd, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, cau, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, cad, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, cbu, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, cbd, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
#endif
}

// 只配置EPWMxB输出动作
// zro/prd/cau/cad/cbu/cbd值: 0-不变；1-拉低；2-拉高；3-翻转
// 上升下降模式下优先级：SOFT>T1U>T2U>CBU>CAU>ZRO>T1D>T2D>CBD>CAD
// 上升模式下优先级：SOFT>PRD>T1U>T2U>CBU>CAU>ZRO
// 下降模式下优先级：SOFT>ZRO>T1D>T2D>CBD>CAD>PRD
void pwm_aq_only_cmpb_cfg(u8 ch, EPWM_ActionQualifierOutput zro, EPWM_ActionQualifierOutput prd,
    EPWM_ActionQualifierOutput cau, EPWM_ActionQualifierOutput cad, EPWM_ActionQualifierOutput cbu,
    EPWM_ActionQualifierOutput cbd)
{
#ifdef USE_BIT_FIELD
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)EPWM_BASE(ch);

    epwm->AQCTLB.bit.ZRO = zro;
    epwm->AQCTLB.bit.PRD = prd;
    epwm->AQCTLB.bit.CAU = cau;
    epwm->AQCTLB.bit.CAD = cad;
    epwm->AQCTLB.bit.CBU = cbu;
    epwm->AQCTLB.bit.CBD = cbd;
#else
    uint32_t epwm_base = EPWM_BASE(ch);

    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, zro, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, prd, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, cau, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, cad, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, cbu, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, cbd, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
#endif
}

// a_zro: 当CTR=0时，EPWM1A输出动作, a_prd: 当CTR=PRD时，EPWM1A输出动作
// b_zro: 当CTR=0时，EPWM1B输出动作, b_prd: 当CTR=PRD时，EPWM1B输出动作
void pwm_aq_zro_prd_cfg(u8 ch, EPWM_ActionQualifierOutput a_zro, EPWM_ActionQualifierOutput a_prd,
    EPWM_ActionQualifierOutput b_zro, EPWM_ActionQualifierOutput b_prd)
{
#ifdef USE_BIT_FIELD
    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)EPWM_BASE(ch);

    epwm->AQCTLA.bit.ZRO = a_zro;
    epwm->AQCTLA.bit.PRD = a_prd;
    epwm->AQCTLB.bit.ZRO = b_zro;
    epwm->AQCTLB.bit.PRD = b_prd;
#else
    uint32_t epwm_base = EPWM_BASE(ch);

    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, a_zro, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, a_prd, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, b_zro, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, b_prd, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
#endif
}
void epwm_gpio_init()
{
    GPIO_MuxConfig(0, GPIO_0_EPWM1_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(1, GPIO_1_EPWM1_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(2, GPIO_2_EPWM2_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(3, GPIO_3_EPWM2_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(4, GPIO_4_EPWM3_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(5, GPIO_5_EPWM3_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(6, GPIO_6_EPWM4_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(7, GPIO_7_EPWM4_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(8, GPIO_8_EPWM5_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(9, GPIO_9_EPWM5_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(10, GPIO_10_EPWM6_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(11, GPIO_11_EPWM6_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
//    GPIO_MuxConfig(12, GPIO_12_EPWM7_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(13, GPIO_13_EPWM7_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(14, GPIO_14_EPWM8_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(15, GPIO_15_EPWM8_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(30, GPIO_30_EPWM9_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(31, GPIO_31_EPWM9_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(39, GPIO_39_EPWM10_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(40, GPIO_40_EPWM10_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(56, GPIO_56_EPWM11_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(57, GPIO_57_EPWM11_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(58, GPIO_58_EPWM12_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    //GPIO_MuxConfig(59, GPIO_59_EPWM12_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
}

short adc_result = 0;
float vt = 0, tmp = 0;
uint16_t num=0;
void test_temp(u32 adj_td_os, u32 adj_td_ga, u32 adj_vout, u32 adj_vref)
{
    HWREG(REGFILE_BASE + 0x24) = 0x55AA55AA; // 解除trim锁定
    HWREG(REGFILE_BASE)
        = (0x22222110 & ~(0xF << 18) | (adj_vout << 18)) & ~(0xF << 22) | (adj_vref << 22);
    HWREG(REGFILE_BASE + 0x4)
        = (0x880000 & ~(0xF << 16) | adj_td_os << 16) & ~(0xF << 20) | adj_td_ga << 20;
    HWREG(REGFILE_BASE + 0x8)  = 0x1CFCE; // 设置REGFILE第三个寄存器为默认值
    HWREG(REGFILE_BASE + 0x20) = 1;       // 使能trim功能

    ADC_setPrescaler(ADCB_BASE, ADC_CLK_DIV_4_0);
    ASysCtl_enableTemperatureSensor();               // 开启温度传感器
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB); // 使能ADCB的数字部分的时钟
    ADC_enableConverter(ADCB_BASE);                  // 使能ADCB IP
    simple_delay(200);                               // 上电稳定
    // 使用内部参考电压, 方便测试
    ADC_setVREF(ADCB_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);
    /* 配置ADC的输入为 VIN15 (温度传感器)，结果寄存器为NUMBER0 */
    ADC_setupSOC(
        ADCB_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN14, ADC_SAMPLE_WINDOW_80);

    while (1)
    {
        DEVICE_DELAY_US(500000);
        num=num+1;
        ADC_forceMultipleSOC(ADCB_BASE, 0x1); // 软件触发adc开始转化
        DEVICE_DELAY_US(1000);
        adc_result = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0); // 读取转化结果
        vt         = (float)adc_result / 4095 * 3.3;
        tmp        = (vt - 1.1) / 0.006;
        // 这里打印的结果为采集到的温度传感器的电压值并非温度值
        printf("adc_result: %d, V: %f T:%f,num=%d\n", adc_result, vt, tmp,num);
    }
}

void flash_test(u32 sectors_count)
{
    puts("flash test");
    Flash_initModule(1, 1);

    int i, sector, base, val;

    for (sector = 0; sector < sectors_count; sector++)
    {
        if (sector == 4)
        {
            continue;
        }
        base = FLASH0DATA_BASE + 4096 * sector;

        printf("sector %d test...\n", sector);
        Flash_eraseSector(sector);
        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != 0xFFFFFFFF)
            {
                printf("erase check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
                board_led_blink_fast();
            }
        }

        for (i = 0; i < 1024; i++)
            Flash_writeWord(base + i * 4, sector * i);

        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != sector * i)
            {
                printf("flash write check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
                board_led_blink_fast();
            }
        }

        Flash_eraseSector(sector); // 最后记得要重新擦除一下
        for (i = 0; i < 1024; i++)
        {
            val = Flash_readWord(base + i * 4);
            if (val != 0xFFFFFFFF)
            {
                printf("erase check error:sector=%d, idx=%x, val=%x\n", sector, i, val);
                board_led_blink_fast();
            }
        }
    }
}

void tests_core0()
{
//    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPU2);
//    GPIO_setPadConfig(33, GPIO_PIN_TYPE_STD);
//    GPIO_setDirectionMode(33, GPIO_DIR_MODE_OUT);
//
//    epwm_gpio_init(); // 使能所有EWPM的IO口
//
//    for (int i = 0; i < EPWM_NUM; i++) // 使能所有EPWM时钟
//        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (i << 8));
//
//    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
//
//    for (int i = 0; i < EPWM_NUM; i++)
//    {
//        pwm_tb_cfg(i, EPWM_COUNTER_MODE_UP, 9999, 1, 1, 0, 0);
//        pwm_aq_zro_prd_cfg(i, 3, 0, 3, 0);
//    }
//    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
//    EPWM_forceSyncPulse(EPWM_BASE(0));
//    EPWM_forceSyncPulse(EPWM_BASE(3));
//    EPWM_forceSyncPulse(EPWM_BASE(6));
//    EPWM_forceSyncPulse(EPWM_BASE(9));
    //test_temp(0b1000, 0b1000, 0b1111, 0b1000);
    //DEVICE_DELAY_US(500);
    SPI_BUS_init();
while(1)
{
    for(i=0;i<=65535;i++)
    {
        SPI_BUS_write(i+1,i);
    }
    for(i=0;i<=65535;i++)
    {
        SPI_BUS_read(i+1,i);
    }
}
//    flash_test(256);
//while(1)
//{
//    test_temp(0b1000, 0b1000, 0b1111, 0b1000);
//    DEVICE_DELAY_US(500);
//}
}

void tests_core1()
{
    while (1)
    {
       DEVICE_DELAY_US(1000);
       GPIO_togglePin(33);
    };
}

