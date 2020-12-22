#ifndef __C_PWM_H__
#define __C_PWM_H__
#include "sys.h"

void TIM3_Init(u16 arr,u16 psc);
void TIM2_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void PWM_120_Out(float PWM);

typedef struct 
{
    void  (*C_TIM3_Init)(u16 arr,u16 psc);
    void  (*C_TIM2_Init)(u16 arr,u16 psc);
    void  (*C_TIM4_Init)(u16 arr,u16 psc);
    void  (*C_PWM_120_Out)(float PWM);
}m_pwm;
extern m_pwm C_PWM;
#endif

