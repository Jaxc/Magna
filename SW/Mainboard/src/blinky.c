#include "tx_api.h"
#include "main.h"


VOID blinky(ULONG initial_input) {
    while(1) {
        tx_thread_sleep(1);
    }
}