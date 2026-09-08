#include "board.h"

extern __interrupt void timer0ISR(void);

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void Board_init()
{
    EALLOW;

    INTERRUPT_init();
    Timer_init();

    EDIS;
}

//*****************************************************************************
//
// Timer init
//
//*****************************************************************************
void Timer_init()
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    CPUTimer_setPeriod(CPUTIMER0_BASE, 100000000);
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    CPUTimer_startTimer(CPUTIMER0_BASE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init()
{
    //
    // Interrupt Setings for timer0
    //
    Interrupt_register(INT_TIMER0, &timer0ISR);
    Interrupt_enable(INT_TIMER0);
}
