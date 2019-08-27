/************************************************
	*	异步串行数据的一般格式是：起始位+数据位+停止位，
	*												 其中起始为1位，数据位可以是5、6、7、8位，停止位可以是1、1.5、2位。
	*	起始位是一个值为0的位，所以对于正逻辑的TTL电平，起始位是一位时间的低电平；
	*	停止位是值为1的位，所以对于正逻辑的TTL电平，停止位是高电平。对于负逻辑(如RS-232电平)则相反。
	*			_____  _   _   _   _   _________
	* TTL     |_| |_| |_| |_| |_|
	*          0 1 0 1 0 1 0 1 0 1 
	* 起始位->| |<-            ->||<-停止位
	*
	*          _   _   _   _   _   
	* 232_____| |_| |_| |_| |_| |________
	*          0 1 0 1 0 1 0 1 0 1 0
 	* 起始位 ->||<-              ->||<- 停止位
	*
	* 1个字节为10位（1位起始位、8位数据位、1位停止位）共占约1.05ms
	* 波特率为：10bit /1.05ms * 1000s ≈9600 bit/s
	* 1帧时间长度： 10bit *1000s / 9600(bit/s) ≈ 1.04167ms
	*
	* Pin说明：Tx Out_PP
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
