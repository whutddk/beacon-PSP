#define uint8 uint8

void touch_delay();
void CT_I2C_Init(void);
void CT_SDA_OUT();
void CT_SDA_IN();

//IIC
void CT_I2C_Init(void);		 
void CT_I2C_Start(void);				//开始信号
void CT_I2C_Stop(void);	  				//停止信号
void CT_I2C_Send_Byte(uint8 txd);			//IIC发送一个字节
uint8 CT_I2C_Read_Byte(unsigned char ack);	//IIC读取一个字节
uint8 CT_I2C_Wait_Ack(void); 				//IIC等待ACKD信号
void CT_I2C_Ack(void);					//IIC发送ACKD信号
void CT_I2C_NAck(void);					//IIC不发送ACKD信号	  

//io口定义
#define SET_SDA()     LPLD_GPIO_Output_b(PTD, 9, 1)   
#define CLR_SDA()     LPLD_GPIO_Output_b(PTD, 9, 0) 

#define SET_CLK()     LPLD_GPIO_Output_b(PTD, 8, 1)
#define CLR_CLK()     LPLD_GPIO_Output_b(PTD, 8, 0)

#define CT_READ_SDA   LPLD_GPIO_Input_b(PTD, 9)
