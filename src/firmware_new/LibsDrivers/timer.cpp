#include "timer.h"
#include <device.h>


struct sTaskItem
{
    uint32_t    period;
    uint32_t    next_time_call;
    Thread      *callback_class;
};

volatile uint32_t g_time = 0;
volatile sTaskItem g_task_list[TIMER_MAX_TASKS];


#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler(void)
{
    for (unsigned int i = 0; i < TIMER_MAX_TASKS; i++)
    {
        if (g_task_list[i].callback_class != nullptr && g_time > g_task_list[i].next_time_call)
        {
            g_task_list[i].next_time_call = g_time + g_task_list[i].period;
            g_task_list[i].callback_class->main();
        }
    }

    g_time++;
}

#ifdef __cplusplus
}
#endif


Timer::Timer()
{
    
} 

Timer::~Timer()
{

}

void Timer::init(uint32_t frequency)
{
    current_ptr = 0;
    g_time      = 0;

    for (unsigned int i = 0; i < TIMER_MAX_TASKS; i++)
    {
        g_task_list[i].period           = 0;
        g_task_list[i].next_time_call   = 0;
        g_task_list[i].callback_class   = nullptr;
    }

    //interrupt every 1ms
    SysTick_Config(SystemCoreClock/frequency);
    __enable_irq();

    delay_ms(10);
}

int Timer::add_task(Thread *callback_class, unsigned int period_ms)
{
    if (current_ptr < TIMER_MAX_TASKS)
    {
        __disable_irq();

        period_ms = period_ms - 1;

        g_task_list[current_ptr].period           = period_ms;
        g_task_list[current_ptr].next_time_call   = g_time + period_ms;
        g_task_list[current_ptr].callback_class   = callback_class;
        current_ptr++;

        __enable_irq();

        return 0;
    }
    else
    {
        return -1;
    }
}


uint32_t Timer::get_time()
{
    return g_time;
}

void Timer::delay_ms(uint32_t time_ms)
{
    time_ms = time_ms + g_time;
    while (time_ms > g_time)
    {
        __asm("wfi");
    }
}