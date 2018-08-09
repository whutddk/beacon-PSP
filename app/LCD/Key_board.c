#include "include.h"
extern uint8 show[9];
extern double show_chn[50];
extern uint8 TxBuf[32];
uint8 *key_value = 0;  
void Key_Scan()
{
  show[6] = 0.000000;
  if(ctp_dev.x[0] > 640 && ctp_dev.x[0] < 680)       //第一列
  {
    if(ctp_dev.y[0] < 250&&ctp_dev.y[0] > 215)     
    {
      show[7] = 0;
      send_data(0, 111);
      
    }  
    if(ctp_dev.y[0] < 215&&ctp_dev.y[0] > 155)
    {
      show[7] = show[7] + 10.0;
      send_data(4, 555);
    }
    if(ctp_dev.y[0] < 155&&ctp_dev.y[0] > 105)
    {
      show[7] = 9;
      send_data(8, 999);
    }
    if(ctp_dev.y[0] < 105&&ctp_dev.y[0] > 60)
    {
      show[7] = 13;
      send_data(12, 131313);
    }
  }
  else if(ctp_dev.x[0] > 680&&ctp_dev.x[0] < 725)       //第二列
  {
    if(ctp_dev.y[0] < 250&&ctp_dev.y[0] > 215)     
    {
      show[7] = 250;
      send_data(1, 222);
    }  
    if(ctp_dev.y[0] < 215&&ctp_dev.y[0] > 155)
    {
      show[7]= show[7] -  10.0;
      send_data(5, 666);
    }
    if(ctp_dev.y[0] < 155&&ctp_dev.y[0] > 105)
    {
      show[7] = 10;
      send_data(9, 101010);
    }
    if(ctp_dev.y[0] < 105&&ctp_dev.y[0] > 60)
    {
      show[7] = 14;
      send_data(13, 141414);
    }    
  }
  else if(ctp_dev.x[0] > 725&&ctp_dev.x[0] < 770)       //第三列
  {
    if(ctp_dev.y[0] < 250&&ctp_dev.y[0] > 215)     
    {
      show[7] = show[7] + 50.0;
      send_data(2, 333);
    }  
    if(ctp_dev.y[0] < 215&&ctp_dev.y[0] > 155)
    {
      show[7] = 7;
      send_data(6, 777);
    }
    if(ctp_dev.y[0] < 155&&ctp_dev.y[0] > 105)
    {
      show[7] = 11;
      send_data(10, 111111);
    }
    if(ctp_dev.y[0] < 105&&ctp_dev.y[0] > 60)
    {
      show[7] = 15;
      send_data(14, 151515);
    }  
  }
  else if(ctp_dev.x[0] > 770&&ctp_dev.x[0] < 800)       //第四列
  {
    if(ctp_dev.y[0] < 250&&ctp_dev.y[0] > 215)     
    {
      show[7]= show[7] - 50.0;
      send_data(3, 444);
    }  
    if(ctp_dev.y[0] < 215&&ctp_dev.y[0] > 155)
    {
      show[7] = 8;
      send_data(7, 888);
    }
    if(ctp_dev.y[0] < 155&&ctp_dev.y[0] > 105)
    {
      show[7] = 12;
      send_data(11, 121212);
    }
    if(ctp_dev.y[0] < 105&&ctp_dev.y[0] > 60)
    {
      show[7] = 16;
      send_data(15, 161616);
    }  
  }
  buf2asc(1234);
  LCD_Internal_Font_ROM(550,200,Black,White,0,0,4,0);
  Show_String(show,1);
}