#include "include.h"

DAC_InitTypeDef dac_init_struct;

void dac_init()
{
  //�ڲ�ʹ��DAC�������������ж�DMA�������
  //�����ʼ��DACͨ������
  dac_init_struct.DAC_Dacx = DAC0;
  LPLD_DAC_Init(dac_init_struct);
}