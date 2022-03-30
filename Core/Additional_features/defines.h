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



#endif /* ADDITIONAL_FEATURES_DEFINES_H_ */
