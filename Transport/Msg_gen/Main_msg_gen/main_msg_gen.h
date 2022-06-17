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

/*  @def 	MAIN_MSG_RELAY
 *  @brief 	Main message ID for the relay main message
 */
#define MAIN_MSG_RELAY 0x03

/*  @def 	MAIN_MSG_HUMIDITY_SP
 *  @brief 	Main message ID for the humidity main message (from SMART POWER)
 */
#define MAIN_MSG_HUMIDITY_SP 0x04

/*  @def MAIN_MSG_TEMPERATURE_SP
 *  @brief Main message ID for the temperature main message (from SMART POWER)
 */
#define MAIN_MSG_TEMPERATURE_SP 0x05

/*  @def 	MAIN_MSG_HUMIDITY_SS_1
 *  @brief 	Main message ID for the humidity main message (from SMART SENSOR 1)
 */
#define MAIN_MSG_HUMIDITY_SS_1 0x06

/*  @def MAIN_MSG_TEMPERATURE_SS_1
 *  @brief Main message ID for the temperature main message (from SMART SENSOR 1)
 */
#define MAIN_MSG_TEMPERATURE_SS_1 0x07

/*  @def 	MAIN_MSG_HUMIDITY_SS_2
 *  @brief 	Main message ID for the humidity main message (from SMART SENSOR 2)
 */
#define MAIN_MSG_HUMIDITY_SS_2 0x08

/*  @def MAIN_MSG_TEMPERATURE_SS_2
 *  @brief Main message ID for the temperature main message (from SMART SENSOR 2)
 */
#define MAIN_MSG_TEMPERATURE_SS_2 0x09

/*  @def 	MAIN_MSG_HUMIDITY_SEN5X
 *  @brief 	Main message ID for the humidity main message (from SEN5X sensor)
 */
#define MAIN_MSG_HUMIDITY_SEN5X 0x0A

/*  @def MAIN_MSG_TEMPERATURE_SEN5X
 *  @brief Main message ID for the temperature main message (from SEN5X sensor)
 */
#define MAIN_MSG_TEMPERATURE_SEN5X 0x0B

/*  @def MAIN_MSG_VOC_INDEX_SEN5X
 *  @brief Main message ID for the voc index main message (from SEN5X sensor)
 */
#define MAIN_MSG_VOC_INDEX_SEN5X 0x0C

/*  @def MAIN_MSG_NOX_INDEX_SEN5X
 *  @brief Main message ID for the nox index main message (from SEN5X sensor)
 */
#define MAIN_MSG_NOX_INDEX_SEN5X 0x0D

/*  @def MAIN_MSG_WEIGHT
 *  @brief Main message ID for the weight main message
 */
#define MAIN_MSG_WEIGHT 0x0E

/*  @def MAIN_MSG_PRESSURE
 *  @brief Main message ID for the pressure main message
 */
#define MAIN_MSG_PRESSURE	0x0F

/*  @def MAIN_MSG_DOOR_STATE
 *  @brief Main message ID for the door state main message
 */
#define MAIN_MSG_DOOR_STATE 0x10

/*  @def MAIN_MSG_PM1
 *  @brief Main message ID for the pm1 main message
 */
#define MAIN_MSG_PM1	0x11

/*  @def MAIN_MSG_PM2_5
 *  @brief Main message ID for the pm2_5 main message
 */
#define MAIN_MSG_PM2_5	0x12

/*  @def MAIN_MSG_PM4
 *  @brief Main message ID for the pm4 main message
 */
#define MAIN_MSG_PM4	0x13

/*  @def MAIN_MSG_PM10
 *  @brief Main message ID for the pm10 main message
 */
#define MAIN_MSG_PM10	0x14

/* @fn 		HAL_StatusTypeDef send_main_msg_led_color(uint8_t light_color,UART_HandleTypeDef * uart )
 * @brief 	Function used to send the light color value message
 * @param 	light_color is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_led_color(uint8_t light_color,UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_relay(uint8_t relay_state,UART_HandleTypeDef * uart )
 * @brief 	Function used to send the relay value message
 * @param 	relay_state is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_relay(uint8_t relay_state,UART_HandleTypeDef * uart );

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

/* @fn 		HAL_StatusTypeDef send_main_msg_temperature(float temperature, uint8_t MAIN_MSG_ID, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the temperature value message
 * @note	temperature is a float value
 * @param 	temperature is the value to be sent
 * @param	main_msg_id is the id of the message
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_temperature(float temperature, uint8_t MAIN_MSG_ID, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_humidity(double humidity, uint8_t MAIN_MSG_ID, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the temperature value message
 * @note	temperature is a double, because it's a float value
 * @param 	temperature is the value to be sent
 * @param	main_msg_id is the id of the message
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_humidity(double humidity, uint8_t MAIN_MSG_ID, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_pressure(uint16_t pressure, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the pressure value message
 * @param 	pressure is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_pressure(uint16_t pressure, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_door_state(uint8_t door_state, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the door state value message
 * @param 	door_state is the value to be sent : send true (1) if the door is opened ; send false (0) if the door is closed
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_door_state(uint8_t door_state, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_pm1(float pm1, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the pm1 value message
 * @param 	pm1 is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_pm1(float pm1, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_pm2_5(float pm2_5, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the pm2_5 value message
 * @param 	pm2_5 is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_pm2_5(float pm2_5, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_pm4(float pm4, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the pm4 value message
 * @param 	pm4 is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_pm4(float pm4, UART_HandleTypeDef * uart );

/* @fn 		HAL_StatusTypeDef send_main_msg_pm10(float pm10, UART_HandleTypeDef * uart );
 * @brief 	Function used to send the pm1 value message
 * @param 	pm10 is the value to be sent
 * @param 	uart Uart structure used to the communication with the Jetson Nano
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_main_msg_pm10(float pm10, UART_HandleTypeDef * uart );
