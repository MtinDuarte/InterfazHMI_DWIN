/*
 * ao0_app.h
 *
 * Created: 2/4/2022 20:32:05
 *  Author: Martin Duarte
 */ 


#ifndef AO0_APP_H_
#define AO0_APP_H_
#include <stdint.h>
#include <stdbool.h>

typedef struct 
{
	union
	{
		struct 
		{
			uint8_t firstNumber;
			uint8_t lastNumber;		
		}numbers;	
		
		struct 
		{
			uint16_t min_ASCIIValue;
			uint16_t max_ASCIIValue;			
		}letters;
	};
	uint16_t clearEntry;
	uint16_t specialSymbol;
}pageParameters;


typedef struct app_pages
{
	uint8_t pageId;
	pageParameters	pageContent;
}CreatePage;

bool ao0_app_CreatePages(void);
bool ao0_appInit(void);

#endif /* AO0_APP_H_ */
