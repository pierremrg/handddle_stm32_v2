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
extern uint8_t previous_pwm_cooling_fan;
extern uint8_t previous_pwm_heater_fan;
extern uint8_t pwm_cooling_fan;
extern uint8_t pwm_heater_fan;

//for UART
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart5;

//Variables used to get SMART_SENSOR_frequency
extern int ic_val1_cooling, ic_val2_cooling, difference_cooling, is_first_captured_cooling;
extern int ic_val1_heater, ic_val2_heater, difference_heater, is_first_captured_heater;
extern int frequency;// for PWM of fans
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

//Timer and variable for lights
//Common variable
extern uint8_t led_color;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim12;

//For sound module
extern bool sm_next;
extern bool sm_pause;
extern bool sm_stop;
extern bool sm_playback;
extern bool sm_previous;
extern uint8_t sm_volume;
extern uint8_t sm_eq;
extern uint8_t sm_track;
extern bool sm_repeat;

//For door
extern bool door_init;
extern bool door_command;
extern bool door_closure;
extern bool door_opening;
extern bool door_state;
extern bool previous_door_state;
extern bool left_latch_error, right_latch_error;
extern TIM_HandleTypeDef htim7;
extern uint64_t var_timer_7_tick;

//For thermistor, pressure
extern ADC_HandleTypeDef hadc1;

//For temperature and humidity : Smart Power
extern I2C_HandleTypeDef hi2c1;
/*   Struct used to return a "tuple"    */
typedef struct i2C1_temp_humi {
	float temperature;
	float humidity;
	bool error_status;
} Struct_TH;

//Smart Sensor 1
extern I2C_HandleTypeDef hi2c2;

//Temperature
extern uint8_t desired_temperature;
extern bool heater_activated;

//For SGP41
typedef struct {

	uint16_t sraw_voc;
	uint16_t sraw_nox;
	uint8_t	cmd_init[SGP41_BYTES_TO_TRANSMIT];
	bool error_status; // 0 or 1

} struct_VN;

//For relay
bool relay_command;

//System On/Off
bool system_on_off;

#endif /* ADDITIONAL_FEATURES_EXTERN_VARIABLES_H_ */
