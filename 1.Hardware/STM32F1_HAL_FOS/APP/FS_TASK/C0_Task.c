#include "C0_Task.h"
#include "C_USART.h"
#include "C_Read.h"
TaskHandle_t C0Task_Handler;




void C0_task(void *pvParameters)
{

    while(1)
    {
        if(C_USART.UART_1.Read_cnt>2)
            C_Read.C_Read_SWJ();
	    vTaskDelay(20);
    }
}
