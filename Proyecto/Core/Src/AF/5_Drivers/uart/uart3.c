/*
 * uart3.c
 *
 * Created: 26/2/2022 14:44:34
 *  Author: Martin Duarte
 */
#include "ring_buffer.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "uart3.h"
#include "main.h"

#include "conf_usarts.h"

static bool g_initFlag;
UART_HandleTypeDef uart3;
static uint8_t g_byte;

static struct ring_buffer g_rxBuffHandler;
static uint8_t	g_rxBuffer	[32];

#ifdef	USART3_RX_INTERRUPT_DRIVEN_MODE
void USART3_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &uart3)
	{
		ring_buffer_put(&g_rxBuffHandler, g_byte);
		//HAL_UART_Transmit(&uart3, g_byte, 1, HAL_MAX_DELAY);
		HAL_UART_Receive_IT(&uart3, &g_byte,1);
	}
}
#endif

#ifdef USART_3_DMA_DRIVEN_MODE

static bool g_FrameisReady;
DMA_HandleTypeDef hdma_usart3_rx;
#define RxBuf_SIZE 64
#define MainBuf_SIZE 64
static uint8_t RxBuf[RxBuf_SIZE];
static uint8_t MainBuf[MainBuf_SIZE];


void USART3_HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
//	if (Size < RxBuf_SIZE)
	//	{
		HAL_UART_DMAStop(&uart3);

		memcpy(MainBuf,RxBuf,sizeof(RxBuf));
		memset(RxBuf,'\0',sizeof(RxBuf_SIZE));
		g_FrameisReady = true;


		HAL_UARTEx_ReceiveToIdle_DMA(&uart3, RxBuf, RxBuf_SIZE);
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
		////}

}

#endif


/**
 * @brief USART initialization
 *
 * @param baudrate Defined baudrate - for details view conf_usarts
 * @return true
 * @return false
 */
bool USART3_Init(unsigned long baudrate)
{
	uart3.Instance = USART3;
	uart3.Init.BaudRate = baudrate;
	uart3.Init.WordLength = UART_WORDLENGTH_8B;
	uart3.Init.StopBits = UART_STOPBITS_1;
	uart3.Init.Parity = UART_PARITY_NONE;
	uart3.Init.Mode = UART_MODE_TX_RX;
	uart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart3.Init.OverSampling = UART_OVERSAMPLING_16;
	uart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&uart3) != HAL_OK)
	{
		Error_Handler();
	}

#ifdef USART_3_DMA_DRIVEN_MODE
	g_FrameisReady  = false;
	g_rxBuffHandler = ring_buffer_init(g_rxBuffer,sizeof(g_rxBuffer));
	HAL_UARTEx_ReceiveToIdle_DMA(&uart3, RxBuf, RxBuf_SIZE);
	__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
#endif

	g_initFlag = true;

	return 	g_initFlag;
}

bool USART3_EnableInterrupts(void)
{
	bool ret = false;
	if (HAL_OK == HAL_UART_Receive_IT(&uart3, &g_byte, 1))
	{
		g_rxBuffHandler = ring_buffer_init(g_rxBuffer,sizeof(g_rxBuffer));
		ret =  true;
	}
	return ret;
}


/**
 * @brief Handler for transmitting data through UART
 *
 * @param data byte
 */
void USART3_Transmitbyte (uint8_t data)
{
	/* Wait for empty transmit buffer */
	HAL_UART_Transmit(&uart3, &data, 1, 100);
}
void _USART3_TransmitData (uint8_t* data)
{
	/* Wait for empty transmit buffer */
	while(*data!='\0') USART3_Transmitbyte(*data++);
}

/**
 * @brief Handler for transmitting data through UART
 *
 * @param data byte
 */
void USART3_TransmitData (uint8_t* data, uint8_t dataLen)
{
	/* Wait for empty transmit buffer */
	HAL_UART_Transmit(&uart3, data, dataLen, HAL_MAX_DELAY);
}




/**
 * @brief Handler for reading UART and save data in a ring buffer.
 *
 * @param byte   Incoming byte
 * @return true  If byte was successfuly added to ring buffer.
 * @return false If ring buffer has no space.
 */
bool USART3_readByteNoWait(uint8_t* byte)
{
	if(ring_buffer_is_empty(&g_rxBuffHandler))
		return false;

	*byte = ring_buffer_get(&g_rxBuffHandler);

	return true;
}
bool USART3_readData(uint8_t* buffer, uint8_t len, uint16_t timeoutMs)
{
	if(HAL_OK == HAL_UART_Receive(&uart3, buffer, len, timeoutMs))
		return true;
	else
		return false;
}
bool USART3_isFrameReady(void)
{
	return g_FrameisReady;
}
void USART3_FrameProcessed(void)
{
	g_FrameisReady = false;
}
bool USART3_getFrame(uint8_t* buffer)
{
	//HAL_UART_DMAStop(&uart3);


	memcpy(buffer,MainBuf,sizeof(MainBuf));
	USART3_FrameProcessed();

	//HAL_UARTEx_ReceiveToIdle_DMA(&uart3, RxBuf, RxBuf_SIZE);
	//__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
	return true;
}



