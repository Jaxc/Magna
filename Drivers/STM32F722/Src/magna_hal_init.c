/*
 * HAL_init.c
 *
 *  Created on: Mar 26, 2020
 *      Author: jaxc
 */

/* Includes ------------------------------------------------------------------*/
#include "magna_hal_init.h"

#include "../../../usbd/inc/usb_magna.h"
#include "dma.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "sai.h"
#include "spi.h"

uint8_t test_0[256], test_1[256];

static usb_magna_t mag = {
    .midi_rx_buffer = &test_0[0],
    .cdc_rx_buffer = &test_1[0],
    .midi_rx_size = 256,
    .cdc_rx_size = 256,
    .midi_user = NULL,
    .cdc_user = NULL,
    .midi_rx_complete = NULL,
    .midi_tx_complete = NULL,
    .cdc_rx_complete = NULL,
    .cdc_tx_complete = NULL,
};

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* function for replacing STs main function*/
void magna_hal_init(void)
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

  usb_magna_init(&mag);

}
