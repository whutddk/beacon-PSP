/*
name��  FreeCars��λ��ʾ��������
author��FreeCars����
Date:   2014-10-22
site:   Http://FreeCars.taobao.com
QQȺ��  384273254��149168724
��Ȩ��  �˴���ΪFreeCars��λ��Э����룬��������ʹ�ã�Ҳ����������ҵ��;�����뱣���˶����֣�
tips:   ǿ�ҽ���С�����ʹ��FreeCars��Ʒ������ģ����װ��������λ�������￪ʼ��
*/

#ifndef __FREECARS_H__
#define __FREECARS_H__

//1 ͷ�ļ� 
#include "common.h"
#include "include.h"

#define FreeCarsUARTPort UART5
#define FreeCarsIRQ      IRQ_UART5
#define FreeCarsBR       115200       //������

//FreeCars��λ�� ����������ʾ�� ����ͨ������������λ�����øı�
#define UartDataNum      17	    

//���²�Ҫ�޸�
#define UartRxBufferLen  100
#define UartRxDataLen    41           //FreeCars��λ�����͸�������MCU���գ���Ҫ��
#define UartRxCmdLen     7	      //FreeCars��λ�������������ݳ��ȣ���Ҫ��

#define UartCmdNum  SerialPortRx.Buffer[SerialPortRx.Stack-3]//�����
#define UartCmdData SerialPortRx.Buffer[SerialPortRx.Stack-2]//��������
//�������ݵĳ���ֻҪ�����鳤��Ϊ26=22+3+1������Ϊ���뷢���ַ���ȡ��ͳһ
//ȡ���ݵĳ������ַ����ĳ�����ȣ������ڷ��������ǻ�෢����һЩ
//��Чλ������Ӱ�첻���
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
void sendRoadDataToCamViewer(uint8* LineData);//������������
void sendCamImgToCamViewer(void);//����ͼ��
#endif 
