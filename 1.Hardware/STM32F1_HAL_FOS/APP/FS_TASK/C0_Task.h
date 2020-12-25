#ifndef __C0_Task_H__
#define __C0_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//任务优先级
#define C0_TASK_PRIO		3
//任务堆栈大小	
#define C0_STK_SIZE 		50  
//任务句柄
extern TaskHandle_t C0Task_Handler;
//任务函数
void C0_task(void *pvParameters);

#endif

