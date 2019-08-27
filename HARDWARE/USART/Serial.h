/************************************************
	*	�첽�������ݵ�һ���ʽ�ǣ���ʼλ+����λ+ֹͣλ��
	*												 ������ʼΪ1λ������λ������5��6��7��8λ��ֹͣλ������1��1.5��2λ��
	*	��ʼλ��һ��ֵΪ0��λ�����Զ������߼���TTL��ƽ����ʼλ��һλʱ��ĵ͵�ƽ��
	*	ֹͣλ��ֵΪ1��λ�����Զ������߼���TTL��ƽ��ֹͣλ�Ǹߵ�ƽ�����ڸ��߼�(��RS-232��ƽ)���෴��
	*			_____  _   _   _   _   _________
	* TTL     |_| |_| |_| |_| |_|
	*          0 1 0 1 0 1 0 1 0 1 
	* ��ʼλ->| |<-            ->||<-ֹͣλ
	*
	*          _   _   _   _   _   
	* 232_____| |_| |_| |_| |_| |________
	*          0 1 0 1 0 1 0 1 0 1 0
 	* ��ʼλ ->||<-              ->||<- ֹͣλ
	*
	* 1���ֽ�Ϊ10λ��1λ��ʼλ��8λ����λ��1λֹͣλ����ռԼ1.05ms
	* ������Ϊ��10bit /1.05ms * 1000s ��9600 bit/s
	* 1֡ʱ�䳤�ȣ� 10bit *1000s / 9600(bit/s) �� 1.04167ms
	*
	* Pin˵����Tx Out_PP
	*        : Rx IPU 
**************************************************/
#ifndef __SERIAL_H
#define __SERIAL_H
#include "hal_sys.h"
#include "hal_delay.h"

#define Tx_Pin()			PAout->bit5
#define Rx_Pin()			PAin->bit6

#define EXTI_LineSerial			EXTI_Line6
#define EXTI_IRQSerial			EXTI4_15IRQn







void Serial_Rx_Init(void);
void Serial_Write_Start_Bit(uint32_t timer);
void Serial_Write_Stop_Bit(uint32_t	timer);
void Serial_Write_Data(uint8_t data,uint32_t timer);
void Serial_Write_String(uint8_t *data,uint8_t len,uint32_t timer);
uint8_t Serial_Read_Data(u32 timer);








#endif 
