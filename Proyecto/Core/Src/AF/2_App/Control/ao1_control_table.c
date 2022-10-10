/*
 * ao1_control_table.c
 *
 * Created: 4/12/2022 6:02:59 PM
 *  Author: Martin Duarte
 */ 
#include "ao1_control_table.h"
#include "ao1_control.h"

extern bool request_writeNumber (uint16_t value);
extern bool request_writeLetter (uint16_t value);
extern bool request_doNothing   (uint16_t value);

const ScreeenBehaviour_t ScreeenBehaviour[] = {
							/* Evaluate if Speaker is ONLINE	| Change IconNo		*/
	{PAGE_0, Speakers     , request_changeSpeakerState		, 0},
							/* Evaluate if Mic is ONLINE		| Change IconNo		*/
	{PAGE_0, Microphone	  , request_changeMicrophoneState	, 0},
							/* Evaluate actualPage and next page| ChangePage if necessary*/
	{PAGE_0, PagingControl, request_changePage			, 0},
							/* Evaluate button					| ChangePage if necessary*/
	{PAGE_0, Emergency	  , ao1_control_doNothing			, 0},


	//{PAGE_0, TouchControl , request_writeNumber		, 0/*ao1_control_requestChangePage_Wait*/},
	//{PAGE_0, TouchControl  , request_writeNumber		, ao1_control_doNothing},
	
	//{PAGE_1, Delete  , write_Nothing			, ao1_control_doNothing},
		
//	{PAGE_2, Letters , request_writeLetter		, ao1_control_requestChangePage_Wait},
//	{PAGE_2, Delete  , request_writeLetter		, ao1_control_doNothing},
//	{PAGE_2, Page_J_R, request_doNothing		, ao1_control_requestChangePage_Wait},
//	{PAGE_2, Page_S_Z, request_doNothing		, ao1_control_requestChangePage_Wait},
//
//	{PAGE_3, Letters , request_writeLetter		, ao1_control_requestChangePage_Wait},
//	{PAGE_3, Delete  , request_writeLetter		, ao1_control_doNothing},
//	{PAGE_3, Page_A_I, request_doNothing		, ao1_control_requestChangePage_Wait},
//	{PAGE_3, Page_S_Z, request_doNothing		, ao1_control_requestChangePage_Wait},
//
//	{PAGE_4, Letters , request_writeLetter		, ao1_control_requestChangePage_Wait},
//	{PAGE_4, Delete  , request_writeLetter		, ao1_control_doNothing },
//	{PAGE_4, Page_A_I, request_doNothing		, ao1_control_requestChangePage_Wait},
//	{PAGE_4, Page_J_R, request_doNothing		, ao1_control_requestChangePage_Wait}
};

const uint8_t TableSize = sizeof(ScreeenBehaviour)/sizeof(ScreeenBehaviour_t);

/**
 * @brief Specific application callback to write a value in application page 0.
 *
 * @param value  Incoming value to be written
 * @return true
 * @return false
 */
bool request_writeNumber(uint16_t value)
{
	uint16_t previousValue = 0;
	ao1_control_requestReadVpWait(page_ID_0_VP_ADDRESS,&previousValue);

	if(previousValue != 0)
	{
		value = (value << 8) | previousValue ;
	}

	ao1_control_requestWriteVpNoWait(page_ID_0_VP_ADDRESS,value);
	ao1_control_requestWriteVpNoWait(page_ID_2_VP_ADDRESS,0);
	HAL_Delay(10);
	ClearBufferindexes();
	return true;
}
/**
 * @brief Specific application callback to write a value in application page 2.
 *
 * @param value Incoming value to be written
 * @return true
 * @return false
 */
bool request_writeLetter(uint16_t value)
{
	ao1_control_requestWriteVpNoWait(page_ID_2_VP_ADDRESS,value);
	HAL_Delay(10);
	ClearBufferindexes();
	return true;
}
/**
 * @brief Idle function callback.
 *
 * @param value
 * @return true
 * @return false
 */
bool request_doNothing(uint16_t value)
{
	//...
	return true;
}

bool request_changeSpeakerState(uint16_t SpeakerId)
{
	ao1_control_changeSpeakerState(SpeakerId);
	HAL_Delay(10);
	ClearBufferindexes();
	return true;

}
bool request_changeMicrophoneState(uint16_t MicId)
{
	ao1_control_changeMicprophoneState(MicId);
	HAL_Delay(10);
	ClearBufferindexes();
	return true;
}

bool request_changePage(uint16_t direction)
{
	ao1_control_changePagebyButton(direction);
}
