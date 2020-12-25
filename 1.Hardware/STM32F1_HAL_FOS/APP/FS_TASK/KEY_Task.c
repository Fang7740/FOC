#include "KEY_Task.h"
#include "C_USART.h"
#include "C_Read.h"
#include "C_KEY.h"
#include "C_OLED.h"
TaskHandle_t KEYTask_Handler;

void KEY_task(void *pvParameters)
{
    u8 KEY;
    while(1)
    {
        KEY=C_KEY.C_KEY_Scan();
        if(KEY!=0)
        {
            printf("µ±Ç°°´¼ü=%d\r\n",KEY);
        }
	    vTaskDelay(200);
    }
}
