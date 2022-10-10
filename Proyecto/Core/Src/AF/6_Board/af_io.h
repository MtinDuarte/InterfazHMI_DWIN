/*
 * af_io.h
 *
 * Created: 26/2/2022 11:28:25
 *  Author: Martin Duarte
 */ 


#ifndef AF_IO_H_
#define AF_IO_H_
#include <stdbool.h>


bool af_io_init(void);
void af_io_signalError(void);
void af_io_toggleUserLed(void);

#endif /* AF_IO_H_ */
