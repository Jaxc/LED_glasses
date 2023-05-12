#include "pattern_generate.h"
#include "process_data.h"
#include "tim.h"

struct pwm_init_params_s {
  uint8_t           channel_type;
  TIM_HandleTypeDef *timer;
  uint32_t          channel;
  uint32_t          active_channel
};

#define PWM_FRAME_SIZE (FRAME_SIZE * 8)
#define PWM_CONTROLLER_SIZE (PWM_FRAME_SIZE / PWM_CONTROLLERS_USED)
#define DUTY_0 (htim1.Init.Period * (0.3))
#define DUTY_1 (htim1.Init.Period * (0.53))
#define EMPTY_BUFFER_SIZE (24)

#define CHANNEL_R 0
#define CHANNEL_N 1

uint8_t pwm_buffer[PWM_FRAME_SIZE];
uint8_t new_data_available[PWM_CONTROLLERS_USED] __attribute__ ((section("ccmram"))) = {0};

uint8_t pwm_buffer2[PWM_CONTROLLERS_USED][PWM_BUFFER_DMA_SIZE] __attribute__ ((section("ccmram")))= {0};

struct pwm_init_params_s pwm_init_params[PWM_CONTROLLERS_USED]=
{
  {CHANNEL_N, &htim1, TIM_CHANNEL_3, HAL_TIM_ACTIVE_CHANNEL_3},
  #if PWM_CONTROLLERS_USED > 1
  {CHANNEL_R, &htim1, TIM_CHANNEL_1, HAL_TIM_ACTIVE_CHANNEL_1},
  #endif
};


uint8_t empty_buffer[EMPTY_BUFFER_SIZE] = {0};

void encode_pwm(uint8_t inbuffer[FRAME_SIZE], uint8_t outbuffer[PWM_FRAME_SIZE]);


void transmit_led(uint8_t buffer[FRAME_SIZE]) {

    encode_pwm(buffer, pwm_buffer);


    for(uint8_t i = 0; i < PWM_CONTROLLERS_USED; i++) {
        new_data_available[i] = 1;
    }
    return;
}

void encode_pwm(uint8_t inbuffer[FRAME_SIZE], uint8_t outbuffer[PWM_FRAME_SIZE]){

    for (uint16_t i = 0; i < N_LEDS; i++) {
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

void output_data(uint8_t *buffer, uint8_t pwm_controller) {

    static uint32_t left[PWM_CONTROLLERS_USED] = {0};

    if (new_data_available[pwm_controller] == 1) {
        if ((PWM_CONTROLLER_SIZE - left[pwm_controller]) < PWM_BUFFER_SIZE) {
            int i = 0;
            for( ; i < PWM_CONTROLLER_SIZE - left[pwm_controller]; i++) {
                buffer[i] = pwm_buffer[left[pwm_controller] + i + PWM_CONTROLLER_SIZE * pwm_controller];
            }
            for( ;i < PWM_BUFFER_SIZE; i++) {
                buffer[i] = 0x00;
            }
            left[pwm_controller] = 0;
            new_data_available[pwm_controller] = 0;
        } else {
            volatile uint32_t offset = PWM_CONTROLLER_SIZE * pwm_controller;
            memcpy(buffer, &pwm_buffer[left[pwm_controller] + offset], PWM_BUFFER_SIZE);
            left[pwm_controller] += PWM_BUFFER_SIZE;
        }
        
    } else {
        memcpy(buffer, empty_buffer, PWM_BUFFER_SIZE);
    }

    
    uint8_t all_channels_complete = 0;
    for(uint8_t i = 0; i < PWM_CONTROLLERS_USED; i++) {
        all_channels_complete |= new_data_available[i];
    }

    if( 0 == all_channels_complete) {
        sending_complete();
    }
    

}

void init_pwm(void) {
    for(uint8_t i = 0; i < PWM_CONTROLLERS_USED; i++) {
        if (CHANNEL_R == pwm_init_params[i].channel_type) {
            HAL_TIM_PWM_Start_DMA(pwm_init_params[i].timer, pwm_init_params[i].channel, pwm_buffer2[i], PWM_BUFFER_DMA_SIZE);
        } else {
            HAL_TIMEx_PWMN_Start_DMA(pwm_init_params[i].timer, pwm_init_params[i].channel, pwm_buffer2[i], PWM_BUFFER_DMA_SIZE);
        }

    }
  
  
}

void handle_HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) {
    for(uint8_t i = 0; i < PWM_CONTROLLERS_USED; i++) {
        if (htim->Instance == pwm_init_params[i].timer->Instance) {
 
            if (htim->Channel == pwm_init_params[i].active_channel) {
                output_data(pwm_buffer2[i], i);
            }
        }    
    }
}

void handle_HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    for(uint8_t i = 0; i < PWM_CONTROLLERS_USED; i++) {
        if (htim->Instance == pwm_init_params[i].timer->Instance) {
 
            if (htim->Channel == pwm_init_params[i].active_channel) {
                output_data(&pwm_buffer2[i][PWM_BUFFER_SIZE], i);
            }    
        }
    }
}
