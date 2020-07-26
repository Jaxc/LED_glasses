/*
 * lights.h
 *
 *  Created on: Jul 26, 2020
 *      Author: jaxc
 */

#ifndef EFFECTS_LIGHTS_LIGHTS_H_
#define EFFECTS_LIGHTS_LIGHTS_H_

/* Lightning effect functions */
void lights_flash_new_frame (void);
void lights_flash_gen_data(uint8_t *buffer, uint16_t buffer_index);
void lights_flash_beat_start (void);

void lights_led_off_gen_data(uint8_t *buffer, uint16_t buffer_index);

void lights_led_on_gen_data(uint8_t *buffer, uint16_t buffer_index);

void lights_single_flow_gen_data(uint8_t *buffer, uint16_t buffer_index);
void lights_single_flow_beat_start (void);

void lights_strobe_new_frame (void);
void lights_strobe_gen_data(uint8_t *buffer, uint16_t buffer_index);
void lights_strobe_beat_start (void);
void lights_strobe_beat_stop (void);

void rain_new_frame (void);
void rain_gen_data(uint8_t *buffer, uint16_t buffer_index);
void rain_beat_start (void);

/* Lightning program Macros*/

#define LIGHTS_FLASH {          .light_new_frame    = &lights_flash_new_frame,          \
                                .light_gen_data     = &lights_flash_gen_data,           \
                                .light_beat_start   = &lights_flash_beat_start,         \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_LED_OFF {        .light_new_frame    = &do_nothing,                      \
                                .light_gen_data     = &lights_led_off_gen_data,         \
                                .light_beat_start   = &do_nothing,                      \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_LED_ON {         .light_new_frame    = &do_nothing,                      \
                                .light_gen_data     = &lights_led_on_gen_data,          \
                                .light_beat_start   = &do_nothing,                      \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_SINGLE_FLOW {    .light_new_frame    = &do_nothing,                      \
                                .light_gen_data     = &lights_single_flow_gen_data,     \
                                .light_beat_start   = &lights_single_flow_beat_start,   \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_STROBE {         .light_new_frame    = &lights_strobe_new_frame,         \
                                .light_gen_data     = &lights_strobe_gen_data,          \
                                .light_beat_start   = &lights_strobe_beat_start,        \
                                .light_beat_stop    = &lights_strobe_beat_stop,}

#define LIGHTS_RAIN {           .light_new_frame    = &rain_new_frame,                  \
                                .light_gen_data     = &rain_gen_data,                   \
                                .light_beat_start   = &rain_beat_start,                 \
                                .light_beat_stop    = &do_nothing,}

#endif /* EFFECTS_LIGHTS_LIGHTS_H_ */
