
#include "usbd_internal.h"

#include "usbd_magna_desc.h"
#include "error_codes.h"
#include <stdio.h>

static usbd_context_t magna_ctx = { 0 };

static void usbd_ctrl_error(usbd_context_t *ctx)
{
    usbd_ep_stall(ctx, 0x00);
    usbd_ep_stall(ctx, 0x80);
}

static void usbd_ctrl_send_status(usbd_context_t *ctx)
{
    ctx->ep0_state = USBD_EP0_STATUS_TX;

    usbd_ep_transmit(ctx, 0, NULL, 0);
}

static void usbd_ctrl_recv_status(usbd_context_t *ctx)
{
    ctx->ep0_state = USBD_EP0_STATUS_RX;

    usbd_ep_receive(ctx, 0, NULL, 0);
}

static void usbd_get_descriptor(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    uint16_t length = 0;
    uint8_t *desc;

    switch (setup->wValue >> 8)
    {
    case USB_DEVICE_DESC_TYPE:
        desc = (uint8_t *)usbd_get_dev_desc(&length);
        break;
    case USB_CONFIG_DESC_TYPE:
        desc = (uint8_t *)usbd_get_cfg_desc(0, &length);
        break;
    case USB_STRING_DESC_TYPE:
        switch ((uint8_t)(setup->wValue))
        {
        case USBD_IDX_LANGID_STR:
            desc = (uint8_t *)usbd_get_langid_str(&length);
            break;
        case USBD_IDX_MFC_STR:
            desc = (uint8_t *)usbd_get_mfc_str(&length);
            break;
        case USBD_IDX_PRODUCT_STR:
            desc = (uint8_t *)usbd_get_prod_str(&length);
            break;
        case USBD_IDX_SERIAL_STR:
            desc = (uint8_t *)usbd_get_serial_str(&length);
            break;
        case USBD_IDX_CONFIG_STR:
            desc = (uint8_t *)usbd_get_cfg_str(&length);
            break;
        case USBD_IDX_CDC_IF_STR:
            desc = (uint8_t *)usbd_get_cdc_if_str(&length);
            break;
        default:
            usbd_ctrl_error(ctx);
            return;
        }
        break;
    case USB_DEVICE_QUALIFIER_DESC_TYPE:
    default:
        usbd_ctrl_error(ctx);
        return;
    }

    if ((length != 0) && (setup->wLength != 0))
    {
        length = MIN(length, setup->wLength);

        usbd_ctrl_transmit(ctx, desc, length);
    }
}

static void usbd_setup_address(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    if ((setup->wIndex == 0) && (setup->wLength == 0))
    {
        if (ctx->current_state == USB_DEVICE_STATE_CONFIGURED)
        {
            usbd_ctrl_error(ctx);
        }
        else
        {
            ctx->address = (uint8_t)(setup->wValue) & 0x7F;
            usbd_set_address(ctx, ctx->address);
            usbd_ctrl_send_status(ctx);

            if (ctx->address != 0)
            {
                ctx->current_state = USB_DEVICE_STATE_ADDRESSED;
            }
            else
            {
                ctx->current_state = USB_DEVICE_STATE_DEFAULT;
            }
        }
    }
    else
    {
        usbd_ctrl_error(ctx);
    }
}

static void usbd_setup_config(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    uint8_t cfg = (uint8_t)setup->wValue;

    if (cfg > USBD_NUM_CONFIGS)
    {
        usbd_ctrl_error(ctx);
    }
    else
    {
        if (ctx->current_state == USB_DEVICE_STATE_ADDRESSED)
        {
            if (cfg)
            {
                ctx->current_config = cfg;
                ctx->current_state = USB_DEVICE_STATE_CONFIGURED;
                ctx->restore_state = USB_DEVICE_STATE_CONFIGURED;
                if (usbd_magna_class_init(ctx, cfg))
                {
                    usbd_ctrl_error(ctx);
                    return;
                }
                usbd_ctrl_send_status(ctx);
            }
            else
            {
                usbd_ctrl_send_status(ctx);
            }
        }
        else if (ctx->current_state == USB_DEVICE_STATE_CONFIGURED)
        {
            if (cfg == 0)
            {
                ctx->current_state = USB_DEVICE_STATE_ADDRESSED;
                ctx->restore_state = USB_DEVICE_STATE_ADDRESSED;
                ctx->current_config = cfg;
                if (usbd_magna_class_deinit(ctx, cfg))
                {
                    usbd_ctrl_error(ctx);
                    return;
                }
                usbd_ctrl_send_status(ctx);
            }
            else if (cfg != ctx->current_config)
            {
                ctx->current_config = cfg;
                if (usbd_magna_class_init(ctx, cfg))
                {
                    usbd_ctrl_error(ctx);
                    return;
                }
                usbd_ctrl_send_status(ctx);
            }
            else
            {
                usbd_ctrl_send_status(ctx);
            }
        }
        else
        {
            usbd_ctrl_error(ctx);
        }
    }
}

