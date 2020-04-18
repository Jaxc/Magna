/*
 * audio_interface.c
 *
 *  Created on: Apr 2, 2020
 *      Author: jaxc
 */
#include "sai.h"
#include <string.h>
#include "audio_interface.h"

#define BUFFERSIZE 200
#define N_CIRC_BUFFER 2
extern uint32_t usbd_internal_buffer[48 * 2 ];
uint32_t buffer_read_ = 0;

#define OUTPUT_BUFFER_SAMPLES 4800
#define OUTPUT_BUFFER_CHANNELS 2
#define OUTPUT_BUFFER_SIZE OUTPUT_BUFFER_SAMPLES * OUTPUT_BUFFER_CHANNELS

uint32_t audio_output_buffer[N_CIRC_BUFFER][OUTPUT_BUFFER_SIZE] = {0};
uint8_t buffer_sel = 1;

#define INT_BUFF_SIZE 32
uint32_t intermediate_buffer [INT_BUFF_SIZE][OUTPUT_BUFFER_SIZE];

uint8_t int_read_cnt = 0;
uint8_t int_write_cnt = INT_BUFF_SIZE / 2;

uint32_t audio_Input_buffer_1[N_CIRC_BUFFER][OUTPUT_BUFFER_SIZE] = {0};
uint32_t audio_Input_buffer_2[N_CIRC_BUFFER][OUTPUT_BUFFER_SIZE] = {0};

uint8_t triangle_wave = 0;
uint8_t triangle_wave_2 = 0;

struct rx_buffer_info_t rx_buffer_info_audio;

void sai_buffer_1_complete_callback(SAI_HandleTypeDef *hsai);
void sai_buffer_2_complete_callback(SAI_HandleTypeDef *hsai);

//static void SAI_DMAError(DMA_HandleTypeDef *hdma);

manga_error_code_t sai_receive_dma_double_buffer(SAI_HandleTypeDef *hsai, uint8_t *buffer1, uint8_t *buffer2, uint16_t buffer_size)
{

    manga_error_code_t ret = MAGNA_OK;

    if((buffer1 == NULL) || (buffer2 == NULL)) {
        ret = MAGNA_INVALID_ARGUMENT;
    } else if(buffer_size == 0) {
        ret = MAGNA_INVALID_ARGUMENT;
    } else if(hsai->State == HAL_SAI_STATE_READY) {
        /* Lock HW */
        if (HAL_LOCKED == hsai->Lock) {
            ret = MAGNA_HAL_BUSY;
        } else {
            hsai->Lock = HAL_LOCKED;


            hsai->ErrorCode = HAL_SAI_ERROR_NONE;
            hsai->State = HAL_SAI_STATE_BUSY_RX;

            /* Setup DMA */
            if(HAL_DMAEx_MultiBufferStart_IT(hsai->hdmarx, (uint32_t)&hsai->Instance->DR, (uint32_t)buffer1, (uint32_t)buffer2, buffer_size) != HAL_OK)
            {
                hsai->Lock = HAL_UNLOCKED;
                ret = MAGNA_HAL_ERROR;
            }

            if (MAGNA_OK == ret) {
                /* Check If SAI is enabled, enable if not. */
                if((hsai->Instance->CR1 & SAI_xCR1_SAIEN) == RESET)
                {
                    hsai->Instance->CR1 |= SAI_xCR1_SAIEN;
                }

                /* Enable error handling interrupts */
                if((hsai->Init.AudioMode == SAI_MODESLAVE_RX) || (hsai->Init.AudioMode == SAI_MODESLAVE_TX)) {
                    /* Slave interrupts */
                    hsai->Instance->IMR |= SAI_IT_AFSDET | SAI_IT_LFSDET;
                } else {
                  /* Master interrupts */
                    hsai->Instance->IMR |= SAI_IT_WCKCFG;
                }

                /* Enable SAI Rx DMA Request */
                hsai->Instance->CR1 |= SAI_xCR1_DMAEN;

                /* Process Unlocked */
                hsai->Lock = HAL_UNLOCKED;
            }
        }

        ret = MAGNA_OK;
    } else {
        /* HAL BUSY */
        ret = MAGNA_HAL_BUSY;
    }
    return ret;
}

