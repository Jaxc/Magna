
#include "usb_magna.h"
#include "usbd_magna_desc.h"
#include "usbd_internal.h"
#include "error_codes.h"
#include "stm32f7xx_hal.h"


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

static int usb_transmit(uint8_t epnum, uint8_t *data, uint16_t length)
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

    __enable_irq();

    return ret;
}

int usbd_magna_class_init(usbd_context_t *ctx, uint8_t cfgidx)
{
	(void)cfgidx;
    int ret = 0;

    /* Open Endpoints */
    ret = usbd_ep_open(ctx, USBD_EP_CDC_TX,
                       USBD_EP_BULK_TYPE, USBD_BULK_PACKET_SIZE);
    if (ret)
    {
        goto error;
    }

    ret = usbd_ep_open(ctx, USBD_EP_CDC_RX,
                       USBD_EP_BULK_TYPE, USBD_BULK_PACKET_SIZE);
    if (ret)
    {
        goto error;
    }

    ret = usbd_ep_open(ctx, USBD_EP_CDC_CMD,
                       USBD_EP_INTR_TYPE, USBD_INT_PACKET_SIZE);
    if (ret)
    {
        goto error;
    }

    if ((ctx != NULL) && (magna != NULL))
    {
        ctx->class_data = (void *)magna;

        usbd_ep_receive(ctx, USBD_EP_CDC_RX, magna->cdc_rx_buffer, magna->cdc_rx_size);
    }
    else
    {
        ret = MAGNA_FAILED;
    }

error:

    return ret;
}

int usbd_magna_class_deinit(usbd_context_t *ctx, uint8_t cfgidx)
{
	(void)cfgidx;
    int ret = 0;

    ret = usbd_ep_close(ctx, USBD_EP_CDC_TX);
    if (ret)
    {
        goto error;
    }

    ret = usbd_ep_close(ctx, USBD_EP_CDC_RX);
    if (ret)
    {
        goto error;
    }

    ret = usbd_ep_close(ctx, USBD_EP_CDC_CMD);
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
    uint8_t ifalt = 0;

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
            usbd_ctrl_transmit(ctx, &ifalt, 1);
        }
        break;
    default:
        break;
    }

    return MAGNA_OK;
}

void usbd_cdc_tx(usbd_context_t *ctx)
{
    usb_magna_t *mag = (usb_magna_t *)ctx->class_data;
    tx_busy = 0;

    if (mag)
    {
        if (mag->cdc_tx_complete)
        {
            mag->cdc_tx_complete(mag->cdc_user);
        }
    }
}

void usbd_cdc_rx(usbd_context_t *ctx, uint16_t length)
{
    usb_magna_t *mag = (usb_magna_t *)ctx->class_data;
    if (mag)
    {
        if (mag->cdc_rx_complete)
        {
            mag->cdc_rx_complete(mag->cdc_rx_buffer, length, mag->cdc_user);
        }

        usbd_ep_receive(ctx, USBD_EP_CDC_RX, mag->cdc_rx_buffer, mag->cdc_rx_size);
    }
}

int usb_cdc_transmit(uint8_t *data, uint16_t length)
{
    //__disable_irq();
    return usb_transmit(USBD_EP_CDC_TX, data, length);
    //__enable_irq();
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
    if ((usb_magna->cdc_rx_buffer == NULL) ||
        (usb_magna->cdc_rx_size == 0))
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