static void usbd_get_config(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    if (setup->wLength != 1)
    {
        usbd_ctrl_error(ctx);
    }
    else
    {
        if (ctx->current_state == USB_DEVICE_STATE_ADDRESSED)
        {
            uint8_t default_cfg = 0;
            usbd_ctrl_transmit(ctx, &default_cfg, 1);
        }
        else if (ctx->current_state == USB_DEVICE_STATE_CONFIGURED)
        {
            usbd_ctrl_transmit(ctx, &ctx->current_config, 1);
        }
        else
        {
            usbd_ctrl_error(ctx);
        }
    }
}

static void usbd_get_status(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
	(void)setup;
    const uint16_t dev_cfg = (USB_CONFIG_SELF_POWERED);

    if ((ctx->current_state == USB_DEVICE_STATE_ADDRESSED) ||
        (ctx->current_state == USB_DEVICE_STATE_CONFIGURED))
    {
        usbd_ctrl_transmit(ctx, (uint8_t *)&dev_cfg, sizeof(dev_cfg));
    }
    else
    {
        usbd_ctrl_error(ctx);
    }
}

static void usbd_setup_feature(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    if (setup->wValue == USB_FEATURE_REMOTE_WAKEUP)
    {
        ctx->remote_wake_armed = 1;
        usbd_ctrl_send_status(ctx);
    }
}

static void usbd_clear_feature(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    if (((ctx->current_state == USB_DEVICE_STATE_ADDRESSED) ||
        (ctx->current_state == USB_DEVICE_STATE_CONFIGURED)) &&
        (setup->wValue == USB_FEATURE_REMOTE_WAKEUP))
    {
        ctx->remote_wake_armed = 0;
        usbd_ctrl_send_status(ctx);
    }
    else
    {
        usbd_ctrl_error(ctx);
    }
}

static void usbd_std_dev_request(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    switch (setup->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR:
        usbd_get_descriptor(ctx, setup);
        break;
    case USB_REQ_SET_ADDRESS:
        usbd_setup_address(ctx, setup);
        break;
    case USB_REQ_SET_CONFIGURATION:
        usbd_setup_config(ctx, setup);
        break;
    case USB_REQ_GET_CONFIGURATION:
        usbd_get_config(ctx, setup);
        break;
    case USB_REQ_GET_STATUS:
        usbd_get_status(ctx, setup);
        break;
    case USB_REQ_SET_FEATURE:
        usbd_setup_feature(ctx, setup);
        break;
    case USB_REQ_CLEAR_FEATURE:
        usbd_clear_feature(ctx, setup);
        break;
    default:
        usbd_ctrl_error(ctx);
        break;
    }
}

static void usbd_std_if_request(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    switch (ctx->current_state)
    {
    case USB_DEVICE_STATE_CONFIGURED:
        if (LOBYTE(setup->wIndex) <= USBD_NUM_INTERFACES)
        {
            usbd_magna_setup(ctx, setup);

            if (setup->wLength == 0)
            {
                usbd_ctrl_send_status(ctx);
            }
        }
        else
        {
            usbd_ctrl_error(ctx);
        }
        break;
    default:
        usbd_ctrl_error(ctx);
        break;
    }
}

static void usbd_std_ep_request(usbd_context_t *ctx, usb_setup_packet_t *setup)
{
    uint8_t epnum = LOBYTE(setup->wIndex);
    uint16_t ep_status = 0;

    if (setup->bmRequestType.type == USB_REQUEST_TYPE_CLASS)
    {
        usbd_magna_setup(ctx, setup);
    }
    else
    {
        switch (ctx->current_state)
        {
        case USB_DEVICE_STATE_ADDRESSED:
            if (epnum & 0x7F)
            {
                usbd_ep_stall(ctx, epnum);
            }
            break;
        case USB_DEVICE_STATE_CONFIGURED:
            switch (setup->bRequest)
            {
            case USB_REQ_SET_FEATURE:
                if ((epnum & 0x7F) &&
                    (setup->wValue == USB_FEATURE_EP_HALT))
                {
                    usbd_ep_stall(ctx, epnum);
                }

                usbd_magna_setup(ctx, setup);
                usbd_ctrl_send_status(ctx);
                break;

            case USB_REQ_CLEAR_FEATURE:
                if (setup->wValue == USB_FEATURE_EP_HALT)
                {
                    if (epnum & 0x7F)
                    {
                        usbd_ep_stall(ctx, epnum);
                        usbd_magna_setup(ctx, setup);
                    }

                    usbd_ctrl_send_status(ctx);
                }
                break;

            case USB_REQ_GET_STATUS:
                ep_status = usbd_ep_is_stalled(ctx, epnum) ? 1 : 0;
                usbd_ctrl_transmit(ctx, (uint8_t *)&ep_status, 2);
                break;

            default:
                break;
            }
        default:
            usbd_ctrl_error(ctx);
            break;
        }
    }
}

