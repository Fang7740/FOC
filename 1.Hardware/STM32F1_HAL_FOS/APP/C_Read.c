#include "C_Read.h"
#include "C_Send.h"
m_read C_Read=
{
    Read_SWJ,
    1,
};

void Read_SWJ()
{
    vTaskDelay(20);
    
    if(C_USART.UART_1.Read_BUF[0]==0xAA)
    {
        
        switch (C_USART.UART_1.Read_BUF[1])
        {
            case 0x02:C_Read.C_DATA.PWM=C_USART.UART_1.Read_BUF[3]/100.0;
                C_Send.C_Send_Data(ID_ACK,0,0);
                //USART1->DR=C_USART.UART_1.Read_BUF[3];
                break;
            default:
                break;
        }
    }
   C_USART.UART_1.Read_cnt=0;
}
