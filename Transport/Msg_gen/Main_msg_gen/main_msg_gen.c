/* Handddle
 * Communication module
 * 2022
 */

#include "main_msg_gen.h"
#include "../../Inc/msg_types.h"
#include "../../uid.h"


HAL_StatusTypeDef send_main_msg_nox(uint16_t nox,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_nox[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_NOX, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	Tx_msg_nox[DATA] = nox >> 8;
	Tx_msg_nox[DATA+1] = nox >> 0;

	for(int i = DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_nox[i] = 0x00;

	Tx_msg_nox[MSG_SIZE] = '\n'; // The 21st value -> Send (MSG_SIZE + 1) bytes
	return HAL_UART_Transmit(uart,Tx_msg_nox,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_voc(uint16_t voc,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_voc[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_VOC, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_voc[DATA] = voc >> 8;
	Tx_msg_voc[DATA+1] = voc >> 0;

	for(int i = DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_voc[i] = 0x00;

	Tx_msg_voc[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_voc,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_sgp_initialization(bool sgp_initialization,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_sgp_init[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_SPG_INITIALIZATION, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	Tx_msg_sgp_init[DATA] = sgp_initialization;

	for(int i = DATA + 1; i< MSG_SIZE; i++)
		Tx_msg_sgp_init[i] = 0x00;

	Tx_msg_sgp_init[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_sgp_init,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_humidity(double humidity, UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_humidity[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_HUMIDITY, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	uint16_t humidity_bytes = humidity * 100;
	Tx_msg_humidity[DATA] = humidity_bytes >> 8; // humidity takes two bytes because it's a uint16_t value
	Tx_msg_humidity[DATA + 1] = humidity_bytes;

	for(int i = DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_humidity[i] = 0x00;

	Tx_msg_humidity[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_humidity,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_temperature(double temperature, UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_temperature[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_TEMPERATURE, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	uint16_t temperature_bytes = temperature * 100;
	Tx_msg_temperature[DATA] = temperature_bytes >> 8; // humidity takes two bytes because it's a uint16_t value
	Tx_msg_temperature[DATA + 1] = temperature_bytes;

	for(int i = DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_temperature[i] = 0x00;

	Tx_msg_temperature[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_temperature,MSG_SIZE+1,200);
}
