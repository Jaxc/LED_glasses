/*
 * colours.h
 *
 *  Created on: Feb 24, 2019
 *      Author: jaxc
 */

#ifndef INC_COLOURS_PALETTE_H_
#define INC_COLOURS_PALETTE_H_

#include <stdint.h>

struct colours {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

void get_colour (struct colours *colours_out, uint32_t hue, uint32_t saturation);



#endif /* INC_COLOURS_PALETTE_H_ */
