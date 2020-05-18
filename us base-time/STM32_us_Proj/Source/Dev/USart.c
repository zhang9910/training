#include "config.h"
#include "USart.h"

#if USART1_EN == 1
	uint8   g_USART1_RxBuf[USART1_RX_BUF_SIZE];//串口接收缓冲区
	uint16 	g_USART1_RecPos = 0;//存放当前串口接收数据存放的位置
#endif 

#if USART2_EN == 1
	uint8   g_USART2_RxBuf[USART2_RX_BUF_SIZE];//串口接收缓冲区
	uint16 	g_USART2_RecPos = 0;//存放当前串口接收数据存放的位置
#endif 

#if USART3_EN == 1
	uint8   g_USART3_RxBuf[USART3_RX_BUF_SIZE];//串口接收缓冲区
	uint16 	g_USART3_RecPos = 0;//存放当前串口接收数据存放的位置
#endif 

void UsartInit(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
#if USART1_EN == 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9 ;  //TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10 ;  //RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = USART1_BAUD;  
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);//初始化串口1
#if 0 //由于FinSH中rt_hw_console_getchar使用查询方式实现，故串口1中断初始化需注释掉
	//串口1中断初始化
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
#endif
	USART_Cmd(USART1, ENABLE);//使能串口1
	
  USART_ClearFlag(USART1, USART_FLAG_TC  );//清发送完成标志位
#endif


#if USART2_EN == 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2 ;  //TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 ;  //RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = USART2_BAUD;  
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructure);//初始化串口2
	
	//串口2中断初始化
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//添加串口空闲中断使能，请不要使用USART_IT_RXNE|USART_IT_IDLE，记住分开写两条语句

	USART_Cmd(USART2, ENABLE);//使能串口2
	
  USART_ClearFlag(USART2, USART_FLAG_TC  );//清发送完成标志位
#endif

#if USART3_EN == 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10 ;  //TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11 ;  //RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = USART3_BAUD;  
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No;
  USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART3, &USART_InitStructure);//初始化串口3
	
	//串口3中断初始化
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART3, ENABLE);//使能串口3
	
  USART_ClearFlag(USART3, USART_FLAG_TC  );//清发送完成标志位
#endif

}


//为能够调用printf函数从选定的串口打印输出，重定义fputc函数，本例子使用串口1
int fputc(int ch,FILE *f)
{
	
	USART_SendData(USART1, (uint8)ch);
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
	
	return (ch);

}

static void UsartSendByte(USART_TypeDef* USARTx,uint8 ch)
{
	
	USART_SendData(USARTx, (uint8)ch);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)== RESET);
}


void UsartSendString(USART_TypeDef* USARTx,uint8 *str)
{
	uint32 pos = 0;
	while(*(str+pos)!='\0')
	{
		UsartSendByte(USARTx,*(str+pos));
		pos ++;
		
	}

}



#if 0 //由于FinSH中rt_hw_console_getchar使用查询方式实现，故串口1中断回调需注释掉
//USART1_IRQHandler,串口1中断回调函数
void USART1_IRQHandler(void)
{
#if USART1_EN == 1 

#endif
	if( USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!=RESET )				// 串口接收数据 
	{		
#if USART1_EN == 1 

#endif
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
	if( USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET ) 				// 串口溢出错误
	{
			USART_ClearFlag(USART1, USART_FLAG_ORE);
	}
}
#endif




//USART2_IRQHandler,串口2中断回调函数
void USART2_IRQHandler(void)
{
	#if USART2_EN == 1 
		//用户代码
	 uint8 RecCh;
	#endif
	if( USART_GetFlagStatus(USART2,USART_FLAG_RXNE)!=RESET )				// 串口接收数据 
	{		
		#if USART2_EN == 1 
					 //用户代码
		RecCh = (uint8)USART_ReceiveData(USART2);
		g_USART2_RxBuf[g_USART2_RecPos++] = RecCh;
		
		#endif
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
	if( USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET ) 				// 串口溢出错误
	{
			USART_ClearFlag(USART2, USART_FLAG_ORE);
	}
	if( USART_GetFlagStatus(USART2,USART_FLAG_IDLE)==SET ) 				// 串口溢出错误
	{
		#if USART2_EN == 1 
					 //用户代码
		
		g_USART2_RxBuf[g_USART2_RecPos] = '\0';
		rt_sem_release(usart2_recv_sem);//释放一个信号量，表示数据已接收;给出二值信号量 ，发送接收到新数据帧标志，供前台线程查询
		
		#endif
		USART_ReceiveData(USART2);//使用该语句清除空闲中断标志位，请不要使用USART_ClearITPendingBit(USART2, USART_IT_IDLE);该语句无法达到效果
	}
}




//USART3_IRQHandler,串口3中断回调函数
void USART3_IRQHandler(void)
{
	#if USART3_EN == 1 
		//用户代码
	#endif

	if( USART_GetFlagStatus(USART3,USART_FLAG_RXNE)!=RESET )				// 串口接收数据 
	{		
		#if USART3_EN == 1 
			//用户代码
		#endif
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}
	if( USART_GetFlagStatus(USART3,USART_FLAG_ORE)==SET ) 				// 串口溢出错误
	{
			USART_ClearFlag(USART3, USART_FLAG_ORE);
	}
}


void rt_hw_console_output(const char *str)  //实现该函数，才能使用rt_kprintf
{

	 /* 进入临界段 */
  rt_enter_critical();
	
	while(*str!='\0')
	{
		 /* 换行 */
    if (*str == '\n')//RT-Thread 系统中已有的打印均以 \n 结尾，而并非 \r\n，所以在字符输出时，需要在输出 \n 之前输出 \r，完成回车与换行，否则系统打印出来的信息将只有换行
    {
       USART_SendData(USART1, '\r');
	
	     while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
    }

		USART_SendData(USART1, *(str++));
	
	  while(USART_GetFlagStatus(USART1, USART_FLAG_TC)== RESET);
		
	}
	 /* 退出临界段 */
  rt_exit_critical();  //注意：使用进入临界段语句rt_enter_critical(); 一定要使用退出临界段语句 rt_exit_critical();否则调度器锁住，无法进行调度
	
}

char rt_hw_console_getchar(void)//使用Finsh组件三步骤：1.实现该函数及rt_hw_console_output函数；2.rtconfig.h中开启RT_USING_FINSH宏;3.添加Finsh组件(cmd.c、msh.c、shell.c)，
{  //查询方式实现，记得将Usart1初始化中的中断接收配置相关代码注释掉
	   int ch = -1;
	   /*等待串口1输入数据*/
     if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
		 {
         ch = (int)USART_ReceiveData(USART1);
			   USART_ClearFlag(USART1, USART_FLAG_RXNE);
		 }
		 else
		 {
			 
         if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
         {
             USART_ClearFlag(USART1, USART_FLAG_ORE);
         }
         rt_thread_mdelay(10);
			 
		 }

     return ch;
}
