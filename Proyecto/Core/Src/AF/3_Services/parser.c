/*
 * parser.c
 *
 * Created: 5/3/2022 17:10:13
 *  Author: Martin Duarte
 */ 
#include "uart1.h"
#include "parser.h"
#include "conf_app.h"
#include "ao1_control_table.h"
#include "ao1_control.h"
#include "stm32f3xx_hal.h"

extern const ScreeenBehaviour_t ScreeenBehaviour[];
extern const uint8_t TableSize;

/*Globals	*/
/**
 * @brief UART parser finite state machine states.
 * 
 */
static enum MEF_STATE{
			IDLE
	,		WAITING_FOR_HEADER_H
	,		WAITING_FOR_HEADER_L
	, 		WAITING_FOR_BYTE_COUNT
	,		WAITING_FOR_COMMAND
	,		WAITING_FOR_ADDRESS
	,		WAITING_PY_WORD_LEN
	,		WAITING_FOR_PAYLOAD
//	, 		WAITING_FOR_CRC
}Secuence;


static bool g_uartInitflag;
static uint8_t  uart2_buf[100];


//extern Timer_t Timer1;
extern uint8_t byteReceived;
extern bool g_uart1ByteReceived;
extern bool Timeout_flag;
extern uint16_t  g_actualPage;

/**
 * @brief HAL for clearing buffer indexes.
 * 
 */
void ClearBufferindexes(void)
{
	USART1_clearRingBuffer();
	//memset(uart2_buf,0,sizeof(uart2_buf));
	Secuence = WAITING_FOR_HEADER_H;
}
/**
 * @brief Initialization of parser MEF.
 * This function will initialize parser state machine waiting for header (0x5A)
 * of a new incoming message.
 * 
 * @return true 
 * @return false 
 */
bool Parser_init(void)
{
	Secuence = WAITING_FOR_HEADER_H;
	return true;
}
/**
 * @brief De-initialization of parser + Uart channel
 * This handler de-init parser service. 
 * @return true 
 * @return false 
 */
bool Parser_deInit(void)
{
	Secuence = IDLE;
	g_uartInitflag = false;
	return true;
}
/**
 * @brief Handler for receiving incoming data
 * 
 * @param ControlData Structure pointer of the resulting message
 * @return true 
 * @return false 
 */
bool Parser_getMessage(SerialData* ControlData)
{
	uint8_t buff;
	static volatile uint8_t i, length, addr_flag=0;
	bool MsgRcv = false;
	static bool keepGoing = true;
	volatile bool Timeout = false;
	
	
	while ( (keepGoing = USART1_readByteNoWait(&buff)) && MsgRcv == false && !Timeout)
	{
//		if(false == swTimer_isRunning(TIMEOUT_TIMER) && true == swTimer_isEnable(TIMEOUT_TIMER))
//		{
//			Timeout = true;
//			ClearBufferindexes();
//			break;
//		}
//		else if(false == swTimer_isRunning(SESSION_TIMER) && true == swTimer_isEnable(SESSION_TIMER))
//		{
//			Timeout = true;
//			ao1_control_requestSetInitialState();
//			break;
//		}
			switch (Secuence)
			{
				case IDLE:
				/*	Do nothing */
				break;

				case WAITING_FOR_HEADER_H:
				{
					//if (true == USART1_readByteNoWait(&buff))
					{
						if (buff == HEADER_H)
						{
							uart2_buf[i] = buff;
							i++;
							Secuence = WAITING_FOR_HEADER_L;
							//swTimer_set(TIMEOUT_TIMER);
						}
					}
					break;
				}
				case WAITING_FOR_HEADER_L:
				{
					//if (true == USART1_readByteNoWait(&buff))
						{
							if (buff == HEADER_L)
							{
								uart2_buf[i] = buff;
								i++;
								Secuence = WAITING_FOR_BYTE_COUNT;
								//swTimer_set(TIMEOUT_TIMER);
							}
							else
							{
								Secuence = WAITING_FOR_HEADER_H;
								ClearBufferindexes();
								i = 0;
							}
						}
						break;
				}
				case WAITING_FOR_BYTE_COUNT:
				{
					//if (true == USART1_readByteNoWait(&buff))
					{
						//USART1_readByteNoWait(&buff);
						length = buff;
						uart2_buf[i] = buff;
						i++;
						Secuence = WAITING_FOR_COMMAND;
						//swTimer_set(TIMEOUT_TIMER);
					}
					break;
				}
				case WAITING_FOR_COMMAND:
				{
					//if (true == USART1_readByteNoWait(&buff))
					{
						if (buff == WRITE_VP_COMMAND ||
							buff == READ_VP_COMMAND	 ||
							buff == WRITE_REG_COMMAND||
							buff == READ_REGISTER_COMMAND)
						{
							uart2_buf[i] = buff;
							i++;
							length--;
							ControlData->cmdId = buff;
							Secuence = WAITING_FOR_ADDRESS;
							//swTimer_set(TIMEOUT_TIMER);
						}
						else
						{
							ClearBufferindexes();
							Secuence = WAITING_FOR_HEADER_H;
							i = 0;
						}
					}
					break;
				}
				case WAITING_FOR_ADDRESS:
				{
					//if (true == USART1_readByteNoWait(&buff))
					{
						if (addr_flag == 0)
						{
							uart2_buf[i] = buff;
							i++;
							length--;
							ControlData->address = buff << 8;
							addr_flag = 1;	// flag first time
							//swTimer_set(TIMEOUT_TIMER);
						}
						else
						{
							//swTimer_set(TIMEOUT_TIMER);
							addr_flag = 0;
							uart2_buf[i] = buff;
							i++;
							ControlData->address |= buff;
							Secuence = WAITING_PY_WORD_LEN;
							length--;
						}
					}
					break;
				}
				case WAITING_PY_WORD_LEN:
				{
					//if (true == USART1_readByteNoWait(&buff))
					{
						//swTimer_set(TIMEOUT_TIMER);
						uart2_buf[i] = buff;
						ControlData->py_wlen = buff;
						Secuence = WAITING_FOR_PAYLOAD;
						length--;
						i++;
					}
					break;
				}
				case WAITING_FOR_PAYLOAD:
				{
					//if (true == USART1_readByteNoWait(&buff))
					{
						//swTimer_set(TIMEOUT_TIMER);
						uart2_buf[i] = buff;
						i++;

						if (length > 1)
						{
							ControlData->value = ((uint16_t)buff << 8);
							length--;
						}
						else
						{
							// Process last data in uart buffer
							ControlData->value |= buff;
							// Set MEF to first state:
							//swTimer_disable(TIMEOUT_TIMER);
							ClearBufferindexes();
							Secuence = WAITING_FOR_HEADER_L;
							length=0;
							i = 0;
							MsgRcv = true;
						}
					}
					break;
				}
				default:
					break;
			}
		}
		return MsgRcv;
}
/**
 * @brief Handler function to validate incoming data of each page
 * For the application, each page will have data boundaries, 
 * if the corresponding page doesn't meet the required boundaries,
 * skip executing application function handlers. 
 * 
 * @param actualPage Actual page refreshed by the device
 * @param value 	 Value sent by the device
 * @return true 	 The value is within the boundaries
 * @return false 	 The value is out of boundaries.
 */
