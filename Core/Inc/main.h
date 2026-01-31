/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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
#define VALF1_ON_Pin GPIO_PIN_0
#define VALF1_ON_GPIO_Port GPIOA
#define VALF1_OFF_Pin GPIO_PIN_1
#define VALF1_OFF_GPIO_Port GPIOA
#define VALF2_ON_Pin GPIO_PIN_2
#define VALF2_ON_GPIO_Port GPIOA
#define VALF2_OFF_Pin GPIO_PIN_3
#define VALF2_OFF_GPIO_Port GPIOA
#define VALF3_ON_Pin GPIO_PIN_4
#define VALF3_ON_GPIO_Port GPIOA
#define VALF3_OFF_Pin GPIO_PIN_5
#define VALF3_OFF_GPIO_Port GPIOA
#define VALF4_ON_Pin GPIO_PIN_6
#define VALF4_ON_GPIO_Port GPIOA
#define VALF4_OFF_Pin GPIO_PIN_7
#define VALF4_OFF_GPIO_Port GPIOA
#define VALF5_ON_Pin GPIO_PIN_4
#define VALF5_ON_GPIO_Port GPIOC
#define VALF5_OFF_Pin GPIO_PIN_5
#define VALF5_OFF_GPIO_Port GPIOC
#define VALF6_ON_Pin GPIO_PIN_0
#define VALF6_ON_GPIO_Port GPIOB
#define VALF6_OFF_Pin GPIO_PIN_1
#define VALF6_OFF_GPIO_Port GPIOB
#define VALF7_ON_Pin GPIO_PIN_2
#define VALF7_ON_GPIO_Port GPIOB
#define VALF7_OFF_Pin GPIO_PIN_10
#define VALF7_OFF_GPIO_Port GPIOB
#define VALF8_ON_Pin GPIO_PIN_11
#define VALF8_ON_GPIO_Port GPIOB
#define VALF8_OFF_Pin GPIO_PIN_12
#define VALF8_OFF_GPIO_Port GPIOB
#define VALF9_ON_Pin GPIO_PIN_13
#define VALF9_ON_GPIO_Port GPIOB
#define VALF9_OFF_Pin GPIO_PIN_14
#define VALF9_OFF_GPIO_Port GPIOB
#define BUTTON_1_Pin GPIO_PIN_15
#define BUTTON_1_GPIO_Port GPIOB
#define BUTTON_2_Pin GPIO_PIN_8
#define BUTTON_2_GPIO_Port GPIOA
#define BUTTON_3_Pin GPIO_PIN_9
#define BUTTON_3_GPIO_Port GPIOA
#define BUTTON_4_Pin GPIO_PIN_6
#define BUTTON_4_GPIO_Port GPIOC
#define BUTTON_5_Pin GPIO_PIN_7
#define BUTTON_5_GPIO_Port GPIOC
#define MCP2515_INT_Pin GPIO_PIN_9
#define MCP2515_INT_GPIO_Port GPIOD
#define MCP2515_RST_Pin GPIO_PIN_10
#define MCP2515_RST_GPIO_Port GPIOA
#define MCP2515_MISO_Pin GPIO_PIN_11
#define MCP2515_MISO_GPIO_Port GPIOA
#define MCP2515_MOSI_Pin GPIO_PIN_12
#define MCP2515_MOSI_GPIO_Port GPIOA
#define BUTTON_6_Pin GPIO_PIN_15
#define BUTTON_6_GPIO_Port GPIOA
#define VALF10_ON_PWM_Pin GPIO_PIN_8
#define VALF10_ON_PWM_GPIO_Port GPIOC
#define VALF10_OFF_PWM_Pin GPIO_PIN_9
#define VALF10_OFF_PWM_GPIO_Port GPIOC
#define BUTTON_MODE_Pin GPIO_PIN_0
#define BUTTON_MODE_GPIO_Port GPIOD
#define BUTTON_MENU_Pin GPIO_PIN_1
#define BUTTON_MENU_GPIO_Port GPIOD
#define BUTTON_PLUS_Pin GPIO_PIN_2
#define BUTTON_PLUS_GPIO_Port GPIOD
#define BUTTON_MINUS_Pin GPIO_PIN_3
#define BUTTON_MINUS_GPIO_Port GPIOD
#define BUTTON_MAIN_Pin GPIO_PIN_4
#define BUTTON_MAIN_GPIO_Port GPIOD
#define BUZZER_Pin GPIO_PIN_6
#define BUZZER_GPIO_Port GPIOD
#define BUTTON_7_Pin GPIO_PIN_3
#define BUTTON_7_GPIO_Port GPIOB
#define BUTTON_8_Pin GPIO_PIN_4
#define BUTTON_8_GPIO_Port GPIOB
#define FLOWINPUT_Pin GPIO_PIN_5
#define FLOWINPUT_GPIO_Port GPIOB
#define BUTTON_GPS_Pin GPIO_PIN_6
#define BUTTON_GPS_GPIO_Port GPIOB
#define BUTTON_PROGRAM_Pin GPIO_PIN_7
#define BUTTON_PROGRAM_GPIO_Port GPIOB
#define MCP2515_CS_Pin GPIO_PIN_10
#define MCP2515_CS_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
