/* Handddle
 * Communication module
 * 2022
 */

#include "transport.h"
#include "../../Inc/msg_types.h"
#include "../../uid.h"

/** @def ERROR_MSG_X
 *  @brief Error ID for the X error message
 */
#define ERROR_MSG_X 0x00


/** @fn int send_error_msg_x(UART_HandleTypeDef * uart )
 * @brief Function used to send the x error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_x(UART_HandleTypeDef * uart );
