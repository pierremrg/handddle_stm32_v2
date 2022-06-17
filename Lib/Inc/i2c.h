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

#define SEN5X_ADDRESS							0x69


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

//Enumerate index of elements of SEN5X command array
typedef enum {

	SEN5X_COMMAND_START_MEASUREMENT = 0x0021,

	SEN5X_COMMAND_READ_ALL_VALUES   = 0x03C4,

	SEN5X_FIRST_BYTE_COMMAND    	= 0,
	SEN5X_SECOND_BYTE_COMMAND   	= 1,


} sen5x_index_cmd_array;

//Enumerate index of elements of SEN5X command array
typedef enum {

	SEN5X_PM1_FIRST_BYTE			= 0,
	SEN5X_PM1_SECOND_BYTE  			= 1,
	SEN5X_PM1_CRC_BYTE  			= 2,

	SEN5X_PM2_5_FIRST_BYTE 			= 3,
	SEN5X_PM2_5_SECOND_BYTE 		= 4,
	SEN5X_PM2_5_CRC_BYTE 			= 5,

	SEN5X_PM4_FIRST_BYTE 			= 6,
	SEN5X_PM4_SECOND_BYTE 			= 7,
	SEN5X_PM4_CRC_BYTE 				= 8,

	SEN5X_PM10_FIRST_BYTE 			= 9,
	SEN5X_PM10_SECOND_BYTE 			= 10,
	SEN5X_PM10_CRC_BYTE 			= 11,

	SEN5X_TEMPERATURE_FIRST_BYTE 	= 12,
	SEN5X_TEMPERATURE_SECOND_BYTE 	= 13,
	SEN5X_TEMPERATURE_CRC_BYTE 		= 14,

	SEN5X_HUMIDITY_FIRST_BYTE 		= 15,
	SEN5X_HUMIDITY_SECOND_BYTE 		= 16,
	SEN5X_HUMIDITY_CRC_BYTE 		= 17,

	SEN5X_VOC_INDEX_FIRST_BYTE 		= 18,
	SEN5X_VOC_INDEX_SECOND_BYTE 	= 19,
	SEN5X_VOC_INDEX_CRC_BYTE 		= 20,

	SEN5X_NOX_INDEX_FIRST_BYTE 		= 21,
	SEN5X_NOX_INDEX_SECOND_BYTE 	= 22,
	SEN5X_NOX_INDEX_CRC_BYTE 		= 23,

} sen5x_index_buffer_array;


/*
 * @brief  	This function is used to collect Temperature & Humidity with the SHT40.
 * @param	hi2c_x is the i2c channel which we send the frame
 * @retval 	return an HAL_StatusTypeDef variable to know if we can communicate with the SHT40
 */
HAL_StatusTypeDef write_frame_temp_humi_sht40(I2C_HandleTypeDef *hi2c_x);

/*
 * @brief  	This function is used to send an UART frame to the SHT40.
 * @param	hi2c_x is the i2c channel which we send the frame
 * @retval 	return a Struct_TH variable to get the temperature and the humidity rate
 */
struct_sht40 read_temp_humi_sht40(I2C_HandleTypeDef *hi2c_x);

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
 * @retval 	return a struct_sgp41 variable to get the NOx and VOC index
 */
struct_sgp41 sgp41_receive_raw_datas(I2C_HandleTypeDef *hi2c);

/*
 * @brief  	This function is used to collect datas from with the SEN5X sensor.
 * @param	hi2c_x is the i2c channel which we send the frame
 * @param 	command is the command ID to send to the sen5x
 * @retval 	return an HAL_StatusTypeDef variable to know if we can communicate with the sensor
 */
HAL_StatusTypeDef write_frame_sen5x(I2C_HandleTypeDef *hi2c_x, uint16_t command);

/*
 * @brief  	This function is used to send an UART frame to the SEN5X.
 * @param	hi2c_x is the i2c channel which we send the frame
 * @retval 	return a struct_sen5x variable to get all datas from the sensor
 */
struct_sen5x read_datas_sen5x(I2C_HandleTypeDef *hi2c_x);

#endif /* INC_I2C_H_ */
