/* Handddle
 * Communication module
 * 2022
 */

#include "cmd_msg_parser.h"

// Message ACK header
uint8_t msg_ack_cmd[MSG_SIZE + 1] = {
	MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
	MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
	MSG_TYPE_COMMAND, 								// Message type
	CMD_ACK, 										// Sub message type
	MSG_LENGTH_FIRST_BYTE, MSG_LENGTH_1_SECOND_BYTE	// Length
}; 													// 12 first bytes

void build_ack_msg_cmd(uint8_t ack){
	// Ack value
	msg_ack_cmd[DATA] = ack;

	// Padding with zeros
	for (int i=DATA + 1; i<MSG_SIZE; i++)
		msg_ack_cmd[i] = ZERO;

	msg_ack_cmd[MSG_SIZE] = '\n'; // The 21st value -> Send (MSG_SIZE + 1) bytes
}

void send_cmd_ack(UART_HandleTypeDef * uart){
	build_ack_msg_cmd(ONE);
	HAL_UART_Transmit(uart, msg_ack_cmd, MSG_SIZE + 1, DEFAULT_TIMEOUT);
}

void send_cmd_ack_with_value(UART_HandleTypeDef * uart, uint8_t value){
	build_ack_msg_cmd(value);
	HAL_UART_Transmit(uart, msg_ack_cmd, MSG_SIZE + 1, DEFAULT_TIMEOUT);
}

void send_cmd_nok(UART_HandleTypeDef * uart){
	build_ack_msg_cmd(ZERO);
	HAL_UART_Transmit(uart, msg_ack_cmd, MSG_SIZE + 1, DEFAULT_TIMEOUT);
}


void parser_cmd_udpate_watchdog(uint8_t * rx_buff, UART_HandleTypeDef * uart){
	watchdog_update = true;
}

void parser_cmd_force_reset(uint8_t * rx_buff, UART_HandleTypeDef * uart){
	watchdog_actived = true;
}

void parser_cmd_cooling_fan(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];
	if(data >= MIN_PWM_FAN && data <= MAX_PWM_FAN)
	{
		pwm_cooling_fan = data;
	}
}

void parser_cmd_heater_fan(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];
	if(data >= MIN_PWM_FAN && data <= MAX_PWM_FAN)
	{
		pwm_heater_fan = data;
	}
}








void parser_cmd(uint8_t * rx_buff, UART_HandleTypeDef * uart){
	uint8_t cmd_type = rx_buff[INFORMATION_TYPE]; // The first byte has already been checked. We want the second one with the cmd type

	switch(cmd_type){
		case CMD_UPDATE_WATCHDOG:
			send_cmd_ack(uart);
			parser_cmd_udpate_watchdog(rx_buff, uart);
			break;
		case CMD_FORCE_RESET:
			send_cmd_ack(uart);
			parser_cmd_force_reset(rx_buff, uart);
			break;
		case CMD_COOLING_FAN:
			send_cmd_ack(uart);
			parser_cmd_cooling_fan(rx_buff, uart);
			break;
		case CMD_HEATER_FAN:
			send_cmd_ack(uart);
			parser_cmd_heater_fan(rx_buff, uart);
			break;
		default:
			send_cmd_nok(uart);
	}

}



