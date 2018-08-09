#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H


#include "include.h"



#define  USE_FSMC
//#define  USE_SPI




//LCD��Ҫ������
typedef struct  
{										    
	uint16 width;			//LCD ���
	uint16 height;			//LCD �߶�
	uint16 id;				//LCD ID��ATK-7' TFTLCD��֧��id����
	uint8  dir;			//���������������ƣ�0��������1��������	
	uint16 sysreg;			//PREF�Ĵ��������õ�ǰ����ҳ����ʾҳ�ͱ���ȣ�ATK-7' TFTLCD�ݲ�֧�ֺ��������ã�ͳһΪ��������	
	uint8	wramcmd;		//��ʼдgramָ��
	uint8  setxcmd;		//����x����ָ��
	uint8  setycmd;		//����y����ָ��	 
}_lcd_dev; 	  



//-----------------------------------------------------------------------------------------------
#define LCD_COMM_ADD		 (*((volatile unsigned short *) 0x6F010000)) /* RS = 0 */	 	 	          //�����״̬��ַ
#define LCD_DATA_ADD		 (*((volatile unsigned short *) 0x6F000000)) /* RS = 1 */

void LCD_CmdWrite(uint8_t cmd);
void LCD_DataWrite(uint8_t data);
void LCD_DataWrite(uint8_t data);
uint8_t LCD_DataRead(void);
uint8_t LCD_StatusRead(void);
uint8_t LCD_CmdRead(uint8_t Addr);





#endif /*_LCD_INTERFACE_H*/



