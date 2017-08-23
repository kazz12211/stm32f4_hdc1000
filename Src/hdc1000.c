/*
 * hdc1000.c
 *
 *  Created on: 2017/08/22
 *      Author: ktsubaki
 */

#include "hdc1000.h"

int8_t HDC1000_Init(HDC1000_HandleTypeDef *h, I2C_HandleTypeDef * i2c, uint8_t address) {
	h->i2c = i2c;
	h->address = address;

	uint8_t commands[] = {
		HDC1000_CONFIGURATION_ADDRESS,
		0b00000000,
		0b00000000
	};

	HAL_StatusTypeDef state = HAL_I2C_Master_Transmit(h->i2c, h->address, commands, 3, 100);

	if(state != HAL_OK)
		return -1;
	return 0;
}

uint16_t _getdata(HDC1000_HandleTypeDef *h, uint8_t address) {
	uint32_t wait_counter = 0;
	uint8_t receivedData[2];
	uint16_t data;

	if(HAL_I2C_Master_Transmit(h->i2c, h->address, &address, 1, 100) != HAL_OK) {
		return HDC1000_ERROR_CODE;
	}

	while(wait_counter++ <= 500000) {}

	if(HAL_I2C_Master_Receive(h->i2c, h->address, receivedData, 2, 100) != HAL_OK) {
		return HDC1000_ERROR_CODE;
	}

	data = receivedData[0] << 8;
	data |= receivedData[1];

	return data;
}

float HDC1000_Get_Temperature(HDC1000_HandleTypeDef *h) {
	uint16_t data = _getdata(h, HDC1000_TEMP_ADDRESS);
	if(data == HDC1000_ERROR_CODE) {
		return HDC1000_ERROR_CODE;
	}

	return (data / 65536.0 * 165.0) - 40.0;
}

float HDC1000_Get_Humidity(HDC1000_HandleTypeDef *h) {
	uint16_t data = _getdata(h, HDC1000_HUMI_ADDRESS);
	if(data == HDC1000_ERROR_CODE) {
		return HDC1000_ERROR_CODE;
	}

	return (data / 65536.0 * 100.0);
}
