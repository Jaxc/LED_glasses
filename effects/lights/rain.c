/*
 * rain.c
 *
 *  Created on: Jan 10, 2020
 *      Author: jaxc
 */

#include "main.h"
#include "led_position.h"

uint8_t rain_cnt = 0;

struct rain_driplet  {
    uint8_t y;
};

#define N_RAIN_DRIPLET N_COLS
#define TRAIL_LEN 5

struct rain_driplet rain_driplets[N_RAIN_DRIPLET] = {[0 ... N_RAIN_DRIPLET-1] = {TRAIL_LEN + N_ROWS + 1}  };

void rain_gen_frame(uint8_t buffer[N_LEDS]) {

    for(uint8_t j = 0; j < N_RAIN_DRIPLET; j++) {
        if((TRAIL_LEN + N_ROWS) < rain_driplets[j].y) {

        } else {
            rain_driplets[j].y++;
        }
    }


    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        buffer[current_led] = 0;
            if (led_pos_eye(current_led)) {
                    if((TRAIL_LEN + N_ROWS) < rain_driplets[16 - led_pos_cart_x[current_led]].y) {

                    } else {
                        int8_t rain_y_diff = rain_driplets[16 - led_pos_cart_x[current_led]].y - led_pos_cart_y[current_led];
                        if (0 <= rain_y_diff) {
                            if (TRAIL_LEN > rain_y_diff) {
                                buffer[current_led]  = 0xFF >> rain_y_diff;
                            }
                        }
                    break;
                }
            } else {
                    if((TRAIL_LEN + N_ROWS) < rain_driplets[led_pos_cart_x[current_led]].y) {

                    } else {
                        int8_t rain_y_diff = rain_driplets[led_pos_cart_x[current_led]].y - led_pos_cart_y[current_led];
                        if (0 <= rain_y_diff) {
                            if (TRAIL_LEN > rain_y_diff) {
                                buffer[current_led] = 0xFF >> rain_y_diff ;
                            }
                        }
                    }
        }
    }


}

uint32_t random_rain = 22222;

void rain_beat_start(void) {
    for(uint8_t i = 0; i < 2 ; i++) {
        uint8_t next_drip = random_rain % N_RAIN_DRIPLET;
        random_rain = (random_rain * 196314165) + 907633515;
        if ((TRAIL_LEN + N_ROWS + 1) == rain_driplets[next_drip].y) {
            rain_driplets[next_drip].y = 0;
            break;
        }
    }
}


