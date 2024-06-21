#include "tim.h"
// uint32_t time1_current_ms = 0;
void rtos_tim_config(void)
{
    timer_parameter_struct timer_initpara;
    timer_deinit(TIMER1);
    /* TIMER1 configuration */
    timer_initpara.prescaler = (84 - 1);
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = (1000 - 1);
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 1;
    timer_init(TIMER1, &timer_initpara);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER1);

    /* TIMER1 counter enable */
    
    timer_interrupt_flag_clear(TIMER1, TIMER_INT_UP);
    timer_interrupt_enable(TIMER1, TIMER_INT_UP);
}

void TIMER1_IRQHandler(void)
{
    if (timer_interrupt_flag_get(TIMER1, TIMER_INT_UP) != RESET)
    {
        // time1_current_ms++;
        xPortSysTickHandler();
        timer_interrupt_flag_clear(TIMER1, TIMER_INT_UP);
    }
}

void tim_config(void)
{
    rcu_periph_clock_enable(RCU_TIMER1);
    rtos_tim_config();
}