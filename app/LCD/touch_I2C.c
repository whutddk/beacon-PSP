#include "include.h"
GPIO_InitTypeDef Touch_I2C_init_struct; //触屏I2C
void touch_delay()
{
  uint8 i,j;
  for (i = 0 ; i< 1;i++)
    for ( j = 0 ; j < 100;j++ );
}

void CT_CLK_Init()
{
  Touch_I2C_init_struct.GPIO_PTx = PTD;
  Touch_I2C_init_struct.GPIO_Pins = GPIO_Pin8;   //PTD8-SCL   PTD9-SDA
  Touch_I2C_init_struct.GPIO_Dir = DIR_OUTPUT;
  Touch_I2C_init_struct.GPIO_Output = OUTPUT_H;
  Touch_I2C_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(Touch_I2C_init_struct);
}

void CT_SDA_IN()
{
  // 配置 SDA 输入,内部上拉，不产生中断
  Touch_I2C_init_struct.GPIO_PTx = PTD;      //PORTB
  Touch_I2C_init_struct.GPIO_Pins = GPIO_Pin9;     //引脚9
  Touch_I2C_init_struct.GPIO_Dir = DIR_INPUT;        //输入
  Touch_I2C_init_struct.GPIO_PinControl = INPUT_PULL_UP|IRQC_DIS;     //内部上拉|不产生中断
  LPLD_GPIO_Init(Touch_I2C_init_struct);	
}


void CT_SDA_OUT()
{
  Touch_I2C_init_struct.GPIO_PTx = PTD;
  Touch_I2C_init_struct.GPIO_Pins = GPIO_Pin9;   //PTD8-SCL   PTD9-SDA
  Touch_I2C_init_struct.GPIO_Dir = DIR_OUTPUT;
  Touch_I2C_init_struct.GPIO_Output = OUTPUT_H;
  Touch_I2C_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(Touch_I2C_init_struct);	
}
void CT_I2C_Start(void)
{
  DDRD9 = 1;
  //CT_SDA_OUT();     //sda??ê?3?
  SET_SDA();	  	  
  SET_CLK();
  touch_delay();
  CLR_SDA();//START:when CLK is high,DATA change form high to low 
  touch_delay();
  CLR_CLK();//?ˉ×?I2C×ü??￡?×?±?·￠?í?ò?óê?êy?Y 
}	  

void CT_I2C_Stop(void)
{
  DDRD9 = 1;
  CLR_CLK();
  CLR_SDA();//STOP:when CLK is high DATA change form low to high
  touch_delay();
  SET_CLK();
  SET_SDA();//·￠?íI2C×ü???áê?D?o?
  touch_delay();							   	
}


uint8 CT_I2C_Wait_Ack(void)
{
  uint8 ucErrTime=0;
  DDRD9 = 1;;      //SDAéè???aê?è?  
  SET_SDA();touch_delay();	   
  SET_CLK();touch_delay();
  DDRD9 = 0;
  while(CT_READ_SDA)
  {
    ucErrTime++;
    if(ucErrTime>250)
    {
      CT_I2C_Stop();
      return 1;
    }
  }
  CLR_CLK();//ê±?óê?3?0 	   
  return 0;  
} 

void CT_I2C_Ack(void)
{
  DDRD9 = 1;
  CLR_CLK();
  
  CLR_SDA();
  touch_delay();
  SET_CLK();
  touch_delay();
  CLR_CLK();
}

void CT_I2C_NAck(void)
{
  DDRD9 = 1;
  CLR_CLK();
  
  SET_SDA();
  touch_delay();
  SET_CLK();
  touch_delay();
  CLR_CLK();
}					 				     

void CT_I2C_Send_Byte(uint8 txd)
{                        
  uint8 t;   
  DDRD9 = 1; 
  CLR_CLK();//à-μíê±?ó?aê?êy?Y′?ê?
  for(t=0;t<8;t++)
  {              
    //        CT_I2C_SDA=(txd&0x80)>>7;
    if((txd&0x80)>>7)
      SET_SDA();
    else	
      CLR_SDA();
    
    txd<<=1; 	      
    SET_CLK();
    touch_delay(); 
    CLR_CLK();	
    touch_delay();
  }	 
} 	    

uint8 CT_I2C_Read_Byte(unsigned char ack)
{
  unsigned char i,receive=0;
  DDRD9 = 0;
  for(i=0;i<8;i++ )
  {
    CLR_CLK(); 	    	   
    touch_delay();
    SET_CLK();
    receive<<=1;
    if(CT_READ_SDA)receive++;   
  }	  				 
  if (!ack)CT_I2C_NAck();//·￠?ínACK
  else CT_I2C_Ack(); //·￠?íACK   
  return receive;
}




