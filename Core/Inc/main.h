/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "defines.h"
#include "extern_variables.h"
#include "functions.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define V_OUT_EE_Pin GPIO_PIN_2
#define V_OUT_EE_GPIO_Port GPIOC
#define V_OUT_PLUG_Pin GPIO_PIN_3
#define V_OUT_PLUG_GPIO_Port GPIOC
#define THERMISTOR_Pin GPIO_PIN_0
#define THERMISTOR_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define PRESSURE_Pin GPIO_PIN_4
#define PRESSURE_GPIO_Port GPIOA
#define COOLING_FAN_PWM_Pin GPIO_PIN_5
#define COOLING_FAN_PWM_GPIO_Port GPIOA
#define DOOR_RIGHT_LATCH_Pin GPIO_PIN_6
#define DOOR_RIGHT_LATCH_GPIO_Port GPIOA
#define DOOR_LEFT_LATCH_Pin GPIO_PIN_5
#define DOOR_LEFT_LATCH_GPIO_Port GPIOC
#define HEATER_FAN_PWM_Pin GPIO_PIN_2
#define HEATER_FAN_PWM_GPIO_Port GPIOB
#define SMART_SENSOR_1_SCL_Pin GPIO_PIN_10
#define SMART_SENSOR_1_SCL_GPIO_Port GPIOB
#define WHITE_LIGHT_Pin GPIO_PIN_14
#define WHITE_LIGHT_GPIO_Port GPIOB
#define TACHY_COOLING_FAN_Pin GPIO_PIN_6
#define TACHY_COOLING_FAN_GPIO_Port GPIOC
#define RELAY_Pin GPIO_PIN_9
#define RELAY_GPIO_Port GPIOC
#define SMART_SENSOR_2_SCL_Pin GPIO_PIN_8
#define SMART_SENSOR_2_SCL_GPIO_Port GPIOA
#define BLUE_LIGHT_Pin GPIO_PIN_9
#define BLUE_LIGHT_GPIO_Port GPIOA
#define GREEN_LIGHT_Pin GPIO_PIN_10
#define GREEN_LIGHT_GPIO_Port GPIOA
#define RED_LIGHT_Pin GPIO_PIN_11
#define RED_LIGHT_GPIO_Port GPIOA
#define DOOR_CMD_Pin GPIO_PIN_11
#define DOOR_CMD_GPIO_Port GPIOC
#define DFPlayer_TX_Pin GPIO_PIN_12
#define DFPlayer_TX_GPIO_Port GPIOC
#define DFPlayer_RX_Pin GPIO_PIN_2
#define DFPlayer_RX_GPIO_Port GPIOD
#define SMART_SENSOR_1_SDA_Pin GPIO_PIN_3
#define SMART_SENSOR_1_SDA_GPIO_Port GPIOB
#define SMART_SENSOR_2_SDA_Pin GPIO_PIN_4
#define SMART_SENSOR_2_SDA_GPIO_Port GPIOB
#define SMART_POWER_SCL_Pin GPIO_PIN_6
#define SMART_POWER_SCL_GPIO_Port GPIOB
#define SMART_POWER_SDA_Pin GPIO_PIN_7
#define SMART_POWER_SDA_GPIO_Port GPIOB
#define HEATER_Pin GPIO_PIN_9
#define HEATER_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
