
#include "usb_magna.h"
#include "usbd_magna_desc.h"
#include "usbd_internal.h"
#include "error_codes.h"
#include "stm32f7xx_hal.h"
#include "queue.h"


static struct {
    uint32_t dwBaudrate;
    uint8_t bStopBits;
    uint8_t bParityType;
    uint8_t bDataBits;
} __attribute__((packed)) cdc_line_coding = {
    .dwBaudrate = 9600,
    .bStopBits = 1,
    .bParityType = 0,
    .bDataBits = 8,
};

static uint8_t tx_busy = 0;
static usb_magna_t *magna = NULL;

#define BUFFERSIZE 200

uint8_t circular_counter = 0;
uint32_t usbd_internal_buffer[96*2 * 2] = {0};
uint32_t usbd_internal_buffer_cnt = 0;

struct rx_buffer_info_t {
    uint8_t *data;
    uint16_t length;
};

struct rx_buffer_info_t rx_buffer_info;


int usb_feedback_transmit(void);

/*static */ int usb_transmit(uint8_t epnum, uint8_t *data, uint16_t length)
{
    int ret = MAGNA_BUSY;

    if (tx_busy)
    {
        return ret;
    }

    ret = usbd_transmit(epnum, data, length);
    if (ret)
    {
        return ret;
    }

    tx_busy = 1;

    return ret;
}

int usbd_magna_class_init(usbd_context_t *ctx, uint8_t cfgidx)
{
	(void)cfgidx;
    int ret = 0;

    /* Open Endpoints */
    /*ret = usbd_ep_open(ctx, USBD_EP_AUDIO_IN,
                       USBD_EP_ISOC_TYPE, USBD_ISOC_PACKET_SIZE);
    if (ret)
    {
        goto error;
    }

    ret = usbd_ep_open(ctx, USBD_EP_AUDIO_FEEDBACK,
                       USBD_EP_ISOC_TYPE, USBD_FEEDBACK_PACKET_SIZE);
    if (ret)
    {
        goto error;
    }

    ret = usbd_ep_open(ctx, USBD_EP_AUDIO_OUT,
                       USBD_EP_ISOC_TYPE, USBD_ISOC_PACKET_SIZE);
    if (ret)
    {
        goto error;
    }*/

    if ((ctx != NULL) && (magna != NULL))
    {
        ctx->class_data = (void *)magna;

//        usbd_ep_receive(ctx, USBD_EP_AUDIO_OUT, magna->audio_rx_1_buffer, magna->audio_rx_1_size);
    }
    else
    {
        ret = MAGNA_FAILED;
    }

    return ret;
}

int usbd_magna_class_deinit(usbd_context_t *ctx, uint8_t cfgidx)
{
	(void)cfgidx;
    int ret = 0;

    ret = usbd_ep_close(ctx, USBD_EP_AUDIO_OUT);
    if (ret)
    {
        goto error;
    }


    ctx->class_data = NULL;

error:

    return ret;
}

int usbd_magna_setup(usbd_context_t *ctx,
                       usb_setup_packet_t *setup)
{
    static uint8_t ifalt[USBD_NUM_INTERFACES] = {0};
    int ret = MAGNA_OK;

    switch (setup->bmRequestType.type)
    {
    case USB_REQUEST_TYPE_CLASS:
        if (setup->wLength)
        {
            if ((setup->bmRequestType.direction) &&
                (setup->bRequest == CDC_GET_LINE_CODING))
            {
                usbd_ctrl_transmit(ctx, (uint8_t *)&cdc_line_coding,
                                   sizeof(cdc_line_coding));
            }
            else if (setup->bRequest == CDC_SET_LINE_CODING)
            {
                usbd_ctrl_receive(ctx, (uint8_t *)&cdc_line_coding,
                                  sizeof(cdc_line_coding));
            }
        }
        break;
    case USB_REQUEST_TYPE_STANDARD:
        if (setup->bRequest == USB_REQ_GET_INTERFACE)
        {
            usbd_ctrl_transmit(ctx, &ifalt[setup->wIndex], 1);

        } else if (setup->bRequest == USB_REQ_SET_INTERFACE) {
            if (ifalt[setup->wIndex] != setup->wValue) {
                usbd_magna_setup_endpoints(ctx, setup);
                ifalt[setup->wIndex] = setup->wValue;
            }

        } else {

        }
        break;
    default:
        break;
    }

    return ret;
}


