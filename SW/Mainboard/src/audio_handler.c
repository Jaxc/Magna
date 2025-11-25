#include <stdbool.h>
#include <stdio.h>
#include "tx_api.h"
#include "main.h"
#include "i2s.h"
#include "sai.h"
#include "tim.h"
#include "SEGGER_RTT.h"
#include "debug.h"


#define SAMPLES_PER_BUFFER      (256u)
#define SAMPLES_PER_DMA_BUFFER  (2u * SAMPLES_PER_BUFFER)
#define N_AUDIO_CHANNELS        (2u)
#define INPUT_BUFFER_SIZE       (N_AUDIO_CHANNELS*SAMPLES_PER_DMA_BUFFER)
#define OUTPUT_BUFFER_SIZE      (N_AUDIO_CHANNELS*SAMPLES_PER_DMA_BUFFER)

#define master_i2s              (hi2s2)
#define cue_i2s                 (hi2s3)

#define channel1_i2s              (hsai_BlockA1)
#define channel2_i2s              (hsai_BlockB1)
#define channel3_i2s              (hsai_BlockA2)
#define channel4_i2s              (hsai_BlockB2)

#define timeout_timer             (htim14)

#define COUNTER_FREQ              (108000000u)
#define AUDIO_FREQ                (48000u)

#define WAIT_INTERRUPT_TIMEOUT    (uint32_t)(1.5f*108000000u / 48000u)

#define AUDIO_SEMAPHORE_TIMEOUT   (uint32_t)(1.5f* SAMPLES_PER_BUFFER/TX_TIMER_TICKS_PER_SECOND)


/* Struct to keep track of which part of the DMA transfer has been processed
 * and which is pending.  */
typedef struct audio_dma_state {
    bool buf_1;
    bool buf_2;
} audio_dma_state_t;

struct audio_buffer_dma_states {
    audio_dma_state_t channel_1;
    audio_dma_state_t channel_2;
    audio_dma_state_t channel_3;
    audio_dma_state_t channel_4;
    audio_dma_state_t cue_out;
    audio_dma_state_t mst_out;
};

enum buffer_enum {
    buf_1 = 0,
    buf_2
};

enum buffer_enum active_buffer = buf_2;

struct audio_buffer_dma_states dma_states;

uint32_t channel_1_input_buffer[INPUT_BUFFER_SIZE];
uint32_t channel_2_input_buffer[INPUT_BUFFER_SIZE];
uint32_t channel_3_input_buffer[INPUT_BUFFER_SIZE];
uint32_t channel_4_input_buffer[INPUT_BUFFER_SIZE];

uint32_t master_output_buffer[OUTPUT_BUFFER_SIZE];
uint32_t cue_output_buffer[OUTPUT_BUFFER_SIZE];

static void init_audio (void);
static void start_i2s(void);
bool check_dma_completion(void);

char diagbuffer[100];

extern TX_SEMAPHORE semaphore_audio_dma;

volatile uint32_t n_dma_completion,n_cue_half,n_cue_compl, n_master_half, n_master_complete = 0;

VOID audio_handler(ULONG initial_input) {

    init_audio();

    while(1) {
        uint32_t semaphore_status = tx_semaphore_get(&semaphore_audio_dma, TX_WAIT_FOREVER/*AUDIO_SEMAPHORE_TIMEOUT*/);
        if (TX_SUCCESS != semaphore_status) {
            log_fatal(__LINE__,__FILE__);
        }
        /* Data is available, do stuff!!!! */

        /* for now, sum outputs and put in master, put sine in cue*/
        for (uint16_t i = 0; i < SAMPLES_PER_BUFFER; i++) {


            log_info(__LINE__,__FILE__);
            log_info(__LINE__,__FILE__);
        }

        if (active_buffer == buf_1) {

            active_buffer = buf_2;
        } else {
            active_buffer = buf_1;
        }
    }
}

