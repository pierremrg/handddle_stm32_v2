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
#define WHITE		 				6

#ifndef INC_LIGHTS_H_
#define INC_LIGHTS_H_

void fade(int color);

void fadeB(int color);

int percentage(int value, int perc);

void set_lights(int color);


#endif /* INC_LIGHTS_H_ */
