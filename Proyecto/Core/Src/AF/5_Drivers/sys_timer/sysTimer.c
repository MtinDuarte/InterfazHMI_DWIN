/*
 * sysTimer.c
 *
 * Created: 5/22/2022 9:28:35 AM
 *  Author: Martin Duarte
 */ 
#include "sysTimer.h"
//#include "hw_timer.h"
#include <stdint.h>
#include <stdbool.h>
#include "stm32f3xx_hal.h"
uint64_t g_sysTimerCounter;

void HAL_IncTick(void)
{
	g_sysTimerCounter++;
	uwTick += uwTickFreq;
}
uint64_t SYS_TimerGetTimeMs(void)
{
	uint32_t time;
	//irqflags_t flags;
	//flags = cpu_irq_save();
	time  = g_sysTimerCounter;
	//cpu_irq_restore(flags);
	return time;
}
void SYS_TimerHandler (void)
{
	static bool firstTimeFlag = true;
	static uint64_t elapsed_ms;	
	static uint64_t currentTime_ms;
	static uint64_t prevTime_ms;
	
	
	currentTime_ms = SYS_TimerGetTimeMs();
		
	if (false == firstTimeFlag)
	{
		currentTime_ms -= elapsed_ms;
	}
	else
	{
		prevTime_ms =  currentTime_ms;	
		firstTimeFlag = false;
	}
}
