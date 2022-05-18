#include <test.h>

extern uint8_t rxBuffer[rxBufferSize];
extern uint8_t mainBuffer[rxBufferSize];
extern uint8_t mainBufferCount;
extern uint8_t rxChar[1];
extern uint8_t rxCount;
extern uint8_t rxWait;

/*@brief	TDD test program, runs when test program is defined in main
 * @author	Wilhelm Nordgren, Jesper Jansson, Natasha Donner
 *
 */
void Test_program(void){
	while(1){
		Test_wifiStartup();
		Test_sensorStartup();
		Test_getHumidVal();
		Test_readTemp();
		Test_uploadTemp();
		Test_uploadHumid();
		Test_uartPrint();
		Test_ATsend();
		Test_UARTreceive_IT();
		Test_isERROR();
		Test_ConnectWifi();
		Test_sensorStartup();
		Test_sendTempAnyLengt();
		Test_DMA();
	}
}

/*@brief	Tests getHumidVal() function, sends value over uart for debugging
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

/*@brief	Tests uploadHumid() function
 *@author	Wilhelm Nordgren
 */
void Test_uploadHumid(void){
	uploadHumid();
}

/*@brief	Tests uploadTemp() function
 *@author	Wilhelm Nordgren
 */
void Test_uploadTemp(void){
	uploadTemp();
}

/*@brief	Tests wifiStartup() function
 *@author	Wilhelm Nordgren
 */
void Test_wifiStartup (void){
	wifiStartup();
//	connectToServer();
}

/*@brief	Tests sensorStartup() function
 *@author	Wilhelm Nordgren
 */
void Test_sensorStartup (void){
	sensorStartup();
}

/*@brief	Tests uartPrint() function
 *@author	Wilhelm Nordgren
 */
void Test_uartPrint (void){
	uint8_t intArray[8] = {1+48, 2+48, 3+48, 4+48, 5+48, 6+48};
	uartPrint(intArray,sizeof(intArray));
	uartPrintString("Hello World!");
}

/*@brief	Tests readTemp() function
 *@author	Wilhelm Nordgren
 */
void Test_readTemp (void){
	uartPrintString("Temperature is:");
	uint16_t val = getTempVal();
	uint8_t tempVal[2];
	tempVal[0] = (val / 10) + 48;
	tempVal[1] = (val % 10) + 48;
	uartPrint((uint8_t*)tempVal, 2);
}

/*
 *@brief	Tests the UARTreceiveIT function by requesting input from serial terminal and echoing the received data
 *@author	Jesper Jansson
 */
void Test_UARTreceive_IT(void) {
	uartPrintString("Write something!");
	UARTreceiveIT(&huart5);
	while(rxWait) {

	}
	uartPrint(rxBuffer, rxBufferSize);
}

/*
 *@brief	Tests the ATsend function by sending a series of AT commands that instruct the Wifi module to connect and disconnest to a network
 *@author	Jesper Jansson
 */
void Test_ATsend (void){
	char cwmode[] = "AT+CWMODE=1\r\n";
	char cwjap[] = "AT+CWJAP=\"jeppes\",\"2e492b166007\"\r\n";
	char cwqap[] = "AT+CWQAP\r\n";
	ATsend(cwmode);
	uartPrintString("Connecting to Wifi...");
	ATsend(cwjap);
	HAL_Delay(10000);
	uartPrintString("Disconnecting from Wifi...\r\n");
	ATsend(cwqap);
}

/*
 *@brief	Tests the isERROR function by giving it a correct input string and an incorrect input string and printing the returned result to the serial terminal
 *@author	Jesper Jansson
 */
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

/*
 *@brief	Tests wifiConnect
 *@brief	Hardcoded wifi name and password
 *@author	Natasha Donner
 */
void Test_ConnectWifi(void)
{
	char wifi[] = "iPhone";
	char password[] = "natashadonner1";
	wifiConnect(wifi,password);
	HAL_Delay(2000);
}

/*
 *@brief	Tests sendTempAnyLength()
 *@brief	Sends value with 2bytes and 7bytes
 *@author	Natasha Donner
 */
void Test_sendTempAnyLengt(void)
{
	int8_t val = getTempVal();
	char* value = intToCharArray(val);
	char test[] = "1237890";
	sendTempAnyLength(value);
	sendTempAnyLength(test);
}

