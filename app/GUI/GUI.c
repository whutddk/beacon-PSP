#include "include.h"

extern int16 BUFF[];


//the data in show[] will be output when call show_string
uint8 show[9] = "$$$$$.$$$";

void buf2asc(double data)
{
  int16 num = (int16)data;
  uint16 temp1 = 0;
  uint16 temp2 = 0;
  
  
  uint8* p = show;
  
 //decise the sign
  {
    if (num < 0)
    {
      *p = '-';
      num = -num;
    }
    else
    {
      *p = '+';
    }
    p++;
  }
  //1000
  {
    temp1 = num / 1000;
    if ( temp1 != 0 )
    {
      *p = temp1 + 0x30;
      p++;
    }
  }
  //100
  {
    num = num % 1000;
    
    temp2 = num / 100 ;
    
    if ( temp2 != 0 || temp1 != 0 )
    {
      *p = temp2 + 0x30;
      p++;
    }
  } 
  //10
  {
    num = num % 100;
    temp1 = num / 10;
    if ( p != show || temp1 != 0 )
    {
      *p = temp1 + 0x30;
      p++;
    }
  }
  //1
  {
    num = num % 10;
    *p = num + 0x30;
    p++;
  }
  //.
  {
    *p = '.';
    p++;
  }
  num = (int16)data * 1000;  
  //0.1
  {
    temp2 = num / 100 ;
    *p = temp2 + 0x30;
    p++;
  }
  
  //0.01
  {
    num = num % 100;
    temp1 = num / 10;   
    *p = temp1 + 0x30;
    p++;
    
  }
  //0.001
  {
    num = num % 10;
    *p = num + 0x30;
  }


}


//必要时刷新
void debugdata_input()
{
  LCD_Initializtion();
  LcdClear(Cyan);
  
  buf2asc(-5987.032);
  LCD_Internal_Font_ROM(100,50,Black,White,0,0,4,0);
  Show_String( show,1);
  
  buf2asc(show_chn[1]);
  LCD_Internal_Font_ROM(250,50,Black,White,0,0,4,0);
  Show_String(show,1);
  
  buf2asc(show_chn[2]);
  LCD_Internal_Font_ROM(400,50,Black,White,0,0,4,0);
  Show_String( show,1);
  
  buf2asc(show_chn[3]);
  LCD_Internal_Font_ROM(550,50,Black,White,0,0,4,0);
  Show_String(show,1);
  
  buf2asc(show_chn[4]);
  LCD_Internal_Font_ROM(100,200,Black,White,0,0,4,0);
  Show_String(show,1);
  
  buf2asc(show_chn[5]);
  LCD_Internal_Font_ROM(250,200,Black,White,0,0,4,0);
  Show_String(show,1);
  
  buf2asc(show_chn[6]);
  LCD_Internal_Font_ROM(400,200,Black,White,0,0,4,0);
  Show_String(show,1);
  
//  buf2asc(show_chn[7]);
//  LCD_Internal_Font_ROM(550,200,Black,White,0,0,4,0);
//  Show_String(show,1);
  
    /*矩阵键盘显示*/
  LCD_Internal_Font_ROM(650,230,White,Magenta,0,0,4,0);
  Show_String(" +    -   yes  stop",1);
  
  LCD_Internal_Font_ROM(650,280,White,Magenta,0,0,4,0);
  Show_String(" 5    6    7    8 ",1);
  
  LCD_Internal_Font_ROM(650,330,White,Magenta,0,0,4,0);
  Show_String(" 9    0    A    B ",1);
  
  LCD_Internal_Font_ROM(650,380,White,Magenta,0,0,4,0);
  Show_String(" C    D    E    F ",1);
}