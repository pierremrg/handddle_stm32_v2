/*
 * i2c.h
 *
 *  Created on: Apr 4, 2022
 *      Author: handddle
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

#define CRC8_POLYNOMIAL 						0x31

#define SHT40_ADDRESS 							0x44
#define SHT40_COMMAND							0xFD

#define SGP41_ADDRESS							0x59


//Enumerate index of elements of SHT40 buffer array
typedef enum {

    SHT40_BUFFER_TEMPERATURE_FIRST_BYTE 	= 0,
	SHT40_BUFFER_TEMPERATURE_SECOND_BYTE 	= 1,
	SHT40_BUFFER_TEMPERATURE_CRC_BYTE 		= 2,

	SHT40_BUFFER_HUMIDITY_FIRST_BYTE 		= 3,
	SHT40_BUFFER_HUMIDITY_SECOND_BYTE 		= 4,
	SHT40_BUFFER_HUMIDITY_CRC_BYTE 			= 5


} sht40_index_buffer_array;

//Enumerate index of elements of SGP41 command array
typedef enum {

    SGP41_COMMAND_FIRST_BYTE 		= 0,
	SGP41_COMMAND_SECOND_BYTE 		= 1,


	SGP41_HUMIDITY_FIRST_BYTE 		= 2,
	SGP41_HUMIDITY_SECOND_BYTE 		= 3,
	SGP41_HUMIDITY_CRC		 		= 4,

	SGP41_TEMPERATURE_FIRST_BYTE 	= 5,
	SGP41_TEMPERATURE_SECOND_BYTE 	= 6,
	SGP41_TEMPERATURE_CRC		 	= 7,


} sgp41_index_cmd_array;

//Enumerate index of elements of SGP41 buffer array
typedef enum {

    SGP41_BUFFER_VOC_FIRST_BYTE 		= 0,
	SGP41_BUFFER_VOC_SECOND_BYTE 		= 1,
	SGP41_BUFFER_VOC_CRC_BYTE 			= 2,

	SGP41_BUFFER_NOX_FIRST_BYTE 		= 3,
	SGP41_BUFFER_NOX_SECOND_BYTE 		= 4,
	SGP41_BUFFER_NOX_CRC_BYTE 			= 5


} sgp41_index_buffer_array;

/*
 * @brief  	This function is used to collect Temperature & Humidity with the SHT40.
 * @param	hi2c_x is the i2c channel which we send the frame
 * @retval 	return an HAL_StatusTypeDef variable to know if we can communicate with the SHT40
 */
HAL_StatusTypeDef write_frame_temp_humi_SHT40(I2C_HandleTypeDef *hi2c_x);

/*
 * @brief  	This function is used to send an UART frame to the SHT40.
 * @param	hi2c_x is the i2c channel which we send the frame
 * @retval 	return a Struct_TH variable to get the temperature and the humidity rate
 */
Struct_TH read_temp_humi_SHT40(I2C_HandleTypeDef *hi2c_x);

/*
 * @brief  	This function is used to calculate the checksum of a data according to sensirion's datasheet
 * @param	data is the value for which we'll calculate the checksum
 * @retval 	return as an integer value the checksum calculated
 */
uint8_t calc_crc(uint16_t data);

/*
 * @brief  	This function is used to calculate the humidity ticks from the humidity value still according to sensirion's datasheet
 * @param	humidity is the value for which we'll calculate the ticks
 * @retval 	return as an integer the value the ticks calculated
 */
uint16_t sgp41_humidity_to_ticks(float humidity);

/*
 * @brief  	This function is used to calculate the temperature ticks from the temperature value still according to sensirion's datasheet
 * @param	temperature is the value for which we'll calculate the ticks
 * @retval 	return as an integer the value the ticks calculated
 */
uint16_t sgp41_temperature_to_ticks(float temperature);

/*
 * @brief  	This function is used to send i2c frame to the sgp41
 * @param	hi2c is the i2c channel which we communicate
 * @param	command is the command ID to send to the sgp41
 * @param 	humidity and temperature is the environment datas used as parameter to calculate the NOx value with the humidity and temperature compensation
 * @retval 	return an HAL_StatusTypeDef variable to know if we can communicate with the SGP41
 */
HAL_StatusTypeDef sgp41_send_command(I2C_HandleTypeDef *hi2c, uint16_t command, float humidity, float temperature);

/*
 * @brief  	This function is used to get i2c values from the sgp41
 * @param	hi2c is the i2c channel which we communicate
 * @retval 	return a struct_VN variable to get the NOx and VOC index
 */
struct_VN sgp41_receive_raw_datas(I2C_HandleTypeDef *hi2c);

#endif /* INC_I2C_H_ */
