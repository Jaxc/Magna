#include "tx_api.h"
#include "main.h"
#include "i2s.h"
#include "sai.h"


#define SAMPLES_PER_BUFFER      (64u)
#define N_AUDIO_CHANNELS        (2u)
#define INPUT_BYTES_PER_SAMPLE  (2u)
#define OUTPUT_BYTES_PER_SAMPLE (2u)
#define INPUT_BUFFER_SIZE       (N_AUDIO_CHANNELS*INPUT_BYTES_PER_SAMPLE*SAMPLES_PER_BUFFER)
#define OUTPUT_BUFFER_SIZE      (N_AUDIO_CHANNELS*OUTPUT_BYTES_PER_SAMPLE*SAMPLES_PER_BUFFER)

uint8_t channel_1_input_buffer[INPUT_BUFFER_SIZE];
uint8_t channel_2_input_buffer[INPUT_BUFFER_SIZE];
uint8_t channel_3_input_buffer[INPUT_BUFFER_SIZE];
uint8_t channel_4_input_buffer[INPUT_BUFFER_SIZE];

uint16_t master_output_buffer[OUTPUT_BUFFER_SIZE];
uint16_t cue_output_buffer[OUTPUT_BUFFER_SIZE];

static void init_audio (void);
static void start_i2s(void);


VOID audio_handler(ULONG initial_input) {

    init_audio();

    while(1) {
        tx_thread_sleep(1);
    }
}




static void init_audio (void) {

    for (uint16_t i = 0; i < OUTPUT_BUFFER_SIZE; i++) {
        master_output_buffer[i] = i;
        cue_output_buffer[i] = i;
    }

    start_i2s();
}

static void start_i2s(void) {
    HAL_SAI_Receive_DMA(&hsai_BlockB1,channel_2_input_buffer, INPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&hsai_BlockA2,channel_3_input_buffer, INPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&hsai_BlockB2,channel_4_input_buffer, INPUT_BUFFER_SIZE);

    HAL_I2S_Transmit_DMA(&hi2s2,master_output_buffer,OUTPUT_BUFFER_SIZE);
    HAL_I2S_Transmit_DMA(&hi2s3,master_output_buffer,OUTPUT_BUFFER_SIZE);

    /* Channel 1 is initialzed last as it is the one driving the clocks. This should
     * lead to all channels being synchonized. */
    HAL_SAI_Receive_DMA(&hsai_BlockA1,channel_1_input_buffer, INPUT_BUFFER_SIZE);
}