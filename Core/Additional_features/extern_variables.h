/*
 * external_variables.h
 *
 *  Created on: Feb 22, 2022
 *      Author: handddle
 */

#ifndef ADDITIONAL_FEATURES_EXTERN_VARIABLES_H_
#define ADDITIONAL_FEATURES_EXTERN_VARIABLES_H_

#include "libraries.h"

//For watchdog
extern bool watchdog_actived;
extern bool watchdog_update;

// For fans
extern uint8_t pwm_cooling_fan;
extern uint8_t pwm_heater_fan;

// For light color
extern uint8_t light_color;

//for UART
extern UART_HandleTypeDef huart2;

//Variables used to get frequency
extern int ic_val1_cooling, ic_val2_cooling, difference_cooling, is_first_captured_cooling;
extern int ic_val1_heater, ic_val2_heater, difference_heater, is_first_captured_heater;
extern int frequency;// for PWM of fans
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

//Timer and variable for lights
//Common variable
extern int led_color;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim12;


#endif /* ADDITIONAL_FEATURES_EXTERN_VARIABLES_H_ */
