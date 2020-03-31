
#ifndef USB_MAGNA_H_
#define USB_MAGNA_H_

#include <stdint.h>

typedef struct {
    /* Up to USB_MAX_NUM_OF_BUFFERS rotating buffers per interface */
    uint8_t *audio_rx_1_buffer;
    uint8_t *audio_rx_2_buffer;
    uint8_t *audio_tx_1_buffer;
    uint8_t *audio_tx_2_buffer;
    uint16_t audio_rx_1_size;
    uint16_t audio_rx_2_size;
    uint16_t audio_tx_1_size;
    uint16_t audio_tx_2_size;
    /* User data to be passed through the callbacks */
    void *midi_user;
    void *cdc_user;
    /* Transmission Callbacks */
    void (* audio_rx_1_complete)(uint8_t *, uint16_t, void *);
    void (* audio_rx_2_complete)(uint8_t *, uint16_t, void *);
    void (* audio_tx_1_complete)(void *);
    void (* audio_tx_2_complete)(void *);
} usb_magna_t;

int usb_magna_is_configured(void);
int usb_midi_transmit(uint8_t *data, uint16_t length);
int usb_cdc_transmit(uint8_t *data, uint16_t length);

int usb_magna_init(usb_magna_t *usb_magna);
int usb_magna_deinit(void);

#endif /* USB_MAGNA_H_ */
