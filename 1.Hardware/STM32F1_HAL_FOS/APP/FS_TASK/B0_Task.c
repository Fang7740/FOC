#include "B0_Task.h"
#include "C_USART.h"
#include "C_PWM.h"
TaskHandle_t B0Task_Handler;



void B0_task(void *pvParameters)
{
    float pwm=0;
    
    while(1)
    {
       
        C_PWM.C_PWM_120_Out(pwm);
	    vTaskDelay(200);
        pwm=pwm+0.01;
        if(pwm>=1)
        pwm=0;
    }
}

