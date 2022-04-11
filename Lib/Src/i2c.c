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
	uint8_t i2c_buffer[SHT40_BYTES_TO_TRANSMIT] = {SHT40_COMMAND}; // Buffer for data read/written on the i2c bus

	/* SmartSensor */
	return_value = HAL_I2C_Master_Transmit(hi2c_x, (SHT40_ADDRESS << OFFSET_OF_1), i2c_buffer, SHT40_BYTES_TO_TRANSMIT, DEFAULT_TIMEOUT); // Decalage de 1 bit car adresse sur 7 bits : pour avoir sur 8bits
	return return_value;
}


Struct_TH read_temp_humi_SHT40(I2C_HandleTypeDef *hi2c_x)
{
	HAL_StatusTypeDef return_value; //of i2C communication : HAL_OK or HAL_ERROR ...
	uint16_t reading_humidity_ticks, crc_humidity, reading_temperature_ticks, crc_temperature;
	uint8_t i2c_buffer[SHT40_BYTES_TO_RECEIVE] = {ZERO}; 				/* Buffer for data read/written on the i2c bus */
	Struct_TH i2C;

	// Read 2 bytes from the temperature register
	return_value = HAL_I2C_Master_Receive(hi2c_x, (SHT40_ADDRESS << OFFSET_OF_1) , i2c_buffer, SHT40_BYTES_TO_RECEIVE, DEFAULT_TIMEOUT);
	if(return_value == HAL_OK)
	{
		/* Temperature is located in next two bytes, padded by two trailing bits */
		reading_temperature_ticks = (i2c_buffer[SHT40_BUFFER_TEMPERATURE_FIRST_BYTE] << BYTE_OFFSET) + (i2c_buffer[SHT40_BUFFER_TEMPERATURE_SECOND_BYTE]); // sur 2 octets
		i2C.temperature = FIRST_CONST_175 * reading_temperature_ticks / SECOND_CONST_65535 - THIRD_CONST_45;     // temperature ticks to temperature : from datasheet
		crc_temperature = calc_crc(reading_temperature_ticks);

		/* Humidity is located in the 4th and 5th bytes */
		reading_humidity_ticks = (i2c_buffer[SHT40_BUFFER_HUMIDITY_FIRST_BYTE] << BYTE_OFFSET) + i2c_buffer[SHT40_BUFFER_HUMIDITY_SECOND_BYTE]; // On two bytes
		i2C.humidity = FOURTH_CONST_125 * reading_humidity_ticks / SECOND_CONST_65535 - FIFTH_CONST_6 ;     // from datasheet
		crc_humidity = calc_crc(reading_humidity_ticks);

		if(crc_temperature == i2c_buffer[SHT40_BUFFER_TEMPERATURE_CRC_BYTE] && crc_humidity == i2c_buffer[SHT40_BUFFER_HUMIDITY_CRC_BYTE])
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


//From datasheet
uint16_t sgp41_humidity_to_ticks(float humidity)
{
	uint16_t ticks = ceil(ceil(humidity)*65535/100);
	return ticks;
}

//From datasheet
uint16_t sgp41_temperature_to_ticks(float temperature)
{
	uint16_t ticks = ceil((ceil(temperature)+45) * 65535 /175);
	return ticks;
}


HAL_StatusTypeDef sgp41_send_command(I2C_HandleTypeDef *hi2c, uint16_t command, float temperature, float humidity)
{
	uint8_t cmd_array[SGP41_BYTES_TO_TRANSMIT];
	HAL_StatusTypeDef return_value;

	uint16_t humidity_ticks = ZERO;
	humidity_ticks = sgp41_humidity_to_ticks(humidity);

	uint16_t temperature_ticks = ZERO;
	temperature_ticks = sgp41_temperature_to_ticks(temperature);


	cmd_array[SGP41_COMMAND_FIRST_BYTE] 		= command >> BYTE_OFFSET;
	cmd_array[SGP41_COMMAND_SECOND_BYTE]		= command >> NO_BYTE_OFFSET;

	cmd_array[SGP41_HUMIDITY_FIRST_BYTE]		= humidity_ticks >> BYTE_OFFSET;
	cmd_array[SGP41_HUMIDITY_SECOND_BYTE]		= humidity_ticks >> NO_BYTE_OFFSET;
	cmd_array[SGP41_HUMIDITY_CRC]				= calc_crc(humidity_ticks);

	cmd_array[SGP41_TEMPERATURE_FIRST_BYTE]		= temperature_ticks >> BYTE_OFFSET;
	cmd_array[SGP41_TEMPERATURE_SECOND_BYTE]	= temperature_ticks >> NO_BYTE_OFFSET;
	cmd_array[SGP41_TEMPERATURE_CRC]			= calc_crc(temperature_ticks);

	return_value = HAL_I2C_Master_Transmit(hi2c, SGP41_ADDRESS << OFFSET_OF_1, (uint8_t *)cmd_array, SGP41_BYTES_TO_TRANSMIT, DEFAULT_TIMEOUT);

	return return_value;
}

struct_VN sgp41_receive_raw_datas(I2C_HandleTypeDef *hi2c)
{
	uint8_t buffer[SGP41_BYTES_TO_RECEIVE];
	HAL_StatusTypeDef return_value;
	struct_VN sgp41_values;

	sgp41_values.error_status = false;

	return_value = HAL_I2C_Master_Receive(hi2c, SGP41_ADDRESS << OFFSET_OF_1, (uint8_t *)buffer, SGP41_BYTES_TO_RECEIVE, DEFAULT_TIMEOUT);

	if(return_value != HAL_OK)
	{
		sgp41_values.error_status = true;
	}

	sgp41_values.sraw_voc = (buffer[SGP41_BUFFER_VOC_FIRST_BYTE] << BYTE_OFFSET) + (buffer[SGP41_BUFFER_VOC_SECOND_BYTE]);
	sgp41_values.sraw_nox = (buffer[SGP41_BUFFER_NOX_FIRST_BYTE] << BYTE_OFFSET) + (buffer[SGP41_BUFFER_NOX_SECOND_BYTE]);

	if(calc_crc(sgp41_values.sraw_voc) != buffer[SGP41_BUFFER_VOC_CRC_BYTE])
	{
		sgp41_values.error_status = true;
	}

	if(calc_crc(sgp41_values.sraw_nox) != buffer[SGP41_BUFFER_NOX_FIRST_BYTE])
	{
		sgp41_values.error_status = true;
	}

	return sgp41_values;
}
