/*@brief	File contains tools used during development and test runs.
 *@file		tool.c
 *@author	Wilhelm Nordgren
 *@author	Jesper Jansson
 *@author	Natasha Donner
 *
 *
 */
#include "tool.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t buff[255];
uint8_t rxBuffer[rxBufferSize];
uint8_t mainBuffer[mainBufferSize];
uint8_t mainBufferCount = 0;
uint8_t rxChar[1];
uint8_t rxCount;
uint8_t rxWait;

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
 *@brief	Receives data sent over UART until end transmission is detected.
 *@author	Jesper Jansson
 */
void UARTreceiveIT(UART_HandleTypeDef *huart){
	rxWait = 1;
	HAL_UART_Receive_IT(huart, rxChar, 1);	// Start receiving first byte
}

/*
 *@brief	Sends an AT command over UART4. Prints the command and received answer over UART5.
 *@brief	Example: ATsend("AT");
 *@author	Jesper Jansson
 */
void ATsend (char out[]){
	uint8_t size = strlen(out);
	HAL_UART_Transmit(&huart4, (uint8_t *)out, size, maxTimeout);
}

/*
 *@brief	Checks if the five first characters of an array matches the the string "ERROR".
 *@brief	Example: isERROR(arr);
 *@param	uint8_t arr[]
 *@return	uint8_t; 1 if true, 0 if false.
 *@author	Jesper Jansson
 */
uint8_t isERROR(uint8_t arr[]) {
	uint8_t err[] = {'E','R','R','O','R'};
	for(int i = 0; i < 5; i++) {
		if(arr[i] != err[i]) {
			return 0;
		}
	}
	return 1;
}

/*
 * @brief Callback function for the UARTReceiveIT function. Checks received byte and copies it to the rxBuffer. Calls for reception of the next byte until end of transmission is detected
 * @author Jesper Jansson
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	rxBuffer[rxCount] = rxChar[0];
	rxCount++;
	if(rxChar[0] == 'K') {
		if(rxBuffer[rxCount - 2] == 'O'){
			rxWait = 0;
			rxCount = 0;
		} else {
			HAL_UART_Receive_IT(huart, rxChar, 1);
		}
	} else if (rxCount == 5) {
		if(isERROR(rxBuffer)) {
			rxWait = 0;
			rxCount = 0;
		}
	} else {
		HAL_UART_Receive_IT(huart, rxChar, 1);
	}
}

/*
 *
 */
void uartReset(UART_HandleTypeDef *huart)
{
	huart->RxState = HAL_UART_STATE_READY;
}

/*
 *@brief	Converts integer to char array
 *@param	int integer
 *@brief	Example: intToCharArray(24567);
 *@author	Natasha Donner
 */
char* intToCharArray(int integer)
{
	int count = 0;
	int copy = integer;

	// Loop ends when count is the same as quantity of numbers in copy
	while (copy) {
		copy = copy/10;
		count++;
	}

	// Char array for result
	char* charArr;
	charArr = (char*)malloc(count);

	// Duplicate char array
	char charArr1 [count];
	int index = 0;
	while (integer) {
		// Modulus with ten to get the last positioned number
		// Add "0" to get ASCII character
		charArr1[++index] =  integer % 10 + '0';
		// Truncate with 10
		// 0.1 gives int = 0, will then end while loop.
		integer /= 10;
	}

	// Reverse array to get the characters in the right position
	int i;
	for(i = 0; i < index; i++) {
		charArr[i] = charArr1[index - i];
	}
	// Null character on the last index o
	// To stop the array memory allocation
	charArr[i] = '\0';

	// Return char array
	return (char*)charArr;
}
