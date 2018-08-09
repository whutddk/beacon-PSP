#define uint8 uint8

void touch_delay();
void CT_I2C_Init(void);
void CT_SDA_OUT();
void CT_SDA_IN();

//IIC
void CT_I2C_Init(void);		 
void CT_I2C_Start(void);				//��ʼ�ź�
void CT_I2C_Stop(void);	  				//ֹͣ�ź�
void CT_I2C_Send_Byte(uint8 txd);			//IIC����һ���ֽ�
uint8 CT_I2C_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
uint8 CT_I2C_Wait_Ack(void); 				//IIC�ȴ�ACKD�ź�
void CT_I2C_Ack(void);					//IIC����ACKD�ź�
void CT_I2C_NAck(void);					//IIC������ACKD�ź�	  

//io�ڶ���
#define SET_SDA()     LPLD_GPIO_Output_b(PTD, 9, 1)   
#define CLR_SDA()     LPLD_GPIO_Output_b(PTD, 9, 0) 

#define SET_CLK()     LPLD_GPIO_Output_b(PTD, 8, 1)
#define CLR_CLK()     LPLD_GPIO_Output_b(PTD, 8, 0)

#define CT_READ_SDA   LPLD_GPIO_Input_b(PTD, 9)
