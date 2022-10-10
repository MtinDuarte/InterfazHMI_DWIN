/*
 * parser.h
 *
 * Created: 5/3/2022 17:10:24
 *  Author: Martin Duarte
 */ 


#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ao1_control.h"
#define HEADER_H 0x5A
#define HEADER_L 0xA5


typedef struct Serial{
	uint8_t		cmdId;
	uint16_t	address;
	uint8_t		py_wlen;
	uint16_t  	value;
}SerialData;

typedef struct Handshake_{
	
	uint8_t		cmdId;
	uint16_t	address;
	uint8_t		py_wlen;
	uint16_t  	value;
}Handshake_t;



bool Parser_init(void);
bool Parser_deInit(void);
bool Parser_getMessage(SerialData* ControlData);
bool Parser_startRequest(VP_Req* DataReq);
bool Parser_validateBoundaries(uint16_t actualPage, uint16_t* value);
bool Parser_fetchUserInteraction(void);

void ClearBufferindexes(void);


#endif /* PARSER_H_ */
