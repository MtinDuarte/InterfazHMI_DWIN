/*
 * ao1_control.c
 *
 * Created: 4/3/2022 18:16:36
 *  Author: Martin Duarte
 */ 
#include <stdlib.h>
#include <string.h>
#include "conf_usarts.h"
#include "conf_textboxes.h"
#include "conf_app.h"
#include "ao1_control.h"
#include "ao1_control_table.h"
#include "parser.h"
#include "hw_timer.h"
#include "sw_timers.h"
#include "uart1.h"
#include "stm32f3xx_hal.h"
#include "esp8266.h"

uint16_t  g_actualPage;
g_IconStates_t	g_IconStates[PAGES_DEFINED];


/************************************************************************/
/* Function Prototypes                                                  */
/************************************************************************/
static bool Send_NoWait (VP_Req *DataReq);
static bool Send_Wait (VP_Req *DataReq);

/************************************************************************/
/* Private utility functions 	                                                */
/************************************************************************/
static uint32_t ToLittleEndian (uint32_t Word)
{
	uint32_t b0,b1,b2,b3;
	uint32_t res;

	b0 = (Word & 0x000000ff) << 24u;
	b1 = (Word & 0x0000ff00) << 8u;
	b2 = (Word & 0x00ff0000) >> 8u;
	b3 = (Word & 0xff000000) >> 24u;

	res = b0 | b1 | b2 | b3;
	return res;
}
static uint16_t getSpeakerVp (uint8_t SpeakerId)
{
	switch(SpeakerId)
	{
		case Speaker_1:		return SPEAKER_ICON_VP_1;
		case Speaker_2:		return SPEAKER_ICON_VP_2;
		case Speaker_3:		return SPEAKER_ICON_VP_3;
		case Speaker_4:		return SPEAKER_ICON_VP_4;
		case Speaker_5:		return SPEAKER_ICON_VP_5;
		case Speaker_6:		return SPEAKER_ICON_VP_6;
		case Speaker_7:		return SPEAKER_ICON_VP_7;
		case Speaker_8:		return SPEAKER_ICON_VP_8;
		case Speaker_9:		return SPEAKER_ICON_VP_9;
		case Speaker_10:	return SPEAKER_ICON_VP_10;
		case Speaker_11:	return SPEAKER_ICON_VP_11;
		case Speaker_12: 	return SPEAKER_ICON_VP_12;
		default:			return 0;
	}
}
/************************************************************************/
/* Private functions	                                                */
/************************************************************************/
static bool Send_NoWait (VP_Req *DataReq)
{
	USART1_Transmit(DataReq->req.header.header_H);
	USART1_Transmit(DataReq->req.header.header_L);
	USART1_Transmit(DataReq->req.ByteCount);
	USART1_Transmit(DataReq->req.Command);
	USART1_Transmit(DataReq->req.VP_H);
	USART1_Transmit(DataReq->req.VP_L);
	for (int i = 0 ; i < DataReq->req.Datalen; i++)
	{
		USART1_Transmit(DataReq->req.Data[i]);
	}
	HAL_Delay(50);
	ClearBufferindexes();
	return true;
}
static bool Send_Wait (VP_Req *DataReq)
{
	bool ret = false;
	ClearBufferindexes();
	USART1_Transmit(DataReq->req.header.header_H);
	USART1_Transmit(DataReq->req.header.header_L);
	USART1_Transmit(DataReq->req.ByteCount);
	USART1_Transmit(DataReq->req.Command);
	USART1_Transmit(DataReq->req.VP_H);
	USART1_Transmit(DataReq->req.VP_L);
	for (int i = 0 ; i < DataReq->req.Datalen; i++)
	{
		USART1_Transmit(DataReq->req.Data[i]);
	}
	/*	As serial data is being received in ring buffer,
	this delay will give time to catch answer	*/
	HAL_Delay(100);



	if (true == Parser_startRequest(DataReq))
		ret = true;
	
	return ret;
}


static bool Request_writeVpNoWait(uint16_t vp_Address, uint16_t value)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;

	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(value);
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H =(vp_Address & 0xFF00)>>8;
	pData->req.VP_L =(vp_Address & 0xFF);
	pData->req.Datalen = sizeof(uint16_t);
	//memcpy(pData->req.Data,&value,pData->req.Datalen);
	pData->req.Data[0] = (value & 0xFF00)>>8;
	pData->req.Data[1] = (value & 0xFF);

	return  Send_NoWait(pData);
}

