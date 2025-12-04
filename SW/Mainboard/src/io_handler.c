#include <stdbool.h>
#include "tx_api.h"
#include "main.h"
#include "tim.h"
#include "debug.h"
#include "adc.h"

#define N_POTENTIOMETERS        (24u)
#define N_ADC_IO_CHANNELS       (12u)
#define N_IO_SAMPLES_PER_BUFFER (2u)
#define N_IO_CAPTURES           (N_POTENTIOMETERS * N_IO_SAMPLES_PER_BUFFER / N_ADC_IO_CHANNELS)
#define N_BUFFERS_BEFORE_INTTERRUPT (2u)

#define IO_CAPTURES_DMA_SIZE    (2 * N_BUFFERS_BEFORE_INTTERRUPT * N_ADC_IO_CHANNELS * N_IO_CAPTURES)


uint16_t io_analog_data[IO_CAPTURES_DMA_SIZE];


typedef uint16_t io_sample_run[N_IO_SAMPLES_PER_BUFFER];
typedef struct {
    io_sample_run pot0;
    io_sample_run pot1;
    io_sample_run pot2;
    io_sample_run pot3;
    io_sample_run pot4;
    io_sample_run pot5;
    io_sample_run pot6;
    io_sample_run pot7;
    io_sample_run pot8;
    io_sample_run pot9;
    io_sample_run pot10;
    io_sample_run pot11;
    io_sample_run pot12;
    io_sample_run pot13;
    io_sample_run pot14;
    io_sample_run pot15;
    io_sample_run pot16;
    io_sample_run pot17;
    io_sample_run pot18;
    io_sample_run pot19;
    io_sample_run pot20;
    io_sample_run pot21;
    io_sample_run pot22;
    io_sample_run pot23;
} io_adc_data_t;

typedef io_sample_run io_sample_grouping_t[N_POTENTIOMETERS];

extern TX_QUEUE io_adc_data_ptr_queue;

void init_io(void);

VOID io_handler(ULONG initial_input) {
    init_io();

    while(1) {

        UINT queue_status;
        io_sample_grouping_t *adc_data = NULL;
        queue_status = tx_queue_receive(&io_adc_data_ptr_queue, &adc_data, TX_WAIT_FOREVER);
        if (queue_status != TX_SUCCESS) {
            LOG_INFO;
        }
    }
}


void init_io (void) {
    HAL_StatusTypeDef status;

    status = HAL_ADC_Start_DMA(&hadc2, (uint32_t *)io_analog_data, IO_CAPTURES_DMA_SIZE);
    if (HAL_OK != status) {
        log_fatal(__LINE__,__FILE__);
    }
    /* Start Potentiometer select output */
    status = HAL_TIM_OC_Start(&htim4,HAL_TIM_ACTIVE_CHANNEL_1 | HAL_TIM_ACTIVE_CHANNEL_2);

    /* enable output */
    htim4.Instance->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;

    status = HAL_TIM_OC_Start(&htim3, HAL_TIM_ACTIVE_CHANNEL_2 | HAL_TIM_ACTIVE_CHANNEL_4);
    if (HAL_OK != status) {
        log_fatal(__LINE__,__FILE__);
    }
    /* enable output */
    htim3.Instance->CCER |= TIM_CCER_CC2E | TIM_CCER_CC4E;





}

void io_adc_callback(bool complete){
    uint16_t *data_start;
    if (true == complete) {
        data_start = &io_analog_data[N_ADC_IO_CHANNELS * N_IO_CAPTURES];
    } else {
        data_start = io_analog_data;
    }
    UINT queue_status = tx_queue_send(&io_adc_data_ptr_queue, &data_start, TX_NO_WAIT);
    if (queue_status != TX_SUCCESS) {
        LOG_INFO;
    }
}