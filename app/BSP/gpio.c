#include "include.h"
GPIO_InitTypeDef io_inittype;
void gpio_init()
{
  io_inittype.GPIO_PTx = PTB; //led bz
  io_inittype.GPIO_Pins = GPIO_Pin19 | GPIO_Pin20 | GPIO_Pin21 | GPIO_Pin22 | GPIO_Pin23;
  io_inittype.GPIO_Dir = DIR_INPUT;
  io_inittype.GPIO_Output = OUTPUT_H;
  io_inittype.GPIO_PinControl = IRQC_DIS | INPUT_PULL_UP ;
  LPLD_GPIO_Init(io_inittype);
 
  io_inittype.GPIO_PTx = PTA; //led bz
  io_inittype.GPIO_Pins = GPIO_Pin24 | GPIO_Pin25 | GPIO_Pin26 | GPIO_Pin27 ;
  io_inittype.GPIO_Dir = DIR_INPUT;
  io_inittype.GPIO_Output = OUTPUT_H;
  io_inittype.GPIO_PinControl = IRQC_DIS | INPUT_PULL_UP ;
  LPLD_GPIO_Init(io_inittype);
}