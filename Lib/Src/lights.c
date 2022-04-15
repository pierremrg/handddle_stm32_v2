/*
 * Lights.c
 *
 *  Created on: 22 déc. 2021
 *      Author: handddle
 */
#include "../Inc/lights.h"


//FADE
int pwm = ZERO, token = ZERO;

int percentage(int value, int perc)
{
	int return_value;
	if(perc != ZERO) return_value = (perc * value) / CONST_PERCENT;
	return return_value;
}

void fade(int color)
{
	switch (color) {
		case WHITE_PT:
			htim1.Instance -> CCR4 = ZERO;
			htim1.Instance -> CCR3 = ZERO;
			htim1.Instance -> CCR2 = ZERO;
			htim12.Instance -> CCR1 = percentage(WHITE_PT_W_CONST, pwm);

			if(pwm <= MAX_PWM_FADE)
			{
				if(token == ZERO)
				{
					pwm += ONE;
					if(pwm == MAX_PWM_FADE) token = ONE;
				}
				else if(pwm > MIN_PWM_FADE && token == ONE)
				{
					pwm -= ONE;
					if(pwm == MIN_PWM_FADE) token = ZERO;
				}
			}
			break;

		case RED:
			htim1.Instance -> CCR4 = percentage(RED_R_CONST, pwm);
			htim1.Instance -> CCR3 = ZERO;
			htim1.Instance -> CCR2 = ZERO;
			htim12.Instance -> CCR1 = ZERO;

			if(pwm <= MAX_PWM_FADE)
			{
				if(token == ZERO)
				{
					pwm += ONE;
					if(pwm == MAX_PWM_FADE) token = ONE;
				}
				else if(pwm > MIN_PWM_FADE && token == ONE)
				{
					pwm -= ONE;
					if(pwm == MIN_PWM_FADE) token = ZERO;
				}
			}
			break;

		case GREEN:
			htim1.Instance -> CCR4 = ZERO;
			htim1.Instance -> CCR3 = percentage(GREEN_G_CONST, pwm);
			htim1.Instance -> CCR2 = ZERO;
			htim12.Instance -> CCR1 = ZERO;

			if(pwm <= MAX_PWM_FADE)
			{
				if(token == ZERO)
				{
					pwm += ONE;
					if(pwm == MAX_PWM_FADE)
					{
						token = ONE;
					}
				}
				else if(pwm > MIN_PWM_FADE && token == ONE)
				{
					pwm -= ONE;

					if(pwm == MIN_PWM_FADE) token = ZERO;
				}
			}
			break;

		case ORANGE:
			htim1.Instance -> CCR4 = percentage(ORANGE_R_CONST, pwm);
			htim1.Instance -> CCR3 = percentage(ORANGE_G_CONST, pwm);
			htim1.Instance -> CCR2 = ZERO;
			htim12.Instance -> CCR1 = ZERO;

			if(pwm <= MAX_PWM_FADE)
			{
				if(token == ZERO)
				{
					pwm += ONE;
					if(pwm == MAX_PWM_FADE) token = ONE;
				}
				else if(pwm > MIN_PWM_FADE && token == ONE)
				{
					pwm -= ONE;

					if(pwm == MIN_PWM_FADE) token = ZERO;
				}
			}
			break;

		case BLUE:
			htim1.Instance -> CCR4 = ZERO;
			htim1.Instance -> CCR3 = ZERO;
			htim1.Instance -> CCR2 = percentage(BLUE_B_CONST, pwm);
			htim12.Instance -> CCR1 = ZERO;

			if(pwm <= MAX_PWM_FADE)
			{
				if(token == ZERO)
				{
					pwm += ONE;
					if(pwm == MAX_PWM_FADE) token= ONE;
				}
				else if(pwm > MIN_PWM_FADE && token == ONE)
				{
					pwm -= ONE;
					if(pwm == MIN_PWM_FADE) token = ZERO;
				}
			}
			break;

		case BLUE_HANDDDLE:
			htim1.Instance -> CCR4 = ZERO;
			htim1.Instance -> CCR3 = percentage(BLUE_HANDDDLE_G_CONST, pwm);
			htim1.Instance -> CCR2 = percentage(BLUE_HANDDDLE_B_CONST, pwm);
			htim12.Instance -> CCR1 = ZERO;

			if(pwm <= MAX_PWM_FADE)
			{
				if(token == ZERO)
				{
					pwm += ONE;
					if(pwm == MAX_PWM_FADE) token= ONE;
				}
				else if(pwm > MIN_PWM_FADE && token == ONE)
				{
					pwm -= ONE;
					if(pwm == MIN_PWM_FADE) token = ZERO;
				}
			}
			break;

		case WHITE:
			htim1.Instance -> CCR4 = ZERO;
			htim1.Instance -> CCR3 = ZERO;
			htim1.Instance -> CCR2 = ZERO;
			htim12.Instance -> CCR1 = percentage(WHITE_W_CONST, pwm);

			if(pwm <= MAX_PWM_FADE)
			{
				if(token == ZERO)
				{
					pwm += ONE;
					if(pwm == MAX_PWM_FADE) token= ONE;
				}
				else if(pwm > MIN_PWM_FADE && token == ONE)
				{
					pwm -= ONE;
					if(pwm == MIN_PWM_FADE) token = ZERO;
				}
			}
			break;
	}
}


