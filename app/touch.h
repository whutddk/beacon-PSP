void TP_INT_Config(void);
void portb_isr();

#define CT_CMD_WR		0XBA	//D�䨺y?Y?����?
#define CT_CMD_RD   	0XBB	//?����y?Y?����?
#define CT_EXCHG_XY		1		//�̡¡�aXY��?����

#define CT_MAX_TOUCH    5		//��?��Y�䣤?t?����?�䨮?��3?��?��?��y
#define CT_READ_XY_REG 	0x721  	//?����?��?����??��??�� 
#define CT_CONFIG_REG   0x6A2	//????2?��y?e��???��??��

//��?��Y�䣤?t?��?????��
typedef struct
{
  //uint8   (*init)(void);			//3?��??���䣤?t?��?????��
  //void (*scan)(void);			//����?���䣤?t?�� 	 
  uint16 x[CT_MAX_TOUCH];		//�䣤?tX��?����
  uint16 y[CT_MAX_TOUCH];		//�䣤?tY��?����
  uint8	ppr[CT_MAX_TOUCH];		//�䣤?t��?��??1��|	 
  uint8 tpsta;					//�䣤?t?�����䨬?
  //[0]:0,�䣤?t��?0?TD��;1,�䣤?t��?0��DD��
  //[1]:0,�䣤?t��?1?TD��;1,�䣤?t��?1��DD��
  //[2]:0,�䣤?t��?2?TD��;1,�䣤?t��?2��DD��
  //[3]:0,�䣤?t��?3?TD��;1,�䣤?t��?3��DD��
  //[4]:0,�䣤?t��?4?TD��;1,�䣤?t��?4��DD��
  //[5:6]:���ꨢ?
  //[7]:0,??��D��DD��䣤?t;1,��D��DD��䣤?t,?����??��3?��y?Y
  
}_m_ctp_dev;


extern _m_ctp_dev ctp_dev;
extern uint8 show[9];
extern double show_chn[50];

uint8 GT811_WR_Reg(uint16 reg,uint8 *buf,uint8 len);//?��GT811D�䨨?��?��?��y?Y						    
uint8 GT811_WR_Reg(uint16 reg,uint8 *buf,uint8 len);//�䨮GT811?��3?��?��?��y?Y
uint8 GT811_Send_Cfg(uint8 * buf,uint16 cfg_len);//?��GT811����?��????2?��y
void GT811_Wakeup_Sleep(void);			//??D?GT811
uint8 GT811_Init(void);	    			//3?��??��GT811						 
void GT811_Scan(void);					//����?��GT811	  
void CT_TEST(void);

