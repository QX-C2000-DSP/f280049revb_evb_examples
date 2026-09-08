#include "device.h"
#include "driverlib.h"

#include <stdio.h>

volatile struct SCI_REGS *dbg_uart; // 调试使用的串口

// 用户层重载putchar回调函数
int putchar(int c)
{
    while (!dbg_uart->SCICTL2.bit.TXEMPTY)
        ;
    dbg_uart->SCITXBUF.all = c;
    while (!dbg_uart->SCICTL2.bit.TXEMPTY)
        ;

    return c;
}

// 使用打印SCI的串口初始化流程
void StdOutInit(volatile struct SCI_REGS *sci, int baudrate, uint32_t pin, uint32_t pin_mux)
{
    dbg_uart = sci;

    if (sci == &SciaRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIA);
    else if (sci == &ScibRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIB);
    else if (sci == &ScicRegs)
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SCIC);

    if (sci == &SciaRegs)
    {
        CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
    }
    else if (sci == &ScibRegs)
    {
        CpuSysRegs.PCLKCR7.bit.SCI_B = 1;
    }

    float tmp = (float)DEVICE_LSPCLK_FREQ / 8 / baudrate;
    if ((tmp - (int)tmp) >= 0.5)
        tmp = tmp + 1;
    int val = (int)tmp - 1;

    sci->SCICCR.bit.SCICHAR  = 7;
    sci->SCILBAUD.all        = val & 0xFF;
    sci->SCIHBAUD.all        = val >> 8;
    sci->SCICTL1.bit.SWRESET = 1;
    sci->SCICTL1.bit.TXENA   = 1;

    GPIO_setPinConfig(pin_mux);
    GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
}

/* Timer interrupt - Time frequency: 1kHz(1ms) */
#define SYS_TICKS_PER_SECOND    1000

static int TIMER_init(uint32_t timer_base)
{
    uint32_t SystemClock = SysCtl_getClock(DEVICE_OSCSRC_FREQ);
    uint32_t prescaler   = CPUTIMER_CLOCK_PRESCALER_1;                              // 设置分频因子
    uint32_t period      = SystemClock / ((prescaler + 1) * SYS_TICKS_PER_SECOND);  // 计算周期

    if (CPUTIMER0_BASE == timer_base)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER0);
    }
    else if (CPUTIMER1_BASE == timer_base)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER1);
    }
    else if (CPUTIMER2_BASE == timer_base)
    {
        SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TIMER2);
    }
    else
    {
        return -1;
    }

    CPUTimer_stopTimer(timer_base);                 // 停止定时器
    CPUTimer_setPeriod(timer_base, period - 1);     // 设置周期
    CPUTimer_setPreScaler(timer_base, prescaler);   // 设置定时器的时钟源
    CPUTimer_reloadTimerCounter(timer_base);        // 重载初始值
    CPUTimer_enableInterrupt(timer_base);           // 设置定时器的中断
    CPUTimer_startTimer(timer_base);                // 开启定时器

    return 0;
}

/*----------------------------------------------------------------------------------*/
/* timer tick count */
static volatile uint32_t time_tick;

__interrupt void timer0_isr(void)
{
    /* timer Tick add */
    time_tick++;
}

void TIMER0_init(void)
{
    TIMER_init(CPUTIMER0_BASE);

    /* set timer0 interrupt */
    Interrupt_register(INT_TIMER0, timer0_isr);
    Interrupt_enable(INT_TIMER0);
}

/*----------------------------------------------------------------------------------*/
void delay_ms(volatile uint32_t ms)
{
    volatile uint32_t tc = time_tick;
    while (time_tick - tc < ms) {

    }
}

int main(void)
{
    /* in order for interrupts to have a default entry port,
        do not run away when interrupt is not registered */
    Interrupt_initVectorTable();
    Device_init();

    /* remap printf */
    StdOutInit(&ScibRegs, 115200, 12, GPIO_12_SCIB_TX);

    TIMER0_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while (1)
    {
        printf(" 1 \r\n");
        delay_ms(1000);
        printf(" 2 \r\n");
        delay_ms(1000);
        printf(" 3 \r\n");
    };

    return 0;
}