manga_error_code_t sai_transmit_dma_double_buffer(SAI_HandleTypeDef *hsai, uint8_t *buffer1, uint8_t *buffer2, uint16_t buffer_size)
{
    manga_error_code_t ret = MAGNA_OK;

    if((buffer1 == NULL) || (buffer2 == NULL)) {
        ret = MAGNA_INVALID_ARGUMENT;
    } else if(buffer_size == 0) {
        ret = MAGNA_INVALID_ARGUMENT;
    } else if(hsai->State == HAL_SAI_STATE_READY) {
        /* Lock HW */
        if (HAL_LOCKED == hsai->Lock) {
            ret = MAGNA_HAL_BUSY;
        } else {
            hsai->Lock = HAL_LOCKED;

            hsai->ErrorCode = HAL_SAI_ERROR_NONE;
            hsai->State = HAL_SAI_STATE_BUSY_TX;

            /* Setup callbacks */
            hsai->hdmatx->XferCpltCallback = sai_buffer_1_complete_callback;
            hsai->hdmatx->XferM1CpltCallback = sai_buffer_2_complete_callback;
            //hsai->hdmatx->XferErrorCallback = SAI_DMAError;

            /* Setup DMA */
            if(HAL_DMAEx_MultiBufferStart_IT(hsai->hdmatx, (uint32_t)buffer1, (uint32_t)&hsai->Instance->DR, (uint32_t)buffer2, buffer_size) != HAL_OK) {
                hsai->Lock = HAL_UNLOCKED;
                ret = MAGNA_HAL_ERROR;
            }

            if (MAGNA_OK == ret) {
                /* Check If SAI is enabled, enable if not. */
                if((hsai->Instance->CR1 & SAI_xCR1_SAIEN) == RESET)
                {
                    hsai->Instance->CR1 |= SAI_xCR1_SAIEN;
                }

                /* Enable error handling interrupts */
                if((hsai->Init.AudioMode == SAI_MODESLAVE_RX) || (hsai->Init.AudioMode == SAI_MODESLAVE_TX)) {
                    /* Slave interrupts */
                    hsai->Instance->IMR |= SAI_IT_AFSDET | SAI_IT_LFSDET;
                } else {
                  /* Master interrupts */
                    hsai->Instance->IMR |= SAI_IT_WCKCFG;
                }

                /* Enable SAI Rx DMA Request */
                hsai->Instance->CR1 |= SAI_xCR1_DMAEN;

                /* Process Unlocked */
                hsai->Lock = HAL_UNLOCKED;
            }
        }

        ret = MAGNA_OK;
    } else {
        /* HAL BUSY */
        ret = MAGNA_HAL_BUSY;
    }
    return ret;
}


void start_codecs(void)
{
    sai_receive_dma_double_buffer(&hsai_BlockB1, (uint8_t * )audio_Input_buffer_1[0], (uint8_t * )audio_Input_buffer_1[1], OUTPUT_BUFFER_SIZE);
    //HAL_SAI_Receive_DMA(&hsai_BlockA2, (uint8_t * )audio_Input_buffer_2, OUTPUT_BUFFER_SIZE);

    /*HAL_SAI_Transmit_DMA(&hsai_BlockB1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);
    HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);*/

    //sai_transmit_dma_double_bufer(&hsai_BlockB1, (uint8_t * )audio_output_buffer[0], (uint8_t * )audio_output_buffer[1], OUTPUT_BUFFER_SIZE);
    sai_transmit_dma_double_buffer(&hsai_BlockA1, (uint8_t * )audio_output_buffer[0], (uint8_t * )audio_output_buffer[1], OUTPUT_BUFFER_SIZE);
}


