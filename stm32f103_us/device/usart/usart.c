/**
 ********************************************************
 * @file           : usart.c
 * @details        : The file provides code for the configuration, 
                     receiving and sending of the usart instances.
 * @author         : weijianx
 * @email          : 3176184465@qq.com
 * @date           : 2020-05-19
 * @version        : V1.0
 ********************************************************
*/

#include "usart.h"	
#include "config.h"


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (uint8_t) ch;      
	return ch;
}
#endif 



//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
uint8_t USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
uint16_t USART_RX_STA=0;       //接收状态标记	  

//BitAction UartRecvFrameOK = Bit_RESET;

uint8_t aRxBuffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲
UART_HandleTypeDef UART1_Handler; //UART1句柄
UART_HandleTypeDef UART2_Handler; //UART2句柄
  
/**
 * @brief        Initialize the UART mode
 * @param        bound 波特率
 * @retval       None
 */
void uart_init(uint32_t bound)
{	
#if EN_USART1_RX   //如果使能了接收
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    //USART1
	UART1_Handler.Init.BaudRate=bound;				    //波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
	
#endif
	
#if EN_USART2_RX   //如果使能了接收
	//UART 初始化设置
	UART2_Handler.Instance=USART2;					    //USART1
	UART2_Handler.Init.BaudRate=bound;				    //波特率
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
	
#endif
  
}

/** 
 * @brief     UART底层初始化，时钟使能，引脚配置，中断配置
 * @brief     此函数会被HAL_UART_Init()调用
 * @param     huart,串口句柄
 * @retval    None
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
#if EN_USART1_RX
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//抢占优先级3，子优先级3
#endif	
	}
	
	if(huart->Instance==USART2)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART2_CLK_ENABLE();			//使能USART1时钟
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
#if EN_USART2_RX
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//抢占优先级3，子优先级3
#endif	
	}
}

/** 
 * @brief        串口接收回调函数
 * @param        huart,串口句柄 
 * @retval       None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	if(huart->Instance==USART1)//如果是串口1
	{
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了 
		
			}
			else //还没收到0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}

	}
	
	if(huart->Instance==USART2)//如果是串口2
	{
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else 
				{
					USART_RX_STA|=0x8000;	//接收完成了 
				
					USART_RX_BUF[USART_RX_STA]='\0';
					rt_sem_release(usart2_recv_sem);//释放一个信号量，表示数据已接收;给出二值信号量 ，发送接收到新数据帧标志，供前台线程查询
				}
			}
			else //还没收到0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}

	}
}

/** 
 * @brief    串口1中断服务程序
 * @retval   None
 */
#if 0
void USART1_IRQHandler(void)                	
{ 
	uint32_t timeout=0;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&UART1_Handler);	//调用HAL库中断处理公用函数
	
	timeout=0;
    while (HAL_UART_GetState(&UART1_Handler) != HAL_UART_STATE_READY)//等待就绪
	{
		timeout++;////超时处理
		if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
		timeout++; //超时处理
		if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 
#endif


void USART2_IRQHandler(void)                	
{ 
	uint32_t timeout=0;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&UART2_Handler);	//调用HAL库中断处理公用函数
	
	timeout=0;
    while (HAL_UART_GetState(&UART2_Handler) != HAL_UART_STATE_READY)//等待就绪
	{
		timeout++;////超时处理
		if(timeout>HAL_MAX_DELAY) break;		
	
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
		timeout++; //超时处理
		if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 


/** 
 * @brief       串口1接收处理函数，当接收到相应的信息时，
                便会触发相应的事件
 * @retval      TRUE    
 */
//unsigned char USART1_RecProcess(void)
//{
//	
//#if EN_USART1_RX == 1 
////	if(USART1RecTimer) return FALSE;
//	if(!USART_RX_STA) return FALSE;
//	
//	USART_RX_BUF[USART_RX_STA]='\0';
//	
//	//收包处理
////	"Beep On" 
////	"BeeP Off"
//	if(strstr((char *)USART_RX_BUF,"Beep On")!= NULL)
//	{
////		BeepOn();
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
//	}
//	else if(strstr((char *)USART_RX_BUF,"Beep Off")!= NULL)
//	{
////		BeepOff();
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
//	}
//	//memset(g_USART1_RxBuf,0,USART1_RX_BUF_SIZE);
//	USART_RX_STA = 0;
//	
//#endif

//	return TRUE;
//}


void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    __HAL_UNLOCK(&UART1_Handler);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&UART1_Handler, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&UART1_Handler, (uint8_t *)(str + i), 1, 1);
    }
}


char rt_hw_console_getchar(void)//使用Finsh组件三步骤：1.实现该函数及rt_hw_console_output函数；2.rtconfig.h中开启RT_USING_FINSH宏;3.添加Finsh组件(cmd.c、msh.c、shell.c)，
{  //查询方式实现，记得将USART1初始化中的中断接收配置相关代码注释掉
	 int ch = -1;
	   /*等待串口1输入数据*/
     if(__HAL_UART_GET_FLAG(&UART1_Handler, USART_FLAG_RXNE) != RESET)
	 {

		 HAL_UART_Receive(&UART1_Handler, (uint8_t*)ch, sizeof(ch), 1000);
		 __HAL_UART_CLEAR_FLAG(&UART1_Handler, USART_FLAG_RXNE);
	 }
	 else
	 {
		 
		 if(__HAL_UART_GET_FLAG(&UART1_Handler, USART_FLAG_ORE) != RESET)
		 {
//			 USART_ClearFlag(USART1, USART_FLAG_ORE);
			 __HAL_UART_CLEAR_FLAG(&UART1_Handler, USART_FLAG_ORE);
		 }
		 rt_thread_mdelay(10);
			 
	 }

     return ch;
}
