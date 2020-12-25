#include "B0_Task.h"
#include "C_USART.h"
#include "C_PWM.h"
#include "C_Read.h"
TaskHandle_t B0Task_Handler;



void B0_task(void *pvParameters)
{

    while(1)
    {
       
        C_PWM.C_PWM_120_Out(C_Read.C_DATA.PWM);
	    vTaskDelay(200);
    }
}

