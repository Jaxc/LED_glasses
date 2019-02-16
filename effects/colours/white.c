/*
 * white.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"

void colour_white_new_frame (void) {

}


void colour_white_gen_data(uint8_t buffer[3], uint16_t buffer_index) {
    buffer[0] = 0xff;
    buffer[1] = 0xff;
    buffer[2] = 0xff;
}
