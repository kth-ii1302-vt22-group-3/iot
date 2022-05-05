/*
 * @brief	Headerfile for tool.c
 * @file	tool.h
 * @author	Wilhelm Nordgren
 *
 */

#include "usart.h"
#include <string.h>

#define rxBufferSize 128
#define maxTimeout 1000

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;

void uartPrintString (char out[]);
void uartPrint (uint8_t out[],uint8_t length);
void ATsend (char out[]);
void UARTtransmit_IT (uint8_t *data, uint8_t size);
void UARTreceiveIT(UART_HandleTypeDef *huart);
