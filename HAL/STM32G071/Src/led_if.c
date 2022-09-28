#include "pattern_generate.h"
#include "spi.h"

#define SPI_FRAME_SIZE (FRAME_SIZE + 12)

uint8_t spi_buffer[2][SPI_FRAME_SIZE];
uint8_t active_buffer = 0;

void transmit_led(uint8_t buffer[FRAME_SIZE]) {

    pad_spi_payload(buffer, spi_buffer[active_buffer]);
    HAL_SPI_Transmit_DMA(&hspi2, spi_buffer[active_buffer], SPI_FRAME_SIZE);
    active_buffer = !active_buffer;
}

void pad_spi_payload(uint8_t bufferin[FRAME_SIZE], uint8_t bufferout[SPI_FRAME_SIZE]) {
    uint16_t i = FRAME_SIZE + 4;

    bufferout[0] = 0x00;
    bufferout[1] = 0x00;
    bufferout[2] = 0x00;
    bufferout[3] = 0x00;

    /* copy the payload from input buffer to output buffer*/
    memcpy(bufferin, bufferout[4], FRAME_SIZE);

    bufferout[i]   = 0xff;
    bufferout[i+1] = 0xff;
    bufferout[i+2] = 0xff;
    bufferout[i+3] = 0xff;
    bufferout[i+4] = 0xff;
    bufferout[i+5] = 0xff;
    bufferout[i+6] = 0xff;
    bufferout[i+7] = 0xff;
}