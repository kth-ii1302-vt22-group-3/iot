/*
 * UartReceive.h
 *
 *  Created on: 16 May 2022
 *      Author: natashadonner
 */


#include <string.h>
#include "usart.h"

#define BUFFER_SIZE 20

void init(void);
void USER_UART_IDLECallback(UART_HandleTypeDef *huart);
void getResponse(void);
