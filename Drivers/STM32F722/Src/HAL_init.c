/*
 * HAL_init.c
 *
 *  Created on: Mar 26, 2020
 *      Author: jaxc
 */

/* Includes ------------------------------------------------------------------*/
#include "dma.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "sai.h"
#include "spi.h"



/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* function for replacing STs main function*/
void init_hal(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_SAI1_Init();
  MX_SAI2_Init();
  MX_SPI2_Init();
  MX_USB_DEVICE_Init();

}
