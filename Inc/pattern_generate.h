/*
 * pattern_generate.h
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "colours.h"

#ifndef INC_PATTERN_GENERATE_H_
#define INC_PATTERN_GENERATE_H_

#define N_LEDS 86
#define FRAME_SIZE 8 + (N_LEDS * 4)

void tx_led_buffer(void);
void create_payload(uint8_t buffer[FRAME_SIZE]);
void get_current_led(uint8_t buffer[4], uint16_t i);
void pattern_new_frame (void);
void pattern_gen_data(uint8_t buffer[4]);
void cycle_effects (void);

void beat_start(void);
void beat_stop(void);

typedef enum patterns {
    LED_OFF,
    FLASH_WHITE,
    CYCLE_COLOURS,
    FLASH_COLOURS,
    STROBE,
    SINGLE_FLOW,
    CYCLE_COLOURS_BEATS,
    FLOWING_HUE,
    RANDOM_OFFSET_HUE,
    N_EFFECTS
} pattern;

typedef void (*new_frame)(void);
typedef void (*gen_light_data)(uint8_t *buffer, uint16_t buffer_index);
typedef void (*gen_colour_data)(struct colours *buffer, uint16_t buffer_index);
typedef void (*beat_start_func)(void);
typedef void (*beat_stop_func)(void);

struct Presets {
    new_frame       light_new_frame;
    gen_light_data  light_gen_data;
    beat_start_func      light_beat_start;
    beat_stop_func       light_beat_stop;
    new_frame       colour_new_frame;
    gen_colour_data colour_gen_data;
    beat_start_func      colour_beat_start;
    beat_stop_func       colour_beat_stop;
};

/* Declarations for effect functions */
static inline void do_nothing(void) {
    return;
}
/* Lights */
void test_1_gen_data(uint8_t *buffer, uint16_t buffer_index);

void test_2_new_frame (void);
void test_2_gen_data(uint8_t *buffer, uint16_t buffer_index);

void test_3_new_frame (void);
void test_3_gen_data(uint8_t *buffer, uint16_t buffer_index);

void test_4_new_frame (void);
void test_4_gen_data(uint8_t *buffer, uint16_t buffer_index);

void test_5_new_frame (void);
void test_5_gen_data(struct colours *buffer, uint16_t buffer_index);

void test_6_new_frame (void);
void test_6_gen_data(struct colours *buffer, uint16_t buffer_index);


void lights_flash_new_frame (void);
void lights_flash_gen_data(uint8_t *buffer, uint16_t buffer_index);
void lights_flash_beat_start (void);
void lights_flash_beat_stop (void);

void lights_led_off_new_frame (void);
void lights_led_off_gen_data(uint8_t *buffer, uint16_t buffer_index);

void lights_led_on_new_frame (void);
void lights_led_on_gen_data(uint8_t *buffer, uint16_t buffer_index);

void lights_single_flow_new_frame (void);
void lights_single_flow_gen_data(uint8_t *buffer, uint16_t buffer_index);
void lights_single_flow_beat_start (void);
void lights_single_flow_beat_stop (void);

void lights_strobe_new_frame (void);
void lights_strobe_gen_data(uint8_t *buffer, uint16_t buffer_index);
void lights_strobe_beat_start (void);
void lights_strobe_beat_stop (void);

/* Colour */
void colour_cycle_new_frame (void);
void colour_cycle_gen_data (struct colours *buffer, uint16_t buffer_index);

void colour_beat_change_new_frame (void);
void colour_beat_change_gen_data (struct colours *buffer, uint16_t buffer_index);
void lights_beat_change_beat_start (void);
void lights_beat_change_beat_stop (void);

void colour_white_new_frame (void);
void colour_white_gen_data (struct colours *buffer, uint16_t buffer_index);

void colour_cycle_beats_new_frame(void);
void colour_cycle_beats_gen_data(struct colours *buffer, uint16_t buffer_index);
void colour_cycle_beats_beat_start(void);

void colour_flowing_hue_new_frame(void);
void colour_flowing_hue_gen_data(struct colours *buffer, uint16_t buffer_index);

void colour_random_offset_hue_new_frame(void);
void colour_random_offset_hue_gen_data(struct colours *buffer, uint16_t buffer_index);

#endif /* INC_PATTERN_GENERATE_H_ */
