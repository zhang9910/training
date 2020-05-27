#ifndef  __CONFIG_H__
#define  __CONFIG_H__

//无符号类型的定义
#define uchar unsigned char
#define uint unsigned int 
	
#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int
	
//----------------------------------------


//全局宏定义
#define CPU_INT_DISABLE()  {__set_PRIMASK(1);} //关闭中断
#define CPU_INT_ENABLE()   {__set_PRIMASK(0);}  //打开中断

//全局类型定义
typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;

typedef enum //定义消息枚举类型
{
	MSG_NULL = 0,
	/******************************/
	//添加用户消息常量，例如：MSG_XXX,
	MSG_KEY1_PRESS,
	MSG_KEY2_PRESS,
	
	
	/******************************/
	MSG_NUM
	
}MSG_TYPE;

//-------------------------------------
#ifdef MAIN_CONFIG  //头文件被多个C调用时，避免变量冲突问题
	#define EXT
#else 
	#define EXT extern
#endif
	
//-------------------------------------
//RTOS相关头文件包含
#include <rthw.h>
#include <rtthread.h>
#include "Task.h"//自定义文件，Task.c中存放线程、定时器、IPC等相关代码
	
	
//-------------------------------------
	
//常用头文件包含
#include "stm32f1xx.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
	
#include "type.h"
//-------------------------------------
	
//外设驱动头文件包含
#include "system.h"
#include "SysTick.h"

#include "usart.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "adc.h"
#include "exti.h"
#include "Button.h"
#include "ChipInfo.h"
#include "BspDs18b20.h"
#include "delay.h"

#include "eeprom1.h"
//#include "Adc1.h"
#include "dma.h"
#include "adc11.h"
#include "BspTimer.h"


//----------------------------------------
//全局变量定义,请使用EXT修饰
EXT unsigned char g_Var;	
EXT rt_sem_t usart2_recv_sem;//定义串口2接收信号量控制块指针
EXT rt_mq_t  msg_mq;//定义消息队列控制块
EXT rt_timer_t ADCProcessSoftTimer;//软件定时器控制块指针
//----------------------------------------
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
