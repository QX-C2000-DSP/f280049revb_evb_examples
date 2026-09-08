#include "board.h"

extern __interrupt void scirxISR(void);

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
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{
    //
    // Interrupt Setings for sci
    //
    if (SCI_BASE == SCIA_BASE)
    {
        Interrupt_register(INT_SCIA_RX, &scirxISR);
        Interrupt_enable(INT_SCIA_RX);
    }
    else if (SCI_BASE == SCIB_BASE)
    {
        Interrupt_register(INT_SCIB_RX, &scirxISR);
        Interrupt_enable(INT_SCIB_RX);
    }
    else
    {
        Interrupt_register(INT_SCIC_RX, &scirxISR);
        Interrupt_enable(INT_SCIC_RX);
    }
}
