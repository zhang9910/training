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
	TaskInit();                             //任务初始化
	

	
}

/***************宏定义任务时钟间隔*************/
#define  ATaskPeriod 1000
#define  BTaskPeriod 1000
#define  CTaskPeriod 2000
#define  Usart1ControlBeepPeriod 20
/**********************************************/

/*****************函数声明*********************/
void ATask(void);//声明A任务函数
void BTask(void);//声明B任务函数
void CTask(void);//声明C任务函数
void Usart1ControlBeepTask(void);
/**********************************************/

/** 
 * @brief        每个任务的时钟设置
 * @retval       None
 */
void  TaskInit(void)
{
	ATaskTimer = ATaskPeriod;//A任务每隔ATaskPeriod ms运行一次
	BTaskTimer = BTaskPeriod;//B任务每隔BTaskPeriod ms运行一次
	CTaskTimer = CTaskPeriod;//C任务每隔CTaskPeriod ms运行一次
    Usart1ControlBeepTimer = Usart1ControlBeepPeriod ;
	
}

/** 
 * @brief       任务执行
 * @retval      None
 */
void  TaskRun(void)
{
	ATask();//PA.8 任务
	BTask();//PD.2 任务
	CTask();
	Usart1ControlBeepTask();

}

/** 
 * @brief         执行任务A，PA.8灯的闪烁
 * @retval        None
 */
void ATask(void)
{
	static uint8  cnt;
	
	if(ATaskTimer) return;
	ATaskTimer = ATaskPeriod;
	
	//以下补充任务代码
	if(++cnt % 2 == 0)
	{	
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		cnt = 0;
	}
  else
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	
	
}

/** 
 * @brief         执行任务B，PD.2灯的闪烁
 * @retval        None
 */
void BTask(void)
{
	static uint8  cnt;
	if(BTaskTimer) return;
	BTaskTimer = BTaskPeriod;
	
	//以下补充任务代码
	
	if(++cnt % 2 == 0)
	{	
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
		cnt = 0;
	}
    else
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
}

/** 
 * @brief         执行任务C，串口1的传输
 * @retval        None
 */
void CTask(void)
{
	uint8_t tx_buf1[]="CTask is Running.\r\n";
	uint8_t tx_buf2[]="USART2 is Sending.\r\n";

	if(CTaskTimer) return;
	CTaskTimer = CTaskPeriod;
	
	//以下补充任务代码
    printf("System Total Run time is %f s\r\n",GetRunTime()/1000.0);
	HAL_UART_Transmit(&UART1_Handler, (uint8_t*)tx_buf1, sizeof(tx_buf1), 1000);
	HAL_UART_Transmit(&UART1_Handler, (uint8_t*)tx_buf2, sizeof(tx_buf2), 1000);

}

/** 
 * @brief           执行串口的任务
 * @retval          None
 */
void Usart1ControlBeepTask(void)
{
	if(Usart1ControlBeepTimer) return;
	Usart1ControlBeepTimer = Usart1ControlBeepPeriod ;
	//以下补充任务代码
	Usart1_RecProcess();
}



