/*
 * UartReceive.c
 *
 *  Created on: 16 May 2022
 *      Author: Jesper Jansson
 */
#include <uartReceive.h>

extern uint8_t rxBuffer[BUFFER_SIZE];
uint8_t rspBuffer[BUFFER_SIZE];
uint8_t rspBufferCount = 0;
uint8_t rspOK = 0;

extern UART_HandleTypeDef huart5;
extern DMA_HandleTypeDef hdma_uart5_rx;

void init(void) {
	__HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart5, (uint8_t *)rxBuffer, BUFFER_SIZE);
}

void getResponse(void) {
	if(rspOK) {
		HAL_UART_Transmit(&huart5, (uint8_t *)"Response1: ", 10, 500);
		HAL_UART_Transmit(&huart5, rspBuffer, rspBufferCount, 500);
		HAL_UART_Transmit(&huart5, (uint8_t *)"\r\n", 2, 500);
		rspOK = 0;
	    memset(rspBuffer,0,BUFFER_SIZE);
	}
}
void USER_UART_IDLECallback(UART_HandleTypeDef *huart)
{
	//Stop this DMA transmission
    HAL_UART_DMAStop(&huart5);

    //Calculate the length of the received data
    uint8_t data_length  = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_uart5_rx);

//	Test function: Print out the received data
//    HAL_UART_Transmit(&huart5,(uint8_t *)"Received data: ",15,0x200);
//    HAL_UART_Transmit(&huart5,rxBuffer,data_length,0x200);
//    HAL_UART_Transmit(&huart5,(uint8_t *)"\r\n",2,0x200);

    //Copy from rxBuffer to rspBuffer
    memcpy(rspBuffer,rxBuffer,data_length);
    rspBufferCount = data_length;
    rspOK = 1;

	//Zero Receiving Buffer
    memset(rxBuffer,0,data_length);
    data_length = 0;

    //Restart to start DMA transmission of 255 bytes of data at a time
    HAL_UART_Receive_DMA(&huart5, (uint8_t*)rxBuffer, BUFFER_SIZE);
}
