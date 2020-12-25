#include "C_USART.h"
#include "stdio.h"
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
#define RXBUFFERSIZE   1 //缓存大小

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
/*              串口 IO初始化                  */
/*                                            */
/**********************************************/
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_Initure;
    if(huart->Instance==USART1)//如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_9;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_10;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
		#if EN_USART1_RX
		HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);			//抢占优先级3，子优先级3
		#endif	
	}
	else if(huart->Instance == USART2)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART2_CLK_ENABLE();			//使能USART1时钟
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_2;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_3;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
		
		#if EN_USART2_RX
		HAL_NVIC_EnableIRQ(USART2_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//抢占优先级3，子优先级3
		#endif	
	}
		
	else if(huart->Instance == USART3)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART3_CLK_ENABLE();			//使能USART1时钟
		__HAL_RCC_AFIO_CLK_ENABLE();
	
		GPIO_Initure.Pin=GPIO_PIN_10;			//PA9
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PA9

		GPIO_Initure.Pin=GPIO_PIN_11;			//PA10
		GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PA10
		
		#if EN_USART3_RX
		HAL_NVIC_EnableIRQ(USART3_IRQn);				//使能USART1中断通道
		HAL_NVIC_SetPriority(USART3_IRQn,3,3);			//抢占优先级3，子优先级3
		#endif	
	}
	
}



/**********************************************/
/*                                            */
/*              串口1初始化                   */
/*                                            */
/**********************************************/

void Uart1_Init(u32 bound)
{
	
	UART1_Handler.Instance=USART1;                      //USART1
	UART1_Handler.Init.BaudRate=bound;                  //波特率设置
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART1_Handler);					    //HAL_UART_Init()会使能UART1
	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)C_USART.UART_1.aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
	C_USART.UART_1.Read_cnt=0;
}

/**********************************************/
/*                                            */
/*              串口2初始化                   */
/*                                            */
/**********************************************/

void Uart2_Init(u32 bound)
{
	UART2_Handler.Instance=USART2;                      //USART1
	UART2_Handler.Init.BaudRate=bound;                  //波特率设置
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART2_Handler);					    //HAL_UART_Init()会使能UART1
	HAL_UART_Receive_IT(&UART2_Handler, (u8 *)C_USART.UART_2.aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}

/**********************************************/
/*                                            */
/*              串口3初始化                   */
/*                                            */
/**********************************************/

void Uart3_Init(u32 bound)
{
	
	UART3_Handler.Instance=USART3;                      //USART1
	UART3_Handler.Init.BaudRate=bound;                  //波特率设置
	UART3_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //字长为8位数据格式
	UART3_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART3_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART3_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //无硬件流控
	UART3_Handler.Init.Mode=UART_MODE_TX_RX;		    //收发模式
	HAL_UART_Init(&UART3_Handler);					    //HAL_UART_Init()会使能UART1
	HAL_UART_Receive_IT(&UART3_Handler, (u8 *)C_USART.UART_3.aRxBuffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}

/**********************************************/
/*                                            */
/*              串口1中断		                  */
/*           读取WLT8016的回传数据            */
/**********************************************/

void USART1_IRQHandler(void) 	  
{
	u32 timeout=0;
  	u32 maxDelay=0x1FFFF;
	HAL_UART_IRQHandler(&UART1_Handler);	//调用HAL库中断处理公用函数
	timeout=0;
   	while (HAL_UART_GetState(&UART1_Handler)!=HAL_UART_STATE_READY)//等待就绪
	{
    timeout++;////超时处理
    if(timeout>maxDelay) break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler,(u8 *)C_USART.UART_1.aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
     timeout++; //超时处理
     if(timeout>maxDelay) break;	
	}

}

/**********************************************/
/*                                            */
/*              串口1中断		                  */
/*           读取WLT8016的回传数据            */
/**********************************************/

void USART2_IRQHandler(void) 	  
{
	u32 timeout=0;
  	u32 maxDelay=0x1FFFF;
	HAL_UART_IRQHandler(&UART2_Handler);	//调用HAL库中断处理公用函数
	timeout=0;
   	while (HAL_UART_GetState(&UART2_Handler)!=HAL_UART_STATE_READY)//等待就绪
	{
    timeout++;////超时处理
    if(timeout>maxDelay) break;		
	}
	timeout=0;
	while(HAL_UART_Receive_IT(&UART2_Handler,(u8 *)C_USART.UART_2.aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
     timeout++; //超时处理
     if(timeout>maxDelay) break;	
	}

}
/**********************************************/
/*                                            */
/*              串口3中断		                  */
/*           读取WLT8016的回传数据            */
/**********************************************/
void USART3_IRQHandler(void) 	  
{
	u32 timeout=0;
  u32 maxDelay=0x1FFFF;
	
	HAL_UART_IRQHandler(&UART3_Handler);	//调用HAL库中断处理公用函数
	timeout=0;
    while (HAL_UART_GetState(&UART3_Handler)!=HAL_UART_STATE_READY)//等待就绪
	{
     timeout++;////超时处理
     if(timeout>maxDelay) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART3_Handler,(u8 *)C_USART.UART_3.aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
     timeout++; //超时处理
     if(timeout>maxDelay) break;	
	}
}

/**********************************************/
/*                                            */
/*              HAL_库中断处理判断            */
/*                                            */
/**********************************************/
u8 buff[3];
u8 cnt=0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	u8 Res;
	if(huart->Instance==USART1)//如果是串口1
	{
		Res=C_USART.UART_1.aRxBuffer[0]; 
		C_USART.UART_1.Read_BUF[C_USART.UART_1.Read_cnt]=Res;
		C_USART.UART_1.Read_cnt++;
		USART3->DR=Res;
	}
	
	else if(huart->Instance==USART2)//如果是串口3
	{
		
		Res=C_USART.UART_2.aRxBuffer[0]; 
		USART1->DR=Res;
		//UART5->TDR=Res;
	}
	
	else if(huart->Instance==USART3)//如果是串口3
	{
		
		Res=C_USART.UART_3.aRxBuffer[0]; 
		USART1->DR=Res;
		//UART5->TDR=Res;
	}
}


void USART1_SendData(char str)
{
	USART1->DR=str;
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕 
		
}

void USART2_SendData(char str)
{
	USART2->DR=str;
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕 
} 

void USART3_SendData(char str)
{
		
   USART3->DR=str;
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕 
}
/**********************************************/
/*                                            */
/*              printf 函数                   */
/*                                            */
/**********************************************/
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{ 	
		while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
		USART1->DR=(u8)ch;   
		return ch;
}


