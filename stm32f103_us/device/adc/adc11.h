/**
 * @file      : adc11.h
 * @brief     : Header for adc11.c file.
*/


#ifndef __ADC11_H__
#define __ADC11_H__

#include "config.h"


#define ADC1_EN   1


#if ADC1_EN == 1

#define NbrOfChannel 4
extern __IO uint16 ADCConvertedValue[NbrOfChannel] ;    //adc1四通道接收数据的数组


extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC1_Init(void);

#endif





#endif
