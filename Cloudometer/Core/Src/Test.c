#include <test.h>

void Test_program(void){
	//Test_sensorStartup();
	Test_uartPrint();
}

void Test_sensorStartup (void){
	sensorStartup();
}

void Test_uartPrint (void){
	uint8_t intArray[8] = {1+48, 2+48, 3+48, 4+48, 5+48, 6+48};
	uint8_t test3 = sizeof(intArray);
	uartPrint(intArray,sizeof(intArray));
	uartPrintString("Hello World!");
}
