#include <stdbool.h>
#include "tx_api.h"
#include "main.h"
#include "tim.h"
#include "debug.h"
#include "adc.h"

#define N_ADC_IO_CHANNELS (12u)
#define N_IO_CAPTURES     (4u)


uint16_t io_analog_data[N_ADC_IO_CHANNELS*N_IO_CAPTURES];

void init_io(void);

VOID io_handler(ULONG initial_input) {
    init_io();

    while(1) {
        static uint32_t io_cnt = 0;

        tx_thread_sleep(10);

        io_cnt++;

    }
}


void init_io (void) {
    HAL_StatusTypeDef status;

    /* Start Potentiometer select output */
    status = HAL_TIM_OC_Start(&htim4,HAL_TIM_ACTIVE_CHANNEL_1 | HAL_TIM_ACTIVE_CHANNEL_2);
    if (HAL_OK != status) {
        log_fatal(__LINE__,__FILE__);
    }
    /* enable output */
    htim4.Instance->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
    status = HAL_ADC_Start_DMA(&hadc2, (uint32_t *)io_analog_data, sizeof(io_analog_data));

}

void io_adc_callback(bool complete){

}