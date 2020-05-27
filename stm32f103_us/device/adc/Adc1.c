#include "config.h"
#include "Adc1.h"

#if ADC_EN == 1

__IO uint16 ADCConvertedValue[NbrOfChannel] = {0};

ADC_HandleTypeDef hadc1;         //ADC1句柄
DMA_HandleTypeDef hdma_adc1;     //ADC1_DMA句柄

void AdcGpioInit(void);
//void AdcDMAInit(void);
void AdcModeInit(void);

void AdcInit(void)
{
	//	AdcDMAInit();
	AdcModeInit();
//	HAL_ADC_MspInit(&hadc1);

	

}	

void AdcModeInit(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	RCC_PeriphCLKInitTypeDef ADC_CLKInit;
	
	ADC_CLKInit.PeriphClockSelection=RCC_PERIPHCLK_ADC;			//ADC外设时钟
	ADC_CLKInit.AdcClockSelection=RCC_ADCPCLK2_DIV6;			//分频因子6时钟为72M/6=12MHz
	HAL_RCCEx_PeriphCLKConfig(&ADC_CLKInit);					//设置ADC时钟
	
    hadc1.Instance=ADC1;
    hadc1.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //右对齐
    hadc1.Init.ScanConvMode=DISABLE;                      //非扫描模式
    hadc1.Init.ContinuousConvMode=DISABLE;                //关闭连续转换
    hadc1.Init.NbrOfConversion=1;                         //1个转换在规则序列中 也就是只转换规则序列1 
    hadc1.Init.DiscontinuousConvMode=DISABLE;             //禁止不连续采样模式
    hadc1.Init.NbrOfDiscConversion=0;                     //不连续采样通道数为0
    hadc1.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //软件触发
    HAL_ADC_Init(&hadc1);                                 //初始化 
	
	HAL_ADCEx_Calibration_Start(&hadc1);					 //校准ADC
	
	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

}

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
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
//    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
//    {
//      Error_Handler();
//    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */
  	//开启ADC的DMA模式
	
	HAL_ADC_Start_DMA(adcHandle, (uint32_t*)ADCConvertedValue, 4);

  /* USER CODE END ADC1_MspInit 1 */
  }
}


/*************************************************************************
*                            变量定义
*************************************************************************
*/


/*************************************************************************
*                             软件定时器回调函数定义
*************************************************************************
*/
static void ADCProcessSoftTimer_callback(void* parameter)
{
  printf("\r\n ADC1 CH10(PC0) value = %.2f V \r\n",(float)ADCConvertedValue[0]/4096 * 3.3);

}

int ADCProcessInit()
{
	AdcInit();//ADC初始化
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


