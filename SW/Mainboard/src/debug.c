#include <stdio.h>
#include "main.h"
#include "SEGGER_RTT.h"

void log_info (uint32_t line, char *file) {
	char info_buffer[100];
	snprintf(info_buffer,100, "INFO: tick: %ld file: %s line: %ld\r\n", HAL_GetTick(), file, line);
	SEGGER_RTT_WriteString (0, info_buffer);
}

void log_fatal(uint32_t line, char *file) {
	char info_buffer[100];
	snprintf(info_buffer,100, "FATAL: tick: %ld file: %s line: %ld\r\n", HAL_GetTick(), file, line);
	SEGGER_RTT_WriteString (0, info_buffer);
	//Error_Handler();
}