#ifndef USB_IF_H__
#define USB_IF_H__

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifndef SWAPBYTE
#define SWAPBYTE(addr) (((uint16_t)(*((uint8_t *)(addr)))) + \
                       (((uint16_t)(*(((uint8_t *)(addr)) + 1))) << 8))
#endif

#ifndef LOBYTE
#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#endif

#ifndef HIBYTE
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >>8))
#endif

#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

#define USB_EP_TX(epnum)                (uint8_t)(0x80 | (0x7F & epnum))
#define USB_EP_RX(epnum)                (uint8_t)(0x00 | (0x7F & epnum))

#define USB_DEVICE_STATE_DEFAULT        1
#define USB_DEVICE_STATE_ADDRESSED      2
#define USB_DEVICE_STATE_CONFIGURED     3
#define USB_DEVICE_STATE_SUSPENDED      4

#define USB_REQUEST_TYPE_STANDARD       0x00
#define USB_REQUEST_TYPE_CLASS          0x01
#define USB_REQUEST_TYPE_VENDOR         0x02

#define USB_REQ_RECIPIENT_DEVICE        0x00
#define USB_REQ_RECIPIENT_INTERFACE     0x01
#define USB_REQ_RECIPIENT_ENDPOINT      0x02

#define USB_REQ_GET_STATUS              0x00
#define USB_REQ_CLEAR_FEATURE           0x01
#define USB_REQ_SET_FEATURE             0x03
#define USB_REQ_SET_ADDRESS             0x05
#define USB_REQ_GET_DESCRIPTOR          0x06
#define USB_REQ_SET_DESCRIPTOR          0x07
#define USB_REQ_GET_CONFIGURATION       0x08
#define USB_REQ_SET_CONFIGURATION       0x09
#define USB_REQ_GET_INTERFACE           0x0A
#define USB_REQ_SET_INTERFACE           0x0B
#define USB_REQ_SYNCH_FRAME             0x0C

#define USBD_EP_CTRL_TX                 0x80 //USB_EP_TX(0)
#define USBD_EP_CTRL_RX                 0x00 //USB_EP_RX(0)

#define USBD_EP_AUDIO_IN                0x83
#define USBD_EP_AUDIO_OUT               0x01
#define USBD_EP_AUDIO_FEEDBACK          0x82

#define USBD_CTRL_PACKET_SIZE           0x40
#define USBD_BULK_PACKET_SIZE           0x40
#define USBD_ISOC_PACKET_SIZE           0x126
#define USBD_FEEDBACK_SIZE              0x04
#define USBD_INT_PACKET_SIZE            0x08
#define USBD_FEEDBACK_PACKET_SIZE       0x08

#define USBD_EP_CTRL_TYPE               0
#define USBD_EP_ISOC_TYPE               1
#define USBD_EP_BULK_TYPE               2
#define USBD_EP_INTR_TYPE               3

#define EP_IS_TX(epnum)                 (0x7F & epnum)
#define EP_IS_RX(epnum)                 !(0x7F & epnum)

#define USBD_MAGNA_NUM_EP_IN          2 /* CTRL + IN */
#define USBD_MAGNA_NUM_EP_OUT         1 /* CTRL + OUT */

/*  EP0 State */
#define USBD_EP0_IDLE                   0
#define USBD_EP0_SETUP                  1
#define USBD_EP0_DATA_TX                2
#define USBD_EP0_DATA_RX                3
#define USBD_EP0_STATUS_TX              4
#define USBD_EP0_STATUS_RX              5
#define USBD_EP0_STALL                  6

typedef struct {
    uint16_t total_length;
    uint16_t rem_length;
    uint16_t max_packet_length;
} usbd_endpoint_t;

typedef struct {
    volatile uint32_t current_state;
    volatile uint32_t restore_state;
     uint32_t remote_wake_armed;
     uint8_t address;
     uint8_t current_config;
    void *dev_data;
    void *class_data;
    usbd_endpoint_t ep0_tx;
    usbd_endpoint_t ep0_rx;
    uint8_t ep0_state;
} usbd_context_t;

