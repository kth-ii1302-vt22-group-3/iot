#include <test.h>

void Test_program(void){
	Test_sensorStartup();
	Test_uartPrint();
	Test_readTemp();
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
