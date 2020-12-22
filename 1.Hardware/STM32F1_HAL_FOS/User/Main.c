/**************************************************************************************
 *
 *  Recall_XS年修改版本 Main模块
 *
 *  文件名称		: main.c
 *  编写作者 		: fx
 *  创建日期		: 2020/12/20
 *  更新日期		: 2020/12/22
 *  软件版本    : V1.0
 *  功能简介		: FreeRTOS 系统
 *
 **************************************************************************************
 * Description:
 *
 *	采用STM32F1为控制器。
 *		构架修改以适应快速数据发送
 *
 *
 * Conditions:调试阶段。
 *            1、添加FreeRTos操作系统，后期用于分割任务。
 *            2、添加ADC采集读取磁编码器位置数据。
 *            3、添加串口协议，将磁编码器位置和速度发送给上位机。
 *            4、添加定时器 2、3、4的1通道输出3个互补的PWM波形。12-22（死区时间待确认。）
 *
 *						
 *  无
 *
 * 
 **************************************************************************************
 */
#define Recall_XS  "版本:Recall_XS_V0   更新时间:2020-12-09"            //版本说明，必须要
 //-----------------------------------------头文件-------------------------------------//

#include "main.h"
#include "C_USART.h"
#include "C_Time.h"
#include "FreeRTOS.h"
#include "task.h"
#include "A0_Task.h"
#include "B0_Task.h"
#include "C_ADC.h"
#include "C_PWM.h"

#define START_TASK_PRIO		1
#define START_STK_SIZE 		128  
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);
uint16_t ADC_ConvertedValue[3];



int main(void)
{
	long int clk;
	HAL_Init();                    	 
  Stm32_Clock_Init(RCC_PLL_MUL9);   	
	delay_init(72);      
	C_USART.C_Uart1_Init(115200);		
	C_USART.C_Uart2_Init(115200);		
  C_PWM.C_TIM3_Init(10000,2);        	//TIM1 PWM初始化, Fpwm=72M/256=281.25Khz
  C_PWM.C_TIM2_Init(10000,2);        	//TIM1 PWM初始化, Fpwm=72M/256=281.25Khz
  C_PWM.C_TIM4_Init(10000,2);        	//TIM1 PWM初始化, Fpwm=72M/256=281.25Khz
	MX_DMA_Init_();
	MY_ADC_Init();                  	//初始化ADC1通道1
  printf("\r\n------------------------------------\r\n%s\r\n------------------------------------\r\n",Recall_XS);//打印版本信息 不可屏蔽		
	clk=HAL_RCC_GetHCLKFreq();     		
	printf("clk:%ld\r\n",clk);	
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_ConvertedValue,3);  

  xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
  vTaskStartScheduler();          //开启任务调度
	
}
void start_task(void *pvParameters)
{
   taskENTER_CRITICAL();           //进入临界区
    //A0 任务用于驱动RGB
    xTaskCreate((TaskFunction_t )A0_task,     	
                (const char*    )"A0_task",   	
                (uint16_t       )A0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )A0_TASK_PRIO,	
                (TaskHandle_t*  )&A0Task_Handler);   
    //B0任务 未用
    xTaskCreate((TaskFunction_t )B0_task,     
                (const char*    )"B0_task",   
                (uint16_t       )B0_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )B0_TASK_PRIO,
                (TaskHandle_t*  )&B0Task_Handler);         
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}



