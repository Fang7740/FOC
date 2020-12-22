/**************************************************************************************
 *
 *  Recall_XS���޸İ汾 Mainģ��
 *
 *  �ļ�����		: main.c
 *  ��д���� 		: fx
 *  ��������		: 2020/12/20
 *  ��������		: 2020/12/22
 *  ����汾    : V1.0
 *  ���ܼ��		: FreeRTOS ϵͳ
 *
 **************************************************************************************
 * Description:
 *
 *	����STM32F1Ϊ��������
 *		�����޸�����Ӧ�������ݷ���
 *
 *
 * Conditions:���Խ׶Ρ�
 *            1�����FreeRTos����ϵͳ���������ڷָ�����
 *            2�����ADC�ɼ���ȡ�ű�����λ�����ݡ�
 *            3����Ӵ���Э�飬���ű�����λ�ú��ٶȷ��͸���λ����
 *            4����Ӷ�ʱ�� 2��3��4��1ͨ�����3��������PWM���Ρ�12-22������ʱ���ȷ�ϡ���
 *
 *						
 *  ��
 *
 * 
 **************************************************************************************
 */
#define Recall_XS  "�汾:Recall_XS_V0   ����ʱ��:2020-12-09"            //�汾˵��������Ҫ
 //-----------------------------------------ͷ�ļ�-------------------------------------//

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
  C_PWM.C_TIM3_Init(10000,2);        	//TIM1 PWM��ʼ��, Fpwm=72M/256=281.25Khz
  C_PWM.C_TIM2_Init(10000,2);        	//TIM1 PWM��ʼ��, Fpwm=72M/256=281.25Khz
  C_PWM.C_TIM4_Init(10000,2);        	//TIM1 PWM��ʼ��, Fpwm=72M/256=281.25Khz
	MX_DMA_Init_();
	MY_ADC_Init();                  	//��ʼ��ADC1ͨ��1
  printf("\r\n------------------------------------\r\n%s\r\n------------------------------------\r\n",Recall_XS);//��ӡ�汾��Ϣ ��������		
	clk=HAL_RCC_GetHCLKFreq();     		
	printf("clk:%ld\r\n",clk);	
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_ConvertedValue,3);  

  xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
  vTaskStartScheduler();          //�����������
	
}
void start_task(void *pvParameters)
{
   taskENTER_CRITICAL();           //�����ٽ���
    //A0 ������������RGB
    xTaskCreate((TaskFunction_t )A0_task,     	
                (const char*    )"A0_task",   	
                (uint16_t       )A0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )A0_TASK_PRIO,	
                (TaskHandle_t*  )&A0Task_Handler);   
    //B0���� δ��
    xTaskCreate((TaskFunction_t )B0_task,     
                (const char*    )"B0_task",   
                (uint16_t       )B0_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )B0_TASK_PRIO,
                (TaskHandle_t*  )&B0Task_Handler);         
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}



