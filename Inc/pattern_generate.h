/*
 * pattern_generate.h
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "colours_palette.h"
#include "led_position.h"

#ifndef INC_PATTERN_GENERATE_H_
#define INC_PATTERN_GENERATE_H_

#define FRAME_SIZE (N_LEDS * BYTES_PER_LED)

void tx_led_buffer(void);
void create_payload(uint8_t buffer[FRAME_SIZE]);
void get_current_led(uint8_t buffer[4], uint16_t i);
void pattern_new_frame (void);
void pattern_gen_data(uint8_t buffer[4]);
void cycle_effects (void);

void beat_start(void);
void beat_stop(void);

#ifdef COMPILE_TESTS
typedef enum patterns {
    LED_OFF,
    test_1,
    test_2,
    test_3,
    test_4,
    test_5,
    test_6,
    test_7,
    test_8,
    test_9,
#ifdef USE_ADC
    test_10,
    test_11,
#endif
    test_12,
    N_EFFECTS
} pattern;
#else

typedef enum patterns {
    LED_OFF,
    HYPNOSIS,
    CYCLE_COLOURS,
    FLASH_COLOURS,
    STROBE,
    CYCLE_COLOURS_BEATS,
    FLOWING_HUE,
    RANDOM_OFFSET_HUE,
    RADIAL_HUE,
    MATRIX,
    TEXT,
    N_EFFECTS
} pattern;

#endif

typedef void (*gen_frame)(uint8_t buffer[FRAME_SIZE]);
typedef void (*beat_start_func)(void);
typedef void (*beat_stop_func)(void);

struct colour_preset {
    gen_frame           colour_gen_frame;
    beat_start_func     colour_beat_start;
    beat_stop_func      colour_beat_stop;
};

struct light_preset {
    gen_frame           light_gen_frame;
    beat_start_func     light_beat_start;
    beat_stop_func      light_beat_stop;
};

struct Presets {
    struct light_preset light;
    struct colour_preset colour;
};

/* Declarations for effect functions */
static inline void do_nothing(void) {
    return;
}


void start_timing(void);

uint32_t get_ellapsed_time(void);

void stop_timing(void);

void set_effect(pattern new_pattern);

#endif /* INC_PATTERN_GENERATE_H_ */
