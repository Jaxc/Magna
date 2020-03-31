/*
 * debug_functions.c
 *
 *  Created on: Mar 30, 2020
 *      Author: jaxc
 */

#include "main.h"

#include "stdio.h"

int __io_putchar(int ch)
{
 ITM_SendChar(ch);
 return(ch);
}

int _write(int file, char *ptr, int len)
 {
 int DataIdx;
 for (DataIdx = 0; DataIdx < len; DataIdx++)
 {
 __io_putchar(*ptr++);
 usbd_delay_ms(1);
 }
 return len;
 }
