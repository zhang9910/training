#ifndef __TASK_H__
#define __TASK_H__

typedef struct 
{
	//��̬�����߳�ʱʹ�õ��̲߳����ṹ��
	char *name;
  void (*entry)(void *parameter);
  void       *parameter;
  rt_uint32_t stack_size;
	rt_uint8_t  priority;
	rt_uint32_t tick;
}TaskStruct;

void TaskInit(void);


#endif