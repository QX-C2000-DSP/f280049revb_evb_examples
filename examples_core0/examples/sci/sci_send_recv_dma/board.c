#include "../sci_send_recv_dma/board.h"

extern __interrupt void dmach2ISR(void);
extern char send_frame[256];
extern char recv_frame[256];

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void Board_init()
{
    EALLOW;

    PinMux_init();
    SCI_init();
    DMA_init();
    INTERRUPT_init();

    EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    //
    // PinMux for modules assigned to CPU1
    //
    GPIO_MuxConfig(
        SCI_TX_PIN_NUM, SERIAL_TX_GPIO_CONFIG(SCI_TX_PIN_NUM), GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_MuxConfig(
        SCI_RX_PIN_NUM, SERIAL_RX_GPIO_CONFIG(SCI_RX_PIN_NUM), GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
}

//*****************************************************************************
//
// SCI init
//
//*****************************************************************************
void SCI_init()
{

    if (SCI_BASE == SCIA_BASE)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    }
    else if (SCI_BASE == SCIB_BASE)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    }
    else
    {
        /* EALLOW: It must be added; otherwise, due to the register write protection,
            the value cannot be written in. */
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
        EALLOW;
        GpioCtrlRegs.SPSEL.bit.SPSEL = 1; // 仅LINA基地址选择作为SCIC使用时, 需要使用此寄存器切换模块功能.
        EDIS;
    }

    SCI_setConfig(SCI_BASE, DEVICE_LSPCLK_FREQ, SCI_BAUD_RATE,
        SCI_CONFIG_WLEN | SCI_CONFIG_STOP | SCI_CONFIG_PAR);
    SCI_enableFIFO(SCI_BASE);
    SCI_resetRxFIFO(SCI_BASE);
    SCI_setFIFOInterruptLevel(SCI_BASE, SCI_FIFO_TX0, SCI_FIFO_RX1);

    SCI_enableInterrupt(SCI_BASE, SCI_INT_RXFF | SCI_INT_RXERR);

    ((volatile struct SCI_REGS *)SCI_BASE)->SCIDMACTL.bit.DMA_TX_EN = 1;
    ((volatile struct SCI_REGS *)SCI_BASE)->SCIDMACTL.bit.DMA_RX_EN = 1;
}

void DMA_init()
{
    DMA_ConfigParams dconfig = { 0 };

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

    DMA_initController();

    // DMA channel 1 用于发送
    dconfig.srcAddr         = (u32)send_frame;
    dconfig.destAddr        = (u32)(&((volatile struct SCI_REGS *)SCI_BASE)->SCITXBUF);
    dconfig.srcWidth        = DMA_TRANS_WIDTH_8;  // 设置DMA数据位宽为8bit
    dconfig.destWidth       = DMA_TRANS_WIDTH_8;  // 设置DMA数据位宽为8bit
    dconfig.srcMsize        = DMA_MSIZE_1;        // 设置DMA一次传输请求传输一个字节
    dconfig.destMsize       = DMA_MSIZE_1;        // 设置DMA一次传输请求传输一个字节
    dconfig.blockSize       = 0;                  // 一次DMA业务总长度，在main中动态配置
    dconfig.srcHSInterface  = DMA_TRIGGER_MEM;    // 设DMA源地址触发类型
    if (SCI_BASE == SCIA_BASE)
    {
        dconfig.destHSInterface = DMA_TRIGGER_SCIATX; // 设DMA目的地址触发类型
    }
    else if (SCI_BASE == SCIB_BASE)
    {
        dconfig.destHSInterface = DMA_TRIGGER_SCIBTX; // 设DMA目的地址触发类型
    }
    else
    {
        dconfig.destHSInterface = DMA_TRIGGER_SCICTX; // 设DMA目的地址触发类型
    }
    dconfig.srcInc          = DMA_INC_TYPE_INCREMENT;
    dconfig.destInc         = DMA_INC_TYPE_NO_CHANGE;
    DMA_configChannel(DMA_CH1_BASE, &dconfig);
    DmaCh1Regs.INTSIGNAL_EN = 0x0; // 禁用所有中断

    // DMA channel 2 用于接收
    dconfig.srcAddr         = (u32)(&((volatile struct SCI_REGS *)SCI_BASE)->SCIRXBUF);
    dconfig.destAddr        = (u32)recv_frame;
    dconfig.srcWidth        = DMA_TRANS_WIDTH_8;
    dconfig.destWidth       = DMA_TRANS_WIDTH_8;
    dconfig.srcMsize        = DMA_MSIZE_1;
    dconfig.destMsize       = DMA_MSIZE_1;
    dconfig.blockSize       = 0;
    if (SCI_BASE == SCIA_BASE)
    {
        dconfig.srcHSInterface = DMA_TRIGGER_SCIARX; // 设DMA源地址触发类型
    }
    else if (SCI_BASE == SCIB_BASE)
    {
        dconfig.srcHSInterface = DMA_TRIGGER_SCIBRX; // 设DMA源地址触发类型
    }
    else
    {
        dconfig.srcHSInterface = DMA_TRIGGER_SCICRX; // 设DMA源地址触发类型
    }
    dconfig.destHSInterface = DMA_TRIGGER_MEM;
    dconfig.srcInc          = DMA_INC_TYPE_NO_CHANGE;
    dconfig.destInc         = DMA_INC_TYPE_INCREMENT;
    DMA_configChannel(DMA_CH2_BASE, &dconfig);
    DmaCh2Regs.INTSIGNAL_EN = 0xFFE2; // 使能DMA完成和所有错误中断

    DMA_startChannel(2); // 启动接收DMA
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{
    Interrupt_register(INT_DMA_CH2, &dmach2ISR);
    Interrupt_enable(INT_DMA_CH2);
}
