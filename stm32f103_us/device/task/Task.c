/**
 ********************************************************
 * @file           : Tak.c
 * @brief          : Project file name Task.c
 * @details        : This file describes the execution of threaded tasks.
 * @version        : V1.0
 ********************************************************
*/


#include "config.h"
#include "Task.h"

/*************************************************************************
*                            变量定义
*************************************************************************
*/



static rt_thread_t dynamic_thread = RT_NULL;//动态线程控制块指针
rt_sem_t usart2_recv_sem;//定义串口2接收信号量控制块指针
rt_mq_t  msg_mq;//定义消息队列控制块
/*************************************************************************
*                             线程入口函数声明
*************************************************************************
*/
void led_thread_entry(void *parameter);
void usart2_recv_thread_entry(void *parameter);//串口2接收处理入口函数
void msg_process_thread_entry(void *parameter);//用户消息处理入口函数
void adc_getVol_thread_entry(void *parameter);//ADC获取电压值
void led1_thread_entry(void *parameter);
	
	
/*************************************************************************
*                             线程结构体数组(适合线程动态创建)
*************************************************************************
*/
TaskStruct TaskThreads[] = {
			{"ledThread", led_thread_entry,  RT_NULL,  256,  5, 10},
			{"usart2_recv_thread", usart2_recv_thread_entry, 	RT_NULL, 512, 2, 	10 	},
			{"msg_process_thread",  msg_process_thread_entry, RT_NULL, 512, 2,   10 },
			{"adc_getVol_thread",adc_getVol_thread_entry, RT_NULL, 512, 2, 10},
			{"led1_thread", led1_thread_entry, RT_NULL, 256, 2, 10},  
			
			/*********************************************************/
			//改变栈的大小，可改变线程数量；也可通过改变 rtconfig.h 中的 RT_MAIN_THREAD_STACK_SIZE 大小，来改变线程数量
			//用户添加线程参数
			//例如：{线程名字,线程入口函数,线程入口函数参数,线程栈大小,线程的优先级,线程时间片},
			
			
			
			{"",RT_NULL, RT_NULL,RT_NULL,RT_NULL,RT_NULL}
	
};
	
	
/**
 *@brief      初始化任务
 *@retval     None
 */
void TaskInit(void)
{
	uint8_t TaskThreadIndex = 0;
	usart2_recv_sem = rt_sem_create("usart2_recv_sem",  //信号量名字
									0,                  //信号量初始值
									RT_IPC_FLAG_FIFO    //信号量模式 FIFO(0x00)
	                                );
	
	if(usart2_recv_sem != RT_NULL)
		rt_kprintf("信号量usart2_recv_sem创建成功\n\n");
	
	msg_mq = rt_mq_create("msg_mq",							//消息队列名字
						   32,  									//消息的最大长度, bytes
						   10,										//消息队列的最大容量(个数)
						   RT_IPC_FLAG_FIFO			//队列模式 FIFO
	                     );
	if(msg_mq != RT_NULL)
		rt_kprintf("消息队列key_mq创建成功\n\n");
	
	 while(1)
	 {
		 if(strcmp(TaskThreads[TaskThreadIndex].name,"") != 0)
		 {
			 
				dynamic_thread = rt_thread_create(TaskThreads[TaskThreadIndex].name,       // 线程名字 
                                TaskThreads[TaskThreadIndex].entry,  // 线程入口函数 
                                TaskThreads[TaskThreadIndex].parameter,           // 线程入口函数参数
                                TaskThreads[TaskThreadIndex].stack_size,               // 线程栈大小 
                                TaskThreads[TaskThreadIndex].priority,                 // 线程的优先级 
                                TaskThreads[TaskThreadIndex].tick                 // 线程时间片
                   	            );
				if(dynamic_thread != RT_NULL)
				{
					rt_thread_startup(dynamic_thread);
				}
			  TaskThreadIndex ++;
		 }
		 else
			 break;
		 
	 }
}


/*************************************************************************
*                             线程入口函数定义
*************************************************************************
*/

/**
 *@brief      执行线程，灯0的变化
 *@retval     None
 */
void led_thread_entry(void *parameter)
{//led线程，每隔2s,变换PA.1状态
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_2);
	    rt_thread_mdelay(2000);	
		rt_kprintf("System Running Time:%d s \r\n",rt_tick_get()/RT_TICK_PER_SECOND);
	}
}

/**
 *@brief      执行线程，串口2信息的接收
 *@retval     None
 */
void usart2_recv_thread_entry(void *parameter)
{//串口2接收处理
	rt_err_t uwRet = RT_EOK;
	while(1)
	{
		 uwRet =rt_sem_take(usart2_recv_sem, RT_WAITING_FOREVER);//获取串口2接收帧完成信号量
		 if(RT_EOK == uwRet )
		 {
			 rt_kprintf("Usart2 Receive Data:%s\n",USART_RX_BUF);
			 
			if(strstr((char *)USART_RX_BUF,"Beep On")!= NULL)
			{
		//		BeepOn();
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
			}
			else if(strstr((char *)USART_RX_BUF,"Beep Off")!= NULL)
			{
		//		BeepOff();
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
			}
			 memset(USART_RX_BUF,0,USART_REC_LEN);//清零
			 USART_RX_STA = 0;
		 }
	}
}

/**
 *@brief      执行线程，按键的读取
 *@retval     None
 */
void msg_process_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK;
	uint8_t r_queue;//用于接收msg_mq消息队列信息
	
	while(1)
	{  //获取队列信息

		 uwRet = rt_mq_recv(msg_mq,
							&r_queue,
							sizeof(r_queue),
							RT_WAITING_FOREVER
							);
		 if(RT_EOK == uwRet )
		 {
			 switch(r_queue)//根据接收到的消息内容分别进行处理
			 {
#if 0
				 case MSG_KEY1_PRESS:rt_kprintf("Receive message:KEY1(PE.3) is press\n\n");break;
				 case MSG_KEY2_PRESS:rt_kprintf("Receive message:KEY2(PE.2) is press\n\n");break;
				 default: rt_kprintf("No Message!\n\n");break;
#endif				 
			 }
			
		 }
		 else
		 {
			 rt_kprintf("数据接收错误，错误代码：0x%lx\n\n",uwRet);
		 }
	}				
	
}

/**
 *@brief      执行线程，获取电压值
 *@retval     None
 */
void adc_getVol_thread_entry(void *parameter)
{
	uint16_t val;
	
	while(1)
	{
		val = Get_Adc();
		rt_kprintf("the vol is %d mv\r\n", val);
		rt_thread_mdelay(1000);
	}
}


/**
 *@brief      执行线程，灯1的变化
 *@retval     None
 */
void led1_thread_entry(void *parameter)
{

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
		rt_thread_mdelay(1000);

	}
}


