#ifndef __KEY_Task_H__
#define __KEY_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//任务优先级
#define KEY_TASK_PRIO		3
//任务堆栈大小	
#define KEY_STK_SIZE 		50  
//任务句柄
extern TaskHandle_t KEYTask_Handler;
//任务函数
void KEY_task(void *pvParameters);

#endif

