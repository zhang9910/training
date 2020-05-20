/**
 ********************************************************
 * @file           : beep.c
 * @details        : The file provides code for the configuration
                      of the  beep.
 * @author         : weijianx
 * @email          : 3176184465@qq.com
 * @date           : 2020-05-19
 * @version        : V1.0
 ********************************************************
*/

#include "beep.h"


/**
 * @brief       蜂鸣器 IO初始化
 * @retval       None
 */
void Beep_Init(void)
{

    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//开启GPIOA时钟

	
    GPIO_Initure.Pin=GPIO_PIN_5; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//推挽输出
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);

	
}

/**
 * @brief       开启蜂鸣器
 * @retval       None
 */
void BeepOn(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

/**
 * @brief       关闭蜂鸣器
 * @retval       None
 */
void BeepOff(void)
{

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}


