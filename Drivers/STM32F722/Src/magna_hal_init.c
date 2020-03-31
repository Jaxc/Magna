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

#define BUFFER_SIZE 256
uint8_t audio_rx_1_buf[BUFFER_SIZE], audio_rx_2_buf[BUFFER_SIZE];
uint8_t audio_tx_1_buf[BUFFER_SIZE], audio_tx_2_buf[BUFFER_SIZE];

static usb_magna_t magna_buffer_config = {
    .audio_rx_1_buffer = &audio_rx_1_buf[0],
    .audio_rx_2_buffer = &audio_rx_2_buf[0],
    .audio_tx_1_buffer = &audio_tx_1_buf[0],
    .audio_tx_2_buffer = &audio_tx_2_buf[0],
    .audio_rx_1_size = BUFFER_SIZE,
    .audio_rx_2_size = BUFFER_SIZE,
    .audio_tx_1_size = BUFFER_SIZE,
    .audio_tx_2_size = BUFFER_SIZE,
    .midi_user = NULL,
    .cdc_user = NULL,
    .audio_rx_1_complete = NULL,
    .audio_rx_2_complete = NULL,
    .audio_tx_1_complete = NULL,
    .audio_tx_2_complete = NULL,
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

  usb_magna_init(&magna_buffer_config);

}
