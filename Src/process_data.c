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
    PROCESS_ACTIVE
};

uint8_t process_state = PROCESS_IDLE;

void process_data(void) {
    if (PROCESS_ACTIVATE == process_state) {
        uint32_t audio_time = 0;
        uint32_t led_time = 0;

        HAL_TIM_Base_Start(&htim2);
        process_state = PROCESS_ACTIVE;

        __HAL_TIM_SET_COUNTER(&htim2, 0);
        process_audio();
        audio_time = __HAL_TIM_GET_COUNTER(&htim2);
        tx_led_buffer();
        led_time = __HAL_TIM_GET_COUNTER(&htim2) - audio_time;

        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_TIM_Base_Stop(&htim2);
        process_state = PROCESS_IDLE;
    } else if (PROCESS_ACTIVE == process_state) {
        /* This should never happen */
        Error_Handler();
    } else {
        /* Do nothing */
    }
}

void start_process_data(void) {
    if (PROCESS_IDLE == process_state) {
        process_state = PROCESS_ACTIVATE;
    } else {
        /* New interrupt before last one is processed */
        Error_Handler();
    }
}


