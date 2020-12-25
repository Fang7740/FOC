/**************************************************************************************
 *
 *  Recall_XS年修改版本 Main模块
 *
 *  文件名称		: main.c
 *  编写作者 		: fx
 *  创建日期		: 2020/12/20
 *  更新日期		: 2020/12/25
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
 *            5、PWM上电调试有问题,待解决。
 *            6、添加多功能开关程序,添加OLED显示屏程序。2020-12-25
 *
 *						
 *  无
 *
 * 
 **************************************************************************************
 */
#define FOC  "版本:FOC_V0   更新时间:2020-12-09"            //版本说明，必须要
 //-----------------------------------------头文件-------------------------------------//

#include "main.h"
#include "C_USART.h"
#include "C_Time.h"
#include "FreeRTOS.h"
#include "task.h"
#include "A0_Task.h"
#include "B0_Task.h"
#include "C0_Task.h"
#include "KEY_Task.h"
#include "C_KEY.h"
#include "C_ADC.h"
#include "C_PWM.h"
#include "C_OLED.h"
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
  C_KEY.C_KEY_Init();
	C_USART.C_Uart1_Init(115200);		
	C_USART.C_Uart3_Init(115200);		
  C_PWM.C_TIM3_Init(2000-1,2-1);        	//TIM3 PWM初始化, Fpwm=72M/2/2000=18Khz  
  C_PWM.C_TIM2_Init(2000-1,2-1);      	  //TIM2 PWM初始化, Fpwm=72M/2/2000=18Khz
  C_PWM.C_TIM4_Init(2000-1,2-1);        	//TIM4 PWM初始化, Fpwm=72M/2/2000=18Khz
	C_OLED.C_OLED_Init();
	C_OLED.C_OLED_Clear();											 //清空OLED屏幕
	C_OLED.C_OLED_ShowString(20, 4, "FOC_V0", 24, 1);				 //开机显示
  delay_ms(1000);
	MX_DMA_Init_();
	MY_ADC_Init();                  	//初始化ADC1通道1
  printf("\r\n------------------------------------\r\n%s\r\n------------------------------------\r\n",FOC);//打印版本信息 不可屏蔽		
	clk=HAL_RCC_GetHCLKFreq();
  C_OLED.C_OLED_Clear();		
  C_OLED.C_OLED_ShowString(0, 4, "CLK", 12, 1);				 //开机显示     		
  C_OLED.C_OLED_ShowNumber(30,4,clk,8,12,1);   //OLED显示
  printf("clk:%ld\r\n",clk);	
  delay_ms(1000);
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
    //A0 任务读取磁编码器位置
    xTaskCreate((TaskFunction_t )A0_task,     	
                (const char*    )"A0_task",   	
                (uint16_t       )A0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )A0_TASK_PRIO,	
                (TaskHandle_t*  )&A0Task_Handler);   
    //B0任务 PWM
    xTaskCreate((TaskFunction_t )B0_task,     
                (const char*    )"B0_task",   
                (uint16_t       )B0_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )B0_TASK_PRIO,
                (TaskHandle_t*  )&B0Task_Handler);     

		//C0任务 上位机读取
    xTaskCreate((TaskFunction_t )C0_task,     
                (const char*    )"C0_task",   
                (uint16_t       )C0_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )C0_TASK_PRIO,
                (TaskHandle_t*  )&C0Task_Handler);  

    //KEY任务 按键
    xTaskCreate((TaskFunction_t )KEY_task,     
                (const char*    )"KEY_task",   
                (uint16_t       )KEY_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )KEY_TASK_PRIO,
                (TaskHandle_t*  )&KEYTask_Handler);  
								
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}



