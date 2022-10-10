/*
 * UART3.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Martin
 */

#ifndef SRC_AF_5_DRIVERS_UART_UART3_H_
#define SRC_AF_5_DRIVERS_UART_UART3_H_
#include <stdbool.h>
#include <stdint.h>
#include "stm32f3xx_hal.h"


bool USART3_Init(unsigned long baudrate);
void USART3_TransmitData (uint8_t* data, uint8_t dataLen);
void USART3_Transmitbyte (uint8_t data);
bool USART3_readData(uint8_t* buffer, uint8_t len, uint16_t timeoutMs);
void _USART3_TransmitData (uint8_t* data);
bool USART3_EnableInterrupts(void);
bool USART3_readByteNoWait(uint8_t* byte);
void HAL_UART3Ex_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
bool USART3_isFrameReady(void);
void USART3_FrameProcessed(void);
bool USART3_getFrame(uint8_t* buffer);
void USART3_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart, uint16_t Size);
#endif /* SRC_AF_5_DRIVERS_UART_UART3_H_ */
