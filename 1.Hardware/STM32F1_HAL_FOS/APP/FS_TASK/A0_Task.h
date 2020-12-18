#ifndef __A0_Task_H__
#define __A0_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//任务优先级
#define A0_TASK_PRIO		2
//任务堆栈大小	
#define A0_STK_SIZE 		50  
//任务句柄
extern TaskHandle_t A0Task_Handler;
//任务函数
void A0_task(void *pvParameters);





#endif

