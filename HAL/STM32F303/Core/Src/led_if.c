#include "pattern_generate.h"

#define SPI_FRAME_SIZE (FRAME_SIZE + 12)

uint8_t spi_buffer[2][SPI_FRAME_SIZE];
uint8_t active_buffer = 0;

void transmit_led(uint8_t buffer[FRAME_SIZE]) {

    return;

}
