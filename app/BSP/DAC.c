#include "include.h"

DAC_InitTypeDef dac_init_struct;

void dac_init()
{
  //在不使用DAC缓冲区、各种中断DMA的情况下
  //仅需初始化DAC通道即可
  dac_init_struct.DAC_Dacx = DAC0;
  LPLD_DAC_Init(dac_init_struct);
}