/*
 * esp8266.c
 *
 *  Created on: Sep 3, 2022
 *      Author: Martin
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "esp8266.h"
#include "uart3.h"
#include "uart2.h"
#include "stm32f3xx_hal.h"
#include "conf_ATCmds.h"
#include "conf_usarts.h"


typedef enum{
	RESTORE,
	RESET_MODULE,
	AT,
	CWMODE,
	CWJAP,
	MQTTUSERCFG,
	MQTTCONN,
	MQTTSUB,
	GET_RETAIN_MESSAGES,
	CONNECTED,
}Esp8266_states_e;
Esp8266_states_e Secuence;

static void ESP_Send(char* data)
{
	_USART3_TransmitData((uint8_t*)data);
}
static void PC_Send(char* data)
{
	_USART2_TransmitData((uint8_t*)data);
}
static void ESP_readRespose(char* data, uint16_t len, uint16_t timeout)
{
	USART3_readData((uint8_t*)data, len, timeout);
}

bool ESP8266_Init(void)
{
	/*	Initialization:	*/

#ifdef USART_3_DMA_DRIVEN_MODE
	Secuence = AT;
	sm_initByDMA();
#else
	sm_initByPolling();
#endif

	return true;
}

void sm_initByDMA (void)
{
	uint8_t data[80] = {0};
	char dataWifiCfg[40]= {0};
	bool connected = false;
	while(!connected)
	{
		switch(Secuence)
		{
			case RESTORE:
			{
				memset(data,'\0',sizeof(data));
				do
				{
					PC_Send("Restore command:\r\n");
					ESP_Send("AT+RESTORE\r\n");
					HAL_Delay(5000);

				}while(!USART3_isFrameReady());
				Secuence = AT;
				USART3_getFrame(data);
				if(strstr((char*)data,"ready"))
				{
					PC_Send("ESP8266 factory reset completed\r\n");

				}
			}break;
			case RESET_MODULE:
			{
				memset(data,'\0',sizeof(data));
				do
				{
					PC_Send("Reset command:\r\n");
					ESP_Send("AT+RST\r\n");
					HAL_Delay(5000);

				}while(!USART3_isFrameReady());
				Secuence = AT;
				USART3_getFrame(data);
				//if(strstr((char*)data,"ready"))
				{
					PC_Send("ESP8266 reseted successfuly\r\n");

				}
			}break;
			case AT:
			{
				memset(data,'\0',sizeof(data));
				do
				{
					PC_Send("Sending AT command:\r\n");
					ESP_Send("AT\r\n");
					HAL_Delay(3000);

				}while(!USART3_isFrameReady());

				USART3_getFrame(data);
				if(strstr((char*)data,"AT\r\n\r\nOK\r\n"))
				{
					PC_Send("AT---->OK\r\n");
					Secuence = CWMODE;
				}
			}break;
			case CWMODE:
			{
				memset(data,'\0',sizeof(data));
				do
				{
					PC_Send("Sending CWMODE command:\r\n");
					ESP_Send("AT+CWMODE=1\r\n");
					HAL_Delay(2000);

				}while(!USART3_isFrameReady());

				USART3_getFrame(data);
				if(strstr((char*)data,"AT+CWMODE=1\r\n\r\nOK\r\n"))
				{
					PC_Send("AT+CWMODE---->OK\r\n");
					Secuence = CWJAP;
				}
			}break;
			case CWJAP:
			{
				memset(data,'\0',sizeof(data));
				do
				{
					PC_Send("Sending CWJAP command:\r\n");
					ESP_Send("AT+CWJAP=\"Tim Gabi-2.4Ghz\",\"17761395\"\r\n");
					HAL_Delay(5000);

				}while(!USART3_isFrameReady());

				USART3_getFrame(data);
				if(strstr((char*)data,"WIFI GOT IP\r\n\r\nOK\r\n"))
				{
					PC_Send("CONNECTED!\r\n");
					Secuence = MQTTUSERCFG;
				}
			}break;
			case MQTTUSERCFG:
			{
				memset(data,'\0',sizeof(data));
				do
				{
					PC_Send("Sending MQTTUSERCFG command:\r\n");
					sprintf((char*)data,"AT+MQTTUSERCFG=0,1,\"ESP8266\",\"admin\",\"admin\",0,0,\"\"\r\n");
					ESP_Send(data);
					HAL_Delay(5000);

				}while(!USART3_isFrameReady());

				USART3_getFrame(data);
				if(strstr((char*)data,"OK\r\n"))
				{
					PC_Send("MQTTUSERCFG---->OK\r\n");
					Secuence = MQTTCONN;
				}
				else if (strstr((char*)data,"ERROR"))
				{
					PC_Send("MQTTUSERCFG---->OK\r\n");
					Secuence = RESET_MODULE;
				}
			}break;
			case MQTTCONN:
			{
				memset(data,'\0',sizeof(data));
				sprintf((char*)data,"AT+MQTTCONN=0,\"192.168.1.6\",1883,0\r\n");
				do
				{
					PC_Send("Sending MQTTCONN command:\r\n");
					ESP_Send(data);
					HAL_Delay(2000);

				}while(!USART3_isFrameReady());

				USART3_getFrame(data);
				if(strstr((char*)data,"OK\r\n"))
				{
					PC_Send("MQTTCONN---->OK\r\n");
					Secuence = MQTTSUB;
				}
			}break;
			case MQTTSUB:
			{
				memset(data,'\0',sizeof(data));
				sprintf((char*)data,"AT+MQTTSUB=0,\"#\",2\r\n");
				do
				{
					PC_Send("Sending MQTTSUB command:\r\n");
					ESP_Send(data);
					HAL_Delay(2000);

				}while(!USART3_isFrameReady());

				USART3_getFrame(data);
				if(strstr((char*)data,"OK\r\n"))
				{
					PC_Send("MQTTSUB---->OK\r\n");
					//Secuence = CONNECTED;
					Secuence = CONNECTED;
				}
			}break;
			case GET_RETAIN_MESSAGES:
			{	/*	The idea was to get Retained messages here, but i could not make it. */
				do
				{
					PC_Send("Waiting Retained messages:\r\n");
					HAL_Delay(2000);
				}while(!USART3_isFrameReady());
				USART3_getFrame(data);
				if(strstr((char*)data,"RECEIVE"))
				{
					PC_Send("");
					//Secuence = CONNECTED;
					Secuence = CONNECTED;
				}
			}break;
			case CONNECTED:
			{
				PC_Send("ESP8266:Initialization finished \r\n");
				connected = true;
			} break;
		}
	}
}


