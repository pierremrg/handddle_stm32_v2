/* Handddle
 * Communication module
 * 2022
 */

#include "parser.h"


// Message ACK header
uint8_t msg_ack[MSG_SIZE + 1] = {
	MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
	MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
	MSG_TYPE_INFORMATION, // Message type
	CMD_ACK, // Sub message type
	MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE // Length
}; // 12 first bytes

bool check_msg_identifier(uint8_t * rx_buff)
{
	return rx_buff[IDENTIFIER_FIRST_BYTE] == MSG_HEADER_IDENTIFIER_FIRST_BYTE
		&& rx_buff[IDENTIFIER_SECOND_BYTE] == MSG_HEADER_IDENTIFIER_SECOND_BYTE;
}

bool check_msg_UID(uint8_t * rx_buff)
{
	bool is_receiver = rx_buff[UID_1_TYPOLOGY] == MSG_HEADER_UID_1_TYPOLOGY
				    && rx_buff[UID_2_MONTH] == MSG_HEADER_UID_2_MONTH
					&& rx_buff[UID_3_YEAR] == MSG_HEADER_UID_3_YEAR
				    && rx_buff[UID_4_ID] == MSG_HEADER_UID_4_ID;

	bool is_broadcast = rx_buff[UID_1_TYPOLOGY] == MSG_HEADER_UID_1_BROADCAST
					 && rx_buff[UID_2_MONTH] == MSG_HEADER_UID_BROADCAST
					 && rx_buff[UID_3_YEAR] == MSG_HEADER_UID_BROADCAST
					 && rx_buff[UID_4_ID] == MSG_HEADER_UID_BROADCAST;

	return (is_receiver || is_broadcast);
}

bool check_msg_size(uint8_t * rx_buff)
{
	return rx_buff[LENGTH_FIRST_BYTE] == MSG_HEADER_SIZE_FIRST_BYTE
		&& rx_buff[LENGTH_SECOND_BYTE] == MSG_HEADER_SIZE_SECOND_BYTE;
}

void build_ack_msg(uint8_t ack)
{
	// Ack value
	msg_ack[DATA] = ack;

	// Padding with zeros
	for (int i=DATA + 1; i < MSG_SIZE; i++)
	{
		msg_ack[i] = ZERO;
	}
}

void parser(uint8_t * rx_buff, UART_HandleTypeDef * uart)
{

	if(check_msg_identifier(rx_buff))
	{

		// This message is from the Jetson Nano
		if(check_msg_size(rx_buff))
		{

			// This message has the correct size
			if(check_msg_UID(rx_buff))
			{

				// This messages is for this STM32
				uint8_t msg_type = rx_buff[MSG_TYPE];

				switch(msg_type)
				{
					case MSG_TYPE_COMMAND:
						parser_cmd(rx_buff, uart);
						break;
					default:
						// Unknown message --> Sending ACK NOK
						build_ack_msg(ZERO);
						HAL_UART_Transmit(uart, msg_ack, MSG_SIZE, DEFAULT_TIMEOUT);
						break;
				}
			}
		}
	}
}
