/*
 * HeaterFan.c
 *
 *  Created on: Jan 7, 2022
 *      Author: handddle
 */

#include "../Inc/heater_fan.h"


void set_heater_fan_pwm(uint8_t dutycyle, TIM_HandleTypeDef *htim)
{
	uint8_t PWM = 0;
	PWM = DUTY_CYCLE_INVERSE - dutycyle;
	htim->Instance -> CCR4 = PWM; //Timer 2 CHANNEL 4
}

int get_heater_frequency(void)
{
	int prevFrq = 0;

	if((heater_fan_frequency - prevFrq > TOLERANCE) || (prevFrq - heater_fan_frequency > TOLERANCE))
	{
		prevFrq = heater_fan_frequency;
		return heater_fan_frequency;
	}
	return prevFrq;
}

int get_heater_rpm(void)
{
	int vitesse;
	vitesse = get_heater_frequency() * 30;
	return vitesse;
}

void set_heater(bool command)
{
	if(command)
	{
		HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, GPIO_PIN_SET);
	} else
	{
		HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, GPIO_PIN_RESET);
	}
}
