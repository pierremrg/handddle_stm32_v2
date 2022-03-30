/* Handddle
 * Communication module
 * 2022
 */

#include "main.h"

/*  @def 	MAIN_MSG_LIGHT_COLOR
 *  @brief 	Main message ID for the voc main message
 */
#define MAIN_MSG_LIGHT_COLOR 0x00

/*  @def 	MAIN_MSG_VOC
 *  @brief 	Main message ID for the voc main message
 */
#define MAIN_MSG_VOC 0x01

/*  @def 	MAIN_MSG_NOX
 *  @brief 	Main message ID for the nox main message
 */
#define MAIN_MSG_NOX 0x02

/*  @def 	MAIN_MSG_SPG_INITIALIZATION
 *  @brief 	Main message ID for the sgp initialization time main message
 */
#define MAIN_MSG_SPG_INITIALIZATION 0x03

/*  @def 	MAIN_MSG_HUMIDITY
 *  @brief 	Main message ID for the humidity main message
 */
#define MAIN_MSG_HUMIDITY 0x04

/*  @def MAIN_MSG_TEMPERATURE
 *  @brief Main message ID for the temperature main message
 */
#define MAIN_MSG_TEMPERATURE 0x05

/* @fn 		HAL_StatusTypeDef send_main_msg_led_color(uint8_t light_color,UART_HandleTypeDef * uart )
 * @brief 	Function used to send the light color value message
 * @param 	light_color is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_led_color(uint8_t light_color,UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_nox(uint16_t nox,UART_HandleTypeDef * uart )
 * @brief 	Function used to send the nox value message
 * @param 	nox is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_nox(uint16_t nox,UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_voc(uint16_t voc,UART_HandleTypeDef * uart )
 * @brief 	Function used to send the voc value message
 * @param 	voc is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_voc(uint16_t voc,UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_sgp_initialization(bool sgp_initialization,UART_HandleTypeDef * uart )
 * @brief 	Function used to send the sgp_initialization value message
 * @param 	sgp_initialization is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_sgp_initialization(bool sgp_initialization,UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_temperature(double temperature, UART_HandleTypeDef * uart )
 * @brief 	Function used to send the temperature value message
 * @note	temperature is a double, because it's a float value
 * @param 	temperature is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_temperature(double temperature, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_humidity(double humidity, UART_HandleTypeDef * uart )
 * @brief 	Function used to send the temperature value message
 * @note	temperature is a double, because it's a float value
 * @param 	temperature is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_humidity(double humidity, UART_HandleTypeDef * uart );
