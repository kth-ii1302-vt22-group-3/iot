#include "wifi.h"

char network[] = "W";
char password[] = "bogenarlos";

void wifiStartup (void){
	static char connect[60] = "AT+CWJAP=\"";
	strncat(connect, network, sizeof(network)-1);
	strncat(connect, "\",\"",5);
	strncat(connect, password, sizeof(password));
	strncat(connect, "\"\r\n", 6);
	int size = sizeof(network) - 1 + sizeof(password) - 1 + 16;
	char connectWith[size];
	strncat(connectWith, connect, size);

	HAL_Delay(2000);
	ATsend("AT+RST\r\n");
	HAL_Delay(2000);
	ATsend("AT+CWQAP\r\n");
	HAL_Delay(5000);
	ATsend("AT\r\n");
	HAL_Delay(1000);
	ATsend("AT+UART_DEF=115200,8,1,0,0\r\n");
	HAL_Delay(1000);
	ATsend("AT+CWMODE_DEF=1\r\n");
	HAL_Delay(1000);
	ATsend(connectWith);
	HAL_Delay(10000);
}

void connectToServer (void){
	ATsend("AT+CIPSTART=\"TCP\",\"172.20.10.3\",8080\r\n");
	HAL_Delay(10000);
	ATsend("AT+CIPSEND=14\r\n");
	HAL_Delay(10000);
	ATsend("Hello World!\r\n");
	HAL_Delay(10000);
}