uint32_t feedback_value = (96 << 14);

int usbd_magna_setup_endpoints(usbd_context_t *ctx,
                                usb_setup_packet_t *setup)
{
    int ret = MAGNA_OK;
    if (USBD_AUDIO_INTERFACE == setup->wIndex) {
        if (0 == setup->wValue) {
            ret = usbd_ep_close(ctx, USBD_EP_AUDIO_IN);

            /*if (!ret)
            {
                ret = usbd_ep_close(ctx, USBD_AUDIO_IN_CHN2);
            }*/
        } else {
            ret = usbd_ep_open(ctx, USBD_EP_AUDIO_IN,
                               USBD_EP_ISOC_TYPE, USBD_ISOC_PACKET_SIZE);
            /*if (!ret)
            {
                ret = usbd_ep_open(ctx, USBD_AUDIO_IN_CHN2,
                               USBD_EP_ISOC_TYPE, USBD_ISOC_PACKET_SIZE);
            }*/
        }
    } else if (USBD_AUDIO_INTERFACE2 == setup->wIndex) {
        if (0 == setup->wValue) {
            ret = usbd_ep_close(ctx, USBD_EP_AUDIO_OUT);

            if (!ret)
            {
                ret = usbd_ep_close(ctx, USBD_EP_AUDIO_FEEDBACK);
            }
        } else {
            ret = usbd_ep_open(ctx, USBD_EP_AUDIO_OUT,
                               USBD_EP_ISOC_TYPE, USBD_ISOC_PACKET_SIZE);


            if (!ret)
            {
                ret = usbd_ep_receive(ctx, USBD_EP_AUDIO_OUT, &magna->audio_rx_buffer[circular_counter], magna->audio_rx_size);
            }

            if (!ret)
            {
                ret = usbd_ep_open(ctx, USBD_EP_AUDIO_FEEDBACK,
                               USBD_EP_ISOC_TYPE, USBD_EP_AUDIO_FEEDBACK);
            }

            if (!ret)
            {
                ret = usbd_ep_transmit(ctx, USBD_EP_AUDIO_FEEDBACK,
                                   (uint8_t *)&feedback_value, USBD_EP_AUDIO_FEEDBACK);
            }
        }

    }
    return ret;
}

void usbd_cdc_tx(usbd_context_t *ctx)
{
    usb_magna_t *mag = (usb_magna_t *)ctx->class_data;
    tx_busy = 0;

    if (mag)
    {
       /* if (mag->cdc_tx_complete)
        {
            mag->cdc_tx_complete(mag->cdc_user);
        }*/
    }
}

