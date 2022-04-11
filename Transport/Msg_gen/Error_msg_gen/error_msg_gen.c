/* Handddle
 * Communication module
 * 2022
 */

#include "../../Inc/msg_types.h"
#include "../../uid.h"
#include "../../Inc/transport.h"
#include "error_msg_gen.h"

HAL_StatusTypeDef send_error_msg_left_latch(UART_HandleTypeDef * uart )
{
	uint8_t Tx_msg_error_left_latch[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID, // UID of the STM32
		MSG_TYPE_ERROR, 								// Message type
		ERROR_MSG_LEFT_LATCH, 									// Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; 		// 12 first bytes

	for(int i = DATA; i< MSG_SIZE; i++)
		Tx_msg_error_left_latch[i] = ZERO;

	Tx_msg_error_left_latch[MSG_SIZE] = '\n';		// The 21st value -> Send (MSG_SIZE + 1) bytes
	return HAL_UART_Transmit(uart, Tx_msg_error_left_latch, MSG_SIZE+OFFSET_OF_1, DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_error_msg_right_latch(UART_HandleTypeDef * uart )
{
	uint8_t Tx_msg_error_right_latch[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID, // UID of the STM32
		MSG_TYPE_ERROR, 								// Message type
		ERROR_MSG_RIGHT_LATCH, 									// Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; 		// 12 first bytes

	for(int i = DATA; i< MSG_SIZE; i++)
		Tx_msg_error_right_latch[i] = ZERO;

	Tx_msg_error_right_latch[MSG_SIZE] = '\n';		// The 21st value -> Send (MSG_SIZE + 1) bytes
	return HAL_UART_Transmit(uart, Tx_msg_error_right_latch, MSG_SIZE+OFFSET_OF_1, DEFAULT_TIMEOUT);
}



HAL_StatusTypeDef send_error_msg_i2c_smart_power(UART_HandleTypeDef * uart )
{
	uint8_t Tx_msg_error_i2c_smart_power[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID, // UID of the STM32
		MSG_TYPE_ERROR, 								// Message type
		ERROR_MSG_I2C_SMART_POWER, 									// Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; 		// 12 first bytes

	for(int i = DATA; i< MSG_SIZE; i++)
		Tx_msg_error_i2c_smart_power[i] = ZERO;

	Tx_msg_error_i2c_smart_power[MSG_SIZE] = '\n';		// The 21st value -> Send (MSG_SIZE + 1) bytes
	return HAL_UART_Transmit(uart, Tx_msg_error_i2c_smart_power, MSG_SIZE+OFFSET_OF_1, DEFAULT_TIMEOUT);
}



HAL_StatusTypeDef send_error_msg_i2c_smart_sensor_1(UART_HandleTypeDef * uart )
{
	uint8_t Tx_msg_error_smart_sensor_1[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID, // UID of the STM32
		MSG_TYPE_ERROR, 								// Message type
		ERROR_MSG_I2C_SMART_SENSOR_1, 									// Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; 		// 12 first bytes

	for(int i = DATA; i< MSG_SIZE; i++)
		Tx_msg_error_smart_sensor_1[i] = ZERO;

	Tx_msg_error_smart_sensor_1[MSG_SIZE] = '\n';		// The 21st value -> Send (MSG_SIZE + 1) bytes
	return HAL_UART_Transmit(uart, Tx_msg_error_smart_sensor_1, MSG_SIZE+OFFSET_OF_1, DEFAULT_TIMEOUT);
}



HAL_StatusTypeDef send_error_msg_i2c_smart_sensor_2(UART_HandleTypeDef * uart )
{
	uint8_t Tx_msg_error_smart_sensor_2[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID, // UID of the STM32
		MSG_TYPE_ERROR, 								// Message type
		ERROR_MSG_I2C_SMART_SENSOR_2, 					// Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; 		// 12 first bytes

	for(int i = DATA; i< MSG_SIZE; i++)
		Tx_msg_error_smart_sensor_2[i] = ZERO;

	Tx_msg_error_smart_sensor_2[MSG_SIZE] = '\n';		// The 21st value -> Send (MSG_SIZE + 1) bytes
	return HAL_UART_Transmit(uart, Tx_msg_error_smart_sensor_2, MSG_SIZE+OFFSET_OF_1, DEFAULT_TIMEOUT);
}