void set_lights(int color)
{
	switch(color)
	{
		//Color : White
	    case WHITE:
	    	htim1.Instance->CCR4 = ZERO; //Modulation
	    	htim1.Instance->CCR3 = ZERO; //Modulation
	    	htim1.Instance->CCR2 = ZERO; //Modulation
	    	htim12.Instance->CCR1 = WHITE_W_CONST; //Modulation
	    	break;

	    case WHITE_PT:
	    	htim1.Instance->CCR4 = ZERO; //Modulation
	    	htim1.Instance->CCR3 = ZERO; //Modulation
	    	htim1.Instance->CCR2 = ZERO; //Modulation
	    	htim12.Instance->CCR1 = WHITE_PT_W_CONST; //Modulation
	    	break;

	    case RED:
	    	htim1.Instance->CCR4 = RED_R_CONST; //Modulation
	    	htim1.Instance->CCR3 = ZERO; //Modulation
	    	htim1.Instance->CCR2 = ZERO; //Modulation
	    	htim12.Instance->CCR1 = ZERO; //Modulation
	    	break;

	    case GREEN:
	    	htim1.Instance->CCR4 = ZERO; //Modulation
	    	htim1.Instance->CCR3 = GREEN_G_CONST; //Modulation
	    	htim1.Instance->CCR2 = ZERO; //Modulation
	    	htim12.Instance->CCR1 = ZERO; //Modulation
	    	break;

	    case BLUE:
	    	htim1.Instance->CCR4 = ZERO; //Modulation
	    	htim1.Instance->CCR3 = ZERO; //Modulation
	    	htim1.Instance->CCR2 = BLUE_B_CONST; //Modulation
	    	htim12.Instance->CCR1 = ZERO; //Modulation
	    	break;

	    case BLUE_HANDDDLE:
	    	htim1.Instance->CCR4 = ZERO; //Modulation  		14
	    	htim1.Instance->CCR3 = BLUE_HANDDDLE_G_CONST; //Modulation 		90
	    	htim1.Instance->CCR2 = BLUE_HANDDDLE_B_CONST; //Modulation 		45
	    	htim12.Instance->CCR1 = ZERO; //Modulation			ZERO
	    	break;

	    case DARK:
	    	htim1.Instance->CCR4 = ZERO; //Modulation
	    	htim1.Instance->CCR3 = ZERO; //Modulation
	    	htim1.Instance->CCR2 = ZERO; //Modulation
	    	htim12.Instance->CCR1 = ZERO; //Modulation
	    	break;

	    case ORANGE:
	    	htim1.Instance->CCR4 = ORANGE_R_CONST; //Modulation
	    	htim1.Instance->CCR3 = ORANGE_G_CONST; //Modulation
	    	htim1.Instance->CCR2 = ZERO; //Modulation
	    	htim12.Instance->CCR1 = ZERO; //Modulation
	    	break;
	}
}
