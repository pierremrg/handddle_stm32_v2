/* Handddle
 * Communication module
 * 2022
 */

#include "main.h"
#include "libraries.h"
#include "functions.h"
#include "defines.h"
#include "../../Inc/msg_types.h"
#include "../../Inc/transport.h"
#include "../../uid.h"


// Extern variables
bool watchdog_actived;
bool watchdog_update;

uint8_t pwm_cooling_fan;

uint8_t led_color;

bool sm_next;
bool sm_pause;
bool sm_stop;
bool sm_playback;
bool sm_previous;
uint8_t sm_volume;
uint8_t sm_eq;
uint8_t sm_track;
bool sm_repeat;

bool door_command;
bool door_state;

uint8_t desired_temperature;

bool relay_command;

bool static_light;


/** @def CMD_ACK
 *  @brief Message ID for the ack when it's a command message
 */
#define CMD_ACK 									0x00

/** @def CMD_UPDATE_WATCHDOG
 *  @brief Command ID for the watchdog
 */
#define CMD_UPDATE_WATCHDOG 						0x01

/** @def CMD_FORCE_RESET
 *  @brief Command ID to force reset
 */
#define CMD_FORCE_RESET 							0x02

/** @def CMD_COOLING_FAN
 *  @brief Command ID to run the cooling fan at given dutycyle
 */
#define CMD_COOLING_FAN 							0x03

/** @def CMD_TEMPERATURE
 *  @brief Command ID to set desired temperature heater
 */
#define CMD_TEMPERATURE 							0x04

/** @def CMD_LIGHT_COLOR
 *  @brief Command ID to set a color
 */
#define CMD_LIGHT_COLOR 							0x05

/** @def CMD_ON_OFF
 *  @brief Command ID to put the system in standby mode
 */
#define CMD_ON_OFF		 							0x06

/** @def CMD_DOOR
 *  @brief Command ID to lock or unlock the door
 */
#define CMD_DOOR									0x07

/** @def CMD_RELAY
 *  @brief Command ID to activate or deactivate the relay
 */
#define CMD_RELAY									0x0A

/** @def CMD_SOUND_MODULE_VOLUME
 *  @brief Command ID to modify the volume
 */
#define CMD_SOUND_MODULE_VOLUME						0x0F

/** @def CMD_SOUND_MODULE_EQ
 *  @brief Command ID to select an EQ
 */
#define CMD_SOUND_MODULE_EQ							0x10

/** @def CMD_SOUND_MODULE_TRACK
 *  @brief Command ID to select a track
 */
#define CMD_SOUND_MODULE_SELECT_TRACK				0x11

/** @def CMD_SOUND_MODULE_REPEAT
 *  @brief Command ID to repeat or not the track
 */
#define CMD_SOUND_MODULE_REPEAT						0x12

/** @def CMD_SOUND_MODULE_SIMPLE_CMD
 *  @brief Command ID to select a function
 */
#define CMD_SOUND_MODULE_SIMPLE_CMD 				0x13


/*	@fn 	void parser_cmd_update_watchdog(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to update watchdog's value for each watchog message received
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_update_watchdog(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_force_reset(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to forced the stm32 to reset
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_force_reset(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_cooling_fan(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to parse the command value to send to the cooling fan
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_cooling_fan(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_heater_temperature(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to parse the command value to send to the heater fan
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_heater_temperature(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_led_color(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to parse the command value to send to the register of timer (to set a color)
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_led_color(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_door(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to parse the command value to lock or unlock the door
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_door(uint8_t * rx_buff, UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_relay(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to activate or deactivate the relay
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_relay(uint8_t * rx_buff, UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_sound_module_simple_command(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * 	@brief 	Function used to parse the command value to select the right sound module function
 * 	@param 	rx_buff Pointer to the array tab containing the message received
 * 	@param 	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_sound_module_simple_command(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_sound_module_volume(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * 	@brief 	Function used to parse the command value to select the volume
 * 	@param 	rx_buff Pointer to the array tab containing the message received
 * 	@param 	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_sound_module_volume(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_sound_module_eq(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * 	@brief 	Function used to parse the command value to select the eq
 * 	@param 	rx_buff Pointer to the array tab containing the message received
 * 	@param 	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_sound_module_eq(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_sound_module_select_track(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * 	@brief 	Function used to parse the command value to select the track
 * 	@param 	rx_buff Pointer to the array tab containing the message received
 * 	@param 	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_sound_module_select_track(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_sound_module_repeat(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * 	@brief 	Function used to parse the command value to loop or not the current track
 * 	@param 	rx_buff Pointer to the array tab containing the message received
 * 	@param 	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_sound_module_repeat(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_on_off(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to put the system on or off
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_on_off(uint8_t * rx_buff, UART_HandleTypeDef * uart);









/*	@fn 	void parser_cmd(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 *	@brief 	Function used to parse each message received from the Jetson Nano
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd(uint8_t * rx_buff, UART_HandleTypeDef * uart);

/* @fn 		void build_ack_msg_cmd(uint8_t ack)
 * @brief 	Function used for the ack message, for command messages.
 * @param 	ack Value for the ack message. 1 -> OK 0 -> NOK
 */
void build_ack_msg_cmd(uint8_t ack);

/* @fn 		void send_cmd_ack(UART_HandleTypeDef * uart)
 * @brief 	Function used to send an ack message to the Jetson Nano
 * @param 	uart Uart strcture used for the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void send_cmd_ack(UART_HandleTypeDef * uart);

/* @fn 		void send_cmd_ack(UART_HandleTypeDef * uart)
 * @brief 	Function used to send an ack message to the Jetson Nano with a specific value
 * @param 	uart Uart strcture used for the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @param 	value is the value to send as an ack value
 */
void send_cmd_ack_with_value(UART_HandleTypeDef * uart, uint8_t value);

/* @fn 		void send_cmd_nok(UART_HandleTypeDef * uart)
 * @brief	Function used to send an nok (not ok) message to the Jetson Nano, if an unknown command type is received -> Sending ACK NOK
 * @param	uart Uart strcture used for the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void send_cmd_nok(UART_HandleTypeDef * uart);
