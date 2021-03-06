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
int16_t T0_degC;
int16_t T1_degC;
int16_t T0_OUT;
int16_t T1_OUT;

// Variables for humidity configuration
int16_t H0_rH;
int16_t H1_rH;
int16_t H0_OUT;
int16_t H1_OUT;

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

	//Get calibration values for temperature

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
	T0_degC = (((uint16_t)(T0_degC)) | (((uint16_t)(buffer[0] & 0x03))<<8)) / 8;
	T1_degC = (((uint16_t)(T1_degC)) | (((uint16_t)(buffer[0] & 0x0C))<<6)) / 8;

	config[0] = 0x3C;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T0_OUT = (uint16_t)buffer[0];

	config[0] = 0x3D;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T0_OUT = ((uint16_t)(buffer[0]<<8)) | (uint16_t)T0_OUT;

	config[0] = 0x3E;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T1_OUT = (uint16_t)buffer[0];

	config[0] = 0x3F;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	T1_OUT = ((uint16_t)(buffer[0]<<8)) | (uint16_t)T1_OUT;

	//Get calibration values for humidity

	config[0] = 0x30;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	H0_rH = (uint16_t) buffer[0];
	H0_rH = H0_rH / 2;

	config[0] = 0x31;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	H1_rH = (uint16_t) buffer[0];
	H1_rH = H1_rH / 2;

	config[0] = 0x36;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	H0_OUT = (uint16_t)buffer[0];

	config[0] = 0x37;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	H0_OUT = ((uint16_t) H0_OUT) | (((uint16_t)(buffer[0]) << 8));

	config[0] = 0x3A;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	H1_OUT = (uint16_t) buffer[0];

	config[0] = 0x3B;
	HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, config, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 1, HAL_MAX_DELAY);
	H1_OUT = ((uint16_t) H1_OUT) | (((uint16_t) (buffer[0]) << 8));

}

/*
 * @brief	Function to get temperature value from sensor. sensorStartup() must be run before
 * 			getTempVal().
 * @return	uint16_t with temperature
 * @author	Wilhelm Nordgren
 */
uint16_t getTempVal (void){
	float val;
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
	int16_t T_OUT = (((uint16_t)buffer[1]) << 8) | (uint16_t)buffer[0];

	val = (float) (T1_degC - T0_degC) * (float)(T_OUT - T0_OUT) / (float)(T1_OUT - T0_OUT) + T0_degC;
	uint16_t retVal = (uint16_t) val;

	return retVal;
}

/*
 * @brief	Function to get humidity value from sensor. sensorStartup() must be run before
 * 			getHumidVal().
 * @return	uint16_t with humidity
 * @author	Wilhelm Nordgren
 */
uint16_t getHumidVal (void){
	float val;
	reg[0]= 0xA8;
	ret = HAL_I2C_Master_Transmit(&hi2c3, SENSOR_ADDR, reg, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) {
		strcpy((char*)buffer, "Error Tx\r\n");
	}else{
		ret = HAL_I2C_Master_Receive(&hi2c3, SENSOR_ADDR, buffer, 2, HAL_MAX_DELAY);
		if ( ret != HAL_OK ) {
			strcpy((char*)buffer, "Error Rx\r\n");
		}
	}
	int16_t H_OUT = (((uint16_t)buffer[1]) << 8) | (uint16_t)buffer[0];

	val = (float)(H_OUT - H0_OUT) * (float)(H1_rH - H0_rH) / (float)(H1_OUT - H0_OUT) + H0_rH;
	uint16_t retVal = (uint16_t) val;

	return retVal;
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

/*
 * @brief	Function gets humidity, puts in char array and pass
 * 			on to the wifi send function
 * @author	Wilhelm Nordgren
 */
void uploadHumid (void){
	uint16_t val = getHumidVal();
	char *humidVal;
	humidVal = (char *) malloc(sizeof(char) * 2);
	humidVal[0] = (char)(val / 10) + 48;
	humidVal[1] = (char)(val % 10) + 48;
	sendHumid(humidVal);
	free(humidVal);
}
