#include "board.h"



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
    GPIO_MuxConfig(6, GPIO_6_CANB_TX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(6, GPIO_DIR_MODE_OUT);
    GPIO_MuxConfig(7, GPIO_7_CANB_RX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(7, GPIO_DIR_MODE_IN);
}

void CAN_init()
{

    CAN_Init_Config ptrCanInit;

    //
    // enable module clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);

    //
    //Initializes CAN parameters.
    //
    CAN_structInit(&ptrCanInit);

    //
    // Software reset.
    //
    CAN_enableStatReset(CANB_BASE);
    //
    //Initialize CAN module
    //
    CAN_initModule(CANB_BASE, &ptrCanInit);


    //
    //Set CAN filter
    //
    //CAN_setAcceptFilter(CANB_BASE, CAN_ACF1, CAN_ID_STD_EXT, 0x111UL, 0x1FFFFFFFUL);

    //
    // 1000K bundrate when can pclk = 100Mhz, sample point = 80%
    // (bundrate = pclk/s_prescale/(s_seg1+2 + s_seg2+1))
    //
    CAN_setBitTimingSlow(CANB_BASE, 3, 18, 4, 1);

    //
    // CAN enters normal communication mode.
    //
    CAN_disableStatReset(CANB_BASE);

    //
    // Set can module working in external loopback test mode.
    //
    CAN_setWorkMode(CANB_BASE, CAN_WORK_MD_ELB);

    CAN_setRCTRL(CANB_BASE, CAN_RX_OVF_DISCARD_NEW, CAN_RX_ALL_FRAME_DISABLE, CAN_SELF_ACK_ENABLE);

    //
    // delay for config ready
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

