/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, VALF1_ON_Pin|VALF1_OFF_Pin|VALF2_ON_Pin|VALF2_OFF_Pin
                          |VALF3_ON_Pin|VALF3_OFF_Pin|VALF4_ON_Pin|VALF4_OFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, VALF5_ON_Pin|VALF5_OFF_Pin|MCP2515_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, VALF6_ON_Pin|VALF6_OFF_Pin|VALF7_ON_Pin|VALF7_OFF_Pin
                          |VALF8_ON_Pin|VALF8_OFF_Pin|VALF9_ON_Pin|VALF9_OFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MCP2515_RST_GPIO_Port, MCP2515_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : VALF1_ON_Pin VALF1_OFF_Pin VALF2_ON_Pin VALF2_OFF_Pin
                           VALF3_ON_Pin VALF3_OFF_Pin VALF4_ON_Pin VALF4_OFF_Pin
                           MCP2515_RST_Pin */
  GPIO_InitStruct.Pin = VALF1_ON_Pin|VALF1_OFF_Pin|VALF2_ON_Pin|VALF2_OFF_Pin
                          |VALF3_ON_Pin|VALF3_OFF_Pin|VALF4_ON_Pin|VALF4_OFF_Pin
                          |MCP2515_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : VALF5_ON_Pin VALF5_OFF_Pin MCP2515_CS_Pin */
  GPIO_InitStruct.Pin = VALF5_ON_Pin|VALF5_OFF_Pin|MCP2515_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : VALF6_ON_Pin VALF6_OFF_Pin VALF7_ON_Pin VALF7_OFF_Pin
                           VALF8_ON_Pin VALF8_OFF_Pin VALF9_ON_Pin VALF9_OFF_Pin */
  GPIO_InitStruct.Pin = VALF6_ON_Pin|VALF6_OFF_Pin|VALF7_ON_Pin|VALF7_OFF_Pin
                          |VALF8_ON_Pin|VALF8_OFF_Pin|VALF9_ON_Pin|VALF9_OFF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_1_Pin BUTTON_7_Pin BUTTON_8_Pin BUTTON_GPS_Pin
                           BUTTON_PROGRAM_Pin */
  GPIO_InitStruct.Pin = BUTTON_1_Pin|BUTTON_7_Pin|BUTTON_8_Pin|BUTTON_GPS_Pin
                          |BUTTON_PROGRAM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_2_Pin BUTTON_3_Pin BUTTON_6_Pin */
  GPIO_InitStruct.Pin = BUTTON_2_Pin|BUTTON_3_Pin|BUTTON_6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_4_Pin BUTTON_5_Pin */
  GPIO_InitStruct.Pin = BUTTON_4_Pin|BUTTON_5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : MCP2515_INT_Pin */
  GPIO_InitStruct.Pin = MCP2515_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MCP2515_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_MODE_Pin BUTTON_MENU_Pin BUTTON_PLUS_Pin BUTTON_MINUS_Pin
                           BUTTON_MAIN_Pin */
  GPIO_InitStruct.Pin = BUTTON_MODE_Pin|BUTTON_MENU_Pin|BUTTON_PLUS_Pin|BUTTON_MINUS_Pin
                          |BUTTON_MAIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : BUZZER_Pin */
  GPIO_InitStruct.Pin = BUZZER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
