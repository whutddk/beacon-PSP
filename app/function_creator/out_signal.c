#include "include.h"
#include "arm_math.h"
uint16 vp2p = 0;
uint8 sign_style = 0;
uint16 TIMER = 1000;
uint16 outs_cnt = 0;

int16 sinlist[100] = {
0,  62,125,187,248,
309,368,425,481,535,
587,637,684,728,770,
809,844,876,904,929,
951,968,982,992,998,
1000,998,992,982,968,
951,929,904,876,844,
809,770,728,684,637,
587,535,481,425,368,
309,248,187,125,62,
0,   -62,-125,-187,-248,
-309,-368,-425,-481,-535,
-587,-637,-684,-728,-770,
-809,-844,-876,-904,-929,
-951,-968,-982,-992,-998,
-1000,-998,-992,-982,-968,
-951,-929,-904,-876,-844,
-809,-770,-728,-684,-637,
-587,-535,-481,-425,-368,
-309,-248,-187,-125,-62

};

PIT_InitTypeDef outs_init_struct;
void pit1_init()//10us system timer
{
  //PIT0 config
  outs_init_struct.PIT_Pitx = PIT1;
  outs_init_struct.PIT_PeriodS = 0;
  outs_init_struct.PIT_PeriodMs = 0;     //定时周期
  outs_init_struct.PIT_PeriodUs = 10;     
  outs_init_struct.PIT_Isr = out_cnt;  //设置中断函数
  //PIT0 init
  LPLD_PIT_Init(outs_init_struct); 
  
  LPLD_PIT_EnableIrq(outs_init_struct);

}

void out_cnt()
{
  outs_cnt ++;
//out_signal();
}

  uint16 out_temp = 2048;
float temp2 ,temp3;
void out_signal()
{
  if (!LPLD_GPIO_Input_b(PTA, 24) && sign_style != 0)
  {
    bz_set(datarec);
    sign_style = 0;
  }
  else if ( !LPLD_GPIO_Input_b(PTA, 25) && sign_style != 1)
  {
    bz_set(datarec);
    sign_style = 1;
  }
   else if ( !LPLD_GPIO_Input_b(PTA, 26) && sign_style != 2)
  {
    bz_set(datarec);
    sign_style = 2;
  }
  
  get_bar();
  vp2p = BAR_set[0] / 2;
  TIMER = BAR_set[3] * 2;
  if (outs_cnt >= TIMER)
  {
    outs_cnt = 0;
  }
  switch (sign_style)
    {
      
      case(0)://sin
//temp2 = //outs_cnt / TIMER ;
        //arm_sin_cos_f32(360 * outs_cnt / TIMER, &temp2, &temp3)  ;
        out_temp =((1000 + sinlist[(uint8)(100*outs_cnt / TIMER)]) * vp2p /1000);
        break;
        case(1)://trigle 
           if( outs_cnt < (TIMER / 2) )
          {
            out_temp = vp2p * outs_cnt / (TIMER / 2);
          }
          else
          {
            out_temp = vp2p - ( vp2p * (outs_cnt - TIMER / 2)) / (TIMER / 2) ;
          }
           
          break;
          case(2):
            if( outs_cnt < (TIMER / 2) )
          {
            out_temp = vp2p;
          }
          else
          {
            out_temp = 0;
          }
          break;
    }
//  if( out_temp > 65535 )    
//  {
//    out_temp = 65535;
//  }

  LPLD_DAC_SetBufferDataN(DAC0,out_temp, 1);
}