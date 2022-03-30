/* Handddle
 * Communication module
 * 2022
 */

#include "main_msg_gen.h"
#include "../../Inc/msg_types.h"
#include "../../uid.h"
#include "../../Inc/transport.h"


HAL_StatusTypeDef send_main_msg_led_color(uint8_t light_color,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_light_color[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_LIGHT_COLOR, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	Tx_msg_light_color[DATA] = light_color;

	for(int i = DATA + OFFSET_OF_1; i< MSG_SIZE; i++)
		Tx_msg_light_color[i] = ZERO;

	Tx_msg_light_color[MSG_SIZE] = '\n';	// The 21st value -> Send (MSG_SIZE + OFFSET_OF_1) bytes
	return HAL_UART_Transmit(uart,Tx_msg_light_color,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_nox(uint16_t nox,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_nox[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_NOX, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	Tx_msg_nox[DATA] = nox >> BYTE_OFFSET;
	Tx_msg_nox[DATA+OFFSET_OF_1] = nox >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		Tx_msg_nox[i] = ZERO;

	Tx_msg_nox[MSG_SIZE] = '\n'; // The 21st value -> Send (MSG_SIZE + OFFSET_OF_1) bytes
	return HAL_UART_Transmit(uart,Tx_msg_nox,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_voc(uint16_t voc,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_voc[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_VOC, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	Tx_msg_voc[DATA] = voc >> BYTE_OFFSET;
	Tx_msg_voc[DATA+OFFSET_OF_1] = voc >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		Tx_msg_voc[i] = ZERO;

	Tx_msg_voc[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_voc,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_sgp_initialization(bool sgp_initialization,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_sgp_init[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_SPG_INITIALIZATION, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	Tx_msg_sgp_init[DATA] = sgp_initialization;

	for(int i = DATA + OFFSET_OF_1; i< MSG_SIZE; i++)
		Tx_msg_sgp_init[i] = ZERO;

	Tx_msg_sgp_init[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_sgp_init,MSG_SIZE+OFFSET_OF_1, DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_humidity(double humidity, UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_humidity[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_HUMIDITY, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t humidity_bytes = humidity * MULTIPLIER_FACTOR_100;
	Tx_msg_humidity[DATA] = humidity_bytes >> BYTE_OFFSET; // humidity takes two bytes because it's a uint16_t value
	Tx_msg_humidity[DATA + OFFSET_OF_1] = humidity_bytes;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		Tx_msg_humidity[i] = ZERO;

	Tx_msg_humidity[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_humidity,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_temperature(double temperature, UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_temperature[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_TEMPERATURE, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t temperature_bytes = temperature * MULTIPLIER_FACTOR_100; // to send a OFFSET_OF_2-byte value
	Tx_msg_temperature[DATA] = temperature_bytes >> BYTE_OFFSET; // humidity takes two bytes because it's a uint16_t value
	Tx_msg_temperature[DATA + OFFSET_OF_1] = temperature_bytes;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		Tx_msg_temperature[i] = ZERO;

	Tx_msg_temperature[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_temperature,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}
