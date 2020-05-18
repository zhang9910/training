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

//-------------------------------------
#ifdef MAIN_CONFIG  //头文件被多个C调用时，避免变量冲突问题
	#define EXT
#else 
	#define EXT extern
#endif
	

	
//-------------------------------------
	
//常用头文件包含
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
	
//-------------------------------------
	
//外设驱动头文件包含
#include "system.h"
#include "SysTick.h"
#include "Gpio.h"
#include "USart.h"
	

		
//----------------------------------------
//全局变量定义,请使用EXT修饰
EXT unsigned char g_Var;	

//----------------------------------------
#endif

/********************************************************************************************************
**                            End Of File
********************************************************************************************************/