void sai_buffer_1_complete_callback(SAI_HandleTypeDef *hsai) {
    (void)hsai;

    /*HAL_SAI_Receive_DMA(&hsai_BlockB2, (uint8_t * )audio_Input_buffer_1, OUTPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&hsai_BlockA2, (uint8_t * )audio_Input_buffer_2, OUTPUT_BUFFER_SIZE);*/

    /*HAL_SAI_Transmit_DMA(&hsai_BlockB1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);
    HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);*/
    //memcpy(audio_output_buffer[buffer_sel], audio_Input_buffer_1, OUTPUT_BUFFER_SIZE);

    //rx_buffer_info_audio.data = (uint8_t *)intermediate_buffer[int_read_cnt];
    //rx_buffer_info_audio.length = OUTPUT_BUFFER_SIZE*4;

    //queue_add(&audio_interface_queue_buffer, &rx_buffer_info_audio);

    buffer_read_++;
    memcpy(audio_output_buffer[0], &audio_Input_buffer_1[0], sizeof(audio_Input_buffer_1[0]));
}

void sai_buffer_2_complete_callback(SAI_HandleTypeDef *hsai) {
    (void)hsai;

    /*HAL_SAI_Receive_DMA(&hsai_BlockB2, (uint8_t * )audio_Input_buffer_1, OUTPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&hsai_BlockA2, (uint8_t * )audio_Input_buffer_2, OUTPUT_BUFFER_SIZE);*/

    /*HAL_SAI_Transmit_DMA(&hsai_BlockB1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);
    HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t * )audio_output_buffer[buffer_sel], OUTPUT_BUFFER_SIZE);*/
    //memcpy(audio_output_buffer[buffer_sel], audio_Input_buffer_1, OUTPUT_BUFFER_SIZE);

    //rx_buffer_info_audio.data = (uint8_t *)intermediate_buffer[int_read_cnt];
    //rx_buffer_info_audio.length = OUTPUT_BUFFER_SIZE*4;

    //queue_add(&audio_interface_queue_buffer, &rx_buffer_info_audio);

    buffer_read_++;
    memcpy(audio_output_buffer[1], &audio_Input_buffer_1[1], sizeof(audio_Input_buffer_1[1]));
}

uint32_t some_var = 0;

void audio_interface_queue_buffer(void *received_buffer_info)
{
    if (received_buffer_info != NULL) {
        struct rx_buffer_info_t *received_buffer_info_int = received_buffer_info;
        uint32_t i = 0;
        for(uint32_t j = 0; j < received_buffer_info_int->length; j += 6 ) {
            audio_output_buffer[buffer_sel][i+0] = ((uint32_t)received_buffer_info_int->data[j+2] << 16)
                    + ((uint32_t)received_buffer_info_int->data[j+1] << 8) + received_buffer_info_int->data[j];
            audio_output_buffer[buffer_sel][i+1] = ((uint32_t)received_buffer_info_int->data[j+5] << 16)
                    + ((uint32_t)received_buffer_info_int->data[j+1] << 4) + received_buffer_info_int->data[j + 3];
            i+=2;
        }
    }

    some_var ++;
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai) {
    (void) hsai;

    //memcpy(audio_output_buffer[buffer_sel], &audio_Input_buffer_1[0], sizeof(audio_Input_buffer_1[0]) * OUTPUT_BUFFER_SIZE);
    int_write_cnt = (int_write_cnt + 1) % INT_BUFF_SIZE;
    //audio_interface_queue_buffer

}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai) {
    (void) hsai;

    //memcpy(audio_output_buffer[buffer_sel], &audio_Input_buffer_1[OUTPUT_BUFFER_SIZE], sizeof(audio_Input_buffer_1[0]) * OUTPUT_BUFFER_SIZE);
    int_write_cnt = (int_write_cnt + 1) % INT_BUFF_SIZE;
    //audio_interface_queue_buffer

}
