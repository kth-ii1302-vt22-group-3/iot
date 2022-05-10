#include "wifi.h"

char network[] = "jeppes";
char password[] = "2e492b166007";

void wifiStartup (void){
	ATsend("AT+CWQAP\r\n");
	HAL_Delay(5000);
	ATsend("AT\r\n");
	HAL_Delay(1000);
	ATsend("AT+UART_DEF=115200,8,1,0,0\r\n");
	HAL_Delay(1000);
	ATsend("AT+CWMODE_DEF=1\r\n");
	HAL_Delay(1000);

	ATsend(compWifiCred());
//	ATsend("AT+CWJAP=\"jeppes\",\"2e492b166007\"\r\n");
	HAL_Delay(10000);
}

void connectToServer (void){
	ATsend("AT+CIPSTART=\"TCP\",\"java.lab.ssvl.kth.se\",7\r\n");
	HAL_Delay(10000);
	ATsend("AT+CIPSEND=14\r\n");
	HAL_Delay(10000);
	ATsend("Hello World!\r\n");
	HAL_Delay(10000);
}

char compWifiCred (void){
	static char connect[] = "AT+CWJAP=\"";
	strncat(connect, network, sizeof(network));
	strncat(connect, "\",\"",5);
	strncat(connect, password, sizeof(password));
	strncat(connect, "\"\r\n", 6);
	return connect;
}


