#include "C_Time.h"
#include "Timer.h"
void Error_Handler(void);

TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
extern DMA_HandleTypeDef hdma_tim2_up;
m_time C_Time=
{
	Time3_Init,
};

void Time3_Init(u32 Time)
{
	TIM3_Handler.Instance=TIM3;                          //通用定时器3
    TIM3_Handler.Init.Prescaler=7200-1;                     //分频系数
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM3_Handler.Init.Period=Time*1000-1;                        //自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE  
}



//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

//回调函数，定时器中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		C_Timer.C_Timer_Run();

}


