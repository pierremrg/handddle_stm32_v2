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
uint8_t pwm_heater_fan;

uint8_t light_color;



/** @def CMD_ACK
 *  @brief Message ID for the ack when it's a command message
 */
#define CMD_ACK 0x00

/** @def CMD_UPDATE_WATCHDOG
 *  @brief Command ID for the watchdog
 */
#define CMD_UPDATE_WATCHDOG 0x01

/** @def CMD_FORCE_RESET
 *  @brief Command ID to force reset
 */
#define CMD_FORCE_RESET 0x02

/** @def CMD_COOLING_FAN
 *  @brief Command ID to run the cooling fan at given dutycyle
 */
#define CMD_COOLING_FAN 0x03

/** @def CMD_HEATER_FAN
 *  @brief Command ID to run the heater fan at given dutycyle
 */
#define CMD_HEATER_FAN 0x04

/** @def CMD_LIGHT_COLOR
 *  @brief Command ID to set a color
 */
#define CMD_LIGHT_COLOR 0x05


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

/*	@fn 	void parser_cmd_heater_fan(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to parse the command value to send to the heater fan
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_heater_fan(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/*	@fn 	void parser_cmd_light_color(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 *	@brief 	Function used to parse the command value to send to the register of timer (to set a color)
 *	@param	rx_buff Pointer to the array tab containing the message received
 *	@param	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_light_color(uint8_t * rx_buff,UART_HandleTypeDef * uart);











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