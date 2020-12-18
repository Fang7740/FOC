#include "A0_Task.h"
#include "C_USART.h"
#include "C_ADC.h"
#include "C_Send.h"
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
    while(1)
    {
    
      
      adcx=ADC_ConvertedValue[2];
      if(adcx>oled)
      cha=adcx-oled;
      else 
      cha=oled-adcx;
  
      speed=cha*speedx;
      if(speed>1&&speed<250)
      
      JD[0]=(adcx&0xFF00)>>8;
      JD[1]=(adcx&0x00FF);
      JD[2]=(int)speed;
      //printf("speed=%d\r\n",JD[2]);
      C_Send.C_Send_Data(ID_JD,3,JD);
      Get_Adc(1);
      oled=adcx;
      vTaskDelay(10);
      //adcx=ADC_ConvertedValue[2];
			//printf("AVT=%d\r\n",adcx);
		
    }
}   

