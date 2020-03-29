#ifndef USB_DESC_H_
#define USB_DESC_H_

#include <stdint.h>
#include <usbd_internal.h>
/*------------------------------------------------------------------------------*/
/*  General descriptors                                                         */
/*------------------------------------------------------------------------------*/

#define USBD_NUM_CONFIGS                1
#define USBD_NUM_INTERFACES             2
#define USBD_CFG_SIZE                   (USB_CONFIG_DESC_SIZE + USB_AUDIO_BLOCK_SIZE)
/*136 */

#define USB_DEVICE_DESC_TYPE            1
#define USB_CONFIG_DESC_TYPE            2
#define USB_STRING_DESC_TYPE            3
#define USB_INTERFACE_DESC_TYPE         4
#define USB_ENDPOINT_DESC_TYPE          5
#define USB_DEVICE_QUALIFIER_DESC_TYPE  6

#define USB_LANGID_DESC_TYPE            USB_STRING_DESC_TYPE
#define USB_IAD_DESC_TYPE               0x0b
#define USB_BOS_DESC_TYPE               0x0f
#define USB_CS_INTERFACE_TYPE           0x24
#define USB_CS_ENDPOINT_TYPE            0x25

#define USB_DEVICE_USB_VERSION          0x0200
#define USB_DEVICE_CLASS                0x00
#define USB_DEVICE_SUB_CLASS            0x00
#define USB_DEVICE_PROTOCAL_CLASS       0x00
#define MAGNA_VERSION                   0x0001

#define USB_DEVICE_DESC_SIZE            18
#define USB_TERMINAL_DESC_SIZE          12
#define USB_CONFIG_DESC_SIZE            9
#define USB_INTERFACE_DESC_SIZE         9
#define USB_AUDIO_CONTROL_SIZE          10
#define USB_ENDPOINT_DESC_SIZE          7
#define USB_AS_GENERAL_SIZE             7
#define USB_TYPE_1_FORMAT               11
#define USB_LANGID_DESC_SIZE            4
#define USB_IAD_DESC_SIZE               8

#define USBD_IDX_LANGID_STR             0
#define USBD_IDX_MFC_STR                1
#define USBD_IDX_PRODUCT_STR            2
#define USBD_IDX_SERIAL_STR             3
#define USBD_IDX_CONFIG_STR             4
#define USBD_IDX_MIDI_IF_STR            5
#define USBD_IDX_CDC_IF_STR             6

#define USB_LANGID_ENG_US               0x0409

#define USB_CONFIG_REMOTE_WAKEUP        0x02
#define USB_CONFIG_SELF_POWERED         0x40
#define USB_CONFIG_ATTRIBUTES           USB_CONFIG_SELF_POWERED | 0x80

#define USB_CONFIG_VALUE                0x01
#define USB_CONFIG_MAXPOWER             0x32

#define USB_FEATURE_EP_HALT             0
#define USB_FEATURE_REMOTE_WAKEUP       1
#define USB_FEATURE_TEST_MODE           2

#define USB_INTERFACE_ALT_0             0x00
#define USB_INTERFACE_ALT_1             0x01

#define USBD_AUDIO_CONTROL_INTERFACE    0x00
#define USBD_AUDIO_INTERFACE            0x01
#define USBD_AUDIO_INTERFACE2            0x02
#define USBD_CDC_CONTROL_INTERFACE      0x03
#define USBD_CDC_DATA_INTERFACE         0x04
#define UDBD_MIDI_INTERFACE             0x05

#define USBD_AUDIO_CLASS                0x01

#define USB_AUDIO_CONTROL_SUBCLASS      0x01
#define USB_AUDIOSTREAMING_SUBCLASS     0x02
#define USB_MIDISTREAMING_SUBCLASS      0x03

#define USB_AUDIO_PROTOCOL              0x00

#define USB_GENERAL_SUBTYPE             0x01
#define USB_FORMAT_TYPE_SUBTYPE         0x02

