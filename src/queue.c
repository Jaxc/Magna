/*
 * queue.c
 *
 *  Created on: Apr 5, 2020
 *      Author: jaxc
 */

#include <stddef.h>
#include <stdint.h>
#include "queue.h"
#include "stm32f7xx.h"

#define QUEUE_SIZE 32

struct queue_element {
    queue_fcn_t function;
    void *data;
};

struct queue_element queue[QUEUE_SIZE];

uint8_t queue_empty (void);
uint8_t queue_full (void);
void queue_execute(void);


uint8_t queue_read  = 0;
uint8_t queue_write = 0;

manga_error_code_t queue_add (queue_fcn_t queue_fcn, void *queue_data) {
    manga_error_code_t ret = MAGNA_OK;
    if (queue_fcn != NULL) {
        if ((uint32_t) queue_fcn == 0xffffff) {
            __BKPT();
        }
        if (!queue_full()) {
            queue[queue_write].function = queue_fcn;
            queue[queue_write].data = queue_data;

            queue_write++;

            if (queue_write >= QUEUE_SIZE) {
                queue_write = 0;
            }
            ret = MAGNA_OK;
        } else {
            ret = MAGNA_QUEUE_FULL;
        }
    }else {
        ret = MAGNA_INVALID_ARGUMENT;
    }
    return ret;
}

void queue_execute_all(void) {
    while(!queue_empty()) {
        queue_execute();
    }
}

void queue_execute(void) {
    if (!queue_empty()) {
        queue[queue_read].function(queue[queue_read].data);
        queue[queue_read].function = NULL;
        queue[queue_read].data = NULL;

        queue_read++;
        if (queue_read >= QUEUE_SIZE) {
            queue_read = 0;
        }
    }
}


uint8_t queue_empty (void) {
    return queue_read == queue_write;
}

uint8_t queue_full (void) {
    return queue_write == (queue_read - 1);
}


