#ifndef _C_USART_H__
#define _C_USART_H__
#include "sys.h"
void Uart1_Init(u32 bound);
void Uart2_Init(u32 bound);
void Uart3_Init(u32 bound);

void USART1_SendData(char str);
void USART2_SendData(char str);
void USART3_SendData(char str);
typedef struct
{
	u8 Read_BUF[100];
	int Read_cnt;
	u8 Ready;
	u8 aRxBuffer[1];
	u8 SIZE;
} __attribute__ ((__packed__))
UARTx;

typedef struct 
{
	/* data */
	void (*C_Uart1_Init)(u32 bound);
	void (*C_Uart2_Init)(u32 bound);
	void (*C_Uart3_Init)(u32 bound);
	void (*CUSART1_SendData)(char str);
	void (*CUSART2_SendData)(char str);
	void (*CUSART3_SendData)(char str);
	UARTx UART_1;
	UARTx UART_2;
	UARTx UART_3;
	
}__attribute__ ((__packed__))
m_Uart;
extern m_Uart C_USART;

#endif

