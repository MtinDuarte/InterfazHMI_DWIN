/*
 * uart2.c
 *
 * Created: 26/2/2022 14:44:34
 *  Author: Martin Duarte
 */
#include "ring_buffer.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "uart2.h"
#include "main.h"

static bool g_initFlag;
UART_HandleTypeDef uart2;


#ifdef	USART2_RX_INTERRUPT_DRIVEN_MODE
static struct ring_buffer g_rxBuffHandler;
static uint8_t	g_rxBuffer	[32];
#endif


/**
 * @brief USART initialization
 *
 * @param baudrate Defined baudrate - for details view conf_usarts
 * @return true
 * @return false
 */
bool USART2_Init(unsigned long baudrate)
{
	uart2.Instance = USART2;
	uart2.Init.BaudRate = baudrate;
	uart2.Init.WordLength = UART_WORDLENGTH_8B;
	uart2.Init.StopBits = UART_STOPBITS_1;
	uart2.Init.Parity = UART_PARITY_NONE;
	uart2.Init.Mode = UART_MODE_TX_RX;
	uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart2.Init.OverSampling = UART_OVERSAMPLING_16;
	uart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&uart2) != HAL_OK)
	{
		Error_Handler();
	}

	//HAL_UART_Receive_IT(&uart2, &g_byte, 1);
	//g_rxBuffHandler = ring_buffer_init(g_rxBuffer,sizeof(g_rxBuffer));


	g_initFlag = true;

	return 	g_initFlag;
}

/**
 * @brief Handler for transmitting data through UART
 *
 * @param data byte
 */
void USART2_Transmit (uint8_t data)
{
	/* Wait for empty transmit buffer */
	HAL_UART_Transmit(&uart2, &data, 1, HAL_MAX_DELAY);
}


/**
 * @brief Handler for transmitting data through UART
 *
 * @param data byte
 */
void USART2_TransmitData (uint8_t* data, uint8_t dataLen)
{
	/* Wait for empty transmit buffer */
	HAL_UART_Transmit(&uart2, data, dataLen, HAL_MAX_DELAY);
}
void _USART2_TransmitData (uint8_t* data)
{
	/* Wait for empty transmit buffer */
	while(*data!='\0') USART2_Transmit(*data++);
}



/**
 * @brief Handler for reading UART and save data in a ring buffer.
 *
 * @param byte   Incoming byte
 * @return true  If byte was successfuly added to ring buffer.
 * @return false If ring buffer has no space.
 */
bool USART2_readByteNoWait(uint8_t* byte)
{
	//if (HAL_OK ==  HAL_UART_Receive(&uart2, byte, 1, HAL_MAX_DELAY))
	//	return true;
	//else
	//		return false;
	//if(ring_buffer_is_empty(&g_rxBuffHandler))
		//return false;

//	*byte = ring_buffer_get(&g_rxBuffHandler);

	return true;
}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart == &uart2)
//	{
//		//ring_buffer_put(&g_rxBuffHandler, g_byte);
//		//HAL_UART_Transmit(&uart2, g_byte, 1, HAL_MAX_DELAY);
//		//HAL_UART_Receive_IT(&uart2, &g_byte,1);
//	}
//}
