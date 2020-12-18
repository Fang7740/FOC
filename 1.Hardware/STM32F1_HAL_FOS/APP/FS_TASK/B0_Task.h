#ifndef __B0_Task_H__
#define __B0_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//任务优先级
#define B0_TASK_PRIO		3
//任务堆栈大小	
#define B0_STK_SIZE 		50  
//任务句柄
extern TaskHandle_t B0Task_Handler;
//任务函数
void B0_task(void *pvParameters);

#endif

