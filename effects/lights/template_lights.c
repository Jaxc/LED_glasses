#include "pattern_generate.h"

 void template_light_gen_frame (uint8_t buffer[N_LEDS]) {
    /* Frame init code goes here, things like incrementing counters etc*/



    /* Pixel assignment goes here*/
    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        /* Remember to assign buffer[i], buffer[i+1] and buffer[i+2] */

        /* example */
        buffer[current_led] = 255; /* Full light */

        /* LED done, prepare to calculate next LED. */
    }
 }