/*
 * HAL_UART.c
 *
 *  Created on: Sep 15, 2022
 *      Author: Martin
 */
#include "HAL_UART.h"
#include "uart1.h"
#include "uart3.h"
#include "main.h"
#include "conf_usarts.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef uart1;
extern UART_HandleTypeDef uart3;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart->Instance == USART3 && huart->RxState == HAL_UART_STATE_READY)
  {
	#ifdef USART_3_DMA_DRIVEN_MODE
		  USART3_HAL_UART_RxCpltCallback(&uart3, Size);
	#else
		  USART3_HAL_UART_RxCpltCallback(&uart3);
	#endif
  }
  if (huart->Instance == USART1 && huart->RxState == HAL_UART_STATE_READY)
  {
	#ifdef USART_1_DMA_DRIVEN_MODE
		  USART1_HAL_UART_RxCpltCallback(&uart1, Size);
	#else
		  USART1_HAL_UART_RxCpltCallback(&uart1);
	#endif
  }
}
