/*
������ͷ*2
*/

/*
name��  FreeCars��λ��ʾ��������
author��FreeCars����
Date:   2014-10-22
site:   Http://FreeCars.taobao.com
QQȺ��  384273254��149168724 
��Ȩ��  �˴���ΪFreeCars��λ��Э����룬��������ʹ�ã�Ҳ����������ҵ��;�����뱣���˶����֣�
tips:   ǿ�ҽ���С�����ʹ��FreeCars��Ʒ������ģ����װ��������λ�������￪ʼ��
*/

#include "common.h"
#include "include.h"

#define IsSingleLine  0

uint8 uSendBuf[UartDataNum*2]={0};
uint8 FreeCarsDataNum=UartDataNum*2;

double UartData[9] = {0};
SerialPortType SerialPortRx;

/*
��ĳ��ͨ���������������
chanel��ͨ��
data  ������-32768~32767
*/
void push(uint8 chanel,uint16 data)
{
  uSendBuf[chanel*2]=data/256;
  uSendBuf[chanel*2+1]=data%256;
}


/*
��ѯ������һ֡����
����ʱ�������ݳ����й�
�����Է����ж����������Ե���
����ʱ����㿴�����ĵ�
*/
void sendDataToScope()
{
  uint8 i,sum=0; 
  //ʹ����ѯ�ķ�ʽ�������ݣ�������δ���ͣ�����ͣ�ڴ˴�ֱ���������
  LPLD_UART_PutChar(FreeCarsUARTPort,251);
  LPLD_UART_PutChar(FreeCarsUARTPort,109);
  LPLD_UART_PutChar(FreeCarsUARTPort,37);
  sum+=(251);      //ȫ�����ݼ���У��
  sum+=(109);
  sum+=(37);
  for(i=0;i<FreeCarsDataNum;i++)
  {
    LPLD_UART_PutChar(FreeCarsUARTPort,uSendBuf[i]);
    sum+=uSendBuf[i];         //ȫ�����ݼ���У��
  }
  LPLD_UART_PutChar(FreeCarsUARTPort,sum);
}

void pcdata(void)//�����ж�
{
  int i,b,d1;
  uint32 d;
  
  //if((UART_S1_REG(UART0) & UART_S1_RDRF_MASK))//�ǽ����ж�
  {
    SerialPortRx.Data = LPLD_UART_GetChar(UART0);  
    
    if( SerialPortRx.Stack < UartRxBufferLen )
    {
      SerialPortRx.Buffer[SerialPortRx.Stack++] = SerialPortRx.Data;
      
      if(   SerialPortRx.Stack >= UartRxDataLen  //UartRxDataLen����Ϊһ֡
         && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen]  ==0xff //У����ͷ
           && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+1]==0x55
             && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+2]==0xaa
               && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+3]==0x10 )
      {   //double data 9��ͨ������У��
        SerialPortRx.Check = 0;
        b = SerialPortRx.Stack - UartRxDataLen; //��ʼλ
        for(i=b; i<SerialPortRx.Stack-1; i++)  //��У��λ���λ����У��
        {
          SerialPortRx.Check += SerialPortRx.Buffer[i];//У��
        }
        
        if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
        {   //У��ɹ����������ݽ���
          for(i = 0; i<9; i++)
          {
            d = SerialPortRx.Buffer[b+i*4+4]*0x1000000L + SerialPortRx.Buffer[b+i*4+5]*0x10000L + SerialPortRx.Buffer[b+i*4+6]*0x100L + SerialPortRx.Buffer[b+i*4+7];
            if(d>0x7FFFFFFF)
            {
              d1 = 0x7FFFFFFF - d;
            }
            else
            {
              d1 = d;
            }
            UartData[i]=d1;
            UartData[i]/=65536.0;
          }
          UartDebug();  //תȥ�������ܵ������ݸ�������
        }
        SerialPortRx.Stack = 0;
      }
      else if(   SerialPortRx.Stack >= UartRxCmdLen //UartRxDataLen����Ϊһ֡
              && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen]  ==0xff
                && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+1]==0x55
                  && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+2]==0xaa
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+3]==0x77 )//cmd
      {
        SerialPortRx.Check = 0;
        b = SerialPortRx.Stack - UartRxCmdLen; //��ʼλ
        for(i=b; i<SerialPortRx.Stack-1; i++)  //��У��λ���λ����У��
        {
          SerialPortRx.Check += SerialPortRx.Buffer[i];//У��
        }
        if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
        {   //У��ɹ�
          UartCmd(UartCmdNum,UartCmdData);//������յ����������MCU�������
        }
        SerialPortRx.Stack = 0;
      }
    }
    else
    {
      SerialPortRx.Stack = 0;
    } 
  }
}

/*�������ݴ���*/
uint8 flag_receive = 0;
void UartDebug()
{
  uint8 i;
  for(i=0;i<9;i++)
  {
    push(i,(uint16)UartData[i]);
    show_chn[i] = UartData[i];
  }
  
}

void UartCmd(uint8 cmdnum,uint8 cmddata)///
{
  switch(cmddata)
  {
    case(6):break;//F6
    case(7):break;//F7
    case(8):break;//F8
    case(9):break;//F9
    case(10):break;//F10
    case(11):break;//F11
    case(12):break;//F12
    case(100):break;//PAUSE//�ɿ�����
    case(101):break;//PG UP
    case(103):break;//PF DN
    case(104):break;//END//����
  }
}

/*
��ѯ������һ֡����
����ʱ�������ݳ����й�
�����Է����ж����������Ե���
LineData: ����������ͷͼ������������Ϣ

void sendRoadDataToCamViewer(uint8* LineData)
{
uint8  sum=0;                                 
uint16 i,dataNumber;//ע��i��dataNumer����������
//ʹ����ѯ�ķ�ʽ�������ݣ�������δ���ͣ�����ͣ�ڴ˴�ֱ���������
LPLD_UART_PutChar(FreeCarsUARTPort,0xFC);
LPLD_UART_PutChar(FreeCarsUARTPort,0x08);
LPLD_UART_PutChar(FreeCarsUARTPort,0xCF);
sum+=(0xFC);      //ȫ�����ݼ���У��
sum+=(0x08);  
sum+=(0xCF);
dataNumber =  V;//˫��ģʽ���͵�����ΪImgHeight*2
for(i=0;i<dataNumber;i++)
{
LPLD_UART_PutChar(FreeCarsUARTPort,LineData[i]);
sum += LineData[i] ;        //ȫ�����ݼ���У��
  }
LPLD_UART_PutChar(FreeCarsUARTPort,sum);
}


extern uint8 BUFF[H*V];//����ͷ���ݣ�ʹ��һά���飬�ӿ�����ٶ�
void sendCamImgToCamViewer(void)
{
uint16 i,j;
uint16 offset;
LPLD_UART_PutChar(FreeCarsUARTPort,0xFF);//FF,FE,FF,FE �ĸ�����ʾһ��ͼ��Ŀ�ʼ
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);
LPLD_UART_PutChar(FreeCarsUARTPort,0xFF);
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);
for(i = 0;i < V;i++)
{      
offset = i*H; //��ø��е�ƫ����
for(j = 0;j < H;j++)
{
uint8 d = BUFF[offset + j];
if(d > 0xFD) d = 0xFD;
LPLD_UART_PutChar(FreeCarsUARTPort,d);
    }
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);//FE,FE �ĸ�����ʾ����
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);
  }
j=0;
}

*/