/* Write functions for textBoxes	                                    */
static bool Request_cleanVpAddress(uint16_t VpAddress, uint8_t length)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + length;
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H = VpAddress>>8;
	pData->req.VP_L = VpAddress & 0x00FF;
	pData->req.Datalen = length;
	return Send_NoWait(pData);
}
static bool Request_writeSelectLetter (void)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(SelectLetter);
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H = SELECT_LETTER_VP>>8;
	pData->req.VP_L = SELECT_LETTER_VP & 0x00FF;
	pData->req.Datalen = sizeof(SelectLetter);
	memcpy(pData->req.Data,SelectLetter,pData->req.Datalen);
	return Send_NoWait(pData);
}
static bool Request_writeSelectNumber(void)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
		
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(SelectNumber);
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H = SELECT_NUMBER_VP>>8;
	pData->req.VP_L = SELECT_NUMBER_VP & 0x00FF;
	pData->req.Datalen = sizeof(SelectNumber);
	memcpy(pData->req.Data,SelectNumber,pData->req.Datalen);
	return Send_NoWait(pData);
}
static bool Request_writeGenericText(uint16_t GenericVP, char* text, uint8_t length)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;

	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + length;
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H = GenericVP>>8;
	pData->req.VP_L = GenericVP & 0x00FF;
	pData->req.Datalen = length;
	memcpy(pData->req.Data,text,pData->req.Datalen);
	return Send_NoWait(pData);
}
static bool Request_writeCallingStatus(const char * Message , uint8_t length)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + length;
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H = STATUS_VP>>8;
	pData->req.VP_L = STATUS_VP & 0x00FF;
	pData->req.Datalen = length;
	memcpy(pData->req.Data,Message,pData->req.Datalen);
	return Send_NoWait(pData);
}


