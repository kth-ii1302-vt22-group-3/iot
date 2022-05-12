#include "wifi.h"
#include <stdlib.h>

char network[] = "W";
char password[] = "bogenarlos";

void wifiStartup (void){
	ATsend("AT+RST\r\n");
	HAL_Delay(500);
	ATsend("AT+CWQAP\r\n");
	HAL_Delay(500);
	ATsend("AT\r\n");
	HAL_Delay(500);
	ATsend("AT+UART_DEF=115200,8,1,0,0\r\n");
	HAL_Delay(500);
	ATsend("AT+CWMODE_DEF=1\r\n");
	HAL_Delay(1000);
	composeWifiAT();
//	char *connectWith = composeWifiAT();
//	ATsend(connectWith);
//	free(connectWith);
	HAL_Delay(2000);
}

void connectToServer (void){
	ATsend("AT+CIPSTART=\"TCP\",\"172.20.10.3\",8080\r\n");
	HAL_Delay(2000);

}

void discFromServer (void){
	ATsend("AT+CIPCLOSE\r\n");
	HAL_Delay(1000);
}

void sendTemp (char out[]){
	ATsend("AT+CIPSEND=4\r\n");
//	ATsend(out);
//	ATsend("\r\n");

	int len = 5;
	char *temp;
	temp = (char *) calloc(len, sizeof(char));

	strcat(temp, out);
	strcat(temp, "\r\n\0");
	ATsend(temp);
	free(temp);
//	static char message[4];
//	strncat(message, out, 2);
//	strncat(message, "\r\n", 2);
//	uartPrintString("This is message : ");
//	uartPrintString(message);
//	ATsend(message);
	HAL_Delay(1000);
}


void composeWifiAT (void){
	int len = sizeof(network) - 1 + sizeof(password) - 1 + 17;
	char *connect;
	connect = (char *) calloc(len, sizeof(char));

	strcat(connect, "AT+CWJAP=\"");
	strcat(connect, network);
	strcat(connect, "\",\"");
	strcat(connect, password);
	strcat(connect, "\"\r\n\0");
	ATsend(connect);
	free(connect);
//	char *connectWith;
//	connectWith = (char *) malloc(sizeof(char) * len);
//	strncat(connectWith, connect, len);
//	return connectWith;
//	return connect;
}


