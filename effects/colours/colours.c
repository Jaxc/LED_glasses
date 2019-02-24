/*
 * colours.c
 *
 *  Created on: Feb 24, 2019
 *      Author: jaxc
 */


/* Inspiration take from http://www.vagrearg.org/content/hsvrgb */
#include "colours.h"


void get_colour (struct colours *colours_out, uint32_t hue, uint32_t saturation) {

    if (saturation == 0) {
            colours_out->red = 0xff;
            colours_out->green = 0xff;
            colours_out->blue = 0xff;
            return;
    } else if (saturation > 255) {
        saturation = 255;
    }

    if (hue > 1535) {
        hue = 1535;
    }


    switch (hue >> 8) {
    case 0:
        colours_out->red = 0xff;
        colours_out->green = hue % 256;
        colours_out->blue = 0x00;
        break;
    case 1:
        colours_out->red = 0xff - (hue % 256);
        colours_out->green = 0xff;
        colours_out->blue = 0x00;
        break;
    case 2:
        colours_out->red = 0x00;
        colours_out->green = 0xff;
        colours_out->blue = hue % 256;
        break;
    case 3:
        colours_out->red = 0x00;
        colours_out->green = 0xff - (hue % 256);
        colours_out->blue = 0xff;
        break;
    case 4:
        colours_out->red = hue % 256;
        colours_out->green = 0x00;
        colours_out->blue = 0xff;
        break;
    default :
        colours_out->red = 0xff;
        colours_out->green = 0x00;
        colours_out->blue = 0xff - (hue % 256);
        break;
    }
}