#define USB_FORMAT_TYPE_1               0x01

#define USBD_AUDIO_FORMAT_PCM           0x0001

/*------------------------------------------------------------------------------*/
/*  AUDIO control interface                                                              */
/*------------------------------------------------------------------------------*/

#define USBD_AC_HEADER                  0x01
#define USBD_AC_BCD_VER                 0x0100
#define USBD_AC_SIZE                    (2*(USB_INTERFACE_DESC_SIZE + USB_TERMINAL_DESC_SIZE) \
                                         + USB_AUDIO_CONTROL_SIZE)
#define USBD_AC_BLOCK_SIZE              USBD_AC_SIZE + USB_INTERFACE_DESC_SIZE

#define USB_AC_INPUT_TERMINAL           0x02
#define USB_AC_OUTPUT_TERMINAL          0x03

#define USB_AC_INPUT_LINE_1_ID          0x01
#define USB_AC_INPUT_USB_ID             0x02
#define USB_AC_OUTPUT_USB_ID            0x03
#define USB_AC_OUTPUT_MASTER_ID         0x04

#define USB_AC_TERMINAL_LINE            0x0603
#define USB_AC_TERMINAL_USB             0x0101
#define USB_AC_INPUT_ASSOC              0x00
#define USB_AC_INPUT_CHANNELS           0x02
#define USB_AC_INPUT_CHANNEL_CFG        0x0003
#define USB_AC_OUTPUT_SOURCE_ID         0x01

#define USBD_ENDPOINT_0_SIZE            (USB_ENDPOINT_DESC_SIZE + USB_AS_GENERAL_SIZE)
#define USBD_ENDPOINT_1_SIZE            (USB_ENDPOINT_DESC_SIZE)
#define USBD_ENDPOINT_2_SIZE            (USB_ENDPOINT_DESC_SIZE + USB_AS_GENERAL_SIZE)
#define USBD_ENDPOINT_3_SIZE            (USB_ENDPOINT_DESC_SIZE)
#define USBD_ENPOINTS_SIZE              (USBD_ENDPOINT_0_SIZE + USBD_ENDPOINT_1_SIZE \
                                        + USBD_ENDPOINT_2_SIZE + USBD_ENDPOINT_3_SIZE)

#define USBD_AUDIO_INTERFACE_SIZE       (2 * USB_INTERFACE_DESC_SIZE + USB_AS_GENERAL_SIZE \
                                        + USB_TYPE_1_FORMAT)

#define USB_AUDIO_BLOCK_SIZE            (USBD_AC_BLOCK_SIZE + USBD_ENPOINTS_SIZE \
                                        + 2 * USBD_AUDIO_INTERFACE_SIZE)

/*------------------------------------------------------------------------------*/
/*  MIDI Interface                                                              */
/*------------------------------------------------------------------------------*/

#define USBD_MIDI_CS_IF_DESC_TYPE       USB_CS_INTERFACE_TYPE
#define USBD_MIDI_CS_EP_DESC_TYPE       USB_CS_ENDPOINT_TYPE

#define USBD_MIDI_CONTROL_SIZE          9
#define USBD_MIDI_STREAM_SIZE           7
#define USBD_MIDI_JACK_IN_SIZE          6
#define USBD_MIDI_JACK_OUT_SIZE         9
#define USBD_MIDI_ENDPOINT_SIZE         5

#define USBD_MIDI_SIZE                  (2 * USB_INTERFACE_DESC_SIZE) + \
                                        USBD_MIDI_CONTROL_SIZE + \
                                        USBD_MIDI_STREAM_SIZE + \
                                        (2 * USBD_MIDI_JACK_IN_SIZE) + \
                                        (2 * USBD_MIDI_JACK_OUT_SIZE) + \
                                        (2 * USB_ENDPOINT_DESC_SIZE) + \
                                        (2 * USBD_MIDI_ENDPOINT_SIZE)

