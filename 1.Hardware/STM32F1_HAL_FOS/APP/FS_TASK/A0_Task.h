#ifndef __A0_Task_H__
#define __A0_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//�������ȼ�
#define A0_TASK_PRIO		2
//�����ջ��С	
#define A0_STK_SIZE 		50  
//������
extern TaskHandle_t A0Task_Handler;
//������
void A0_task(void *pvParameters);





#endif

