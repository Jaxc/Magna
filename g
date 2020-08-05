[1mdiff --git a/docs/frmts10.pdf b/docs/frmts10.pdf[m
[1mnew file mode 100644[m
[1mindex 0000000..0664d66[m
Binary files /dev/null and b/docs/frmts10.pdf differ
[1mdiff --git a/magda.txt b/magda.txt[m
[1mdeleted file mode 100644[m
[1mindex 9cff800..0000000[m
[1m--- a/magda.txt[m
[1m+++ /dev/null[m
[36m@@ -1,171 +0,0 @@[m
[31m-[m
[31m-Bus 001 Device 061: ID 0483:5740 STMicroelectronics Virtual COM Port[m
[31m-Device Descriptor:[m
[31m-  bLength                18[m
[31m-  bDescriptorType         1[m
[31m-  bcdUSB               2.00[m
[31m-  bDeviceClass            0 (Defined at Interface level)[m
[31m-  bDeviceSubClass         0 [m
[31m-  bDeviceProtocol         0 [m
[31m-  bMaxPacketSize0        64[m
[31m-  idVendor           0x0483 STMicroelectronics[m
[31m-  idProduct          0x5740 Virtual COM Port[m
[31m-  bcdDevice            0.01[m
[31m-  iManufacturer           1 Skrooter Audio[m
[31m-  iProduct                2 Magna DJ Mixer[m
[31m-  iSerial                 3 00000000001A[m
[31m-  bNumConfigurations      1[m
[31m-  Configuration Descriptor:[m
[31m-    bLength                 9[m
[31m-    bDescriptorType         2[m
[31m-    wTotalLength          127[m
[31m-    bNumInterfaces          3[m
[31m-    bConfigurationValue     1[m
[31m-    iConfiguration          4 Magna Config[m
[31m-    bmAttributes         0xc0[m
[31m-      Self Powered[m
[31m-    MaxPower              100mA[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        0[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass         2 Communications[m
[31m-      bInterfaceSubClass      2 Abstract (modem)[m
[31m-      bInterfaceProtocol      1 AT-commands (v.25ter)[m
[31m-      iInterface              6 Magna CDC Interface[m
[31m-      CDC Header:[m
[31m-        bcdCDC               1.10[m
[31m-      CDC Call Management:[m
[31m-        bmCapabilities       0x00[m
[31m-        bDataInterface          1[m
[31m-      CDC ACM:[m
[31m-        bmCapabilities       0x02[m
[31m-          line coding and serial state[m
[31m-      CDC Union:[m
[31m-        bMasterInterface        0[m
[31m-        bSlaveInterface         1 [m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x83  EP 3 IN[m
[31m-        bmAttributes            3[m
[31m-          Transfer Type            Interrupt[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0008  1x 8 bytes[m
[31m-        bInterval              10[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        1[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           2[m
[31m-      bInterfaceClass        10 CDC Data[m
[31m-      bInterfaceSubClass      0 Unused[m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              6 Magna CDC Interface[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x02  EP 2 OUT[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               0[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x82  EP 2 IN[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               0[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        0[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           4[m
[31m-      bInterfaceClass         1 Audio[m
[31m-      bInterfaceSubClass      2 Streaming[m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x83  EP 3 IN[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               1[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x84  EP 4 IN[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               1[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x03  EP 3 OUT[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               1[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x04  EP 4 OUT[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               1[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        0[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           2[m
[31m-      bInterfaceClass         1 Audio[m
[31m-      bInterfaceSubClass      3 MIDI Streaming[m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x85  EP 5 IN[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               1[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x85  EP 5 IN[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0040  1x 64 bytes[m
[31m-        bInterval               1[m
[31m-Device Status:     0x0003[m
[31m-  Self Powered[m
[31m-  Remote Wakeup Enabled[m
[1mdiff --git a/src/mixer_main.c b/src/mixer_main.c[m
[1mindex fc7c12d..16c4a1a 100644[m
[1m--- a/src/mixer_main.c[m
[1m+++ b/src/mixer_main.c[m
[36m@@ -34,7 +34,7 @@[m [mint main (void) {[m
     HAL_TIM_OC_Start(&htim4, TIM_CHANNEL_2);[m
     //HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);[m
 [m
[31m-    HAL_ADC_Start_DMA(&hadc1, adc_data, 8);[m
[32m+[m[32m    //HAL_ADC_Start_DMA(&hadc1, adc_data, 8);[m
     usbd_delay_ms(10000);[m
 [m
     while(1) {[m
[1mdiff --git a/ur22.txt b/ur22.txt[m
[1mdeleted file mode 100644[m
[1mindex 158506e..0000000[m
[1m--- a/ur22.txt[m
[1m+++ /dev/null[m
[36m@@ -1,480 +0,0 @@[m
[31m-[m
[31m-Bus 001 Device 063: ID 0499:170f Yamaha Corp. [m
[31m-Device Descriptor:[m
[31m-  bLength                18[m
[31m-  bDescriptorType         1[m
[31m-  bcdUSB               2.00[m
[31m-  bDeviceClass          239 Miscellaneous Device[m
[31m-  bDeviceSubClass         2 ?[m
[31m-  bDeviceProtocol         1 Interface Association[m
[31m-  bMaxPacketSize0        64[m
[31m-  idVendor           0x0499 Yamaha Corp.[m
[31m-  idProduct          0x170f [m
[31m-  bcdDevice            1.04[m
[31m-  iManufacturer           1 [m
[31m-  iProduct                2 [m
[31m-  iSerial                 0 [m
[31m-  bNumConfigurations      2[m
[31m-  Configuration Descriptor:[m
[31m-    bLength                 9[m
[31m-    bDescriptorType         2[m
[31m-    wTotalLength          292[m
[31m-    bNumInterfaces          4[m
[31m-    bConfigurationValue     1[m
[31m-    iConfiguration          0 [m
[31m-    bmAttributes         0xc0[m
[31m-      Self Powered[m
[31m-    MaxPower              500mA[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        1[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           0[m
[31m-      bInterfaceClass         1 Audio[m
[31m-      bInterfaceSubClass      2 Streaming[m
[31m-      bInterfaceProtocol     32 [m
[31m-      iInterface              0 [m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        1[m
[31m-      bAlternateSetting       1[m
[31m-      bNumEndpoints           2[m
[31m-      bInterfaceClass         1 Audio[m
[31m-      bInterfaceSubClass      2 Streaming[m
[31m-      bInterfaceProtocol     32 [m
[31m-      iInterface              0 [m
[31m-      AudioStreaming Interface Descriptor:[m
[31m-        bLength                16[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      1 (AS_GENERAL)[m
[31m-        bTerminalLink           1[m
[31m-        bmControls           0x00[m
[31m-        bFormatType             1[m
[31m-        bmFormats         0x00000001[m
[31m-          PCM[m
[31m-        bNrChannels             2[m
[31m-        bmChannelConfig   0x00000000[m
[31m-        iChannelNames           0 [m
[31m-      AudioStreaming Interface Descriptor:[m
[31m-        bLength                 6[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      2 (FORMAT_TYPE)[m
[31m-        bFormatType             1 (FORMAT_TYPE_I)[m
[31m-        bSubslotSize            4[m
[31m-        bBitResolution         24[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x03  EP 3 OUT[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x00c8  1x 200 bytes[m
[31m-        bInterval               1[m
[31m-        AudioControl Endpoint Descriptor:[m
[31m-          bLength                 8[m
[31m-          bDescriptorType        37[m
[31m-          bDescriptorSubtype      1 (EP_GENERAL)[m
[31m-          bmAttributes         0x00[m
[31m-          bmControls           0x00[m
[31m-          bLockDelayUnits         0 Undefined[m
[31m-          wLockDelay              0[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x83  EP 3 IN[m
[31m-        bmAttributes           17[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Feedback[m
[31m-        wMaxPacketSize     0x0004  1x 4 bytes[m
[31m-        bInterval               8[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        2[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           0[m
[31m-      bInterfaceClass         1 Audio[m
[31m-      bInterfaceSubClass      2 Streaming[m
[31m-      bInterfaceProtocol     32 [m
[31m-      iInterface              0 [m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        2[m
[31m-      bAlternateSetting       1[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass         1 Audio[m
[31m-      bInterfaceSubClass      2 Streaming[m
[31m-      bInterfaceProtocol     32 [m
[31m-      iInterface              0 [m
[31m-      AudioStreaming Interface Descriptor:[m
[31m-        bLength                16[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      1 (AS_GENERAL)[m
[31m-        bTerminalLink          20[m
[31m-        bmControls           0x00[m
[31m-        bFormatType             1[m
[31m-        bmFormats         0x00000001[m
[31m-          PCM[m
[31m-        bNrChannels             2[m
[31m-        bmChannelConfig   0x00000000[m
[31m-        iChannelNames           0 [m
[31m-      AudioStreaming Interface Descriptor:[m
[31m-        bLength                 6[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      2 (FORMAT_TYPE)[m
[31m-        bFormatType             1 (FORMAT_TYPE_I)[m
[31m-        bSubslotSize            4[m
[31m-        bBitResolution         24[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x81  EP 1 IN[m
[31m-        bmAttributes            5[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x00c8  1x 200 bytes[m
[31m-        bInterval               1[m
[31m-        AudioControl Endpoint Descriptor:[m
[31m-          bLength                 8[m
[31m-          bDescriptorType        37[m
[31m-          bDescriptorSubtype      1 (EP_GENERAL)[m
[31m-          bmAttributes         0x00[m
[31m-          bmControls           0x00[m
[31m-          bLockDelayUnits         0 Undefined[m
[31m-          wLockDelay              0[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        3[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           2[m
[31m-      bInterfaceClass         1 Audio[m
[31m-      bInterfaceSubClass      3 MIDI Streaming[m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      MIDIStreaming Interface Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      1 (HEADER)[m
[31m-        bcdADC               1.00[m
[31m-        wTotalLength           37[m
[31m-      MIDIStreaming Interface Descriptor:[m
[31m-        bLength                 6[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      2 (MIDI_IN_JACK)[m
[31m-        bJackType               1 Embedded[m
[31m-        bJackID                 1[m
[31m-        iJack                   0 [m
[31m-      MIDIStreaming Interface Descriptor:[m
[31m-        bLength                 6[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      2 (MIDI_IN_JACK)[m
[31m-        bJackType               2 External[m
[31m-        bJackID                 2[m
[31m-        iJack                   0 [m
[31m-      MIDIStreaming Interface Descriptor:[m
[31m-        bLength                 9[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      3 (MIDI_OUT_JACK)[m
[31m-        bJackType               1 Embedded[m
[31m-        bJackID                 3[m
[31m-        bNrInputPins            1[m
[31m-        baSourceID( 0)          2[m
[31m-        BaSourcePin( 0)         1[m
[31m-        iJack                   0 [m
[31m-      MIDIStreaming Interface Descriptor:[m
[31m-        bLength                 9[m
[31m-        bDescriptorType        36[m
[31m-        bDescriptorSubtype      3 (MIDI_OUT_JACK)[m
[31m-        bJackType               2 External[m
[31m-        bJackID                 4[m
[31m-        bNrInputPins            1[m
[31m-        baSourceID( 0)          1[m
[31m-        BaSourcePin( 0)         1[m
[31m-        iJack                   0 [m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 9[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x02  EP 2 OUT[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0200  1x 512 bytes[m
[31m-        bInterval               0[m
[31m-        bRefresh                0[m
[31m-        bSynchAddress           0[m
[31m-        MIDIStreaming Endpoint Descriptor:[m
[31m-          bLength                 5[m
[31m-          bDescriptorType        37[m
[31m-          bDescriptorSubtype      1 (GENERAL)[m
[31m-          bNumEmbMIDIJack         1[m
[31m-          baAssocJackID( 0)       1[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 9[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x85  EP 5 IN[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0200  1x 512 bytes[m
[31m-        bInterval               0[m
[31m-        bRefresh                0[m
[31m-        bSynchAddress           0[m
[31m-        MIDIStreaming Endpoint Descriptor:[m
[31m-          bLength                 5[m
[31m-          bDescriptorType        37[m
[31m-          bDescriptorSubtype      1 (GENERAL)[m
[31m-          bNumEmbMIDIJack         1[m
[31m-          baAssocJackID( 0)       3[m
[31m-  Configuration Descriptor:[m
[31m-    bLength                 9[m
[31m-    bDescriptorType         2[m
[31m-    wTotalLength          442[m
[31m-    bNumInterfaces          5[m
[31m-    bConfigurationValue     2[m
[31m-    iConfiguration          0 [m
[31m-    bmAttributes         0xc0[m
[31m-      Self Powered[m
[31m-    MaxPower              500mA[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        0[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           0[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      1 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  0a 24 01 00 01 34 00 02 01 02[m
[31m-      ** UNRECOGNIZED:  0c 24 02 01 01 01 00 02 03 00 00 00[m
[31m-      ** UNRECOGNIZED:  09 24 03 02 01 03 00 01 00[m
[31m-      ** UNRECOGNIZED:  0c 24 02 03 03 06 00 02 03 00 00 00[m
[31m-      ** UNRECOGNIZED:  09 24 03 04 01 01 00 03 00[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        1[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           0[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        1[m
[31m-      bAlternateSetting       1[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 01 01 01 00[m
[31m-      ** UNRECOGNIZED:  0e 24 02 01 02 04 18 02 44 ac 00 80 bb 00[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x01  EP 1 OUT[m
[31m-        bmAttributes           37[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Implicit feedback Data[m
[31m-        wMaxPacketSize     0x0038  1x 56 bytes[m
[31m-        bInterval               1[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        1[m
[31m-      bAlternateSetting       2[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 01 01 01 00[m
[31m-      ** UNRECOGNIZED:  0e 24 02 01 02 04 18 02 88 58 01 00 77 01[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x01  EP 1 OUT[m
[31m-        bmAttributes           37[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Implicit feedback Data[m
[31m-        wMaxPacketSize     0x0068  1x 104 bytes[m
[31m-        bInterval               1[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        1[m
[31m-      bAlternateSetting       3[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 01 01 01 00[m
[31m-      ** UNRECOGNIZED:  0e 24 02 01 02 04 18 02 10 b1 02 00 ee 02[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x01  EP 1 OUT[m
[31m-        bmAttributes           37[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Implicit feedback Data[m
[31m-        wMaxPacketSize     0x00c8  1x 200 bytes[m
[31m-        bInterval               1[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        2[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           0[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        2[m
[31m-      bAlternateSetting       1[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 04 01 01 00[m
[31m-      ** UNRECOGNIZED:  0e 24 02 01 02 04 18 02 44 ac 00 80 bb 00[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x81  EP 1 IN[m
[31m-        bmAttributes           37[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Implicit feedback Data[m
[31m-        wMaxPacketSize     0x0038  1x 56 bytes[m
[31m-        bInterval               1[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        2[m
[31m-      bAlternateSetting       2[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 04 01 01 00[m
[31m-      ** UNRECOGNIZED:  0e 24 02 01 02 04 18 02 88 58 01 00 77 01[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x81  EP 1 IN[m
[31m-        bmAttributes           37[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Implicit feedback Data[m
[31m-        wMaxPacketSize     0x0068  1x 104 bytes[m
[31m-        bInterval               1[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        2[m
[31m-      bAlternateSetting       3[m
[31m-      bNumEndpoints           1[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      2 [m
[31m-      bInterfaceProtocol      0 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 04 01 01 00[m
[31m-      ** UNRECOGNIZED:  0e 24 02 01 02 04 18 02 10 b1 02 00 ee 02[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x81  EP 1 IN[m
[31m-        bmAttributes           37[m
[31m-          Transfer Type            Isochronous[m
[31m-          Synch Type               Asynchronous[m
[31m-          Usage Type               Implicit feedback Data[m
[31m-        wMaxPacketSize     0x00c8  1x 200 bytes[m
[31m-        bInterval               1[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        3[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           2[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass      3 [m
[31m-      bInterfaceProtocol    255 [m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 00 01 24 00[m
[31m-      ** UNRECOGNIZED:  06 24 02 02 01 00[m
[31m-      ** UNRECOGNIZED:  09 24 03 02 01 01 01 01 00[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x02  EP 2 OUT[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0200  1x 512 bytes[m
[31m-        bInterval               0[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x85  EP 5 IN[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0200  1x 512 bytes[m
[31m-        bInterval               0[m
[31m-    Interface Descriptor:[m
[31m-      bLength                 9[m
[31m-      bDescriptorType         4[m
[31m-      bInterfaceNumber        4[m
[31m-      bAlternateSetting       0[m
[31m-      bNumEndpoints           2[m
[31m-      bInterfaceClass       255 Vendor Specific Class[m
[31m-      bInterfaceSubClass    255 Vendor Specific Subclass[m
[31m-      bInterfaceProtocol    255 Vendor Specific Protocol[m
[31m-      iInterface              0 [m
[31m-      ** UNRECOGNIZED:  07 24 01 00 01 24 00[m
[31m-      ** UNRECOGNIZED:  06 24 02 02 01 00[m
[31m-      ** UNRECOGNIZED:  09 24 03 02 01 01 01 01 00[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x04  EP 4 OUT[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0200  1x 512 bytes[m
[31m-        bInterval               0[m
[31m-      Endpoint Descriptor:[m
[31m-        bLength                 7[m
[31m-        bDescriptorType         5[m
[31m-        bEndpointAddress     0x84  EP 4 IN[m
[31m-        bmAttributes            2[m
[31m-          Transfer Type            Bulk[m
[31m-          Synch Type               None[m
[31m-          Usage Type               Data[m
[31m-        wMaxPacketSize     0x0200  1x 512 bytes[m
[31m-        bInterval               0[m
[1mdiff --git a/usbd/inc/usbd_magna_desc.h b/usbd/inc/usbd_magna_desc.h[m
[1mindex d439771..b041caf 100644[m
[1m--- a/usbd/inc/usbd_magna_desc.h[m
[1m+++ b/usbd/inc/usbd_magna_desc.h[m
[36m@@ -8,8 +8,9 @@[m
 /*------------------------------------------------------------------------------*/[m
 [m
 #define USBD_NUM_CONFIGS                1[m
[31m-#define USBD_NUM_INTERFACES             3[m
[31m-#define USBD_CFG_SIZE                   127[m
[32m+[m[32m#define USBD_NUM_INTERFACES             2[m
[32m+[m[32m#define USBD_CFG_SIZE                   (USB_CONFIG_DESC_SIZE + USB_AUDIO_BLOCK_SIZE)[m
[32m+[m[32m/*136 */[m
 [m
 #define USB_DEVICE_DESC_TYPE            1[m
 #define USB_CONFIG_DESC_TYPE            2[m
[36m@@ -17,6 +18,7 @@[m
 #define USB_INTERFACE_DESC_TYPE         4[m
 #define USB_ENDPOINT_DESC_TYPE          5[m
 #define USB_DEVICE_QUALIFIER_DESC_TYPE  6[m
[32m+[m
 #define USB_LANGID_DESC_TYPE            USB_STRING_DESC_TYPE[m
 #define USB_IAD_DESC_TYPE               0x0b[m
 #define USB_BOS_DESC_TYPE               0x0f[m
[36m@@ -30,9 +32,13 @@[m
 #define MAGNA_VERSION                   0x0001[m
 [m
 #define USB_DEVICE_DESC_SIZE            18[m
[32m+[m[32m#define USB_TERMINAL_DESC_SIZE          12[m
 #define USB_CONFIG_DESC_SIZE            9[m
 #define USB_INTERFACE_DESC_SIZE         9[m
[32m+[m[32m#define USB_AUDIO_CONTROL_SIZE          10[m
 #define USB_ENDPOINT_DESC_SIZE          7[m
[32m+[m[32m#define USB_AS_GENERAL_SIZE             7[m
[32m+[m[32m#define USB_TYPE_1_FORMAT               11[m
 #define USB_LANGID_DESC_SIZE            4[m
 #define USB_IAD_DESC_SIZE               8[m
 [m
[36m@@ -47,12 +53,79 @@[m
 #define USB_LANGID_ENG_US               0x0409[m
 [m
 #define USB_CONFIG_REMOTE_WAKEUP        0x02[m
[31m-#define USB_CONFIG_SELF_POWERED         0x01[m
[32m+[m[32m#define USB_CONFIG_SELF_POWERED         0x40[m
[32m+[m[32m#define USB_CONFIG_ATTRIBUTES           USB_CONFIG_SELF_POWERED | 0x80[m
[32m+[m
[32m+[m[32m#define USB_CONFIG_VALUE                0x01[m
[32m+[m[32m#define USB_CONFIG_MAXPOWER             0x32[m
 [m
 #define USB_FEATURE_EP_HALT             0[m
 #define USB_FEATURE_REMOTE_WAKEUP       1[m
 #define USB_FEATURE_TEST_MODE           2[m
 [m
[32m+[m[32m#define USB_INTERFACE_ALT_0             0x00[m
[32m+[m[32m#define USB_INTERFACE_ALT_1             0x01[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_CONTROL_INTERFACE    0x00[m
[32m+[m[32m#define USBD_AUDIO_INTERFACE            0x01[m
[32m+[m[32m#define USBD_AUDIO_INTERFACE2           0x02[m
[32m+[m[32m#define USBD_CDC_CONTROL_INTERFACE      0x03[m
[32m+[m[32m#define USBD_CDC_DATA_INTERFACE         0x04[m
[32m+[m[32m#define UDBD_MIDI_INTERFACE             0x05[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_CLASS                0x01[m
[32m+[m
[32m+[m[32m#define USB_AUDIO_CONTROL_SUBCLASS      0x01[m
[32m+[m[32m#define USB_AUDIOSTREAMING_SUBCLASS     0x02[m
[32m+[m[32m#define USB_MIDISTREAMING_SUBCLASS      0x03[m
[32m+[m
[32m+[m[32m#define USB_AUDIO_PROTOCOL              0x00[m
[32m+[m
[32m+[m[32m#define USB_GENERAL_SUBTYPE             0x01[m
[32m+[m[32m#define USB_FORMAT_TYPE_SUBTYPE         0x02[m
[32m+[m
[32m+[m[32m#define USB_FORMAT_TYPE_1               0x01[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_FORMAT_PCM           0x0001[m
[32m+[m
[32m+[m[32m/*------------------------------------------------------------------------------*/[m
[32m+[m[32m/*  AUDIO control interface                                                              */[m
[32m+[m[32m/*------------------------------------------------------------------------------*/[m
[32m+[m
[32m+[m[32m#define USBD_AC_HEADER                  0x01[m
[32m+[m[32m#define USBD_AC_BCD_VER                 0x0100[m
[32m+[m[32m#define USBD_AC_SIZE                    (2*(USB_INTERFACE_DESC_SIZE + USB_TERMINAL_DESC_SIZE) \[m
[32m+[m[32m                                         + USB_AUDIO_CONTROL_SIZE)[m
[32m+[m[32m#define USBD_AC_BLOCK_SIZE              USBD_AC_SIZE + USB_INTERFACE_DESC_SIZE[m
[32m+[m
[32m+[m[32m#define USB_AC_INPUT_TERMINAL           0x02[m
[32m+[m[32m#define USB_AC_OUTPUT_TERMINAL          0x03[m
[32m+[m
[32m+[m[32m#define USB_AC_INPUT_LINE_1_ID          0x01[m
[32m+[m[32m#define USB_AC_INPUT_USB_ID             0x02[m
[32m+[m[32m#define USB_AC_OUTPUT_USB_ID            0x03[m
[32m+[m[32m#define USB_AC_OUTPUT_MASTER_ID         0x04[m
[32m+[m
[32m+[m[32m#define USB_AC_TERMINAL_LINE            0x0603[m
[32m+[m[32m#define USB_AC_TERMINAL_USB             0x0101[m
[32m+[m[32m#define USB_AC_INPUT_ASSOC              0x00[m
[32m+[m[32m#define USB_AC_INPUT_CHANNELS           0x02[m
[32m+[m[32m#define USB_AC_INPUT_CHANNEL_CFG        0x0003[m
[32m+[m[32m#define USB_AC_OUTPUT_SOURCE_ID         0x01[m
[32m+[m
[32m+[m[32m#define USBD_ENDPOINT_0_SIZE            (USB_ENDPOINT_DESC_SIZE + USB_AS_GENERAL_SIZE)[m
[32m+[m[32m#define USBD_ENDPOINT_1_SIZE            (USB_ENDPOINT_DESC_SIZE + USB_AS_GENERAL_SIZE)[m
[32m+[m[32m#define USBD_ENDPOINT_2_SIZE            (USB_ENDPOINT_DESC_SIZE + USB_AS_GENERAL_SIZE)[m
[32m+[m[32m#define USBD_ENDPOINT_3_SIZE            (USB_ENDPOINT_DESC_SIZE)[m
[32m+[m[32m#define USBD_ENPOINTS_SIZE              (USBD_ENDPOINT_0_SIZE + USBD_ENDPOINT_1_SIZE \[m
[32m+[m[32m                                        + USBD_ENDPOINT_2_SIZE + USBD_ENDPOINT_3_SIZE)[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_INTERFACE_SIZE       (2 * USB_INTERFACE_DESC_SIZE + USB_AS_GENERAL_SIZE \[m
[32m+[m[32m                                        + USB_TYPE_1_FORMAT)[m
[32m+[m
[32m+[m[32m#define USB_AUDIO_BLOCK_SIZE            (USBD_AC_BLOCK_SIZE + USBD_ENPOINTS_SIZE \[m
[32m+[m[32m                                        + 2 * USBD_AUDIO_INTERFACE_SIZE)[m
[32m+[m
 /*------------------------------------------------------------------------------*/[m
 /*  MIDI Interface                                                              */[m
 /*------------------------------------------------------------------------------*/[m
[36m@@ -80,6 +153,29 @@[m
 #define USBD_MIDI_JACK_EMBEDDED         0x01[m
 #define USBD_MIDI_JACK_EXTERNAL         0x02[m
 [m
[32m+[m[32m#define USBD_AUDIO_CONTROL_EP           0x00[m
[32m+[m[32m#define USBD_AUDIOSTREAM_EP             0x04[m
[32m+[m[32m#define USBD_MIDI_EP                    0x02[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_IN_CHN1              0x81[m
[32m+[m[32m#define USBD_AUDIO_IN_CHN2              0x82[m
[32m+[m[32m#define USBD_AUDIO_MASTER               0x01[m
[32m+[m[32m#define USBD_AUDIO_PHONES               0x02[m
[32m+[m
[32m+[m[32m#define USBD_MIDI_IN                    0x85[m
[32m+[m[32m#define USBD_MIDI_OUT                   0x05[m
[32m+[m
[32m+[m[32m#define USDB_AUDIO_ASYNC                USBD_EP_ISOC_TYPE | 0x4[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_INTERVAL             0x01[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_DELAY                0x01[m
[32m+[m
[32m+[m[32m#define USBD_AUDIO_RESOLUTION           24[m
[32m+[m[32m#define USBD_N_AUDIO_SAMPLERATE         0x01[m
[32m+[m[32m#define USBD_AUDIO_SAMPLERATE           96000[m
[32m+[m
[32m+[m[32m#define USBD_SUB_FRAME_SIZE              0x04[m
 /*------------------------------------------------------------------------------*/[m
 /*  CDC Interface                                                               */[m
 /*------------------------------------------------------------------------------*/[m
[36m@@ -91,6 +187,9 @@[m
 #define USBD_CDC_UNION_SIZE             5[m
 #define USBD_CDC_CALL_MAN_SIZE          5[m
 [m
[32m+[m[32m#define USBD_CDC_CONTROL_ENDPOINTS      0x01[m
[32m+[m[32m#define USBD_CDC_DATA_ENDPOINTS         0x02[m
[32m+[m
 #define USBD_CDC_SIZE                   (2 * USB_INTERFACE_DESC_SIZE) + \[m
                                         USBD_CDC_HEADER_SIZE + \[m
                                         USBD_CDC_CALL_MAN_SIZE + \[m
[36m@@ -100,13 +199,23 @@[m
 [m
 [m
 #define USBD_CDC_HEADER_SUBTYPE         0x00[m
[31m-#define USBD_CDC_ACM_SUBTYPE            0x02[m
[32m+[m[32m#define USBD_CDC_ACM_CLASS               0x02[m
[32m+[m[32m#define USBD_CDC_ACM_SUBCLASS            0x02[m
[32m+[m[32m#define USBD_CDC_ACM_PROTOCOL           0x01[m
[32m+[m
[32m+[m[32m#define USBD_CDC_DATA_CLASS              0x0A[m
[32m+[m[32m#define USBD_CDC_DATA_SUBCLASS           0x00[m
[32m+[m[32m#define USBD_CDC_DATA_PROTOCOL          0x00[m
[32m+[m
 #define USBD_CDC_UNION_SUBTYPE          0x06[m
 #define USBD_CDC_CALL_MAN_SUBTYPE       0x01[m
 [m
 #define CDC_SET_LINE_CODING             0x20[m
 #define CDC_GET_LINE_CODING             0x21[m
 [m
[32m+[m[32m#define USBD_CDC_EP_INTERVAL            0x0A[m
[32m+[m[32m#define USBD_CDC_DATA_INTERVAL          0x00[m
[32m+[m
 /*------------------------------------------------------------------------------*/[m
 /*  Functions                                                                   */[m
 /*------------------------------------------------------------------------------*/[m
[1mdiff --git a/usbd/src/usbd_magna_desc.c b/usbd/src/usbd_magna_desc.c[m
[1mindex 8c292db..cae04d2 100644[m
[1m--- a/usbd/src/usbd_magna_desc.c[m
[1m+++ b/usbd/src/usbd_magna_desc.c[m
[36m@@ -43,182 +43,360 @@[m [mstatic uint8_t usbd_magna_cfg_desc[USBD_CFG_SIZE] = {[m
     LOBYTE(USBD_CFG_SIZE),              /* wTotalLength:no of returned bytes */[m
     HIBYTE(USBD_CFG_SIZE),[m
     USBD_NUM_INTERFACES,                /* bNumInterfaces: 4 interface */[m
[31m-    0x01,                               /* bConfigurationValue: Configuration value */[m
[32m+[m[32m    USB_CONFIG_VALUE,                   /* bConfigurationValue: Configuration value */[m
     USBD_IDX_CONFIG_STR,                /* iConfiguration: Index of string descriptor describing the configuration */[m
[31m-    0xC0,                               /* bmAttributes: self powered */[m
[31m-    0x32,                               /* MaxPower 0 mA */[m
[32m+[m[32m    USB_CONFIG_ATTRIBUTES,              /* bmAttributes: self powered */[m
[32m+[m[32m    USB_CONFIG_MAXPOWER,                /* MaxPower 100 mA */[m
[32m+[m
[32m+[m
 [m
 /*---------------------------------------------------------------------------*/[m
[31m-/*  CDC Interface                                                            */[m
[32m+[m[32m/*  Audio interface                                                           */[m
 /*---------------------------------------------------------------------------*/[m
 [m
[31m-    /*Interface Descriptor */[m
[32m+[m[32m/* Audio control interface*/[m
[32m+[m[32m    USB_INTERFACE_DESC_SIZE,[m
[32m+[m[32m    USB_INTERFACE_DESC_TYPE,[m
[32m+[m[32m    USBD_AUDIO_CONTROL_INTERFACE,[m
[32m+[m[32m    USB_INTERFACE_ALT_0,[m
[32m+[m[32m    USBD_AUDIO_CONTROL_EP,[m
[32m+[m[32m    USBD_AUDIO_CLASS,[m
[32m+[m[32m    USB_AUDIO_CONTROL_SUBCLASS,[m
[32m+[m[32m    USB_AUDIO_PROTOCOL,[m
[32m+[m[32m    0x00,[m
[32m+[m
[32m+[m[32m    /* Audio control descriptor*/[m
[32m+[m[32m    USB_AUDIO_CONTROL_SIZE,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USBD_AC_HEADER,[m
[32m+[m[32m    LOBYTE(USBD_AC_BCD_VER),[m
[32m+[m[32m    HIBYTE(USBD_AC_BCD_VER),[m
[32m+[m[32m    LOBYTE(USBD_AC_SIZE),[m
[32m+[m[32m    HIBYTE(USBD_AC_SIZE),[m
[32m+[m[32m    0x02,[m
[32m+[m[32m    0x01,[m
[32m+[m[32m    0x02,[m
[32m+[m
[32m+[m[32m    /* Audio control Terminal input analogue*/[m
[32m+[m[32m    USB_TERMINAL_DESC_SIZE,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_AC_INPUT_TERMINAL,[m
[32m+[m[32m    USB_AC_INPUT_LINE_1_ID,[m
[32m+[m[32m    LOBYTE(USB_AC_TERMINAL_LINE),[m
[32m+[m[32m    HIBYTE(USB_AC_TERMINAL_LINE),[m
[32m+[m[32m    USB_AC_INPUT_ASSOC,[m
[32m+[m[32m    USB_AC_INPUT_CHANNELS,[m
[32m+[m[32m    LOBYTE(USB_AC_INPUT_CHANNEL_CFG),[m
[32m+[m[32m    HIBYTE(USB_AC_INPUT_CHANNEL_CFG),[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m
[32m+[m[32m    /* Audio control Terminal Output USB*/[m
[32m+[m[32m    USB_INTERFACE_DESC_SIZE,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_AC_OUTPUT_TERMINAL,[m
[32m+[m[32m    USB_AC_OUTPUT_USB_ID,[m
[32m+[m[32m    LOBYTE(USB_AC_TERMINAL_USB),[m
[32m+[m[32m    HIBYTE(USB_AC_TERMINAL_USB),[m
[32m+[m[32m    USB_AC_INPUT_ASSOC,[m
[32m+[m[32m    USB_AC_OUTPUT_SOURCE_ID,[m
[32m+[m[32m    0x00,[m
[32m+[m
[32m+[m[32m    /* Audio control Terminal input USB */[m
[32m+[m[32m    USB_TERMINAL_DESC_SIZE,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_AC_INPUT_TERMINAL,[m
[32m+[m[32m    USB_AC_INPUT_USB_ID,[m
[32m+[m[32m    LOBYTE(USB_AC_TERMINAL_USB),[m
[32m+[m[32m    HIBYTE(USB_AC_TERMINAL_USB),[m
[32m+[m[32m    USB_AC_INPUT_ASSOC,[m
[32m+[m[32m    USB_AC_INPUT_CHANNELS,[m
[32m+[m[32m    LOBYTE(USB_AC_INPUT_CHANNEL_CFG),[m
[32m+[m[32m    HIBYTE(USB_AC_INPUT_CHANNEL_CFG),[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m
[32m+[m[32m    /* Audio control Terminal Output analogue*/[m
[32m+[m[32m    USB_INTERFACE_DESC_SIZE,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_AC_OUTPUT_TERMINAL,[m
[32m+[m[32m    USB_AC_OUTPUT_MASTER_ID,[m
[32m+[m[32m    LOBYTE(USB_AC_TERMINAL_LINE),[m
[32m+[m[32m    HIBYTE(USB_AC_TERMINAL_LINE),[m
[32m+[m[32m    USB_AC_INPUT_ASSOC,[m
[32m+[m[32m    USB_AC_INPUT_USB_ID,[m
[32m+[m[32m    0x00,[m
[32m+[m
[32m+[m[32m/*Interface No EP Descriptor */[m
     USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */[m
     USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */[m
[31m-    0x00,                               /* bInterfaceNumber: Number of Interface */[m
[31m-    0x00,                               /* bAlternateSetting: Alternate setting */[m
[31m-    0x01,                               /* bNumEndpoints: One endpoints used */[m
[31m-    0x02,                               /* bInterfaceClass: Communication Interface Class */[m
[31m-    0x02,                               /* bInterfaceSubClass: Abstract Control Model */[m
[31m-    0x01,                               /* bInterfaceProtocol: Common AT commands */[m
[31m-    0x06,                /* iInterface: */[m
[31m-[m
[31m-    /*Header Functional Descriptor*/[m
[31m-    USBD_CDC_HEADER_SIZE,               /* bLength: Endpoint Descriptor size */[m
[31m-    USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[31m-    0x00,                               /* bDescriptorSubtype: Header Func Desc */[m
[31m-    0x10,                               /* bcdCDC: spec release number */[m
[31m-    0x01,[m
[32m+[m[32m    USBD_AUDIO_INTERFACE,                               /* bInterfaceNumber: Number of Interface */[m
[32m+[m[32m    USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */[m
[32m+[m[32m    USBD_AUDIO_CONTROL_EP,                               /* bNumEndpoints: One endpoints used */[m
[32m+[m[32m    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */[m
[32m+[m[32m    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */[m
[32m+[m[32m    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */[m
[32m+[m[32m    0x00,                /* iInterface: */[m
 [m
[31m-    /*Call Management Functional Descriptor*/[m
[31m-    USBD_CDC_CALL_MAN_SIZE,             /* bFunctionLength */[m
[31m-    USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[31m-    0x01,                               /* bDescriptorSubtype: Call Management Func Desc */[m
[31m-    0x00,                               /* bmCapabilities: D0+D1 */[m
[31m-    0x01,                               /* bDataInterface: 1 */[m
[31m-[m
[31m-    /*ACM Functional Descriptor*/[m
[31m-    USBD_CDC_ACM_SIZE,                  /* bFunctionLength */[m
[31m-    USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[31m-    0x02,                               /* bDescriptorSubtype: Abstract Control Management desc */[m
[31m-    0x02,                               /* bmCapabilities */[m
[31m-[m
[31m-    /*Union Functional Descriptor*/[m
[31m-    USBD_CDC_UNION_SIZE,                /* bFunctionLength */[m
[31m-    USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[31m-    0x06,                               /* bDescriptorSubtype: Union func desc */[m
[31m-    0x00,                               /* bMasterInterface: Communication class interface */[m
[31m-    0x01,                               /* bSlaveInterface0: Data Class Interface */[m
[32m+[m[32m/*Interface Descriptor */[m
[32m+[m[32m    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */[m
[32m+[m[32m    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */[m
[32m+[m[32m    USBD_AUDIO_INTERFACE,                               /* bInterfaceNumber: Number of Interface */[m
[32m+[m[32m    USB_INTERFACE_ALT_1,                               /* bAlternateSetting: Alternate setting */[m
[32m+[m[32m    USBD_AUDIOSTREAM_EP,                               /* bNumEndpoints: One endpoints used */[m
[32m+[m[32m    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */[m
[32m+[m[32m    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */[m
[32m+[m[32m    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */[m
[32m+[m[32m    0x00,                /* iInterface: */[m
 [m
[31m-    /*Endpoint 2 Descriptor*/[m
[31m-    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
[31m-    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    USBD_EP_CDC_CMD,                    /* bEndpointAddress */[m
[31m-    0x03,                               /* bmAttributes: Interrupt */[m
[31m-    LOBYTE(USBD_INT_PACKET_SIZE),        /* wMaxPacketSize: */[m
[31m-    HIBYTE(USBD_INT_PACKET_SIZE),[m
[31m-    0x0A,                               /* bInterval: */[m
[32m+[m[32m    /* Class-specific AS General Interface Descriptor */[m
[32m+[m[32m    USB_AS_GENERAL_SIZE,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_GENERAL_SUBTYPE,[m
[32m+[m[32m    USB_AC_INPUT_USB_ID,[m
[32m+[m[32m    USBD_AUDIO_DELAY,[m
[32m+[m[32m    LOBYTE(USBD_AUDIO_FORMAT_PCM),[m
[32m+[m[32m    HIBYTE(USBD_AUDIO_FORMAT_PCM),[m
[32m+[m
[32m+[m[32m    /* Type I Format Type Descriptor */[m
[32m+[m[32m    USB_TYPE_1_FORMAT,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_FORMAT_TYPE_SUBTYPE,[m
[32m+[m[32m    USB_FORMAT_TYPE_1,[m
[32m+[m[32m    USB_AC_INPUT_CHANNELS,[m
[32m+[m[32m    USBD_SUB_FRAME_SIZE,[m
[32m+[m[32m    USBD_AUDIO_RESOLUTION,[m
[32m+[m[32m    USBD_N_AUDIO_SAMPLERATE,[m
[32m+[m[32m    LOBYTE(USBD_AUDIO_SAMPLERATE),[m
[32m+[m[32m    HIBYTE(USBD_AUDIO_SAMPLERATE),[m
[32m+[m[32m    LOBYTE(USBD_AUDIO_SAMPLERATE >> 16),[m
 [m
[31m-/*---------------------------------------------------------------------------*/[m
 [m
[31m-    /*Data class interface descriptor*/[m
[31m-    USB_INTERFACE_DESC_SIZE,            /* bLength: Endpoint Descriptor size */[m
[31m-    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: */[m
[31m-    0x01,                               /* bInterfaceNumber: Number of Interface */[m
[31m-    0x00,                               /* bAlternateSetting: Alternate setting */[m
[31m-    0x02,                               /* bNumEndpoints: Two endpoints used */[m
[31m-    0x0A,                               /* bInterfaceClass: CDC */[m
[31m-    0x00,                               /* bInterfaceSubClass: */[m
[31m-    0x00,                               /* bInterfaceProtocol: */[m
[31m-    USBD_IDX_CDC_IF_STR,                /* iInterface: */[m
[31m-[m
[31m-    /*Endpoint OUT Descriptor*/[m
[32m+[m[32m    /*Endpoint 0 Descriptor*/[m
     USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
     USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    USBD_EP_CDC_RX,                     /* bEndpointAddress */[m
[31m-    0x02,                               /* bmAttributes: Bulk */[m
[31m-    LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */[m
[32m+[m[32m    USBD_AUDIO_IN_CHN1,                    /* bEndpointAddress */[m
[32m+[m[32m    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */[m
[32m+[m[32m    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
     HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x00,                               /* bInterval: ignore for Bulk transfer */[m
[32m+[m[32m    USBD_AUDIO_INTERVAL,                               /* bInterval: */[m
[32m+[m
[32m+[m[32m    /* Class-specific Isochronous Audio Data Endpoint Descriptor */[m
[32m+[m[32m    USB_AS_GENERAL_SIZE,[m
[32m+[m[32m    USB_CS_ENDPOINT_TYPE,[m
[32m+[m[32m    USB_GENERAL_SUBTYPE,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m
 [m
[31m-    /*Endpoint IN Descriptor*/[m
[32m+[m[32m    /*Endpoint 1 Descriptor*/[m
     USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
     USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    USBD_EP_CDC_TX,                     /* bEndpointAddress */[m
[31m-    0x02,                               /* bmAttributes: Bulk */[m
[31m-    LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */[m
[32m+[m[32m    USBD_AUDIO_IN_CHN2,                    /* bEndpointAddress */[m
[32m+[m[32m    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */[m
[32m+[m[32m    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
     HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x00,                               /* bInterval: ignore for Bulk transfer */[m
[31m-[m
[31m-/*---------------------------------------------------------------------------*/[m
[31m-/*  Audio interface                                                           */[m
[31m-/*---------------------------------------------------------------------------*/[m
[32m+[m[32m    USBD_AUDIO_INTERVAL,                               /* bInterval: */[m
[32m+[m
[32m+[m[32m    /* Class-specific Isochronous Audio Data Endpoint Descriptor */[m
[32m+[m[32m    USB_AS_GENERAL_SIZE,[m
[32m+[m[32m    USB_CS_ENDPOINT_TYPE,[m
[32m+[m[32m    USB_GENERAL_SUBTYPE,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m
[32m+[m[32m/*Interface No EP Descriptor */[m
[32m+[m[32m    USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */[m
[32m+[m[32m    USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */[m
[32m+[m[32m    USBD_AUDIO_INTERFACE2,                               /* bInterfaceNumber: Number of Interface */[m
[32m+[m[32m    USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */[m
[32m+[m[32m    USBD_AUDIO_CONTROL_EP,                               /* bNumEndpoints: One endpoints used */[m
[32m+[m[32m    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */[m
[32m+[m[32m    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */[m
[32m+[m[32m    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */[m
[32m+[m[32m    0x00,                /* iInterface: */[m
 [m
[31m-    /*Interface Descriptor */[m
[32m+[m[32m/*Interface Descriptor */[m
     USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */[m
     USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */[m
[31m-    0x02,                               /* bInterfaceNumber: Number of Interface */[m
[31m-    0x00,                               /* bAlternateSetting: Alternate setting */[m
[31m-    0x04,                               /* bNumEndpoints: One endpoints used */[m
[31m-    0x01,                               /* bInterfaceClass: Communication Interface Class */[m
[31m-    0x02,                               /* bInterfaceSubClass: Abstract Control Model */[m
[31m-    0x00,                               /* bInterfaceProtocol: Common AT commands */[m
[32m+[m[32m    USBD_AUDIO_INTERFACE2,                               /* bInterfaceNumber: Number of Interface */[m
[32m+[m[32m    USB_INTERFACE_ALT_1,                               /* bAlternateSetting: Alternate setting */[m
[32m+[m[32m    USBD_AUDIOSTREAM_EP,                               /* bNumEndpoints: One endpoints used */[m
[32m+[m[32m    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */[m
[32m+[m[32m    USB_AUDIOSTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */[m
[32m+[m[32m    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */[m
     0x00,                /* iInterface: */[m
 [m
[31m-    /*Endpoint 0 Descriptor*/[m
[31m-    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
[31m-    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    0x83,                    /* bEndpointAddress */[m
[31m-    0x05,                               /* bmAttributes: Interrupt */[m
[31m-    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
[31m-    HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x01,                               /* bInterval: */[m
[32m+[m[32m    /* Class-specific AS General Interface Descriptor */[m
[32m+[m[32m    USB_AS_GENERAL_SIZE,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_GENERAL_SUBTYPE,[m
[32m+[m[32m    USB_AC_INPUT_USB_ID,[m
[32m+[m[32m    USBD_AUDIO_DELAY,[m
[32m+[m[32m    LOBYTE(USBD_AUDIO_FORMAT_PCM),[m
[32m+[m[32m    HIBYTE(USBD_AUDIO_FORMAT_PCM),[m
[32m+[m
[32m+[m[32m    /* Type I Format Type Descriptor */[m
[32m+[m[32m    USB_TYPE_1_FORMAT,[m
[32m+[m[32m    USB_CS_INTERFACE_TYPE,[m
[32m+[m[32m    USB_FORMAT_TYPE_SUBTYPE,[m
[32m+[m[32m    USB_FORMAT_TYPE_1,[m
[32m+[m[32m    USB_AC_INPUT_CHANNELS,[m
[32m+[m[32m    USBD_SUB_FRAME_SIZE,[m
[32m+[m[32m    USBD_AUDIO_RESOLUTION,[m
[32m+[m[32m    USBD_N_AUDIO_SAMPLERATE,[m
[32m+[m[32m    LOBYTE(USBD_AUDIO_SAMPLERATE),[m
[32m+[m[32m    HIBYTE(USBD_AUDIO_SAMPLERATE),[m
[32m+[m[32m    LOBYTE(USBD_AUDIO_SAMPLERATE >> 16),[m
 [m
[31m-    /*Endpoint 1 Descriptor*/[m
[31m-    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
[31m-    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    0x84,                    /* bEndpointAddress */[m
[31m-    0x05,                               /* bmAttributes: Interrupt */[m
[31m-    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
[31m-    HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x01,                               /* bInterval: */[m
 [m
     /*Endpoint 2 Descriptor*/[m
     USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
     USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    0x03,                    /* bEndpointAddress */[m
[31m-    0x05,                               /* bmAttributes: Interrupt */[m
[32m+[m[32m    USBD_AUDIO_MASTER,                    /* bEndpointAddress */[m
[32m+[m[32m    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */[m
     LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
     HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x01,                               /* bInterval: */[m
[32m+[m[32m    USBD_AUDIO_INTERVAL,                               /* bInterval: */[m
[32m+[m
[32m+[m[32m    /* Class-specific Isochronous Audio Data Endpoint Descriptor */[m
[32m+[m[32m    USB_AS_GENERAL_SIZE,[m
[32m+[m[32m    USB_CS_ENDPOINT_TYPE,[m
[32m+[m[32m    USB_GENERAL_SUBTYPE,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
[32m+[m[32m    0x00,[m
 [m
     /*Endpoint 3 Descriptor*/[m
     USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
     USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    0x04,                    /* bEndpointAddress */[m
[31m-    0x05,                               /* bmAttributes: Interrupt */[m
[32m+[m[32m    USBD_AUDIO_PHONES,                    /* bEndpointAddress */[m
[32m+[m[32m    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */[m
     LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
     HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x01,                               /* bInterval: */[m
[32m+[m[32m    USBD_AUDIO_INTERVAL,                               /* bInterval: */[m
 [m
[32m+[m[32m#if 0[m
[32m+[m[32m/*---------------------------------------------------------------------------*/[m
[32m+[m[32m/*  MIDI interface                                                           */[m
 /*---------------------------------------------------------------------------*/[m
 [m
     USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */[m
     USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */[m
[31m-    0x03,                               /* bInterfaceNumber: Number of Interface */[m
[31m-    0x00,                               /* bAlternateSetting: Alternate setting */[m
[31m-    0x02,                               /* bNumEndpoints: One endpoints used */[m
[31m-    0x01,                               /* bInterfaceClass: Communication Interface Class */[m
[31m-    0x03,                               /* bInterfaceSubClass: Abstract Control Model */[m
[31m-    0x00,                               /* bInterfaceProtocol: Common AT commands */[m
[32m+[m[32m    USBD_AUDIO_INTERFACE,//UDBD_MIDI_INTERFACE,                               /* bInterfaceNumber: Number of Interface */[m
[32m+[m[32m    USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */[m
[32m+[m[32m    USBD_MIDI_EP,                               /* bNumEndpoints: One endpoints used */[m
[32m+[m[32m    USBD_AUDIO_CLASS,                               /* bInterfaceClass: Communication Interface Class */[m
[32m+[m[32m    USB_MIDISTREAMING_SUBCLASS,                               /* bInterfaceSubClass: Abstract Control Model */[m
[32m+[m[32m    USB_AUDIO_PROTOCOL,                               /* bInterfaceProtocol: Common AT commands */[m
     0x00,                               /* iInterface: */[m
 [m
     /*Endpoint 0 Descriptor*/[m
     USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
     USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    0x85,                    /* bEndpointAddress */[m
[31m-    0x05,                               /* bmAttributes: Interrupt */[m
[31m-    LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
[31m-    HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x01,                               /* bInterval: */[m
[31m-[m
[31m-    /*Endpoint 0 Descriptor*/[m
[31m-    USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
[31m-    USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    0x85,                    /* bEndpointAddress */[m
[31m-    0x05,                               /* bmAttributes: Interrupt */[m
[32m+[m[32m    USBD_MIDI_IN,                    /* bEndpointAddress */[m
[32m+[m[32m    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */[m
     LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
     HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x01,                               /* bInterval: */[m
[32m+[m[32m    USBD_AUDIO_INTERVAL,                               /* bInterval: */[m
 [m
     /*Endpoint 1 Descriptor*/[m
     USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
     USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[31m-    0x85,                    /* bEndpointAddress */[m
[31m-    0x05,                               /* bmAttributes: Interrupt */[m
[32m+[m[32m    USBD_MIDI_OUT,                    /* bEndpointAddress */[m
[32m+[m[32m    USDB_AUDIO_ASYNC,                               /* bmAttributes: Interrupt */[m
     LOBYTE(USBD_BULK_PACKET_SIZE),        /* wMaxPacketSize: */[m
     HIBYTE(USBD_BULK_PACKET_SIZE),[m
[31m-    0x01,                               /* bInterval: */[m
[32m+[m[32m    USBD_AUDIO_INTERVAL,                               /* bInterval: */[m
[32m+[m
[32m+[m
[32m+[m[32m    /*---------------------------------------------------------------------------*/[m
[32m+[m[32m    /*  CDC Interface                                                            */[m
[32m+[m[32m    /*---------------------------------------------------------------------------*/[m
[32m+[m
[32m+[m[32m        /*Interface Descriptor */[m
[32m+[m[32m        USB_INTERFACE_DESC_SIZE,            /* bLength: Interface Descriptor size */[m
[32m+[m[32m        USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: Interface */[m
[32m+[m[32m        USBD_CDC_CONTROL_INTERFACE,          /* bInterfaceNumber: Number of Interface */[m
[32m+[m[32m        USB_INTERFACE_ALT_0,    /* bAlternateSetting: Alternate setting */[m
[32m+[m[32m        USBD_CDC_CONTROL_ENDPOINTS,         /* bNumEndpoints: One endpoint used */[m
[32m+[m[32m        USBD_CDC_ACM_CLASS,                  /* bInterfaceClass: Communication Interface Class */[m
[32m+[m[32m        USBD_CDC_ACM_SUBCLASS,               /* bInterfaceSubClass: Abstract Control Model */[m
[32m+[m[32m        USBD_CDC_ACM_PROTOCOL,              /* bInterfaceProtocol: Common AT commands */[m
[32m+[m[32m        USBD_IDX_CDC_IF_STR,                /* iInterface: */[m
[32m+[m
[32m+[m[32m        /*Header Functional Descriptor*/[m
[32m+[m[32m        USBD_CDC_HEADER_SIZE,               /* bLength: Endpoint Descriptor size */[m
[32m+[m[32m        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[32m+[m[32m        0x00,                               /* bDescriptorSubtype: Header Func Desc */[m
[32m+[m[32m        0x10,                               /* bcdCDC: spec release number */[m
[32m+[m[32m        0x01,[m
[32m+[m
[32m+[m[32m        /*Call Management Functional Descriptor*/[m
[32m+[m[32m        USBD_CDC_CALL_MAN_SIZE,             /* bFunctionLength */[m
[32m+[m[32m        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[32m+[m[32m        0x01,                               /* bDescriptorSubtype: Call Management Func Desc */[m
[32m+[m[32m        0x00,                               /* bmCapabilities: D0+D1 */[m
[32m+[m[32m        0x01,                               /* bDataInterface: 1 */[m
[32m+[m
[32m+[m[32m        /*ACM Functional Descriptor*/[m
[32m+[m[32m        USBD_CDC_ACM_SIZE,                  /* bFunctionLength */[m
[32m+[m[32m        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[32m+[m[32m        0x02,                               /* bDescriptorSubtype: Abstract Control Management desc */[m
[32m+[m[32m        0x02,                               /* bmCapabilities */[m
[32m+[m
[32m+[m[32m        /*Union Functional Descriptor*/[m
[32m+[m[32m        USBD_CDC_UNION_SIZE,                /* bFunctionLength */[m
[32m+[m[32m        USBD_CDC_CS_IF_DESC_TYPE,           /* bDescriptorType: CS_INTERFACE */[m
[32m+[m[32m        0x06,                               /* bDescriptorSubtype: Union func desc */[m
[32m+[m[32m        0x00,                               /* bMasterInterface: Communication class interface */[m
[32m+[m[32m        0x01,                               /* bSlaveInterface0: Data Class Interface */[m
[32m+[m
[32m+[m[32m        /*Endpoint 2 Descriptor*/[m
[32m+[m[32m        USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
[32m+[m[32m        USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[32m+[m[32m        USBD_EP_CDC_CMD,                    /* bEndpointAddress */[m
[32m+[m[32m        USBD_EP_INTR_TYPE,                  /* bmAttributes: Interrupt */[m
[32m+[m[32m        LOBYTE(USBD_INT_PACKET_SIZE),       /* wMaxPacketSize: */[m
[32m+[m[32m        HIBYTE(USBD_INT_PACKET_SIZE),[m
[32m+[m[32m        USBD_CDC_EP_INTERVAL,               /* bInterval: */[m
[32m+[m
[32m+[m[32m    /*---------------------------------------------------------------------------*/[m
[32m+[m
[32m+[m[32m        /*Data class interface descriptor*/[m
[32m+[m[32m        USB_INTERFACE_DESC_SIZE,            /* bLength: Endpoint Descriptor size */[m
[32m+[m[32m        USB_INTERFACE_DESC_TYPE,            /* bDescriptorType: */[m
[32m+[m[32m        USBD_CDC_DATA_INTERFACE,            /* bInterfaceNumber: Number of Interface */[m
[32m+[m[32m        USB_INTERFACE_ALT_0,                               /* bAlternateSetting: Alternate setting */[m
[32m+[m[32m        USBD_CDC_DATA_ENDPOINTS,                               /* bNumEndpoints: Two endpoints used */[m
[32m+[m[32m        USBD_CDC_DATA_CLASS,                               /* bInterfaceClass: CDC */[m
[32m+[m[32m        USBD_CDC_DATA_SUBCLASS,                               /* bInterfaceSubClass: */[m
[32m+[m[32m        USBD_CDC_DATA_PROTOCOL,                               /* bInterfaceProtocol: */[m
[32m+[m[32m        USBD_IDX_CDC_IF_STR,                /* iInterface: */[m
[32m+[m
[32m+[m[32m        /*Endpoint OUT Descriptor*/[m
[32m+[m[32m        USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
[32m+[m[32m        USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[32m+[m[32m        USBD_EP_CDC_RX,                     /* bEndpointAddress */[m
[32m+[m[32m        USBD_EP_BULK_TYPE,                               /* bmAttributes: Bulk */[m
[32m+[m[32m        LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */[m
[32m+[m[32m        HIBYTE(USBD_BULK_PACKET_SIZE),[m
[32m+[m[32m        USBD_CDC_DATA_INTERVAL,                               /* bInterval: ignore for Bulk transfer */[m
[32m+[m
[32m+[m[32m        /*Endpoint IN Descriptor*/[m
[32m+[m[32m        USB_ENDPOINT_DESC_SIZE,             /* bLength: Endpoint Descriptor size */[m
[32m+[m[32m        USB_ENDPOINT_DESC_TYPE,             /* bDescriptorType: Endpoint */[m
[32m+[m[32m        USBD_EP_CDC_TX,                     /* bEndpointAddress */[m
[32m+[m[32m        USBD_EP_BULK_TYPE,                               /* bmAttributes: Bulk */[m
[32m+[m[32m        LOBYTE(USBD_BULK_PACKET_SIZE),      /* wMaxPacketSize: */[m
[32m+[m[32m        HIBYTE(USBD_BULK_PACKET_SIZE),[m
[32m+[m[32m        USBD_CDC_DATA_INTERVAL,                               /* bInterval: ignore for Bulk transfer */[m
[32m+[m[32m#endif[m
 };[m
 [m
 #define USB_STRING(Name, String) \[m
