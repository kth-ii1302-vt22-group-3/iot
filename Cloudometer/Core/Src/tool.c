/*@brief	File contains tools used during development and test runs.
 *@file		tool.c
 *@author	Wilhelm Nordgren
 *
 *
 */
#include "tool.h"

uint8_t rxBuffer[rxBufferSize];
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
 *@brief	Receives data sent over UART5 until end of line is detected.
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
	rxWait = 1;
	uartPrintString(out);
	uint8_t size = strlen(out);
	HAL_UART_Transmit(&huart4, (uint8_t *)out, size, maxTimeout);
	UARTreceiveIT(&huart4);
	while(rxWait){}
	uartPrint(rxBuffer, rxCount);
}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
//	HAL_UART_Receive_DMA(&huart5, rxBuffer, rxBufferSize);
//}
//
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if((rxBuffer[rxCount - 1] != 'O') & (rxChar[0] != 'K')) {
		rxBuffer[rxCount] = rxChar[0];
		rxCount++;
		HAL_UART_Receive_IT(huart, rxChar, 1);
	} else {
		rxBuffer[rxCount] = rxChar[0];
		rxCount++;
		rxWait = 0;
	}
}
