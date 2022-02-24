/*
 * Lights.c
 *
 *  Created on: 22 déc. 2021
 *      Author: handddle
 */
#include "../Inc/lights.h"

int percentage(int value, int perc)
{
	int return_value;
	if(perc != 0) return_value = (perc * value) / 100;
	return return_value;
}

void fade(int color)
{
	//FADE
	int pwm = 0, tokenB = 0;

	if(color == BLUE_HANDDDLE && pwm<=100)
	{
		if(tokenB == 0)
		{
			htim1.Instance -> CCR4 = percentage(14, pwm);
			htim1.Instance -> CCR3 = percentage(90, pwm);
			htim1.Instance -> CCR2 = percentage(45, pwm);
			htim12.Instance -> CCR1 = 0;
			pwm++;
			if(pwm == 100){tokenB=1;}
		}
		else if(pwm>0 && tokenB == 1)
		{
			htim1.Instance -> CCR4 = percentage(14, pwm);
			htim1.Instance -> CCR3 = percentage(90, pwm);
			htim1.Instance -> CCR2 = percentage(45, pwm);
			htim12.Instance -> CCR1 = 0;
			pwm--;
			if(pwm == 1){color = BLUE_HANDDDLE; tokenB = 0; pwm=0;}
		}
	}
	else if(color == ORANGE && pwm<=100)
	{
		if(tokenB == 0)
		{
			htim1.Instance -> CCR4 = percentage(100, pwm);
			htim1.Instance -> CCR3 = percentage(40, pwm);
			htim1.Instance -> CCR2 = 0;
			htim12.Instance -> CCR1 = 0;
			pwm++;
			if(pwm == 100){tokenB=1;}
		}
		else if(pwm>0 && tokenB == 1)
		{
			htim1.Instance -> CCR4 = percentage(100, pwm);
			htim1.Instance -> CCR3 = percentage(40, pwm);
			htim1.Instance -> CCR2 = 0;
			htim12.Instance -> CCR1 = 0;
			pwm--;
			if(pwm == 5){color = 1; tokenB = ORANGE; pwm=0;}
		}
	}
	else if(color == WHITE && pwm<=100)
	{
		if(tokenB == 0)
		{
			htim1.Instance -> CCR4 = 0;
			htim1.Instance -> CCR3 = 0;
			htim1.Instance -> CCR2 = 0;
			htim12.Instance -> CCR1 = percentage(100, pwm);
			pwm++;
			if(pwm == 100){tokenB=1;}
		}
		else if(pwm>0 && tokenB == 1)
		{
			htim1.Instance -> CCR4 = 0;
			htim1.Instance -> CCR3 = 0;
			htim1.Instance -> CCR2 = 0;
			htim12.Instance -> CCR1 = percentage(100, pwm);
			pwm--;
			if(pwm == 5){color = WHITE; tokenB = 0; pwm=0;}
		}
	}
}


void set_lights(int color)
{
	switch(color)
	{
		//Color : White
	    case WHITE:
	    	htim1.Instance->CCR4 = 0; //Modulation
	    	htim1.Instance->CCR3 = 0; //Modulation
	    	htim1.Instance->CCR2 = 0; //Modulation
	    	htim12.Instance->CCR1 = 100; //Modulation
	    	break;

	    case WHITE_PT:
	    	htim1.Instance->CCR4 = 0; //Modulation
	    	htim1.Instance->CCR3 = 0; //Modulation
	    	htim1.Instance->CCR2 = 0; //Modulation
	    	htim12.Instance->CCR1 = 50; //Modulation
	    	break;

	    case RED:
	    	htim1.Instance->CCR4 = 100; //Modulation
	    	htim1.Instance->CCR3 = 0; //Modulation
	    	htim1.Instance->CCR2 = 0; //Modulation
	    	htim12.Instance->CCR1 = 0; //Modulation
	    	break;

	    case GREEN:
	    	htim1.Instance->CCR4 = 0; //Modulation
	    	htim1.Instance->CCR3 = 100; //Modulation
	    	htim1.Instance->CCR2 = 0; //Modulation
	    	htim12.Instance->CCR1 = 0; //Modulation
	    	break;

	    case BLUE_HANDDDLE:
	    	htim1.Instance->CCR4 = 14; //Modulation
	    	htim1.Instance->CCR3 = 90; //Modulation
	    	htim1.Instance->CCR2 = 45; //Modulation
	    	htim12.Instance->CCR1 = 0; //Modulation
	    	break;

	    case DARK:
	    	htim1.Instance->CCR4 = 0; //Modulation
	    	htim1.Instance->CCR3 = 0; //Modulation
	    	htim1.Instance->CCR2 = 0; //Modulation
	    	htim12.Instance->CCR1 = 0; //Modulation
	    	break;

	    case ORANGE:
	    	htim1.Instance->CCR4 = 100; //Modulation
	    	htim1.Instance->CCR3 = 40; //Modulation
	    	htim1.Instance->CCR2 = 0; //Modulation
	    	htim12.Instance->CCR1 = 0; //Modulation
	    	break;
	}
}

