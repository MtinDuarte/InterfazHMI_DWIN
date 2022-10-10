/*
 * af.c
 *
 * Created: 26/2/2022 19:39:37
 *  Author: Martin Duarte
 */ 
#include "af.h"
// Function prototypes
bool af_init(void);
void af_assert (void);
extern uint8_t g_actualPage;

/**
 * @brief Application framework initialization
 * 		  This application runs the main program.
 * @return true 
 * @return false 
 */
bool af_init(void)
{
	
	/*	Application object initialization	*/	
	if (!ao0_appInit())
		return false;

	/*	Try communicating with screen	*/	
	if (!ao1_control_fetchScreen())
		return false;

	if (!ao1_control_fetchButtonStates())
		return false;
	
	if (!ao1_control_requestWriteInitialText())
		return false;

	while (true)
	{
		ESP8266_ParserMessage();
		//run_tasks();
		fetchUsertActivityTask();
		/*	Wait for user interaction */
	}
	return true;
}
void fetchUsertActivityTask (void)
{
	if (true == ao1_control_waitForUserInput())
	{
		//ao1_control_requestApplicationValues();
	}	
}

void af_assert(void)
{
	while(true)
	{
		/*	flag here error for example light a led */
		af_io_signalError();
	}

}
