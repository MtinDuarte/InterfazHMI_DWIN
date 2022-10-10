/*
 * timer0.c
 *
 * Created: 20/3/2022 10:26:22
 *  Author: Martin Duarte
 */ 
#include "hw_timer.h"
#include "conf_app.h"
#include "sysTimer.h"

#include <stdbool.h>
#include <limits.h>
#include <stdint.h>


extern bool ao1_control_fechSwTimers(void);
typedef bool (*Hw_TimerCb)(void);
Hw_TimerCb fetch_SwTimerCb;

Timer_t Timer1;
Timer_t Timer2;
extern uint64_t g_sysTimerCounter;
bool Timeout_flag;

//#define OCRX_COMPARE_VALUE(interval_ms)	(uint16_t)(sysclk_get_main_hz() * interval_ms / 1000 / 2 / TIMER_1_PRESCALER - 1)

ISR(TIMER1_COMPA_vect)
{	
	g_sysTimerCounter++;
}

bool TIMER_1_Init(Timer_t* Timer)
{
	fetch_SwTimerCb = &ao1_control_fechSwTimers;
	/*	Initialize struct	*/
	Timer->Enable	= true;
	Timer->Counter	= 0;
	Timer->Index	= 1;
		

   return true;
}
bool Timer_1_Disable(void)
{
	Timer1.Enable = false;
	/*	Disable timer	*/
	return (Timer1.Enable);
}
bool Timer_1_Enable(void)
{

	Timer1.Enable = true;	
	return (Timer1.Enable == true);
}
bool Timer_1_Set(uint8_t Timeout)
{
	/*	Load timer only if it is not running */
	if(false == Timer1.Enable)
		Timer1.Enable = true;

	Timer1.Counter = Timeout;
	
	return true;
}
bool Timer_1_isRunning(void)
{
	return (true == (Timer1.Counter > 0));
}




