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
#include "queue.h"

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
    while(1) {
        queue_execute();

        //usbd_delay_ms(1000);
        //static uint8_t msg[256] = "Hello world\r\n";
        //int msg_len = sizeof(msg);

        //manga_error_code_t ret = usb_cdc_transmit(msg, msg_len);

    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

}
