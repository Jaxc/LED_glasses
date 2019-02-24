/*
 * white.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"
#include "colours.h"

void colour_white_new_frame (void) {

}


void colour_white_gen_data(struct colours *buffer, uint16_t buffer_index) {
    get_colour(buffer, 0, 0);
}
