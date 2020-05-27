/**
 ********************************************************
 * @file           : system.c
 * @brief          : The file describes the execution of 
                     various tasks of the system
 * @author         : weijianx
 * @email          : 3176184465@qq.com
 * @date           : 2020-05-19
 * @version        : V1.0
 ********************************************************
*/

#include "config.h"
#include "system.h"



/** 
 * @brief      CPU相关设置
 * @retval     None
 */
void CpuInit(void)
{
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择第2组中断优先级，即2位主优先级，2位次优先级
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);     //设置优先级为分组2
}

/** 
 * @brief        系统初始化
 * @retval       None
 */
void SysInit(void)
{
	
	CpuInit();//配置系统信息
	
	
	//外设驱动初始化
	SysTickInit();//系统滴答定时器初始化
	
	HAL_Init();                    	 	    //初始化HAL库    
	delay_init(72);               		    //初始化延时函数
	uart_init(115200);					    //初始化串口
	LED_Init();							    //初始化LED	
	KEY_Init();							    //初始化按键
	Beep_Init();                            //初始化蜂鸣器
	ADC_Init();                             //初始化ADC
	EXTI_Init();                            //初始化中断
	Tim2Init(72,1000);                      //中断周期为1ms,用于按键扫描
//	MX_ADC1_Init();
	MX_DMA_Init();

	
}



