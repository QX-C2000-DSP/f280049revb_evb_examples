
#include "board.h"


extern uint16_t sData[128];                // Send data buffer
extern uint16_t rData[128];                // Receive data buffer

extern __interrupt void dmach2ISR(void);

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

	PinMux_init();
	SPI_init();
	DMA_init();

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
	
	//
	// SPIA -> mySPI1 Pinmux
	//
	GPIO_setPinConfig(mySPI1_SPISIMO_PIN_CONFIG);
	GPIO_setPadConfig(mySPI1_SPISIMO_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(mySPI1_SPISIMO_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(mySPI1_SPISOMI_PIN_CONFIG);
	GPIO_setPadConfig(mySPI1_SPISOMI_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(mySPI1_SPISOMI_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(mySPI1_SPICLK_PIN_CONFIG);
	GPIO_setPadConfig(mySPI1_SPICLK_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(mySPI1_SPICLK_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(mySPI1_SPIPTE_PIN_CONFIG);
	GPIO_setPadConfig(mySPI1_SPIPTE_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(mySPI1_SPIPTE_GPIO, GPIO_QUAL_ASYNC);


}

//*****************************************************************************
//
// SPI Configurations
//
//*****************************************************************************
void SPI_init(){
	mySPI1_init();
}

void mySPI1_init(){
    // Enable the clock for the SPI1 peripheral
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);

	SPI_disableModule(mySPI1_BASE);
	SPI_setConfig(mySPI1_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
				  SPI_MODE_CONTROLLER, mySPI1_BITRATE, mySPI1_DATAWIDTH);
	SPI_setPTESignalPolarity(mySPI1_BASE, SPI_PTE_ACTIVE_LOW);
	SPI_enableFIFO(mySPI1_BASE);
	SPI_setFIFOInterruptLevel(mySPI1_BASE, SPI_FIFO_TX8, SPI_FIFO_RX8);
	SPI_enableLoopback(mySPI1_BASE);
	SPI_enableModule(mySPI1_BASE);
}


void DMA_init()
{
    DMA_ConfigParams dconfig = { 0 };

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DMA);

    DMA_initController();

    // DMA channel 1 用于发送
    dconfig.srcAddr         = (u32)sData;
    dconfig.destAddr        = (u32)&(SpibRegs.SPITXBUF);
    dconfig.srcWidth        = DMA_TRANS_WIDTH_16;  // 设置DMA数据位宽为16bit
    dconfig.destWidth       = DMA_TRANS_WIDTH_16;  // 设置DMA数据位宽为16bit
    dconfig.srcMsize        = DMA_MSIZE_8;        // 设置DMA一次传输请求传输8个16bit
    dconfig.destMsize       = DMA_MSIZE_8;        // 设置DMA一次传输请求传输8个16bit
    dconfig.blockSize       = 127;                 // 一次DMA业务总长度
    dconfig.srcHSInterface  = DMA_TRIGGER_MEM;    // 设DMA源地址触发类型
    dconfig.destHSInterface = DMA_TRIGGER_SPIB_TX; // 设DMA目的地址触发类型
    dconfig.srcInc          = DMA_INC_TYPE_INCREMENT;
    dconfig.destInc         = DMA_INC_TYPE_NO_CHANGE;
    DMA_configChannel(DMA_CH1_BASE, &dconfig);
    DmaCh1Regs.INTSIGNAL_EN = 0x0; // 禁用所有中断

    // DMA channel 2 用于接收
    dconfig.srcAddr         = (u32)&(SpibRegs.SPIRXBUF);
    dconfig.destAddr        = (u32)rData;
    dconfig.srcWidth        = DMA_TRANS_WIDTH_16;
    dconfig.destWidth       = DMA_TRANS_WIDTH_16;
    dconfig.srcMsize        = DMA_MSIZE_8;
    dconfig.destMsize       = DMA_MSIZE_8;
    dconfig.blockSize       = 127;
    dconfig.srcHSInterface  = DMA_TRIGGER_SPIB_RX;
    dconfig.destHSInterface = DMA_TRIGGER_MEM;
    dconfig.srcInc          = DMA_INC_TYPE_NO_CHANGE;
    dconfig.destInc         = DMA_INC_TYPE_INCREMENT;
    DMA_configChannel(DMA_CH2_BASE, &dconfig);
    DmaCh2Regs.INTSIGNAL_EN = 0xFFE2; // 使能DMA完成和所有错误中断

}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){

    Interrupt_register(INT_DMA_CH2, &dmach2ISR);
    Interrupt_enable(INT_DMA_CH2);
}