/* Write functions for textBoxes	                                    */
static bool Request_pageId(uint16_t* pageId)
{
	volatile bool ret;
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	uint8_t DataCode = 0x1;
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(DataCode);
	pData->req.Command = READ_VP_COMMAND;
	pData->req.VP_H =(PAGE_ID_REQUEST_CODE & 0xFF00)>>8;
	pData->req.VP_L =(PAGE_ID_REQUEST_CODE & 0xFF);
	pData->req.Datalen = sizeof(DataCode);
	memcpy(pData->req.Data,&DataCode,pData->req.Datalen);
	
	if (true ==  Send_Wait(pData))
	{
		*pageId = pData->resp.value;
		ret = true;
	}
	return ret;
}
static bool Request_firmwareVersion(void)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	uint8_t DataCode = 0x1;
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(DataCode);
	pData->req.Command = READ_VP_COMMAND;
	pData->req.VP_H =(FIRMWARE_VERSION_CODE & 0xFF00)>>8;
	pData->req.VP_L =(FIRMWARE_VERSION_CODE & 0xFF);
	pData->req.Datalen = sizeof(DataCode);
	memcpy(pData->req.Data,&DataCode,pData->req.Datalen);
	
	return Send_Wait(pData);
}
static bool Request_changePage(uint32_t PageId)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	uint32_t DataCode = CHANGE_PAGE_DATACODE;
	uint32_t Data = ( PageId << 24)					|
					((PageId	 & 0x0000FF00) << 8)|
					((DataCode   & 0x000000FF) << 8)|
					( DataCode	 >>8);
	
	pData->req.Datalen = sizeof(Data);
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(DataCode);
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H =(CHANGE_PAGE_CODE & 0xFF00)>>8;
	pData->req.VP_L =(CHANGE_PAGE_CODE & 0xFF);
	memcpy(pData->req.Data,&Data,sizeof(Data));
	return  Send_NoWait(pData);
}
static bool Request_restartScreenNoWait(void)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	uint32_t DataCode = RESTART_SCREEN_DATACODE;
	uint32_t Data = ToLittleEndian(DataCode);
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(DataCode);
	pData->req.Command = WRITE_VP_COMMAND;
	pData->req.VP_H =(RESTART_SCREEN_CODE & 0xFF00)>>8;
	pData->req.VP_L =(RESTART_SCREEN_CODE & 0xFF);
	pData->req.Datalen = sizeof(DataCode);
	memcpy(pData->req.Data,&Data,pData->req.Datalen);
	return  Send_NoWait(pData);
}
static bool Request_initialState(void)
{
	bool ret =  false;

	/*	This is the only function which waits to an answer */
	if (true == ao1_control_requestChangePage_Wait(PAGE_ID_0))
		ret = true;

	/*	These functions are noWait, answer will not be processed */
	//ao1_control_requestWriteVpNoWait(page_ID_0_VP_ADDRESS,0);
	//ao1_control_requestWriteVpNoWait(page_ID_2_VP_ADDRESS,0);
	//Request_cleanVpAddress(STATUS_VP,sizeof(uint16_t));
	//Request_writeSelectNumber();
	//Request_writeSelectLetter();
	return ret;
}
static bool Request_initialState_NoWait(void)
{
	ao1_control_requestChangePage_NoWait(PAGE_ID_0);
	ao1_control_requestWriteVpNoWait(page_ID_0_VP_ADDRESS,0);
	ao1_control_requestWriteVpNoWait(page_ID_2_VP_ADDRESS,0);
	Request_cleanVpAddress(STATUS_VP,16);
	Request_writeSelectNumber();
	Request_writeSelectLetter();
	return true;
}
static bool Request_writeFirstPageTextBoxesTittles(void)
{
	Request_writeGenericText(SPEAKER_1_TEXT_VP, Speaker_1_Text, sizeof(Speaker_1_Text));
	Request_writeGenericText(SPEAKER_2_TEXT_VP, Speaker_2_Text, sizeof(Speaker_2_Text));
	Request_writeGenericText(SPEAKER_3_TEXT_VP, Speaker_3_Text, sizeof(Speaker_3_Text));
	Request_writeGenericText(SPEAKER_4_TEXT_VP, Speaker_4_Text, sizeof(Speaker_4_Text));
	Request_writeGenericText(SPEAKER_5_TEXT_VP, Speaker_5_Text, sizeof(Speaker_5_Text));
	Request_writeGenericText(SPEAKER_6_TEXT_VP, Speaker_6_Text, sizeof(Speaker_6_Text));
	Request_writeGenericText(SPEAKER_7_TEXT_VP, Speaker_7_Text, sizeof(Speaker_7_Text));
	Request_writeGenericText(SPEAKER_8_TEXT_VP, Speaker_8_Text, sizeof(Speaker_8_Text));
	Request_writeGenericText(SPEAKER_9_TEXT_VP, Speaker_9_Text, sizeof(Speaker_9_Text));
	Request_writeGenericText(SPEAKER_10_TEXT_VP, Speaker_10_Text, sizeof(Speaker_10_Text));
	Request_writeGenericText(SPEAKER_11_TEXT_VP, Speaker_11_Text, sizeof(Speaker_11_Text));
	Request_writeGenericText(SPEAKER_12_TEXT_VP, Speaker_12_Text, sizeof(Speaker_12_Text));

	return true;
}
/* Icon functions	                                    */
static bool Request_IconState(uint16_t vp_Address, uint16_t* value)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	uint8_t data = 1;
	bool ret = false;

	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(data);
	pData->req.Command = READ_VP_COMMAND;
	pData->req.VP_H =(vp_Address & 0xFF00)>>8;
	pData->req.VP_L =(vp_Address & 0xFF);
	pData->req.Datalen = sizeof(data);
	memcpy(pData->req.Data,&data,pData->req.Datalen);
	if (true == Send_Wait(pData))
	{
		*value = (pData->resp.value);
		ret = true;
	}
	return ret;
}