usb_setup_packet_t setup_trace[1024] = {0};
uint16_t trace_cnt = 0;



void usbd_setup_stage(usbd_context_t *ctx, usb_setup_packet_t *setup)
{

    ctx->ep0_state = USBD_EP0_SETUP;

    setup->wValue = SWAPBYTE(&(setup->wValue));
    setup->wIndex = SWAPBYTE(&(setup->wIndex));
    setup->wLength = SWAPBYTE(&(setup->wLength));

    memcpy(&setup_trace[trace_cnt], setup, sizeof(usb_setup_packet_t));
    trace_cnt++;

    switch (setup->bmRequestType.recipient)
    {
    case USB_REQ_RECIPIENT_DEVICE:
        usbd_std_dev_request(ctx, setup);
        break;
    case USB_REQ_RECIPIENT_INTERFACE:
        usbd_std_if_request(ctx, setup);
        break;
    case USB_REQ_RECIPIENT_ENDPOINT:
        usbd_std_ep_request(ctx, setup);
        break;
    default:
        usbd_ep_stall(ctx, setup->bmRequestType.direction ? 0x80 : 0x00);
        break;
    }
}

void usbd_data_rx_stage(usbd_context_t *ctx, uint8_t epnum,
                        uint8_t *xfer_buff, uint16_t xfer_count)
{
    uint16_t rx_count = 0;

    if (epnum == 0)
    {
        if (ctx->ep0_state == USBD_EP0_DATA_RX)
        {
            if (ctx->ep0_rx.rem_length > ctx->ep0_rx.max_packet_length)
            {
                ctx->ep0_rx.rem_length -= ctx->ep0_rx.max_packet_length;
                rx_count = MIN(ctx->ep0_rx.rem_length, ctx->ep0_rx.max_packet_length);

                usbd_ep_receive(ctx, epnum, xfer_buff, rx_count);
            }
            else
            {
                usbd_ctrl_send_status(ctx);
            }
        }
    }
    else if (ctx->current_state == USB_DEVICE_STATE_CONFIGURED)
    {
        switch (epnum) {
        case USBD_EP_AUDIO_OUT:
            usbd_audio_rx(ctx, xfer_count);

            break;
        default:
            break;
        }
    }
}

void usbd_data_tx_stage(usbd_context_t *ctx, uint8_t epnum, uint8_t *xfer_buff)
{
    if (epnum == 0)
    {
        if (ctx->ep0_state == USBD_EP0_DATA_TX)
        {
            if (ctx->ep0_tx.rem_length > ctx->ep0_tx.max_packet_length)
            {
                ctx->ep0_tx.rem_length -= ctx->ep0_tx.max_packet_length;
                uint16_t tx_count = MIN(ctx->ep0_tx.rem_length, ctx->ep0_tx.max_packet_length);

                usbd_ep_transmit(ctx, epnum, xfer_buff, tx_count);

                usbd_ep_receive(ctx, 0, NULL, 0);
            }
            else if (ctx->ep0_tx.rem_length == ctx->ep0_tx.max_packet_length)
            {
                ctx->ep0_tx.rem_length = 0;
                usbd_ctrl_send_status(ctx);

                usbd_ctrl_recv_status(ctx);
            }
            else
            {
                usbd_ctrl_recv_status(ctx);
            }
        }
    }
    else if (ctx->current_state == USB_DEVICE_STATE_CONFIGURED)
    {
      /*  switch (USB_EP_TX(epnum)) {
        case USBD_EP_CDC_TX:
            usbd_cdc_tx(ctx);
            break;
        default:
            break;
        }*/
    }
}

