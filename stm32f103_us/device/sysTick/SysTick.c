#include "config.h"
#include "SysTick.h"

//uint32 sysTimer[MAX_TIMER];//软件定时器数组
//static uint32 g_iRunTimer = 0;//定义系统全局运行时间



void SysTickInit(void)
{

	Stm32_Clock_Init(RCC_PLL_MUL9); 
//	SysTick_Config(72000000/1000);//每隔1ms进一次系统滴答中断响应函数，主频72M
	
}

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t delta;
    rt_uint32_t current_delay;

    /* 获得延时经过的tick数 */
    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));

    /* 获得当前时间 */
    delta = SysTick->VAL;

    /* 循环获得当前时间，直到达到指定的时间后退出循环 */
    do
    {
			if ( delta > SysTick->VAL )
				current_delay = delta - SysTick->VAL;
			else
        /* 延时跨越了一次OS tick的边界时的处理 */
				current_delay = SysTick->LOAD + delta - SysTick->VAL;
    } while( current_delay < us );
}


#if 0
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t delta;
    /* 获得延时经过的 tick 数 */
    us = us * (SysTick->LOAD/(1000000/RT_TICK_PER_SECOND));
    /* 获得当前时间 */
    delta = SysTick->VAL;
    /* 循环获得当前时间，直到达到指定的时间后退出循环 */
    while (delta - SysTick->VAL< us);
}
#endif



