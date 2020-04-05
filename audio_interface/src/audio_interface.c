/*
 * audio_interface.c
 *
 *  Created on: Apr 2, 2020
 *      Author: jaxc
 */
#include "sai.h"

#define OUTPUT_BUFFER_SIZE 96*2
uint32_t audio_output_buffer[OUTPUT_BUFFER_SIZE] = {0};

uint32_t audio_Input_buffer_1[OUTPUT_BUFFER_SIZE] = {0};
uint32_t audio_Input_buffer_2[OUTPUT_BUFFER_SIZE] = {0};

uint8_t triangle_wave = 0;
uint8_t triangle_wave_2 = 0;

void start_codecs(void) {

    HAL_SAI_Receive_DMA(&hsai_BlockB2, (uint8_t * )audio_Input_buffer_1, OUTPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&hsai_BlockA2, (uint8_t * )audio_Input_buffer_2, OUTPUT_BUFFER_SIZE);

    HAL_SAI_Transmit_DMA(&hsai_BlockB1, (uint8_t * )audio_output_buffer, OUTPUT_BUFFER_SIZE);
    HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t * )audio_output_buffer, OUTPUT_BUFFER_SIZE);

}


void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai) {

    (void) hsai;
    for(uint8_t i; i < OUTPUT_BUFFER_SIZE; i+=2) {
        audio_output_buffer[i] = (uint32_t)triangle_wave << 8;
        audio_output_buffer[i+1] = 0;//(uint32_t)triangle_wave_2 << 8;
        triangle_wave ++;
        triangle_wave_2 += 2;
    }

    //usbd_ep_receive(ctx, USBD_AUDIO_OUT, test_buffer, USBD_ISOC_PACKET_SIZE);

    HAL_SAI_Receive_DMA(&hsai_BlockB2, (uint8_t * )audio_Input_buffer_1, OUTPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&hsai_BlockA2, (uint8_t * )audio_Input_buffer_2, OUTPUT_BUFFER_SIZE);

    HAL_SAI_Transmit_DMA(&hsai_BlockB1, (uint8_t * )audio_output_buffer, OUTPUT_BUFFER_SIZE);
    HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t * )audio_output_buffer, OUTPUT_BUFFER_SIZE);
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai) {
    (void) hsai;
}
