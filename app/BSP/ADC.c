#include "include.h"

ADC_InitTypeDef adc_struct;
uint16 BAR_set[4] ={0}; 

void ADC_init()
{
  adc_struct.ADC_Adcx = ADC1;
  adc_struct.ADC_BitMode = SE_12BIT;
  adc_struct.ADC_DiffMode = ADC_SE;
  adc_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;
  adc_struct.ADC_HwAvgSel = HW_DISAVG ;
  adc_struct.ADC_CalEnable = TRUE;
  adc_struct.ADC_DmaEnable = FALSE;        
  adc_struct.ADC_HwTrgCfg = HW_TRGDSABLE;      
  
  LPLD_ADC_Init(adc_struct);
  
  LPLD_ADC_Chn_Enable(ADC1, AD14); //B10
  LPLD_ADC_Chn_Enable(ADC1, AD15); //B11
  LPLD_ADC_Chn_Enable(ADC1, AD16); //
  
  adc_struct.ADC_Adcx = ADC0;
  adc_struct.ADC_BitMode = SE_12BIT;
  adc_struct.ADC_DiffMode = ADC_SE;
  adc_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;
  adc_struct.ADC_HwAvgSel = HW_DISAVG ;
  adc_struct.ADC_CalEnable = TRUE;
  adc_struct.ADC_DmaEnable = FALSE;        
  adc_struct.ADC_HwTrgCfg = HW_TRGDSABLE;      
  
  LPLD_ADC_Init(adc_struct);
  LPLD_ADC_Chn_Enable(ADC0, AD16); //
}

void get_bar()
{
  BAR_set[0] = LPLD_ADC_Get(ADC1, AD14);
  BAR_set[1] = LPLD_ADC_Get(ADC1, AD15);
  BAR_set[2] = LPLD_ADC_Get(ADC1, AD16);
  BAR_set[3] = LPLD_ADC_Get(ADC0, AD16);
}
