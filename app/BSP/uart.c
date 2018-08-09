#include "include.h"

UART_InitTypeDef uart_init_struct;
void UART_init()
{
  uart_init_struct.UART_Uartx = UART5; //use UART5
  uart_init_struct.UART_BaudRate = 115200; //115200
  uart_init_struct.UART_RxPin = PTE9;  //rxd
  uart_init_struct.UART_TxPin = PTE8;  //txd
  uart_init_struct.UART_RxIntEnable = TRUE;
  uart_init_struct.UART_RxIsr = pcdata; //freecars isr
  //UART init
  LPLD_UART_Init(uart_init_struct);
  LPLD_UART_EnableIrq(uart_init_struct);
}