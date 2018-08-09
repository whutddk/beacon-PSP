/*
name：  FreeCars上位机示波器例程
author：FreeCars军哥
Date:   2014-10-22
site:   Http://FreeCars.taobao.com
QQ群：  384273254，149168724
版权：  此代码为FreeCars上位机协议代码，允许任意使用，也允许用于商业用途，但请保留此段文字！
tips:   强烈建议小伙伴们使用FreeCars出品的蓝牙模块套装，无线上位机从这里开始！
*/

#ifndef __FREECARS_H__
#define __FREECARS_H__

//1 头文件 
#include "common.h"
#include "include.h"

#define FreeCarsUARTPort UART5
#define FreeCarsIRQ      IRQ_UART5
#define FreeCarsBR       115200       //波特率

//FreeCars上位机 串口数据显示框 接收通道数，按照上位机设置改变
#define UartDataNum      17	    

//以下不要修改
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars上位机发送浮点数据MCU接收，不要改
#define UartRxCmdLen     7	      //FreeCars上位机接收命令数据长度，不要改

#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//命令号
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//命令数据
//尽管数据的长度只要求数组长度为26=22+3+1；但是为了与发送字符串取得统一
//取数据的长度与字符串的长度相等，这样在发送数据是会多发送了一些
//无效位，但是影响不大的
typedef struct 
{
  int Stack;
  uint8 Data;
  uint8 PreData;
  uint8 Buffer[UartRxBufferLen];
  uint8 Enable;
  uint8 Check;
}SerialPortType;

extern uint8 uSendBuf[UartDataNum*2];
extern SerialPortType SerialPortRx;
extern double UartData[9];

void pcdata();
void UartDebug();
void UartCmd(uint8 cmdnum,uint8 cmddata);
void sendDataToScope();
void push(uint8 ,uint16);
void sendRoadDataToCamViewer(uint8* LineData);//发送赛道数据
void sendCamImgToCamViewer(void);//发送图像
#endif 
