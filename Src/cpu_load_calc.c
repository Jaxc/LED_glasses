/*
 * cpu_load_calc.c
 *
 *  Created on: Dec 29, 2019
 *      Author: jaxc
 */

#include "cpu_load_calc.h"

void log_load(uint16_t active_cnt,uint16_t idle_cnt, TIM_HandleTypeDef *timer_active, TIM_HandleTypeDef *timer_idle){

    uint32_t cpu_load = ((uint32_t)active_cnt) << 16 | timer_active->Instance->CNT;
    uint32_t cpu_idle = ((uint32_t)idle_cnt) << 16 | timer_idle->Instance->CNT;

}

