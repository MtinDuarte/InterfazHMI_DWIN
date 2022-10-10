/*
 * sw_timers.h
 *
 * Created: 5/8/2022 11:24:44 AM
 *  Author: Martin Duarte
 */ 


#ifndef SW_TIMERS_H_
#define SW_TIMERS_H_

typedef bool(*Sw_TimerCallback)(uint32_t arg);
typedef bool(*Sw_TimerCallbackNoArgs)(void);


typedef struct{
	uint8_t						Index;
	bool						Enable;
	uint64_t					Counter;
	Sw_TimerCallback			TimerCb;
	Sw_TimerCallbackNoArgs		TimerCbNoArgs;
	
}swTimer_t;

enum TimerIndex
{
	/**/
	SESSION_TIMER,
	SERIAL_DATA_TIMER,
	USER_INPUT_TIMER,
	USER_FETCH_TIMER,
};

void swTimer_fetch(void);
bool swTimer_init(void);
bool swTimer_set(uint8_t TimerIndex);
bool swTimer_enable(uint8_t TimerIndex);
bool swTimer_disable(uint8_t TimerIndex);
bool swTimer_isRunning(uint8_t TimerIndex);
bool swTimer_isEnable(uint8_t TimerIndex);
#endif /* SW_TIMERS_H_ */