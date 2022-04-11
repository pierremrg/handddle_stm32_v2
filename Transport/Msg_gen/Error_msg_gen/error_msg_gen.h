/* Handddle
 * Communication module
 * 2022
 */

#include "main.h"

/** @def ERROR_MSG_LEFT_LATCH
 *  @brief Error ID for the left latch error message
 */
#define ERROR_MSG_LEFT_LATCH 			0x00

/** @def ERROR_MSG_RIGHT_LATCH
 *  @brief Error ID for the left latch error message
 */
#define ERROR_MSG_RIGHT_LATCH			0x01

/** @def ERROR_MSG_I2C_SMART_POWER
 *  @brief Error ID for the i2c communication error message
 */
#define ERROR_MSG_I2C_SMART_POWER		0x02

/** @def ERROR_MSG_I2C_SMART_SENSOR_1
 *  @brief Error ID for the i2c communication error message
 */
#define ERROR_MSG_I2C_SMART_SENSOR_1	0x03

/** @def ERROR_MSG_I2C_SMART_SENSOR_2
 *  @brief Error ID for the i2c communication error message
 */
#define ERROR_MSG_I2C_SMART_SENSOR_2	0x04


/* @fn HAL_StatusTypeDef send_error_msg_left_latch(UART_HandleTypeDef * uart)
 * @brief Function used to send the left latch error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_left_latch(UART_HandleTypeDef * uart );

/* @fn HAL_StatusTypeDef send_error_msg_right_latch(UART_HandleTypeDef * uart)
 * @brief Function used to send the right latch error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_right_latch(UART_HandleTypeDef * uart );

/* @fn HAL_StatusTypeDef send_error_msg_i2c_smart_power(UART_HandleTypeDef * uart )
 * @brief Function used to send the i2c smart power error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_i2c_smart_power(UART_HandleTypeDef * uart );

/* @fn HAL_StatusTypeDef send_error_msg_i2c_smart_sensor_1(UART_HandleTypeDef * uart )
 * @brief Function used to send the i2c smart sensors 1 error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_i2c_smart_sensor_1(UART_HandleTypeDef * uart );

/* @fn HAL_StatusTypeDef send_error_msg_i2c_smart_sensor_2(UART_HandleTypeDef * uart )
 * @brief Function used to send the i2c smart sensors 2 error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_i2c_smart_sensor_2(UART_HandleTypeDef * uart );