void fadeB(int color)
{
	switch(color)
	{
		case RED:
			for(int pwm=0; pwm<100; pwm++)
			{
				htim1.Instance -> CCR4 = percentage(100, pwm);
				htim1.Instance -> CCR3 = 0;
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			for(int pwm=100; pwm>0; pwm--)
			{
				htim1.Instance -> CCR4 = percentage(100, pwm);
				htim1.Instance -> CCR3 = 0;
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			break;

		case GREEN:
			for(int pwm=0; pwm<100; pwm++)
			{
				htim1.Instance -> CCR4 = 0;
				htim1.Instance -> CCR3 = percentage(100, pwm);
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			for(int pwm=100; pwm>0; pwm--)
			{
				htim1.Instance -> CCR4 = 0;
				htim1.Instance -> CCR3 = percentage(100, pwm);
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			break;

		case BLUE_HANDDDLE:
			for(int pwm=0; pwm<100; pwm++)
			{
				htim1.Instance -> CCR4 = percentage(14, pwm);
				htim1.Instance -> CCR3 = percentage(90, pwm);
				htim1.Instance -> CCR2 = percentage(45, pwm);
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			for(int pwm=100; pwm>0; pwm--)
			{
				htim1.Instance -> CCR4 = percentage(14, pwm);
				htim1.Instance -> CCR3 = percentage(90, pwm);
				htim1.Instance -> CCR2 = percentage(45, pwm);
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			break;

		case WHITE:
			for(int pwm=0; pwm<100; pwm++)
			{
				htim1.Instance -> CCR4 = 0;
				htim1.Instance -> CCR3 = 0;
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = percentage(100, pwm);
				HAL_Delay(20);
			}
			for(int pwm=100; pwm>0; pwm--)
			{
				htim1.Instance -> CCR4 = 0;
				htim1.Instance -> CCR3 = 0;
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = percentage(100, pwm);
				HAL_Delay(20);
			}
			break;

		case WHITE_PT:
			for(int pwm=0; pwm<100; pwm++)
			{
				htim1.Instance -> CCR4 = 0;
				htim1.Instance -> CCR3 = 0;
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = percentage(50, pwm);
				HAL_Delay(20);
			}
			for(int pwm=100; pwm>0; pwm--)
			{
				htim1.Instance -> CCR4 = 0;
				htim1.Instance -> CCR3 = 0;
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = percentage(50, pwm);
				HAL_Delay(20);
			}
			break;

		case ORANGE:
			for(int pwm=0; pwm<100; pwm++)
			{
				htim1.Instance -> CCR4 = percentage(100, pwm);
				htim1.Instance -> CCR3 = percentage(40, pwm);
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			for(int pwm=100; pwm>0; pwm--)
			{
				htim1.Instance -> CCR4 = percentage(100, pwm);
				htim1.Instance -> CCR3 = percentage(40, pwm);
				htim1.Instance -> CCR2 = 0;
				htim12.Instance -> CCR1 = 0;
				HAL_Delay(20);
			}
			break;
	}
}
