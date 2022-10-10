/*
 * ao1_control.h
 *
 * Created: 4/3/2022 18:17:16
 *  Author: Martin Duarte
 */ 
#ifndef AO1_CONTROL_H_
#define AO1_CONTROL_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct header
{
	uint8_t header_H;
	uint8_t header_L;	
}header;
typedef struct VP_Req{
	union
	{
		struct
		{
			header header;
			uint8_t ByteCount;
			uint8_t Command;
			uint8_t VP_H;
			uint8_t VP_L;
			uint8_t Datalen;
			uint8_t Data[50];
		}req;
				
		struct 
		{
			uint16_t value;
		}resp;
		
	};
}VP_Req;

typedef struct
{
	uint16_t iconLastState[12];
}g_IconStates_t;




bool ao1_control_requestStartHandshake(void);
bool ao1_control_requestPageId(uint16_t* pageId);
bool ao1_control_waitForUserInput(void);
bool ao1_control_fetchScreen(void);
bool ao1_control_requestWriteVpNoWait(uint16_t vp_Address, uint16_t value);
bool ao1_control_requestChangePage_Wait (uint32_t pageId);
bool ao1_control_requestChangePage_NoWait (uint32_t pageId);
bool ao1_control_requestWriteStatusMessage(void);
bool ao1_control_requestSetInitialState(void);
bool ao1_control_doNothing(uint32_t value);
bool ao1_control_requestApplicationValues(void);
bool ao1_control_requestReadVpWait(uint16_t vp_Address, uint16_t* value);
bool ao1_control_fechSwTimers(void);
bool ao1_control_swTimer_enable(uint8_t TimerIndex);
bool ao1_control_swTimer_set(uint8_t TimerIndex, uint8_t Timeout_seconds);
bool ao1_control_requestWriteInitialText(void);
bool ao1_control_changeSpeakerState(uint16_t SpeakerId);
bool ao1_control_changeMicprophoneState(uint16_t SpeakerId);
bool ao1_control_changePagebyButton(uint16_t direction);
#endif /* AO1_CONTROL_H_ */