/*	private program control functions	*/
static bool Fetch_userAction(void)
{
	return Parser_fetchUserInteraction();
}
/************************************************************************/
/* Public functions		                                                */
/************************************************************************/
bool ao1_control_waitForUserInput(void)
{
	return Fetch_userAction();
}
bool ao1_control_fetchScreen(void)
{
	bool screenIsResponding = false, page_fetched = false;

	do
	{
		/*	This request will ask for Screen firmware version,
			is the way to ask if the screen is responding	*/
		screenIsResponding = ao1_control_requestStartHandshake();
		
		if (screenIsResponding)
		{
			/*	Being here means screen responded with firmware version,
				this functions will set up to initial page for starting
				the application	*/

			page_fetched = ao1_control_requestPageId(&g_actualPage);

			if (g_actualPage != PAGE_ID_0)
			{
				Request_initialState();
			}
		}
	}while(screenIsResponding != true);
	
	return true;
}
bool ao1_control_requestWriteStatusMessage(void)
{
	Request_writeCallingStatus(Calling, Size_Calling);
	HAL_Delay(2500);
	Request_cleanVpAddress(STATUS_VP,16);
	Request_writeCallingStatus(Busy, Size_Busy);
	HAL_Delay(2500);
	Request_cleanVpAddress(STATUS_VP,16);
	Request_writeCallingStatus(Not_Available, Size_NotAvailable);
	HAL_Delay(2500);
	Request_cleanVpAddress(STATUS_VP,20);
	Request_writeCallingStatus(Connected,Size_Connected);
	return true;
}
bool ao1_control_requestReadVpWait(uint16_t vp_Address, uint16_t* value)
{
	VP_Req NewReq = {0};
	VP_Req* pData = &NewReq;
	uint8_t data = 1;
	bool ret = false;
	
	pData->req.header.header_H = HEADER_H;
	pData->req.header.header_L = HEADER_L;
	pData->req.ByteCount = COMMAND_LENGTH + VP_LENGTH + sizeof(data);
	pData->req.Command = READ_VP_COMMAND;
	pData->req.VP_H =(vp_Address & 0xFF00)>>8;
	pData->req.VP_L =(vp_Address & 0xFF);
	pData->req.Datalen = sizeof(data);
	memcpy(pData->req.Data,&data,pData->req.Datalen);
	if (true == Send_Wait(pData))
	{
		*value = (pData->resp.value)>> 8;
		ret = true;
	}
	return ret;
}
bool ao1_control_requestStartHandshake(void)
{	
	bool ScreenIsResponding = false;
	
	if (false == Request_firmwareVersion())
	{
		/*	Being here means screen is not responding,
			so this will try to restart screen, and repeat de process	*/
		Request_restartScreenNoWait();

		/*	To avoid continuous restarts, this delay will give time
			to the screen to recover	*/
		HAL_Delay(2000);
		ScreenIsResponding = false;
	}
	else
		ScreenIsResponding = true;

	return ScreenIsResponding;
}
bool ao1_control_requestPageId(uint16_t* pageId)
{
	return Request_pageId(pageId);
}
bool ao1_control_requestChangePage_Wait (uint32_t pageId)
{	
	uint16_t currentPage = 0;
	bool	 pageChanged = false; 
	{
		if (true == Request_pageId(&currentPage))
		{
			if (pageId != currentPage)
			{
				if (true ==  Request_changePage(pageId))
				{
					g_actualPage = pageId;
					pageChanged  = true;						
				}					
			}
		}			
	}
	return pageChanged;
}
bool ao1_control_requestChangePage_NoWait (uint32_t pageId)
{
	return Request_changePage(pageId);
}
bool ao1_control_requestWriteVpNoWait(uint16_t vp_Address, uint16_t value)
{
	return Request_writeVpNoWait(vp_Address, value);
}
bool ao1_control_changeSpeakerState(uint16_t SpeakerId)
{
	uint16_t speakerState = 0, NextState = 0, SpeakerVp = 0;
	bool ret = false;
	SpeakerVp = getSpeakerVp(SpeakerId);
	Request_IconState(SpeakerVp, &speakerState);

	if (speakerState == 0)	/*	SpeakerState is offline, don't change state	*/
		return ret;
	else if (speakerState < SPEAKER_OFFLINE || speakerState == SPEAKER_EMERGENCY )
	{
		/* Return false because icon state is out of bounds.*/
		ret = ao1_control_requestWriteVpNoWait(SpeakerVp, 1);
		return ret;
	}
	else
	{
		/* Change speaker state */
		NextState =  speakerState + 1;
		ret = ao1_control_requestWriteVpNoWait(SpeakerVp, NextState);
	}
	return ret;
}
bool ao1_control_changeMicprophoneState(uint16_t MicId)
{
	uint16_t MicrophoneState = 0, NextState = 0;
	bool ret = false;
	Request_IconState(MICROPHONE_ICON_VP, &MicrophoneState);

	if (MicrophoneState == 0 || MicrophoneState < MICROPHONE_SPEAKING || MicrophoneState > MICROPHONE_ACTIVE )
	{
		ret = ao1_control_requestWriteVpNoWait(MICROPHONE_ICON_VP, MICROPHONE_ACTIVE);
		return ret;	// Return false because icon state is out of bounds.
	}
	else
	{

		NextState =  MicrophoneState - 1;
		ret = ao1_control_requestWriteVpNoWait(MICROPHONE_ICON_VP, NextState);
	}
	return ret;
}
bool ao1_control_requestSetInitialState(void)
{
	return Request_initialState();
}
bool ao1_control_requestApplicationValues(void)
{
	uint16_t floor, apartament;
	bool ret = false;
	if (true == ao1_control_requestReadVpWait(page_ID_0_VP_ADDRESS, &floor))
	{
		if (true == ao1_control_requestReadVpWait(page_ID_2_VP_ADDRESS, &apartament))
		{
			//if(floor != 0 || apartament != 0)
			//{
				//swTimer_set(SESSION_TIMER);
			//}
			if (floor != 0 && apartament != 0) 
			{
				if (true == ao1_control_requestChangePage_Wait(PAGE_ID_1))
				{
					Request_writeCallingStatus(Calling,Size_Calling);
					HAL_Delay(3000);
					Request_writeCallingStatus(Busy,Size_Busy);
					HAL_Delay(3000);
					Request_writeCallingStatus(Not_Available,Size_NotAvailable);
					HAL_Delay(3000);
					Request_writeCallingStatus(Connected,Size_Connected);
					HAL_Delay(3000);
					ao1_control_requestSetInitialState();
					ret = true;
					//swTimer_disable(SESSION_TIMER);
				}
			}
		}
	}
	return ret;
}
bool ao1_control_doNothing(uint32_t value)
{
	// Nothing... Just return true
	return true;
}
bool ao1_control_requestWriteInitialText(void)
{
	char numberOfPages [5] = {'\0'};
	sprintf(numberOfPages,"1/%i",PAGES_DEFINED);
	char speakerSelection [5] = {"0"};
	char SpeakerOfflineCounter [3] = {"12"};

	Request_writeFirstPageTextBoxesTittles();

	Request_writeGenericText(SPEAKER_PAGE_COUNTER,numberOfPages, sizeof (numberOfPages));
	Request_writeGenericText(SPEAKER_SELECTION_COUNTER,speakerSelection, sizeof(speakerSelection));
	Request_writeGenericText(SPEAKER_OFFLINE_COUNTER,SpeakerOfflineCounter,sizeof(SpeakerOfflineCounter));

	return true;
}
bool ao1_control_setSpeakerState(MQTT_t* Message)
{
	if(Message->Status < SPEAKER_ICON_MAX && Message->Status < SPEAKER_ICON_MAX)
	{
		uint16_t status = (uint16_t) Message->Status;
		uint16_t speakerVp = getSpeakerVp(Message->SpeakerNumber);
		if(speakerVp != 0)
			ao1_control_requestWriteVpNoWait(speakerVp,status);
	}
}
bool ao1_control_changePagebyButton(uint16_t direction)
{
	char numberOfPages [4] = {'\0'};
	bool ret = false;
	if(direction == Left && g_actualPage != 0)
	{
		uint8_t nextPage = (g_actualPage + 1) - 1;
		sprintf(numberOfPages,"%i/%i",nextPage,PAGES_DEFINED);
		ret = Request_writeGenericText(SPEAKER_PAGE_COUNTER,numberOfPages, sizeof (numberOfPages));
		if(ret)
			g_actualPage -= 1;
	}
	else if (direction == Right)
	{
		if((g_actualPage + 1) == PAGES_DEFINED)
			return ret;

		uint8_t nextPage = (g_actualPage + 1) + 1;
		sprintf(numberOfPages,"%i/%i",nextPage,PAGES_DEFINED);
		ret = Request_writeGenericText(SPEAKER_PAGE_COUNTER,numberOfPages, sizeof (numberOfPages));
		if(ret)
			g_actualPage += 1;
	}

	return ret;
}


