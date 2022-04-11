/*
 * door.h
 *
 *  Created on: Feb 1, 2022
 *      Author: handddle
 */
#include "../../Core/Inc/main.h"

TIM_HandleTypeDef htim7;
uint8_t previous_pwm_cooling_fan;
uint8_t previous_pwm_heater_fan;
uint8_t pwm_cooling_fan;
uint8_t pwm_heater_fan;
uint8_t previous_led_color;
uint8_t led_color;
bool door_state;
bool door_init;

uint8_t latches_state;
bool left_latch_error, right_latch_error;

bool door_closure;
bool door_opening;

uint64_t var_timer_7_tick;

#ifndef INC_DOOR_H_
#define INC_DOOR_H_

/*	@fn 	bool get_latch_state_2(void);
 * 	@brief 	Function used to know if the left door latch is locked or not
 * 	@retval return true (locked) or false (unlocked)
 */
bool get_door_left_latch_state(void);

/*	@fn 	bool get_latch_state_1(void);
 * 	@brief 	Function used to know if the right door latch is locked or not
 * 	@retval return true (locked) or false (unlocked)
 */
bool get_door_right_latch_state(void);

/*	@fn 	uint8_t get_latches_state(void);
 * 	@brief 	Function used to know if the door is opened, close or in error
 * 	@retval return 0, 1 or 2
 */
uint8_t get_latches_state(void);

/*	@fn 	void set_door_lock(bool cmd_door_closed);
 * 	@brief 	Function used to locked or unlocked the door
 * 	@param 	cmd_door_closed is the variable used to lock or unlock the door
 */
void set_door_lock(bool cmd_door_closed);

/*	@fn 	void door_cycle(bool door_cycle_on);
 * 	@brief 	Function used to activate or not the door automation
 * 	@param 	door_cycle_on is the variable with which activate or not the door cycle
 */
void door_cycle(bool door_cycle_on);


#endif /* INC_DOOR_H_ */
