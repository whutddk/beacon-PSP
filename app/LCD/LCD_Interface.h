#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H


#include "include.h"



#define  USE_FSMC
//#define  USE_SPI




//LCD重要参数集
typedef struct  
{										    
	uint16 width;			//LCD 宽度
	uint16 height;			//LCD 高度
	uint16 id;				//LCD ID（ATK-7' TFTLCD不支持id读）
	uint8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	uint16 sysreg;			//PREF寄存器，设置当前操作页，显示页和背光等（ATK-7' TFTLCD暂不支持横竖屏设置，统一为横屏）。	
	uint8	wramcmd;		//开始写gram指令
	uint8  setxcmd;		//设置x坐标指令
	uint8  setycmd;		//设置y坐标指令	 
}_lcd_dev; 	  



//-----------------------------------------------------------------------------------------------
#define LCD_COMM_ADD		 (*((volatile unsigned short *) 0x6F010000)) /* RS = 0 */	 	 	          //命令或状态地址
#define LCD_DATA_ADD		 (*((volatile unsigned short *) 0x6F000000)) /* RS = 1 */

void LCD_CmdWrite(uint8_t cmd);
void LCD_DataWrite(uint8_t data);
void LCD_DataWrite(uint8_t data);
uint8_t LCD_DataRead(void);
uint8_t LCD_StatusRead(void);
uint8_t LCD_CmdRead(uint8_t Addr);





#endif /*_LCD_INTERFACE_H*/



