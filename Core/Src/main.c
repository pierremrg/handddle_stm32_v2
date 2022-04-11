/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "defines.h"
#include "functions.h"
#include "extern_variables.h"

#include "../../Transport/Parser/parser.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"

#include "../../Lib/Inc/cooling_fan.h"
#include "../../Lib/Inc/heater_fan.h"
#include "../../Lib/Inc/lights.h"
#include "../../Lib/Inc/sound_module.h"
#include "../../Lib/Inc/door.h"
#include "../../Lib/Inc/i2c.h"
#include "../../Lib/Inc/pressure.h"
#include "../../Lib/Inc/thermistor.h"
#include "../../Lib/Inc/gas_index_algorithm.h"
#include "../../Lib/Inc/relay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim12;

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM12_Init(void);
static void MX_UART5_Init(void);
static void MX_TIM7_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM9_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Buffer used to store received bytes from the Jetson card
uint8_t rx_buffer[MSG_SIZE];

// Buffer used with the sound module
uint8_t rx_buffer2[MSG_SIZE];

uint64_t last_watchdog_time = 0;
bool watchdog_actived = false; 	//extern
bool watchdog_update = false;	//extern
bool var_toggle = false;

// Variable used to be increment at each tick of timer 4 (main)
uint64_t var_timer_4_tick = 0;
// Variable used to be increment at each tick of timer 7 (door)
uint64_t var_timer_7_tick = 0;
// Variable used to be true at each tick of timer 9 (50ms)
bool var_timer_9_tick = 0;

//send messages
bool send_messages = false;
bool get_i2c_values = false;

//fans
uint8_t pwm_cooling_fan = 0;
uint8_t pwm_heater_fan = 0;
int cooling_frq;// for PWM of fans
int cooling_rpm;// for PWM of fans

//light color
uint8_t led_color = 0;
uint8_t previous_led_color = 0;
uint8_t led_color_buffer = 0;

//sound module
//extern
bool sm_next = false;
bool sm_pause = false;
bool sm_stop = false;
bool sm_playback = false;
bool sm_previous = false;
uint8_t sm_volume = 20; // default volume
uint8_t previous_sm_volume = 0;
uint8_t sm_eq = 0;
uint8_t previous_sm_eq;
uint8_t sm_track = 0;
uint8_t previous_sm_track = 0;
bool sm_repeat = false;

bool uart2_irq_is_captured = false;
bool uart5_irq_is_captured = false;

//door
bool door_init;
bool door_state;
bool previous_door_state;
bool door_closure = false;
bool door_opening = false;

//thermistor
ntc_thermistor_values ntc_values;
uint16_t adc_temperature_raw_value;

//pressure
uint16_t pressure = 0;

//temperature, humidity : Smart Power
Struct_TH temp_humi_SP;

//temperature, humidity : Smart Sensor n°1
Struct_TH temp_humi_SS_1;

//temperature, humidity : Smart Sensor n°2
Struct_TH temp_humi_SS_2;

//UART return value
HAL_StatusTypeDef return_value_SP, return_value_SS_1, return_value_SS_2;

//temperature
uint8_t desired_temperature = 0;
bool heater_activated = false;
float average_temperature = 0, average_humidity = 0;

//Sgp41
HAL_StatusTypeDef sgp41_return_value;
struct_VN pollution_data;
GasIndexAlgorithmParams params_voc;
GasIndexAlgorithmParams params_nox;
int32_t voc_index_value;
int32_t nox_index_value;
uint16_t sraw_voc;
uint16_t sraw_nox;
uint8_t sgp41_timer_init = 0;
uint8_t sgp41_timer_feeding = 0;
bool sgp41_tick = true;

//relay
bool relay_command = RELAY_ON;

//Sytem
bool system_on_off = SYSTEM_ON;
uint8_t led_color_system_off = DARK;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM12_Init();
  MX_UART5_Init();
  MX_TIM7_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM9_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  /* USER CODE BEGIN 2 */

  /*     SMART LIGHT    */
  //RED -- TIMER 1 CH4
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  //GREEN -- TIMER 1 CH3
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  //BLUE TIMER 1 CH2
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  //WHITE -- TIMER 12 - CH1
  HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);

  //Timers for PWM
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // For PWM cooling fan
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4); // For PWM heater fan
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1); // To get tachymeter frequency

  set_cooling_fan_pwm(PWM_STOP, &htim2);
  set_heater_fan_pwm(PWM_STOP, &htim2);

  // Main timer ticks each second
  HAL_TIM_Base_Start_IT(&htim4);

  // Timer ticks each 50ms (i2c)
