/*
 * pattern_generate.h
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#ifndef INC_PATTERN_GENERATE_H_
#define INC_PATTERN_GENERATE_H_

#define N_LEDS 3
#define FRAME_SIZE 8 + (N_LEDS * 4)

void tx_led_buffer(void);
void create_payload(uint8_t buffer[FRAME_SIZE]);
void get_current_led(uint8_t buffer[4], uint16_t i);
void pattern_new_frame (void);
void pattern_gen_data(uint8_t buffer[4]);

typedef enum patterns {
    LED_OFF,
    FLASH_WHITE,
    CYCLE_COLOURS,
    FLASH_COLOURS,
    STROBE,
    N_EFFECTS
} pattern;


/* Declarations for effect functions */
void led_off_new_frame (void);
void led_off_gen_data(uint8_t buffer[4]);
void white_flash_new_frame (void);
void white_flash_gen_data(uint8_t buffer[4]);
void strobe_new_frame (void);
void strobe_gen_data(uint8_t buffer[4]);
void cycle_colour_new_frame (void);
void cycle_colour_gen_data(uint8_t buffer[4]);

#endif /* INC_PATTERN_GENERATE_H_ */
