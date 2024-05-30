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
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "u8g2.h"
#include "ring_buffer.h"
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
#define PLUS_KEY_Pin GPIO_PIN_7
#define PLUS_KEY_GPIO_Port GPIOB
#define PLUS_KEY_EXTI_IRQn EXTI4_15_IRQn
#define OK_KEY_Pin GPIO_PIN_14
#define OK_KEY_GPIO_Port GPIOC
#define OK_KEY_EXTI_IRQn EXTI4_15_IRQn
#define MINUS_KEY_Pin GPIO_PIN_15
#define MINUS_KEY_GPIO_Port GPIOC
#define MINUS_KEY_EXTI_IRQn EXTI4_15_IRQn
#define DC_Pin GPIO_PIN_5
#define DC_GPIO_Port GPIOA
#define RES_Pin GPIO_PIN_6
#define RES_GPIO_Port GPIOA
#define INPUT_EI_Pin GPIO_PIN_11
#define INPUT_EI_GPIO_Port GPIOA
#define INPUT_EI_EXTI_IRQn EXTI4_15_IRQn

/* USER CODE BEGIN Private defines */
uint8_t u8x8_gpio_and_delay_stm32(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t getCurPageNum();
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