//  HAL_TIM_Base_Start_IT(&htim9);

  // Start UART reception
  HAL_UART_Receive_IT(&huart2, rx_buffer, MSG_SIZE);
  HAL_UART_Receive_IT(&huart5, rx_buffer2, MSG_SIZE);
  //Ack value send to the Jetson Nano
  send_cmd_ack_with_value(&huart2, DEFAULT_ACK_VALUE);

  // Led color
  if((MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_RACK) || (MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF))
  {
	  led_color = WHITE;
	  previous_led_color = WHITE;
	  led_color_buffer = WHITE;
  } else if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT)
  {
	  led_color =  WHITE_PT;
	  previous_led_color = WHITE_PT;
	  led_color_buffer = WHITE_PT;
  }

  send_main_msg_led_color(led_color, &huart2);

  //sound module
  //local
  previous_sm_volume = sm_volume;
  previous_sm_eq = sm_eq;
  previous_sm_track = sm_track;
  sm_init(sm_volume);

  //door
  if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF || MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT)
  {
	  door_command = LOCKED;
	  set_door_lock(door_command); //default: door opened

	  if(get_latches_state() == PRESENT)
	  {
		  door_state = CLOSED;
		  previous_door_state = CLOSED;
		  door_init = false;
	  } else
	  {
		  door_state = OPENED;
		  previous_door_state = OPENED;
		  door_init = true;
	  }
  }

  //sgp41 INIT
  GasIndexAlgorithm_init(&params_voc, GasIndexAlgorithm_ALGORITHM_TYPE_VOC);
  GasIndexAlgorithm_init(&params_nox, GasIndexAlgorithm_ALGORITHM_TYPE_NOX);

  //relay : default always activate
  set_relay_on(relay_command);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*
	   * SYSTEM
	   */
	  if(system_on_off == SYSTEM_ON)
	  {
		  /*
		   * 		Apply functions
		   */
		  set_cooling_fan_pwm(pwm_cooling_fan, &htim2);
		  set_heater_fan_pwm(pwm_heater_fan, &htim2);
		  set_heater(heater_activated);
		  set_lights(led_color);
		  set_door_lock(door_command);
		  if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF || MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT) door_cycle(true);

		  if(desired_temperature >= DESIRED_TEMP_MIN && desired_temperature <= DESIRED_TEMP_MAX && door_state == CLOSED)
		  {
			  set_temperature(desired_temperature, temp_humi_SP.temperature, temp_humi_SS_1.temperature);
		  } else
		  {
			  heater_activated = false;
			  pwm_heater_fan = PWM_HEATER_10;
		  }
		  set_relay_on(relay_command);



		  /*
		   * 		Assign variables
		   */

		  if(previous_door_state != door_state)
		  {
			  previous_door_state = door_state;
			  if(door_state == OPENED)
			  {
				  door_opening = true;
			  } else if(door_state == CLOSED)
			  {
				  door_closure = true;
			  }
		  }

		  if(led_color_buffer != led_color) // Store previous led color
		  {
			  previous_led_color = led_color_buffer;
			  led_color_buffer = led_color;
		  }



		  /*
		   * 		Sending datas
		   */
		  if(send_messages == true)
		  {
			  send_messages = false;

			  send_sec_msg_air_extraction_tachymeter(cooling_rpm, &huart2);
			  send_sec_msg_ee_temperature(ntc_values.temperatureC, &huart2);
			  send_main_msg_pressure(pressure, &huart2);

			  //Smart Light
			  if(previous_led_color != led_color)
			  {
				  send_main_msg_led_color(led_color, &huart2);
			  }

			  // Smart Power
			  if(return_value_SP == HAL_OK && temp_humi_SP.error_status == false)
			  {
				  send_main_msg_humidity(temp_humi_SP.humidity, MAIN_MSG_HUMIDITY_SP, &huart2);
				  send_main_msg_temperature(temp_humi_SP.temperature, MAIN_MSG_TEMPERATURE_SP, &huart2);
			  }

			  // Smart Sensor 1
			  if(return_value_SS_1 == HAL_OK && temp_humi_SS_1.error_status == false)
			  {
				  send_main_msg_humidity(temp_humi_SS_1.humidity, MAIN_MSG_HUMIDITY_SS_1, &huart2);
				  send_main_msg_temperature(temp_humi_SS_1.temperature, MAIN_MSG_TEMPERATURE_SS_1, &huart2);
			  }

			  // Smart Sensor 2
			  if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF &&
					  return_value_SS_2 == HAL_OK && temp_humi_SS_2.error_status == false)
			  {
				  send_main_msg_humidity(temp_humi_SS_2.humidity, MAIN_MSG_HUMIDITY_SS_2, &huart2);
				  send_main_msg_temperature(temp_humi_SS_2.temperature, MAIN_MSG_TEMPERATURE_SS_2, &huart2);
			  }

			  //SGP41
			  if(var_timer_4_tick > (SGP41_CONDITIONNING_TIME + SGP41_SRAW_FEEDING_TIME))
			  {
				  send_main_msg_nox(nox_index_value, &huart2);
				  send_main_msg_voc(voc_index_value, &huart2);
			  }

			  //Relay
			  send_main_msg_relay(relay_command, &huart2);



			  /*
			   * 		Watchdog
			   */
			  if(watchdog_actived == true)
			  {
				  watchdog_actived = false;
				  HAL_NVIC_SystemReset();
			  }

			  if(watchdog_update == true)
			  {
				  watchdog_update = false;
				  update_last_watchdog_time();
			  }
		  }
	  } else
	  {
//		  led_color_system_off = DARK; //no problem w/ the ligths if i add this variable

		  set_cooling_fan_pwm(PWM_STOP, &htim2);
		  set_heater_fan_pwm(PWM_STOP, &htim2);
		  set_heater(false);
		  set_lights(led_color_system_off);
		  set_relay_on(RELAY_OFF);
	  }


	  /*
	   * 	Reading Datas
	   */
	  if(uart2_irq_is_captured == true)
	  {
		  uart2_irq_is_captured = false;
		  parser(rx_buffer,&huart2);
		  memset(rx_buffer, ZERO, sizeof(rx_buffer));
		  HAL_UART_Receive_IT(&huart2, rx_buffer, MSG_SIZE);
	  }

	  if(uart5_irq_is_captured == true)
	  {
		  uart5_irq_is_captured = false;
		  parser(rx_buffer2,&huart2);
		  memset(rx_buffer2, ZERO, sizeof(rx_buffer2));
		  HAL_UART_Receive_IT(&huart5, rx_buffer2, MSG_SIZE);
	  }

	  if(get_i2c_values)
	  {
		  get_i2c_values = false;

		  /* SmartSensor */
		  return_value_SP = write_frame_temp_humi_SHT40(&hi2c1);
		  return_value_SS_1 = write_frame_temp_humi_SHT40(&hi2c2);
		  return_value_SS_2 = write_frame_temp_humi_SHT40(&hi2c3);

		  /* SGP41 */
		  if(sgp41_timer_init >= SGP41_CONDITIONNING_TIME) //if init is finished
			  sgp41_return_value = sgp41_send_command(&hi2c2, SGP41_MEASUREMENT_COMMAND, average_temperature, average_humidity);

		  HAL_TIM_Base_Start_IT(&htim9); // Start this timer to get all i2c values
	  }

	  if(var_timer_9_tick)	  //the timer 9 start if get_i2c_values = true and tick 50ms after that all frames are sent.
	  {							//Then the timer is stopped and we get all the temperatures
		  var_timer_9_tick = false;
		  HAL_TIM_Base_Stop_IT(&htim9);

		  temp_humi_SP = read_temp_humi_SHT40(&hi2c1);
		  temp_humi_SS_1 = read_temp_humi_SHT40(&hi2c2);
		  temp_humi_SS_2 = read_temp_humi_SHT40(&hi2c3);

		  // if init is finished and i2c communication is established
		  if(sgp41_timer_init >= SGP41_CONDITIONNING_TIME && sgp41_return_value == HAL_OK)
		 {
			  pollution_data = sgp41_receive_raw_datas(&hi2c2);

		      GasIndexAlgorithm_process(&params_nox, pollution_data.sraw_nox, &nox_index_value);
		      GasIndexAlgorithm_process(&params_voc, pollution_data.sraw_voc, &voc_index_value);
		 }
	  }

	  cooling_frq = get_cooling_frequency();
	  cooling_rpm = get_cooling_rpm();
	  adc_temperature_raw_value = reading_adc_channel_0();
	  ntc_values = applying_coefficients(adc_temperature_raw_value);
	  ntc_values.temperatureC = temperature_calculation(ntc_values);
	  if(MSG_HEADER_UID_1_TYPOLOGY == TYPE_MACHINE_ROOF || MSG_HEADER_UID_1_TYPOLOGY == TYPE_POST_TREATMENT) door_state = get_latches_state();

	  //Initialization of sgp41
	  if(sgp41_tick && sgp41_timer_init < SGP41_CONDITIONNING_TIME)
	  {
		  sgp41_tick = false;
		  sgp41_timer_init += ONE;

		  sgp41_return_value = sgp41_send_command(&hi2c2, SGP41_INITIALIZATION_COMMAND, SGP41_INIT_TEMPERATURE, SGP41_INIT_HUMIDITY);
	  }

	  //Average temperature and humidity
	  average_humidity = (temp_humi_SP.humidity + temp_humi_SS_1.humidity) / (float)TWO;
	  average_temperature = (temp_humi_SP.temperature + temp_humi_SS_1.temperature) / (float)TWO;

	  /*
	   * 		Sound module
	   */
	  if(sm_next)
	  {
		  sm_next = false;
		  sm_next_track();
	  }
	  if(sm_pause)
	  {
		  sm_pause = false;
		  sm_pause_track();
	  }
	  if(sm_stop)
	  {
		  sm_stop = false;
		  sm_stop_track();
	  }
	  if(sm_previous)
	  {
		  sm_previous = false;
		  sm_previous_track();
	  }

	  if(sm_repeat)
	  {
		  sm_repeat_track(sm_repeat);
		  sm_repeat = false;
	  }

	  if(sm_playback)
	  {
		  sm_playback = false;
		  sm_playback_track();
	  }

	  if(previous_sm_volume != sm_volume)
	  {
		  sm_change_volume(sm_volume);
		  previous_sm_volume = sm_volume;
	  }

	  if(previous_sm_eq != sm_eq)
	  {
		  sm_select_eq(sm_eq);
		  previous_sm_eq = sm_eq;
	  }

	  if(previous_sm_track != sm_track)
	  {
		  sm_select_track(sm_track);
		  previous_sm_track = sm_track;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 2-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 100-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 2000-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 2000-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0xFFFF;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 2000-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 2000-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 10000-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 20-1;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 50000-1;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */

}

