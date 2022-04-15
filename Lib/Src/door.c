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

#include "../../Transport/Msg_gen/Error_msg_gen/error_msg_gen.h"


bool get_door_right_latch_state(void)
{
	bool right_latch;

	if(HAL_GPIO_ReadPin(DOOR_RIGHT_LATCH_GPIO_Port, DOOR_RIGHT_LATCH_Pin))
		right_latch = PRESENT;
	else
		right_latch = NOT_PRESENT;

	return right_latch;
}

bool get_door_left_latch_state(void)
{
	bool left_latch;

	if(HAL_GPIO_ReadPin(DOOR_LEFT_LATCH_GPIO_Port, DOOR_LEFT_LATCH_Pin))
		left_latch = PRESENT;
	else
		left_latch = NOT_PRESENT;

	return left_latch;
}

uint8_t get_latches_state(void)
{
	bool right_latch = get_door_right_latch_state();
	bool left_latch = get_door_left_latch_state();
	uint8_t latches;

	if((right_latch == PRESENT) && (left_latch == PRESENT))
		latches = PRESENT;
	else if((right_latch == NOT_PRESENT) && (left_latch == NOT_PRESENT))
		latches = NOT_PRESENT;
	else if((right_latch == PRESENT) && (left_latch == NOT_PRESENT))
		latches = LEFT_LATCH_ERROR;
	else if((right_latch == NOT_PRESENT) && (left_latch == PRESENT))
		latches = RIGHT_LATCH_ERROR;


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
	latches_state = get_latches_state();

	if(door_opening)
	{
		door_opening = false;

		previous_pwm_cooling_fan = pwm_cooling_fan;
		previous_pwm_heater_fan = pwm_heater_fan;
		previous_static_light = static_light;


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
			static_light = previous_static_light;
		}
	}

	if(latches_state == NOT_PRESENT)
	{
		door_state = OPENED;
		led_color = WHITE;
		static_light = true;

		left_latch_error = false;
		right_latch_error = false;

		if(var_timer_7_tick == ZERO) HAL_TIM_Base_Start_IT(&htim7);

	} else if(latches_state == PRESENT)
	{
		door_state = CLOSED;

		left_latch_error = false;
		right_latch_error = false;

		if(var_timer_7_tick != ZERO && (MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF
				|| MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT))
		{
			var_timer_7_tick = ZERO;
		}
	} else if (latches_state == LEFT_LATCH_ERROR) {
		left_latch_error = true;
	} else if (latches_state == RIGHT_LATCH_ERROR) {
		right_latch_error = true;
	}


	if(door_state == OPENED)
	{
		door_command = LOCKED;
	}
}
