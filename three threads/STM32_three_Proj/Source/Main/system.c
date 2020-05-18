#include "config.h"
#include "system.h"


void CpuInit(void)
{
	//CPU相关设置
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择第2组中断优先级，即2位主优先级，2位次优先级
	
}

void SysInit(void)
{
	
	CpuInit();//配置系统信息
	
	
	//外设驱动初始化
	SysTickInit();//系统滴答定时器初始化
	LedGpioInit();//LED初始化
	BeepGpioInit();//Beep蜂鸣器初始化
	UsartInit();//串口初始化
	TaskInit();//任务初始化
	

	
}

#define  ATaskPeriod 200
#define  BTaskPeriod 300
#define  CTaskPeriod 2000
#define  Usart1ControlBeepPeriod 20



void ATask(void);//声明A任务函数
void BTask(void);//声明B任务函数
void CTask(void);
void Usart1ControlBeepTask(void);



void  TaskInit(void)
{
	ATaskTimer = ATaskPeriod;//A任务每隔ATaskPeriod ms运行一次
	BTaskTimer = BTaskPeriod;//B任务每隔BTaskPeriod ms运行一次
	CTaskTimer = CTaskPeriod;//C任务每隔CTaskPeriod ms运行一次
  Usart1ControlBeepTimer = Usart1ControlBeepPeriod ;
	
}
void  TaskRun(void)
{
	ATask();//PA.0 任务
	BTask();//PA.1 任务
	CTask();
	Usart1ControlBeepTask();

}

void ATask(void)
{
	static uint8  cnt;
	
	if(ATaskTimer) return;
	ATaskTimer = ATaskPeriod;
	
	//以下补充任务代码
	if(++cnt % 2 == 0)
	{	
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		cnt = 0;
	}
  else
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	
	
}

void BTask(void)
{
	static uint8  cnt;
	if(BTaskTimer) return;
	BTaskTimer = BTaskPeriod;
	
	//以下补充任务代码
	
	if(++cnt % 2 == 0)
	{	
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		cnt = 0;
	}
  else
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void CTask(void)
{

	if(CTaskTimer) return;
	CTaskTimer = CTaskPeriod;
	
	//以下补充任务代码
  printf("System Total Run time is %f s\n",GetRunTime()/1000.0);
	UsartSendString(USART1,"CTask is Running.\n--------------------------------\n");
	UsartSendString(USART2,"USART2 is Sending.\n--------------------------------\n");
}

void Usart1ControlBeepTask(void)
{
	if(Usart1ControlBeepTimer) return;
	Usart1ControlBeepTimer = Usart1ControlBeepPeriod ;
	//以下补充任务代码
	Usart1_RecProcess();
}



