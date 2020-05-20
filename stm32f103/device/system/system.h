/**
 ********************************************************
 * @file      : system.h
 * @brief     : Header for system.c file.
 ********************************************************
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__



void SysInit(void);//系统初始化

void  TaskInit(void);//任务初始化，包括任务运行周期设置等
void  TaskRun(void);//任务运行，可在main.c文件 main函数中调用


#endif


