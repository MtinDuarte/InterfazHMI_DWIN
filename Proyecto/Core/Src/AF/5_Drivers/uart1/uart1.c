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
#include "main.h"

bool g_initFlag;
bool g_uart1ByteReceived;
UART_HandleTypeDef uart1, uart2;
uint8_t g_byte;


#ifdef	USART1_RX_INTERRUPT_DRIVEN_MODE
static struct ring_buffer g_rxBuffHandler;
static uint8_t	g_rxBuffer	[32];
#endif

static void _MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}
/**
 * @brief USART initialization
 * 
 * @param baudrate Defined baudrate - for details view conf_usarts
 * @return true 
 * @return false 
 */
bool USART1_Init(unsigned long baudrate)
{

#ifdef DMA_ENABLE
	_MX_DMA_Init();
#else
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

//	uart2.Instance = USART2;
//	uart2.Init.BaudRate = 38400;
//	uart2.Init.WordLength = UART_WORDLENGTH_8B;
//	uart2.Init.StopBits = UART_STOPBITS_1;
//	uart2.Init.Parity = UART_PARITY_NONE;
//	uart2.Init.Mode = UART_MODE_TX_RX;
//	uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	uart2.Init.OverSampling = UART_OVERSAMPLING_16;
//	uart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//	uart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
//	if (HAL_UART_Init(&uart2) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	while(1)
//	{
//		HAL_UART_Transmit(&uart2,(uint8_t*)"UART_INITIALIZED!\r\n",sizeof("UART_INITIALIZED!\r\n"),HAL_MAX_DELAY);
//		HAL_Delay(1000);
//	}


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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &uart1)
	{
		ring_buffer_put(&g_rxBuffHandler, g_byte);
		//HAL_UART_Transmit(&uart2, g_byte, 1, HAL_MAX_DELAY);
		HAL_UART_Receive_IT(&uart1, &g_byte,1);
	}
}

