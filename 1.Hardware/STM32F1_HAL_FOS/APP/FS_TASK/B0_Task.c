#include "B0_Task.h"
#include "C_USART.h"
TaskHandle_t B0Task_Handler;



void B0_task(void *pvParameters)
{
   

    while(1)
    {
       
			vTaskDelay(20);
    }
}

