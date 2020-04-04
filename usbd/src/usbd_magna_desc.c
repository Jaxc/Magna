
#include "usbd_magna_desc.h"

#include "usbd_internal.h"

#define USBD_VID                        0x1209 /*STM32 Full Speed Default VID*/
#define USBD_PID                        0x000D /*STM32 Full Speed Default PID*/

#define USBD_LANGID_ENG_US              0x0409
#define USBD_MANUFACTURER_STRING        L"Skrooter Audio"
#define USBD_PRODUCT_STRING             L"Magna DJ Mixer"
#define USBD_SERIALNUMBER_STRING        L"00000000001A"
#define USBD_CONFIGURATION_STRING       L"Magna Config"
#define USBD_CDC_IF_STRING              L"Magna CDC Interface"

/* USB Standard Device Descriptor */
static uint8_t usbd_magna_dev_desc[USB_DEVICE_DESC_SIZE] = {
    USB_DEVICE_DESC_SIZE,
    USB_DEVICE_DESC_TYPE,
    LOBYTE(USB_DEVICE_USB_VERSION),
    HIBYTE(USB_DEVICE_USB_VERSION),
    USB_DEVICE_CLASS,
    USB_DEVICE_SUB_CLASS,
    USB_DEVICE_PROTOCAL_CLASS,
    USBD_CTRL_PACKET_SIZE,
    LOBYTE(USBD_VID),
    HIBYTE(USBD_VID),
    LOBYTE(USBD_PID),
    HIBYTE(USBD_PID),
    LOBYTE(MAGNA_VERSION),
    HIBYTE(MAGNA_VERSION),
    USBD_IDX_MFC_STR,
    USBD_IDX_PRODUCT_STR,
    USBD_IDX_SERIAL_STR,
    USBD_NUM_CONFIGS,
};

