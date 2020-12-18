#ifndef __Timer_H__
#define __Timer_H__
#include "sys.h"

void Timer_Run(void);
typedef struct
{
	int Tim_MS;
	int Tim_S;
	int Tim_Min;
	int Tim_H;
}
Time;
typedef struct{
	void (*C_Timer_Run)(void);
	Time C_Time;
}
m_timer;
extern m_timer C_Timer;

#endif

