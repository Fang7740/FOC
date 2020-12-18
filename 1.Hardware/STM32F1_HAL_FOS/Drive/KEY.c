#include "KEY.h"
#include "Timer.h"


void KEY_INIT()
{
		GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //����GPIOAʱ��
	
		__HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIODʱ��
		__HAL_RCC_AFIO_CLK_ENABLE();
		__HAL_AFIO_REMAP_SWJ_NOJTAG(); 
		GPIO_Initure.Pin=GPIO_PIN_15; 				//PB8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);	//PA8��1��Ĭ�ϳ�ʼ�������
	
    GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

u8 KEY_Scan()
{
    
}
