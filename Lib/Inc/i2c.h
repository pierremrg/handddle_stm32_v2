/*
 * i2c.h
 *
 *  Created on: Apr 4, 2022
 *      Author: handddle
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "main.h"

#define CRC8_POLYNOMIAL 	0x31

#define SHT40_ADDRESS 		0x44

/*
 * @brief  This function is used to collect Temperature & Humidity with the SHT40.
 * @retval return an HAL_StatusTypeDef variable to know if we can communicate with the SHT40
 * @param	hi2c_x is the i2c channel which we send the frame
 */
HAL_StatusTypeDef write_frame_temp_humi_SHT40(I2C_HandleTypeDef *hi2c_x);

/*
 * @brief  	This function is used to send an UART frame to the SHT40.
 * @retval 	return a Struct_TH variable to get the temperature and the humidity rate
 * @param	hi2c_x is the i2c channel which we send the frame
 */
Struct_TH read_temp_humi_SHT40(I2C_HandleTypeDef *hi2c_x);

#endif /* INC_I2C_H_ */
