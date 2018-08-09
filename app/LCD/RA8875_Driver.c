#include "include.h"

GPIO_InitTypeDef LCDIO_inittype;
void LCDIO_init(void)
{
//  LCDIO_inittype.GPIO_PTx = PTE;
//  LCDIO_inittype.GPIO_Pins = GPIO_Pin26 | GPIO_Pin27 | GPIO_Pin28  ;  
//  LCDIO_inittype.GPIO_Dir = DIR_OUTPUT;
//  LCDIO_inittype.GPIO_Output = OUTPUT_H; 
//  LPLD_GPIO_Init( LCDIO_inittype);
  
//  LCDIO_inittype.GPIO_PTx = PTA;
//  LCDIO_inittype.GPIO_Pins = GPIO_Pin6 | GPIO_Pin7;
//  LCDIO_inittype.GPIO_Dir = DIR_OUTPUT;
//  LCDIO_inittype.GPIO_Output = OUTPUT_H; 
//  LPLD_GPIO_Init( LCDIO_inittype);
  
  LCDIO_inittype.GPIO_PTx = PTC;
  LCDIO_inittype.GPIO_Pins = GPIO_Pin13 | GPIO_Pin14 | GPIO_Pin15 
                              | GPIO_Pin16 | GPIO_Pin17 | GPIO_Pin18 | GPIO_Pin19;
  LCDIO_inittype.GPIO_Dir = DIR_OUTPUT;
  LCDIO_inittype.GPIO_Output = OUTPUT_H;  
  LPLD_GPIO_Init( LCDIO_inittype);
  
  LCDIO_inittype.GPIO_PTx = PTD;
  LCDIO_inittype.GPIO_Pins = GPIO_Pin0_7;
  LCDIO_inittype.GPIO_Dir = DIR_OUTPUT;
  LCDIO_inittype.GPIO_Output = OUTPUT_H;  
  LPLD_GPIO_Init( LCDIO_inittype);
  
}

void LCD_Initializtion(void)
{
  LCDIO_init();	
  LPLD_LPTMR_DelayMs(10);;
  RA8875_PLL_ini();
  LCD_CmdWrite(0x10);  //SYSR   uint8_t[4:3]=00 256 color  uint8_t[2:1]=  00 8bit MPU interface
  LCD_DataWrite(0x0c);   // if 8bit MCU interface   and 65k color display  						    
  //LCD_DataWrite(0x0F); // if 16bit MCU interface   and 65k color display  
  

  
  //HSD050IDW1 setting
  //==============	Display Window	800x480 ==================	
  
  LCD_CmdWrite(0x04);  //PCLK inverse
  LCD_DataWrite(0x81);
  LPLD_LPTMR_DelayMs(1);;
  
  //Horizontal set
  LCD_CmdWrite(0x14); //HDWR//Horizontal Display Width Setting Bit[6:0]                      
  LCD_DataWrite(0x63);//Horizontal display width(pixels) = (HDWR + 1)*8                      
  LCD_CmdWrite(0x15);//Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)   
  LCD_DataWrite(0x00);//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]               
  LCD_CmdWrite(0x16); //HNDR//Horizontal Non-Display Period Bit[4:0]                         
  LCD_DataWrite(0x03);//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8                
  LCD_CmdWrite(0x17); //HSTR//HSYNC Start Position[4:0]                                      
  LCD_DataWrite(0x03);//HSYNC Start Position(PCLK) = (HSTR + 1)*8                            
  LCD_CmdWrite(0x18); //HPWR//HSYNC Polarity ,The period width of HSYNC.                     
  LCD_DataWrite(0x0B);//HSYNC Width [4:0]   HSYNC Pulse width(PCLK) = (HPWR + 1)*8    
  //Vertical set                             
  LCD_CmdWrite(0x19); //VDHR0 //Vertical Display Height Bit [7:0]                            
  LCD_DataWrite(0xdf);//Vertical pixels = VDHR + 1                                           
  LCD_CmdWrite(0x1a); //VDHR1 //Vertical Display Height Bit [8]                              
  LCD_DataWrite(0x01);//Vertical pixels = VDHR + 1                                           
  LCD_CmdWrite(0x1b); //VNDR0 //Vertical Non-Display Period Bit [7:0]                        
  LCD_DataWrite(0x20);//Vertical Non-Display area = (VNDR + 1)                               
  LCD_CmdWrite(0x1c); //VNDR1 //Vertical Non-Display Period Bit [8]                          
  LCD_DataWrite(0x00);//Vertical Non-Display area = (VNDR + 1)                               
  LCD_CmdWrite(0x1d); //VSTR0 //VSYNC Start Position[7:0]                                    
  LCD_DataWrite(0x16);//VSYNC Start Position(PCLK) = (VSTR + 1)                              
  LCD_CmdWrite(0x1e); //VSTR1 //VSYNC Start Position[8]                                      
  LCD_DataWrite(0x00);//VSYNC Start Position(PCLK) = (VSTR + 1)                              
  LCD_CmdWrite(0x1f); //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]                        
  LCD_DataWrite(0x01);//VSYNC Pulse Width(PCLK) = (VPWR + 1                               
  
  //Active window  set 
  //setting active window X
  LCD_CmdWrite(0x30); //Horizontal Start Point 0 of Active Window (HSAW0)
  LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [7:0]
  LCD_CmdWrite(0x31); //Horizontal Start Point 1 of Active Window (HSAW1)	   
  LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [9:8]
  LCD_CmdWrite(0x34); //Horizontal End Point 0 of Active Window (HEAW0)
  LCD_DataWrite(0x1F); //Horizontal End Point of Active Window [7:0]
  LCD_CmdWrite(0x35); //Horizontal End Point 1 of Active Window (HEAW1)	   
  LCD_DataWrite(0x03); //Horizontal End Point of Active Window [9:8]
  
  //setting active window Y
  LCD_CmdWrite(0x32); //Vertical Start Point 0 of Active Window (VSAW0)
  LCD_DataWrite(0x00); //Vertical Start Point of Active Window [7:0]
  LCD_CmdWrite(0x33); //Vertical Start Point 1 of Active Window (VSAW1)	   
  LCD_DataWrite(0x00); //Vertical Start Point of Active Window [8]
  LCD_CmdWrite(0x36); //Vertical End Point of Active Window 0 (VEAW0)
  LCD_DataWrite(0xdf); //Vertical End Point of Active Window [7:0]
  LCD_CmdWrite(0x37); //Vertical End Point of Active Window 1 (VEAW1)	   
  LCD_DataWrite(0x01); //Vertical End Point of Active Window [8]
  
  //backlight on for RAiO RA8875_demo_board_V2
  PWM1_enable();
  PWM1_fnuction_sel();
  PWM1_clock_ratio(0x05); //bit0~3     
  PWM1_duty_cycle(0x05); // 
   
}


/*******************************************************************************
* Function Name  : RA8875_PLL_ini
* Description    : Initialization RA8875 system clock
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void RA8875_PLL_ini(void)
{
  LCD_CmdWrite(0x88);       
  LCD_DataWrite(0x86);
  //LCD_DataWrite(0x14);
  LPLD_LPTMR_DelayMs(1);    
  LCD_CmdWrite(0x89);       
  LCD_DataWrite(0x0);  
  LPLD_LPTMR_DelayMs(1);

  Software_Reset();
  LPLD_LPTMR_DelayMs(5);;
}	



/*******************************************************************************
* Function Name  : Chk_Busy
* Description    : Check whether the Memory Read/Write is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_Busy(void)
{
  uint8_t temp; 	
  do
  {
    temp=LCD_StatusRead();
  }while((temp&0x80)==0x80);	   
}

/*******************************************************************************
* Function Name  : Chk_Busy_BTE
* Description    : Check whether the BTE is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_Busy_BTE(void)
{
  uint8_t temp;  	
  do
  {
    temp=LCD_StatusRead();
  }while((temp&0x40)==0x40);	   
}
/*******************************************************************************
* Function Name  : Chk_Busy_DIR_Access
* Description    : Check whether the DIR_Access is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_Busy_DIR_Access(void)
{
  uint8_t  temp;	
  do
  {
    temp=LCD_StatusRead();
  }while((temp&0x01)==0x01);	   
}

/*******************************************************************************
* Function Name  : Chk_DMA_Busy
* Description    : Check whether the DMA is busy
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Chk_DMA_Busy(void)
{
  uint8_t temp; 	
  do
  {
    LCD_CmdWrite(0xBF);
    temp = LCD_DataRead();
  }while((temp&0x01)==0x01);   
}

/*******************************************************************************
* Function Name  : Display_ON
* Description    : Display on
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/		 
void Display_ON(void)
{	
  LCD_CmdWrite(0x01);//PWRR
  LCD_DataWrite(0x80);
}
/*******************************************************************************
* Function Name  : Display_OFF
* Description    : Display OFF 
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Display_OFF(void)
{
  LCD_CmdWrite(0x01);//PWRR
  LCD_DataWrite(0x00);
}
/*******************************************************************************
* Function Name  : Normal_Mode_exitSleep
* Description    : Normal mode
* Input          : None
* Output         : None
* Return         : None
* Attention		   : 1. There are 3 ways to wake up from sleep mode:  
Touch Panel wake up, Key Scan wake up ,Software wake up. 
2. When using IIC interface, this function is not supported. 
*******************************************************************************/
void Normal_Mode_exitSleep(void)
{	
  LCD_CmdWrite(0x01);//PWRR
  LCD_DataWrite(0x00);
}
/*******************************************************************************
* Function Name  : Sleep_Mode
* Description    : Sleep mode. 
* Input          : None
* Output         : None
* Return         : None
* Attention		   : 1. There are 3 ways to wake up from sleep mode:  
Touch Panel wake up, Key Scan wake up ,Software wake up. 
2. When using IIC interface, this function is not supported. 
*******************************************************************************/
void Sleep_Mode(void)
{
  LCD_CmdWrite(0x01);//PWRR
  LCD_DataWrite(0x02);
}

