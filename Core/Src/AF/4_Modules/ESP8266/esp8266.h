/*
 * esp8266.h
 *
 *  Created on: Sep 3, 2022
 *      Author: Martin
 */

#ifndef SRC_AF_4_MODULES_ESP8266_ESP8266_H_
#define SRC_AF_4_MODULES_ESP8266_ESP8266_H_
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 15
#define MAX_TOPIC_LENGTH 15


typedef struct {
	char Command [MAX_COMMAND_LENGTH];
	char Topic [MAX_TOPIC_LENGTH];
	uint8_t LinkID;
	int DataLen;
	int SpeakerNumber;
	int Status;
}MQTT_t;


bool ESP8266_Init(void);
void ESP8266_ParserMessage(void);
void sm_initByDMA (void);
#endif /* SRC_AF_4_MODULES_ESP8266_ESP8266_H_ */
