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
		HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, GPIO_PIN_SET); //activate
	} else
	{
		HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, GPIO_PIN_RESET);
	}
}

void set_temperature(uint8_t desired_temp, float smart_power_temperature, float smart_sensor_temperature)
{
	float average_temperature = ZERO;

	average_temperature = (smart_power_temperature + smart_sensor_temperature) / TWO;

	if(average_temperature < desired_temp && desired_temp != ZERO)
	{
		if((desired_temp - average_temperature) > DELTA_INERTIA)
		{
			pwm_heater_fan = PWM_HEATER_90;
			heater_activated = true;
			pwm_cooling_fan = PWM_STOP;
		} else
		{
			pwm_heater_fan = PWM_HEATER_30;
			heater_activated = false;
			pwm_cooling_fan = PWM_STOP;
		}
	} else if(average_temperature > desired_temp && desired_temp != ZERO)
	{
		if((average_temperature - desired_temp) > DELTA_INERTIA)
		{
			pwm_cooling_fan = PWM_COOLING_100;
			pwm_heater_fan = PWM_HEATER_30;
			heater_activated = false;
		} else
		{
			pwm_cooling_fan = PWM_COOLING_30;
			pwm_heater_fan = PWM_HEATER_30;
			heater_activated = false;
		}
	}
}

