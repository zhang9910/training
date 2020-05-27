/* Includes ------------------------------------------------------------------*/
#include "tim2.h"
#include "config.h"

/* USER CODE BEGIN 0 */
uint8_t timer2_state = 0;
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 72-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
//    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
//    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
//    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
}

////定时器3中断服务函数
//void TIM2_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&htim2);
//}

////回调函数，定时器中断服务函数调用
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if(htim==(&htim2))
//    {
//		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_2);
//		rt_thread_mdelay(2000);
////        ButtonProj();//按键定时扫描
//    }
//}


//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	static uint32_t time_cnt =0;

//	if(htim->Instance == TIM2)
//	{
//		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_2);
////			rt_thread_mdelay(500);	
////		if(++time_cnt > 1000)//计时1s置位标志
////		{
////			time_cnt =0;
////			
////			timer2_state = 1;//置位标志
////		}
////		if ( __HAL_TIM_GET_IT_SOURCE(&htim2, TIM_IT_UPDATE) != RESET ) 
////		{	
////			//----------------------------------------------------------
////			//填充用户代码 Add User Code
////			
////			ButtonProj();//按键定时扫描

////				
////			

////			//---------------------------------------------------------
////	//		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  
////			__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
////		}	
//	}

//}
