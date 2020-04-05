/*
 * queue.h
 *
 *  Created on: Apr 5, 2020
 *      Author: jaxc
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include "error_codes.h"

typedef void (*queue_fcn_t)(void *in_data);

void queue_execute(void);
manga_error_code_t queue_add (queue_fcn_t queue_fcn, void *queue_data) ;

#endif /* INC_QUEUE_H_ */
