#include "board.h"

extern u8 src_buf[256];
extern u8 dst_buf[256];

extern __interrupt void dmach1ISR(void);

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void Board_init()
{
    EALLOW;

    INTERRUPT_init();
    DMA_init();

    EDIS;
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{
    Interrupt_register(INT_DMA_CH1, &dmach1ISR);
    Interrupt_enable(INT_DMA_CH1);
}

//*****************************************************************************
//
// DMA init
//
//*****************************************************************************
void DMA_init()
{
    DMA_ConfigParams dconfig = { 0 };

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

    DMA_initController();

    // DMA channel 1 config
    dconfig.srcAddr         = (u32)src_buf;
    dconfig.destAddr        = (u32)dst_buf;
    dconfig.srcWidth        = DMA_TRANS_WIDTH_8; // 设置DMA数据位宽为32bit
    dconfig.destWidth       = DMA_TRANS_WIDTH_8; // 设置DMA数据位宽为32bit
    dconfig.srcMsize        = DMA_MSIZE_8;        // 设置DMA一次传输请求传输8个字节
    dconfig.destMsize       = DMA_MSIZE_8;        // 设置DMA一次传输请求传输8个字节
    dconfig.blockSize       = 31;                 // 一次DMA业务总长度
    dconfig.srcHSInterface  = DMA_TRIGGER_MEM;    // 设DMA源地址触发类型
    dconfig.destHSInterface = DMA_TRIGGER_MEM;    // 设DMA目的地址触发类型
    dconfig.srcInc          = DMA_INC_TYPE_INCREMENT;    // 设DMA源地址递增
    dconfig.destInc         = DMA_INC_TYPE_INCREMENT;    // 设DMA目的地址递增

    DMA_configChannel(DMA_CH1_BASE, &dconfig);
    DmaCh1Regs.INTSIGNAL_EN = 0xFFE2; // 使能DMA完成和所有错误中断
}
