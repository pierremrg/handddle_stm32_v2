/*
 * Pressure.c
 *
 *  Created on: Jan 31, 2022
 *      Author: handddle
 */


#include "../Inc/pressure.h"

/*    Get ADC Value    */
uint16_t reading_adc_channel_4(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, DEFAULT_TIMEOUT);
	uint16_t ADC_Pressure = HAL_ADC_GetValue(&hadc1);

	return ADC_Pressure;
}

uint16_t get_pressure(void)
{
	uint16_t adc_value = reading_adc_channel_4();

	// according to the sensor datasheet for the 500PA, DifferentialPressure = (750 * AOut / Vdd) - 150
	float sensor_voltage = (adc_value / ADC_12_BIT) * VOLTAGE_SUPPLY;
	uint16_t pressure = (FIRST_CONST_750 * sensor_voltage / VOLTAGE_SUPPLY) - SECOND_CONST_150;

	return pressure;
}
