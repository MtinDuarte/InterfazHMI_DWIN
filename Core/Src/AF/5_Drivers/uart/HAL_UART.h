/*
 * HAL_UART.h
 *
 *  Created on: Sep 15, 2022
 *      Author: Martin
 */

#ifndef SRC_AF_5_DRIVERS_UART_HAL_UART_H_
#define SRC_AF_5_DRIVERS_UART_HAL_UART_H_
#include "stm32f3xx_hal.h"
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);

#endif /* SRC_AF_5_DRIVERS_UART_HAL_UART_H_ */
