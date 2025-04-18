/*
 * WM8731.h
 *
 *  Created on: Apr 7, 2020
 *      Author: jaxc
 */

#ifndef AUDIO_INTERFACE_INC_WM8731_H_
#define AUDIO_INTERFACE_INC_WM8731_H_

#include <stdint.h>

/*Device address */
#define WM8731_ADDR_1 0x34
#define WM8731_ADDR_2 0x36

/* Device register addresses */
#define WM8731_REG_LEFT_LINE_IN    0x00 << 1
#define WM8731_REG_RIGHT_LINE_IN   0x01 << 1
#define WM8731_REG_LEFT_PHN_OUT    0x02 << 1
#define WM8731_REG_RIGHT_PHN_OUT   0x03 << 1
#define WM8731_REG_ANALOG_PATH     0x04 << 1
#define WM8731_REG_DIGITAL_PATH    0x05 << 1
#define WM8731_REG_POWER_DOWN      0x06 << 1
#define WM8731_REG_DIGITAL_IF      0x07 << 1
#define WM8731_REG_SAMPLING_CTRL   0x08 << 1
#define WM8731_REG_ACTIVE_CTRL     0x09 << 1
#define WM8731_REG_RESET           0x0F << 1

struct device_registers {
    uint8_t addr;
    uint16_t data;
};

#endif /* AUDIO_INTERFACE_INC_WM8731_H_ */
