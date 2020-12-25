#ifndef __C_Send_H__
#define __C_Send_H__
#include "sys.h"
#include "C_USART.h"

#define ID_JD 0XAA01
#define ID_ACK 0XAA00
void Send_Data(u16 ID,u8 len,u8 *dat);
typedef struct
{
	u16 ID;
	u8  Len;
	u8  Data[10];
	u16 crc;
}m_Send_BUFF;

typedef struct
{
	void (*C_Send_Data)(u16 ID,u8 len,u8 *dat);
	m_Send_BUFF C_DATA;
}m_Send;
extern m_Send C_Send;

#endif

