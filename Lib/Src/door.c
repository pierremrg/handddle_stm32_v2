/*
 * door.c
 *
 *  Created on: Feb 1, 2022
 *      Author: handddle
 */

#include "../Inc/door.h"
#include "../Inc/lights.h"
#include "../Inc/sound_module.h"

#include "../../Transport/uid.h"


bool get_door_latch_1(void)
{
	bool latch_1;
	// Latch State 1
	if(HAL_GPIO_ReadPin(DOOR_LATCH_1_GPIO_Port, DOOR_LATCH_1_Pin))
		latch_1 = PRESENT;
	else
		latch_1 = NOT_PRESENT;

	return latch_1;
}

bool get_door_latch_2(void)
{
	bool latch_2;
	// Latch State 2
	if(HAL_GPIO_ReadPin(DOOR_LATCH_2_GPIO_Port, DOOR_LATCH_2_Pin))
		latch_2 = PRESENT;
	else
		latch_2 = NOT_PRESENT;

	return latch_2;
}

uint8_t get_latches_state(void)
{
	bool latch_1 = get_door_latch_1();
	bool latch_2 = get_door_latch_2();
	uint8_t latches;

	if((latch_1 == PRESENT) && (latch_2 == PRESENT))
		latches = PRESENT;
	else if((latch_1 == NOT_PRESENT) && (latch_2 == NOT_PRESENT))
		latches = NOT_PRESENT;
	else
		latches = LATCH_ERROR;

	return latches;
}


void set_door_lock(bool cmd_door_closed)
{
	if(cmd_door_closed)
		HAL_GPIO_WritePin(DOOR_CMD_GPIO_Port, DOOR_CMD_Pin, GPIO_PIN_RESET); // Door is locked
	else
		HAL_GPIO_WritePin(DOOR_CMD_GPIO_Port, DOOR_CMD_Pin, GPIO_PIN_SET); // Door is unlocked
}

void door_cycle(bool door_cycle_on)
{
	uint8_t latches_state = get_latches_state();

	if(door_opening)
	{
		door_opening = false;

		previous_pwm_cooling_fan = pwm_cooling_fan;
		previous_pwm_heater_fan = pwm_heater_fan;

		if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF)
		{
			pwm_cooling_fan = PWM_STOP;
			pwm_heater_fan = PWM_STOP;
		} else if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT)
		{
			pwm_cooling_fan = MAX_PWM_FAN;
			pwm_heater_fan = PWM_STOP;
		}


	} else if(door_closure)
	{
		door_closure = false;

		if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT)
		{
			var_timer_7_tick = ZERO;

			if(door_init) door_init = false;
			else {
				pwm_cooling_fan = PWM_DOOR_CLOSURE_PT;
				led_color = WHITE_PT;
			}
		} else
		{
			pwm_cooling_fan = previous_pwm_cooling_fan;
			pwm_heater_fan = previous_pwm_heater_fan;
			led_color = previous_led_color;
		}
	}

	if(latches_state == NOT_PRESENT)
	{
		door_state = OPENED;
		led_color = WHITE;

		if(var_timer_7_tick == ZERO) HAL_TIM_Base_Start_IT(&htim7);

	} else if(latches_state == PRESENT)
	{
		door_state = CLOSED;

		if(var_timer_7_tick != ZERO && MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF)
		{
			var_timer_7_tick = ZERO;
		}

		if(var_timer_7_tick == EXTRACTION_TIME_AFTER_DOOR_OPENED && MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT)
		{
			pwm_cooling_fan = PWM_STOP;
			var_timer_7_tick = ZERO;
		}
	}

	if(door_state == OPENED)
	{
		door_command = LOCKED;
	}
}
