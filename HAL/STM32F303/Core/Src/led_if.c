#include "pattern_generate.h"
#include "tim.h"


#define PWM_FRAME_SIZE (FRAME_SIZE * 8)

uint32_t pwm_buffer[PWM_FRAME_SIZE];

#define DUTY_0 (htim1.Init.Period * 0.3)
#define DUTY_1 (htim1.Init.Period * 0.5)

void transmit_led(uint8_t buffer[FRAME_SIZE]) {


    encode_pwm(buffer, pwm_buffer);

    HAL_TIMEx_PWMN_Start_DMA(&htim1, TIM_CHANNEL_3, pwm_buffer, PWM_FRAME_SIZE);

    return;
}

void encode_pwm(uint8_t inbuffer[FRAME_SIZE], uint32_t outbuffer[PWM_FRAME_SIZE]){

    for (uint8_t i = 0; i < N_LEDS; i++) {
        for (uint8_t j = 0; j < BYTES_PER_LED; j++) {
            uint8_t current_byte = inbuffer[i * 3 + j];
            for (uint8_t k = 0; k < 8; k++) {
                if ((current_byte & 0x80) == 0x80) {
                    outbuffer[((i * BYTES_PER_LED) + j) * 8 + k] = DUTY_1;
                } else {
                    outbuffer[((i * BYTES_PER_LED) + j) * 8 + k] = DUTY_0;
                }
                
                current_byte = current_byte << 1;
            }
        }
    }

    /* For some reason there is a tail of the signa, so we end with a defined 0 to drag it down*/
    outbuffer[PWM_FRAME_SIZE - 1] = 0;
}

void start_transmission(void) {
    HAL_TIM_Base_Start_IT(&htim17);
}