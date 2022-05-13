/*
 *	@brief	Sensor startup/configure function and functions to use sensor.
 *	@file	sensor.c
 *	@author	Wilhelm Nordgren
 *
 */
#include "sensor.h"
#include "i2c.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>

HAL_StatusTypeDef ret;
static const uint8_t SENSOR_ADDR = 0x5F << 1;

uint8_t buffer[12];
uint8_t reg[1];

// Variables for temperature configuration
uint16_t T0_degC;
uint16_t T1_degC;
uint16_t T0_OUT;
uint16_t T1_OUT;


/*
 * @brief	Sensor startup and config function. Function run once at startup.
 * @author	Wilhelm Nordgren
 */
void sensorStartup (void){
	uint8_t config[2];

	//Startup sensor
	config[0] = 0x20;
	config[1] = 0x85;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 2, HAL_MAX_DELAY);
	HAL_Delay(100);

	//Get calibration values

	config[0] = 0x32;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T0_degC = buffer[0];

	config[0] = 0x33;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T1_degC = buffer[0];

	config[0] = 0x35;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T0_degC = (T0_degC | ((buffer[0] & 0x03)<<8)) / 8;
	T1_degC = (T1_degC | ((buffer[0] & 0x0C)<<6)) / 8;


	config[0] = 0x3C;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T0_OUT = buffer[0];

	config[0] = 0x3D;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T0_OUT = (buffer[0]<<8) | T0_OUT;

	config[0] = 0x3E;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T1_OUT = buffer[0];

	config[0] = 0x3F;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T1_OUT = (buffer[0]<<8) | T1_OUT;

}

/*
 * @brief	Function to get temperature value from sensor. sensorStartup() must be run before
 * 			getTempVal().
 * @return	uint16_t with temperature
 * @author	Wilhelm Nordgren
 */
uint16_t getTempVal (void){
	uint16_t val;
	reg[0]= 0xAA;
	ret = HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, reg, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) {
		strcpy((char*)buffer, "Error Tx\r\n");
	}else{
		ret = HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 2, HAL_MAX_DELAY);
		if ( ret != HAL_OK ) {
			strcpy((char*)buffer, "Error Rx\r\n");
		}
	}
	uint16_t T_OUT = (((uint16_t)buffer[1])<<8) | (uint16_t)buffer[0];

	val = (((T1_degC - T0_degC) * (T_OUT - T0_OUT)) / (T1_OUT - T0_OUT)) + T0_degC -2;

	return val;
}

/*
 * @brief	Function gets temperature, puts in char array and pass
 * 			on to the wifi send function
 * @author	Wilhelm Nordgren
 */
void uploadTemp (void){
	uint16_t val = getTempVal();
	char *tempVal;
	tempVal = (char *) malloc(sizeof(char) * 2);
	tempVal[0] = (char)(val / 10) + 48;
	tempVal[1] = (char)(val % 10) + 48;
	sendTemp(tempVal);
	free(tempVal);
}
