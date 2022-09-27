/*
 * white.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "colours_palette.h"
#include "main.h"

void colour_white_gen_data(struct colours *buffer, uint16_t buffer_index) {
    UNUSED(buffer_index);
    get_colour(buffer, 0, 0);
}
