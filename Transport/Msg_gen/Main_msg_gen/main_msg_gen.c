/* Handddle
 * Communication module
 * 2022
 */

#include "main_msg_gen.h"
#include "../../Inc/msg_types.h"
#include "../../uid.h"
#include "../../Inc/transport.h"


HAL_StatusTypeDef send_main_msg_led_color(uint8_t light_color,UART_HandleTypeDef * uart ){
	uint8_t tx_msg_light_color[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_LIGHT_COLOR, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	tx_msg_light_color[DATA] = light_color;

	for(int i = DATA + OFFSET_OF_1; i< MSG_SIZE; i++)
		tx_msg_light_color[i] = ZERO;

	tx_msg_light_color[MSG_SIZE] = '\n';	// The 21st value -> Send (MSG_SIZE + OFFSET_OF_1) bytes
	return HAL_UART_Transmit(uart,tx_msg_light_color,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_relay(uint8_t relay_state,UART_HandleTypeDef * uart ){
	uint8_t tx_msg_relay_state[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_RELAY, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	tx_msg_relay_state[DATA] = relay_state;

	for(int i = DATA + OFFSET_OF_1; i< MSG_SIZE; i++)
		tx_msg_relay_state[i] = ZERO;

	tx_msg_relay_state[MSG_SIZE] = '\n';	// The 21st value -> Send (MSG_SIZE + OFFSET_OF_1) bytes
	return HAL_UART_Transmit(uart,tx_msg_relay_state,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_nox(uint16_t nox,UART_HandleTypeDef * uart ){
	uint8_t tx_msg_nox[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_NOX, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	tx_msg_nox[DATA] = nox >> BYTE_OFFSET;
	tx_msg_nox[DATA+OFFSET_OF_1] = nox >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_nox[i] = ZERO;

	tx_msg_nox[MSG_SIZE] = '\n'; // The 21st value -> Send (MSG_SIZE + OFFSET_OF_1) bytes
	return HAL_UART_Transmit(uart,tx_msg_nox,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_voc(uint16_t voc,UART_HandleTypeDef * uart ){
	uint8_t tx_msg_voc[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_VOC, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	tx_msg_voc[DATA] = voc >> BYTE_OFFSET;
	tx_msg_voc[DATA+OFFSET_OF_1] = voc >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_voc[i] = ZERO;

	tx_msg_voc[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,tx_msg_voc,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_humidity(double humidity, uint8_t MAIN_MSG_ID,UART_HandleTypeDef * uart ){
	uint8_t tx_msg_humidity[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_ID, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	tx_msg_humidity[DATA] = (uint8_t)humidity;

	for(int i = DATA + OFFSET_OF_1; i< MSG_SIZE; i++)
		tx_msg_humidity[i] = ZERO;

	tx_msg_humidity[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,tx_msg_humidity,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_temperature(float temperature, uint8_t MAIN_MSG_ID, UART_HandleTypeDef * uart ){
	uint8_t tx_msg_temperature[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_ID, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t temperature_bytes = temperature * MULTIPLIER_FACTOR_10; // to send a OFFSET_OF_2-byte value
	tx_msg_temperature[DATA] = temperature_bytes >> BYTE_OFFSET; // humidity takes two bytes because it's a uint16_t value
	tx_msg_temperature[DATA + OFFSET_OF_1] = temperature_bytes;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_temperature[i] = ZERO;

	tx_msg_temperature[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,tx_msg_temperature,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_pressure(uint16_t pressure, UART_HandleTypeDef * uart ){
	uint8_t tx_msg_pressure[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PRESSURE, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	tx_msg_pressure[DATA] = pressure >> BYTE_OFFSET;
	tx_msg_pressure[DATA+OFFSET_OF_1] = pressure >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_pressure[i] = ZERO;

	tx_msg_pressure[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,tx_msg_pressure,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}


HAL_StatusTypeDef send_main_msg_door_state(uint8_t door_state, UART_HandleTypeDef * uart ){
	uint8_t tx_msg_door_state[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_DOOR_STATE, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; // 12 first bytes

	tx_msg_door_state[DATA] = door_state;

	for(int i = DATA + OFFSET_OF_1; i< MSG_SIZE; i++)
		tx_msg_door_state[i] = ZERO;

	tx_msg_door_state[MSG_SIZE] = '\n';	// The 21st value -> Send (MSG_SIZE + OFFSET_OF_1) bytes
	return HAL_UART_Transmit(uart,tx_msg_door_state,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_pm1(float pm1, UART_HandleTypeDef * uart ){
	uint8_t tx_msg_pm1[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PM1, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t pm1_bytes = pm1 * MULTIPLIER_FACTOR_10;
	tx_msg_pm1[DATA] 				= pm1_bytes >> BYTE_OFFSET;
	tx_msg_pm1[DATA+OFFSET_OF_1] 	= pm1_bytes >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_pm1[i] = ZERO;

	tx_msg_pm1[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,tx_msg_pm1,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_pm2_5(float pm2_5, UART_HandleTypeDef * uart ){
	uint8_t tx_msg_pm2_5[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PM2_5, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t pm2_5_bytes = pm2_5 * MULTIPLIER_FACTOR_10;
	tx_msg_pm2_5[DATA] 				= pm2_5_bytes >> BYTE_OFFSET;
	tx_msg_pm2_5[DATA+OFFSET_OF_1] 	= pm2_5_bytes >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_pm2_5[i] = ZERO;

	tx_msg_pm2_5[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,tx_msg_pm2_5,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_pm4(float pm4, UART_HandleTypeDef * uart ){
	uint8_t tx_msg_pm4[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PM4, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t pm4_bytes = pm4 * MULTIPLIER_FACTOR_10;
	tx_msg_pm4[DATA] 				= pm4_bytes >> BYTE_OFFSET;
	tx_msg_pm4[DATA+OFFSET_OF_1] 	= pm4_bytes >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_pm4[i] = ZERO;

	tx_msg_pm4[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,tx_msg_pm4,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}

HAL_StatusTypeDef send_main_msg_pm10(float pm10, UART_HandleTypeDef * uart ){
	uint8_t tx_msg_pm10[MSG_SIZE + OFFSET_OF_1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PM10, // Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_2_SECOND_BYTE // Length
	}; // 12 first bytes

	uint16_t pm10_bytes = pm10 * MULTIPLIER_FACTOR_10;
	tx_msg_pm10[DATA] 				= pm10_bytes >> BYTE_OFFSET;
	tx_msg_pm10[DATA+OFFSET_OF_1] 	= pm10_bytes >> ZERO;

	for(int i = DATA + OFFSET_OF_2; i< MSG_SIZE; i++)
		tx_msg_pm10[i] = ZERO;

	tx_msg_pm10[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,tx_msg_pm10,MSG_SIZE+OFFSET_OF_1,DEFAULT_TIMEOUT);
}
