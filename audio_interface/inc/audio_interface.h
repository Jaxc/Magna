/*
 * audio_interface.h
 *
 *  Created on: Apr 2, 2020
 *      Author: jaxc
 */

#ifndef AUDIO_INTERFACE_INC_AUDIO_INTERFACE_H_
#define AUDIO_INTERFACE_INC_AUDIO_INTERFACE_H_

struct rx_buffer_info_t {
    uint8_t *data;
    uint16_t length;
};

void start_codecs(void);
void init_codec(void);
void audio_interface_queue_buffer(void *received_buffer_info);



#endif /* AUDIO_INTERFACE_INC_AUDIO_INTERFACE_H_ */
