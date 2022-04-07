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
	uint16_t reading_humidity_ticks, crc_humidity, reading_temperature_ticks, crc_temperature;
	uint8_t i2c_buffer[BYTES_TO_READ_SHT40] = {ZERO}; 				/* Buffer for data read/written on the i2c bus */
	Struct_TH i2C;

	// Read 2 bytes from the temperature register
	return_value = HAL_I2C_Master_Receive(hi2c_x, (SHT40_ADDRESS << ONE) , i2c_buffer, BYTES_TO_READ_SHT40, DEFAULT_TIMEOUT);
	if(return_value == HAL_OK)
	{
		/* Temperature is located in next two bytes, padded by two trailing bits */
		reading_temperature_ticks = (i2c_buffer[FIRST_BYTE] << BYTE_OFFSET) + (i2c_buffer[SECOND_BYTE]); // sur 2 octets
		i2C.temperature = FIRST_CONST_175 * reading_temperature_ticks / SECOND_CONST_65535 - THIRD_CONST_45;     // temperature ticks to temperature : from datasheet
		crc_temperature = calc_crc(reading_temperature_ticks);

		/* Humidity is located in the 4th and 5th bytes */
		reading_humidity_ticks = (i2c_buffer[FOURTH_BYTE] << BYTE_OFFSET) + i2c_buffer[FIFTH_BYTE]; // On two bytes
		i2C.humidity = FOURTH_CONST_125 * reading_humidity_ticks / SECOND_CONST_65535 - FIFTH_CONST_6 ;     // from datasheet
		crc_humidity = calc_crc(reading_humidity_ticks);

		if(crc_temperature == i2c_buffer[THIRD_BYTE] && crc_humidity == i2c_buffer[SIXTH_BYTE])
		{
			i2C.error_status = false;
		} else
		{
			i2C.error_status = true;
		}
	} else {
		i2C.error_status = true;
	}

	return i2C;
}


uint8_t calc_crc(uint16_t data)
{
	uint8_t byte_array[2];
	byte_array[0] = data >> BYTE_OFFSET;
	byte_array[1] = data >> 0;

	uint8_t crc = 0xFF;
	for(int i = 0; i < 2; i++)
	{
		crc ^= byte_array[i];
		for(uint8_t bit = 8; bit > 0; --bit)
		{
			if(crc & 0x80)
			{
				crc = (crc << 1) ^ 0x31u;
			} else {
			crc = (crc << 1);
			}
		}
	}
	return crc;
}




