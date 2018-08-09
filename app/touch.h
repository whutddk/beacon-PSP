void TP_INT_Config(void);
void portb_isr();

#define CT_CMD_WR		0XBA	//D¡ä¨ºy?Y?¨¹¨¢?
#define CT_CMD_RD   	0XBB	//?¨¢¨ºy?Y?¨¹¨¢?
#define CT_EXCHG_XY		1		//¦Ì¡Â¡ÁaXY¡Á?¡À¨º

#define CT_MAX_TOUCH    5		//¦Ì?¨¨Y¡ä£¤?t?¨¢¡Á?¡ä¨®?¡ì3?¦Ì?¦Ì?¨ºy
#define CT_READ_XY_REG 	0x721  	//?¨¢¨¨?¡Á?¡À¨º??¡ä??¡Â 
#define CT_CONFIG_REG   0x6A2	//????2?¨ºy?e¨º???¡ä??¡Â

//¦Ì?¨¨Y¡ä£¤?t?¨¢?????¡Â
typedef struct
{
  //uint8   (*init)(void);			//3?¨º??¡¥¡ä£¤?t?¨¢?????¡Â
  //void (*scan)(void);			//¨¦¡§?¨¨¡ä£¤?t?¨¢ 	 
  uint16 x[CT_MAX_TOUCH];		//¡ä£¤?tX¡Á?¡À¨º
  uint16 y[CT_MAX_TOUCH];		//¡ä£¤?tY¡Á?¡À¨º
  uint8	ppr[CT_MAX_TOUCH];		//¡ä£¤?t¦Ì?¦Ì??1¨¢|	 
  uint8 tpsta;					//¡ä£¤?t?¨¢¡Á¡ä¨¬?
  //[0]:0,¡ä£¤?t¦Ì?0?TD¡ì;1,¡ä£¤?t¦Ì?0¨®DD¡ì
  //[1]:0,¡ä£¤?t¦Ì?1?TD¡ì;1,¡ä£¤?t¦Ì?1¨®DD¡ì
  //[2]:0,¡ä£¤?t¦Ì?2?TD¡ì;1,¡ä£¤?t¦Ì?2¨®DD¡ì
  //[3]:0,¡ä£¤?t¦Ì?3?TD¡ì;1,¡ä£¤?t¦Ì?3¨®DD¡ì
  //[4]:0,¡ä£¤?t¦Ì?4?TD¡ì;1,¡ä£¤?t¦Ì?4¨®DD¡ì
  //[5:6]:¡À¡ê¨¢?
  //[7]:0,??¨®D¨®DD¡ì¡ä£¤?t;1,¨®D¨®DD¡ì¡ä£¤?t,?¨¦¨°??¨¢3?¨ºy?Y
  
}_m_ctp_dev;


extern _m_ctp_dev ctp_dev;
extern uint8 show[9];
extern double show_chn[50];

uint8 GT811_WR_Reg(uint16 reg,uint8 *buf,uint8 len);//?¨°GT811D¡ä¨¨?¨°?¡ä?¨ºy?Y						    
uint8 GT811_WR_Reg(uint16 reg,uint8 *buf,uint8 len);//¡ä¨®GT811?¨¢3?¨°?¡ä?¨ºy?Y
uint8 GT811_Send_Cfg(uint8 * buf,uint16 cfg_len);//?¨°GT811¡¤¡é?¨ª????2?¨ºy
void GT811_Wakeup_Sleep(void);			//??D?GT811
uint8 GT811_Init(void);	    			//3?¨º??¡¥GT811						 
void GT811_Scan(void);					//¨¦¡§?¨¨GT811	  
void CT_TEST(void);

