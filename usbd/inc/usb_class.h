
#ifndef USB_CLASS_H_
#define USB_CLASS_H_

#include <stdint.h>

typedef struct {
    /* Up to USB_MAX_NUM_OF_BUFFERS rotating buffers per interface */
    uint8_t *midi_rx_buffer;
    uint8_t *cdc_rx_buffer;
    uint16_t midi_rx_size;
    uint16_t cdc_rx_size;
    /* User data to be passed through the callbacks */
    void *midi_user;
    void *cdc_user;
    /* Transmission Callbacks */
    void (* midi_rx_complete)(uint8_t *, uint16_t, void *);
    void (* midi_tx_complete)(void *);
    void (* cdc_rx_complete)(uint8_t *, uint16_t, void *);
    void (* cdc_tx_complete)(void *);
} usb_device_t;

int usb_is_configured(void);
int usb_midi_transmit(uint8_t *data, uint16_t length);
int usb_cdc_transmit(uint8_t *data, uint16_t length);

int usb_device_init(usb_device_t *usb_device);
int usb_device_deinit(void);

#endif /* USB_CLASS_H_ */
