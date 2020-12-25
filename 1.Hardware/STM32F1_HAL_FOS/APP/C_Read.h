#ifndef __C_Read_H__
#define __C_Read_H__
#include "sys.h"
#include "C_USART.h"
#include "FreeRTOS.h"
#include "task.h"
void Read_SWJ(void);

typedef struct 
{
    /* data */
    float PWM;
}d_read;


typedef struct 
{
    /* data */
    void (*C_Read_SWJ)(void);
    d_read C_DATA;
}m_read;

extern m_read C_Read;

#endif 
