#include "include.h"

uint16 sys_cnt = 0;

uint16 bzpwm_cnt = 0 ;
void sys_timer()
{
  sys_cnt++;
  bz_cnt++;
  bzpwm_cnt++;
  if ( sys_cnt >= 1000 )
  {
    sys_cnt = 0;
  }
} 
  