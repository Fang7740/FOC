#ifndef __C_OLED_H__
#define __C_OLED_H__
#include "sys.h"

//-----------------OLED�˿ڶ���----------------  					   

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

#define OLED_CS_H   		OLED_CS_GPIO ->BSRR  = OLED_CS_Pin  //�ߵ�ƽ
#define OLED_CS_L   		OLED_CS_GPIO ->BRR   = OLED_CS_Pin  //�͵�ƽ

#define OLED_DC_H   		OLED_DC_GPIO ->BSRR  = OLED_DC_Pin  //�ߵ�ƽ
#define OLED_DC_L   		OLED_DC_GPIO ->BRR   = OLED_DC_Pin  //�͵�ƽ

#define OLED_RST_H   		OLED_RST_GPIO ->BSRR = OLED_RST_Pin  //�ߵ�ƽ
#define OLED_RST_L   		OLED_RST_GPIO ->BRR  = OLED_RST_Pin  //�͵�ƽ

#define OLED_SDA_H   		OLED_SDA_GPIO ->BSRR = OLED_SDA_Pin  //�ߵ�ƽ
#define OLED_SDA_L   		OLED_SDA_GPIO ->BRR  = OLED_SDA_Pin  //�͵�ƽ

#define OLED_SCL_H   		OLED_SCL_GPIO ->BSRR = OLED_SCL_Pin  //�ߵ�ƽ
#define OLED_SCL_L   		OLED_SCL_GPIO ->BRR  = OLED_SCL_Pin  //�͵�ƽ
//-----------------OLED�˿ڶ���---------------- 
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

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

void OLED_DisplayTurn(uint8_t i); ////��Ļ��ת180��
void OLED_ColorTurn(uint8_t i);  ////���Ժ���
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
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode); //��ָ��λ����ʾһ���ַ�,���������ַ� //x:0~127  //y:0~63 //size1:ѡ������ 6x8/6x12/8x16/12x24 //mode:0,��ɫ��ʾ;1,������ʾ
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r); //x,y:Բ������
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);//����
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);  //����
void OLED_Clear(void); //��������
void OLED_Refresh(void);
void OLED_DisPlay_Off(void);  //�ر�OLED��ʾ
void OLED_DisPlay_On(void);  ////����OLED��ʾ
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
void OLED_Init(void);

typedef struct
{
	void (*C_OLED_Init)(void);
	////��Ļ��ת180��
	void (*C_OLED_DisplayTurn)(uint8_t i); 
	////���Ժ���
	void (*C_OLED_ColorTurn)(uint8_t i);  
	  //�ر�OLED��ʾ
	void (*C_OLED_DisPlay_Off)(void);
	////����OLED��ʾ
	void (*C_OLED_DisPlay_On)(void);  
	//��������
	void (*C_OLED_Clear)(void); 
	void (*C_OLED_DrawPoint)(uint8_t x, uint8_t y, uint8_t t);  //����
	void (*C_OLED_DrawLine)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);//����
	void (*C_OLED_DrawCircle)(uint8_t x, uint8_t y, uint8_t r); //x,y:Բ������
	//��ʾ�ַ��� //x,y:������� //size1:�����С  //*chr:�ַ�����ʼ��ַ  //mode:0,��ɫ��ʾ;1,������ʾ
	void (*C_OLED_ShowString)(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode);
	//��ָ��λ����ʾһ���ַ�,���������ַ� //x:0~127  //y:0~63 //size1:ѡ������ 6x8/6x12/8x16/12x24 //mode:0,��ɫ��ʾ;1,������ʾ
	void (*C_OLED_ShowChar)(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode); 
	//��ʾһ�������ַ�
	void (*C_OLED_Show_CH_String)(uint8_t x, uint8_t y, const uint8_t *p, uint8_t size, uint8_t mode);
	//��ʾ���� //x,y :������� //num :Ҫ��ʾ������ //len :���ֵ�λ�� //size:�����С //mode:0,��ɫ��ʾ;1,������ʾ
	void (*C_OLED_ShowNumber)(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size1, uint8_t mode);
	//��ʾ���� //x,y:������� //num:���ֶ�Ӧ����� //mode:0,��ɫ��ʾ;1,������ʾ
	void (*C_OLED_ShowChinese)(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mod);
	//��ʾ����
	void (*C_OLED_ShowCH)(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode);
	//x,y���������  //sizex,sizey,ͼƬ����  //BMP[]��Ҫд���ͼƬ����  //mode:0,��ɫ��ʾ;1,������ʾ
	void (*C_OLED_ShowPicture)(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode);
	
}m_oled;
extern m_oled C_OLED;

#endif

