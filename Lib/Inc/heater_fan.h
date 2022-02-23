/*
 * HeaterFan.h
 *
 *  Created on: Jan 7, 2022
 *      Author: handddle
 */

#ifndef INC_HEATER_FAN_H_
#define INC_HEATER_FAN_H_

#include "main.h"

//Variables used to get frequency
int ic_val1_heater, ic_val2_heater, difference_heater, is_first_captured_heater;
int heater_fan_frequency, prevFrq;

/*	@fn 	void set_heater_fan_pwm(int dutycyle, TIM_HandleTypeDef *htim)
 * 	@brief 	Function used to set a run the heater fan at a given dutycyle
 * 	@param	dutycyle is the variable used to give a rotation speed to the fan
 * 	@param 	htim is the timer used to send the dutycyle to the fan
 */
void set_heater_fan_pwm(uint8_t dutycyle, TIM_HandleTypeDef *htim);

/*	@fn 	int get_heater_frequency(void)
 * 	@brief 	Function used to get the fan's frequency
 */
int get_heater_frequency(void);

/* @fn 		int get_heater_rpm(void)
 * @brief	Function used to convert the frequency into RPM
 */
int get_heater_rpm(void);

/* @fn 		int set_heater(bool command)
 * @brief	Function used to set or not the heater
 * @param	command is true if we want to set heater; else we set false
 */
void set_heater(bool command);



#endif /* INC_HEATER_FAN_H_ */
