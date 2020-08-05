/*
 * WM8731.c
 *
 *  Created on: Apr 7, 2020
 *      Author: jaxc
 */

#ifdef CODEC_WM8731

#include "WM8731.h"
#include "i2c.h"
#include "gpio.h"

#define CODEC_ADDRESS WM8731_ADDR_1

const struct device_registers WM8731_regs[] = {
    {WM8731_REG_LEFT_LINE_IN,  0x0017},
    {WM8731_REG_RIGHT_LINE_IN, 0x0017},
    {WM8731_REG_LEFT_PHN_OUT,  0x0079},
    {WM8731_REG_RIGHT_PHN_OUT, 0x0079},
    {WM8731_REG_ANALOG_PATH,   0x0014},
    {WM8731_REG_DIGITAL_PATH,  0x0000},
    {WM8731_REG_POWER_DOWN,    0x0000},
    {WM8731_REG_DIGITAL_IF,    0x000A},
    {WM8731_REG_SAMPLING_CTRL, 0x0000},
    {WM8731_REG_ACTIVE_CTRL,   0x0001},

};


void init_codec (void) {
    uint16_t data = 0x00;
    HAL_StatusTypeDef status = HAL_OK;

    //HAL_GPIO_WritePin(CODEC_NRST_GPIO_Port,CODEC_NRST_Pin, GPIO_PIN_SET);

    for (uint8_t i = 0; i < sizeof(WM8731_regs)/sizeof(WM8731_regs[0]); i++) {
        HAL_Delay(100);
        data = WM8731_regs[i].data;
        status = HAL_I2C_Mem_Write(&hi2c1, CODEC_ADDRESS, WM8731_regs[i].addr + ((data && 0xFF00) >> 8), 0x01, (uint8_t *)&data, 0x01, 1000);
        if (HAL_OK != status) {
            //Error_Handler();
        }
    }
}

#endif /* CODEC_WM8731 */
