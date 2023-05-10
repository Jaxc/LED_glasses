/*
 * font_engine.c
 *
 *  Created on: May 09, 2023
 *      Author: jaxc
 */

#include <stdint.h>

struct font_data_struct {
    uint8_t length;
    uint16_t data[8];
};

extern const struct font_data_struct font_data[256];