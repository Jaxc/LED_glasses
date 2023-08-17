
#include "pattern_generate.h"

 void template_colour_gen_frame (uint8_t buffer[FRAME_SIZE]) {
    /* Frame init code goes here, things like incrementing counters etc*/



    /* Pixel assignment goes here*/
    uint16_t current_led = 0; /*Variable to keep track on which pixel is currently being
                                assigned. */
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        /* Remember to assign buffer[i], buffer[i+1] and buffer[i+2] */

        /* example */
        buffer[i] = 255; /* Green value */
        buffer[i+1] = 255; /* Red value */
        buffer[i+2] = 255; /* Blue value */

        /* LED done, prepare to calculate next LED. */
        current_led++;
    }
 }