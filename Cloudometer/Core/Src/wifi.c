#include "wifi.h"

//#define NETWORK "jeppes"
//#define PASSWORD ""

void wifiStartup (void){

	ATsend("AT\r\n");
	ATsend("AT+UART_DEF=115200,8,1,0,0\r\n");
	ATsend("AT+CWMODE_DEF=1\r\n");
	ATsend("AT+CWJAP=\"jeppes\",\"2e492b166007\"\r\n");
	HAL_Delay(5000);
}

void connectToServer (void){
	ATsend("AT+CIPSTART=\"TCP\",\"java.lab.ssvl.kth.se\",7\r\n");
	HAL_Delay(5000);
	ATsend("AT+CIPSEND=14\r\n");
	HAL_Delay(5000);
	ATsend("Hello World!");
}