void usbd_handle_rx_buffer(void *received_buffer_info)
{
    if (received_buffer_info != NULL) {
        struct rx_buffer_info_t *received_buffer_info_int = received_buffer_info;
        uint32_t i = 0;
        for(uint32_t j = 0; j < received_buffer_info_int->length; j += 6 ) {
            usbd_internal_buffer[i+0] = received_buffer_info_int->data[j]
                 +  (received_buffer_info_int->data[j+1] << 8) + (received_buffer_info_int->data[j+2] << 16);
            usbd_internal_buffer[i+1] = received_buffer_info_int->data[j+3]
                 +  (received_buffer_info_int->data[j+4] << 8) + (received_buffer_info_int->data[j+5] << 16);
            usbd_internal_buffer[i+2] = received_buffer_info_int->data[j]
                 +  (received_buffer_info_int->data[j+1] << 8) + (received_buffer_info_int->data[j+2] << 16);
            usbd_internal_buffer[i+3] = received_buffer_info_int->data[j+3]
                 +  (received_buffer_info_int->data[j+4] << 8) + (received_buffer_info_int->data[j+5] << 16);
            usbd_internal_buffer[i+4] = received_buffer_info_int->data[j]
                 +  (received_buffer_info_int->data[j+1] << 8) + (received_buffer_info_int->data[j+2] << 16);
            usbd_internal_buffer[i+5] = received_buffer_info_int->data[j+3]
                 +  (received_buffer_info_int->data[j+4] << 8) + (received_buffer_info_int->data[j+5] << 16);
            usbd_internal_buffer[i+6] = received_buffer_info_int->data[j]
                 +  (received_buffer_info_int->data[j+1] << 8) + (received_buffer_info_int->data[j+2] << 16);
            usbd_internal_buffer[i+7] = received_buffer_info_int->data[j+3]
                 +  (received_buffer_info_int->data[j+4] << 8) + (received_buffer_info_int->data[j+5] << 16);
            i+=8;
        }
    }

    usbd_internal_buffer_cnt ++;

}


void usbd_audio_rx(usbd_context_t *ctx, uint16_t length)
{

    usb_magna_t *mag = (usb_magna_t *)ctx->class_data;
    if (mag)
    {
        rx_buffer_info.data = &mag->audio_rx_buffer[circular_counter];
        rx_buffer_info.length = length;
        if(queue_add(&usbd_handle_rx_buffer, &rx_buffer_info) == MAGNA_OK) {
            if (circular_counter < 3) {
                circular_counter++;
            } else {
                circular_counter = 0;
            }
        }
        usbd_ep_receive(ctx, USBD_EP_AUDIO_OUT, &mag->audio_rx_buffer[circular_counter], mag->audio_rx_size);
    }

    usb_feedback_transmit();
}

void usbd_cdc_rx(usbd_context_t *ctx, uint16_t length)
{
    (void)length;
    usb_magna_t *mag = (usb_magna_t *)ctx->class_data;
    if (mag)
    {
        /*if (mag->cdc_rx_complete)
        {
            mag->cdc_rx_complete(mag->cdc_rx_buffer, length, mag->cdc_user);
        }

        usbd_ep_receive(ctx, USBD_EP_CDC_RX, mag->cdc_rx_buffer, mag->cdc_rx_size);*/
    }
}

int usb_feedback_transmit(void)
{
   uint32_t data;
   data = 96 << 14;
    return usb_transmit(USBD_EP_AUDIO_FEEDBACK, (uint8_t * )&data, 4);
}

int usb_cdc_transmit(uint8_t *data, uint16_t length)
{
    (void)data;
    (void)length;
    //__disable_irq();
    //return usb_transmit(USBD_EP_CDC_TX, data, length);
    //__enable_irq();
    return 0;
}

int usb_magna_init(usb_magna_t *usb_magna)
{
    int ret = MAGNA_OK;

    if (usb_magna == NULL)
    {
        ret = MAGNA_FAILED;
        goto error;
    }

    /* Check if we have valid buffers */
    if ((usb_magna->audio_rx_buffer == NULL) ||
        (usb_magna->audio_rx_size == 0))
    {
        ret = MAGNA_INVALID_ARGUMENT;
        goto error;
    } else if ((usb_magna->audio_tx_buffer == NULL) ||
            (usb_magna->audio_tx_size == 0))
    {
        ret = MAGNA_INVALID_ARGUMENT;
        goto error;
    }

    ret = usbd_init();
    if (ret)
    {
        goto error;
    }

    magna = usb_magna;

error:

    return ret;
}

int usb_magna_deinit(void)
{
    magna = NULL;

    return usbd_deinit();
}
