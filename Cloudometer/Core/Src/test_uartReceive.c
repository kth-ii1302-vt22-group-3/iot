/*
 * test_uartReceive.c
 *
 *  Created on: May 16, 2022
 *      Author: natashadonner
 */
#include "uartReceive.h"
#include "usart.h"

void Test(void)
{
	while(1)
	{
		getResponse();
		HAL_Delay(1000);
	}
}
