#ifndef __ADC_H__
#define __ADC_H__
#include "sys.h"
#include "delay.h"

void MY_ADC_Init(void); 				//ADC通道初始化
u16  Get_Adc(u32 ch); 		        //获得某个通道值 
u16 Get_Adc_Average(u32 ch,u8 times);//得到某个通道给定次数采样的平均值
extern ADC_HandleTypeDef hadc1;
void MX_DMA_Init(void);
#endif

