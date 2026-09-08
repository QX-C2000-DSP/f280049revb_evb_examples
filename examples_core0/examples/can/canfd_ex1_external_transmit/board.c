#include "board.h"



extern __interrupt void canbISR(void);
extern u8 errorFlag;

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
    CAN_init();
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
    GPIO_MuxConfig(31, GPIO_31_CANA_TX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(31, GPIO_DIR_MODE_OUT);
    GPIO_MuxConfig(30, GPIO_30_CANA_RX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(30, GPIO_DIR_MODE_IN);
    GPIO_MuxConfig(6, GPIO_6_CANB_TX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(6, GPIO_DIR_MODE_OUT);
    GPIO_MuxConfig(7, GPIO_7_CANB_RX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(7, GPIO_DIR_MODE_IN);
}

void CAN_init()
{
    CAN_Init_Config canInit;
    CANFD_Config canFd;

    //
    // enable module clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);

    //
    //Initializes CAN parameters.
    //
    CAN_structInit(&canInit);
    CANFD_structInit(&canFd);
    canInit.canFDControl = CAN_FD_ENABLE;
    canFd.TDC = CAN_FD_TDC_ENABLE;
    canFd.SSPOffset = 20;
    canInit.ptrCanFd = &canFd;

    //
    // Software reset.
    //
    CAN_enableStatReset(CANA_BASE);
    CAN_enableStatReset(CANB_BASE);
    //
    //Initialize CAN module
    //
    CAN_initModule(CANA_BASE, &canInit);
    CAN_initModule(CANB_BASE, &canInit);

    //
    //Set CAN filter
    //
    CAN_setAcceptFilter(CANA_BASE, CAN_ACF1, CAN_ID_STD, 0x111, 0x0U);
    CAN_setAcceptFilter(CANB_BASE, CAN_ACF1, CAN_ID_STD, 0x222, 0x0U);

    //
    // 500K bundrate when can pclk = 100Mhz, sample point = 80%
    // (bundrate = pclk/s_prescale/(s_seg1+2 + s_seg2+1))
    //
    CAN_setBitTimingSlow(CANA_BASE, 3, 38, 9, 9);
    CAN_setBitTimingSlow(CANB_BASE, 3, 38, 9, 9);
    //
    // 2000K bundrate when can pclk = 100Mhz, sample point = 80%
    // (bundrate = pclk/s_prescale/(s_seg1+2 + s_seg2+1))
    //
    CANFD_setBitTimingFast(CANA_BASE, 1, 18, 4, 4);
    CANFD_setBitTimingFast(CANB_BASE, 1, 18, 4, 4);

    //
    // CAN enters normal communication mode.
    //
    CAN_disableStatReset(CANA_BASE);
    CAN_disableStatReset(CANB_BASE);

    //
    // Enable CANB receive interrupt.
    //
    CAN_enableInterrupt(CANB_BASE, CAN_INT_RIE);

    //
    // delay for configure ready
    //
    simple_delay(100);

}


//*****************************************************************************
//
// verify_data_byte
//
//*****************************************************************************
void verify_data_byte(void *buf1, void *buf2, u32 len)
{
    for (int i = 0; i < len; i++)
    {
        if (((u8 *)buf1)[i] != ((u8 *)buf2)[i])
        {
            errorFlag = 1;
            break;
        }
    }
}

//*****************************************************************************
//
// simple_delay
//
//*****************************************************************************
// 1s ~= 500000 at 25Mhz cpu_clk
void simple_delay(u32 count)
{
    volatile int i = 0;
    for (i = 0; i < count; i++)
        ;
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{

    //
    // Interrupt Setings for INT_CANB_BASE
    //
    Interrupt_register(INT_CANB, &canbISR);
    Interrupt_enable(INT_CANB);
}

