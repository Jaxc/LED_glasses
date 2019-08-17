/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */
#include "tim.h"
#include "pattern_generate.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
const uint16_t bpm_settings[] = {43478, 34483, 21739, 17241};
/*const uint16_t bpm_settings[] = {46154, 45455, 44776, 44118, 43478, 42857,
        42254, 41379, 40000, 38710, 37500, 36364, 35294, 34884, 34483, 34091,
        33333, 31579, 30000};*/
uint8_t current_bpm = 0;
uint8_t len_bpm = 4;
/* USER CODE END 1 */

/** Configure pins
     PA8   ------> RCC_MCO
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BTN_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTN_1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == BTN_1_Pin) {
        HAL_NVIC_DisableIRQ(BTN_1_EXTI_IRQn);
        HAL_NVIC_DisableIRQ(BTN_2_EXTI_IRQn);
        HAL_TIM_Base_Start_IT(&htim7);
        cycle_effects();
        //HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);

    } else if (GPIO_Pin == BTN_2_Pin) {
        HAL_NVIC_DisableIRQ(BTN_1_EXTI_IRQn);
        HAL_NVIC_DisableIRQ(BTN_2_EXTI_IRQn);
        HAL_TIM_Base_Start_IT(&htim7);
        current_bpm = (current_bpm + 1) % len_bpm;
        __HAL_TIM_SET_AUTORELOAD(&htim14, bpm_settings[current_bpm] - 1);
    }
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
