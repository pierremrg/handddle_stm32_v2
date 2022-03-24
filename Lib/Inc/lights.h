/*
 * Lights.h
 *
 *  Created on: 22 déc. 2021
 *      Author: handddle
 */
#include "../../Core/Inc/main.h"

#define DARK             			0
#define WHITE_PT 					1
#define RED			 				2
#define GREEN 						3
#define ORANGE			 			4
#define BLUE_HANDDDLE 				5
#define BLUE						6
#define WHITE		 				7

#ifndef INC_LIGHTS_H_
#define INC_LIGHTS_H_

/*	@fn 	void fade(int color);
 * 	@brief 	Function used to make a fade effect with the led
 * 	@param 	color is the color use to make the fade effect without blocking loop
 */
void fade(int color);

/*	@fn 	void fadeB(int color);
 * 	@brief 	Function used to make a fade effect with the led
 * 	@param 	color is the color use to make the fade effect with blocking loop
 */
void fadeB(int color);

/*	@fn 	int percentage(int value, int perc);
 * 	@brief 	Function used to converte the input value (0-255) to percentage value for the pwm
 * 	@param 	value is the variable to convert
 * 	@param 	perc is the desired percentage value
 * 	@retval	return the calculated value
 */
int percentage(int value, int perc);

/*	@fn 	void set_lights(int color);
 * 	@brief 	Function used to set led color
 * 	@param 	color is the color use to set the led
 */
void set_lights(int color);


#endif /* INC_LIGHTS_H_ */
