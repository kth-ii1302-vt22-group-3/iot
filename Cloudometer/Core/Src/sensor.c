/*
 * sensor.c
 *
 *  Created on: Apr 11, 2022
 *      Author: natashadonner
 *
 */
#include "sensor.h"
#include "i2c.h"
#include "usart.h"
#include <string.h>

static const uint16_t SENSOR_ADDR = 0x5F << 1;
uint8_t buffer[12];

void sensorStartup (void){
	uint8_t reg[1];
	uint8_t data[4];
	uint8_t config[2] = {0};
	config[0] = 0x20;
	config[1] = 0x85;
	data[0] = 0x41;
	HAL_UART_Transmit(&huart5, (uint8_t *)data, 2, 5000);

	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 2, HAL_MAX_DELAY);
	HAL_Delay(100);
	while(1){
	reg[0] = 0xa8;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, reg, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, data, 4, HAL_MAX_DELAY);


	HAL_Delay(200);
	}

}
