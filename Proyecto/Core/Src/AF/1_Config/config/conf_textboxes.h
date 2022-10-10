/*
 * conf_textboxes.h
 *
 * Created: 4/3/2022 18:20:19
 *  Author: Martin Duarte
 */ 


#ifndef CONF_TEXTBOXES_H_
#define CONF_TEXTBOXES_H_
#include <stdint.h>

#define PAGES_DEFINED		1
#define MAX_NUMBER_OF_PAGES 10
#define SPEAKERS_PER_PAGE	12

#if (PAGES_DEFINED > MAX_NUMBER_OF_PAGES)
#error	"MAX NUMBER OF PAGES EXCEEDED";
#endif


/*  Speakers VP's */
#define SPEAKER_1_TEXT_VP   0x1500
#define SPEAKER_2_TEXT_VP   0x1550
#define SPEAKER_3_TEXT_VP   0x1600
#define SPEAKER_4_TEXT_VP   0x1650
#define SPEAKER_5_TEXT_VP   0x1700
#define SPEAKER_6_TEXT_VP   0x1750
#define SPEAKER_7_TEXT_VP   0x1800
#define SPEAKER_8_TEXT_VP   0x1850
#define SPEAKER_9_TEXT_VP   0x1900
#define SPEAKER_10_TEXT_VP   0x1950
#define SPEAKER_11_TEXT_VP   0x2000
#define SPEAKER_12_TEXT_VP   0x2050

#define SPEAKER_PAGE_COUNTER		0x2070
#define SPEAKER_SELECTION_COUNTER	0x2075
#define SPEAKER_OFFLINE_COUNTER		0x2077

/*  ICON VARIABLES VP   */
#define SPEAKER_ICON_VP_1    0x1010
#define SPEAKER_ICON_VP_2    0x1030
#define SPEAKER_ICON_VP_3    0x1050
#define SPEAKER_ICON_VP_4    0x1075
#define SPEAKER_ICON_VP_5    0x1100
#define SPEAKER_ICON_VP_6    0x1125
#define SPEAKER_ICON_VP_7    0x1150
#define SPEAKER_ICON_VP_8    0x1175
#define SPEAKER_ICON_VP_9    0x1200
#define SPEAKER_ICON_VP_10   0x1225
#define SPEAKER_ICON_VP_11   0x1250
#define SPEAKER_ICON_VP_12   0x1275
#define MICROPHONE_ICON_VP	 0x1300

#define SPEAKER_ICON_MAX	10
#define SPEAKER_ICON_MIN	0


/*  SPEAKERS_BEHAVIOUR  */
#define SPEAKER_OFFLINE						0x0000
#define SPEAKER_INACTIVE					0x0001
#define SPEAKER_SPEAKING					0x0002
#define SPEAKER_MUSIC						0x0003
#define SPEAKER_MUSIC_AND_SPEAKING			0x0004
#define SPEAKER_GROUP_INACTIVE				0x0005
#define SPEAKER_GROUP_SPEAKING				0x0006
#define SPEAKER_GROUP_MUSIC					0x0007
#define SPEAKER_GROUP_MUSIC_AND_SPEAKING	0x0008
#define SPEAKER_EMERGENCY					0x0009


/*	Microphone Behaviour	*/
#define MICROPHONE_ACTIVE	0x0002
#define MICROPHONE_ONLINE	0x0001
#define MICROPHONE_SPEAKING	0x0000

/*	Configure here speakers description	*/
char Speaker_1_Text []  = "Speaker 1";
char Speaker_2_Text []  = "Speaker 2";
char Speaker_3_Text []  = "Speaker 3";
char Speaker_4_Text []  = "Speaker 4";
char Speaker_5_Text []  = "Speaker 5";
char Speaker_6_Text []  = "Speaker 6";
char Speaker_7_Text []  = "Speaker 7";
char Speaker_8_Text []  = "Speaker 8";
char Speaker_9_Text []  = "Speaker 9";
char Speaker_10_Text [] = "Speaker 10";
char Speaker_11_Text [] = "Speaker 11";
char Speaker_12_Text [] = "Speaker 12";


char Speaker_13_Text []  = "Speaker 13";
char Speaker_14_Text []  = "Speaker 14";
char Speaker_15_Text []  = "Speaker 15";
char Speaker_16_Text []  = "Speaker 16";
char Speaker_17_Text []  = "Speaker 17";
char Speaker_18_Text []  = "Speaker 18";
char Speaker_19_Text []  = "Speaker 19";
char Speaker_20_Text []  = "Speaker 20";
char Speaker_21_Text []  = "Speaker 21";
char Speaker_22_Text []  = "Speaker 22";
char Speaker_23_Text []  = "Speaker 23";
char Speaker_24_Text []  = "Speaker 24";




const char CompanyName [] = "S U R I X";
const char Techonology [] = "Tecnologia";


#define SELECT_LETTER_VP	0x2550
const char SelectLetter[]= "*Marque Dto*";
const uint8_t Size_SLetter = sizeof(SelectLetter)/sizeof(SelectLetter[0]);

#define SELECT_NUMBER_VP	0x2500
const char SelectNumber[]= "*Marque Piso*";
const uint8_t Size_SNumber = sizeof(SelectNumber)/sizeof(SelectNumber[0]);


#define STATUS_VP			0x4000
const char Calling[]		= "Llamando...";
const uint8_t Size_Calling = sizeof(Calling)/sizeof(Calling[0]);

const char Busy[]			= "*Ocupado*";
const uint8_t Size_Busy = sizeof(Busy)/sizeof(Busy[0]);

const char Not_Available[]	= "*Invalido*";
const uint8_t Size_NotAvailable = sizeof(Not_Available)/sizeof(Not_Available[0]);


const char Connected[]	= "*Conectado*";
const uint8_t Size_Connected = sizeof(Not_Available)/sizeof(Not_Available[0]);

#endif /* CONF_TEXTBOXES_H_ */
