/*
 * colour.h
 *
 *  Created on: Jul 26, 2020
 *      Author: jaxc
 */

#ifndef EFFECTS_COLOURS_COLOUR_H_
#define EFFECTS_COLOURS_COLOUR_H_

/* Colour effect functions */
void colour_cycle_gen_frame (uint8_t *buffer);

void colour_flowing_hue_gen_frame(uint8_t *buffer);

void colour_cycle_beats_gen_frame(uint8_t buffer[FRAME_SIZE]);
void colour_cycle_beats_beat_start(void);

void colour_random_offset_hue_gen_frame(uint8_t buffer[FRAME_SIZE]);
void colour_random_offset_hue_beat_start(void);

void colour_radial_hue_gen_frame (uint8_t *buffer);
void colour_radial_hue_beat_start(void);

void colour_beat_radial_hue_gen_frame (uint8_t *buffer);
void colour_beat_radial_hue_beat_start(void);

void colour_hypnosis_gen_frame (uint8_t *buffer);

void colour_white_gen_frame(uint8_t buffer[FRAME_SIZE]);

void colour_green_gen_frame(uint8_t buffer[FRAME_SIZE]);

/* Colour program Macros*/
#define COLOUR_CYCLE {          .colour_gen_frame   = &colour_cycle_gen_frame,              \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_CYCLE_BEATS {     .colour_gen_frame  = &colour_cycle_beats_gen_frame,                         \
                                .colour_beat_start  = &colour_cycle_beats_beat_start,       \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_FLOWING_HUE {    .colour_gen_frame   = &colour_flowing_hue_gen_frame,        \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_RANDOM_OFFSET {  .colour_gen_frame   = &colour_random_offset_hue_gen_frame,                          \
                                .colour_beat_start  = &colour_random_offset_hue_beat_start, \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_RADIAL_HUE {     .colour_gen_frame   = &colour_radial_hue_gen_frame,         \
                                .colour_beat_start  = &colour_radial_hue_beat_start,        \
                                .colour_beat_stop   = &do_nothing,}
#define COLOUR_BEAT_RADIAL_HUE {     .colour_gen_frame   = &colour_beat_radial_hue_gen_frame,         \
                                .colour_beat_start  = &colour_beat_radial_hue_beat_start,        \
                                .colour_beat_stop   = &do_nothing,}                                

#define COLOUR_HYPNOSIS {       .colour_gen_frame   = &colour_hypnosis_gen_frame,           \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_GREEN {          .colour_gen_frame   = &colour_green_gen_frame,                          \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_WHITE {          .colour_gen_frame   = &colour_white_gen_frame,                          \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#endif /* EFFECTS_COLOURS_COLOUR_H_ */
