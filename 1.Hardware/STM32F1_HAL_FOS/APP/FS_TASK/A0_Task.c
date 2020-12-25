#include "A0_Task.h"
#include "C_USART.h"
#include "C_ADC.h"
#include "C_Send.h"
#include "C_OLED.h"
TaskHandle_t A0Task_Handler;
extern  uint16_t ADC_ConvertedValue[3];
void A0_task(void *pvParameters)
{
		u16 adcx;
    u16 oled;
    float speed;
    int cha;
    u8 JD[3];
    float speedx=360/4020.0;
    C_OLED.C_OLED_Clear();											 //清空OLED屏幕
    C_OLED.C_OLED_ShowString(0, 4, "Angle", 24, 1);				 //开机显示
    while(1)
    {
      adcx=ADC_ConvertedValue[2];
      C_OLED.C_OLED_ShowNumber(40,4,adcx,4,24,0);   //OLED显示
      if(adcx>oled)
      cha=adcx-oled;
      else 
      cha=oled-adcx;
      speed=cha*speedx;
      if(speed>1&&speed<250)
      JD[0]=(adcx&0xFF00)>>8;
      JD[1]=(adcx&0x00FF);
      JD[2]=(int)speed;
      C_Send.C_Send_Data(ID_JD,3,JD);
      Get_Adc(1);
      oled=adcx;
      vTaskDelay(10);
      //printf("speed=%d\r\n",JD[2]);
      //adcx=ADC_ConvertedValue[2];
			//printf("AVT=%d\r\n",adcx);
    }
}   

