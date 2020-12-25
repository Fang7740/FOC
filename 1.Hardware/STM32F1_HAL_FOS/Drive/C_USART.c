#include "C_USART.h"
#include "stdio.h"
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define RXBUFFERSIZE   1 //�����С

UART_HandleTypeDef UART1_Handler;
UART_HandleTypeDef UART2_Handler;
UART_HandleTypeDef UART3_Handler;

m_Uart C_USART=
{
	Uart1_Init,
	Uart2_Init,
	Uart3_Init,
	USART1_SendData,
	USART2_SendData,
	USART3_SendData,
};


/**********************************************/
/*                                            */
/*              ���� IO��ʼ��                  */
/*                                            */
/**********************************************/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_Initure;
    if(huart->Instance==USART1)//����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		
		#if EN_USART1_RX
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
		#endif	
	}
	else if(huart->Instance == USART2)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART2_CLK_ENABLE();			//ʹ��USART1ʱ��
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA10
		
		#if EN_USART2_RX
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
		#endif	
	}
		
	else if(huart->Instance == USART3)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART3_CLK_ENABLE();			//ʹ��USART1ʱ��
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_10;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PA9

		GPIO_Initure.Pin=GPIO_PIN_11;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��	
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PA10
		
		#if EN_USART3_RX
		HAL_NVIC_EnableIRQ(USART3_IRQn);				//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART3_IRQn,3,3);			//��ռ���ȼ�3�������ȼ�3
		#endif	
	}
	
}



/**********************************************/
/*                                            */
/*              ����1��ʼ��                   */
/*                                            */
/**********************************************/

void Uart1_Init(u32 bound)
{
	
	UART1_Handler.Instance=USART1;                      //USART1
	UART1_Handler.Init.BaudRate=bound;                  //����������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()��ʹ��UART1
	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)C_USART.UART_1.aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
	C_USART.UART_1.Read_cnt=0;
}

/**********************************************/
/*                                            */
/*              ����2��ʼ��                   */
/*                                            */
/**********************************************/

void Uart2_Init(u32 bound)
{
	UART2_Handler.Instance=USART2;                      //USART1
	UART2_Handler.Init.BaudRate=bound;                  //����������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()��ʹ��UART1
	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)C_USART.UART_2.aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
}

/**********************************************/
/*                                            */
/*              ����3��ʼ��                   */
/*                                            */
/**********************************************/

void Uart3_Init(u32 bound)
{
	
	UART3_Handler.Instance=USART3;                      //USART1
	UART3_Handler.Init.BaudRate=bound;                  //����������
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART3_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART3_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART3_Handler.Init.Mode=UART_MODE_TX_RX;		    //�շ�ģʽ
	HAL_UART_Init(&UART3_Handler);					    //HAL_UART_Init()��ʹ��UART1
	HAL_UART_Receive_IT(&UART3_Handler, (u8 *)C_USART.UART_3.aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
}

/**********************************************/
/*                                            */
/*              ����1�ж�		                  */
/*           ��ȡWLT8016�Ļش�����            */
/**********************************************/

void USART1_IRQHandler(void) 	  
{
	u32 timeout=0;
  	u32 maxDelay=0x1FFFF;
	HAL_UART_IRQHandler(&UART1_Handler);	//����HAL���жϴ����ú���
	timeout=0;
   	while (HAL_UART_GetState(&UART1_Handler)!=HAL_UART_STATE_READY)//�ȴ�����
	{
    timeout++;////��ʱ����
    if(timeout>maxDelay) break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler,(u8 *)C_USART.UART_1.aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
     timeout++; //��ʱ����
     if(timeout>maxDelay) break;	
	}

}

/**********************************************/
/*                                            */
/*              ����1�ж�		                  */
/*           ��ȡWLT8016�Ļش�����            */
/**********************************************/

void USART2_IRQHandler(void) 	  
{
	u32 timeout=0;
  	u32 maxDelay=0x1FFFF;
	HAL_UART_IRQHandler(&UART2_Handler);	//����HAL���жϴ����ú���
	timeout=0;
   	while (HAL_UART_GetState(&UART2_Handler)!=HAL_UART_STATE_READY)//�ȴ�����
	{
    timeout++;////��ʱ����
    if(timeout>maxDelay) break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler,(u8 *)C_USART.UART_2.aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
     timeout++; //��ʱ����
     if(timeout>maxDelay) break;	
	}

}
/**********************************************/
/*                                            */
/*              ����3�ж�		                  */
/*           ��ȡWLT8016�Ļش�����            */
/**********************************************/
void USART3_IRQHandler(void) 	  
{
	u32 timeout=0;
  u32 maxDelay=0x1FFFF;
	
	HAL_UART_IRQHandler(&UART3_Handler);	//����HAL���жϴ����ú���
	timeout=0;
    while (HAL_UART_GetState(&UART3_Handler)!=HAL_UART_STATE_READY)//�ȴ�����
	{
     timeout++;////��ʱ����
     if(timeout>maxDelay) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART3_Handler,(u8 *)C_USART.UART_3.aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//һ�δ������֮�����¿����жϲ�����RxXferCountΪ1
	{
     timeout++; //��ʱ����
     if(timeout>maxDelay) break;	
	}
}

/**********************************************/
/*                                            */
/*              HAL_���жϴ����ж�            */
/*                                            */
/**********************************************/
u8 buff[3];
u8 cnt=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	u8 Res;
	if(huart->Instance==USART1)//����Ǵ���1
	{
		Res=C_USART.UART_1.aRxBuffer[0]; 
		C_USART.UART_1.Read_BUF[C_USART.UART_1.Read_cnt]=Res;
		C_USART.UART_1.Read_cnt++;
		USART3->DR=Res;
	}
	
	else if(huart->Instance==USART2)//����Ǵ���3
	{
		
		Res=C_USART.UART_2.aRxBuffer[0]; 
		USART1->DR=Res;
		//UART5->TDR=Res;
	}
	
	else if(huart->Instance==USART3)//����Ǵ���3
	{
		
		Res=C_USART.UART_3.aRxBuffer[0]; 
		USART1->DR=Res;
		//UART5->TDR=Res;
	}
}


void USART1_SendData(char str)
{
	USART1->DR=str;
	while((USART1->SR&0X40)==0);//ѭ������,ֱ��������� 
		
}

void USART2_SendData(char str)
{
	USART2->DR=str;
	while((USART2->SR&0X40)==0);//ѭ������,ֱ��������� 
} 

void USART3_SendData(char str)
{
		
   USART3->DR=str;
	while((USART3->SR&0X40)==0);//ѭ������,ֱ��������� 
}
/**********************************************/
/*                                            */
/*              printf ����                   */
/*                                            */
/**********************************************/
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{ 	
		while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
		USART1->DR=(u8)ch;   
		return ch;
}


