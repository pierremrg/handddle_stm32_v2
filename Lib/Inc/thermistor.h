/*
 * Thermistance.h
 *
 *  Created on: Feb 9, 2022
 *      Author: handddle
 */
#include "main.h"

#ifndef THERMISTANCE_H_
#define THERMISTANCE_H_

ADC_HandleTypeDef hadc1;

/*
 * @note 	structure used to store all ntc thermistor values
 */
typedef struct ntc_thermistor_values{
	uint16_t div_coefficient, offset, adc_value;
	float temperatureC;
	uint8_t positive_temperature;
} ntc_thermistor_values;

// from ntc google sheets
#define THRESHOLD_10_DEGREES			1782
#define THRESHOLD_15_DEGREES			1862
#define THRESHOLD_20_DEGREES			1951
#define THRESHOLD_25_DEGREES			2048
#define THRESHOLD_30_DEGREES			2152
#define THRESHOLD_35_DEGREES			2261
#define THRESHOLD_40_DEGREES			2374
#define THRESHOLD_45_DEGREES			2490
#define THRESHOLD_50_DEGREES			2606
#define THRESHOLD_55_DEGREES			2720
#define THRESHOLD_60_DEGREES			2832
#define THRESHOLD_65_DEGREES			2940
#define THRESHOLD_70_DEGREES			3042
#define THRESHOLD_75_DEGREES			3138
#define THRESHOLD_80_DEGREES			3228
#define THRESHOLD_85_DEGREES			3311

#define NTC_MULTIPLYING_COEFFICIENT		50
#define ADC_MULTIPLYING_COEFFICIENT		10

#define DIVIDING_COEFFICIENT_10_DEGREES	80
#define DIVIDING_COEFFICIENT_15_DEGREES	89
#define DIVIDING_COEFFICIENT_20_DEGREES	97
#define DIVIDING_COEFFICIENT_25_DEGREES	104
#define DIVIDING_COEFFICIENT_30_DEGREES	109
#define DIVIDING_COEFFICIENT_35_DEGREES	113
#define DIVIDING_COEFFICIENT_40_DEGREES	115
#define DIVIDING_COEFFICIENT_45_DEGREES	116
#define DIVIDING_COEFFICIENT_50_DEGREES	115
#define DIVIDING_COEFFICIENT_55_DEGREES	112
#define DIVIDING_COEFFICIENT_60_DEGREES	108
#define DIVIDING_COEFFICIENT_65_DEGREES	102
#define DIVIDING_COEFFICIENT_70_DEGREES	96
#define DIVIDING_COEFFICIENT_75_DEGREES	90
#define DIVIDING_COEFFICIENT_80_DEGREES	83
#define DIVIDING_COEFFICIENT_85_DEGREES	76

#define OFFSET_10_DEGREES				1010
#define OFFSET_15_DEGREES				897
#define OFFSET_20_DEGREES				807
#define OFFSET_25_DEGREES				737
#define OFFSET_30_DEGREES				684
#define OFFSET_35_DEGREES				648
#define OFFSET_40_DEGREES				628
#define OFFSET_45_DEGREES				624
#define OFFSET_50_DEGREES				637
#define OFFSET_55_DEGREES				668
#define OFFSET_60_DEGREES				717
#define OFFSET_65_DEGREES				788
#define OFFSET_70_DEGREES				881
#define OFFSET_75_DEGREES				998
#define OFFSET_80_DEGREES				1144
#define OFFSET_85_DEGREES				1322

/*	@fn 	uint16_t reading_adc_channel_0(void);
 * 	@brief 	Function used to read the adc value on channel 0
 * 	@retval	return the read value
 */
uint16_t reading_adc_channel_0(void);

/*	@fn 	ntc_thermistor_values applying_coefficients(uint16_t adc_raw_value);
 * 	@brief 	Function used to get the coefficients used to calculate the temperature
 * 	@param	adc_raw_value is the adc value read in previous function
 * 	@retval return a struct with the differents coefficients calculated
 */
ntc_thermistor_values applying_coefficients(uint16_t adc_raw_value);

/*	@fn 	float temperature_calculation(ntc_thermistor_values ntc_values);
 * 	@brief 	Function used to calculate the temperature of embedded electronics
 * 	@param	ntc values is the struct read in the previous function
 * 	@retval	return the themperature in a floatting value
 */
float temperature_calculation(ntc_thermistor_values ntc_values);


#endif /* THERMISTANCE_H_ */
