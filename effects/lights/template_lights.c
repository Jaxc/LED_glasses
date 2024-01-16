#include "pattern_generate.h"

void template_light_gen_frame (uint8_t buffer[N_LEDS]) {
    /* Frame init code goes here, things like incrementing counters etc*/



    /* Pixel assignment goes here*/
    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {

        /* example */
        buffer[current_led] = 255; /* Full light */

        /* LED done, prepare to calculate next LED. */
    }
    return;
}

void template_light_beat_start(void) {
    /* This is called when a beat is detected, so effects that are beat dependent uses this.
       This function is optional */
    return;
}


void template_light_beat_stop(void) {
    /* Not yet implemented, can be omitted as it will never be called */
    return;
}