/*******************************************************************************
* Function Name  : Software_Reset
* Description    : Software Reset. 
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Software_Reset(void)
{	
  LCD_CmdWrite(0x01);//PWRR
  LCD_DataWrite(0x01);
  LCD_DataWrite(0x00);
  LPLD_LPTMR_DelayMs(1); 
}					

/*******************************************************************************
* Function Name  : PCLK_inversion
* Description    : PDAT is fetched at PCLK falling edge.  
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void PCLK_inversion(void)
{ 	
  uint8_t temp;
  LCD_CmdWrite(0x04);//PWRR
  temp = LCD_DataRead();
  temp |= cSetD7;
  LCD_DataWrite(temp);
}

/*******************************************************************************
* Function Name  : PCLK_inversion
* Description    : PDAT is fetched at PCLK rising edge.  
* Input          : None
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void PCLK_non_inversion(void)
{ 	
  uint8_t temp;
  LCD_CmdWrite(0x04);//PWRR
  temp = LCD_DataRead();
  temp &= cClrD7;
  LCD_DataWrite(temp);
}

/*******************************************************************************
* Function Name  : PCLK_width
* Description    : PCLK Period Setting  (Pixel clock (PCLK) period setting. )
* Input          : setx:
00b: PCLK period = System Clock period. 
01b: PCLK period = 2 times of System Clock period. 
10b: PCLK period = 4 times of System Clock period. 
11b: PCLK period = 8 times of System Clock period. 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void PCLK_width(uint8_t setx) //uint8_t[1:0]
{ 	
  uint8_t temp;
  LCD_CmdWrite(0x04);//PWRR
  temp = LCD_DataRead();
  temp &=0x80;
  temp |= setx;
  LCD_DataWrite(temp);
}

/*******************************************************************************
* Function Name  : Serial_ROM_select0
* Description    : Serial Flash/ROM 0 I/F is selected. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Serial_ROM_select0(void)
{       
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp &=cClrD7;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : Serial_ROM_select1
* Description    : Serial Flash/ROM 1 I/F is selected.  
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Serial_ROM_select1(void)
{       
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp |=cSetD7;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : Serial_ROM_Address_set_24bit
* Description    : 24 bits address mode    
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Serial_ROM_Address_set_24bit(void)
{       
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp &=cClrD6;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : Serial_ROM_Address_set_32bit
* Description    : 32 bits address mode    
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Serial_ROM_Address_set_32bit(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp |=cSetD6;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : Select_Serial_Waveform_mode0
* Description    : Mode 0.   
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Select_Serial_Waveform_mode0(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp &=cClrD5;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : Select_Serial_Waveform_mode3
* Description    : Mode 3.   
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Select_Serial_Waveform_mode3(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp |=cSetD5;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Read_Cycle_4bus
* Description    : 4 bus -> no dummy cycle   
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Read_Cycle_4bus(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp &=0xE7;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Read_Cycle_5bus
* Description    : 5 bus -> no dummy cycle   
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Read_Cycle_5bus(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x05);//PWRR
  temp = LCD_DataRead();
  temp &=0xE7;
  temp |=cSetD3;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Read_Cycle_6bus
* Description    : 6 bus -> no dummy cycle   
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Read_Cycle_6bus(void)
{   uint8_t temp;
LCD_CmdWrite(0x05);//PWRR
temp = LCD_DataRead();
temp &=0xE7;
temp |=cSetD4;
LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Font_mode
* Description    : Font mode     
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Font_mode(void)
{   uint8_t temp;
LCD_CmdWrite(0x05);//PWRR
temp = LCD_DataRead();
temp &=cClrD2;
LCD_DataWrite(temp);
}


/*******************************************************************************
* Function Name  : SERIAL_ROM_DMA_mode
* Description    : DMA mode     
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_DMA_mode(void)
{   uint8_t temp;
LCD_CmdWrite(0x05);//PWRR
temp = LCD_DataRead();
temp |=cSetD2;
LCD_DataWrite(temp);
}

/*******************************************************************************
* Function Name  : SERIAL_ROM_Signal_mode
* Description    : Single Mode     
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Signal_mode(void)
{   uint8_t temp;
LCD_CmdWrite(0x05);//PWRR
temp = LCD_DataRead();
temp &=0xFC;
LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Dual_mode0
* Description    : Dual Mode 0     
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/

void SERIAL_ROM_Dual_mode0(void)
{   uint8_t temp;
LCD_CmdWrite(0x05);//PWRR
temp = LCD_DataRead();
temp &=0xFC;
temp |=cSetD1;
LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : SERIAL_ROM_Dual_mode1
* Description    : Dual Mode 1     
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SERIAL_ROM_Dual_mode1(void)
{   uint8_t temp;
LCD_CmdWrite(0x05);//PWRR
temp = LCD_DataRead();
temp &=0xFC;
temp |=cSetD1;
temp |=cSetD0;
LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : SROM_CLK_DIV
* Description    : Serial Flash/ROM Clock Frequency Setting   
* Input          : CLK_DIV ：Serial Flash/ROM Clock Frequency Setting 
*									0xb: SFCL frequency = System clock frequency 
*											 (When DMA enable and Color depth = 256 color 
*											  SFCL frequency = System clock frequency /2) 
*									10b: SFCL frequency = System clock frequency / 2 
*									11b: SFCL frequency = System clock frequency / 4 	
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void SROM_CLK_DIV(uint8_t CLK_DIV)
{
  LCD_CmdWrite(0x06);
  LCD_DataWrite(CLK_DIV);
}


/*******************************************************************************
* Function Name  : Color_256
* Description    : Color Depth Setting ，8-bpp generic TFT, i.e. 256 colors  
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Color_256(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x10);//SYSR
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  LCD_DataWrite(temp);
} 
/*******************************************************************************
* Function Name  : Color_65K
* Description    : Color Depth Setting ，16-bpp generic TFT, i.e. 65K colors.  
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Color_65K(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x10);//SYSR
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  temp |= cSetD3ClrD2 ;
  LCD_CmdWrite(0x10);//SYSR
  LCD_DataWrite(temp);
}

/*******************************************************************************
* Function Name  : MPU_8bit_Interface
* Description    : MCUIF Selection ， 8-bit MCU Interface. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void MPU_8bit_Interface(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x10);//SYSR
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : MPU_16bit_Interface
* Description    : MCUIF Selection ， 16-bit MCU Interface. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void MPU_16bit_Interface(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x10);//SYSR
  temp = LCD_DataRead();
  temp |= cSetD1ClrD0 ;
  LCD_DataWrite(temp);
} 								 
/*******************************************************************************
* Function Name  : GPI_data
* Description    : General Purpose Input. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : KEY_EN : REG[C0h] bit 7 
*******************************************************************************/
uint8_t GPI_data(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x12);//SYSR
  temp = LCD_DataRead();
  return temp;
}
/*******************************************************************************
* Function Name  : GPO_data
* Description    : General Purpose Output  
* Input          : setx ：GPO[3:0] : General Purpose Output 
* Output         : None
* Return         : None
* Attention		   : KEY_EN : REG[C0h] bit 7 
*******************************************************************************/
void GPO_data(uint8_t setx)
{
  LCD_CmdWrite(0x13); 
  LCD_DataWrite(setx);
}

