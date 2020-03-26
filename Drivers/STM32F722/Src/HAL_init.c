/*
 * HAL_init.c
 *
 *  Created on: Mar 26, 2020
 *      Author: jaxc
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"



/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* function for replacing STs main function*/
void init_hal(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();

}
