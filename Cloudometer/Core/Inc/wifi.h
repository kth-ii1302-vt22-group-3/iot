#include "tool.h"
#include <string.h>

void wifiStartup (void);
void connectToServer (void);
void composeWifiAT (void);
void sendTemp (char out[]);
void sendTempAnyLength (char out[]);
void discFromServer (void);
void wifiConnect(char wifi[], char password[]);