#if 0
void check_dma_timeout (void) {
    static uint8_t error_cnt = 0;
    /* DMA still ongoing, check if one channel has stalled */
    if ((dma_states.channel_1.buf_1 && dma_states.channel_1.buf_2) ||
        (dma_states.channel_2.buf_1 && dma_states.channel_2.buf_2) ||
        (dma_states.channel_3.buf_1 && dma_states.channel_3.buf_2) ||
        (dma_states.channel_4.buf_1 && dma_states.channel_4.buf_2) ||
        (dma_states.cue_out.buf_1 && dma_states.cue_out.buf_2) ||
        (dma_states.mst_out.buf_1 && dma_states.mst_out.buf_2)) {
        /* Something has gone bad */
        if (error_cnt > 0) {
            log_fatal(__LINE__,__FILE__);
        } else {
            error_cnt++;
        }
    } else {
        error_cnt = 0;
    }
}


bool check_dma_completion(void){
    tx_interrupt_control(TX_INT_DISABLE);
    n_dma_completion++;
    bool ret = false;
    if (active_buffer == buf_1) {
        if (dma_states.channel_1.buf_2 == true &&
            dma_states.channel_2.buf_2 == true &&
            dma_states.channel_3.buf_2 == true &&
            dma_states.channel_4.buf_2 == true &&
            dma_states.cue_out.buf_2 == true &&
            dma_states.mst_out.buf_2 == true) {
            /* DMA transfer completed successfully */
            ret = true;

            /* Reset buffers to ack transmission */
            dma_states.channel_1.buf_2 = false;
            dma_states.channel_2.buf_2 = false;
            dma_states.channel_3.buf_2 = false;
            dma_states.channel_4.buf_2 = false;
            dma_states.cue_out.buf_2 = false;
            dma_states.mst_out.buf_2 = false;

            active_buffer = buf_2;
        } else {
            check_dma_timeout();
        }
    } else if (active_buffer == buf_2) {
        if (dma_states.channel_1.buf_1 == true &&
            dma_states.channel_2.buf_1 == true &&
            dma_states.channel_3.buf_1 == true &&
            dma_states.channel_4.buf_1 == true &&
            dma_states.cue_out.buf_1 == true &&
            dma_states.mst_out.buf_1 == true) {
            /* DMA transfer completed successfully */
            ret = true;

            /* Reset buffers to ack transmission */
            dma_states.channel_1.buf_1 = false;
            dma_states.channel_2.buf_1 = false;
            dma_states.channel_3.buf_1 = false;
            dma_states.channel_4.buf_1 = false;
            dma_states.cue_out.buf_1 = false;
            dma_states.mst_out.buf_1 = false;

            active_buffer = buf_1;
        } else {
            check_dma_timeout();
        }

    } else {
        log_fatal(__LINE__,__FILE__);
    }

    tx_interrupt_control(TX_INT_ENABLE);
    return ret;
}
#endif

inline uint32_t pack_u32_to_u16(uint32_t in)
{
    uint32_t out = ((in & (uint32_t)0xFFFF0000) >> 16) | ((in & (uint32_t)0x0000FFFF) << 16);
    return out;
}


static void init_audio (void) {
    memset(&dma_states,0,sizeof(dma_states));

    for (uint16_t i = 0; i < OUTPUT_BUFFER_SIZE; i++) {
        master_output_buffer[i] = pack_u32_to_u16(i%2 + 1);
        cue_output_buffer[i] = pack_u32_to_u16(i);
    }

    start_i2s();
}