/* USB CDC device Configuration Descriptor */
static uint8_t usbd_magna_cfg_desc[USBD_CFG_SIZE] = {
    /*Configuration Descriptor*/
    USB_CONFIG_DESC_SIZE,               /* bLength: Configuration Descriptor size */
    USB_CONFIG_DESC_TYPE,               /* bDescriptorType: Configuration */
    LOBYTE(USBD_CFG_SIZE),              /* wTotalLength:no of returned bytes */
    HIBYTE(USBD_CFG_SIZE),
    USBD_NUM_INTERFACES,                /* bNumInterfaces: 4 interface */
    USB_CONFIG_VALUE,                   /* bConfigurationValue: Configuration value */
    USBD_IDX_CONFIG_STR,                /* iConfiguration: Index of string descriptor describing the configuration */
    USB_CONFIG_ATTRIBUTES,              /* bmAttributes: self powered */
    USB_CONFIG_MAXPOWER,                /* MaxPower 100 mA */



/*---------------------------------------------------------------------------*/
/*  Audio interface                                                           */
/*---------------------------------------------------------------------------*/

/* Audio control interface*/
    USB_INTERFACE_DESC_SIZE,
    USB_INTERFACE_DESC_TYPE,
    USBD_AUDIO_CONTROL_INTERFACE,
    USB_INTERFACE_ALT_0,
    USBD_AUDIO_CONTROL_EP,
    USBD_AUDIO_CLASS,
    USB_AUDIO_CONTROL_SUBCLASS,
    USB_AUDIO_PROTOCOL,
    0x00,


    /* Audio control descriptor*/
    USB_AUDIO_CONTROL_SIZE,
    USB_CS_INTERFACE_TYPE,
    USBD_AC_HEADER,
    LOBYTE(USBD_AC_BCD_VER),
    HIBYTE(USBD_AC_BCD_VER),
    LOBYTE(USBD_AC_SIZE),
    HIBYTE(USBD_AC_SIZE),
    0x02,
    0x01,
    0x02,

/*---------------------------------------------------------------------------*/
#if 0
    /* Audio clock source descriptor*/
    USB_CLOCK_DESC_SIZE,
    USB_CS_INTERFACE_TYPE,
    USB_AC_CLOCK_TYPE,
    USB_AC_CLOCK_ID,
    USB_AC_CLOCK_ATTRIBUTE,
    USB_AC_CLOCK_CONTROL,
    USB_AC_CLOCK_ASSOC,
    USB_AC_CLOCK_SOURCE,


    /* Audio clock selector descriptor*/
#endif
/*---------------------------------------------------------------------------*/

    /* Line1 Terminal input analogue*/
    USB_TERMINAL_DESC_SIZE,
    USB_CS_INTERFACE_TYPE,
    USB_AC_INPUT_TERMINAL,
    USB_AC_INPUT_LINE,
    LOBYTE(USB_AC_TERMINAL_LINE),
    HIBYTE(USB_AC_TERMINAL_LINE),
    USB_AC_INPUT_ASSOC,
    USB_AC_INPUT_CHANNELS,
    LOBYTE(USB_AC_INPUT_CHANNEL_CFG),
    HIBYTE(USB_AC_INPUT_CHANNEL_CFG),
    0x00,
    0x00,

    /* Line 1 Terminal Output USB*/
    USB_INTERFACE_DESC_SIZE,
    USB_CS_INTERFACE_TYPE,
    USB_AC_OUTPUT_TERMINAL,
    USB_AC_OUTPUT_USB,
    LOBYTE(USB_AC_TERMINAL_USB),
    HIBYTE(USB_AC_TERMINAL_USB),
    USB_AC_INPUT_ASSOC,
    USB_AC_INPUT_LINE,
    0x00,

/*---------------------------------------------------------------------------*/

    /* Audio control Terminal input USB */
    USB_TERMINAL_DESC_SIZE,
    USB_CS_INTERFACE_TYPE,
    USB_AC_INPUT_TERMINAL,
    USB_AC_INPUT_USB,
    LOBYTE(USB_AC_TERMINAL_USB),
    HIBYTE(USB_AC_TERMINAL_USB),
    USB_AC_INPUT_ASSOC,
    USB_AC_OUTPUT_CHANNELS,
    LOBYTE(USB_AC_INPUT_CHANNEL_CFG),
    HIBYTE(USB_AC_INPUT_CHANNEL_CFG),
    0x00,
    0x00,

    /* Audio control Terminal Output analogue*/
    USB_INTERFACE_DESC_SIZE,
    USB_CS_INTERFACE_TYPE,
    USB_AC_OUTPUT_TERMINAL,
    USB_AC_OUTPUT_LINE,
    LOBYTE(USB_AC_TERMINAL_LINE),
    HIBYTE(USB_AC_TERMINAL_LINE),
    USB_AC_INPUT_ASSOC,
    USB_AC_INPUT_USB,
    0x00,

/*---------------------------------------------------------------------------*/

/*Interface No EP Descriptor */
    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    USBD_AUDIO_INTERFACE2,                               /* bInterfaceNumber: Number of Interface */
    USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */
    USBD_AUDIO_CONTROL_EP,                               /* bNumEndpoints: One endpoints used */
    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */
    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */
    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */
    0x00,                /* iInterface: */

/*Interface Descriptor */
    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    USBD_AUDIO_INTERFACE2,                               /* bInterfaceNumber: Number of Interface */
    USB_INTERFACE_ALT_1,                               /* bAlternateSetting: Alternate setting */
    USBD_AUDIOSTREAM_OUT_EP,                               /* bNumEndpoints: One endpoints used */
    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */
    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */
    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */
    0x00,                /* iInterface: */

    /* Class-specific AS General Interface Descriptor */
    USB_AS_GENERAL_SIZE,
    USB_CS_INTERFACE_TYPE,
    USB_GENERAL_SUBTYPE,
    USB_AC_OUTPUT_USB,
    USBD_AUDIO_DELAY,
    LOBYTE(USBD_AUDIO_FORMAT_PCM),
    HIBYTE(USBD_AUDIO_FORMAT_PCM),

    /* Type I Format Type Descriptor */
    USB_TYPE_1_FORMAT,
    USB_CS_INTERFACE_TYPE,
    USB_FORMAT_TYPE_SUBTYPE,
    USB_FORMAT_TYPE_1,
    USB_AC_OUTPUT_CHANNELS,
    USBD_SUB_FRAME_SIZE,
    USBD_AUDIO_RESOLUTION,
    USBD_N_AUDIO_SAMPLERATE,
    LOBYTE(USBD_AUDIO_SAMPLERATE),
    HIBYTE(USBD_AUDIO_SAMPLERATE),
    LOBYTE(USBD_AUDIO_SAMPLERATE >> 16),


    /* Endpoint OUT 2 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    USBD_EP_AUDIO_OUT,                    /* bEndpointAddress */
    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_ISOC_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_ISOC_PACKET_SIZE),
    USBD_AUDIO_INTERVAL,                               /* bInterval: */

    /* Class-specific Isochronous Audio Data Endpoint Descriptor */
    USB_AS_GENERAL_SIZE,
    USB_CS_ENDPOINT_TYPE,
    USB_GENERAL_SUBTYPE,
    0x00,
    0x00,
    0x00,
    0x00,

    /* Endpoint IN 2 descriptor (feedback) */
    USB_ENDPOINT_DESC_SIZE,
    USB_ENDPOINT_DESC_TYPE,
    USBD_EP_AUDIO_FEEDBACK,
    USDB_AUDIO_FEEDBACK,
    LOBYTE(USBD_FEEDBACK_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_FEEDBACK_SIZE),
    USBD_FEEDBACK_INTERVAL,

