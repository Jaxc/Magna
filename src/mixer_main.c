/*
 * main.c
 *
 *  Created on: Mar 26, 2020
 *      Author: jaxc
 */

#include "magna_hal_init.h"
#include "usb_magna.h"
#include "tim.h"
#include "adc.h"
#include "error_codes.h"
#include <stdio.h>
#include "usbd_internal.h"
#include "usart.h"
#include "audio_interface.h"

uint16_t adc_data[8];

int _write(int file, char *ptr, int len);

extern usb_setup_packet_t setup_trace[1024];
extern uint16_t trace_cnt;

int main (void) {
    magna_hal_init();

/*    for (char i = 0; i < 100; i++) {
        ITM_SendChar(i);
    }*/

    __HAL_DBGMCU_FREEZE_TIM1();
    __HAL_DBGMCU_FREEZE_TIM2();
    __HAL_DBGMCU_FREEZE_TIM3();
    __HAL_DBGMCU_FREEZE_TIM4();
    __HAL_DBGMCU_FREEZE_TIM6();
    __HAL_DBGMCU_FREEZE_TIM7();
    __HAL_DBGMCU_FREEZE_TIM14();
    __HAL_DBGMCU_FREEZE_TIM11();


    uint8_t j = 0;

    htim11.Instance->CNT = 0;
    __disable_irq();
    __HAL_TIM_ENABLE(&htim11);

    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;
    j++;

    __HAL_TIM_DISABLE(&htim11);
    __enable_irq();

    init_codec();

    start_codecs();

    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
    //HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_3);
    //HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_4);
    HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);
    //HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);

    //HAL_ADC_Start_DMA(&hadc1, adc_data, 8);
    usbd_delay_ms(10000);

    uint8_t status_size = 45;

    char current_status[status_size];
    for (int i = 0; i < trace_cnt; i++) {

        snprintf(current_status,status_size,"%03d recip: %02x, req:%02x,index:%04x,val:%04x \r\n", i, setup_trace[i].bmRequestType.recipient, setup_trace[i].bRequest, setup_trace[i].wIndex, setup_trace[i].wValue);
        HAL_UART_Transmit(&huart3,(uint8_t *)current_status, status_size, 1000);
        _write(0,current_status, status_size);
        //usbd_delay_ms(10);

    }

    uint8_t new_usb_data = 0;
    while(1) {

        if (0 != new_usb_data) {


        }


        //usbd_delay_ms(1000);
        //static uint8_t msg[256] = "Hello world\r\n";
        //int msg_len = sizeof(msg);

        //manga_error_code_t ret = usb_cdc_transmit(msg, msg_len);

    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

}
