/*
 * sw_timers.c
 *
 * Created: 5/8/2022 11:24:33 AM
 *  Author: Martin
 */ 
#include "ao1_control.h"
#include "sw_timers.h"
#include "conf_app.h"
#include "sysTimer.h"

swTimer_t Swt_Table [] =
{
/*	 Timer_Index   		-	Enable		-	Timeout_Seconds			   -	PageChange_EventHandler		-	GenericAction	*/
	{SESSION_TIMER	  ,	false		,	TIMEOUT_SESION_MILISECONDS		,ao1_control_requestChangePage_Wait	,0},
	{SERIAL_DATA_TIMER,	false		,	SERIAL_DATA_TIMEOUT_MILISECONDS	,0									,0},
	{USER_INPUT_TIMER ,	false		,	USER_INPUT_TIMEOUT_MILISECONDS	,0	,0},
};

uint8_t Swt_TableLen = sizeof(Swt_Table) / sizeof(Swt_Table[0]);

void swTimer_fetch(void)
{
	static bool firstTimeFlag = true;
	volatile static uint64_t currentTime_ms;
	volatile static uint64_t prevTime_ms;
	
	currentTime_ms = SYS_TimerGetTimeMs();
	
	volatile uint16_t diff = currentTime_ms - prevTime_ms;

	if (!firstTimeFlag)
	{
		for (int i = 0 ; i < Swt_TableLen ; i ++)
		{
			if (Swt_Table[i].Enable == true)
			{
				if(Swt_Table[i].Counter == 0)
				{
					switch(Swt_Table[i].Index)
					{
						case SESSION_TIMER:
						Swt_Table[i].TimerCb(PAGE_ID_0);
						Swt_Table[i].Enable = false;
						break;
					
						case SERIAL_DATA_TIMER:
						//Swt_Table[i].TimerCbNoArgs();
						break;
						case USER_INPUT_TIMER:
						Swt_Table[i].TimerCb(PAGE_ID_2);
						default:
						break;
					}
				}
				else
				{
					if (diff)
					{
						/*	Substract in case execution interval is greater than difference */
						if (Swt_Table[i].Counter > diff)
							Swt_Table[i].Counter -= diff;
						else
						{
							/*	Difference is bigger than execution interval this code will reload 
								Counter in terms of diff	*/
							if(Swt_Table[i].Counter < diff)
							{
								Swt_Table[i].Counter = Swt_Table[i].Counter;
							}
							else
							{
								/*	In case the difference is equal to execution interval:	*/
								Swt_Table[i].Counter += Swt_Table[i].Counter - diff;
							}
							/*	Execute inmediatly	*/
							switch(Swt_Table[i].Index)
							{
								case SESSION_TIMER:
								Swt_Table[i].TimerCb(PAGE_ID_0);
								Swt_Table[i].Enable = false;
								break;
					
								case SERIAL_DATA_TIMER:
								//Swt_Table[i].TimerCbNoArgs();
								break;
								case USER_INPUT_TIMER:
								Swt_Table[i].TimerCb(PAGE_ID_2);
								default:
								break;
							}
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
bool swTimer_init(void)
{
	/*	Timers will be enabled with swTimer_enable	function when necessary	*/
	return true;
}
bool swTimer_set(uint8_t TimerIndex)
{
	bool ret = false;
	if (TimerIndex < Swt_TableLen)
	{
		if (Swt_Table[TimerIndex].Enable == false)
			Swt_Table[TimerIndex].Enable = true;
		
		Swt_Table[TimerIndex].Counter = Swt_Table[TimerIndex].Counter;
		
		ret = true;			
	}
	return ret;
}
bool swTimer_enable(uint8_t TimerIndex)
{
	bool ret = false;
	
	if (TimerIndex <= Swt_TableLen)
	{
		if (Swt_Table[TimerIndex].Enable == false)
		{
			Swt_Table[TimerIndex].Enable = true;
		}
		ret = true;
	}
	return ret;	
}
bool swTimer_disable(uint8_t TimerIndex)
{
	if (TimerIndex < Swt_TableLen)
	{
		if (Swt_Table[TimerIndex].Enable == true)
		{
			Swt_Table[TimerIndex].Enable = false;
			return true;
		}
	}
	return false;
}
bool swTimer_isRunning(uint8_t TimerIndex)
{
	bool ret = false;
	if (TimerIndex < Swt_TableLen)
	{
		if (Swt_Table[TimerIndex].Enable == true)
		{
			if(Swt_Table[TimerIndex].Counter != 0)
				ret = true;
		}
	}
	return ret;	
}
bool swTimer_isEnable(uint8_t TimerIndex)
{
	return (Swt_Table[TimerIndex].Enable == true);
}
