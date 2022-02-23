/*
 * CoolingFan.c
 *
 *  Created on: Jan 7, 2022
 *      Author: handddle
 */

#include "../Inc/cooling_fan.h"

void set_cooling_fan_pwm(uint8_t dutycyle, TIM_HandleTypeDef *htim)
{
	uint8_t PWM = 0;
	PWM = DUTY_CYCLE_INVERSE - dutycyle;
	htim->Instance->CCR1 = PWM; //Timer 2 CHANNEL 1
}

int get_cooling_frequency(void)
{
	if((cooling_fan_frequency - prevFrq > TOLERANCE) || (prevFrq - cooling_fan_frequency > TOLERANCE))
	{
		prevFrq = cooling_fan_frequency;
		return cooling_fan_frequency;
	}
	return prevFrq;
}

int get_cooling_rpm(void)
{
	int rpm = 0;

	rpm = get_cooling_frequency() * 30;
	return rpm;
}
