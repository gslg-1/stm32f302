#ifndef __DBG_FIRST_H
#define __DBH_FIRST_H

#include "stm32f3xx_hal.h"


void readDBGCommand( char * const rxBuffer[] , UART_HandleTypeDef * const hUart );
void executeDBGCommand( char * const rxBuffer[], char * const txBuffer[] );
void executeDBGCommand( char * const buffer[], UART_HandleTypeDef * const hUart );



#endif