/*******************************************************************************
* Function Name  : One_Layer
* Description    : Layer Setting Control ，One layer configuration is selected.  
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void One_Layer(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x20);//DPCR
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);
}	
/*******************************************************************************
* Function Name  : Two_Layers
* Description    : Layer Setting Control ，Two layers configuration is selected.. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/			 
void Two_Layers(void)
{	
  uint8_t temp;
LCD_CmdWrite(0x20);//DPCR
temp = LCD_DataRead();
temp |= cSetD7 ;
LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : HDIR_SEG0_SEGn
* Description    : Horizontal Scan Direction, for n = SEG number. SEG0 to SEG(n-1). 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/		
void HDIR_SEG0_SEGn(void)
{	uint8_t temp;
LCD_CmdWrite(0x20);//DPCR
temp = LCD_DataRead();
temp &= cClrD3 ;
LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : HDIR_SEGn_SEG0
* Description    : Horizontal Scan Direction, for n = SEG number. SEG(n-1) to SEG0. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/		
void HDIR_SEGn_SEG0(void)
{
  uint8_t temp;
  
  LCD_CmdWrite(0x20);//DPCR
  temp = LCD_DataRead();
  temp |= cSetD3 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : VDIR_COM0_COMn
* Description    : Vertical Scan direction, for n = COM numbe ：COM0 to COM(n-1) 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void VDIR_COM0_COMn(void)
{
  uint8_t temp;
  
  LCD_CmdWrite(0x20);//DPCR
  temp = LCD_DataRead();
  temp &= cClrD2 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : VDIR_COMn_COM0
* Description    : Vertical Scan direction, for n = COM numbe ：COM(n-1) to COM0 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void VDIR_COMn_COM0(void)
{
  uint8_t temp;
  
  LCD_CmdWrite(0x20);//DPCR
  temp = LCD_DataRead();
  temp |= cSetD2 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : CGROM_Font
* Description    : CGRAM/CGROM Font Selection Bit in Text Mode ，CGROM font is selected. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   :  The bit is used to select the bit-map source when text-
mode is active(REG[40h] bit 7 is 1), when CGRAM is 
writing(REG[41h] bit 3-2 =01b), the bit  must be set as “0”.
*******************************************************************************/
void CGROM_Font(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : CGROM_Font
* Description    : CGRAM/CGROM Font Selection Bit in Text Mode ，CGRAM font is selected. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   :  The bit is used to select the bit-map source when text-
mode is active(REG[40h] bit 7 is 1), when CGRAM is 
writing(REG[41h] bit 3-2 =01b), the bit  must be set as “0”.
*******************************************************************************/
void CGRAM_Font(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : Internal_CGROM
* Description    : External/Internal CGROM Selection Bit ，
Internal CGROM is selected.(REG[2Fh] must be set 00h ) 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/

void Internal_CGROM(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp &= cClrD5 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : External_CGROM
* Description    : External/Internal CGROM Selection Bit ，
External CGROM is selected. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void External_CGROM(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp |= cSetD5 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : ISO8859_1
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
8x16 character sets with the standard coding of ISO/IEC 8859-
1~4, which supports English and most of European country
languages.  

Selection ISO/IEC 8859-1. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_1(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : ISO8859_2
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
8x16 character sets with the standard coding of ISO/IEC 8859-
1~4, which supports English and most of European country
languages.  

Selection ISO/IEC 8859-2.
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_2(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  temp |= cClrD1SetD0 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : ISO8859_3
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
8x16 character sets with the standard coding of ISO/IEC 8859-
1~4, which supports English and most of European country
languages.  

Selection ISO/IEC 8859-3. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_3(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  temp |= cSetD1ClrD0 ;
  LCD_DataWrite(temp);
}
/*******************************************************************************
* Function Name  : ISO8859_4
* Description    :  When FNCR0 B7 = 0 and B5 = 0, Internal CGROM supports the
8x16 character sets with the standard coding of ISO/IEC 8859-
1~4, which supports English and most of European country
languages.  

Selection ISO/IEC 8859-4. 
* Input          : None 
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void ISO8859_4(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x21);//FNCR0
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  temp |= cSetD1D0 ;
  LCD_DataWrite(temp);
}								 
//--------------------------------//
//REG[22h]

void No_FullAlignment(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);
}
void FullAlignment(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);
}
void Font_with_BackgroundColor(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD6 ;
  LCD_DataWrite(temp);
}
void Font_with_BackgroundTransparency(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp |= cSetD6 ;
  LCD_DataWrite(temp);
}


void NoRotate_Font(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD4 ;
  LCD_DataWrite(temp);
}
void Rotate90_Font(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp |= cSetD4 ;
  LCD_DataWrite(temp);
}


void Horizontal_FontEnlarge_x1(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  LCD_DataWrite(temp);
}
void Horizontal_FontEnlarge_x2(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  temp |= cClrD3SetD2 ;
  LCD_DataWrite(temp);
}
void Horizontal_FontEnlarge_x3(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  temp |= cSetD3ClrD2 ;
  LCD_DataWrite(temp);
}
void Horizontal_FontEnlarge_x4(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  temp |= cSetD3D2 ;
  LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x1(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x2(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  temp |= cClrD1SetD0 ;
  LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x3(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  temp |= cSetD1ClrD0 ;
  LCD_DataWrite(temp);
}
void Vertical_FontEnlarge_x4(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x22);//FNCR1
  temp = LCD_DataRead();
  temp &= cClrD1D0 ;
  temp |= cSetD1D0 ;
  LCD_DataWrite(temp);
}

//-------------------------------------------//
//REG[23h]									 
void CGRAM_Select_Number(uint8_t setx)
{ 
  LCD_CmdWrite(0x23);//CGSR
  LCD_DataWrite(setx);
}	

//-------------------------------------------//
//REG[24h]REG[25h]REG[26h]REG[27h]
void Scroll_Offset(uint16_t X,uint16_t Y)
{
  
  LCD_CmdWrite(0x24);//HOFS0
  LCD_DataWrite(X);
  
  LCD_CmdWrite(0x25);//HOFS1	   
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0x26);//VOFS0
  LCD_DataWrite(Y);  
  
  LCD_CmdWrite(0x27);//VOFS1	   
  LCD_DataWrite(Y>>8); 
}	 
//-------------------------------------------//
//REG[29h]
void Line_distance(uint8_t setx)
{ 
  LCD_CmdWrite(0x29);//LDS
  LCD_DataWrite(setx);
}	  
//-------------------------------------------//
//REG[2Ah]REG[2Bh]REG[2Ch]REG[2Dh]
void Font_Coordinate(uint16_t X,uint16_t Y)
{
  
  LCD_CmdWrite(0x2A);//HOFS0
  LCD_DataWrite(X);
  
  LCD_CmdWrite(0x2B);//HOFS1	   
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0x2C);//VOFS0
  LCD_DataWrite(Y);
  
  LCD_CmdWrite(0x2D);//VOFS1	   
  LCD_DataWrite(Y>>8); 
}


//-------------------------------------------//
//REG[2Eh]
void Font_size_16x16_8x16(void) 
{
  uint8_t temp;
  LCD_CmdWrite(0x2E);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x3f;
  LCD_DataWrite(temp);
}

void Font_size_24x24_12x24(void) 
{
  uint8_t temp;
  LCD_CmdWrite(0x2E);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x3f;
  temp |= 0x40; 
  LCD_DataWrite(temp);
}

void Font_size_32x32_16x32(void) 
{
  uint8_t temp;
  LCD_CmdWrite(0x2E);//FNCR1
  temp = LCD_DataRead();
  temp &= 0x3f;
  temp |= 0x80; 
  LCD_DataWrite(temp);
}


void Font_spacing_set(uint8_t setx) //uint8_t[5:0]
{   uint8_t temp,temp1;
temp1=setx&0x3F;
LCD_CmdWrite(0x2E);//FNCR1
temp = LCD_DataRead();
temp &= 0xc0;
temp |= temp1; 
LCD_DataWrite(temp);

}

//-------------------------------------------//
//REG[2Fh]
void GT_serial_ROM_select_GT21L16T1W(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0x1f;
LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L16U2W(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0x1f;
temp |= 0x20;
LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L24T3Y(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0x1f;
temp |= 0x40;
LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L24M1Z(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0x1f;
temp |= 0x60;
LCD_DataWrite(temp);
}

void GT_serial_ROM_select_GT23L32S4W(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0x1f;
temp |= 0x80;
LCD_DataWrite(temp);
}

void Font_code_GB2312(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
LCD_DataWrite(temp);
}

void Font_code_GB12345(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
temp |= 0x04;
LCD_DataWrite(temp);
}

void Font_code_BIG5(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
temp |= 0x08;
LCD_DataWrite(temp);
}

void Font_code_UNICODE(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
temp |= 0x0C;
LCD_DataWrite(temp);
}

void Font_code_ASCII(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
temp |= 0x10;
LCD_DataWrite(temp);
}

void Font_code_UNIJIS(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
temp |= 0x14;
LCD_DataWrite(temp);
}

void Font_code_JIS0208(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
temp |= 0x18;
LCD_DataWrite(temp);
}

void Font_code_LATIN(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xE3;
temp |= 0x1C;
LCD_DataWrite(temp);
}

void Font_Standard(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xFC;
LCD_DataWrite(temp);
}

void Font_Arial(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xFC;
temp |= 0x01;
LCD_DataWrite(temp);
}

void Font_Roman(void)
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= 0xFC;
temp |= 0x02;
LCD_DataWrite(temp);
}

void Font_Bold(void) //for ASCII
{ uint8_t temp;
LCD_CmdWrite(0x2F);//FNCR1
temp = LCD_DataRead();
temp &= cClrD1D0;
temp |= cSetD1D0;
LCD_DataWrite(temp);
}

//-------------------------------------------//
//REG[30h]~REG[37h]
void Active_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{
  //setting active window X
  
  LCD_CmdWrite(0x30);//HSAW0
  LCD_DataWrite(XL); 
  LCD_CmdWrite(0x31);//HSAW1	   
  LCD_DataWrite(XL>>8);
  
  LCD_CmdWrite(0x34);//HEAW0
  LCD_DataWrite(XR);
  LCD_CmdWrite(0x35);//HEAW1	   
  LCD_DataWrite(XR>>8);
  
  //setting active window Y
  
  LCD_CmdWrite(0x32);//VSAW0
  LCD_DataWrite(YT);  
  LCD_CmdWrite(0x33);//VSAW1	   
  LCD_DataWrite(YT>>8);
  
  LCD_CmdWrite(0x36);//VEAW0
  LCD_DataWrite(YB); 
  LCD_CmdWrite(0x37);//VEAW1	   
  LCD_DataWrite(YB>>8);
}
//--------------------------------------------//
//REG[38h]~REG[3Fh]

void Scroll_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{
  
  LCD_CmdWrite(0x38);//HSSW0
  LCD_DataWrite(XL);
  LCD_CmdWrite(0x39);//HSSW1	   
  LCD_DataWrite(XL>>8);
  
  LCD_CmdWrite(0x3c);//HESW0
  LCD_DataWrite(XR);  
  LCD_CmdWrite(0x3d);//HESW1	   
  LCD_DataWrite(XR>>8);   
  
  LCD_CmdWrite(0x3a);//VSSW0
  LCD_DataWrite(YT);
  LCD_CmdWrite(0x3b);//VSSW1	   
  LCD_DataWrite(YT>>8);
  
  LCD_CmdWrite(0x3e);//VESW0
  LCD_DataWrite(YB);  
  LCD_CmdWrite(0x3f);//VESW1	   
  LCD_DataWrite(YB>>8);
}  


//--------------------------------------------//
//REG[40h]
void Graphic_Mode(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);
}

void Text_Mode(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);	 
} 

void Text_Cursor_Disable(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD6 ;
  LCD_DataWrite(temp);
}

void Text_Cursor_Enable(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp |= cSetD6 ;
  LCD_DataWrite(temp);	 	
} 

void Text_Cursor_Blink_Disable(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD5 ;
  LCD_DataWrite(temp);
}

void Text_Cursor_Blink_Enable(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp |= cSetD5 ;
  LCD_DataWrite(temp);
}

void Memory_Write_LeftRight_TopDown(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  LCD_DataWrite(temp);
}

void Memory_Write_RightLeft_TopDown(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  temp |= cClrD3SetD2 ;
  LCD_DataWrite(temp);
}

void Memory_Write_DownTop_LeftRight(void)
{	
  uint8_t temp;	
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  temp |= cSetD3D2 ;
  LCD_DataWrite(temp);
}

void Memory_Write_TopDown_LeftRight(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  temp |= cSetD3ClrD2 ;
  LCD_DataWrite(temp);
} 

void MemoryWrite_Cursor_autoIncrease(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD1 ;
  LCD_DataWrite(temp);
}

void MemoryWrite_Cursor_NoautoIncrease(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp |= cSetD1 ;
  LCD_DataWrite(temp);
}

void MemoryRead_Cursor_autoIncrease(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp &= cClrD0 ;
  LCD_DataWrite(temp);
}

void MemoryRead_Cursor_NoautoIncrease(void)
{
  uint8_t temp;
  
  LCD_CmdWrite(0x40);//MWCR0
  temp = LCD_DataRead();
  temp |= cSetD0 ;
  LCD_DataWrite(temp);
}  										 

//--------------------------------------------//
//REG[41h]
void No_Graphic_Cursor(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set1(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set2(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4 ;
  temp |= cClrD6D5SetD4 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set3(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4 ;
  temp |= cClrD6SetD5ClrD4 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set4(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4 ;
  temp |= cClrD6SetD5D4 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set5(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4 ;
  temp |= cSetD6ClrD5D4 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set6(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4 ;
  temp |= cSetD6ClrD5SetD4 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set7(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4 ;
  temp |= cSetD6D5ClrD4 ;
  LCD_DataWrite(temp);
}

void Graphic_Cursor_Set8(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD6D5D4 ;
  temp |= cSetD6D5D4 ;
  LCD_DataWrite(temp);
}

void Write_To_Bank1and2(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD3D2 ;
  LCD_DataWrite(temp);
}

void Write_To_CGRAM(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= 0xf3;
  temp |= cClrD3SetD2 ;
  LCD_DataWrite(temp);
}

void Write_To_GraphicCursor(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= 0xf3;
  temp |= cSetD3ClrD2 ;
  LCD_DataWrite(temp);
}

void Write_To_Pattern(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= 0xf3;
  temp |= cSetD3D2 ;
  LCD_DataWrite(temp);
}

void Write_To_Bank1(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp &= cClrD0 ;
  LCD_DataWrite(temp);
}

void Write_To_Bank2(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x41);//MWCR1
  temp = LCD_DataRead();
  temp |= cSetD0 ;
  LCD_DataWrite(temp);  
}	

//--------------------------------------------//
//--------------------------------------------//
//REG[44h]
void Text_Blink_Time(uint8_t setx)
{	
  LCD_CmdWrite(0x44);//CURS
  LCD_DataWrite(setx);
}

//--------------------------------------------//
//REG[45h]  
void Memory_read_LeftRight_TopDown(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x45);//MRCD
  temp = LCD_DataRead();
  temp &= cClrD1D0;
  LCD_DataWrite(temp);
}
void Memory_read_RightLeft_TopDown(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x45);//MRCD
  temp = LCD_DataRead();
  temp |= cClrD1SetD0;
  LCD_DataWrite(temp);
}
void Memory_read_TopDown_LeftRight(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x45);//MRCD
  temp = LCD_DataRead();
  temp |= cSetD1ClrD0;
  LCD_DataWrite(temp);
}
void Memory_read_DownTop_LeftRight(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x45);//MRCD
  temp = LCD_DataRead();
  temp |= cSetD1D0;
  LCD_DataWrite(temp);
}			

//--------------------------------------------//
//REG[46h]~REG[49h]
void XY_Coordinate(uint16_t X,uint16_t Y)
{
  LCD_CmdWrite(0x46);
  LCD_DataWrite(X);  
  LCD_CmdWrite(0x47);	   
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0x48);
  LCD_DataWrite(Y);  
  LCD_CmdWrite(0x49);	   
  LCD_DataWrite(Y>>8);
}



//--------------------------------------------//
//REG[4Ah]~REG[4Dh]
void Memory_read_Coordinate(uint16_t X,uint16_t Y)
{
  
  LCD_CmdWrite(0x4a);
  LCD_DataWrite(X);   
  LCD_CmdWrite(0x4b);	   
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0x4c);
  LCD_DataWrite(Y);
  LCD_CmdWrite(0x4d);	   
  LCD_DataWrite(Y>>8);
} 

//--------------------------------------------//
//REG[4Eh]
void Text_Cursor_Horizontal_Size(uint8_t setx)//uint8_t[3:0]
{
  LCD_CmdWrite(0x4E);//CURS	   
  LCD_DataWrite(setx);
} 

//REG[4Fh] 
void Text_Cursor_Vertical_Size(uint8_t setx)//uint8_t[3:0]
{
  LCD_CmdWrite(0x4F);//CURS	   
  LCD_DataWrite(setx);
} 	

//--------------------------------------------//
//REG[50h] 
void no_BTE_write(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x50);//BECR0
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);  
}

void BTE_enable(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x50);//BECR0
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);  
}

void BTE_contiguous_Data(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x50);//BECR0
  temp = LCD_DataRead();
  temp |= cSetD6 ;
  LCD_DataWrite(temp);  
}

void BTE_rectangular_Data(void)
{	
  uint8_t temp;												   
  LCD_CmdWrite(0x50);//BECR0
  temp = LCD_DataRead();
  temp &= cClrD6 ;
  LCD_DataWrite(temp);  
}									  

//---------------------------------------------//
//REG[51h] 
void BTE_ROP_Code(uint8_t setx)
{	 
  LCD_CmdWrite(0x51);//BECR1	   
  LCD_DataWrite(setx); 
}									   

//---------------------------------------------//
//REG[52h] 
void Layer1_Visible(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0xf8;
  LCD_DataWrite(temp);  
}

void Layer2_Visible(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0xf8;
  temp|=0x01;
  LCD_DataWrite(temp);  
}	

void Transparent_Mode(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0xf8;
  temp|=0x03;
  LCD_DataWrite(temp);  
}

void Lighten_Overlay_Mode(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0xf8;
  temp|=0x02;
  LCD_DataWrite(temp);  
}	

void Boolean_OR(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0xf8;
  temp|=0x04;
  LCD_DataWrite(temp);
}

void Boolean_AND(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0xf8;
  temp|=0x05;
  LCD_DataWrite(temp);  
}  	 


void Floating_window_mode(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0xf8;
  temp|=0x06;
  LCD_DataWrite(temp);  
} 

void Floating_Window_transparent_with_BGTR_enable(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp|=cSetD5;
  LCD_DataWrite(temp);  
}

void Floating_Window_transparent_with_BGTR_disable(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=cClrD5;
  LCD_DataWrite(temp);  
}


void Layer1_2_scroll(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0x3f;
  LCD_DataWrite(temp);  
}  	 

void Layer1_scroll(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0x3f;
  temp|=0x40;
  LCD_DataWrite(temp);  
} 

void Layer2_scroll(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0x3f;
  temp|=0x80;
  LCD_DataWrite(temp);  
} 

void Buffer_scroll(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x52);//LTPR0
  temp = LCD_DataRead();
  temp&=0x3f;
  temp|=0xC0;
  LCD_DataWrite(temp);  
} 

//---------------------------------------------//
//REG[53h] 
void layer2_1_transparency(uint8_t setx)
{  
  LCD_CmdWrite(0x53);//LTPR1
  LCD_DataWrite(setx); 
}

//---------------------------------------------//
//REG[54h]~ [5Fh]
void BTE_Source_Destination	(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{
  uint8_t temp,temp1;
  
  temp=XL;   
  LCD_CmdWrite(0x54);//HSBE0
  LCD_DataWrite(temp);
  temp=XL>>8;   
  LCD_CmdWrite(0x55);//HSBE1	   
  LCD_DataWrite(temp);
  
  temp=XR;   
  LCD_CmdWrite(0x58);//HDBE0
  LCD_DataWrite(temp);
  temp=XR>>8;   
  LCD_CmdWrite(0x59);//HDBE1	   
  LCD_DataWrite(temp); 
  
  temp=YT;   
  LCD_CmdWrite(0x56);//VSBE0
  LCD_DataWrite(temp);
  temp=YT>>8;   
  LCD_CmdWrite(0x57);//VSBE1
  temp1 = LCD_DataRead();
  temp1 &= 0x80;
  temp=temp|temp1; 
  LCD_CmdWrite(0x57);//VSBE1  
  LCD_DataWrite(temp);
  
  
  temp=YB;   
  LCD_CmdWrite(0x5a);//VDBE0
  LCD_DataWrite(temp);
  temp=YB>>8;   
  LCD_CmdWrite(0x5b);//VDBE1
  temp1 = LCD_DataRead();
  temp1 &= 0x80;
  temp=temp|temp1;	
  LCD_CmdWrite(0x5b);//VDBE1   
  LCD_DataWrite(temp);
}							

void Source_Layer1(void)
{   
  uint8_t temp;	
  LCD_CmdWrite(0x57);//VSBE1
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);
}

void Source_Layer2(void)
{	
  uint8_t temp;	
  LCD_CmdWrite(0x57);//VSBE1
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);
}

void Destination_Layer1(void)
{	
  uint8_t temp;	
  LCD_CmdWrite(0x5b);//VDBE1
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);
}

void Destination_Layer2(void)
{	
  uint8_t temp;	
  LCD_CmdWrite(0x5b);//VDBE1
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);
}

//---------------------------------------------//
//---------------------------------------------//
void BTE_Size_setting(uint16_t X,uint16_t Y)
{	 
  LCD_CmdWrite(0x5c);//BEWR0
  LCD_DataWrite(X); 
  LCD_CmdWrite(0x5d);//BEWR1	   
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0x5e);//BEHR0
  LCD_DataWrite(Y);   
  LCD_CmdWrite(0x5f);//BEHR1	   
  LCD_DataWrite(Y>>8);
}									 

//---------------------------------------------//
//REG[60h]~REG[67h]

void Background_color(uint16_t color)
{
#ifdef Color65k
  LCD_CmdWrite(0x60);
  LCD_DataWrite((color&0xf800)>>11);
  
  LCD_CmdWrite(0x61);
  LCD_DataWrite((color&0x07e0)>>5);
  
  LCD_CmdWrite(0x62);
  LCD_DataWrite((color&0x001f));
#endif
  
#ifdef Color256
  LCD_CmdWrite(0x60);
  LCD_DataWrite((color&0xf800)>>13);
  
  LCD_CmdWrite(0x61);
  LCD_DataWrite((color&0x07e0)>>8);
  
  LCD_CmdWrite(0x62);
  LCD_DataWrite((color&0x001f)>>3);
#endif
}

void Text_color(uint16_t color) 
{
#ifdef Color65k
  LCD_CmdWrite(0x63);
  LCD_DataWrite((color&0xf800)>>11);
  LCD_CmdWrite(0x64);
  LCD_DataWrite((color&0x07e0)>>5);
  LCD_CmdWrite(0x65);
  LCD_DataWrite((color&0x001f));
#endif
  
#ifdef Color256
  LCD_CmdWrite(0x63);
  LCD_DataWrite((color&0xf800)>>13);
  
  LCD_CmdWrite(0x64);
  LCD_DataWrite((color&0x07e0)>>8);
  
  LCD_CmdWrite(0x65);
  LCD_DataWrite((color&0x001f)>>3);
#endif
  
}

//--------------------------------------------//
void Text_Background_Color(uint8_t setR,uint8_t setG,uint8_t setB)
{
  LCD_CmdWrite(0x60);//BGCR0
  LCD_DataWrite(setR);
  
  LCD_CmdWrite(0x61);//BGCR0
  LCD_DataWrite(setG);
  
  LCD_CmdWrite(0x62);//BGCR0
  LCD_DataWrite(setB);
} 

void Text_Foreground_Color(uint8_t setR,uint8_t setG,uint8_t setB)
{	    
  LCD_CmdWrite(0x63);//BGCR0
  LCD_DataWrite(setR);
  
  LCD_CmdWrite(0x64);//BGCR0
  LCD_DataWrite(setG);
  
  LCD_CmdWrite(0x65);//BGCR0
  LCD_DataWrite(setB);
  
}


void BTE_Background_color(uint8_t setR,uint8_t setG,uint8_t setB)
{
  LCD_CmdWrite(0x60);//BGCR0
  LCD_DataWrite(setR);
  LCD_CmdWrite(0x61);//BGCR0
  LCD_DataWrite(setG);
  LCD_CmdWrite(0x62);//BGCR0
  LCD_DataWrite(setB);
}


void BTE_Foreground_color(uint8_t setR,uint8_t setG,uint8_t setB)
{
  LCD_CmdWrite(0x63);//BGCR0
  LCD_DataWrite(setR);
  LCD_CmdWrite(0x64);//BGCR0
  LCD_DataWrite(setG);
  LCD_CmdWrite(0x65);//BGCR0
  LCD_DataWrite(setB);
}


//======================================
//for test
void BTE_Background_red(uint8_t setx)
{	  
  LCD_CmdWrite(0x60);//BGCR0
  LCD_DataWrite(setx);
}	

void BTE_Background_green(uint8_t setx)
{	  
  LCD_CmdWrite(0x61);//BGCR1
  LCD_DataWrite(setx);
}							  

void BTE_Background_blue(uint8_t setx)
{	 
  LCD_CmdWrite(0x62);//BGCR2
  LCD_DataWrite(setx);
} 								

void BTE_Foreground_red(uint8_t setx)
{	
  LCD_CmdWrite(0x63);//FGCR0
  LCD_DataWrite(setx);
}								 

void BTE_Foreground_green(uint8_t setx)
{	  
  LCD_CmdWrite(0x64);//FGCR1
  LCD_DataWrite(setx);
}							 

void BTE_Foreground_blue(uint8_t setx)
{  
  LCD_CmdWrite(0x65);//FGCR2
  LCD_DataWrite(setx);
} 	

//======================================

void Pattern_Set_8x8(void)
{  
  uint8_t temp;
  
  LCD_CmdWrite(0x66);//PTNO
  temp = LCD_DataRead();
  temp &= cClrD7;
  LCD_DataWrite(temp);
}	

void Pattern_Set_16x16(void)
{  
  uint8_t  temp;
  LCD_CmdWrite(0x66);//PTNO
  temp = LCD_DataRead();
  temp |= cSetD7; 
  LCD_DataWrite(temp);
}								


void Pattern_Set_number(uint8_t setx)
{   
  uint8_t temp;    
  LCD_CmdWrite(0x66);//PTNO
  temp = LCD_DataRead();
  temp &= 0x80;    
  LCD_DataWrite(temp|setx);
} 	

void BackgroundColor_TransparentMode(uint8_t setR,uint8_t setG,uint8_t setB)
{
  LCD_CmdWrite(0x67);//BGTR_R
  LCD_DataWrite(setR);
  
  LCD_CmdWrite(0x68);//BGTR_G
  LCD_DataWrite(setG);
  
  LCD_CmdWrite(0x69);//BGTR_B
  LCD_DataWrite(setB);
}	  

//REG[70h]~REG[74h]
//==============================================================================
//Subroutine:	Enable_TP 
//==============================================================================
void Enable_TP(void)
{   
  uint8_t temp;	  
  LCD_CmdWrite(0x70);//TPCR0	
  temp = LCD_DataRead();
  temp |= cSetD7;   
  LCD_DataWrite(temp);
}
//==============================================================================
//Subroutine:	Disable_TP 
//==============================================================================
void Disable_TP(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0x70);//TPCR0
  temp = LCD_DataRead();
  temp &= cClrD7;   
  LCD_DataWrite(temp);
}


//==============================================================================
//Subroutine:	Disable_Touch_WakeUp
//==============================================================================
void Disable_Touch_WakeUp(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x70);//TPCR0	
  temp = LCD_DataRead();
  temp &= cClrD3;
  LCD_DataWrite(temp);
}


//==============================================================================
//Subroutine:	Disable_Touch_WakeUp
//==============================================================================
void Enable_Touch_WakeUp(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x70);//TPCR0	
  temp = LCD_DataRead();
  temp &= cClrD3;
  LCD_DataWrite(temp);
}

//==============================================================================
//Subroutine:	TP manual or auto  mode enable
//==============================================================================
void TP_manual_mode(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x71);//TPCR1	
  temp = LCD_DataRead();
  temp |= cSetD6;
  LCD_DataWrite(temp);
}
void TP_auto_mode(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x71);//TPCR1	
  temp = LCD_DataRead();
  temp &= cClrD6;
  temp |= cSetD2;
  /********************/
  //temp |= 0x04;
  //temp |= 0x24;
  LCD_DataWrite(temp);
}
//==============================================================================
//Subroutine:	TP_IDLE_mode
//==============================================================================
void TP_IDLE_mode(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xf0;
  LCD_DataWrite(temp);
}
//==============================================================================
//Subroutine:	TP_event_mode
//==============================================================================
void TP_event_mode(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xf0;
  temp |= 0x01;
  LCD_DataWrite(temp);
  //  LCD_DataWrite(0xc1);
}
//==============================================================================
//Subroutine:	TP_latch_X
//==============================================================================
void TP_latch_X(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xe0;
  temp |= 0x02;
  LCD_DataWrite(temp);
}
//==============================================================================
//Subroutine:	TP_latch_Y
//==============================================================================
void TP_latch_Y(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0x71);//TPCR1
  temp=LCD_DataRead(); 
  temp &= 0xe0;
  temp |= 0x03;
  LCD_DataWrite(temp);
}


// void TP_LDLE(void)
// {
//     uint8_t temp;
//     LCD_CmdWrite(0x71);//TPCR1
//     temp=LCD_DataRead(); 
//     temp &= 0xc0;
//     LCD_DataWrite(temp);
// }
//==============================================================================
//Subroutine:	Detect_TP_X_Y coordinate 
//==============================================================================
uint8_t ADC_X(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x72);//TPXH	 X_coordinate high byte
  //Chk_Busy();
  temp=LCD_DataRead();
  return temp;
}

uint8_t ADC_Y(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x73);//TPYH	  Y_coordinate high byte
  //Chk_Busy();
  temp=LCD_DataRead();
  return temp;
}

uint8_t ADC_XY(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0x74);//TPXYL	  uint8_t[3:2] Y_coordinate low byte  uint8_t[1:0] X_coordinate low byte 
  temp=LCD_DataRead();
  return temp;
}   

//REG[80h]~REG[83h]
void Graphic_Cursor_Coordinate(uint16_t X,uint16_t Y)
{
  LCD_CmdWrite(0x80);
  LCD_DataWrite(X);  
  LCD_CmdWrite(0x81);	   
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0x82);
  LCD_DataWrite(Y);  
  LCD_CmdWrite(0x83);	   
  LCD_DataWrite(Y>>8);
}

