#ifndef __TIMER_H__
#define __TIMER_H__

/* Timer interrupt - Time frequency: 1kHz(1ms) */
#define SYS_TICKS_PER_SECOND    1000

void TIMER0_init(void);
/*-----------------------------------------------------------*/
typedef struct __timer_software_t
{
    uint32_t start;
    uint32_t interval;
} timer_sw_t;

/**
 * @brief Get current timer tick count
 * 
 */
uint32_t clock_time(void);

/**
 * @brief Set a software timer
 * 
 * @param t Point to a software timer
 * @param interval Timer period
 */
void timer_set(timer_sw_t *t, uint32_t interval);

/**
 * @brief Restart the software timer
 * 
 */
void timer_restart(timer_sw_t *t);

/**
 * @brief Check whether the current software timer expired
 * 
 * @param t Point to current software timer
 * @return  1: expired (timeout)
 *          0：not expired
 */
int timer_expired(timer_sw_t *t);

void delay_ms(volatile uint32_t ms);

#endif /* __TIMER_H__ */
