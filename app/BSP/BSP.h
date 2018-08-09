#ifndef _BSP_H_
#define _BSP_H_

extern uint16 sys_cnt ;
extern uint16 bz_cnt ;
extern uint16 bzpwm_cnt;
extern uint16 BAR_set[4] ; 
void sysinit();
void pit0_init();//1ms system timer
void sys_timer();

void UART_init();//uart5 init

void BZPWM_init(uint32 tone);
void BZPWM_ON(uint32 tone );
void BZPWM_OFF();
void gpio_init();

void ADC_init();
void get_bar();
void dac_init();
#endif
