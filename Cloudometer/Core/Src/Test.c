#include <test.h>

extern uint8_t rxBuffer[rxBufferSize];
extern uint8_t rxChar[1];
extern uint8_t rxCount;
extern uint8_t rxWait;

void Test_program(void){
//	Test_sensorStartup();
//	Test_uartPrint();
//	Test_readTemp();
	Test_ATsend();
//	Test_UARTtransmit_IT();
//	Test_UARTreceive_IT();
//	Test_isERROR();
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
//	char cwmode[] = "AT+CWMODE=1\r\n";
//	char cwjap[] = "AT+CWJAP=\"jeppes\",\"2e492b166007\"\r\n";
	char cmd[] = "AT+GMR\r\n";
//	char cmd2[] = "AT+CWQAP\r\n";
//	ATsend(cwmode);
	ATsend(cmd);
//	ATsend(cwjap);


}

void Test_isERROR(void) {
	uint8_t error[] = {'E','R','R','O','R'};
	uint8_t erros[] = {'E','R','R','O','S'};
	if(isERROR(error)) {
		uartPrintString("ERROR is ERROR");
	} else {
		uartPrintString("ERROR is not ERROR");
	}
	if(isERROR(erros)) {
		uartPrintString("ERROS is ERROR");
	} else {
		uartPrintString("ERROS is not ERROR");
	}
}
