/*
 * uart1.h
 *
 * Created: 26/2/2022 14:44:50
 *  Author: Martin Duarte
 */ 


#ifndef UART1_H_
#define UART1_H_
#include <stdint.h>
#include <stdbool.h>
#include "conf_usarts1.h"

bool USART1_Init(unsigned long baudrate);
void USART1_Transmit (uint8_t data);
unsigned char USART1_Receive(void);
void USART1_Flush(void);
bool USART1_readByteNoWait(uint8_t *byte);
bool USART1_clearRingBuffer(void);


#endif /* UART1_H_ */
