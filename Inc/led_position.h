/*
 * led_position.h
 *
 *  Created on: Dec 28, 2019
 *      Author: jaxc
 */

#ifndef INC_LED_POSITION_H_
#define INC_LED_POSITION_H_

#include "pattern_generate.h"


#ifdef GLASSESV1
#define N_ROWS 7
#define N_COLS 8

#define led_pos_eye(x) ((x) < (N_LEDS / 2) ? (0) : (1))
#endif

#ifdef BOTTLEBLINK
#define N_ROWS 7
#define N_COLS 8

#define led_pos_eye(x) (0)
#endif


#ifdef LEDSQUARE
#define N_ROWS 5
#define N_COLS 5

#define led_pos_eye(x) (0)
#endif

extern uint8_t led_pos_cart_x [N_LEDS];

extern uint8_t led_pos_cart_y [N_LEDS];


/* Polar cordinates*/
extern uint32_t led_pos_pol_ang [N_LEDS];

extern uint32_t led_pos_pol_rad [N_LEDS];




#endif /* INC_LED_POSITION_H_ */
