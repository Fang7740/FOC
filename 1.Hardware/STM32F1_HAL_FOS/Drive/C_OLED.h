#ifndef __C_OLED_H__
#define __C_OLED_H__
#include "sys.h"

//-----------------OLED端口定义----------------  					   

#define OLED_CS_GPIO		GPIOB	
#define OLED_CS_Pin		    GPIO_PIN_0

#define OLED_DC_GPIO		GPIOB	
#define OLED_DC_Pin		    GPIO_PIN_1

#define OLED_RST_GPIO		GPIOB	
#define OLED_RST_Pin		GPIO_PIN_3

#define OLED_SDA_GPIO		GPIOB	
#define OLED_SDA_Pin		GPIO_PIN_4

#define OLED_SCL_GPIO		GPIOB	
#define OLED_SCL_Pin		GPIO_PIN_5

#define OLED_CS_H   		OLED_CS_GPIO ->BSRR  = OLED_CS_Pin  //高电平
#define OLED_CS_L   		OLED_CS_GPIO ->BRR   = OLED_CS_Pin  //低电平

#define OLED_DC_H   		OLED_DC_GPIO ->BSRR  = OLED_DC_Pin  //高电平
#define OLED_DC_L   		OLED_DC_GPIO ->BRR   = OLED_DC_Pin  //低电平

#define OLED_RST_H   		OLED_RST_GPIO ->BSRR = OLED_RST_Pin  //高电平
#define OLED_RST_L   		OLED_RST_GPIO ->BRR  = OLED_RST_Pin  //低电平

#define OLED_SDA_H   		OLED_SDA_GPIO ->BSRR = OLED_SDA_Pin  //高电平
#define OLED_SDA_L   		OLED_SDA_GPIO ->BRR  = OLED_SDA_Pin  //低电平

#define OLED_SCL_H   		OLED_SCL_GPIO ->BSRR = OLED_SCL_Pin  //高电平
#define OLED_SCL_L   		OLED_SCL_GPIO ->BRR  = OLED_SCL_Pin  //低电平
//-----------------OLED端口定义---------------- 
#define OLED_CS_Clr()   OLED_CS_L    //DC
#define OLED_CS_Set()   OLED_CS_H    //DC

#define OLED_DC_Clr()   OLED_DC_L    //DC
#define OLED_DC_Set()   OLED_DC_H    //DC

#define OLED_RST_Clr()  OLED_RST_L   //RST
#define OLED_RST_Set()  OLED_RST_H   //RST

#define OLED_SDIN_Clr() OLED_SDA_L   //SDA
#define OLED_SDIN_Set() OLED_SDA_H   //SDA

#define OLED_SCLK_Clr() OLED_SCL_L   //SCL
#define OLED_SCLK_Set() OLED_SCL_H   //SCL

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_DisplayTurn(uint8_t i); ////屏幕旋转180度
void OLED_ColorTurn(uint8_t i);  ////反显函数
void OLED_Refresh_Gram(void);
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode);
void OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode);
void OLED_Show_CH(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
void OLED_ShowCH(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode);
void OLED_ShowNumber(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode);
uint32_t OLED_Pow(uint8_t m, uint8_t n);
void OLED_Show_CH_String(uint8_t x, uint8_t y, const uint8_t *p, uint8_t size, uint8_t mode);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode); //在指定位置显示一个字符,包括部分字符 //x:0~127  //y:0~63 //size1:选择字体 6x8/6x12/8x16/12x24 //mode:0,反色显示;1,正常显示
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r); //x,y:圆心坐标
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);//画线
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);  //画点
void OLED_Clear(void); //清屏函数
void OLED_Refresh(void);
void OLED_DisPlay_Off(void);  //关闭OLED显示
void OLED_DisPlay_On(void);  ////开启OLED显示
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
void OLED_Init(void);

typedef struct
{
	void (*C_OLED_Init)(void);
	////屏幕旋转180度
	void (*C_OLED_DisplayTurn)(uint8_t i); 
	////反显函数
	void (*C_OLED_ColorTurn)(uint8_t i);  
	  //关闭OLED显示
	void (*C_OLED_DisPlay_Off)(void);
	////开启OLED显示
	void (*C_OLED_DisPlay_On)(void);  
	//清屏函数
	void (*C_OLED_Clear)(void); 
	void (*C_OLED_DrawPoint)(uint8_t x, uint8_t y, uint8_t t);  //画点
	void (*C_OLED_DrawLine)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);//画线
	void (*C_OLED_DrawCircle)(uint8_t x, uint8_t y, uint8_t r); //x,y:圆心坐标
	//显示字符串 //x,y:起点坐标 //size1:字体大小  //*chr:字符串起始地址  //mode:0,反色显示;1,正常显示
	void (*C_OLED_ShowString)(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode);
	//在指定位置显示一个字符,包括部分字符 //x:0~127  //y:0~63 //size1:选择字体 6x8/6x12/8x16/12x24 //mode:0,反色显示;1,正常显示
	void (*C_OLED_ShowChar)(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode); 
	//显示一串中文字符
	void (*C_OLED_Show_CH_String)(uint8_t x, uint8_t y, const uint8_t *p, uint8_t size, uint8_t mode);
	//显示数字 //x,y :起点坐标 //num :要显示的数字 //len :数字的位数 //size:字体大小 //mode:0,反色显示;1,正常显示
	void (*C_OLED_ShowNumber)(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode);
	//显示汉字 //x,y:起点坐标 //num:汉字对应的序号 //mode:0,反色显示;1,正常显示
	void (*C_OLED_ShowChinese)(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mod);
	//显示汉字
	void (*C_OLED_ShowCH)(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
	//x,y：起点坐标  //sizex,sizey,图片长宽  //BMP[]：要写入的图片数组  //mode:0,反色显示;1,正常显示
	void (*C_OLED_ShowPicture)(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode);
	
}m_oled;
extern m_oled C_OLED;

#endif

