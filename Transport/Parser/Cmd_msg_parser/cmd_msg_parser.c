/* Handddle
 * Communication module
 * 2022
 */

#include "cmd_msg_parser.h"

// Message ACK header
uint8_t msg_ack_cmd[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_FIRST_BYTE, MSG_HEADER_IDENTIFIER_SECOND_BYTE, MSG_HEADER_SIZE_FIRST_BYTE, MSG_HEADER_SIZE_SECOND_BYTE, // Global information
		MSG_HEADER_UID_1_TYPOLOGY, MSG_HEADER_UID_2_MONTH, MSG_HEADER_UID_3_YEAR, MSG_HEADER_UID_4_ID,  // UID of the STM32
		MSG_TYPE_INFORMATION, 							// Message type
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
	if(data >= MIN_PWM_FAN && data <= MAX_PWM_FAN && door_state == CLOSED)
	{
		pwm_cooling_fan = data;
		heater_activated = false;
	}
}

void parser_cmd_heater_temperature(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];
	heater_activated = true;
	desired_temperature = data;
}

void parser_cmd_led_color(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];

	if(door_state == CLOSED)
	{
		if(data >= LIGHT_COLOR_MIN_INDEX && data <= LIGHT_COLOR_MAX_INDEX)
		{
			static_light = true;
			led_color = data;
		} else if(data >= LIGHT_COLOR_MIN_INDEX + FADE_OFFSET
				&& data <= LIGHT_COLOR_MAX_INDEX + FADE_OFFSET)
		{
			static_light = false;
			led_color = data - FADE_OFFSET;
		}
	}
}

void parser_cmd_door(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];

	if((data == CLOSED || data == OPENED) && (MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF || MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT))
	{
		door_command = data;
	}
}

void parser_cmd_relay(uint8_t * rx_buff, UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];

	if((data == RELAY_ON || data == RELAY_OFF) && (MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_RACK || MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT))
	{
		relay_command = data;
	}
}

void parser_cmd_sound_module_simple_command(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];

	switch (data) {
	case 1:
		sm_previous = true;
		break;
	case 2:
		sm_next = true;
		break;
	case 3:
		sm_pause = true;
		break;
	case 4:
		sm_playback = true;
		break;
	case 5:
		sm_stop = true;
		break;
	}
}

void parser_cmd_sound_module_volume(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];
	if(data >= SOUND_MODULE_MIN_VOLUME && data <= SOUND_MODULE_MAX_VOLUME)
	{
		sm_volume = data;
	}
}

void parser_cmd_sound_module_eq(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];
	if(data >= SOUND_MODULE_MIN_EQ && data <= SOUND_MODULE_MAX_EQ)
	{
		sm_eq = data;
	}
}

void parser_cmd_sound_module_select_track(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];
	if(data >= SOUND_MODULE_MIN_EQ && data <= SOUND_MODULE_MAX_EQ)
	{
		sm_track = data;
	}
}

void parser_cmd_sound_module_repeat(uint8_t * rx_buff,UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];
	if(data == ONE || data == TWO)
	{
		sm_repeat = data;
	}
}

void parser_cmd_on_off(uint8_t * rx_buff, UART_HandleTypeDef * uart)
{
	uint8_t data = rx_buff[DATA];

	if(data == SYSTEM_ON || data == SYSTEM_OFF)
	{
		system_on_off = data;
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
	case CMD_TEMPERATURE:
		send_cmd_ack(uart);
		parser_cmd_heater_temperature(rx_buff, uart);
		break;
	case CMD_LIGHT_COLOR:
		send_cmd_ack(uart);
		parser_cmd_led_color(rx_buff, uart);
		break;
	case CMD_DOOR:
		send_cmd_ack(uart);
		parser_cmd_door(rx_buff, uart);
		break;
	case CMD_SOUND_MODULE_VOLUME:
		send_cmd_ack(uart);
		parser_cmd_sound_module_volume(rx_buff, uart);
		break;
	case CMD_SOUND_MODULE_EQ:
		send_cmd_ack(uart);
		parser_cmd_sound_module_eq(rx_buff, uart);
		break;
	case CMD_SOUND_MODULE_SELECT_TRACK:
		send_cmd_ack(uart);
		parser_cmd_sound_module_select_track(rx_buff, uart);
		break;
	case CMD_SOUND_MODULE_REPEAT:
		send_cmd_ack(uart);
		parser_cmd_sound_module_repeat(rx_buff, uart);
		break;
	case CMD_SOUND_MODULE_SIMPLE_CMD:
		send_cmd_ack(uart);
		parser_cmd_sound_module_simple_command(rx_buff, uart);
		break;
	case CMD_RELAY:
		send_cmd_ack(uart);
		parser_cmd_relay(rx_buff, uart);
		break;
	case CMD_ON_OFF:
		send_cmd_ack(uart);
		parser_cmd_on_off(rx_buff, uart);
		break;
	default:
		send_cmd_nok(uart);
	}

}