typedef struct {
    union
    {
        struct
        {
            uint8_t recipient : 5;
            uint8_t type : 2;
            uint8_t direction : 1;
        };

        uint8_t bits;
    } bmRequestType;

    uint8_t  bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} __attribute__((packed)) usb_setup_packet_t;

/*------------------------------------------------------------------------------*/
/*  USB HW interface functions                                                  */
/*------------------------------------------------------------------------------*/

int usbd_hw_init(usbd_context_t *ctx);
int usbd_hw_deinit(usbd_context_t *ctx);
int usbd_start(usbd_context_t *ctx);
int usbd_stop(usbd_context_t *ctx);
int usbd_ep_open(usbd_context_t *ctx, uint8_t ep_addr,
                 uint8_t ep_type, uint16_t ep_mps);
int usbd_ep_close(usbd_context_t *ctx, uint8_t ep_addr);
int usbd_ep_flush(usbd_context_t *ctx, uint8_t ep_addr);
int usbd_ep_stall(usbd_context_t *ctx, uint8_t ep_addr);
int usbd_ep_stall_clear(usbd_context_t *ctx, uint8_t ep_addr);
int usbd_ep_is_stalled(usbd_context_t *ctx, uint8_t ep_addr);
int usbd_set_address(usbd_context_t *ctx, uint8_t dev_addr);
uint16_t usbd_get_rx_data_len(usbd_context_t *ctx, uint8_t ep_addr);
void usbd_delay_ms(uint32_t delay_ms);

/*------------------------------------------------------------------------------*/
/*  USB Core interface functions                                            */
/*------------------------------------------------------------------------------*/

void usbd_setup_stage(usbd_context_t *ctx, usb_setup_packet_t *setup);
void usbd_data_rx_stage(usbd_context_t *ctx, uint8_t epnum,
                        uint8_t *xfer_buff, uint16_t xfer_count);
void usbd_data_tx_stage(usbd_context_t *ctx, uint8_t epnum, uint8_t *xfer_buf);
void usbd_start_of_frame(usbd_context_t *ctx);
void usbd_reset(usbd_context_t *ctx);
void usbd_suspend(usbd_context_t *ctx);
void usbd_resume(usbd_context_t *ctx);
void usbd_connect(usbd_context_t *ctx);
void usbd_disconnect(usbd_context_t *ctx);
void usbd_ctrl_transmit(usbd_context_t *ctx,
                        uint8_t *xfer_buff, uint16_t length);
void usbd_ctrl_receive(usbd_context_t *ctx,
                       uint8_t *xfer_buff, uint16_t length);

/*------------------------------------------------------------------------------*/
/*  Class interface functions                                                   */
/*------------------------------------------------------------------------------*/

usbd_context_t *usbd_get_context(void);

int usbd_is_ready(void);
int usbd_transmit(uint8_t epnum, uint8_t *xfer_buff, uint16_t length);

int usbd_ep_transmit(usbd_context_t *ctx, uint8_t ep_addr,
                     uint8_t *tx_buff, uint16_t size);
int usbd_ep_receive(usbd_context_t *ctx, uint8_t ep_addr,
                    uint8_t *rx_buff, uint16_t size);
int usbd_init(void);
int usbd_deinit(void);

int usbd_magna_class_init(usbd_context_t *ctx, uint8_t cfgidx);
int usbd_magna_setup_endpoints(usbd_context_t *ctx, usb_setup_packet_t *setup);
int usbd_magna_class_deinit(usbd_context_t *ctx, uint8_t cfgidx);
int usbd_magna_setup(usbd_context_t *ctx,
                       usb_setup_packet_t *setup);
void usbd_midi_tx(usbd_context_t *ctx);
void usbd_midi_rx(usbd_context_t *ctx, uint16_t length);
void usbd_cdc_tx(usbd_context_t *ctx);
void usbd_audio_rx(usbd_context_t *ctx, uint16_t length);
void usbd_cdc_rx(usbd_context_t *ctx, uint16_t length);

#endif /* USB_IF_H__ */
