#include "tool.h"
#include <string.h>
#include <stdlib.h>

void wifiStartup (void);
void connectToServer (void);
void composeWifiAT (void);
void sendTemp (char out[]);
void sendHumid (char out[]);
void sendTempAnyLength (char out[]);
void discFromServer (void);
void wifiConnect(char wifi[], char password[]);
