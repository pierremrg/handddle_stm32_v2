/* Handddle
 * Communication module
 * 2022
 */
#include "main.h"
#include "../../Inc/msg_types.h"
#include "../../uid.h"

/** @def SEC_MSG_AIR_EXTRACTION_TACHYMETER
 *  @brief Message ID for the air extraction tachymeter secondary message
 */
#define SEC_MSG_AIR_EXTRACTION_TACHYMETER 0x00

/** @fn 	HAL_StatusTypeDef send_sec_msg_air_extraction_tachymeter(uint16_t tachy, UART_HandleTypeDef * uart)
 * @brief 	Function used to send the Tachy Extraction message
 * @param 	tachy is value to be sent
 * @param 	uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return 	HAL_ERROR if something went wrong; HAL_OK if every went well
 */
HAL_StatusTypeDef send_sec_msg_air_extraction_tachymeter(uint16_t tachy, UART_HandleTypeDef * uart);
