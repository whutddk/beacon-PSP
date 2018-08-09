#include "include.h"


PIT_InitTypeDef pit_init_struct;


void pit0_init()//1ms system timer
{
  //PIT0 config
  pit_init_struct.PIT_Pitx = PIT0;
  pit_init_struct.PIT_PeriodS = 0;
  pit_init_struct.PIT_PeriodMs = 1;     //��ʱ����
  pit_init_struct.PIT_PeriodUs = 0;     
  pit_init_struct.PIT_Isr = sys_timer;  //�����жϺ���
  //PIT0 init
  LPLD_PIT_Init(pit_init_struct); 
  
  LPLD_PIT_EnableIrq(pit_init_struct);

}