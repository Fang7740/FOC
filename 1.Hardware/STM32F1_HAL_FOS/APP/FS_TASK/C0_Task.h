#ifndef __C0_Task_H__
#define __C0_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//�������ȼ�
#define C0_TASK_PRIO		3
//�����ջ��С	
#define C0_STK_SIZE 		50  
//������
extern TaskHandle_t C0Task_Handler;
//������
void C0_task(void *pvParameters);

#endif

