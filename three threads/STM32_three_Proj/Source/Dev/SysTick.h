#ifndef __SYSTICK_H__
#define __SYSTICK_H__



#define MAX_TIMER 8 //利用系统滴答定时器实现软件定时器的个数

extern uint32 sysTimer[MAX_TIMER];
#define DelayTimer 							sysTimer[0]  //延时定时器
#define ATaskTimer 							sysTimer[1]  //A任务运行定时器
#define BTaskTimer 							sysTimer[2]
#define CTaskTimer 							sysTimer[3]
#define Usart1RecTimer 					sysTimer[4] //串口1接收定时器，如果超时，表示一帧接收完毕
#define Usart2RecTimer 					sysTimer[5]
#define Usart3RecTimer 					sysTimer[6]
#define Usart1ControlBeepTimer  sysTimer[7] //Usart1ControlBeepTask使用




void SysTickInit(void);//系统滴答定时器初始化
void SysTickDelayMs(uint32 nms);//延时nms
uint32 GetRunTime(void);//获取系统运行时间




#endif


