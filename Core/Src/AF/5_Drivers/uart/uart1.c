/*
 * uart1.c
 *
 * Created: 26/2/2022 14:44:34
 *  Author: Martin Duarte
 */ 
#include "ring_buffer.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "uart1.h"
#include "stm32f3xx_hal.h"
#include "main.h"

static bool g_initFlag;
UART_HandleTypeDef uart1;

static uint8_t g_byte;
static struct ring_buffer g_rxBuffHandler;
static uint8_t	g_rxBuffer	[32];


#ifdef	USART_1_DMA_DRIVEN_MODE
	DMA_HandleTypeDef hdma_usart1_rx;
	#define RxBuf_SIZE 64
	#define MainBuf_SIZE 64
	static uint8_t RxBuf[RxBuf_SIZE];
	static uint8_t MainBuf[MainBuf_SIZE];


	void USART1_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart, uint8_t bufferLen)
	{
		if(huart == &uart1)
		{
			memcpy(MainBuf,RxBuf,bufferLen);
			  for (int i = 0 ; i < bufferLen; i ++)
					ring_buffer_put(&g_rxBuffHandler, MainBuf[i]);

		  HAL_UARTEx_ReceiveToIdle_DMA(&uart1, RxBuf, RxBuf_SIZE);
		  __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
		}
	}
#endif

#ifdef USART1_RX_INTERRUPT_DRIVEN_MODE
	void USART1_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	{
		if(huart == &uart1)
		{
			ring_buffer_put(&g_rxBuffHandler, g_byte);
			//HAL_UART_Transmit(&uart2, g_byte, 1, HAL_MAX_DELAY);
			HAL_UART_Receive_IT(&uart1, &g_byte,1);
		}
	}
#endif







/**
 * @brief USART initialization
 * 
 * @param baudrate Defined baudrate - for details view conf_usarts
 * @return true 
 * @return false 
 */
bool USART1_Init(unsigned long baudrate)
{


	uart1.Instance = USART1;
	uart1.Init.BaudRate = baudrate;
	uart1.Init.WordLength = UART_WORDLENGTH_8B;
	uart1.Init.StopBits = UART_STOPBITS_1;
	uart1.Init.Parity = UART_PARITY_NONE;
	uart1.Init.Mode = UART_MODE_TX_RX;
	uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart1.Init.OverSampling = UART_OVERSAMPLING_16;
	uart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&uart1) != HAL_OK)
	{
		Error_Handler();
	}

	#ifdef USART_1_DMA_DRIVEN_MODE
		g_rxBuffHandler = ring_buffer_init(g_rxBuffer,sizeof(g_rxBuffer));
		 HAL_UARTEx_ReceiveToIdle_DMA(&uart1, RxBuf, RxBuf_SIZE);
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
	#else
		HAL_UART_Receive_IT(&uart1, &g_byte, 1);
		g_rxBuffHandler = ring_buffer_init(g_rxBuffer,sizeof(g_rxBuffer));
	#endif

	g_initFlag = true;
	
	return 	g_initFlag;
}

/**
 * @brief Handler for transmitting data through UART
 * 
 * @param data byte
 */
void USART1_Transmit (uint8_t data)
{
	/* Wait for empty transmit buffer */
	HAL_UART_Transmit(&uart1, &data, 1, HAL_MAX_DELAY);
}


void USART1_TransmitData(uint8_t* data)
{
	/* Wait for empty transmit buffer */
	while(*data!='\0') USART1_Transmit(*data++);

	//HAL_UART_Transmit(&uart1, &data, 1, HAL_MAX_DELAY);
}

/**
 * @brief Handler for reading UART and save data in a ring buffer.
 * 
 * @param byte   Incoming byte
 * @return true  If byte was successfuly added to ring buffer.
 * @return false If ring buffer has no space.
 */
bool USART1_readByteNoWait(uint8_t* byte)
{
	//if (HAL_OK ==  HAL_UART_Receive(&uart1, byte, 1, HAL_MAX_DELAY))
	//	return true;
	//else
	//		return false;
	if(ring_buffer_is_empty(&g_rxBuffHandler))
		return false;

	*byte = ring_buffer_get(&g_rxBuffHandler);

	return true;
}
/**
 * @brief Handler for clearing ring buffer
 *
 * @return true
 * @return false
 */
bool USART1_clearRingBuffer(void)
{
	ring_buffer_clear(&g_rxBuffHandler);
	return true;
}


