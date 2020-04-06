/*
 * audio_interface.c
 *
 *  Created on: Apr 2, 2020
 *      Author: jaxc
 */
#include "sai.h"
#include <string.h>

#define BUFFERSIZE 200
extern uint32_t usbd_internal_buffer[48 * 2 ];
uint32_t buffer_read_ = 0;

#define OUTPUT_BUFFER_SAMPLES 48
#define OUTPUT_BUFFER_CHANNELS 2
#define OUTPUT_BUFFER_SIZE OUTPUT_BUFFER_SAMPLES * OUTPUT_BUFFER_CHANNELS

uint32_t audio_output_buffer[2][OUTPUT_BUFFER_SIZE] = {0};
uint8_t buffer_sel = 0;

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
    (void)hsai;

    HAL_SAI_Receive_DMA(&hsai_BlockB2, (uint8_t * )audio_Input_buffer_1, OUTPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&hsai_BlockA2, (uint8_t * )audio_Input_buffer_2, OUTPUT_BUFFER_SIZE);

    HAL_SAI_Transmit_DMA(&hsai_BlockB1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);
    HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);

    buffer_sel = (buffer_sel + 1) % 2;
    memcpy(&audio_output_buffer[buffer_sel], &usbd_internal_buffer, sizeof(usbd_internal_buffer));
    for(uint8_t i = 0; i < OUTPUT_BUFFER_SIZE; i++) {

    }
    buffer_read_++;
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai) {
    (void) hsai;
}
