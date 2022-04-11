/*
 * relay.c
 *
 *  Created on: Apr 11, 2022
 *      Author: handddle
 */

#include "../Inc/relay.h"


void set_relay_on(bool command)
{
	if(command)
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET); //close the relay
	} else
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
	}
}
