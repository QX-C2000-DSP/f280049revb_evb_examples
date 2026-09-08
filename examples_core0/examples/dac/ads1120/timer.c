#include "user_inc.h"
#include "timer.h"

/* timer tick count */
static volatile uint32_t time_tick;

static int TIMER_init(uint32_t timer_base)
{
    uint32_t SystemClock = SysCtl_getClock(DEVICE_OSCSRC_FREQ);
    uint32_t prescaler   = CPUTIMER_CLOCK_PRESCALER_1;                              // 设置分频因子: 1分频
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
uint32_t clock_time(void)
{
    return time_tick;
}

void timer_set(timer_sw_t *t, uint32_t interval)
{
    t->interval = interval;
    t->start    = clock_time();
}

void timer_restart(timer_sw_t *t)
{
    t->start = clock_time();
}

int timer_expired(timer_sw_t *t)
{
    /* Note: Can not return diff >= t->interval so we add 1 to diff and return
     t->interval < diff - required to avoid an internal error in mspgcc. */
    uint32_t diff = (clock_time() - t->start) + 1;
    return (t->interval < diff);
}

void delay_ms(volatile uint32_t ms)
{
    volatile uint32_t tc = clock_time();
    while(clock_time() - tc < ms){

    }
}
