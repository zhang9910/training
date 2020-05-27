#ifndef __TASK_H__
#define __TASK_H__

#include "rtthread.h"

typedef struct 
{
	//动态创建线程时使用的线程参数结构体
	char *name;
    void (*entry)(void *parameter);
    void       *parameter;
    rt_uint32_t stack_size;
	rt_uint8_t  priority;
	rt_uint32_t tick;
}TaskStruct;

void TaskInit(void);


#endif
