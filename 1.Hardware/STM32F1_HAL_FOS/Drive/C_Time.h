#ifndef __C_Time_H__
#define __C_Time_H__
#include "sys.h"
void Time3_Init(u32 Time);

typedef struct{
	
	void (*C_Time3_Init)(u32 Time);
	
}
m_time;
extern m_time C_Time;
#endif

