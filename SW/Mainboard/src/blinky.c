#include "tx_api.h"
#include "main.h"
#include "usart.h"

uint8_t tx_data[] = {0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA};

VOID blinky(ULONG initial_input) {
    while(1) {
        tx_thread_sleep(250);
        HAL_UART_Transmit(&huart3, tx_data, sizeof(tx_data), 1000);
    }
}