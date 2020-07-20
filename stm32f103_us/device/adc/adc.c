#include "adc.h"
#include "delay.h"


//ADC_HandleTypeDef ADC1_Handler;		//ADC���

////��ʼ��ADC
////ch: ADC_channels 
////ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
//void ADC_Init(void)
//{ 
//	RCC_PeriphCLKInitTypeDef ADC_CLKInit;
//	
//	ADC_CLKInit.PeriphClockSelection=RCC_PERIPHCLK_ADC;			//ADC����ʱ��
//	ADC_CLKInit.AdcClockSelection=RCC_ADCPCLK2_DIV6;			//��Ƶ����6ʱ��Ϊ72M/6=12MHz
//	HAL_RCCEx_PeriphCLKConfig(&ADC_CLKInit);					//����ADCʱ��
//	
//    ADC1_Handler.Instance=ADC1;
//    ADC1_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //�Ҷ���
//    ADC1_Handler.Init.ScanConvMode=DISABLE;                      //��ɨ��ģʽ
//    ADC1_Handler.Init.ContinuousConvMode=DISABLE;                //�ر�����ת��
//    ADC1_Handler.Init.NbrOfConversion=1;                         //1��ת���ڹ��������� Ҳ����ֻת����������1 
//    ADC1_Handler.Init.DiscontinuousConvMode=DISABLE;             //��ֹ����������ģʽ
//    ADC1_Handler.Init.NbrOfDiscConversion=0;                     //����������ͨ����Ϊ0
//    ADC1_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //��������
//    HAL_ADC_Init(&ADC1_Handler);                                 //��ʼ�� 
//	
//	HAL_ADCEx_Calibration_Start(&ADC1_Handler);					 //У׼ADC
//}

////ADC�ײ��������������ã�ʱ��ʹ��
////�˺����ᱻHAL_ADC_Init()����
////hadc:ADC���
//void HAL_ADC_MspInit1(ADC_HandleTypeDef* hadc)
//{
//    GPIO_InitTypeDef GPIO_Initure;
//    __HAL_RCC_ADC1_CLK_ENABLE();            //ʹ��ADC1ʱ��
//    __HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
//	
//    GPIO_Initure.Pin=GPIO_PIN_1;            //PA1
//    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
//    GPIO_Initure.Pull=GPIO_NOPULL;          //����������
//    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
//}

////���ADCֵ
////ch: ͨ��ֵ 0~16��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
////����ֵ:ת�����
//u16 Get_Adc(void)   
//{
//	uint16_t AD_Value;
//    uint32_t AD_Vol;
//	
//    ADC_ChannelConfTypeDef ADC1_ChanConf;
//    
//    ADC1_ChanConf.Channel=ADC_CHANNEL_1;                        //ͨ��
//    ADC1_ChanConf.Rank=1;                                       //��1�����У�����1
//    ADC1_ChanConf.SamplingTime=ADC_SAMPLETIME_239CYCLES_5;      //����ʱ��               
//    HAL_ADC_ConfigChannel(&ADC1_Handler,&ADC1_ChanConf);        //ͨ������
//	
//    HAL_ADC_Start(&ADC1_Handler);                               //����ADC
//	
//    HAL_ADC_PollForConversion(&ADC1_Handler,10);                //��ѯת��
// 
//	AD_Value = (uint16_t)HAL_ADC_GetValue(&ADC1_Handler);       //���һ��ADC1�������ת�����
//	
//	AD_Vol = AD_Value *3300 / 4096;
//	
//	return (uint16_t)AD_Vol;
//}

//��ȡָ��ͨ����ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
//u16 Get_Adc_Average(u32 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc(ch);
//		delay_ms(5);
//	}
//	return temp_val/times;
//} 