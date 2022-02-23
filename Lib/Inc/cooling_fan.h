/*
 * CoolingFan.h
 *
 *  Created on: Jan 7, 2022
 *      Author: handddle
 */

#ifndef INC_COOLING_FAN_H_
#define INC_COOLING_FAN_H_

#include "main.h"

//Variables used to get frequency
int ic_val1_cooling, ic_val2_cooling, difference_cooling, is_first_captured_cooling;
int cooling_fan_frequency, prevFrq;


/*	@fn 	void set_cooling_fan_pwm(int dutycyle, TIM_HandleTypeDef *htim)
 * 	@brief 	Function used to set a run the cooling fan at a given dutycyle
 * 	@param	dutycyle is the variable used to give a rotation speed to the fan
 * 	@param 	htim is the timer used to send the dutycyle to the fan
 */
void set_cooling_fan_pwm(uint8_t dutycyle, TIM_HandleTypeDef *htim);

/*	@fn 	get_frequency getFrequency(void)
 * 	@brief 	Function used to get the fan's frequency
 */
int get_cooling_frequency(void);

/* @fn 		int get_cooling_rpm(void)
 * @brief	Function used to convert the frequency into RPM
 */
int get_cooling_rpm(void);

#endif /* INC_COOLING_FAN_H_ */