/**
  * @brief TIM12 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM12_Init(void)
{

  /* USER CODE BEGIN TIM12_Init 0 */

  /* USER CODE END TIM12_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM12_Init 1 */

  /* USER CODE END TIM12_Init 1 */
  htim12.Instance = TIM12;
  htim12.Init.Prescaler = 2-1;
  htim12.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim12.Init.Period = 100-1;
  htim12.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim12) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM12_Init 2 */

  /* USER CODE END TIM12_Init 2 */
  HAL_TIM_MspPostInit(&htim12);

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RELAY_Pin|DOOR_CMD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HEATER_GPIO_Port, HEATER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : DOOR_RIGHT_LATCH_Pin */
  GPIO_InitStruct.Pin = DOOR_RIGHT_LATCH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DOOR_RIGHT_LATCH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DOOR_LEFT_LATCH_Pin */
  GPIO_InitStruct.Pin = DOOR_LEFT_LATCH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DOOR_LEFT_LATCH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RELAY_Pin DOOR_CMD_Pin */
  GPIO_InitStruct.Pin = RELAY_Pin|DOOR_CMD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : HEATER_Pin */
  GPIO_InitStruct.Pin = HEATER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HEATER_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void update_last_watchdog_time(){
	last_watchdog_time = var_timer_4_tick;
}

