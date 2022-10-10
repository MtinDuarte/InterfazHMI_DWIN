/*
 * timer0.h
 *
 * Created: 20/3/2022 10:26:35
 *  Author: Martin Duarte
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct{
	bool Enable;
	uint8_t Counter;
	uint8_t Index;
	//uint8_t Timeout;
}Timer_t;


#define TIMER_1_PRESCALER_8
#define TIMER_1_PRESCALER	8
#define TIMER_1_INTERVAL_MS	20



bool TIMER_1_Init(Timer_t* Timer);
bool Timer_1_Clear(void);
bool Timer_1_Disable(void);
bool Timer_1_Enable(void);
bool Timer_1_Set(uint8_t Timeout);
bool hwTimer_init(void);
bool Timer_1_isRunning(void);

#endif /* TIMER1_H_ */