/*
 * ao0_app.c
 *
 * Created: 2/4/2022 20:37:20
 *  Author: Martin Duarte
 */ 

#include "ao0_app.h"
#include "conf_app.h"
#include "af.h"
#include "stm32f3xx_hal.h"
#include "main.h"
//extern Timer_t Timer1;
//extern Timer_t Timer2;

bool ao0_app_CreatePages(void)
{
	return true;
}
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}
bool Timers_Initialize(void)
{
	//if(!TIMER_1_Init(&Timer1))
		//return false;
	
	//if (!TIMER_2_Init(&Timer2))
		//return false;
	
	return true;
}

bool ao0_appInit(void)
{
	/*	Should be placed first	*/

	/*	Initialize ST HAL	*/
	if (HAL_OK != HAL_Init())
		return false;

	/*	Initialize Application Framework I/O Pins	*/
	if (!af_io_init())
		return false;

	MX_DMA_Init();

	/*	Initialize Communication betweeen pc and nucleo board	*/
	if (!USART2_Init(DEFAULT_BAUDRATE_USART_2))
		return false;

	/*	Initialize Communication betweeen nucleo and ESP8266 module	*/
	if (!USART3_Init(DEFAULT_BAUDRATE_USART_3))
		return false;

	if(!ESP8266_Init())
		return false;

	/*	Initialize Communication betweeen LCD screen	*/
	if (!USART1_Init(DEFAULT_BAUDRATE_USART_1))
		return false;

	/*	Initialize Parser */
	if (!Parser_init())
		return false;

	//if (!swTimer_init())
		//return false;
	
	//	if (!Timers_Initialize())
	//		return false;
	//

	return true;
}

void ao0_app_setSpeakerState(MQTT_t* Message)
{
	return ao1_control_setSpeakerState(Message);
}