void sm_initByPolling (void)
{
	uint8_t data[80] = {0};

	ESP_Send("AT+RESTORE\r\n");
	ESP_readRespose(data, sizeof(data),5000);
	if(strstr(data,"ready"))
		PC_Send("ESP8266 factory reset completed\r\n");

	HAL_Delay(1000);

	PC_Send("Sending AT command:\r\n");
	ESP_Send("AT\r\n");
	ESP_readRespose(data, sizeof(data),500);
	if(strstr(data,"OK\r\n"))
		PC_Send("AT---->OK\r\n");

	HAL_Delay(1000);
	memset(data,'\0',sizeof(data));

	ESP_Send("AT+CWMODE=1\r\n");
	ESP_readRespose(data, sizeof(data),500);
	if(strstr(data,"AT+CWMODE=1\r\n\r\nOK\r\n"))
		PC_Send("AT+CWMODE---->OK\r\n");

	HAL_Delay(2000);
	memset(data,'\0',sizeof(data));

	ESP_Send("AT+CWJAP=\"Tim Gabi-2.4Ghz\",\"17761395\"\r\n");
	ESP_readRespose(data, sizeof(data),5000);
	if(strstr(data,"WIFI GOT IP\r\n\r\nOK\r\n"))
		PC_Send("CONNECTED!\r\n");

	memset(data,'\0',sizeof(data));

	sprintf(data,"AT+MQTTUSERCFG=0,1,\"ESP8266\",\"admin\",\"admin\",0,0,\"\"\r\n");
	ESP_Send(data);
	ESP_readRespose(data, sizeof(data),500);
	if(strstr(data,"OK\r\n"))
		PC_Send("MQTTUSERCFG---->OK\r\n");

	HAL_Delay(1000);
	memset(data,'\0',sizeof(data));

	sprintf(data,"AT+MQTTCONN=0,\"192.168.1.6\",1883,0\r\n");
	ESP_Send(data);
	ESP_readRespose(data, sizeof(data),500);
	if(strstr(data,"OK\r\n"))
		PC_Send("MQTTCONN---->OK\r\n");

	HAL_Delay(1000);
	memset(data,'\0',sizeof(data));


	sprintf(data,"AT+MQTTSUB=0,\"test\",1\r\n");
	ESP_Send(data);
	ESP_readRespose(data, sizeof(data),500);
	if(strstr(data,"OK\r\n"))
		PC_Send("MQTTSUB---->OK\r\n");

	HAL_Delay(1000);
	memset(data,'\0',sizeof(data));

	sprintf(data,"AT+MQTTPUB=0,\"test\",\"ESP8266: Talking...\",2,0\r\n");
	ESP_Send(data);
	ESP_readRespose(data, sizeof(data),500);
	if(strstr(data,"OK\r\n"))
		PC_Send("MQTTPUB---->OK\r\n");

}

void ESP8266_ParserMessage(void)
{
	/*	Verify frame is ready from driver module	*/
	if(USART3_isFrameReady())
	{
		char buffer [64]= {'\0'};
		USART3_getFrame(buffer);

		MQTT_t Mqtt_Message = {0};
		  char *token,*command,*LinkID, *Topic, *DataLen,*SpeakerNumber,*Status;
		    /*
		        token: MQTTSUBRECV:0,"Speakers/",3,1:1

		        Command: MQTTSUBRECV
		        LinkID: 0
		        Topic: Speakers/
		        DataLen: 3
		        SpeakerNumber: 1
		        Status: 1
		    */

		   /* get the first token*/
		   token = strtok(buffer, "+");
		   /* */
		   command = strtok(token, ":");
		   LinkID = strtok(NULL, ",");
		   Topic = strtok(NULL, "\"/");
		   SpeakerNumber = strtok(NULL, "\",");
		   DataLen = strtok(NULL, ",");
		   Status = strtok(NULL, "\r\n");

		   Mqtt_Message.DataLen =atoi(DataLen);
		   Mqtt_Message.SpeakerNumber =atoi(SpeakerNumber);
		   Mqtt_Message.Status =atoi(Status);
		   /*	Copy command	*/

		   ao1_control_setSpeakerState(&Mqtt_Message);
		   USART3_FrameProcessed();
	}
}