/*Interface No EP Descriptor */
    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    USBD_AUDIO_INTERFACE,                               /* bInterfaceNumber: Number of Interface */
    USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */
    USBD_AUDIO_CONTROL_EP,                               /* bNumEndpoints: One endpoints used */
    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */
    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */
    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */
    0x00,                /* iInterface: */

/*Interface Descriptor */
    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    USBD_AUDIO_INTERFACE,                               /* bInterfaceNumber: Number of Interface */
    USB_INTERFACE_ALT_1,                               /* bAlternateSetting: Alternate setting */
    USBD_AUDIOSTREAM_IN_EP,                               /* bNumEndpoints: One endpoints used */
    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */
    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */
    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */
    0x00,                /* iInterface: */

    /* Class-specific AS General Interface Descriptor */
    USB_AS_GENERAL_SIZE,
    USB_CS_INTERFACE_TYPE,
    USB_GENERAL_SUBTYPE,
    USB_AC_INPUT_USB,
    USBD_AUDIO_DELAY,
    LOBYTE(USBD_AUDIO_FORMAT_PCM),
    HIBYTE(USBD_AUDIO_FORMAT_PCM),

    /* Type I Format Type Descriptor */
    USB_TYPE_1_FORMAT,
    USB_CS_INTERFACE_TYPE,
    USB_FORMAT_TYPE_SUBTYPE,
    USB_FORMAT_TYPE_1,
    USB_AC_INPUT_CHANNELS,
    USBD_SUB_FRAME_SIZE,
    USBD_AUDIO_RESOLUTION,
    USBD_N_AUDIO_SAMPLERATE,
    LOBYTE(USBD_AUDIO_SAMPLERATE),
    HIBYTE(USBD_AUDIO_SAMPLERATE),
    LOBYTE(USBD_AUDIO_SAMPLERATE >> 16),


    /*Endpoint 2 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    USBD_EP_AUDIO_IN,                    /* bEndpointAddress */
    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_ISOC_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_ISOC_PACKET_SIZE),
    USBD_AUDIO_INTERVAL,                               /* bInterval: */

    /* Class-specific Isochronous Audio Data Endpoint Descriptor */
    USB_AS_GENERAL_SIZE,
    USB_CS_ENDPOINT_TYPE,
    USB_GENERAL_SUBTYPE,
    0x00,
    0x00,
    0x00,
    0x00,

