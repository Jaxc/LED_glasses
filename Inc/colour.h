/*
 * colour.h
 *
 *  Created on: Jul 26, 2020
 *      Author: jaxc
 */

#ifndef EFFECTS_COLOURS_COLOUR_H_
#define EFFECTS_COLOURS_COLOUR_H_

/* Colour effect functions */
void colour_cycle_new_frame (void);
void colour_cycle_gen_data (struct colours *buffer, uint16_t buffer_index);

void colour_cycle_beats_gen_data(struct colours *buffer, uint16_t buffer_index);
void colour_cycle_beats_beat_start(void);

void colour_flowing_hue_new_frame(void);
void colour_flowing_hue_gen_data(struct colours *buffer, uint16_t buffer_index);

void colour_random_offset_hue_gen_data(struct colours *buffer, uint16_t buffer_index);
void colour_random_offset_hue_beat_start(void);

void colour_radial_hue_new_frame (void);
void colour_radial_hue_gen_data(struct colours *buffer, uint16_t buffer_index);
void colour_radial_hue_beat_start(void);

void colour_hypnosis_new_frame (void) ;
void colour_hypnosis_gen_data(struct colours *buffer, uint16_t buffer_index);

void colour_green_gen_data (struct colours *buffer, uint16_t buffer_index);

void colour_white_gen_data (struct colours *buffer, uint16_t buffer_index);

/* Colour program Macros*/
#define COLOUR_CYCLE {          .colour_new_frame   = &colour_cycle_new_frame,              \
                                .colour_gen_data    = &colour_cycle_gen_data,               \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_CYCLE_BEATS {     .colour_new_frame   = &do_nothing,                          \
                                .colour_gen_data    = &colour_cycle_beats_gen_data,         \
                                .colour_beat_start  = &colour_cycle_beats_beat_start,       \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_FLOWING_HUE {    .colour_new_frame   = &colour_flowing_hue_new_frame,        \
                                .colour_gen_data    = &colour_flowing_hue_gen_data,         \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_RANDOM_OFFSET {  .colour_new_frame   = &do_nothing,                          \
                                .colour_gen_data    = &colour_random_offset_hue_gen_data,   \
                                .colour_beat_start  = &colour_random_offset_hue_beat_start, \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_RADIAL_HUE {     .colour_new_frame   = &colour_radial_hue_new_frame,         \
                                .colour_gen_data    = &colour_radial_hue_gen_data,          \
                                .colour_beat_start  = &colour_radial_hue_beat_start,        \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_HYPNOSIS {       .colour_new_frame   = &colour_hypnosis_new_frame,           \
                                .colour_gen_data    = &colour_hypnosis_gen_data,            \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_GREEN {          .colour_new_frame   = &do_nothing,                          \
                                .colour_gen_data    = &colour_green_gen_data,               \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#define COLOUR_WHITE {          .colour_new_frame   = &do_nothing,                          \
                                .colour_gen_data    = &colour_white_gen_data,               \
                                .colour_beat_start  = &do_nothing,                          \
                                .colour_beat_stop   = &do_nothing,}

#endif /* EFFECTS_COLOURS_COLOUR_H_ */
