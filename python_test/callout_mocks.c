
#include "pattern_generate.h"

extern uint8_t light_buffer[N_LEDS];

uint8_t (*p_light_buffer)[N_LEDS] = &light_buffer;

extern uint8_t led_buffer[FRAME_SIZE];

uint8_t (*p_led_buffer)[FRAME_SIZE] = &led_buffer;

void transmit_led(uint8_t buffer[FRAME_SIZE]) {
    return;
}

uint32_t get_audio_power(void) {
    return 0;
}

uint16_t n_leds = N_LEDS;
uint16_t n_rows = N_ROWS;
uint16_t n_cols = N_COLS;