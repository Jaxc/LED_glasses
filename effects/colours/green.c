/*
 * green.c
 *
 *  Created on: Jan 10, 2020
 *      Author: jaxc
 */

#include "colours.h"


void green_gen_data(struct colours *buffer, uint16_t buffer_index) {
    buffer->green = 0xff;
    buffer->blue  = 0x00;
    buffer->red   = 0x00;

}