//---------------------------------//
//REG[84h]

void Graphic_Cursor_Color_0(uint8_t setx)
{	  
  LCD_CmdWrite(0x84);//GCC0
  LCD_DataWrite(setx); 
}  									  

void Graphic_Cursor_Color_1(uint8_t setx)
{	 
  LCD_CmdWrite(0x85);//GCC1
  LCD_DataWrite(setx); 
}  	

//---------------------------------------------//
//REG[8A]
void PWM1_enable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8a);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);  
}

void PWM1_disable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8a);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);  
}

void PWM1_disable_level_low(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8a);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD6 ;
  LCD_DataWrite(temp);  
}

void PWM1_disable_level_high(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8a);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD6 ;
  LCD_DataWrite(temp);  
}

void PWM1_fnuction_sel(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8a);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD4 ;
  LCD_DataWrite(temp);  
}

void PWM1_system_clk_out(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8a);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD4 ;
  LCD_DataWrite(temp);  
}

void PWM1_clock_ratio(uint8_t setx) //bit0~3 
{
  uint8_t temp,temp1;
  temp1= setx&0x0f;
  LCD_CmdWrite(0x8a);//MCLR
  temp = LCD_DataRead();
  temp &= 0xf0;
  temp |= temp1 ;
  LCD_DataWrite(temp);  
}

