/*
 * pattern_generate.h
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#ifndef INC_PATTERN_GENERATE_H_
#define INC_PATTERN_GENERATE_H_

#define N_LEDS 1
#define FRAME_SIZE 8 + (N_LEDS * 4)

void tx_led_buffer(void);
void create_payload(uint8_t buffer[FRAME_SIZE]);
void get_current_led(uint8_t buffer[4], uint16_t i);
void pattern_new_frame (void);
void pattern_gen_data(uint8_t buffer[4]);

typedef enum patterns {
    PATTERN_OFF,
    FLASH_WHITE,
    CYCLE_COLOURS,
    FLASH_COLOURS,
    STROBE
} pattern;

#endif /* INC_PATTERN_GENERATE_H_ */
