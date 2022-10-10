/*
 * main.c
 *
 * Created: 26/2/2022 19:40:38
 *  Author: Martin Duarte
 */
#include <stdbool.h>
#include "mainApp.h"
extern bool af_init(void);
extern void af_assert(void);

int mainApp (void)
{
	/*	Application framework */
	if (!af_init())
	{
		af_assert();
	}
	/* Insert application code here, after the board has been initialized. */
}
