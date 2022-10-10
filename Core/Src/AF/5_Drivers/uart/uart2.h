/*
 * uart2.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Martin
 */

#ifndef SRC_AF_5_DRIVERS_UART_UART2_H_
#define SRC_AF_5_DRIVERS_UART_UART2_H_
#include <stdbool.h>
#include <stdint.h>

bool USART2_Init(unsigned long baudrate);
void USART2_Transmit (uint8_t data);
void USART2_TransmitData (uint8_t* data, uint8_t dataLen);
void _USART2_TransmitData (uint8_t* data);

#endif /* SRC_AF_5_DRIVERS_UART_UART2_H_ */
