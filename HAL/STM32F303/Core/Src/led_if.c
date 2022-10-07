#include "pattern_generate.h"
#include "process_data.h"
#include "tim.h"


#define PWM_FRAME_SIZE (FRAME_SIZE * 8)
#define DUTY_0 (htim1.Init.Period * (0.3))
#define DUTY_1 (htim1.Init.Period * (0.53))
#define EMPTY_BUFFER_SIZE (24)

uint8_t pwm_buffer[PWM_FRAME_SIZE];
uint8_t new_data_available = 0;

uint8_t empty_buffer[EMPTY_BUFFER_SIZE] = {0};

void encode_pwm(uint8_t inbuffer[FRAME_SIZE], uint8_t outbuffer[PWM_FRAME_SIZE]);


void transmit_led(uint8_t buffer[FRAME_SIZE]) {

    encode_pwm(buffer, pwm_buffer);

    new_data_available = 1;
    return;
}

void encode_pwm(uint8_t inbuffer[FRAME_SIZE], uint8_t outbuffer[PWM_FRAME_SIZE]){

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
}

void start_transmission(void) {
    HAL_TIM_Base_Start_IT(&htim17);
}

void output_data(uint8_t *buffer) {

    static uint32_t left = 0;

    if (new_data_available == 1) {
        if ((PWM_FRAME_SIZE - left) < PWM_BUFFER_SIZE) {
            int i = 0;
            void;
            for( ; i < PWM_FRAME_SIZE - left; i++) {
                buffer[i] = pwm_buffer[left + i];
            }
            for( ;i < PWM_BUFFER_SIZE; i++) {
                buffer[i] = 0x00;
            }

            new_data_available = 0;
            sending_complete();
            left = 0;
        } else {
            memcpy(buffer, &pwm_buffer[left], PWM_BUFFER_SIZE);
            left += PWM_BUFFER_SIZE;
        }
        
    } else {
        memcpy(buffer, empty_buffer, PWM_BUFFER_SIZE);
    }

    
    

}
