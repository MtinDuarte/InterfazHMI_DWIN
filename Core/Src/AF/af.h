/*
 * af.h
 *
 * Created: 26/2/2022 14:48:49
 *  Author: Martin Duarte
 */ 


#ifndef AF_H_
#define AF_H_


// From device
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


void fetchUsertActivityTask (void);

// From Application folder
#include "ao1_control.h"
#include "ao0_app.h"
#include "conf_app.h"
//#include "conf_tasks.h"

//
#include "ao1_control_table.h"
//
//// From Services Folder
#include "parser.h"
#include "tasks.h"

/*	From Modules folder */
#include "ESP8266.h"
//// From Drivers folder
#include "HAL_UART.h"
#include "uart1.h"
#include "uart2.h"
#include "uart3.h"
#include "hw_timer.h"
#include "sw_timers.h"
#include "sysTimer.h"
//
//// From board folder
#include "af_io.h"


//// From utils folder
//#include "ring_buffer.h"

#endif /* AF_H_ */
