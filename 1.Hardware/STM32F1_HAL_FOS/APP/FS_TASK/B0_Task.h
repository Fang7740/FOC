#ifndef __B0_Task_H__
#define __B0_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//�������ȼ�
#define B0_TASK_PRIO		3
//�����ջ��С	
#define B0_STK_SIZE 		50  
//������
extern TaskHandle_t B0Task_Handler;
//������
void B0_task(void *pvParameters);

#endif

