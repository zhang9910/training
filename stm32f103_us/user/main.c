/*USER CODE BEGIN Header*/
/**
 ********************************************************
 * @file           : main.c
 * @brief          : Project file name main.c
 * @details        : frame of Project main function enter
 * @author         : weijianx
 * @email          : 3176184465@qq.com
 * @date           : 2020-05-19
 * @version        : V1.0
 ********************************************************
 * @attention
 * @brief hardware platefrom:STM32F103
 ********************************************************
*/

#include "config.h"
#include "system.h"


u8 time_tick = 10;  //默认滤波方式  为平稳滤波

/**
 * @brief        主函数
 * @brief        程序的入口
 * @retval       None
 */
int main(void)
{ 

//	SysInit();        //系统初始化       
    TaskInit();

    while(1)
    {	

	
		rt_thread_mdelay(1000);
		
    }
	
}

