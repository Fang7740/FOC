#include "C_KEY.h"

m_key C_KEY=
{
    KEY_Init,
    KEY_Scan,
};
void KEY_Init()
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           //开启GPIOA时钟
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;            //PA0
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //下拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

u8 KEY_Scan()
{
     if(KEY1==0)
    {
        delay_ms(100);
        if(KEY1==0)
        return 1;
    }

     if(KEY2==0)
    {
        delay_ms(100);
        return 2;
    }
     if(KEY3==0)
    {
        delay_ms(100);
        return 3;
    }
     if(KEY4==0)
    {
        delay_ms(100);
        return 4;
    }  
    return 0;
}




