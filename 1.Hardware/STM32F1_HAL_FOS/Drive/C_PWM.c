#include "C_PWM.h"
TIM_HandleTypeDef 	PWM_Handler;      		//定时器句柄 
TIM_OC_InitTypeDef 	TIM3_CH1Handler;		//定时器1通道1句柄
TIM_HandleTypeDef 	PWM2_Handler;      		//定时器句柄 
TIM_OC_InitTypeDef 	TIM2_CH1Handler;		//定时器1通道1句柄
TIM_HandleTypeDef 	PWM4_Handler;      		//定时器句柄 
TIM_OC_InitTypeDef 	TIM4_CH1Handler;		//定时器1通道1句柄

m_pwm C_PWM=
{
    TIM3_Init,
    TIM2_Init,
    TIM4_Init,
    PWM_120_Out,
};

void TIM3_Init(u16 arr,u16 psc)
{

    PWM_Handler.Instance=TIM3;          	//定时器1
    PWM_Handler.Init.Prescaler=psc;       	//定时器分频
    PWM_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    PWM_Handler.Init.Period=arr;          	//自动重装载值
    PWM_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&PWM_Handler);       	//初始化PWM
    TIM3_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM2
    TIM3_CH1Handler.Pulse=arr;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM3_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //输出比较极性为高
    HAL_TIM_PWM_ConfigChannel(&PWM_Handler,&TIM3_CH1Handler,TIM_CHANNEL_1);//配置TIM1通道1
    HAL_TIM_PWM_Start(&PWM_Handler,TIM_CHANNEL_1);//配置TIM1通道1
    /*
    HAL_TIM_PWM_ConfigChannel(&PWM_Handler,&TIM3_CH1Handler,TIM_CHANNEL_2);//配置TIM1通道1
    HAL_TIM_PWM_Start(&PWM_Handler,TIM_CHANNEL_2);//配置TIM1通道1
    HAL_TIM_PWM_ConfigChannel(&PWM_Handler,&TIM3_CH1Handler,TIM_CHANNEL_3);//配置TIM1通道1
    HAL_TIM_PWM_Start(&PWM_Handler,TIM_CHANNEL_3);//配置TIM1通道1
    HAL_TIM_PWM_ConfigChannel(&PWM_Handler,&TIM3_CH1Handler,TIM_CHANNEL_4);//配置TIM1通道1
    HAL_TIM_PWM_Start(&PWM_Handler,TIM_CHANNEL_4);//配置TIM1通道1
    */
    
}

void TIM2_Init(u16 arr,u16 psc)
{

    PWM2_Handler.Instance=TIM2;          	//定时器1
    PWM2_Handler.Init.Prescaler=psc;       	//定时器分频
    PWM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    PWM2_Handler.Init.Period=arr;          	//自动重装载值
    PWM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&PWM2_Handler);       	//初始化PWM
    TIM2_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM2
    TIM2_CH1Handler.Pulse=arr;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM2_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //输出比较极性为高
    HAL_TIM_PWM_ConfigChannel(&PWM2_Handler,&TIM2_CH1Handler,TIM_CHANNEL_1);//配置TIM1通道1
    HAL_TIM_PWM_Start(&PWM2_Handler,TIM_CHANNEL_1);//配置TIM1通道1

}


void TIM4_Init(u16 arr,u16 psc)
{

    PWM4_Handler.Instance=TIM4;          	//定时器1
    PWM4_Handler.Init.Prescaler=psc;       	//定时器分频
    PWM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    PWM4_Handler.Init.Period=arr;          	//自动重装载值
    PWM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&PWM4_Handler);       	//初始化PWM
    TIM4_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM2
    TIM4_CH1Handler.Pulse=arr;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM4_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //输出比较极性为高
    HAL_TIM_PWM_ConfigChannel(&PWM4_Handler,&TIM4_CH1Handler,TIM_CHANNEL_1);//配置TIM1通道1
    HAL_TIM_PWM_Start(&PWM4_Handler,TIM_CHANNEL_1);//配置TIM1通道1
}


//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;

     if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();			//使能定时器1
		//__HAL_AFIO_REMAP_TIM1_PARTIAL();		//TIM1通道引脚部分重映射使能
		__HAL_RCC_GPIOA_CLK_ENABLE();			//开启GPIOA时钟
    
		GPIO_Initure.Pin=GPIO_PIN_0;           	//PA8
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); 	
	}
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();			//使能定时器1
		//__HAL_AFIO_REMAP_TIM1_PARTIAL();		//TIM1通道引脚部分重映射使能
		__HAL_RCC_GPIOA_CLK_ENABLE();			//开启GPIOA时钟
        __HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOA时钟
		GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;           	//PA8
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); 	
        GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1;           	//PA8
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOB,&GPIO_Initure); 	
	}
     if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();			//使能定时器1
		//__HAL_AFIO_REMAP_TIM1_PARTIAL();		//TIM1通道引脚部分重映射使能
		__HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOA时钟
		GPIO_Initure.Pin=GPIO_PIN_6;           	//PA8
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOB,&GPIO_Initure); 	
	}
}


int D_time=50;
void PWM_120_Out(float PWM)
{
    int PWM_OUT;
    PWM_OUT=(int)(PWM*(2000)/2);

    TIM2->CNT=0; 
    TIM4->CNT=PWM_OUT/3*2;
    TIM3->CNT=PWM_OUT/3*4;
    TIM2->CCR1=PWM_OUT;
    TIM3->CCR1=PWM_OUT; 
    TIM4->CCR1=PWM_OUT; 
}
