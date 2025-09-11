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
#include "stm32f7xx_hal.h"

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
#define USB_PHY_RESET_Pin GPIO_PIN_14
#define USB_PHY_RESET_GPIO_Port GPIOC
#define ADC_FORMAT_Pin GPIO_PIN_15
#define ADC_FORMAT_GPIO_Port GPIOC
#define OE_output_ena_Pin GPIO_PIN_7
#define OE_output_ena_GPIO_Port GPIOA
#define VBUS_ADC_Pin GPIO_PIN_5
#define VBUS_ADC_GPIO_Port GPIOC
#define serial_CLK_Pin GPIO_PIN_12
#define serial_CLK_GPIO_Port GPIOE
#define serial_CLR_Pin GPIO_PIN_13
#define serial_CLR_GPIO_Port GPIOE
#define serial_data_Pin GPIO_PIN_14
#define serial_data_GPIO_Port GPIOE
#define Pot_sel_0_Pin GPIO_PIN_12
#define Pot_sel_0_GPIO_Port GPIOD
#define Pot_sel_1_Pin GPIO_PIN_13
#define Pot_sel_1_GPIO_Port GPIOD
#define ADC_M_S_Pin GPIO_PIN_15
#define ADC_M_S_GPIO_Port GPIOD
#define HSW_EN_Pin GPIO_PIN_10
#define HSW_EN_GPIO_Port GPIOA
#define VBUS_OUT_FLG_Pin GPIO_PIN_1
#define VBUS_OUT_FLG_GPIO_Port GPIOD
#define Button_interrupt_Pin GPIO_PIN_6
#define Button_interrupt_GPIO_Port GPIOD
#define SCL_ADC_IWL_Pin GPIO_PIN_6
#define SCL_ADC_IWL_GPIO_Port GPIOB
#define SDA_ADC_FSAMPEN_Pin GPIO_PIN_7
#define SDA_ADC_FSAMPEN_GPIO_Port GPIOB
#define USB_A_PWR_EN_Pin GPIO_PIN_0
#define USB_A_PWR_EN_GPIO_Port GPIOE
#define VA_en_Pin GPIO_PIN_1
#define VA_en_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