void PWM1_duty_cycle(uint8_t setx) //bit0~7
{
  
  LCD_CmdWrite(0x8b);//PTNO
  LCD_DataWrite(setx);
} 	

void PWM2_enable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8c);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp);  
}

void PWM2_disable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8c);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);  
}

void PWM2_disable_level_low(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8c);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD6 ;
  LCD_DataWrite(temp);  
}

void PWM2_disable_level_high(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8c);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD6 ;
  LCD_DataWrite(temp);  
}

void PWM2_fnuction_sel(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8c);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD4 ;
  LCD_DataWrite(temp);  
}

void PWM2_system_clk_out(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8c);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD4 ;
  LCD_DataWrite(temp);  
}

void PWM2_clock_ratio(uint8_t setx) //bit0~3 
{
  uint8_t temp,temp1;
  temp1= setx&0x0f;
  LCD_CmdWrite(0x8c);//MCLR
  temp = LCD_DataRead();
  temp &= 0xf0;
  temp |= temp1 ;
  LCD_DataWrite(temp);  
}
void PWM2_duty_cycle(uint8_t setx) //bit0~7
{  
  LCD_CmdWrite(0x8d);//PTNO
  LCD_DataWrite(setx);
} 	


//---------------------------------------------//
//REG[8Eh]
void Stop_Memory_Clear(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8e);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD7 ;
  LCD_DataWrite(temp);  
}						 
void Memory_Clear(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8e);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD7 ;
  LCD_DataWrite(temp); 
  Chk_Busy(); 
}
void Clear_Full_Window(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8e);//MCLR
  temp = LCD_DataRead();
  temp &= cClrD6 ;
  LCD_DataWrite(temp);  
}
void Clear_Active_Window(void)
{
  uint8_t temp;
  LCD_CmdWrite(0x8e);//MCLR
  temp = LCD_DataRead();
  temp |= cSetD6 ;
  LCD_DataWrite(temp);  
}