bool Parser_validateBoundaries(uint16_t actualPage, uint16_t* value)
{
	bool valueOK = false;
	switch (actualPage)
	{
		case PAGE_ID_0:
		if(*value >= PAGE_ID_0_MIN_NUMBER	&&
			*value <= PAGE_ID_0_MAX_NUMBER)
		{				
			if (*value == PAGE_ID_0_SPECIAL_SYMBOL)
				*value = 0x4250;
					
			valueOK = true;  
		}break;	
		case PAGE_ID_1:
		{
			if (*value == PAGE_ID_1_HUNG_UP)
				valueOK = true;
		}break;
		case PAGE_ID_2:
		{
			if(*value >= PAGE_ID_2_MIN_ASCII	&&
			   *value <= PAGE_ID_2_MAX_ASCII)
			{
				valueOK = true;  
			}		
		}break;
		case PAGE_ID_3:
		if(*value >= PAGE_ID_3_MIN_ASCII	&&
			*value <= PAGE_ID_3_MAX_ASCII)
		{
			valueOK = true;  
		}break;		
		case PAGE_ID_4:
		if(*value >= PAGE_ID_4_MIN_ASCII	&&
			*value <= PAGE_ID_4_MAX_ASCII)
		{
			valueOK = true;  
		}break;
		default:
			break;
	}
	if (*value == PAGE_ID_2_TOPAGE_J_R || *value == PAGE_ID_2_TOPAGE_S_Z)
	{
		valueOK = true;
	}
	else if (*value == WILDCARD_CLEAR)
	{
		*value = 0;
		 valueOK = true;
	}
				
	return valueOK;
}

/**
 * @brief Parser function handler to Request an action to the device
 * This function executes a query to the device exepecting a response
 * with timeout.
 * 
 * @param timeout Maximium timeout of the query
 * @param DataReq Structure pointer where incoming data will be saved
 * @return true   Response successfuly received
 * @return false  Timeout expired
 */
bool Parser_startRequest(VP_Req *DataReq)
{
	bool MsgReceived = false;
	SerialData ControlData = {0};
	
	//swTimer_set(TIMEOUT_TIMER);
		
	if (true == Parser_getMessage(&ControlData))
	{
		DataReq->resp.value = ControlData.value;
		MsgReceived = true;
	}

	return MsgReceived;						
}
/**
 * @brief Main function handler for waiting for user interaction with the device
 * This function waits for a response, validates boundaries of the incoming 
 * response and executes control/execution callbacks according to a table.
 * @return true   
 * @return false 
 */
bool Parser_fetchUserInteraction(void)
{
	SerialData ControlData;
	bool ret = false;
	Secuence = WAITING_FOR_HEADER_H;

	if (true == Parser_getMessage(&ControlData))
	{
		/*	Initialize/Restart Session Timer because of user interaction */
		//swTimer_set(TIMEOUT_TIMER);

			for (int i = 0 ; i < TableSize; i ++)
			{
				//if (ScreeenBehaviour[i].Page == g_actualPage)				// ... if we are in this page
				{
					if (ScreeenBehaviour[i].Address == ControlData.address) // .. and we received a message with this address
					{
						switch (ControlData.address)						// .. identify address
						{													// .. PageControl addresses.
							case Speakers:
								ScreeenBehaviour[i].FunctionCb(ControlData.value);
								break;
							case Microphone:
								ScreeenBehaviour[i].FunctionCb(ControlData.value);
								break;
							case PagingControl:
								ScreeenBehaviour[i].FunctionCb(ControlData.value);
								break;
							case Emergency:
								break;
							default:										// .. Execution addresses
								//(ScreeenBehaviour[i].FunctionCb)(ControlData.value);
							break;
						}
						/*	if the current page is 0, catch the case of 2 digits input and swap page */
						ret = true;
						break;
					}
				}
			}
	}
	return ret;
}


