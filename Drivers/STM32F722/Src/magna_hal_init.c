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
#include "gpio.h"
#include "sai.h"
#include "i2c.h"
#include "gpio.h"

#define BUFFER_SIZE 512
#define BUFFER_CIRCLE_SIZE 3
uint8_t audio_rx_buf[BUFFER_CIRCLE_SIZE][BUFFER_SIZE], audio_rx_2_buf[BUFFER_SIZE];
uint8_t audio_tx_buf[BUFFER_CIRCLE_SIZE][BUFFER_SIZE], audio_tx_2_buf[BUFFER_SIZE];

static usb_magna_t magna_buffer_config = {
    .audio_rx_buffer = &audio_rx_buf[0][0],
    .audio_tx_buffer = &audio_tx_buf[0][0],
    .audio_rx_size = BUFFER_SIZE,
    .audio_tx_size = BUFFER_SIZE,
    .midi_user = NULL,
    .cdc_user = NULL,
    .audio_rx_complete = NULL,
    .audio_tx_complete = NULL,
};

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* function for replacing STs main function*/
void magna_hal_init(void)
{

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();


  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_SAI2_Init();
  MX_SAI1_Init();
  MX_I2C1_Init();
  MX_GPIO_Init();

  usb_magna_init(&magna_buffer_config);

}
