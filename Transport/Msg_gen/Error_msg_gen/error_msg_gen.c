/* Handddle
 * Communication module
 * 2022
 */

#include "error_msg_gen.h"

HAL_StatusTypeDef send_error_msg_x(UART_HandleTypeDef * uart )
{
	uint8_t Tx_msg_error_tachy_extract[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID, // UID of the STM32
		MSG_TYPE_ERROR, 								// Message type
		ERROR_MSG_X, 									// Sub message type
		MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
	}; 		// 12 first bytes

	for(int i = DATA; i< MSG_SIZE; i++)
		Tx_msg_error_tachy_extract[i] = ZERO;

	Tx_msg_error_tachy_extract[MSG_SIZE] = '\n';		// The 21st value -> Send (MSG_SIZE + 1) bytes
	return HAL_UART_Transmit(uart, Tx_msg_error_tachy_extract, MSG_SIZE+1, DEFAULT_TIMEOUT);
}
