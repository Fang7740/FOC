/*

  WS2812B CPU and memory efficient library

  Date: 28.9.2016

  Author: Martin Hubacek
  	  	  http://www.martinhubacek.cz
  	  	  @hubmartin

  Licence: MIT License

*/

#ifndef WS2812B_H_
#define WS2812B_H_
#include "sys.h"



void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_DMA_Init(void);
void MX_GPIO_Init(void);
void _Error_Handler(char *file, int line);

typedef struct 
{
  /* data */
  void (*C_MX_TIM2_Init)(void);
  void (*C_MX_TIM3_Init)(void);
  void (*C_MX_TIM4_Init)(void);
  void (*C_MX_DMA_Init)(void);
  void (*C_MX_GPIO_Init)(void);
  void (*C__Error_Handler)(char *file, int line);

}m_ws2812b;
extern m_ws2812b C_WS2812B;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim3;
extern DMA_HandleTypeDef hdma_tim2;
extern DMA_HandleTypeDef hdma_tim3;
extern DMA_HandleTypeDef hdma_tim4;

#endif 

