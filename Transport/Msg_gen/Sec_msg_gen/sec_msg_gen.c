/* Handddle
 * Communication module
 * 2022
 */

#include "sec_msg_gen.h"
#include "../../Inc/transport.h"

HAL_StatusTypeDef send_sec_msg_air_extraction_tachymeter(uint16_t tachy, UART_HandleTypeDef * uart){
	uint8_t Tx_msg_air_extraction_tachymeter[MSG_SIZE + ONE] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_AIR_EXTRACTION_TACHYMETER, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	Tx_msg_air_extraction_tachymeter[DATA] = tachy >> BYTE_OFFSET; // takes two bytes because it's a uint16_t value
	Tx_msg_air_extraction_tachymeter[DATA + ONE] = tachy;

	for(int i = DATA + TWO; i< MSG_SIZE; i++)
		Tx_msg_air_extraction_tachymeter[i] = ZERO;

	Tx_msg_air_extraction_tachymeter[MSG_SIZE] = '\n'; // The 21st value -> Send (MSG_SIZE + 1) bytes

	return HAL_UART_Transmit(uart,Tx_msg_air_extraction_tachymeter,MSG_SIZE+ONE,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_sec_msg_ee_temperature(float temp, UART_HandleTypeDef * uart){
	uint8_t Tx_msg_air_ee_temperature[MSG_SIZE + ONE] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_EE_TEMPERATURE, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t double_temp = temp * MULTIPLIER_FACTOR_100;
	Tx_msg_air_ee_temperature[DATA] = double_temp >> BYTE_OFFSET; // takes two bytes because it's a uint16_t value
	Tx_msg_air_ee_temperature[DATA + ONE] = double_temp;

	for(int i = DATA + TWO; i< MSG_SIZE; i++)
		Tx_msg_air_ee_temperature[i] = ZERO;

	Tx_msg_air_ee_temperature[MSG_SIZE] = '\n'; // The 21st value -> Send (MSG_SIZE + 1) bytes

	return HAL_UART_Transmit(uart,Tx_msg_air_ee_temperature,MSG_SIZE+ONE,DEFAULT_TIMEOUT);
}
