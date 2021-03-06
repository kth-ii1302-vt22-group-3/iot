#include "wifi.h"

char network[] = "W";
char password[] = "bogenarlos";

char GETprefix[] = "GET /temperatures/new?value=00 HTTP/1.1\r\nHost: cloudometer-api.herokuapp.com\r\nConnection: close\r\n\r\n";
char GETprefixHumid[] = "GET /temperatures/new?humid=00 HTTP/1.1\r\nHost: cloudometer-api.herokuapp.com\r\nConnection: close\r\n\r\n";

/*
 * @brief	Wifi startup sequence, uses wifi name and password
 * 			from network[] and password[] char arrays.
 * 	@author	Jesper Jansson, Natasha Donner, Wilhelm Nordgren
 */
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
	HAL_Delay(2000);
}

/*
 * @brief	Send AT command to connect to server
 * @author	Jesper Jansson, Natasha Donner, Wilhelm Nordgren
 */
void connectToServer (void){
	ATsend("AT+CIPSTART=\"TCP\",\"cloudometer-api.herokuapp.com\",80,60\r\n");
	HAL_Delay(2000);
}

/*
 * @brief	Send AT command to disconnect from server
 * @author	Jesper Jansson, Natasha Donner, Wilhelm Nordgren
 */
void discFromServer (void){
	ATsend("AT+CIPCLOSE\r\n");
	HAL_Delay(1000);
}

/*
 * @brief	Sends temperature to server
 * @param	A 2-length char array[] with temperature
 * @author	Jesper Jansson, Natasha Donner, Wilhelm Nordgren
 */
void sendTemp (char out[]){
	GETprefix[28] = out[0];
	GETprefix[29] = out[1];
	ATsend("AT+CIPSEND=99\r\n");
	HAL_Delay(500);
	ATsend(GETprefix);
	HAL_Delay(1000);
}

/*
 * @brief	Sends temperature to server
 * @param	A 2-length char array[] with temperature
 * @author	Jesper Jansson, Natasha Donner, Wilhelm Nordgren
 */
void sendHumid (char out[]){
	GETprefixHumid[28] = out[0];
	GETprefixHumid[29] = out[1];
	ATsend("AT+CIPSEND=99\r\n");
	HAL_Delay(500);
	ATsend(GETprefixHumid);
	HAL_Delay(1000);
}

/*
 *
 */
void sendTempAnyLength (char out[]){
//	New version that can take any temperature size and sends it to server.
	int8_t size_t = strlen(out);
	char* size_out = intToCharArray(size_t);
	int8_t size_atcipsend= 15 + size_t;
	char atcipsend[size_atcipsend];
	char prefix[]= "AT+CIPSEND=";
	char newLine []= "\r\n";


	strcpy(atcipsend, prefix);
	strcat(atcipsend,size_out);
	strcat(atcipsend, newLine);

//	for testing purpose, send to computer via UART
	uartPrintString(atcipsend);

//	Remove comment to activate sending AT command
//	ATsend(atcipsend);
	HAL_Delay(500);

	int8_t size_get = 97 + size_t;
	char get[size_get];
	char prefix_get[] = "GET /temperatures/new?value=";
	char subfix_get[] = " HTTP/1.1\r\nHost: cloudometer-api.herokuapp.com\r\nConnection: close\r\n\r\n";
	strcpy(get, prefix_get);
	strcat(get, out);
	strcat(get, subfix_get);

//	for testing purpose, send to computer via UART
	uartPrintString(get);

//	Remove comment to activate sending AT command
//	ATsend(get);
	HAL_Delay(500);
}




/*
 * @brief	Function to connect to the wifi specified in network
 * 			and password arrays
 * 	@author	Jesper Jansson, Natasha Donner, Wilhelm Nordgren
 */
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
}


/*
 *@brief	Receives wifi name and password. Prints name and password.
 *@brief	Appends name and password with string.
 *@brief	Set ESP 01 in station mode with cwmode = 1 command
 *@brief	Connects to wifi
 *@param 	char wifi[], char password[]
 *@brief	Example: wifi_connect("wifi, password");
 *@author	Natasha Donner
 */
void wifiConnect(char wifi[], char password[]){

//	prints wifi and password
	uartPrintString(wifi);
	uartPrintString(password);

//	append cwjap command, wifi and password into array.
	char cwjap[100];
	strcpy(cwjap, "AT+CWJAP=\"");
	strcat(cwjap,wifi);
	strcat(cwjap, "\",\"");
	strcat(cwjap,password);
	strcat(cwjap, "\"\r\n");

	// Set ESP01 to station mode
	char cwmode[] = "AT+CWMODE=1\r\n";


//  send command to ESP
	ATsend(cwmode);
	ATsend(cwjap);
}
