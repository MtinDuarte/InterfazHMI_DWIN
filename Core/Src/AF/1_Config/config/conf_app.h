/*
 * conf_app.h
 *
 * Created: 24/3/2022 12:49:51
 *  Author: Martin Duarte
 */ 


#ifndef CONF_APP_H_
#define CONF_APP_H_

// Escribir 5a a5 05 82 10 10 00 01  para cambiar iconos


#define USER_INPUT_TIMEOUT_MILISECONDS  5000
#define SERIAL_DATA_TIMEOUT_MILISECONDS 3000
#define TIMEOUT_SESION_MILISECONDS	   10000
#define NUMBER_OF_PAGES			   5
#define MAXIMUM_NUMBER_OF_PAGES	   10

#if NUMBER_OF_PAGES > MAXIMUM_NUMBER_OF_PAGES
#error "Maximum number of pages exceeded"
#endif

/************************************************************************/
/* PAGEID_0_NUMBERS BOUNDARIES                                          */
/************************************************************************/
#define PAGE_ID_0					0
#define PAGE_ID_0_MIN_NUMBER		0x2E
#define PAGE_ID_0_MAX_NUMBER		0x39
#define PAGE_ID_0_SPECIAL_SYMBOL	0x2F
#define PAGE_ID_0_PB_ASCII			0x4250
#define page_ID_0_VP_ADDRESS		0x101C	

/************************************************************************/
/* PAGEID_1 Calling page BOUNDARIES		                                        */
/************************************************************************/
#define PAGE_ID_1				0x1
#define PAGE_ID_1_HUNG_UP		0x2E
/************************************************************************/
/* PAGEID_2_A_I BOUNDARIES		                                        */
/************************************************************************/
#define PAGE_ID_2				0x2
#define PAGE_ID_2_MIN_ASCII		0x41	// "A" -> ASCII
#define PAGE_ID_2_MAX_ASCII		0x49	// "I" -> ASCII
#define page_ID_2_VP_ADDRESS	0x2000	
#define PAGE_ID_2_TOPAGE_J_R	0x0040
#define PAGE_ID_2_TOPAGE_S_Z	0x003F

/************************************************************************/
/* PAGEID_3_J_R BOUNDARIES		                                        */
/************************************************************************/
#define PAGE_ID_3				0x3
#define PAGE_ID_3_MIN_ASCII		0x4A
#define PAGE_ID_3_MAX_ASCII		0x52
#define PAGE_ID_3_TOPAGE_A_I	0x003E
#define PAGE_ID_3_TOPAGE_S_Z	0x003F


/************************************************************************/
/* PAGEID_3_S_Z BOUNDARIES		                                        */
/************************************************************************/
#define PAGE_ID_4				0x4
#define PAGE_ID_4_MIN_ASCII		0x53
#define PAGE_ID_4_MAX_ASCII		0x5A
#define PAGE_ID_4_CLEAR			0x003F

/************************************************************************/
/* PAGES WILDCARDS														*/
/************************************************************************/
#define WILDCARD_CLEAR 0x2E

/************************************************************************/
/* FUNCTIONAL CODES														*/
/************************************************************************/
#define CHANGE_PAGE_CODE		0x0084
#define FIRMWARE_VERSION_CODE	0x000F
#define RESTART_SCREEN_CODE		0x0004
#define PAGE_ID_REQUEST_CODE	0x0014


#endif /* CONF_APP_H_ */
