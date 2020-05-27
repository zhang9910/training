#ifndef __ADC1_H__
#define __ADC1_H__




#define ADC_EN   1


#if ADC_EN == 1

#define NbrOfChannel 4
extern __IO uint16 ADCConvertedValue[NbrOfChannel] ;
void AdcInit(void);


#endif





#endif
