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
// uint32_t ADCConvertedValue[NbrOfChannel] ;


extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

//void AdcDMAInit(void);
static void ADC_RegularChannelConfig(ADC_HandleTypeDef *AdcHandle, uint32_t Channel, uint32_t Rank, uint32_t SamplingTime);


#endif





#endif