bool ao1_control_fetchButtonStates (void)
{
	uint16_t speakerState = 0, NextState = 0, SpeakerVp = 0;

	for (int page = 0 ; page< PAGES_DEFINED; page++ )
	{
		for (int SpakerId = 1; SpakerId <= SPEAKERS_PER_PAGE; SpakerId++)
		{
			g_IconStates[page].iconLastState[SpakerId - 1] = 0;
		}
	}

	for (int page = 0 ; page < PAGES_DEFINED ; page ++)
	{
		for (int SpeakerId  = 1 ; SpeakerId <= SPEAKERS_PER_PAGE; SpeakerId ++  )
		{
			SpeakerVp = getSpeakerVp(SpeakerId);
			if ( true == Request_IconState(SpeakerVp, &speakerState))
				g_IconStates[page].iconLastState[SpeakerId - 1] = speakerState;
		}
	}
	return true;
}
/************************************************************************/
/* Interfaces Functions between modules                                 */
/************************************************************************/
bool ao1_control_swTimer_set(uint8_t TimerIndex , uint8_t Timeout_seconds)
{
	bool ret = false;
	
	if (true == swTimer_enable(TimerIndex))
	{
		if (true == swTimer_set(TimerIndex))
			ret = true;
	}
	return ret;
}
bool ao1_control_swTimer_enable(uint8_t TimerIndex)
{
	if (true == swTimer_enable(TimerIndex))
		return true;
	else
		return false;
}
bool ao1_control_fechSwTimers(void)
{
	swTimer_fetch();
	return true;
}
