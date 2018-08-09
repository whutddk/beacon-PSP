/*
带摄像头*2
*/

/*
name：  FreeCars上位机示波器例程
author：FreeCars军哥
Date:   2014-10-22
site:   Http://FreeCars.taobao.com
QQ群：  384273254，149168724 
版权：  此代码为FreeCars上位机协议代码，允许任意使用，也允许用于商业用途，但请保留此段文字！
tips:   强烈建议小伙伴们使用FreeCars出品的蓝牙模块套装，无线上位机从这里开始！
*/

#include "common.h"
#include "include.h"

#define IsSingleLine  0

uint8 uSendBuf[UartDataNum*2]={0};
uint8 FreeCarsDataNum=UartDataNum*2;

double UartData[9] = {0};
SerialPortType SerialPortRx;

/*
向某个通道缓冲区填充数据
chanel：通道
data  ：数据-32768~32767
*/
void push(uint8 chanel,uint16 data)
{
  uSendBuf[chanel*2]=data/256;
  uSendBuf[chanel*2+1]=data%256;
}


/*
轮询法发送一帧数据
消耗时间与数据长度有关
不可以放在中断里面周期性调用
消耗时间计算看帮助文档
*/
void sendDataToScope()
{
  uint8 i,sum=0; 
  //使用轮询的方式发送数据，当数据未发送，程序停在此处直到发送完成
  LPLD_UART_PutChar(FreeCarsUARTPort,251);
  LPLD_UART_PutChar(FreeCarsUARTPort,109);
  LPLD_UART_PutChar(FreeCarsUARTPort,37);
  sum+=(251);      //全部数据加入校验
  sum+=(109);
  sum+=(37);
  for(i=0;i<FreeCarsDataNum;i++)
  {
    LPLD_UART_PutChar(FreeCarsUARTPort,uSendBuf[i]);
    sum+=uSendBuf[i];         //全部数据加入校验
  }
  LPLD_UART_PutChar(FreeCarsUARTPort,sum);
}

void pcdata(void)//接收中断
{
  int i,b,d1;
  uint32 d;
  
  //if((UART_S1_REG(UART0) & UART_S1_RDRF_MASK))//是接收中断
  {
    SerialPortRx.Data = LPLD_UART_GetChar(UART0);  
    
    if( SerialPortRx.Stack < UartRxBufferLen )
    {
      SerialPortRx.Buffer[SerialPortRx.Stack++] = SerialPortRx.Data;
      
      if(   SerialPortRx.Stack >= UartRxDataLen  //UartRxDataLen个数为一帧
         && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen]  ==0xff //校验字头
           && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+1]==0x55
             && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+2]==0xaa
               && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxDataLen+3]==0x10 )
      {   //double data 9个通道数据校验
        SerialPortRx.Check = 0;
        b = SerialPortRx.Stack - UartRxDataLen; //起始位
        for(i=b; i<SerialPortRx.Stack-1; i++)  //除校验位外的位进行校验
        {
          SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
        }
        
        if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
        {   //校验成功，进行数据解算
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
          UartDebug();  //转去处理，把受到的数据付给变量
        }
        SerialPortRx.Stack = 0;
      }
      else if(   SerialPortRx.Stack >= UartRxCmdLen //UartRxDataLen个数为一帧
              && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen]  ==0xff
                && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+1]==0x55
                  && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+2]==0xaa
                    && SerialPortRx.Buffer[SerialPortRx.Stack - UartRxCmdLen+3]==0x77 )//cmd
      {
        SerialPortRx.Check = 0;
        b = SerialPortRx.Stack - UartRxCmdLen; //起始位
        for(i=b; i<SerialPortRx.Stack-1; i++)  //除校验位外的位进行校验
        {
          SerialPortRx.Check += SerialPortRx.Buffer[i];//校验
        }
        if( SerialPortRx.Check == SerialPortRx.Buffer[SerialPortRx.Stack-1] )
        {   //校验成功
          UartCmd(UartCmdNum,UartCmdData);//处理接收到的命令，付给MCU命令变量
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

/*接收数据处理*/
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
    case(100):break;//PAUSE//飞控锁定
    case(101):break;//PG UP
    case(103):break;//PF DN
    case(104):break;//END//掉电
  }
}

/*
轮询法发送一帧数据
消耗时间与数据长度有关
不可以放在中断里面周期性调用
LineData: 保存了摄像头图像处理后的赛道信息

void sendRoadDataToCamViewer(uint8* LineData)
{
uint8  sum=0;                                 
uint16 i,dataNumber;//注意i和dataNumer的数据类型
//使用轮询的方式发送数据，当数据未发送，程序停在此处直到发送完成
LPLD_UART_PutChar(FreeCarsUARTPort,0xFC);
LPLD_UART_PutChar(FreeCarsUARTPort,0x08);
LPLD_UART_PutChar(FreeCarsUARTPort,0xCF);
sum+=(0xFC);      //全部数据加入校验
sum+=(0x08);  
sum+=(0xCF);
dataNumber =  V;//双线模式发送的数据为ImgHeight*2
for(i=0;i<dataNumber;i++)
{
LPLD_UART_PutChar(FreeCarsUARTPort,LineData[i]);
sum += LineData[i] ;        //全部数据加入校验
  }
LPLD_UART_PutChar(FreeCarsUARTPort,sum);
}


extern uint8 BUFF[H*V];//摄像头数据，使用一维数组，加快访问速度
void sendCamImgToCamViewer(void)
{
uint16 i,j;
uint16 offset;
LPLD_UART_PutChar(FreeCarsUARTPort,0xFF);//FF,FE,FF,FE 四个数表示一幅图像的开始
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);
LPLD_UART_PutChar(FreeCarsUARTPort,0xFF);
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);
for(i = 0;i < V;i++)
{      
offset = i*H; //求得该行的偏移量
for(j = 0;j < H;j++)
{
uint8 d = BUFF[offset + j];
if(d > 0xFD) d = 0xFD;
LPLD_UART_PutChar(FreeCarsUARTPort,d);
    }
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);//FE,FE 四个数表示换行
LPLD_UART_PutChar(FreeCarsUARTPort,0xFE);
  }
j=0;
}

*/