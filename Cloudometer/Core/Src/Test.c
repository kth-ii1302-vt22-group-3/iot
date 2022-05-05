#include <test.h>

extern uint8_t rxBuffer[rxBufferSize];
extern uint8_t rxChar[1];
extern uint8_t rxCount;
extern uint8_t rxWait;

void Test_program(void){
//	Test_sensorStartup();
//	Test_uartPrint();
//	Test_readTemp();
//	Test_ATsend();
//	Test_UARTtransmit_IT();
//	Test_UARTreceive_IT();
	ATconnect();
}

void Test_sensorStartup (void){
	sensorStartup();
}

void Test_uartPrint (void){
	uint8_t intArray[8] = {1+48, 2+48, 3+48, 4+48, 5+48, 6+48};
	uartPrint(intArray,sizeof(intArray));
	uartPrintString("Hello World!");
}

void Test_readTemp (void){
	while(1){
	uint16_t val = getTempVal();
	uint8_t tempVal[2];
	tempVal[0] = (val / 10) + 48;
	tempVal[1] = (val % 10) + 48;

	uartPrint((uint8_t*)tempVal, 2);
	HAL_Delay(500);
	}
}

void Test_UARTreceive_IT(void) {
	UARTreceiveIT(&huart5);
	while(rxWait){}
	uartPrint(rxBuffer, rxCount);
}

void Test_ATsend (void){
//	char cmd[] = "AT+GMR";
	uint8_t atgmr[8] = {0x41, 0x54, 0x2b, 0x47, 0x4d, 0x52, 0xd, 0xa};

//	uint8_t at[2] = {0x41, 0x54};
	ATsend(atgmr);
}

void ATconnect(void) {
	uint8_t rxB[2] = {'X','X'};
	char cwmode[] = "AT+CWMODE=1\r\n";
	uint8_t size1 = strlen(cwmode);
	char cwjap[] = "AT+CWJAP=\"jeppes\",\"2e492b166007\"\r\n";
	uint8_t size2 = strlen(cwjap);
	HAL_UART_Transmit(&huart4, (uint8_t *)cwmode, size1, 3000);
	uartPrintString(cwmode);
	HAL_UART_Receive(&huart4, rxB, 2, 3000);
	uartPrint(rxB,2);
	uartPrintString(cwjap);
	HAL_UART_Transmit(&huart4, (uint8_t *)cwjap, size2, 3000);
}
