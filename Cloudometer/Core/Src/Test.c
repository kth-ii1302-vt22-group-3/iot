#include <test.h>

extern uint8_t rxBuffer[rxBufferSize];
extern uint8_t rxChar[1];
extern uint8_t rxCount;
extern uint8_t rxWait;

<<<<<<< Updated upstream
=======
/*@brief	TDD test program
 *@author	Wilhelm Nordgren, Jesper Jansson, Natasha Donner
 */
>>>>>>> Stashed changes
void Test_program(void){
	while(1){
	Test_wifiStartup();
	Test_sensorStartup();
	Test_getTempVal();
	//	Test_uartPrint();
	//	Test_readTemp();
	//	Test_ATsend();
	//	Test_UARTtransmit_IT();
	//	Test_UARTreceive_IT();
	//	Test_isERROR();
	HAL_Delay(5000);
	}
<<<<<<< Updated upstream

}

=======
}

/*
 *@brief	Get humidity value, configure to print over uart for debugging
 *@author	Wilhelm Nordgren
 */
void Test_getHumidVal(void){
	uartPrintString("Humidity is: ");
	uint16_t val = getHumidVal();
	char *humidVal;
	humidVal = (char *) malloc(sizeof(char) * 2);
	humidVal[0] = (char)(val / 10) + 48;
	humidVal[1] = (char)(val % 10) + 48;
	uartPrint((uint8_t*)humidVal, 2);
}

/*
 * @brief
 *@author	Wilhelm Nordgren
 */
void Test_uploadHumid(void){
	uploadHumid();
}

/*
 *@brief
 *@author	Wilhelm Nordgren
 */
>>>>>>> Stashed changes
void Test_uploadTemp(void){
	uploadTemp();
}

<<<<<<< Updated upstream
=======
/*
 *@brief
 *@author	Wilhelm Nordgren
 */
>>>>>>> Stashed changes
void Test_wifiStartup (void){
	wifiStartup();
//	connectToServer();
}

<<<<<<< Updated upstream
=======
/*
 *@brief
 *@author	Wilhelm Nordgren
 */
>>>>>>> Stashed changes
void Test_sensorStartup (void){
	sensorStartup();
}

<<<<<<< Updated upstream
=======
/*
 *@brief
 *@author	Wilhelm Nordgren
 */
>>>>>>> Stashed changes
void Test_uartPrint (void){
	uint8_t intArray[8] = {1+48, 2+48, 3+48, 4+48, 5+48, 6+48};
	uartPrint(intArray,sizeof(intArray));
	uartPrintString("Hello World!");
}

<<<<<<< Updated upstream
=======
/*
 *@brief
 *@author	Wilhelm Nordgren
 */
>>>>>>> Stashed changes
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
	uartPrintString("Is everything OK?");
//	UARTreceiveIT(huart5);
	while(1);
}

void Test_ATsend (void){
//	char cwmode[] = "AT+CWMODE=1\r\n";
		char cwjap[] = "AT+CWJAP=\"jeppes\",\"2e492b166007\"\r\n";
//	char gmr[] = "AT+GMR\r\n";
//		char cwqap[] = "AT+CWQAP\r\n";
//	ATsend(gmr);
//	ATsend(cwmode);
//		uartPrintString("Connecting to Wifi...");
		ATsend(cwjap);
//		HAL_Delay(10000);
//		uartPrintString("Disconnecting from Wifi...\r\n");
//		ATsend(cwqap);
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
