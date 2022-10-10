/*
 * tasks.c
 *
 * Created: 5/18/2022 4:16:58 PM
 *  Author: Martin
 */ 

#include "tasks.h"
#include "af.h"
#include "conf_tasks.h"
#include "af_io.h"
#include "stm32f3xx_hal.h"
#define COMPILE_ENABLE	true

typedef void (*task_handler)(void);

typedef struct task
 {
	uint16_t		executionInterval;
	bool			enable;
	task_handler	taskCb;
 }task_t;

task_t g_tasks [] = {
					{FETCH_USER_ACTIVITY_TASK_INTERVAL, COMPILE_ENABLE ,fetchUsertActivityTask},
					{FETCH_MQTT_ACTIVITY_TASK_INTERVAL, COMPILE_ENABLE ,ESP8266_ParserMessage},
					//{FETCH_MQTT_ACTIVITY,COMPILE_ENABLE, af_io_toggleUserLed}
					};

const uint8_t tasks_size = sizeof(g_tasks)/sizeof(task_t);

void run_tasks(void)
{
	static bool firstTimeFlag = true;
	volatile static uint64_t currentTime_ms;
	volatile static uint64_t prevTime_ms;
	
	currentTime_ms = SYS_TimerGetTimeMs();

	volatile uint16_t diff = currentTime_ms - prevTime_ms;

	if (!firstTimeFlag)
	{
		for (int i = 0 ; i < tasks_size ; i ++)
		{
			if (g_tasks[i].enable == COMPILE_ENABLE)
			{
				if(g_tasks[i].executionInterval == 0)
				{
					/*	Execute inmediatly	*/
					g_tasks[i].taskCb();
				}
				else
				{
					if (diff)
					{
						/*	Substract in case execution interval is greater than difference */
						if (g_tasks[i].executionInterval > diff)
							g_tasks[i].executionInterval -= diff;
						else
						{
							/*	Difference is bigger than execution interval this code will reload 
								executionInterval in terms of diff	*/
							if(g_tasks[i].executionInterval < diff)
							{
								g_tasks[i].executionInterval = g_tasks[i].executionInterval;
							}
							else
							{
								/*	In case the difference is equal to execution interval:	*/
								g_tasks[i].executionInterval += g_tasks[i].executionInterval - diff;
							}
							/*	Execute inmediatly	*/
							g_tasks[i].taskCb();
						}
					}				
				}				
			}
		}
		if(diff)
		{
			prevTime_ms = currentTime_ms;
		}			
	}
	else
	{
		prevTime_ms = currentTime_ms;
		firstTimeFlag = false;
	}
}
