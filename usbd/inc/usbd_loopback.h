/*
 * usbd_loopback.h
 *
 *  Created on: Apr 1, 2018
 *      Author: jaxc
 */

#ifndef USBD_MAGNA_INC_USBD_LOOPBACK_H_
#define USBD_MAGNA_INC_USBD_LOOPBACK_H_

void vcom_echo(void *data);

void vcom_rx_complete(uint8_t *data, uint16_t len, void *usr);

#endif /* USBD_MAGNA_INC_USBD_LOOPBACK_H_ */
