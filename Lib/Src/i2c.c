/*
 * i2c.c
 *
 *  Created on: Apr 4, 2022
 *      Author: handddle
 */

#include "../Inc/i2c.h"

HAL_StatusTypeDef write_frame_temp_humi_SHT40(I2C_HandleTypeDef *hi2c_x)
{
	HAL_StatusTypeDef return_value; //of i2C communication : HAL_OK or HAL_ERROR ...
	uint8_t i2c_buffer[BYTES_TO_TRANSMIT_SHT40] = {SHT40_COMMAND}; // Buffer for data read/written on the i2c bus

	/* SmartSensor */
	return_value = HAL_I2C_Master_Transmit(hi2c_x, (SHT40_ADDRESS << ONE), i2c_buffer, BYTES_TO_TRANSMIT_SHT40, DEFAULT_TIMEOUT); // Decalage de 1 bit car adresse sur 7 bits : pour avoir sur 8bits
	return return_value;
}


Struct_TH read_temp_humi_SHT40(I2C_HandleTypeDef *hi2c_x)
{
	HAL_StatusTypeDef return_value; //of i2C communication : HAL_OK or HAL_ERROR ...
	float reading_humidity, reading_temperature;
	uint8_t i2c_buffer[BYTES_TO_READ_SHT40] = {ZERO}; 				/* Buffer for data read/written on the i2c bus */
	Struct_TH i2C;
	i2C.error_status = false;

	// Read 2 bytes from the temperature register
	return_value = HAL_I2C_Master_Receive(hi2c_x, (SHT40_ADDRESS << ONE) , i2c_buffer, BYTES_TO_READ_SHT40, DEFAULT_TIMEOUT);
	if(return_value == HAL_OK)
	{
		/* Temperature is located in next two bytes, padded by two trailing bits */
		reading_temperature = (i2c_buffer[FIRST_BYTE] << BYTE_OFFSET) + (i2c_buffer[SECOND_BYTE]); // sur 2 octets
		i2C.temperature = FIRST_CONST_175 * reading_temperature / SECOND_CONST_65535 - THIRD_CONST_45;     // from datasheet

		/* Humidity is located in the 4th and 5th bytes */
		reading_humidity = (i2c_buffer[FOURTH_BYTE] << BYTE_OFFSET) + i2c_buffer[FIFTH_BYTE]; // On two bytes
		i2C.humidity = FOURTH_CONST_125 * reading_humidity / SECOND_CONST_65535 - FIFTH_CONST_6 ;     // from datasheet
	} else {
		i2C.error_status = true;
	}

	return i2C;
}