//---------------------------------------------//
//REG[90h] 
void Draw_line(void)
{ 
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x00);
  LCD_DataWrite(0x80);
}

void Draw_square(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x10);
  LCD_DataWrite(0x90);
}

void Draw_square_fill(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x10);
  LCD_DataWrite(0xb0);
}

void Draw_circle(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x40);
}

void Draw_circle_fill(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x60);
}

void Draw_Triangle(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x00);
  LCD_DataWrite(0x81);
}

void Draw_Triangle_fill(void)
{
  LCD_CmdWrite(0x90);//DCR
  LCD_DataWrite(0x01);
  LCD_DataWrite(0xA1);
}

//---------------------------------------------//
//REG[90h]~/EG[9Dh]  									
void Geometric_Coordinate(uint16_t X,uint16_t Y,uint16_t X1  ,uint16_t Y1)
{	 
  LCD_CmdWrite(0x91);
  LCD_DataWrite(X);
  LCD_CmdWrite(0x92);	
  LCD_DataWrite(X>>8);
  LCD_CmdWrite(0x93);
  LCD_DataWrite(Y);  
  LCD_CmdWrite(0x94);
  LCD_DataWrite(Y>>8);
  LCD_CmdWrite(0x95);
  LCD_DataWrite(X1); 
  LCD_CmdWrite(0x96);	
  LCD_DataWrite(X1>>8);
  
  
  
  LCD_CmdWrite(0x97);
  LCD_DataWrite(Y1);  
  LCD_CmdWrite(0x98);
  LCD_DataWrite(Y1>>8);
}



//---------------------------------------------//
//REG[A0h] 
void Draw_Ellipse(void)
{
  LCD_CmdWrite(0xA0);//DCR
  LCD_DataWrite(0x00);
  LCD_DataWrite(0x80);
}
void Draw_Ellipse_fill(void)
{
  LCD_CmdWrite(0xA0);//DCR
  LCD_DataWrite(0x40);
  LCD_DataWrite(0xC0);
}
void Draw_Ellipse_Curve(void)
{  
  uint8_t temp;
  LCD_CmdWrite(0xA0);//DCR
  temp = LCD_DataRead();
  temp &=0x1F;
  temp |= 0x90;
  LCD_DataWrite(temp);
}

void Draw_Ellipse_Curve_Fill(void)
{  
  uint8_t temp;
  LCD_CmdWrite(0xA0);//DCR
  temp = LCD_DataRead();
  temp &=0x1F;
  temp |= 0xD0;
  LCD_DataWrite(temp);
}

void Draw_Ellipse_Curve_part(uint8_t setx)
{
  uint8_t temp,temp1;
  LCD_CmdWrite(0xA0);//DCR
  temp = LCD_DataRead();
  temp1 = setx&0x03;
  temp &=0xfc;
  temp |=temp1;
  LCD_DataWrite(temp);   
}

void Draw_Circle_Square(void)
{
  LCD_CmdWrite(0xA0);//DCR
  LCD_DataWrite(0x20);
  LCD_DataWrite(0xA0);
}

void Draw_Circle_Square_fill(void)
{
  LCD_CmdWrite(0xA0);//DCR
  LCD_DataWrite(0x60);
  LCD_DataWrite(0xE0);
}

