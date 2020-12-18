#ifndef _KEY_H__
#define _KEY_H__
#include "sys.h"
#include "delay.h"
#define KEY1        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)  //KEY0����PC5
#define KEY2        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10) //KEY1����PA15
#define KEY3        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)  //WKUP����PA0
#define KEY4        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)  //WKUP����PA0

#define LED_ON      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);	//PA8��1��Ĭ�ϳ�ʼ�������
#define LED_OFF      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);	//PA8��1��Ĭ�ϳ�ʼ�������

u8 KEY_Scan(void);
void KEY_INIT(void);

#endif

