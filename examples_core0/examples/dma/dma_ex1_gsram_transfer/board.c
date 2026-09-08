
#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
    EALLOW;
    DMA_init();
    INTERRUPT_init();

    EDIS;
}

//*****************************************************************************
//
// DMA Configurations
//
//*****************************************************************************
void DMA_init(){
    myDMA0_init();
}

void myDMA0_init(){
    DMA_ConfigParams dconfig = { 0 };

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

    DMA_initController();

    // DMA channel 1 config
    dconfig.srcAddr         = (u32)srcAddr;
    dconfig.destAddr        = (u32)destAddr;
    dconfig.srcWidth        = DMA_TRANS_WIDTH_16; // 设置DMA数据位宽为16bit
    dconfig.destWidth       = DMA_TRANS_WIDTH_16; // 设置DMA数据位宽为16bit
    dconfig.srcMsize        = DMA_MSIZE_8;        // 设置DMA一次传输请求传输8个16bit
    dconfig.destMsize       = DMA_MSIZE_8;        // 设置DMA一次传输请求传输8个16bit
    dconfig.blockSize       = 127;                 // 一次DMA业务总长度
    dconfig.srcHSInterface  = DMA_TRIGGER_MEM;    // 设DMA源地址触发类型
    dconfig.destHSInterface = DMA_TRIGGER_MEM;    // 设DMA目的地址触发类型
    dconfig.srcInc          = DMA_INC_TYPE_INCREMENT;    // 设DMA源地址递增
    dconfig.destInc         = DMA_INC_TYPE_INCREMENT;    // 设DMA目的地址递增

    DMA_configChannel(DMA_CH1_BASE, &dconfig);
    DmaCh1Regs.INTSIGNAL_EN = 0xFFE2; // 使能DMA完成和所有错误中断
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){

    // Interrupt Settings for INT_myDMA0
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myDMA0, &INT_myDMA0_ISR);
    Interrupt_disable(INT_myDMA0);
}
