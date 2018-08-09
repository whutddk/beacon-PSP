
#include "include.h"

uint16 color_table[]={Red,Green,Blue,White,Black,Grey,Blue2,Magenta,Cyan,Yellow};
uint8 TxBuf[32]=
{
0x01,0x02,0x03,0x4,0x05,0x06,0x07,0x08,
0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,
0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24,
0x25,0x26,0x27,0x28,0x29,0x30,0x31,0x32,
};
uint8 RxBuf[32] = {0,0};

void main (void)
{
  uint16 i;
  

  sysinit();
  
//  
//  
// //HY 
//    Active_Window(0,199,100,339);
//  //	Graphic_Mode();
//  XY_Coordinate(0,100);
//  LCD_CmdWrite(0x02);//MRWC
//  
//  for(i=0;i<48000;i++)
//  {
//    QU_DataWrite(HY[i*2]);
//    QU_DataWrite(HY[i*2+1]);
//    Chk_Busy();
//  }
//   //Hawx 
//    Active_Window(551,799,250,479);
//  //	Graphic_Mode();
//  XY_Coordinate(551,250);
//  LCD_CmdWrite(0x02);//MRWC
//  
//  for(i=0;i<57270;i++)
//  {
//    QU_DataWrite(HAWX[i*2]);
//    QU_DataWrite(HAWX[i*2+1]);
//    Chk_Busy();
//  }
  
  LPLD_LPTMR_DelayMs(1000);
  
  
  debugdata_input();
  /* Infinite loop */
    pit1_init();
    
   bz_set(ready);
  while (1)
  {
//    if ( bzpwm_cnt > 100 )
//    {
//      bzpwm_cnt = 0;
//      get_bar();
//      BZPWM_init(BAR_set[0]);
//    }
    

    bzled_work();
    out_signal();
    //LPLD_Nrf24L01_debug();
//    bzled_work();
    //LPLD_Nrf24L01_RxModeInit();
    //LPLD_Nrf24L01_RecvFrame(RxBuf,32);
    //CT_TEST();
//    for(i=0;i<799;i++)
//    {
//      Scroll_Offset(i,0);
//      Chk_Busy();
//      LPLD_LPTMR_DelayMs(1);
//    }	
  }
}

