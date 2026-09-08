//#############################################################################
//
// FILE:   board.c
//
// TITLE:  Board support file for CAN FIFO Demo
//
//#############################################################################

#include "board.h"

//
// External declarations from main.c
//
extern __interrupt void canbISR(void);

//#############################################################################
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//#############################################################################
void Board_init(void)
{
    EALLOW;

    PinMux_init();
    CAN_init();
    INTERRUPT_init();

    EDIS;
}

//#############################################################################
//
// PINMUX Configurations
//
//#############################################################################
void PinMux_init(void)
{
    //
    // PinMux for modules assigned to CPU1
    // GPIO6 - CANB_TX, GPIO7 - CANB_RX
    //
    GPIO_MuxConfig(6, GPIO_6_CANB_TX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(6, GPIO_DIR_MODE_OUT);
    GPIO_MuxConfig(7, GPIO_7_CANB_RX, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(7, GPIO_DIR_MODE_IN);
}

//#############################################################################
//
// CAN Configurations
//
//#############################################################################
void CAN_init(void)
{
    CAN_Init_Config canInit;

    //
    // Enable CANB module clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CANB);

    //
    // Initialize CAN parameter structures with default values
    //
    CAN_structInit(&canInit);

    //
    // Configure STB mode: FIFO mode (not priority mode)
    // CAN_STB_PRIO_MD_DISABLE = 0: First-in-first-out transmission order
    // CAN_STB_PRIO_MD_ENABLE  = 1: Priority order (lower ID first)
    //
    // For FIFO demo, we use DISABLE (FIFO mode)
    //
    canInit.STBPrioMode = CAN_STB_PRIO_MD_DISABLE;

    //
    // Disable CAN-FD for this demo (Classic CAN mode)
    //
    canInit.canFDControl = CAN_FD_DISABLE;
    canInit.ptrCanFd = NULL;

    //
    // Software reset - required before configuring bit timing
    //
    CAN_enableStatReset(CANB_BASE);

    //
    // Initialize CAN module with parameters
    //
    CAN_initModule(CANB_BASE, &canInit);

    //
    // Set acceptance filter
    // Accept standard frames with ID 0x100-0x1FF
    //
    // Filter configuration:
    // - CAN_ACF1: Use acceptance filter 1
    // - CAN_ID_STD: Accept standard ID frames only
    // - 0x00000100: ID code (base ID)
    // - 0x00000700: ID mask (mask bits 8-10, accept 0x100-0x1FF)
    //
    CAN_setAcceptFilter(CANB_BASE, CAN_ACF1, CAN_ID_STD, 0x00000100UL, 0x00000700UL);

    //
    // Enable acceptance filter 1
    //
    CAN_filterCmd(CANB_BASE, CAN_ACF1, ENABLE);

    //
    // Configure bit timing for 500Kbps
    // CAN PCLK = 100MHz
    // Bit rate = PCLK / (S_PRESC + 1) / (S_Seg_1 + S_Seg_2 + 3)
    // 500K = 100M / 4 / 50 = 500Kbps
    // Sample point = (S_Seg_1 + 2) / (S_Seg_1 + S_Seg_2 + 3) = 40/50 = 80%
    //
    CAN_setBitTimingSlow(CANB_BASE, 3, 38, 9, 9);

    //
    // Configure receive buffer warning limit
    // AFWL = 4: RAFIF triggers when 4+ frames in RB
    // This gives early warning before RB fills up (16 slots)
    //
    CAN_setRxWarnLimit(CANB_BASE, 4);

    //
    // Configure error warning limit
    // EWL = 8: Error warning when TEC/REC >= 8
    //
    CAN_setErrorWarnLimit(CANB_BASE, 8);

    //
    // Exit software reset, enter normal operation mode
    //
    CAN_disableStatReset(CANB_BASE);

    //
    // Enable all CAN interrupts
    // This includes: TSIF, TPIF, RAFIF, RFIF, ROIF, RIF, EIF, AIF
    //
    CAN_enableInterrupt(CANB_BASE, CAN_INT_ALL);

    //
    // Short delay for configuration to take effect
    //
    simple_delay(100);
}

//#############################################################################
//
// INTERRUPT Configurations
//
//#############################################################################
void INTERRUPT_init(void)
{
    //
    // Register CANB interrupt handler
    //
    Interrupt_register(INT_CANB, &canbISR);

    //
    // Enable CANB interrupt in PIE
    //
    Interrupt_enable(INT_CANB);
}

//#############################################################################
//
// simple_delay
//
//#############################################################################
// 1s ~= 500000 at 25Mhz cpu_clk
void simple_delay(uint32_t count)
{
    volatile uint32_t i;
    for(i = 0; i < count; i++)
    {
        ;
    }
}