#if 0
    /*Endpoint 3 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    USBD_AUDIO_OUT_CHN2,                    /* bEndpointAddress */
    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_ISOC_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_ISOC_PACKET_SIZE),
    USBD_AUDIO_INTERVAL                               /* bInterval: */
#endif
#if 0
/*---------------------------------------------------------------------------*/
/*  MIDI interface                                                           */
/*---------------------------------------------------------------------------*/

    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    USBD_AUDIO_INTERFACE,//UDBD_MIDI_INTERFACE,                               /* bInterfaceNumber: Number of Interface */
    USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */
    USBD_MIDI_EP,                               /* bNumEndpoints: One endpoints used */
    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */
    USB_MIDISTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */
    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */
    0x00,                               /* iInterface: */

    /*Endpoint 0 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    USBD_MIDI_IN,                    /* bEndpointAddress */
    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    USBD_AUDIO_INTERVAL,                               /* bInterval: */

    /*Endpoint 1 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    USBD_MIDI_OUT,                    /* bEndpointAddress */
    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    USBD_AUDIO_INTERVAL,                               /* bInterval: */


    /*---------------------------------------------------------------------------*/
    /*  CDC Interface                                                            */
    /*---------------------------------------------------------------------------*/

        /*Interface Descriptor */
        USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
        USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
        USBD_CDC_CONTROL_INTERFACE,          /* bInterfaceNumber: Number of Interface */
        USB_INTERFACE_ALT_0,    /* bAlternateSetting: Alternate setting */
        USBD_CDC_CONTROL_ENDPOINTS,         /* bNumEndpoints: One endpoint used */
        USBD_CDC_ACM_CLASS,                  /* bInterfaceClass: Communication Interface Class */
        USBD_CDC_ACM_SUBCLASS,               /* bInterfaceSubClass: Abstract Control Model */
        USBD_CDC_ACM_PROTOCOL,              /* bInterfaceProtocol: Common AT commands */
        USBD_IDX_CDC_IF_STR,                /* iInterface: */

        /*Header Functional Descriptor*/
        USBD_CDC_HEADER_SIZE,               /* bLength: Endpoint Descriptor size */
        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */
        0x00,                               /* bDescriptorSubtype: Header Func Desc */
        0x10,                               /* bcdCDC: spec release number */
        0x01,

        /*Call Management Functional Descriptor*/
        USBD_CDC_CALL_MAN_SIZE,             /* bFunctionLength */
        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */
        0x01,                               /* bDescriptorSubtype: Call Management Func Desc */
        0x00,                               /* bmCapabilities: D0+D1 */
        0x01,                               /* bDataInterface: 1 */

        /*ACM Functional Descriptor*/
        USBD_CDC_ACM_SIZE,                  /* bFunctionLength */
        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */
        0x02,                               /* bDescriptorSubtype: Abstract Control Management desc */
        0x02,                               /* bmCapabilities */

        /*Union Functional Descriptor*/
        USBD_CDC_UNION_SIZE,                /* bFunctionLength */
        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */
        0x06,                               /* bDescriptorSubtype: Union func desc */
        0x00,                               /* bMasterInterface: Communication class interface */
        0x01,                               /* bSlaveInterface0: Data Class Interface */

        /*Endpoint 2 Descriptor*/
        USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
        USBD_EP_CDC_CMD,                    /* bEndpointAddress */
        USBD_EP_INTR_TYPE,                  /* bmAttributes: Interrupt */
        LOBYTE(USBD_INT_PACKET_SIZE),       /* wMaxPacketSize: */
        HIBYTE(USBD_INT_PACKET_SIZE),
        USBD_CDC_EP_INTERVAL,               /* bInterval: */

    /*---------------------------------------------------------------------------*/

        /*Data class interface descriptor*/
        USB_INTERFACE_DESC_SIZE,            /* bLength: Endpoint Descriptor size */
        USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: */
        USBD_CDC_DATA_INTERFACE,            /* bInterfaceNumber: Number of Interface */
        USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */
        USBD_CDC_DATA_ENDPOINTS,                               /* bNumEndpoints: Two endpoints used */
        USBD_CDC_DATA_CLASS,                               /* bInterfaceClass: CDC */
        USBD_CDC_DATA_SUBCLASS,                               /* bInterfaceSubClass: */
        USBD_CDC_DATA_PROTOCOL,                               /* bInterfaceProtocol: */
        USBD_IDX_CDC_IF_STR,                /* iInterface: */

        /*Endpoint OUT Descriptor*/
        USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
        USBD_EP_CDC_RX,                     /* bEndpointAddress */
        USBD_EP_BULK_TYPE,                               /* bmAttributes: Bulk */
        LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */
        HIBYTE(USBD_BULK_PACKET_SIZE),
        USBD_CDC_DATA_INTERVAL,                               /* bInterval: ignore for Bulk transfer */

        /*Endpoint IN Descriptor*/
        USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
        USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
        USBD_EP_CDC_TX,                     /* bEndpointAddress */
        USBD_EP_BULK_TYPE,                               /* bmAttributes: Bulk */
        LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */
        HIBYTE(USBD_BULK_PACKET_SIZE),
        USBD_CDC_DATA_INTERVAL,                               /* bInterval: ignore for Bulk transfer */
