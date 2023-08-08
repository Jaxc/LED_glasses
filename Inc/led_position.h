/*
 * led_position.h
 *
 *  Created on: Dec 28, 2019
 *      Author: jaxc
 */

#ifndef INC_LED_POSITION_H_
#define INC_LED_POSITION_H_

#ifdef GLASSESV1
#define N_LEDS 86
#define APA102

#define N_ROWS 7
#define N_COLS 8

#define led_pos_eye(x) ((x) < (N_LEDS / 2) ? (0) : (1))
#endif

#ifdef BOTTLEBLINK
#define N_ROWS 7
#define N_COLS 8

#define WS2812
#define N_LEDS 29

#define led_pos_eye(x) (0)
#endif

#if !defined(VERTICAL_MOUNTING) && !defined(HORIZONTAL_MOUNTING)
#error Please define either VERTICAL_MOUNTING or HORIZONTAL_MOUNTING
#endif

# ifdef LEDSQUARE
# ifndef N_LEDSQARE_ROWS
#error Please set N_LEDSQUARE_ROWS to indicate how the LED Sqaure array is formed.
# endif

# ifndef N_LEDSQARE_COLS
#error Please set N_LEDSQUARE_COLS to indicate how the LED Sqaure array is formed.
# endif

#define LEDS_PER_SQUARE_SIDE (5)
#define LEDS_PER_SQUARE (LEDS_PER_SQUARE_SIDE * LEDS_PER_SQUARE_SIDE)

#define N_ROWS (LEDS_PER_SQUARE_SIDE * N_LEDSQARE_ROWS)
#define N_COLS (LEDS_PER_SQUARE_SIDE * N_LEDSQARE_COLS)

#define WS2812
#define N_LEDS (N_ROWS * N_COLS)

#define led_pos_eye(x) (0)

#if defined(VERTICAL_MOUNTING) && N_LEDSQARE_COLS > 1
/* Multiple PWM outputs needed*/
#define PWM_CONTROLLERS_USED N_LEDSQARE_COLS

#elif defined(HORIZONTAL_MOUNTING) && N_LEDSQARE_ROWS > 1
#define PWM_CONTROLLERS_USED N_LEDSQARE_ROWS
#else 
#define PWM_CONTROLLERS_USED (1)
#endif


#define NEEDS_INITIALIZATION
#endif

#ifdef APA102
#define BYTES_PER_LED 4
#endif
#ifdef WS2812
#define BYTES_PER_LED 3
#endif

extern uint8_t led_pos_cart_x [N_LEDS];

extern uint8_t led_pos_cart_y [N_LEDS];


/* Polar cordinates*/
extern uint16_t led_pos_pol_ang [N_LEDS];

extern uint16_t led_pos_pol_rad [N_LEDS];

void led_initialization(void);


#endif /* INC_LED_POSITION_H_ */
