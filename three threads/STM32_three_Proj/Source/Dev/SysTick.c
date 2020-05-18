#include "config.h"
#include "SysTick.h"

uint32 sysTimer[MAX_TIMER];//软件定时器数组
static uint32 g_iRunTimer = 0;//定义系统全局运行时间



void SysTickInit(void)
{
	uchar i;
	for(i = 0;i < MAX_TIMER; i++)
		sysTimer[i] = 0;
	
	SysTick_Config(72000000/1000);//每隔1ms进一次系统滴答中断响应函数，主频72M
	
}

void SysTick_Handler(void) 
{
	uint8 i;
	for(i = 0;i < MAX_TIMER; i++)
	  if(sysTimer[i])
			sysTimer[i]--;
		
	if(g_iRunTimer++ == 0XFFFFFFFF)//最多可计50天左右
		 g_iRunTimer = 0;
	
}


void SysTickDelayMs(uint32 nms)
{
	CPU_INT_ENABLE();//打开CPU中断
	
	DelayTimer = nms;
	while(DelayTimer);//等待延时时间完成
}


uint32 GetRunTime(void)
{
	
	uint32 RunTime;
	
	CPU_INT_DISABLE();//关中断
	RunTime = g_iRunTimer;
	CPU_INT_ENABLE();//开中断
	
	return RunTime;
}


