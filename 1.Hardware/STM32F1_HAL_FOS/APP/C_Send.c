#include "C_Send.h"
#include "string.h"
u8 Send_buff[20];
m_Send C_Send=
{
	Send_Data,
    Read_Data,
};

u16 DXer(u16 data)
{
    u8 half_dat[2];
    u16 re_dat;
    half_dat[0]=(data&0xFF00)>>8;
    half_dat[1]=(data&0x00FF);
    re_dat=half_dat[1]<<8|half_dat[0];
    return re_dat;
}


void Send_Data(u16 ID,u8 len,u8 *dat)
{
    int i;
    C_Send.C_DATA.ID=DXer(ID);
    C_Send.C_DATA.Len=len;
    memcpy( C_Send.C_DATA.Data,dat,len);
    //printf("\r\n");
    memcpy(Send_buff,(unsigned  char *)&C_Send.C_DATA,4+len);
	for ( i = 0; i < 4+len; i++)
    {
        //printf("%02X",Send_buff[i]);
        C_USART.CUSART1_SendData(Send_buff[i]);
    }  
  
}

void Read_Data()
{

}

