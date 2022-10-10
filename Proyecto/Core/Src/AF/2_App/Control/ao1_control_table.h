/*
 * ao1_control_table.h
 *
 * Created: 4/11/2022 4:17:58 PM
 *  Author: Martin Duarte
 */ 


#ifndef AO1_CONTROL_TABLE_H_
#define AO1_CONTROL_TABLE_H_
#include "af.h"

/** Tidy way of saying "reference to a function that "receives nothing and returns nothing"
* For example, if you have a function named "void doSomething()", you can create a variable
* like this one:
*  Runnable_t myFunctionReference = doSomething;
* And then you can pass myFunctionReference to #initDebounceFSM for it to be run when
* a TEC key is pressed.
*/

/** States */
typedef enum {
	PAGE_0,
	PAGE_1,
	PAGE_2,
	PAGE_3,
	PAGE_4,
} Page_t;

/** States */
typedef enum {
	Speaker_1 = 0x0001, Speaker_2 = 0x0002, Speaker_3 = 0x0003, Speaker_4 = 0x0004,
	Speaker_5 = 0x0005, Speaker_6 = 0x0006, Speaker_7 = 0x0007,	Speaker_8 = 0x0008,
	Speaker_9 = 0x0009, Speaker_10= 0x000A, Speaker_11= 0x000B,	Speaker_12 = 0x000C,
	Mic		  = 0x000D, Back= 0x000E,		Next= 0x0010,	   	Alarm = 0x0011,
							Selection = 0x000F,
} Entity_t;

typedef enum {
	Left = 0x000E,
	Right = 0x0010,
}PageDirection_t;

/** Events that can occur */
typedef enum {
	Speakers 		= 0x2100,
	Microphone		= 0x2101,
	PagingControl	= 0x2102,
	Emergency		= 0x2103
} VP_t;

typedef bool (*ExecFuncCb)(uint16_t value);
typedef bool (*ControlFuncCb) (uint32_t PageId);
typedef void (*postActionFunc)(void);
typedef struct {
	// This reads as follows :
	Page_t			Page;		// If I'm in this state...
	VP_t			Address;	// ... and this event occurs
	//Entity_t		Button;
	ExecFuncCb		FunctionCb;	// ... execute this function callback
	ControlFuncCb   ControlCb;	// ... and finally this control callback function
} ScreeenBehaviour_t;

/////////////////////////////////////////////////////////////////////////////////////
typedef struct {
	// This reads as follows :
	VP_t			Address;	// ... and this event occurs
	Entity_t		Button;
	ExecFuncCb		FunctionCb;	// ... execute this function callback
	ControlFuncCb ControlCb;	// ... and finally this control callback function
} ScreeenStates_t;

bool request_changeMicrophoneState(uint16_t value);
bool request_writeNumber(uint16_t value);
bool request_writeLetter(uint16_t value);
bool request_doNothing(uint16_t value);
bool request_changeSpeakerState(uint16_t value);
bool request_changePage(uint16_t direction);

#endif /* AO1_CONTROL_TABLE_H_ */