/******************************************************************************
* Function Name  : Circle_Coordinate_Radius
* Description    : Geometric Pattern Drawing Engine :Circle Of Circlar Corner Input 
* Input          : - X:
*                  - Y:
*       				   - R
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	
void Circle_Coordinate_Radius(uint16_t X,uint16_t Y,uint16_t R)
{
  
  LCD_CmdWrite(0x99);
  LCD_DataWrite(X);  
  LCD_CmdWrite(0x9a);	   
  LCD_DataWrite(X>>8);  
  
  LCD_CmdWrite(0x9b);
  LCD_DataWrite(Y); 
  LCD_CmdWrite(0x9c);	   
  LCD_DataWrite(Y>>8);
  
  LCD_CmdWrite(0x9d);
  LCD_DataWrite(R);
}
/******************************************************************************
* Function Name  : Ellipse_Coordinate_setting
* Description    : Geometric Pattern Drawing Engine :Ellipse Of Circlar Corner Input 
* Input          : - X:
*                  - Y:
*       				   - ELL_A:Long axis
*       		       - ELL_B:short axis
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	
void Ellipse_Coordinate_setting(uint16_t X,uint16_t Y,uint16_t ELL_A,uint16_t ELL_B)
{
  
  LCD_CmdWrite(0xA5);
  LCD_DataWrite(X);
  LCD_CmdWrite(0xA6);	   
  LCD_DataWrite(X>>8);  
  
  LCD_CmdWrite(0xA7);
  LCD_DataWrite(Y); 
  LCD_CmdWrite(0xA8);	   
  LCD_DataWrite(Y>>8);
  
  LCD_CmdWrite(0xA1);
  LCD_DataWrite(ELL_A);
  LCD_CmdWrite(0xA2);
  LCD_DataWrite(ELL_A>>8);
  
  LCD_CmdWrite(0xA3);
  LCD_DataWrite(ELL_B);
  LCD_CmdWrite(0xA4);
  LCD_DataWrite(ELL_B>>8);
} 


/******************************************************************************
* Function Name  : Circle_Square_Coordinate_setting
* Description    : Geometric Pattern Drawing Engine :Square Of Circlar Corner Input 
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*       				   - ELL_A:Long axis
*       		       - ELL_B:short axis
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	
void Circle_Square_Coordinate_setting(uint16_t X0,uint16_t Y0 ,uint16_t X1 ,uint16_t Y1 ,uint16_t ELL_A,uint16_t ELL_B)
{	    
  
  LCD_CmdWrite(0x91);
  LCD_DataWrite(X0);  
  LCD_CmdWrite(0x92);	   
  LCD_DataWrite(X0>>8);
  
  
  LCD_CmdWrite(0x93);
  LCD_DataWrite(Y0);  
  LCD_CmdWrite(0x94);	   
  LCD_DataWrite(Y0>>8);
  
  LCD_CmdWrite(0x95);
  LCD_DataWrite(X1);   
  LCD_CmdWrite(0x96);	   
  LCD_DataWrite(X1>>8);
  
  
  LCD_CmdWrite(0x97);
  LCD_DataWrite(Y1);  
  LCD_CmdWrite(0x98);	   
  LCD_DataWrite(Y1>>8);
  
  LCD_CmdWrite(0xA1);
  LCD_DataWrite(ELL_A);
  LCD_CmdWrite(0xA2);
  LCD_DataWrite(ELL_A>>8);
  
  LCD_CmdWrite(0xA3);
  LCD_DataWrite(ELL_B);
  LCD_CmdWrite(0xA4);
  LCD_DataWrite(ELL_B>>8); 
}

/******************************************************************************
* Function Name  : Draw_Triangle_3point_Coordinate
* Description    : Geometric Pattern Drawing Engine :Triangle Of Circlar Corner Input 
* Input          : - P1_X:
*                  - P1_Y:
*       				   - P2_X
*       		       - P2_Y
*       				   - P3_X
*       		       - P3_Y
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	 
void Draw_Triangle_3point_Coordinate(uint16_t P1_X,uint16_t P1_Y,uint16_t P2_X,uint16_t P2_Y,uint16_t P3_X,uint16_t P3_Y)
{	    
  
  LCD_CmdWrite(0x91);
  LCD_DataWrite(P1_X);  
  LCD_CmdWrite(0x92);	   
  LCD_DataWrite(P1_X>>8);
  
  LCD_CmdWrite(0x93);
  LCD_DataWrite(P1_Y);  
  LCD_CmdWrite(0x94);	   
  LCD_DataWrite(P1_Y>>8);
  
  LCD_CmdWrite(0x95);
  LCD_DataWrite(P2_X);  
  LCD_CmdWrite(0x96);	   
  LCD_DataWrite(P2_X>>8);
  
  LCD_CmdWrite(0x97);
  LCD_DataWrite(P2_Y);  
  LCD_CmdWrite(0x98);	   
  LCD_DataWrite(P2_Y>>8);
  
  LCD_CmdWrite(0xA9);
  LCD_DataWrite(P3_X);  
  LCD_CmdWrite(0xAA);	   
  LCD_DataWrite(P3_X>>8);
  
  LCD_CmdWrite(0xAB);
  LCD_DataWrite(P3_Y);   
  LCD_CmdWrite(0xAC);	   
  LCD_DataWrite(P3_Y>>8);   
}

//---------------------------------------------//
//REG[B0]~REG[B3]
void DMA_Start_address_setting(uint32_t set_address)
{ 
  LCD_CmdWrite(0xB0);
  LCD_DataWrite(set_address);
  
  LCD_CmdWrite(0xB1);
  LCD_DataWrite(set_address>>8);
  
  LCD_CmdWrite(0xB2);
  LCD_DataWrite(set_address>>16);
  
  LCD_CmdWrite(0xB3);
  LCD_DataWrite(set_address>>24);
  
}

//input pic data quantity  for example  pic size = 800*480 = 384000
void DMA_Continuous_mode_size_setting(uint32_t set_size)
{ 
  LCD_CmdWrite(0xB4);
  LCD_DataWrite(set_size);
  
  LCD_CmdWrite(0xB6);
  LCD_DataWrite(set_size>>8);
  
  LCD_CmdWrite(0xB8);
  LCD_DataWrite(set_size>>16);
}

void DMA_block_mode_size_setting(uint16_t BWR,uint16_t BHR,uint16_t SPWR)
{
  LCD_CmdWrite(0xB4);
  LCD_DataWrite(BWR);
  LCD_CmdWrite(0xB5);
  LCD_DataWrite(BWR>>8);
  
  LCD_CmdWrite(0xB6);
  LCD_DataWrite(BHR);
  LCD_CmdWrite(0xB7);
  LCD_DataWrite(BHR>>8);
  
  LCD_CmdWrite(0xB8);
  LCD_DataWrite(SPWR);
  LCD_CmdWrite(0xB9);
  LCD_DataWrite(SPWR>>8);  
}

//---------------------------------------------//
//REG[BFh]
void DMA_Continuous_mode(void)
{ 
  LCD_CmdWrite(0xBF);
  LCD_DataWrite(0x00);
}

void DMA_Block_mode(void)
{ 
  LCD_CmdWrite(0xBF);
  LCD_DataWrite(0x02);
}

void DMA_Start_enable(void)
{  
  uint8_t temp;
  LCD_CmdWrite(0xBF);
  temp = LCD_DataRead();
  temp |= 0x01;
  LCD_DataWrite(temp);
}

//---------------------------------------------//
//REG[C0h]
void Key_Scan_Enable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xC0);
  temp = LCD_DataRead();
  temp |= 0x80;
  LCD_DataWrite(temp);  
}


void Key_Scan_setting(uint8_t setx)//uint8_t[2:0]
{ 
  uint8_t temp;
  LCD_CmdWrite(0xC0);
  temp = LCD_DataRead();
  temp &= 0xf0;
  temp|= (setx&0x07);
  LCD_DataWrite(temp);  
} 

void Long_Key_Scan_enable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xC0);
  temp = LCD_DataRead();
  temp |= 0x40;
  LCD_DataWrite(temp);
}

void Key_Scan_Wakeup_Function_Enable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xC1);	
  temp = LCD_DataRead();
  temp |= 0x80;	// 
  LCD_DataWrite(temp);
}

void Long_Key_Timing_Adjustment(uint8_t setx)
{
  uint8_t temp,temp1;
  temp = setx & 0x1c;
  LCD_CmdWrite(0xC1);
  temp1 = LCD_DataRead();
  temp1|=temp;
  LCD_DataWrite(temp1);   
  
}

//---------------------------------------------//
//REG[D0]
void Floating_window_start_point(uint16_t X,uint16_t Y)
{ 
  LCD_CmdWrite(0xD0);
  LCD_DataWrite(X);
  LCD_CmdWrite(0xD1);
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0xD2);
  LCD_DataWrite(Y);
  LCD_CmdWrite(0xD3);
  LCD_DataWrite(Y>>8);  
}


void Floating_window_size(uint16_t width_X,uint16_t high_Y)
{
  
  LCD_CmdWrite(0xD4);
  LCD_DataWrite(width_X);
  LCD_CmdWrite(0xD5);
  LCD_DataWrite(width_X>>8);
  
  LCD_CmdWrite(0xD6);
  LCD_DataWrite(high_Y);
  LCD_CmdWrite(0xD7);
  LCD_DataWrite(high_Y>>8);
  
}

void Floating_window_display_point(uint16_t X,uint16_t Y)
{
  
  LCD_CmdWrite(0xD8);
  LCD_DataWrite(X);
  LCD_CmdWrite(0xD9);
  LCD_DataWrite(X>>8);
  
  LCD_CmdWrite(0xDA);
  LCD_DataWrite(Y);
  LCD_CmdWrite(0xDB);
  LCD_DataWrite(Y>>8);
  
}


//REG[E0h] 
void Serial_ROM_direct_access_mode_enable(void)
{
  LCD_CmdWrite(0xE0);
  LCD_DataWrite(0x01);
}

void Serial_ROM_direct_access_mode_disable(void)
{
  LCD_CmdWrite(0xE0);
  LCD_DataWrite(0x00);
}

void Direct_access_mode_Address_32bits(uint32_t set_address)
{
  uint8_t temp;  
  temp = set_address>>24;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);
  temp = set_address>>16;
  LCD_DataWrite(temp);
  temp = set_address>>8;
  LCD_DataWrite(temp);
  temp = set_address;
  LCD_DataWrite(temp);
  
}

void Direct_access_mode_Address_24bits(uint32_t set_address)
{
  uint8_t temp=0;
  
  temp = set_address>>16;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);  
  temp = set_address>>8;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);   
  temp = set_address;
  LCD_CmdWrite(0xE1);
  LCD_DataWrite(temp);
  
}

uint8_t Direct_access_mode_Read_Data_buffer(void)
{
  uint8_t Serial_Data;
  LCD_CmdWrite(0xE2);
  Serial_Data=LCD_DataRead(); 
  return Serial_Data;
}

//---------------------------------------------//



//---------------------------------------------//
//REG[F0h] 

void KEYSCAN_Interrupt_Enable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp |= 0x10;	// 
  LCD_DataWrite(temp); 
}

void KEYSCAN_Interrupt_Disable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp &= 0x0F;	// 
  LCD_DataWrite(temp); 
}


void DMA_Interrupt_Enable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp |= 0x08;	// 
  LCD_DataWrite(temp); 
}

void DMA_Interrupt_Disable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF0);	
  temp = LCD_DataRead();
  temp &= 0x17;	// 
  LCD_DataWrite(temp); 
}

void Touch_Panel_Interrupt_Enable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp |= 0x04;
  LCD_DataWrite(temp);
}

void Touch_Panel_Interrupt_Disable(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp &= 0x1B;
  LCD_DataWrite(temp);
}

void BTE_Interrupt_Enable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp |= 0x02;
  LCD_DataWrite(temp);
}

void BTE_Interrupt_Disable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp &= 0x1D;
  LCD_DataWrite(temp);
}

void Font_BTE_read_write_Interrupt_Enable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp |= 0x01;
  LCD_DataWrite(temp);
}

void Font_BTE_read_write_Interrupt_Disable(void)
{
  uint8_t temp;
  LCD_CmdWrite(0xF0);//INTC
  temp=LCD_DataRead(); 
  temp &= 0x1E;
  LCD_DataWrite(temp);
}

//---------------------------------------------//
//REG[F1h] 
void Clear_keyscan_interrupt(void)
{ uint8_t temp;
LCD_CmdWrite(0xF1);//INTC
temp=LCD_DataRead(); 
temp |=cSetD4 ;
LCD_DataWrite(temp);
}

uint8_t Keyscan_Status(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC	
  temp = LCD_DataRead();
  if ((temp&0x10)==0x10)
    return 1;
  else 
    return 0;
}

void Clear_DMA_interrupt(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |=cSetD3 ;
  LCD_DataWrite(temp);
}

uint8_t DMA_Status(void)
{   
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC	
  temp = LCD_DataRead();
  if ((temp&0x08)==0x08)
    return 1;
  else 
    return 0;
}

void clear_TP_interrupt(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |= cSetD2;
  LCD_DataWrite(temp);
}


uint8_t Touch_Status(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC	
  temp = LCD_DataRead();
  if ((temp&0x04)==0x04)
    return 1;
  else 
    return 0;
}

void Clear_BTE_interrupt(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |= cSetD1;
  LCD_DataWrite(temp);
}

uint8_t BTE_Status(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC	
  temp = LCD_DataRead();
  if ((temp&0x02)==0x02)
    return 1;
  else 
    return 0;
}

void Clear_Font_BTE_read_write_Interrupt(void)
{ 
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC
  temp=LCD_DataRead(); 
  temp |= cSetD0;
  LCD_DataWrite(temp);
}

uint8_t Font_BTE_read_write_Status(void)
{	
  uint8_t temp;
  LCD_CmdWrite(0xF1);//INTC	
  temp = LCD_DataRead();
  if ((temp&0x01)==0x01)
    return 1;
  else 
    return 0;
}


void Chk_Wait(void)
{
  //while(MCU_WAIT==0);	   
}

void Show_String(uint8_t *str,uint8_t n)
{   
  Text_Mode();
  LCD_CmdWrite(0x02);
  while(*str != '\0')
  {
    LCD_DataWrite(*str);
    ++str;	 	
    Chk_Busy();
    //Chk_Wait();		
  }
}


void LCD_Reset(void)
{
  //GPIOA->BRR  = GPIO_Pin_3; //RA8875 RESET pin
  //delay_ms(110);
  //GPIOA->BSRR  = GPIO_Pin_3;
  //delay_ms(110);
}

/*******************************************************************************
* Function Name  : LcdClear
* Description    : Clear the screen  
* Input          : Color: Screen Color
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void LcdClear(uint16 color)
{
  Text_color(color); // Set the color
  Geometric_Coordinate(0,0,800,479);
  LCD_CmdWrite(0x90);
  LCD_DataWrite(0xB0);
  
  LCD_CmdWrite(0x01);//Display on
  LCD_DataWrite(0x80);
}

/*******************************************************************************
* Function Name  : lcd_drawpoint
* Description    : Dot on the LCD 
* Input          : x：X coordinate
x：X coordinate
Color: point Color
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/
void Lcd_DrawPoint(uint16 x, uint16 y, uint16 color)
{
  Text_color(color); // Set the color
  LCD_CmdWrite(0x99);
  LCD_DataWrite(x);  
  LCD_CmdWrite(0x9a);	   
  LCD_DataWrite(x>>8);  
  
  LCD_CmdWrite(0x9b);
  LCD_DataWrite(y); 
  LCD_CmdWrite(0x9c);	   
  LCD_DataWrite(y>>8);
  
  LCD_CmdWrite(0x9d);
  LCD_DataWrite(0X01);
  Draw_circle_fill();
}	

/******************************************************************************
* Function Name  : LCD_DrawCircle
* Description    : Bresenham's line algorithm :Circle Input 
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*                  - color:
*                  - fill :Whether can fill
This parameter can be: ENABLE or 0.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void LCD_DrawCircle( uint16_t x, uint16_t y, uint16_t r , uint16_t color , uint16_t fill )
{
  Circle_Coordinate_Radius(x,y,r);
  Text_color(color); // Set the color
  if (fill != 0)
    Draw_circle_fill();		
  else 
    Draw_circle();
}

/******************************************************************************
* Function Name  : LCD_DrawEllipse
* Description    : Bresenham's line algorithm :Ellipse Input 
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*                  - color:
*                  - fill :Whether can fill
This parameter can be: ENABLE or 0.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void LCD_DrawEllipse( uint16_t x, uint16_t y, uint16_t Long_axis , uint16_t Short_axis,uint16_t color , uint16_t fill )
{
  
  Ellipse_Coordinate_setting(x,y,Long_axis,Short_axis);
  Text_color(color); // Set the color
  if (fill != 0)
    Draw_Ellipse_fill();			
  else
    Draw_Ellipse();
}


/******************************************************************************
* Function Name  : LCD_DrawCurve
* Description    : Bresenham's line algorithm :Curve Input  
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*                  - color:
*									 - part
00:	lowe left 
01:	upper left
02:	upper right(RU)
03:	low right
*                  - fill :Whether can fill
This parameter can be: ENABLE or 0.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void LCD_DrawCurve( uint16_t x, uint16_t y, uint16_t Long_axis , uint16_t Short_axis,uint16_t color ,uint16_t part, uint16_t fill )
{
  Ellipse_Coordinate_setting(x,y,Long_axis,Short_axis);
  Text_color(color); // Set the color
  Draw_Ellipse_Curve_part(part);
  if (fill != 0)
    Draw_Ellipse_Curve_Fill();			
  else
    Draw_Ellipse_Curve();
}


/******************************************************************************
* Function Name  : LCD_DrawSquare
* Description    : Bresenham's line algorithm :Curve Input  
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*                  - color:
*                  - fill :Whether can fill
This parameter can be: ENABLE or 0.
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void LCD_DrawSquare( uint16_t x0, uint16_t y0, uint16_t x1 , uint16_t y1,uint16_t color , uint16_t fill )
{
  
  Geometric_Coordinate(x0,y0,x1,y1);
  Text_color(color); // Set the color	
  if (fill != 0)
    Draw_square_fill();	
  else 
    Draw_square();		
}

/******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : Geometric Pattern Drawing Engine :
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*                  - color:
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/	 
void LCD_DrawLine( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color )
{
  Geometric_Coordinate(x0,y0,x1,y1);
  Text_color(color); // 设定颜色 	
  Draw_line();
}

/******************************************************************************
* Function Name  : LCD_DrawTriangle
* Description    : Geometric Pattern Drawing Engine 
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*       				   - x2:
*       		       - y2:
*                  - color:
*                  - fill :Whether can fill
This parameter can be: ENABLE or 0.
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	 
void LCD_DrawTriangle( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t x2, uint16_t y2 ,uint16_t color, uint16_t fill )
{	
  Draw_Triangle_3point_Coordinate(x0,y0,x1,y1,x2,y2);
  Text_color(color); // Set the color
  if (fill != 0)
    Draw_Triangle_fill();			
  else
    Draw_Triangle(); 
}

/******************************************************************************
* Function Name  : LCD_DrawCircleSquare
* Description    : Geometric Pattern Drawing Engine :Square Of Circlar Corner Input 
* Input          : - x0:
*                  - y0:
*       				   - x1:
*       		       - y1:
*       				   - x2:
*       		       - y2:
*                  - color:
*                  - fill :Whether can fill
This parameter can be: ENABLE or 0.
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	 
void LCD_DrawCircleSquare( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t Long_axis , uint16_t Short_axis,uint16_t color, uint16_t fill )
{	
  Circle_Square_Coordinate_setting(x0,y0,x1,y1,Long_axis,Short_axis);	
  Text_color(color); // Set the color
  if (fill != 0)
  {
    Draw_Circle_Square_fill();			
  }
  else
  {
    Draw_Circle_Square();
  }
  
}

/******************************************************************************
* Function Name  : LCD_Internal_Font_ROM
* Description    : The RA8875 embedded 8x16 dots ASCII Font ROM that provides user a convenient way to 
input characters by code. The embedded character set supports ISO/IEC 8859-1~4 coding 
standard. Besides, user can choose the font foreground color by setting the REG[60h~62h] and 
background color by setting the REG[63h~65h]. For the procedure of characters writing please 
refers to below figure:  
* Input          : - x0:
*                  - y0:
*       				   - Foreground_color:
*       		       - Background_color:
*       				   - Alignment:
0 : Full alignment is disable. 
1 : Full alignment is enable. 
*       		       - Transparency:
0 : Font with background color.  
1 : Font with background transparency. 
*                  - zoom:
1 : X1. 
2 : X2. 
3 : X3.
4 : X4.
*                  - turning :Whether can fill
0 : Normal.  
1 : 90 degree display.  
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	
void LCD_Internal_Font_ROM(uint16_t x0, uint16_t y0,uint16_t Foreground_color,uint16_t Background_color,uint16_t Alignment,uint16_t Transparency, uint16_t zoom,uint16_t turning)
{
  Text_Mode();
  Internal_CGROM();
  Font_Coordinate(x0,y0);
  
  /******** Font foreground and background color Select   *******/		
  Text_Foreground_Color((Foreground_color&0xf800)>>11 ,(Foreground_color&0x07e0)>>5,(Foreground_color&0x001f));
  Text_Background_Color((Background_color&0xf800)>>11 ,(Background_color&0x07e0)>>5,(Background_color&0x001f));
  
  /******************** Font Transparency  *********************/	
  if(Alignment) 
    No_FullAlignment();
  else 
    FullAlignment();	
  
  /**************** Full Alignment Selection Bit   **************/	
  if(Transparency) 
    Font_with_BackgroundTransparency();
  else 
    Font_with_BackgroundColor();	
  
  /**************** Enlargement, Transparent Font   ***************/	
  switch (zoom)
  {
  case 0:
    Horizontal_FontEnlarge_x1();
    Vertical_FontEnlarge_x1();
    break;
  case 1:Horizontal_FontEnlarge_x1();
  Vertical_FontEnlarge_x1();
  break;
  case 2:Horizontal_FontEnlarge_x2();
  Vertical_FontEnlarge_x2();
  break;
  case 3:Horizontal_FontEnlarge_x3();
  Vertical_FontEnlarge_x3();
  break;
  case 4:Horizontal_FontEnlarge_x4();
  Vertical_FontEnlarge_x4();
  break;
  default:
    break;
  }
  /*********************** 90 Degree Font  **********************/	
  if(turning) 
    Rotate90_Font();
  else 
    NoRotate_Font();
  
}
/******************************************************************************
* Function Name  : LCD_External_Font_ROM
* Description    : The RA8875 embedded 8x16 dots ASCII Font ROM that provides user a convenient way to 
input characters by code. The embedded character set supports ISO/IEC 8859-1~4 coding 
standard. Besides, user can choose the font foreground color by setting the REG[60h~62h] and 
background color by setting the REG[63h~65h]. For the procedure of characters writing please 
refers to below figure:  
* Input          : - x0:
*                  - y0:
*       				   - Foreground_color:
*       		       - Background_color:
*       				   - Alignment:
0 : Full alignment is disable. 
1 : Full alignment is enable. 
*       		       - Transparency:
0 : Font with background color.  
1 : Font with background transparency. 
*                  - zoom:
1 : X1. 
2 : X2. 
3 : X3.
4 : X4.
*                  - turning :Whether can fill
0 : Normal.  
1 : 90 degree display.  
* Output         : None
* Return         : None
* Attention		   : None
*******************************************************************************/	
void LCD_External_Font_ROM(uint16_t x0, uint16_t y0,uint16_t Foreground_color,uint16_t Background_color,uint16_t Alignment,uint16_t Transparency, uint16_t zoom,uint16_t turning)
{
  Text_Mode();
  //*******set Font rom*******
  CGROM_Font(); 
  //Internal_CGROM();
  External_CGROM();//选择外部字库芯片
  //Font_size_16x16_8x16(); 
  Font_size_24x24_12x24();//字体大小选择
  //Font_size_32x32_16x32();
  
  //GT_serial_ROM_select_GT21L16T1W();
  //GT_serial_ROM_select_GT23L16U2W();
  GT_serial_ROM_select_GT23L24T3Y();//选择GT23L24T3Y
  //GT_serial_ROM_select_GT23L24M1Z();
  //GT_serial_ROM_select_GT23L32S4W();
  
  /***********显示字码选择****************/
  Font_code_GB2312();
  //Font_code_GB12345();
  //Font_code_BIG5();
  //Font_code_UNICODE();
  //Font_code_ASCII();
  //Font_code_UNIJIS();
  //Font_code_JIS0208();
  //Font_code_LATIN();
  
  //Font_Standard();
  Font_Arial();
  //Font_Roman();
  //Font_Bold();
  /****************外置字符芯片设置*******************/
  Serial_ROM_select0();//选择SPI_FLASH ROM0
  //Serial_ROM_select1();
  
  Serial_ROM_Address_set_24bit();//24位寻址模式
  //Serial_ROM_Address_set_32bit();
  //Select_Serial_Waveform_mode0();
  Select_Serial_Waveform_mode3();//波形模式3
  
  //SERIAL_ROM_Read_Cycle_4bus();
  SERIAL_ROM_Read_Cycle_5bus();
  //SERIAL_ROM_Read_Cycle_6bus();
  
  SERIAL_ROM_Font_mode();
  //SERIAL_ROM_DMA_mode();
  
  SERIAL_ROM_Signal_mode();
  //SERIAL_ROM_Dual_mode0();
  //SERIAL_ROM_Dual_mode1();
  
  SROM_CLK_DIV(0x03);	//SFCL频率设定
  
  Font_code_GB2312();	
  Font_Coordinate(x0,y0);
  
  /******** Font foreground and background color Select   *******/		
  Text_Foreground_Color((Foreground_color&0xf800)>>11 ,(Foreground_color&0x07e0)>>5,(Foreground_color&0x001f));
  Text_Background_Color((Background_color&0xf800)>>11 ,(Background_color&0x07e0)>>5,(Background_color&0x001f));
  
  /******************** Font Transparency  *********************/	
  if(Alignment) 
    No_FullAlignment();
  else 
    FullAlignment();	
  
  /**************** Full Alignment Selection Bit   **************/	
  if(Transparency) 
    Font_with_BackgroundTransparency();
  else 
    Font_with_BackgroundColor();	
  
  /**************** Enlargement, Transparent Font   ***************/	
  switch (zoom)
  {
  case 0:
    break;
  case 1:Horizontal_FontEnlarge_x1();
  Vertical_FontEnlarge_x1();
  break;
  case 2:Horizontal_FontEnlarge_x2();
  Vertical_FontEnlarge_x2();
  break;
  case 3:Horizontal_FontEnlarge_x3();
  Vertical_FontEnlarge_x3();
  break;
  case 4:Horizontal_FontEnlarge_x4();
  Vertical_FontEnlarge_x4();
  break;
  default:
    break;
  }
  /*********************** 90 Degree Font  **********************/	
  if(turning) 
    Rotate90_Font();
  else 
    NoRotate_Font();
}
