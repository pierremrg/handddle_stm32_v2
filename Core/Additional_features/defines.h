/*
 * defines.h
 *
 *  Created on: 22 févr. 2022
 *      Author: handddle
 */

#include "libraries.h"

#ifndef ADDITIONAL_FEATURES_DEFINES_H_
#define ADDITIONAL_FEATURES_DEFINES_H_


#define ZERO 								0x00
#define ONE									0x01
#define TWO									0x02

#define FIRST_BYTE							0
#define SECOND_BYTE							1
#define THIRD_BYTE							2
#define FOURTH_BYTE							3
#define FIFTH_BYTE							4
#define SIXTH_BYTE							5
#define SEVENTH_BYTE						6
#define LAST_BYTE							7

#define DEFAULT_ACK_VALUE 					0x01
#define DEFAULT_TIMEOUT 					200

#define BYTE_OFFSET							8
#define OFFSET_OF_1							1
#define OFFSET_OF_2							2
#define MULTIPLIER_FACTOR_100				100 // For 2-byte values to send


// For fans
#define DUTY_CYCLE_INVERSE 					100
#define TOLERANCE  							0
#define TIMCLOCK  							20000000
#define PRESCALER 							2000
#define MIN_PWM_FAN							0
#define MAX_PWM_FAN							100
#define PWM_STOP							0
#define PWM_DOOR_CLOSURE_PT					40 // Post Treatment

// For light color
#define LIGHT_COLOR_MIN_INDEX				0
#define LIGHT_COLOR_MAX_INDEX				7

// For sound module
#define SOUND_MODULE_MIN_VOLUME 			0
#define SOUND_MODULE_MAX_VOLUME 			30
#define SOUND_MODULE_MIN_EQ		 			0
#define SOUND_MODULE_MAX_EQ		 			5

// For door
#define PRESENT								1
#define NOT_PRESENT							0
#define OPENED								true
#define CLOSED								false
#define UNLOCKED							false
#define LOCKED								true
#define LATCH_ERROR							2
#define EXTRACTION_TIME_AFTER_DOOR_OPENED	180

// For pressure
#define ADC_12_BIT 							4096.0 // 2^12
#define VOLTAGE_SUPPLY 						3.3 // Volt
#define FIRST_CONST_750						750
#define SECOND_CONST_150					150

//For Smart Power
#define BYTES_TO_TRANSMIT_SHT40				1
#define BYTES_TO_READ_SHT40					6
#define SHT40_COMMAND						0xFD
#define FIRST_CONST_175						175
#define SECOND_CONST_65535					65535
#define THIRD_CONST_45						45
#define FOURTH_CONST_125					125
#define FIFTH_CONST_6						6

//For heater temperature
#define DELTA_INERTIA						0.5
#define PWM_HEATER_80						80
#define PWM_HEATER_10						10
#define PWM_COOLING_100						100
#define PWM_COOLING_30						30
#define DESIRED_TEMP_MIN					10
#define DESIRED_TEMP_MAX					50

#endif /* ADDITIONAL_FEATURES_DEFINES_H_ */
