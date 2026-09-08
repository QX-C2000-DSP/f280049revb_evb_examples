#include "device.h"

// 注意:CMP最小值不能配置为0, 否则输出波形存在异常。详细说明参见《QX280049_RevB差异手册.docx》
u16 pwm[50] = { 1, 1, 2, 5, 8, 11, 16, 21, 26, 32, 38, 44, 50, 56, 62, 68, 74, 79, 84, 89, 92, 95,
    98, 99, 100, 100, 99, 98, 95, 92, 89, 84, 79, 74, 68, 62, 56, 50, 44, 38, 32, 26, 21, 16, 11, 8,
    5, 2, 1, 1 };

void DMA_init()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

    DMA_ConfigParams dconfig;
    dconfig.srcMultblk      = DMA_MBLK_TYPE_RELOAD;
    dconfig.destMultblk     = DMA_MBLK_TYPE_CONTIGUOUS;
    dconfig.srcAddr         = (u32)pwm;
    dconfig.destAddr        = ((u32)&EPwm1Regs.CMPA.all) + 2;
    dconfig.srcWidth        = DMA_TRANS_WIDTH_16;
    dconfig.destWidth       = DMA_TRANS_WIDTH_16;
    dconfig.srcMsize        = DMA_MSIZE_1;
    dconfig.destMsize       = DMA_MSIZE_1;
    dconfig.blockSize       = 49;
    dconfig.srcInc          = DMA_INC_TYPE_INCREMENT;
    dconfig.destInc         = DMA_INC_TYPE_NO_CHANGE;
    dconfig.srcHSInterface  = DMA_TRIGGER_MEM;
    dconfig.destHSInterface = DMA_TRIGGER_EPWM1SOCA;

    DMA_initController();
    DMA_configChannel(DMA_CH1_BASE, &dconfig);
    DMA_startChannel(1);
}

void EPWM_init()
{
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV    = 0;
    EPwm1Regs.TBCTL.bit.CLKDIV       = 0;
    EPwm1Regs.TBCTL.bit.CTRMODE      = 2;
    EPwm1Regs.CMPA.bit.CMPA          = 50;
    EPwm1Regs.TBPRD                  = 100;
    EPwm1Regs.AQCTLA.bit.CAU         = 1;
    EPwm1Regs.AQCTLA.bit.CAD         = 2;
    EPwm1Regs.AQCTLB.bit.CAU         = 1;
    EPwm1Regs.AQCTLB.bit.CAD         = 2;
    EPwm1Regs.ETPS.bit.SOCPSSEL      = 0;
    EPwm1Regs.ETPS.bit.SOCAPRD       = 1;
    EPwm1Regs.ETPS.bit.SOCACNT       = 1;
    EPwm1Regs.ETSEL.bit.SOCASEL      = 2;
    EPwm1Regs.ETSEL.bit.SOCAEN       = 1;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
}

int main()
{
    GPIO_MuxConfig(0, GPIO_0_EPWM1_A, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(1, GPIO_1_EPWM1_B, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);

    DMA_init();

    EPWM_init();

    while (1)
        ;
}
