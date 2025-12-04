#include <stdbool.h>
#include "adc.h"

void montor_adc_callback(bool complete);
void io_adc_callback(bool complete);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc == &hadc1) {
        montor_adc_callback(true);
    } else if (hadc == &hadc2) {
        io_adc_callback(true);
    }
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc == &hadc1) {
        montor_adc_callback(false);
    } else if (hadc == &hadc2) {
        io_adc_callback(false);
    }
}