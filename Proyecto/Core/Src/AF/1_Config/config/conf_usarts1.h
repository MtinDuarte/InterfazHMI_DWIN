/*
 * conf_usarts1.h
 *
 * Created: 26/2/2022 16:01:45
 *  Author: Martin Duarte
 */ 


#ifndef CONF_USARTS1_H_
#define CONF_USARTS1_H_


#define BAUDRATE 9600
#define FOSC 16000000
#define MYUBBR FOSC/16/BAUDRATE-1

/************************************************************************/
/*							USART MODES                                 */
/************************************************************************/
#define USART1_RX_INTERRUPT_DRIVEN_MODE
#define ASYNCHRONOUS_USART
//#define SYNCHRONOUS_USART
//#define MASTER_SPI

/************************************************************************/
/*							PARITY										*/
/************************************************************************/
#define NO_PARITY
//#define PARITY_EVEN
//#define PARITY_ODD

/************************************************************************/
/*							STOP-BITS									*/
/************************************************************************/
#define STOP_BIT_1
//#define NO_STOP_BIT

/************************************************************************/
/*							APPLICATION SERIAL DATA						*/
/************************************************************************/
#define HEADER_H		0x5A
#define HEADER_L		0xA5

#define WRITE_REG_COMMAND		0x80
#define READ_REGISTER_COMMAND	0x81
#define WRITE_VP_COMMAND		0x82
#define READ_VP_COMMAND			0x83

#define HEADER_LENGTH		 0x02
#define COMMAND_LENGTH		 0x01
#define VP_LENGTH			 0x02
#define CHANGE_PAGE_DATACODE 0x5A01
#define RESTART_SCREEN_DATACODE	0x55AA5AA5

//#define DMA_ENABLE



#endif /* CONF_USARTS1_H_ */
