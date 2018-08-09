#include "include.h"

//double chn[10] = {10.999999};
double show_chn[50] = {0.,0.};


void send_data(uint8 chn , double data)
{
  uint8 data_buff[32] = { 2 };
  uint16 temp16 = 0;
  uint32 data_cal = 0;
  LPLD_Nrf24L01_TxModeInit();
  if ( chn <= 10 )
  {
    data_buff[0] =  chn ;
    
    if ( data > 0.0000000000 )
    {
      data_buff[1] = 0;
    }
    else
    {
      data_buff[1] = 1;
      data = -data;
    }
    
    //send_data_push
    data_cal = (uint32) ( data * 1000 ) ;
    
    temp16 = (uint16) (data_cal >> 16); //upper 16
    data_buff [2] = (uint8) ( temp16 >> 8 );
    data_buff [3] = (uint8) ( temp16 & 0x00ff );
    
    temp16 = (uint16) ( data_cal & 0x0ffff );
    data_buff [4] = (uint8) ( temp16 >> 8 );
    data_buff [5] = (uint8) ( temp16 & 0x00ff );
    
    LPLD_Nrf24L01_SendFrame( data_buff, 32 );
    
  }
  
  else
  {
    return;
  }
  
}

void data_rec()
{
  uint8 data_buff[32] = {100,0};
  uint8 channel  ;
  uint32 temp32 = 0;
  
  LPLD_Nrf24L01_RxModeInit();
  
  LPLD_Nrf24L01_RecvFrame(data_buff, 32);
  
  //no data
  if ( data_buff[0] >= 50 )
  {
    return;
  }
  
  //we have only 10 chn to receive data
  if (data_buff[0] <= 10 )
  {
    channel = data_buff[0];
    
    //get data
    temp32 
      = data_buff[2] << 24 
      | data_buff[3] << 16 
        | data_buff[4] << 8 
          |data_buff[5]  ;
    
    if ( data_buff[1] == 0 )
    {
      show_chn[channel] = temp32 / 1000.0 ;
    }
    
    else if ( data_buff[1] == 1 )
    {
      show_chn[channel] = temp32 / ( -1000.0 ) ;
    }
    
  }
  data_refresh();
  
}