static void start_i2s(void) {
    HAL_SAI_Receive_DMA(&channel2_i2s,(uint8_t *) channel_2_input_buffer, INPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&channel3_i2s,(uint8_t *) channel_3_input_buffer, INPUT_BUFFER_SIZE);
    HAL_SAI_Receive_DMA(&channel4_i2s,(uint8_t *) channel_4_input_buffer, INPUT_BUFFER_SIZE);

    HAL_I2S_Transmit_DMA(&master_i2s, (uint16_t *) master_output_buffer, OUTPUT_BUFFER_SIZE);
    HAL_I2S_Transmit_DMA(&cue_i2s, (uint16_t *) cue_output_buffer, OUTPUT_BUFFER_SIZE);

    /* Disable DMA interrupts for slave DMA streams
     * To reduce the number of interrupts only the master I2S DMA interrupts are needed. When
     * it triggers the interrupt status of the other DMAs are checked to ensure that they
     * completed successfully.
     *
     * Note: Only interrupts related to regular operation are disabled, error interruptes are
     * still active
     */

    __HAL_DMA_DISABLE_IT(channel2_i2s.hdmarx, DMA_IT_TC | DMA_IT_HT);
    __HAL_DMA_DISABLE_IT(channel3_i2s.hdmarx, DMA_IT_TC | DMA_IT_HT);
    __HAL_DMA_DISABLE_IT(channel4_i2s.hdmarx, DMA_IT_TC | DMA_IT_HT);

    __HAL_DMA_DISABLE_IT(master_i2s.hdmatx, DMA_IT_TC | DMA_IT_HT);
    __HAL_DMA_DISABLE_IT(cue_i2s.hdmatx, DMA_IT_TC | DMA_IT_HT);

    /* Channel 1 is initialzed last as it is the one driving the clocks. This should
     * lead to all channels being synchonized. */
    HAL_SAI_Receive_DMA(&channel1_i2s,(uint8_t *) channel_1_input_buffer, INPUT_BUFFER_SIZE);
}


void set_dma_timeout (void) {
    __HAL_TIM_SET_AUTORELOAD(&timeout_timer, WAIT_INTERRUPT_TIMEOUT);
    __HAL_TIM_SET_PRESCALER(&timeout_timer, 0);
    HAL_GPIO_WritePin(OE_output_ena_GPIO_Port, OE_output_ena_Pin, GPIO_PIN_SET);
    HAL_TIM_Base_Start_IT(&timeout_timer);
}

