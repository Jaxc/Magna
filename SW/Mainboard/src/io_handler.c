#include "tx_api.h"
#include "main.h"
#include "usart.h"

VOID io_handler(ULONG initial_input) {
    while(1) {
        static uint32_t io_cnt = 0;

        tx_thread_sleep(10);

        io_cnt++;

    }
}