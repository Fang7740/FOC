#ifndef __ADC_H__
#define __ADC_H__
#include "sys.h"
#include "delay.h"

void MY_ADC_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u32 ch); 		        //���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u32 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ
extern ADC_HandleTypeDef hadc1;
void MX_DMA_Init(void);
#endif

