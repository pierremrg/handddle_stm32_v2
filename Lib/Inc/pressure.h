/*
 * Pressure.c
 *
 *  Created on: Jan 31, 2022
 *      Author: handddle
 */
#include "main.h"

#ifndef INC_LIGHTS_H_
#define INC_LIGHTS_H_

ADC_HandleTypeDef hadc1;

/*	@fn 	uint16_t reading_adc_channel_4(void);
 * 	@brief 	Function used to read the adc value on channel 4
 * 	@retval	return the read value in an unsigned two-byte value
 */
uint16_t reading_adc_channel_4(void);

/*	@fn 	uint16_t get_pressure(void);
 * 	@brief 	Function used to calculate the pressure
 * 	@retval	return the current pressure value
 */
uint16_t get_pressure(void);


#endif /* INC_LIGHTS_H_ */
