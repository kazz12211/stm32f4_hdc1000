/*
 * hdc1000.h
 *
 *  Created on: 2017/08/22
 *      Author: ktsubaki
 */

#ifndef HDC1000_H_
#define HDC1000_H_

#include "stm32f4xx_hal.h"

#define HDC1000_DEFAULT_ADDRESS			0x40
#define HDC1000_CONFIGURATION_ADDRESS	0x02
#define HDC1000_TEMP_ADDRESS			0x00
#define HDC1000_HUMI_ADDRESS			0x01
#define HDC1000_ERROR_CODE				65535

typedef struct {
	uint8_t address;
	I2C_HandleTypeDef *i2c;
} HDC1000_HandleTypeDef;


int8_t HDC1000_Init(HDC1000_HandleTypeDef *h, I2C_HandleTypeDef * i2c, uint8_t address);

float HDC1000_Get_Temperature(HDC1000_HandleTypeDef *h);

float HDC1000_Get_Humidity(HDC1000_HandleTypeDef *h);

#endif /* HDC1000_H_ */
