/*
 * cpu_load_calc.h
 *
 *  Created on: Dec 29, 2019
 *      Author: jaxc
 */

#ifndef INC_CPU_LOAD_CALC_H_
#define INC_CPU_LOAD_CALC_H_

#include "tim.h"

void log_load(uint16_t active_cnt,uint16_t idle_cnt, TIM_HandleTypeDef *timer_active, TIM_HandleTypeDef *timer_idle);



#endif /* INC_CPU_LOAD_CALC_H_ */
