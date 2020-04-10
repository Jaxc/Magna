/*
 * CS43L22.c
 *
 *  Created on: Apr 2, 2020
 *      Author: jaxc
 */

#ifdef CODEC_CS43L22

#include "CS43L22.h"
#include "i2c.h"
#include "gpio.h"

#define CODEC_ADDRESS CS42L2_ADDR_1

const struct device_registers CS43L22_regs[] = {
    {0x00, 0x99},
    {0x47, 0x80},
    {0x32, 0x01},
    {0x32, 0x00},
    {0x00, 0x00},
    {CS42L22_REG_POWER_CTL_1, 0x01},
    {CS42L22_REG_POWER_CTL_2, 0xAF},
    {CS42L22_REG_CLOCKING_CTL, 0x80},
    {CS42L22_REG_INTERFACE_CTL_1, 0x04},
    {CS42L22_REG_INTERFACE_CTL_2, 0x00},
    {CS42L22_REG_PASS_SELECT_A, 0x00},
    {CS42L22_REG_PASS_SELECT_B, 0x00},
    {CS42L22_REG_ANALOG_SZ_SR, 0x00},
    {CS42L22_REG_PASS_GANG_CTL, 0x00},
    {CS42L22_REG_PLAYBACK_CTL_1, 0x70},
    {CS42L22_REG_MISC_CTL, 0x00},
    {CS42L22_REG_PLAYBACK_CTL_2, 0x00},
    {CS42L22_REG_PCM_A_VOLUME, 0x00},
    {CS42L22_REG_PCM_B_VOLUME, 0x00},
    {CS42L22_REG_POWER_CTL_1, 0x9E},
    {CS42L22_REG_CLOCK_OVERFLOW, 0x00},

};


void init_codec (void) {
    uint8_t data = 0x00;
    HAL_StatusTypeDef status = HAL_OK;

    HAL_GPIO_WritePin(CODEC_NRST_GPIO_Port,CODEC_NRST_Pin, GPIO_PIN_SET);

    for (uint8_t i = 0; i < sizeof(CS43L22_regs)/sizeof(CS43L22_regs[0]); i++) {
        data = CS43L22_regs[i].data;
        status = HAL_I2C_Mem_Write(&hi2c2, CODEC_ADDRESS, CS43L22_regs[i].addr, 0x01, &data, 0x01, 1000);
        if (HAL_OK != status) {
            Error_Handler();
        }
    }

    if (0 != data) {
        Error_Handler();
    }
}

#endif /* CODEC_CS43L22 */