void validate_dma_completion (void) {
    if (active_buffer == buf_1) {
        /* As this happens as a reaction of SAI1A finishing there is no need to
         * check that this flag is set, but checking the other part is not
         * is needed to ensure it has not stalled.
         */

        //snprintf(diagbuffer,100, "SAI_HLFCMPL_CB 0x%#08lx 0x%#08lx 0x%#08lx 0x%#08lx\r\n", __HAL_DMA_GET_FLAG(channel2_i2s.hdmarx, DMA_FLAG_TCIF0_4 | DMA_FLAG_HTIF0_4), __HAL_DMA_GET_FLAG(channel3_i2s.hdmarx, DMA_FLAG_TCIF2_6 | DMA_FLAG_HTIF2_6), __HAL_DMA_GET_FLAG(channel4_i2s.hdmarx, DMA_FLAG_TCIF2_6 | DMA_FLAG_HTIF2_6), __HAL_DMA_GET_FLAG(master_i2s.hdmatx, DMA_FLAG_TCIF0_4 | DMA_FLAG_HTIF0_4));
        //SEGGER_RTT_WriteString (0,diagbuffer);

        if ( 0 == __HAL_DMA_GET_FLAG(channel1_i2s.hdmarx, DMA_FLAG_HTIF1_5)) {
            dma_states.channel_1.buf_2 = true;
        } else {log_fatal(__LINE__,__FILE__);}

        if ((DMA_FLAG_TCIF0_4 ==__HAL_DMA_GET_FLAG(channel2_i2s.hdmarx, DMA_FLAG_TCIF0_4 | DMA_FLAG_HTIF0_4))) {
            dma_states.channel_2.buf_1 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_TCIF2_6 == __HAL_DMA_GET_FLAG(channel3_i2s.hdmarx, DMA_FLAG_TCIF2_6 | DMA_FLAG_HTIF2_6))) {
            dma_states.channel_3.buf_1 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_TCIF2_6 == __HAL_DMA_GET_FLAG(channel4_i2s.hdmarx, DMA_FLAG_TCIF2_6 | DMA_FLAG_HTIF2_6))) {
            dma_states.channel_4.buf_1 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_TCIF0_4 ==__HAL_DMA_GET_FLAG(master_i2s.hdmatx, DMA_FLAG_TCIF0_4 | DMA_FLAG_HTIF0_4))) {
            dma_states.mst_out.buf_1 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_TCIF1_5 == __HAL_DMA_GET_FLAG(cue_i2s.hdmatx, DMA_FLAG_TCIF1_5 | DMA_FLAG_HTIF1_5))) {
            dma_states.cue_out.buf_1 = true;
        } else {log_fatal(__LINE__,__FILE__);}

        DMA2->LIFCR = DMA_FLAG_TCIF0_4 | DMA_FLAG_TCIF2_6;
        DMA2->HIFCR = DMA_FLAG_TCIF2_6;
        DMA1->HIFCR = DMA_FLAG_TCIF0_4 | DMA_FLAG_TCIF1_5;
        //snprintf(diagbuffer,100, "%#08lx %#08lx %#08lx %#08lx\r\n", DMA1->LISR, DMA1->HISR, DMA2->LISR, DMA2->HISR);
        //SEGGER_RTT_WriteString (0,diagbuffer);

    } else if (active_buffer == buf_2) {
        if ( 0 == __HAL_DMA_GET_FLAG(channel1_i2s.hdmarx, DMA_FLAG_TCIF1_5)) {
            dma_states.channel_1.buf_2 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_HTIF0_4 == __HAL_DMA_GET_FLAG(channel2_i2s.hdmarx, DMA_FLAG_TCIF0_4 | DMA_FLAG_HTIF0_4))) {
            dma_states.channel_2.buf_2 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_HTIF2_6 == __HAL_DMA_GET_FLAG(channel3_i2s.hdmarx, DMA_FLAG_TCIF2_6 | DMA_FLAG_HTIF2_6))) {
            dma_states.channel_3.buf_2 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_HTIF2_6 == __HAL_DMA_GET_FLAG(channel4_i2s.hdmarx, DMA_FLAG_TCIF2_6 | DMA_FLAG_HTIF2_6))) {
            dma_states.channel_4.buf_2 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_HTIF0_4 == __HAL_DMA_GET_FLAG(master_i2s.hdmatx, DMA_FLAG_TCIF0_4 | DMA_FLAG_HTIF0_4))) {
            dma_states.mst_out.buf_2 = true;
        } else {log_fatal(__LINE__,__FILE__);}
        if ((DMA_FLAG_HTIF1_5 == __HAL_DMA_GET_FLAG(cue_i2s.hdmatx, DMA_FLAG_TCIF1_5 | DMA_FLAG_HTIF1_5))) {
            dma_states.cue_out.buf_2 = true;
        } else {log_fatal(__LINE__,__FILE__);}

        /* This code will only be reached if all interrupts are deemed OK */
        /* Reset interrupt registers. */
        DMA2->LIFCR = DMA_FLAG_HTIF0_4 | DMA_FLAG_HTIF2_6;
        DMA2->HIFCR = DMA_FLAG_HTIF2_6;
        DMA1->HIFCR = DMA_FLAG_HTIF0_4 | DMA_FLAG_HTIF1_5;
    }
    uint32_t ret = tx_semaphore_ceiling_put(&semaphore_audio_dma, 1);
    if (ret != TX_SUCCESS) {
        log_fatal(__LINE__,__FILE__);
    }
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    log_fatal(__LINE__,__FILE__);
}


void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    log_fatal(__LINE__,__FILE__);
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai->Instance == channel1_i2s.Instance) {
        set_dma_timeout();
        //snprintf(diagbuffer,100, "SAI_CMPL_CB %#08lx %#08lx %#08lx %#08lx\r\n", DMA1->LISR, DMA1->HISR, DMA2->LISR, DMA2->HISR);
        //SEGGER_RTT_WriteString (0,diagbuffer);
    } else {
        log_fatal(__LINE__,__FILE__);
    }
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
    if (hsai->Instance == channel1_i2s.Instance) {
        set_dma_timeout();
        //snprintf(diagbuffer,100, "SAI_HLFCMPL_CB %#08lx %#08lx %#08lx %#08lx\r\n", DMA1->LISR, DMA1->HISR, DMA2->LISR, DMA2->HISR);
        //SEGGER_RTT_WriteString (0,diagbuffer);
    } else {
        log_fatal(__LINE__,__FILE__);
    }
}