#define USBD_MIDI_IN_JACK               0x02
#define USBD_MIDI_OUT_JACK              0x03

#define USBD_MIDI_JACK_EMBEDDED         0x01
#define USBD_MIDI_JACK_EXTERNAL         0x02

#define USBD_AUDIO_CONTROL_EP           0x00
#define USBD_AUDIOSTREAM_EP             0x04
#define USBD_MIDI_EP                    0x02

#define USBD_AUDIO_IN_CHN1              0x81
#define USBD_AUDIO_IN_CHN2              0x82
#define USBD_AUDIO_MASTER               0x01
#define USBD_AUDIO_PHONES               0x02

#define USBD_MIDI_IN                    0x85
#define USBD_MIDI_OUT                   0x05

#define USDB_AUDIO_ASYNC                USBD_EP_ISOC_TYPE | 0x4

#define USBD_AUDIO_INTERVAL             0x01

#define USBD_AUDIO_DELAY                0x01

#define USBD_AUDIO_RESOLUTION           24
#define USBD_N_AUDIO_SAMPLERATE         0x01
#define USBD_AUDIO_SAMPLERATE           96000

#define USBD_SUB_FRAME_SIZE              0x04
/*------------------------------------------------------------------------------*/
/*  CDC Interface                                                               */
/*------------------------------------------------------------------------------*/

#define USBD_CDC_CS_IF_DESC_TYPE        USB_CS_INTERFACE_TYPE

#define USBD_CDC_HEADER_SIZE            5
#define USBD_CDC_ACM_SIZE               4
#define USBD_CDC_UNION_SIZE             5
#define USBD_CDC_CALL_MAN_SIZE          5

#define USBD_CDC_CONTROL_ENDPOINTS      0x01
#define USBD_CDC_DATA_ENDPOINTS         0x02

#define USBD_CDC_SIZE                   (2 * USB_INTERFACE_DESC_SIZE) + \
                                        USBD_CDC_HEADER_SIZE + \
                                        USBD_CDC_CALL_MAN_SIZE + \
                                        USBD_CDC_ACM_SIZE + \
                                        USBD_CDC_UNION_SIZE + \
                                        (3 * USB_ENDPOINT_DESC_SIZE)


#define USBD_CDC_HEADER_SUBTYPE         0x00
#define USBD_CDC_ACM_CLASS               0x02
#define USBD_CDC_ACM_SUBCLASS            0x02
#define USBD_CDC_ACM_PROTOCOL           0x01

#define USBD_CDC_DATA_CLASS              0x0A
#define USBD_CDC_DATA_SUBCLASS           0x00
#define USBD_CDC_DATA_PROTOCOL          0x00

#define USBD_CDC_UNION_SUBTYPE          0x06
#define USBD_CDC_CALL_MAN_SUBTYPE       0x01

#define CDC_SET_LINE_CODING             0x20
#define CDC_GET_LINE_CODING             0x21

#define USBD_CDC_EP_INTERVAL            0x0A
#define USBD_CDC_DATA_INTERVAL          0x00

/*------------------------------------------------------------------------------*/
/*  Functions                                                                   */
/*------------------------------------------------------------------------------*/

uint8_t *usbd_get_dev_desc(uint16_t *length);
uint8_t *usbd_get_cfg_desc(uint8_t cfg_no, uint16_t *length);
uint8_t *usbd_get_langid_str(uint16_t *length);
uint8_t *usbd_get_mfc_str(uint16_t *length);
uint8_t *usbd_get_prod_str(uint16_t *length);
uint8_t *usbd_get_serial_str(uint16_t *length);
uint8_t *usbd_get_cfg_str(uint16_t *length);
uint8_t *usbd_get_midi_if_str(uint16_t *length);
uint8_t *usbd_get_cdc_if_str(uint16_t *length);

#endif /* USB_DESC_H_ */
