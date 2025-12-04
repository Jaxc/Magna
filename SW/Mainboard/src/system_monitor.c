#include <stdbool.h>
#include "tx_api.h"
#include "main.h"
#include "adc.h"
#include "debug.h"
#include "tim.h"


#define N_ADC_MONITORING_CHANNELS   (12u)
#define MONITOR_BUF_SIZE            (N_ADC_MONITORING_CHANNELS* 2u)
#define N_SAMPLES_PER_BUFFER        (4u)

#define ADC_RESOLUTION              (4096u)
#define VREF_INT_CAL_VALUE          ((float)*VREFINT_CAL_ADDR_CMSIS)
#define VREF_INT_CAL_VDDA           (3.3f)
#define MCU_TEMP_REF_25C            ((float) *TEMPSENSOR_CAL1_ADDR_CMSIS)


typedef uint16_t adc_sample_run[N_SAMPLES_PER_BUFFER];

typedef struct {
    adc_sample_run temperature;
    adc_sample_run vref_int;
    adc_sample_run usb_b_vbus;
} monitor_adc_data_t;


extern TIM_HandleTypeDef htim6;
extern TX_QUEUE monitor_data_ptr_queue;

void init_system_monitor(void);



uint16_t monitoring_data[MONITOR_BUF_SIZE];

VOID system_monitor(ULONG initial_input) {
    init_system_monitor();

    static volatile float mcu_vref_voltage = 0;
    static float mcu_temp = 0;

    while(1) {
        UINT queue_status;
        monitor_adc_data_t *adc_data = NULL;
        queue_status = tx_queue_receive(&monitor_data_ptr_queue, &adc_data, TX_WAIT_FOREVER);
        if (queue_status != TX_SUCCESS) {
            LOG_INFO;
        }

        uint16_t mcu_temp_value = 0;
        uint16_t mcu_vref_value = 0;
        uint16_t usb_b_vbus_value = 0;
        /* Average samples*/
        for(uint8_t i = 0; i < N_SAMPLES_PER_BUFFER; i++) {
            mcu_temp_value += adc_data->temperature[i];
            mcu_vref_value += adc_data->vref_int[i];
            usb_b_vbus_value += adc_data->usb_b_vbus[i];
        }

        mcu_vref_voltage =/*0.99 * mcu_vref_voltage + 0.01 *  */(4 * VREF_INT_CAL_VDDA * VREF_INT_CAL_VALUE / mcu_vref_value);

        /* convert to votlages, since 4 samples have been summed, it is effectively
         * a 14 bit value */
        float mcu_temp_measurement = ((float)mcu_vref_voltage * mcu_temp_value/(ADC_RESOLUTION * 4));
        mcu_temp = (mcu_temp_measurement - 0.76f)/ 0.0025 + 25;
        float usb_b_vbus_percentage = ((float) mcu_vref_voltage * usb_b_vbus_value/(ADC_RESOLUTION * 4));

        if (65.f <= mcu_temp) {
            LOG_INFO;
        }
/* There needs to be a switch to detect which 5v is used and report only if things are wrong
        if ((5.5 <= usb_b_vbus_percentage) | (4.5 >= usb_b_vbus_percentage)) {
            LOG_INFO;
        }
*/
    }
}


void init_system_monitor(void) {
    HAL_StatusTypeDef status;
    status = HAL_TIM_OC_Start(&htim5,HAL_TIM_ACTIVE_CHANNEL_1 );

    /* Start monitoring ADC */


    status = HAL_ADC_Start_DMA(&hadc1, (uint32_t *)monitoring_data, MONITOR_BUF_SIZE);
    if (HAL_OK != status) {
        log_fatal(__LINE__,__FILE__);
    }
}

void montor_adc_callback(bool complete){
    uint16_t *data_start;
    if (true == complete) {
        data_start = &monitoring_data[N_ADC_MONITORING_CHANNELS];
    } else {
        data_start = monitoring_data;
    }

    UINT queue_status = tx_queue_send(&monitor_data_ptr_queue, &data_start, TX_NO_WAIT);
    if (queue_status != TX_SUCCESS) {
        LOG_INFO;
    }
}