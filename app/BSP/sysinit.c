#include "include.h"

void sysinit()
{  
  uint16 i;
  
  LCD_Initializtion();
  LcdClear(Blue);

      //WHUT
  Active_Window(700,798,0,99); 
  //	Graphic_Mode();
  XY_Coordinate(0,0);
  LCD_CmdWrite(0x02);//MRWC

  for(i=0;i<9900;i++)
  {
    QU_DataWrite(WHUT[i*2]);
    QU_DataWrite(WHUT[i*2+1]);
    Chk_Busy();
  }
  

  LCD_Internal_Font_ROM(0,0,White,Magenta,0,0,4,0);
  Show_String("WUHAN UNIVERSITY OF TECHNOLOGY",1);
  
  bzled_init();
  LCD_Internal_Font_ROM(0,30,White,Black,0,0,4,0);
  Show_String("BZ_LED READY...",1);
  
  UART_init();
  LCD_Internal_Font_ROM(0,60,White,Black,0,0,4,0);
  Show_String("UART READY...",1);
  
  BZPWM_init(500);
  LCD_Internal_Font_ROM(0,90,White,Black,0,0,4,0);
  Show_String("BZ_PWM READY...",1);
  
  LPLD_Nrf24L01_Init();
  LCD_Internal_Font_ROM(0,120,White,Black,0,0,4,0);
  Show_String("24L01 READY...",1);
  
  ADC_init();
  LCD_Internal_Font_ROM(0,150,White,Black,0,0,4,0);
  Show_String("ADC READY...",1);
  
  dac_init();
  LCD_Internal_Font_ROM(0,180,White,Black,0,0,4,0);
  Show_String("DAC READY...",1);
  
  gpio_init();
  LCD_Internal_Font_ROM(0,210,White,Black,0,0,4,0);
  Show_String("IO READY...",1);
  
  pit0_init();//1ms system timer
  LCD_Internal_Font_ROM(0,240,White,Black,0,0,4,0);
  Show_String("PIT READY...",1);
  
  LED_OFF;
  BZ_OFF;
}