uint8_t dummy_data[USBD_ISOC_PACKET_SIZE] = "THIS IS SOME DUMMY DATA";
uint8_t test_buffer[USBD_ISOC_PACKET_SIZE];
void usbd_start_of_frame(usbd_context_t *ctx)
{
    (void)ctx;
    //usb_transmit(USBD_AUDIO_IN_CHN1, dummy_data, USBD_ISOC_PACKET_SIZE);
    //usbd_ep_receive(ctx, USBD_EP_AUDIO_OUT,
    //                   test_buffer, USBD_ISOC_PACKET_SIZE);
    //usb_transmit(USBD_EP_AUDIO_IN, test_buffer, USBD_ISOC_PACKET_SIZE);
    return;
}

void usbd_reset(usbd_context_t *ctx)
{
    ctx->current_state = USB_DEVICE_STATE_DEFAULT;
    ctx->restore_state = USB_DEVICE_STATE_DEFAULT;
    ctx->remote_wake_armed = 0;
    ctx->address = 0;
    ctx->current_config = 0;
    ctx->ep0_state = USBD_EP0_IDLE;

    usbd_ep_close(ctx, USBD_EP_AUDIO_IN);
    usbd_ep_close(ctx, USBD_EP_AUDIO_FEEDBACK);
    usbd_ep_close(ctx, USBD_EP_AUDIO_OUT);

    usbd_ep_open(ctx, USBD_EP_CTRL_TX,
                 USBD_EP_CTRL_TYPE, USBD_CTRL_PACKET_SIZE);
    usbd_ep_open(ctx, USBD_EP_CTRL_RX,
                 USBD_EP_CTRL_TYPE, USBD_CTRL_PACKET_SIZE);

    ctx->ep0_tx.max_packet_length = USBD_CTRL_PACKET_SIZE;
    ctx->ep0_rx.max_packet_length = USBD_CTRL_PACKET_SIZE;
}

void usbd_suspend(usbd_context_t *ctx)
{
    ctx->restore_state = ctx->current_state;
    ctx->current_state = USB_DEVICE_STATE_SUSPENDED;
}

void usbd_resume(usbd_context_t *ctx)
{
    ctx->current_state = ctx->restore_state;
}

void usbd_connect(usbd_context_t *ctx)
{
    (void)ctx;
}


void usbd_disconnect(usbd_context_t *ctx)
{
    ctx->current_state = USB_DEVICE_STATE_DEFAULT;
    ctx->restore_state = USB_DEVICE_STATE_DEFAULT;
    ctx->remote_wake_armed = 0;
    ctx->address = 0;
    ctx->current_config = 0;

    usbd_ep_close(ctx, USBD_EP_AUDIO_IN);
    usbd_ep_close(ctx, USBD_EP_AUDIO_FEEDBACK);
    usbd_ep_close(ctx, USBD_EP_AUDIO_OUT);
}

int usbd_is_ready(void)
{
    return (magna_ctx.current_state == USB_DEVICE_STATE_CONFIGURED);
}

int usbd_transmit(uint8_t epnum, uint8_t *xfer_buff, uint16_t length)
{
    usbd_context_t *ctx = &magna_ctx;

    if (ctx->current_state == USB_DEVICE_STATE_CONFIGURED)
    {
        return usbd_ep_transmit(ctx, epnum, xfer_buff, length);
    }

    return MAGNA_FAILED;
}

void usbd_ctrl_transmit(usbd_context_t *ctx,
                        uint8_t *xfer_buff, uint16_t length)
{
    ctx->ep0_tx.total_length = length;
    ctx->ep0_tx.rem_length = length;
    ctx->ep0_state = USBD_EP0_DATA_TX;

    usbd_ep_transmit(ctx, USBD_EP_CTRL_TX, xfer_buff, length);
}

void usbd_ctrl_receive(usbd_context_t *ctx,
                       uint8_t *xfer_buff, uint16_t length)
{
    ctx->ep0_rx.total_length = length;
    ctx->ep0_rx.rem_length = length;
    ctx->ep0_state = USBD_EP0_DATA_RX;

    usbd_ep_receive(ctx, USBD_EP_CTRL_RX, xfer_buff, length);
}

usbd_context_t *usbd_get_context(void)
{
    return &magna_ctx;
}

int usbd_init(void)
{
    memset(&magna_ctx, 0, sizeof(usbd_context_t));

    magna_ctx.current_state = USB_DEVICE_STATE_DEFAULT;
    magna_ctx.restore_state = USB_DEVICE_STATE_DEFAULT;

    if (usbd_hw_init(&magna_ctx) != MAGNA_OK)
    {
        return MAGNA_FAILED;
    }

    return usbd_start(&magna_ctx);
}

int usbd_deinit(void)
{
    usbd_stop(&magna_ctx);

    usbd_hw_deinit(&magna_ctx);

    memset(&magna_ctx, 0, sizeof(usbd_context_t));

    return MAGNA_OK;
}