/**
 * @brief Callback called after a period of a timer
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM4)
	{

		//each
		if(var_timer_4_tick % TWO == ZERO) // each 2s
		{
			send_messages = true;

			if(last_watchdog_time > var_timer_4_tick)
			{ // Clock overflow

				last_watchdog_time = ZERO;
			}
			if(var_timer_4_tick - last_watchdog_time > WATCHDOG_TIME)
			{

				watchdog_actived = true;
			}
		}

		//I2C
		if(get_i2c_values == false && var_timer_9_tick == ZERO) get_i2c_values = true;

		//SGP41
		if(sgp41_timer_init < SGP41_CONDITIONNING_TIME) sgp41_tick = true;

		var_timer_4_tick += 1;
	}


	//each second : DOOR
	if(htim->Instance == TIM7)
	{
		var_timer_7_tick += 1;
	}

	//each 50ms : I2C
	if(htim->Instance == TIM9)
	{
		var_timer_9_tick = true;
	}
}

/**
 * @brief Callback used when received a message (full buffer)
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance == USART2)
	{
		uart2_irq_is_captured = true;
	}

	else if(huart->Instance == UART5)
	{
		uart5_irq_is_captured = true;
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim -> Channel == HAL_TIM_ACTIVE_CHANNEL_1) // Tachymeter channel
	{
		if(is_first_captured_cooling == 0)
		{
			ic_val1_cooling = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			is_first_captured_cooling = 1;
		}
		else
		{
			ic_val2_cooling = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			if (ic_val2_cooling > ic_val1_cooling) {
				difference_cooling = ic_val2_cooling - ic_val1_cooling;
			} else if (ic_val1_cooling > ic_val2_cooling) {
				difference_cooling = (0xffffffff - ic_val1_cooling) + ic_val2_cooling;
			}

			float refClock = TIMCLOCK/PRESCALER;

			cooling_frq = refClock/difference_cooling;

			__HAL_TIM_SET_COUNTER(htim, 0);
			is_first_captured_cooling = 0;
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
