#include "include.h"

FTM_InitTypeDef ftm_init_struct;
void BZPWM_init(uint32 tone)
{
  //pwm
  ftm_init_struct.FTM_Ftmx = FTM2;	//bz init
  ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	
  ftm_init_struct.FTM_PwmFreq = tone;	//100HZ
  ftm_init_struct.FTM_PwmDeadtimeCfg = DEADTIME_CH23;
  ftm_init_struct.FTM_PwmDeadtimeVal=0;
  LPLD_FTM_Init(ftm_init_struct);
  
  LPLD_FTM_PWM_Enable(FTM2, 
                      FTM_Ch0, 
                      5000, 
                      PTB18, 
                      ALIGN_LEFT        
                        ); 
}

void BZPWM_ON(uint32 tone )
{
  LPLD_FTM_Deinit(ftm_init_struct);
  BZPWM_init(tone);
}

void BZPWM_OFF()
{
  LPLD_FTM_Deinit(ftm_init_struct);
  BZPWM_init(50);
}