/*@brief	File contains tools used during development and test runs.
 *@file		tool.c
 *@author	Wilhelm Nordgren
 *
 *
 */
#include "tool.h"

/*
 *@brief	Prints a string of chars over UART, adds carriage return and newline after.
 *@brief	Example: uartPrintString("Hello World!");
 *@author	Wilhelm Nordgren
 */
void uartPrintString (char out[]){

	HAL_UART_Transmit(&huart5, (uint8_t *)out, strlen(out), 500);
	char newline[2] = "\r\n";
	HAL_UART_Transmit(&huart5, (uint8_t *) newline, 2, 10);
}

/*
 * @brief	Prints an array of 8bit integers, adds carriage return and newline after.
 * 			Remember it's the ASCII table that's printed. If you want to print 1 2 3 4 5, 48 needs
 * 			to be added. Also the sizeof array must be the second argument.
 * 			Example: 	uint8_t intArray[5] = {1+48, 2+48, 3+48, 4+48, 5+48};
 *			uartPrint(intArray, sizeof(intArray));
@author		Wilhelm Nordgren
 */
void uartPrint (uint8_t out[], uint8_t length){
	HAL_UART_Transmit(&huart5, (uint8_t *)out, length, 500);
	char newline[2] = "\r\n";
	HAL_UART_Transmit(&huart5, (uint8_t *) newline, 2, 10);
}

/*
 *@brief	Sends an AT command over UART4
 *@brief	Example: ATsend("AT");
 *@author	Jesper Jansson
 */
void ATsend (char out[]){
	HAL_UART_Transmit(&huart4, (uint8_t *)out, strlen(out), 1000);
}
