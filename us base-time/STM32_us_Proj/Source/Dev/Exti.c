#include "config.h"
#include "Exti.h"


void ExtiGpioInit(void);
void ExtiNvicInit(void);
void ExtiModeInit(void);

void ExtiInit(void)
{
	ExtiGpioInit();
	ExtiNvicInit();
	ExtiModeInit();
}
void ExtiGpioInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}
void ExtiNvicInit(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
void ExtiModeInit(void)
{
	EXTI_InitTypeDef  EXTI_InitStructure;
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}

#if 0
void EXTI2_IRQHandler (void)
{
#if 0
	MSG_TYPE msg = MSG_KEY2_PRESS;
#endif
	if(EXTI_GetITStatus(EXTI_Line2) == SET )
	{
		//用户代码
#if 0		
		rt_mq_send(msg_mq,       // 写入（发送）队列的ID(句柄)
		           &msg,         // 写入（发送）的数据所对应地址 
		           sizeof(msg)   // 数据的长度 
							);
#endif		
		//--------------------------------
		EXTI_ClearFlag(EXTI_Line2);
	}
}
#endif

#if 0
void EXTI3_IRQHandler (void)
{
#if 0
	MSG_TYPE msg = MSG_KEY1_PRESS;
#endif
	if(EXTI_GetITStatus(EXTI_Line3) == SET )
	{
		//用户代码
#if 0		
	rt_mq_send(msg_mq,		// 写入（发送）队列的ID(句柄)
						 &msg,  		// 写入（发送）的数据所对应地址 
						 sizeof(msg)// 数据的长度 
						);
#endif		
		//--------------------------------
		EXTI_ClearFlag(EXTI_Line3);
	}
}
#endif

void EXTI4_IRQHandler (void)
{

	if(EXTI_GetITStatus(EXTI_Line4) == SET )
	{
		//用户代码
//	   printf("PC4 Press!\n");
		//--------------------------------
		EXTI_ClearFlag(EXTI_Line4);
	}
}


void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET )
	{
		//用户代码
//		printf("PC5 Press!\n");
		
		//--------------------------------
		
		EXTI_ClearFlag(EXTI_Line5);
	}
}

