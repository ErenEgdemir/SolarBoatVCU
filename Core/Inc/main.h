/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIS_WAKEUP_Pin GPIO_PIN_3
#define DIS_WAKEUP_GPIO_Port GPIOE
#define DIS_RESET_Pin GPIO_PIN_4
#define DIS_RESET_GPIO_Port GPIOE
#define BTN_1_Pin GPIO_PIN_5
#define BTN_1_GPIO_Port GPIOE
#define BTN_2_Pin GPIO_PIN_6
#define BTN_2_GPIO_Port GPIOE
#define BTN_4_Pin GPIO_PIN_14
#define BTN_4_GPIO_Port GPIOC
#define BTN_5_Pin GPIO_PIN_15
#define BTN_5_GPIO_Port GPIOC
#define C_MPPT_1_Pin GPIO_PIN_0
#define C_MPPT_1_GPIO_Port GPIOC
#define C_MPPT_2_Pin GPIO_PIN_1
#define C_MPPT_2_GPIO_Port GPIOC
#define C_MPPT_3_Pin GPIO_PIN_2
#define C_MPPT_3_GPIO_Port GPIOC
#define C_MPPT_4_Pin GPIO_PIN_3
#define C_MPPT_4_GPIO_Port GPIOC
#define C_MPPT_5_Pin GPIO_PIN_0
#define C_MPPT_5_GPIO_Port GPIOA
#define C_MPPT_6_Pin GPIO_PIN_1
#define C_MPPT_6_GPIO_Port GPIOA
#define HYDROFOIL_Pin GPIO_PIN_2
#define HYDROFOIL_GPIO_Port GPIOA
#define T_MPPT_2_Pin GPIO_PIN_3
#define T_MPPT_2_GPIO_Port GPIOA
#define T_MPPT_3_Pin GPIO_PIN_4
#define T_MPPT_3_GPIO_Port GPIOA
#define T_MPPT_4_Pin GPIO_PIN_5
#define T_MPPT_4_GPIO_Port GPIOA
#define T_MPPT_5_Pin GPIO_PIN_6
#define T_MPPT_5_GPIO_Port GPIOA
#define T_MPPT_6_Pin GPIO_PIN_7
#define T_MPPT_6_GPIO_Port GPIOA
#define T_MOTOR_Pin GPIO_PIN_4
#define T_MOTOR_GPIO_Port GPIOC
#define T_ESC_Pin GPIO_PIN_5
#define T_ESC_GPIO_Port GPIOC
#define MULTIPLEXER_Pin GPIO_PIN_0
#define MULTIPLEXER_GPIO_Port GPIOB
#define THROTTLE_Pin GPIO_PIN_1
#define THROTTLE_GPIO_Port GPIOB
#define MPX_1_Pin GPIO_PIN_7
#define MPX_1_GPIO_Port GPIOE
#define MPX_2_Pin GPIO_PIN_8
#define MPX_2_GPIO_Port GPIOE
#define MPX_3_Pin GPIO_PIN_9
#define MPX_3_GPIO_Port GPIOE
#define MPX_4_Pin GPIO_PIN_10
#define MPX_4_GPIO_Port GPIOE
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define DHT_11_Pin GPIO_PIN_11
#define DHT_11_GPIO_Port GPIOD
#define W_SENS_A_Pin GPIO_PIN_12
#define W_SENS_A_GPIO_Port GPIOD
#define W_SENS_B_Pin GPIO_PIN_13
#define W_SENS_B_GPIO_Port GPIOD
#define S_SERVO_Pin GPIO_PIN_6
#define S_SERVO_GPIO_Port GPIOC
#define RELAY_6_Pin GPIO_PIN_11
#define RELAY_6_GPIO_Port GPIOC
#define RELAY_5_Pin GPIO_PIN_12
#define RELAY_5_GPIO_Port GPIOC
#define RELAY_4_Pin GPIO_PIN_0
#define RELAY_4_GPIO_Port GPIOD
#define RELAY_3_Pin GPIO_PIN_1
#define RELAY_3_GPIO_Port GPIOD
#define RELAY_2_Pin GPIO_PIN_2
#define RELAY_2_GPIO_Port GPIOD
#define W_COOL_Pin GPIO_PIN_3
#define W_COOL_GPIO_Port GPIOD
#define UART_GPS_TX_Pin GPIO_PIN_5
#define UART_GPS_TX_GPIO_Port GPIOD
#define UART_GPS_RX_Pin GPIO_PIN_6
#define UART_GPS_RX_GPIO_Port GPIOD
#define PWM_THROTTLE_Pin GPIO_PIN_3
#define PWM_THROTTLE_GPIO_Port GPIOB
#define I2C_INTERRUPT_Pin GPIO_PIN_5
#define I2C_INTERRUPT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
