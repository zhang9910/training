#include "config.h"
#include "Gpio.h"

void LedGpioInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
	
}
void LedControl(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
	SysTickDelayMs(1000);
  GPIO_ResetBits(GPIOA, GPIO_Pin_0|GPIO_Pin_1);
	SysTickDelayMs(1000);
	
}


void BeepGpioInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_5 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void BeepOn(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

void BeepOff(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

