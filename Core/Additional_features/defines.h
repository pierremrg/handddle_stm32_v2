/*
 * defines.h
 *
 *  Created on: 22 févr. 2022
 *      Author: handddle
 */

#include "libraries.h"

#ifndef ADDITIONAL_FEATURES_DEFINES_H_
#define ADDITIONAL_FEATURES_DEFINES_H_

#define WATCHDOG_TIME						10

#define SYSTEM_ON							true
#define SYSTEM_OFF							false

#define ZERO 								0x00
#define ONE									0x01
#define TWO									0x02

#define DEFAULT_ACK_VALUE 					0x01
#define DEFAULT_TIMEOUT 					200
#define FIFTY_MS_DELAY						50

#define NO_BYTE_OFFSET						0
#define BYTE_OFFSET							8
#define OFFSET_OF_1							1
#define OFFSET_OF_2							2
#define MULTIPLIER_FACTOR_100				100 // For 2-byte values to send
#define MULTIPLIER_FACTOR_10				10 // For 2-byte values to send


// For fans
#define DUTY_CYCLE_INVERSE 					100
#define TOLERANCE  							0
#define TIMCLOCK  							20000000 //20Mhz
#define PRESCALER 							2000
#define MIN_PWM_FAN							0
#define MAX_PWM_FAN							100
#define PWM_STOP							0
#define PWM_DOOR_CLOSURE_PT					40 // Post Treatment

// For light color
#define LIGHT_COLOR_MIN_INDEX				0
#define LIGHT_COLOR_MAX_INDEX				7
#define FADE_OFFSET							10

// For sound module
#define SOUND_MODULE_MIN_VOLUME 			0
#define SOUND_MODULE_MAX_VOLUME 			30
#define SOUND_MODULE_MIN_EQ		 			0
#define SOUND_MODULE_MAX_EQ		 			5

// For door
#define PRESENT								1
#define NOT_PRESENT							0
#define OPENED								0
#define CLOSED								1
#define UNLOCKED							false
#define LOCKED								true
#define LEFT_LATCH_ERROR					2
#define RIGHT_LATCH_ERROR					3

// For pressure
#define ADC_12_BIT 							4096.0 // 2^12
#define VOLTAGE_SUPPLY 						3.3 // Volt
#define FIRST_CONST_750						750
#define SECOND_CONST_150					150

//For Smart Power
#define FIRST_CONST_175						175.0
#define SECOND_CONST_65535					65535.0
#define THIRD_CONST_45						45.0
#define FOURTH_CONST_125					125.0
#define FIFTH_CONST_6						6.0

//For heater temperature
#define DELTA_INERTIA						0.25
#define PWM_HEATER_90						90
#define PWM_HEATER_30						30
#define PWM_COOLING_100						100
#define PWM_COOLING_30						30
#define DESIRED_TEMP_MIN					10
#define DESIRED_TEMP_MAX					50

//For SHT40
#define SHT40_BYTES_TO_TRANSMIT				1
#define SHT40_BYTES_TO_RECEIVE				6

//For SEN5X
#define SEN5X_BYTES_TO_TRANSMIT				2
#define SEN5X_BYTES_TO_RECEIVE				23

//For SGP41
#define SGP41_BYTES_TO_TRANSMIT				8
#define SGP41_BYTES_TO_RECEIVE				6
#define SGP41_MEASUREMENT_COMMAND			0x2619
#define SGP41_INITIALIZATION_COMMAND		0x2612
#define SGP41_INIT_TEMPERATURE				25
#define SGP41_INIT_HUMIDITY					50
#define SGP41_CONDITIONNING_TIME			10 		//in seconds
#define SGP41_SRAW_FEEDING_TIME				180		//in seconds

// For relay
#define RELAY_ON							true
#define RELAY_OFF							false

//SEN5X
#define SEN5X_POLLUTION_FACTOR				10.0
#define SEN5X_TEMPERATURE_FACTOR			100.0
#define SEN5X_HUMIDITY_FACTOR				200.0

#endif /* ADDITIONAL_FEATURES_DEFINES_H_ */
