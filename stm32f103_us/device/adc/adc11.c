/*USER CODE BEGIN Header*/
/**
 ********************************************************
 * @file           : adc11.c
 * @brief          : Project file name adc11.c
 * @details        : The file provides code for the configuration 
                      of the adc1.
 * @author         : weijianx
 * @email          : 3176184465@qq.com
 * @date           : 2020-05-27
 * @version        : V1.0
 ********************************************************
*/


#include "adc11.h"

#if ADC1_EN == 1

__IO uint16 ADCConvertedValue[NbrOfChannel] = {0};

ADC_HandleTypeDef hadc1;         //ADC1句柄
DMA_HandleTypeDef hdma_adc1;     //ADC1_DMA句柄

/**
 *@brief       adc1初始化
 *@retval      None
 */
/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 4;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
//    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
//    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
//    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
//    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
//    Error_Handler();
  }

}

/**
 *@brief     ADC底层驱动，引脚配置，时钟使能
 *@brief     此函数会被HAL_ADC_Init()调用
 *@param     hadc:ADC句柄
 *@retval    None
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**ADC1 GPIO Configuration    
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
//      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

    /* ADC1 interrupt Init */
    HAL_NVIC_SetPriority(ADC1_2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
  /* USER CODE BEGIN ADC1_MspInit 1 */

//	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADCConvertedValue, NbrOfChannel);
  /* USER CODE END ADC1_MspInit 1 */
  }
}


/*************************************************************************
*                             软件定时器回调函数定义
*************************************************************************
*/
static void ADCProcessSoftTimer_callback(void* parameter)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADCConvertedValue, 100);
	printf("\r\n ADC1 CH10(PC0) value = %.2f V \r\n",(float)ADCConvertedValue[0]/4096 * 3.3);

}


int ADCProcessInit()
{
	MX_ADC1_Init();//ADC初始化
	ADCProcessSoftTimer = rt_timer_create("ADCProcessSoftTimer", /* 软件定时器的名称 */
                        ADCProcessSoftTimer_callback,/* 软件定时器的回调函数 */
                        0,			/* 定时器超时函数的入口参数 */
                        2*RT_TICK_PER_SECOND,   /* 软件定时器的超时时间(周期回调时间) */
                        RT_TIMER_FLAG_PERIODIC );
                        /* 软件定时器HARD_TIMER模式 周期模式 */
 
	
	return 0;
}
	
INIT_APP_EXPORT(ADCProcessInit);


#endif




