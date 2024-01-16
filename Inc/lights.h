/*
 * lights.h
 *
 *  Created on: Jul 26, 2020
 *      Author: jaxc
 */

#ifndef EFFECTS_LIGHTS_LIGHTS_H_
#define EFFECTS_LIGHTS_LIGHTS_H_

/* Lightning effect functions */
void lights_led_on_gen_frame (uint8_t buffer[FRAME_SIZE]);

void lights_led_off_gen_frame (uint8_t buffer[FRAME_SIZE]);

void lights_flash_gen_frame (uint8_t buffer[FRAME_SIZE]);
void lights_flash_beat_start (void);

void lights_single_flow_beat_start (void);

void lights_strobe_gen_frame (uint8_t buffer[FRAME_SIZE]);
void lights_strobe_beat_start (void);
void lights_strobe_beat_stop (void);

void rain_gen_frame (uint8_t buffer[FRAME_SIZE]);
void rain_beat_start (void);

void lights_text_gen_frame (uint8_t buffer[FRAME_SIZE]);
void lights_text_beat_start (void);

/* Lightning program Macros*/

#define LIGHTS_FLASH {          .light_gen_frame    = &lights_flash_gen_frame,          \
                                .light_beat_start   = &lights_flash_beat_start,         \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_LED_OFF {        .light_gen_frame    = &lights_led_off_gen_frame,                      \
                                .light_beat_start   = &do_nothing,                      \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_LED_ON {         .light_gen_frame    = &lights_led_on_gen_frame,                      \
                                .light_beat_start   = &do_nothing,                      \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_SINGLE_FLOW {    .light_gen_frame    = &lights_single_flow_gen_frame,                      \
                                .light_beat_start   = &lights_single_flow_beat_start,   \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_STROBE {         .light_gen_frame    = &lights_strobe_gen_frame,         \
                                .light_beat_start   = &lights_strobe_beat_start,        \
                                .light_beat_stop    = &lights_strobe_beat_stop,}

#define LIGHTS_RAIN {           .light_gen_frame    = &rain_gen_frame,                  \
                                .light_beat_start   = &rain_beat_start,                 \
                                .light_beat_stop    = &do_nothing,}

#define LIGHTS_TEXT {           .light_gen_frame    = &lights_text_gen_frame,           \
                                .light_beat_start   = &lights_text_beat_start,          \
                                .light_beat_stop    = &do_nothing,}

#endif /* EFFECTS_LIGHTS_LIGHTS_H_ */
