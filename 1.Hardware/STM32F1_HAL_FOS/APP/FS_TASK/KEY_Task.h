#ifndef __KEY_Task_H__
#define __KEY_Task_H__
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
//�������ȼ�
#define KEY_TASK_PRIO		3
//�����ջ��С	
#define KEY_STK_SIZE 		50  
//������
extern TaskHandle_t KEYTask_Handler;
//������
void KEY_task(void *pvParameters);

#endif