#endif
};

#define USB_STRING(Name, String) \
struct { \
    uint8_t  bLength; \
    uint8_t  bDescriptorType; \
    wchar_t wString[sizeof(String) / sizeof(wchar_t) - 1]; \
} __attribute__((packed)) Name = { \
    .bLength = sizeof(Name), \
    .bDescriptorType = USB_STRING_DESC_TYPE, \
    .wString = String \
}

USB_STRING(usbd_magna_mfc_str, USBD_MANUFACTURER_STRING);
USB_STRING(usbd_magna_prod_str, USBD_PRODUCT_STRING);
USB_STRING(usbd_magna_serial_str, USBD_SERIALNUMBER_STRING);
USB_STRING(usbd_magna_cfg_str, USBD_CONFIGURATION_STRING);
USB_STRING(usbd_magna_cdc_if_str, USBD_CDC_IF_STRING);

static uint8_t usbd_magna_langid_str[4] = {
    4,
    USB_LANGID_DESC_TYPE,
    LOBYTE(USBD_LANGID_ENG_US),
    HIBYTE(USBD_LANGID_ENG_US),
};

uint8_t *usbd_get_dev_desc(uint16_t *length)
{
    *length = USB_DEVICE_DESC_SIZE;
    return usbd_magna_dev_desc;
}

uint8_t *usbd_get_cfg_desc(uint8_t cfg_no, uint16_t *length)
{
    (void)cfg_no;
    *length = USBD_CFG_SIZE;
    return usbd_magna_cfg_desc;
}

uint8_t *usbd_get_langid_str(uint16_t *length)
{
    *length = sizeof(usbd_magna_langid_str);
    return usbd_magna_langid_str;
}

uint8_t *usbd_get_mfc_str(uint16_t *length)
{
    *length = sizeof(usbd_magna_mfc_str);
    return (uint8_t *)&usbd_magna_mfc_str;
}

uint8_t *usbd_get_prod_str(uint16_t *length)
{
    *length = sizeof(usbd_magna_prod_str);
    return (uint8_t *)&usbd_magna_prod_str;
}

uint8_t *usbd_get_serial_str(uint16_t *length)
{
    *length = sizeof(usbd_magna_serial_str);
    return (uint8_t *)&usbd_magna_serial_str;
}

uint8_t *usbd_get_cfg_str(uint16_t *length)
{
    *length = sizeof(usbd_magna_cfg_str);
    return (uint8_t *)&usbd_magna_cfg_str;
}

uint8_t *usbd_get_cdc_if_str(uint16_t *length)
{
    *length = sizeof(usbd_magna_cdc_if_str);
    return (uint8_t *)&usbd_magna_cdc_if_str;
}
