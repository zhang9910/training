#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"


//外部中断初始化
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //开启GPIOA时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //上升沿触发
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_15; 				//PA15
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_5 | GPIO_PIN_4; 				//PC5
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
    //中断线0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,3);       //抢占优先级为2，子优先级为3
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0
    
	//中断线5-PC5
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,2);   	//抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); 
	
	//中断线4-PC4
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,1);   	//抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI4_IRQn); 
	
    //中断线15-PA15
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,0); 	//抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);        	//使能中断线2
}


//void ExtiModeInit(void)
//{
//	EXTI_InitTypeDef  EXTI_InitStructure;
//	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//	
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStructure);
//	
//}

//中断服务函数
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);		//调用中断处理公用函数
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);		//调用中断处理公用函数
	
//	if(__HAL_GPIO_EXTI_GET_FLAG(GPIO_PIN_4) == SET)
//		__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_4);
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);		//调用中断处理公用函数
}

void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);		//调用中断处理公用函数
}


//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//    delay_ms(100);      	//消抖
//    switch(GPIO_Pin)
//    {
//        case GPIO_PIN_0:
//            if(WK_UP==1) 
//            {
//				LED1=!LED1;	//控制LED0,LED1互斥点亮
//				LED0=!LED1;
//            }
//            break;
//        case GPIO_PIN_5:
//            if(KEY0==0)  	//控制LED0翻转 
//            {
//                LED0=!LED0;
//            }
//            break;
//        case GPIO_PIN_15:
//            if(KEY1==0)  
//            {
//				LED1=!LED1;	//控制LED0翻转
//            }
//            break;
//    }
//}
