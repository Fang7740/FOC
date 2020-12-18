#include "Timer.h"
#include "C_USART.h"
m_timer C_Timer=
{
	Timer_Run,
	0,0,0,0,
};
void Timer_Run()
{
	
		C_Timer.C_Time.Tim_S++;
	//printf("Time=%d\r\n",C_Timer.C_Time.Tim_S);
}
