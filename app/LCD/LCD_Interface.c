
#include "include.h"

void delay()
{
  uint8 i,j;
    for (i = 0 ; i< 254;i++)
      for ( j = 0 ; j < 40;j++ );
}

void LCD_CmdWrite(uint8_t cmd)
{	
  LCD_RD_1;
  LCD_CS_0;
  LCD_RS_1;
  
 LPLD_GPIO_Output_8b(PTD, 0, cmd);
  
  LCD_WR_0;
  
  delay();
  //LPLD_SYSTICK_DelayUs(200 );

  LCD_WR_1;
  LCD_CS_1;
  
  LPLD_GPIO_Output_8b(PTD, 0, 0XFF);
  
  LCD_RS_0;
}

void QU_CmdWrite(uint8_t cmd)
{	
  LCD_RD_1;
  LCD_CS_0;
  LCD_RS_1;
  
 LPLD_GPIO_Output_8b(PTD, 0, cmd);
  
  LCD_WR_0;
  

  LCD_WR_1;
  LCD_CS_1;
  
  LPLD_GPIO_Output_8b(PTD, 0, 0XFF);
  
  LCD_RS_0;
}

/*************************LCD数据写入*********************************/
void LCD_DataWrite(uint8_t data)
{
  LCD_RD_1;     
  LCD_CS_0;
  LCD_RS_0;
  
  LPLD_GPIO_Output_8b(PTD, 0, data);
  
  LCD_WR_0;
  
  delay();
  //LPLD_SYSTICK_DelayUs(200 );
  
  LCD_WR_1;
  LCD_CS_1;
  
  LPLD_GPIO_Output_8b(PTD, 0, 0XFF);
  
  LCD_RS_1;	
}

void QU_DataWrite(uint8_t data)
{
  LCD_RD_1;     
  LCD_CS_0;
  LCD_RS_0;
  
  LPLD_GPIO_Output_8b(PTD, 0, data);
  
  LCD_WR_0;
  
  //delay();
  //LPLD_SYSTICK_DelayUs(200 );
  
  LCD_WR_1;
  LCD_CS_1;
  
  LPLD_GPIO_Output_8b(PTD, 0, 0XFF);
  
  LCD_RS_1;	
}

/*********************SPI 数据读取*********************************/
uint8_t LCD_DataRead(void)
{
  uint8 Data;
  LCD_WR_1;
  LCD_CS_0;
  LCD_RS_0;
  LCD_RD_0;
  Data = LPLD_GPIO_Input_b(PTD, 0);
  LCD_RD_1;
  LCD_CS_1;
  LCD_RS_1;
  return Data;
}  

uint8_t LCD_StatusRead(void)
{
  uint8 Data;
  LCD_CS_0;
  LCD_RS_1;
  LCD_WR_1;
  LCD_RD_0;
  
  Data = LPLD_GPIO_Input_b(PTD, 0);
  
  LCD_RD_1;
  LCD_CS_1;
  
  LPLD_GPIO_Output_8b(PTD, 0, 0XFF);
  
  LCD_RS_0;
  
  return Data;
}

//uint8_t LCD_CmdRead(uint8_t Addr)
//{
//   return (LCD_COMM_ADD);
//}
