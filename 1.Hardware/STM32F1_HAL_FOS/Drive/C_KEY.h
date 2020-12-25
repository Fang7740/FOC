#ifndef __C_KEY_H__
#define __C_KEY_H__
#include "sys.h"
#include "delay.h"
void KEY_Init(void);
u8 KEY_Scan(void);
#define KEY1        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)  
#define KEY2        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7) 
#define KEY3        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)  
#define KEY4        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)  

typedef struct 
{
    /* data */
    void (*C_KEY_Init)(void);
    u8  (*C_KEY_Scan)(void);
}m_key;

extern m_key C_KEY;


#endif

