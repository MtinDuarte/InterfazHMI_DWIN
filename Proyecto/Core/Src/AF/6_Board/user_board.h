/*
 * user_board.h
 *
 * Created: 26/2/2022 11:34:06
 *  Author: Martin Duarte
 */ 


#ifndef USER_BOARD_H_
#define USER_BOARD_H_
/************************************************************************/
/* Clock Definitions                                                    */
/************************************************************************/
#define FOSC 16000000 // Clock Speed 16MHz

#define B1_Pin 				GPIO_PIN_13
#define B1_GPIO_Port 		GPIOC
#define USART_TX_Pin 		GPIO_PIN_2
#define USART_TX_GPIO_Port 	GPIOA
#define USART_RX_Pin 		GPIO_PIN_3
#define USART_RX_GPIO_Port 	GPIOA
#define LD2_Pin 			GPIO_PIN_5
#define LD2_GPIO_Port 		GPIOA
#define TMS_Pin 			GPIO_PIN_13
#define TMS_GPIO_Port 		GPIOA
#define TCK_Pin 			GPIO_PIN_14
#define TCK_GPIO_Port 		GPIOA
#define SWO_Pin 			GPIO_PIN_3
#define SWO_GPIO_Port 		GPIOB


#endif /* USER_BOARD_H_ */
