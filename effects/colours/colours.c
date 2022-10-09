/*
 * colours.c
 *
 *  Created on: Feb 24, 2019
 *      Author: jaxc
 */


/* Inspiration take from http://www.vagrearg.org/content/hsvrgb */
#include "colours_palette.h"
#include "pattern_generate.h"

void get_colour (struct colours *colours_out, uint32_t hue, uint32_t saturation) {

    if (saturation == 0) {
            colours_out->red = 0xff;
            colours_out->green = 0xff;
            colours_out->blue = 0xff;
            return;
    } else if (saturation > 255) {
        saturation = 255;
    }

    if (hue > 1024) {
        hue = 1024;
    }


    switch (hue >> 7) {
    case 0:
    case 1:
        colours_out->red = 0xff;
        colours_out->green = hue % 256;
        colours_out->blue = 0x00;
        break;
    case 2:
    case 3:
        colours_out->red = 0xff - (hue % 256);
        colours_out->green = 0xff;
        colours_out->blue = 0x00;
        break;
    case 4:
        colours_out->red = 0x00;
        colours_out->green = 0xff;
        colours_out->blue = (hue % 128) << 1;
        break;
    case 5:
        colours_out->red = 0x00;
        colours_out->green = 0xff - ((hue % 128) << 1);
        colours_out->blue = 0xff;
        break;
    case 6:
        colours_out->red = (hue % 128) << 1;
        colours_out->green = 0x00;
        colours_out->blue = 0xff;
        break;
    default :
        colours_out->red = 0xff;
        colours_out->green = 0x00;
        colours_out->blue = 0xff - ((hue % 128) << 1);
        break;
    }
}
