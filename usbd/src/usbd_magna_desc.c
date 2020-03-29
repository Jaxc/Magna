
#include "usbd_magna_desc.h"

#include "usbd_internal.h"

#define USBD_VID                        0x0483 /*STM32 Full Speed Default VID*/
#define USBD_PID                        0x5740 /*STM32 Full Speed Default PID*/

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
    0x01,                               /* bConfigurationValue: Configuration value */
    USBD_IDX_CONFIG_STR,                /* iConfiguration: Index of string descriptor describing the configuration */
    0xC0,                               /* bmAttributes: self powered */
    0x32,                               /* MaxPower 0 mA */

/*---------------------------------------------------------------------------*/
/*  CDC Interface                                                            */
/*---------------------------------------------------------------------------*/

    /*Interface Descriptor */
    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    0x00,                               /* bInterfaceNumber: Number of Interface */
    0x00,                               /* bAlternateSetting: Alternate setting */
    0x01,                               /* bNumEndpoints: One endpoints used */
    0x02,                               /* bInterfaceClass: Communication Interface Class */
    0x02,                               /* bInterfaceSubClass: Abstract Control Model */
    0x01,                               /* bInterfaceProtocol: Common AT commands */
    0x06,                /* iInterface: */

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
    0x03,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_INT_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_INT_PACKET_SIZE),
    0x0A,                               /* bInterval: */

/*---------------------------------------------------------------------------*/

    /*Data class interface descriptor*/
    USB_INTERFACE_DESC_SIZE,            /* bLength: Endpoint Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: */
    0x01,                               /* bInterfaceNumber: Number of Interface */
    0x00,                               /* bAlternateSetting: Alternate setting */
    0x02,                               /* bNumEndpoints: Two endpoints used */
    0x0A,                               /* bInterfaceClass: CDC */
    0x00,                               /* bInterfaceSubClass: */
    0x00,                               /* bInterfaceProtocol: */
    USBD_IDX_CDC_IF_STR,                /* iInterface: */

    /*Endpoint OUT Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    USBD_EP_CDC_RX,                     /* bEndpointAddress */
    0x02,                               /* bmAttributes: Bulk */
    LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x00,                               /* bInterval: ignore for Bulk transfer */

    /*Endpoint IN Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    USBD_EP_CDC_TX,                     /* bEndpointAddress */
    0x02,                               /* bmAttributes: Bulk */
    LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x00,                               /* bInterval: ignore for Bulk transfer */

/*---------------------------------------------------------------------------*/
/*  Audio interface                                                           */
/*---------------------------------------------------------------------------*/

    /*Interface Descriptor */
    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    0x02,                               /* bInterfaceNumber: Number of Interface */
    0x00,                               /* bAlternateSetting: Alternate setting */
    0x04,                               /* bNumEndpoints: One endpoints used */
    0x01,                               /* bInterfaceClass: Communication Interface Class */
    0x02,                               /* bInterfaceSubClass: Abstract Control Model */
    0x00,                               /* bInterfaceProtocol: Common AT commands */
    0x00,                /* iInterface: */

    /*Endpoint 0 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    0x83,                    /* bEndpointAddress */
    0x05,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x01,                               /* bInterval: */

    /*Endpoint 1 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    0x84,                    /* bEndpointAddress */
    0x05,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x01,                               /* bInterval: */

    /*Endpoint 2 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    0x03,                    /* bEndpointAddress */
    0x05,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x01,                               /* bInterval: */

    /*Endpoint 3 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    0x04,                    /* bEndpointAddress */
    0x05,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x01,                               /* bInterval: */

/*---------------------------------------------------------------------------*/

    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */
    0x03,                               /* bInterfaceNumber: Number of Interface */
    0x00,                               /* bAlternateSetting: Alternate setting */
    0x02,                               /* bNumEndpoints: One endpoints used */
    0x01,                               /* bInterfaceClass: Communication Interface Class */
    0x03,                               /* bInterfaceSubClass: Abstract Control Model */
    0x00,                               /* bInterfaceProtocol: Common AT commands */
    0x00,                               /* iInterface: */

    /*Endpoint 0 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    0x85,                    /* bEndpointAddress */
    0x05,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x01,                               /* bInterval: */

    /*Endpoint 0 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    0x85,                    /* bEndpointAddress */
    0x05,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x01,                               /* bInterval: */

    /*Endpoint 1 Descriptor*/
    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */
    0x85,                    /* bEndpointAddress */
    0x05,                               /* bmAttributes: Interrupt */
    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */
    HIBYTE(USBD_BULK_PACKET_SIZE),
    0x01,                               /* bInterval: */
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