/**
 ********************************************************
 * @file           : BspTimer.c
 * @brief          : Project file name BspTimer.c
 * @details        : The file provides code for the configuration of the tim2.
 * @version        : V1.0
 ********************************************************
*/


#include "config.h"
#include "BspTimer.h"

//定时器2句柄
TIM_HandleTypeDef TIM_TimeBaseStructure;

/**
 *@brief      通用定时器3中断初始化
 *@param      prescaler：自动重装值。
 *@param      period：时钟预分频数
 *@retval     None
 */
void Tim2ModeInit(int prescaler,int period)
{
	
	TIM_TimeBaseStructure.Instance = TIM2;									//重新将Timer设置为缺省值
//	TIM_InternalClockConfig(TIM2);							//采用内部时钟给TIM2提供时钟源
	TIM_TimeBaseStructure.Init.Prescaler = (uint16_t)(prescaler-1);//例如prescaler=7200;			//预分频系数为7200-1，这样计数器时钟为72MHz/7200 = 10kHz。注意：预分频系数取值范围为1-65535
	TIM_TimeBaseStructure.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;	//设置时钟分割
	TIM_TimeBaseStructure.Init.CounterMode = TIM_COUNTERMODE_UP;	//设置计数器模式为向上计数模式
	TIM_TimeBaseStructure.Init.Period = (period<2)?1:period-1;		//设置计数溢出大小，每计period个数就产生一个更新事件
	HAL_TIM_Base_Init(&TIM_TimeBaseStructure);			//将配置应用到TIM2中
//	TIM_ARRPreloadConfig(TIM2, DISABLE);					//禁止ARR预装载缓冲器
	HAL_TIM_Base_Start_IT(&TIM_TimeBaseStructure); //使能定时器2和定时器2更新中断：TIM_IT_UPDATE 
	
}

/**
 *@brief    定时器底册驱动，开启时钟，设置中断优先级
 *@retval   None
 */
void Tim2NvicInit(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE();            //使能TIM2时钟
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

}




/*******************************************************************************************************
** 函数: Tim2Init, Tim定时器延时函数
**------------------------------------------------------------------------------------------------------
** 参数: prescaler 预分频系数
         period  计数周期
Example:
若：
	TIM_Period 即Auto Reload Register(ARR) = 1000  , TIM_Prescaler--71 
则：中断周期为 = 1/(72MHZ /72) * 1000 = 1ms

	TIMxCLK/CK_PSC --> TIMxCNT --> TIM_Period(ARR) --> 中断 且TIMxCNT重置为0重新计数 
        
** 返回: void
********************************************************************************************************/
void Tim2Init(int prescaler,int period)
{
	Tim2ModeInit(prescaler,period);
	Tim2NvicInit();
	

//  TIM_ClearFlag(TIM2, TIM_FLAG_Update);					//清除溢出中断标志
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);				//开启TIM2的中断
//	TIM_Cmd(TIM2,ENABLE);
	
	__HAL_TIM_CLEAR_FLAG(&TIM_TimeBaseStructure, TIM_FLAG_UPDATE);
	__HAL_TIM_ENABLE_IT(&TIM_TimeBaseStructure, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(&TIM_TimeBaseStructure);
	
}

/**
 *@brief       定时器2中断服务函数
 *@retval      None
 */
void  TIM2_IRQHandler(void)
{


	if ( __HAL_TIM_GET_IT_SOURCE(&TIM_TimeBaseStructure, TIM_IT_UPDATE) != RESET ) 
	{	
		//----------------------------------------------------------
		//填充用户代码 Add User Code
		
		ButtonProj();//按键定时扫描


		//---------------------------------------------------------
//		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  
		__HAL_TIM_CLEAR_IT(&TIM_TimeBaseStructure, TIM_IT_UPDATE);
	}		 	
}



