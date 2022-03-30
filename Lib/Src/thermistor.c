/*
 * Thermistance.c
 *
 *  Created on: Feb 9, 2022
 *      Author: handddle
 */

#include "../Inc/thermistor.h"

uint16_t reading_adc_channel_0(void)
{
	uint16_t adc_raw_value;

	ADC_ChannelConfTypeDef sConfig = {0};
	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	// Get ADC value
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, DEFAULT_TIMEOUT);
	adc_raw_value = HAL_ADC_GetValue(&hadc1);
	return adc_raw_value;
}


ntc_thermistor_values applying_coefficients(uint16_t adc_raw_value)
{
	ntc_thermistor_values ntc_values;
	ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_10_DEGREES;
	ntc_values.offset 			= OFFSET_10_DEGREES;

	if(adc_raw_value > THRESHOLD_10_DEGREES)
	{
		if(adc_raw_value > THRESHOLD_10_DEGREES) {
			ntc_values.div_coefficient	= DIVIDING_COEFFICIENT_10_DEGREES;
			ntc_values.offset				= OFFSET_10_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_15_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_15_DEGREES;
			ntc_values.offset				= OFFSET_15_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_20_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_20_DEGREES;
			ntc_values.offset				= OFFSET_20_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_25_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_25_DEGREES;
			ntc_values.offset				= OFFSET_25_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_30_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_30_DEGREES;
			ntc_values.offset				= OFFSET_30_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_35_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_35_DEGREES;
			ntc_values.offset				= OFFSET_35_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_40_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_40_DEGREES;
			ntc_values.offset				= OFFSET_40_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_45_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_45_DEGREES;
			ntc_values.offset				= OFFSET_45_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_50_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_50_DEGREES;
			ntc_values.offset				= OFFSET_50_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_55_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_55_DEGREES;
			ntc_values.offset				= OFFSET_55_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_60_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_60_DEGREES;
			ntc_values.offset				= OFFSET_60_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_65_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_65_DEGREES;
			ntc_values.offset				= OFFSET_65_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_70_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_70_DEGREES;
			ntc_values.offset				= OFFSET_70_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_75_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_75_DEGREES;
			ntc_values.offset				= OFFSET_75_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_80_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_80_DEGREES;
			ntc_values.offset				= OFFSET_80_DEGREES;
		}

		if(adc_raw_value > THRESHOLD_85_DEGREES) {
			ntc_values.div_coefficient 	= DIVIDING_COEFFICIENT_85_DEGREES;
			ntc_values.offset				= OFFSET_85_DEGREES;
		}
	}
	ntc_values.adc_value = adc_raw_value;

	return ntc_values;
}

float temperature_calculation(ntc_thermistor_values ntc_values)
{
	ntc_values.temperatureC = (ntc_values.adc_value * NTC_MULTIPLYING_COEFFICIENT) / ntc_values.div_coefficient;

	if(ntc_values.temperatureC >= ntc_values.offset)
	{
		ntc_values.temperatureC = ntc_values.temperatureC - ntc_values.offset;
		ntc_values.positive_temperature = ONE;
	}
	else
	{
		ntc_values.temperatureC = ntc_values.offset - ntc_values.temperatureC;
		ntc_values.positive_temperature = ZERO;
	}

	return ntc_values.temperatureC/ADC_MULTIPLYING_COEFFICIENT;
}
