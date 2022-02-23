/* Handddle
 * Communication module
 * 2022
 */

#include "main.h"
#include "Cmd_msg_parser/cmd_msg_parser.h"
#include "../uid.h"
#include "../Inc/msg_types.h"


/*  @fn 	bool check_msg_size(uint8_t * rx_buff)
 *  @brief 	Function used to check the identifier of the messages
 *  @param	rx_buff Pointer to the array tab containing the message received
 */
bool check_msg_identifier(uint8_t * rx_buff);

/*  @fn 	bool check_msg_UID(uint8_t * rx_buff)
 *  @brief 	Function used to check the UID in the messages. If not the same as the one defined for the STM32, the message is not for us.
 *  @param	rx_buff Pointer to the array tab containing the message received
 */
bool check_msg_UID(uint8_t * rx_buff);

/*  @fn 	bool check_msg_size(uint8_t * rx_buff)
 *  @brief 	The message has to be check because if it is not correct it might suggest that the code version are not the same between the STM32 and Jetson boards.
 *  @param	rx_buff Pointer to the array tab containing the message received
 */
bool check_msg_size(uint8_t * rx_buff);

/** @fn void build_ack_msg(uint8_t ack)
 * @brief General function used for the ack message. If the message is not recognized, a NON ack is sent
 * @param ack Value for the ack message. 1 -> OK 0 -> NOK
 */
void build_ack_msg(uint8_t ack);

/** @fn void parser(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * @brief For every messages received, a ACK message is sent. If it is a OK ACK, it will have the cmd or info type.
 * @note  Depending on the type defined, there are special parsers used to parse the message
 * @note  General parser function used to dispatch every message to the correct parser depending on the message type
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser(uint8_t * rx_buff, UART_HandleTypeDef * uart);
