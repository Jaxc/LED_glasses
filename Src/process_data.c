/*
 * process_data.c
 *
 *  Created on: Jul 27, 2020
 *      Author: jaxc
 */

#include "adc.h"
#include "pattern_generate.h"
#include "tim.h"

enum {
    PROCESS_IDLE = 0,
    PROCESS_ACTIVATE,
    PROCESS_ACTIVE,
    PROCESS_SENDING,
};

volatile uint8_t process_state = PROCESS_IDLE;

void process_data(void) {
    switch (process_state) {

    case PROCESS_IDLE:
        /* Do nothing */
        break;

    case PROCESS_ACTIVATE:

        {
            volatile uint32_t audio_time = 0;
            volatile uint32_t led_time = 0;

            process_state = PROCESS_ACTIVE;
            start_timing();
#ifdef USE_ADC
            process_audio();
#endif
            audio_time = get_ellapsed_time();
            tx_led_buffer();
            led_time = get_ellapsed_time() - audio_time;

            stop_timing();
            process_state = PROCESS_SENDING;
        }

        break;

    case PROCESS_ACTIVE:
        /* This should never happen */
        Error_Handler();
        break;

    case PROCESS_SENDING:
        break;

    default :
        break;
    }
}

void sending_complete(void) {
    if (PROCESS_SENDING == process_state) {
        process_state = PROCESS_IDLE;
    }
}

void start_process_data(void) {
    if (PROCESS_IDLE == process_state) {
        process_state = PROCESS_ACTIVATE;
    } else if (PROCESS_SENDING == process_state) {
        /* Do nothing*/
    } else {
        /* New interrupt before last one is processed */
        Error_Handler();
    }
}


