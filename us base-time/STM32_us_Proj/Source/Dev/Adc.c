#include "config.h"
#include "Adc.h"

#if ADC_EN == 1

__IO uint16 ADCConvertedValue[NbrOfChannel] = {0};

void AdcGpioInit(void);
void AdcDMAInit(void);
void AdcModeInit(void);

void AdcInit(void)
{
	AdcGpioInit();
	AdcDMAInit();
	AdcModeInit();

}	

void AdcGpioInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* Configure PC.0 (ADC Channel10)、PC.1 (ADC Channel11)、PC.2 (ADC Channel12)、PC.3 (ADC Channel13) as analog input -------------------------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void AdcDMAInit(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	 /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32)(&(ADC1->DR));
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = NbrOfChannel;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
}
void AdcModeInit(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
  RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	/* Enable ADC1clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	/* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = NbrOfChannel;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 4, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	
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


