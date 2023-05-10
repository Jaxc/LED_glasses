/*
 * led_position.c
 *
 *  Created on: Dec 29, 2019
 *      Author: jaxc
 */

#include "pattern_generate.h"

#ifdef NEEDS_INITIALIZATION
#include <math.h>
#endif


#ifdef GLASSESV1

uint8_t led_pos_cart_x [N_LEDS] = {

            /* Right eye */
              7, 6, 5, 4, 3, 2,     //Row 0
           1, 2, 3, 4, 5, 6, 7,     //Row 1
        7, 6, 5, 4, 3, 2, 1, 0,     //Row 2
        0, 1, 2, 3, 4, 5, 6, 7,     //Row 3
           6, 5, 4, 3, 2, 1,        //Row 4
           1, 2, 3, 4, 5,           //Row 5
              4, 3, 2,              //Row 6

            /* Left eye  */
        7, 6, 5, 4, 3, 2,           //Row 0
        1, 2, 3, 4, 5, 6, 7,        //Row 1
        7, 6, 5, 4, 3, 2, 1, 0,     //Row 2
        0, 1, 2, 3, 4, 5, 6, 7,     //Row 3
           6, 5, 4, 3, 2, 1,        //Row 4
           1, 2, 3, 4, 5,           //Row 5
              4, 3, 2,              //Row 6
};

uint8_t led_pos_cart_y [N_LEDS] = {

            /* Right eye */
              0, 0, 0, 0, 0, 0,     //Row 0
           1, 1, 1, 1, 1, 1, 1,     //Row 1
        2, 2, 2, 2, 2, 2, 2, 2,     //Row 2
        3, 3, 3, 3, 3, 3, 3, 3,     //Row 3
           4, 4, 4, 4, 4, 4,        //Row 4
           5, 5, 5, 5, 5,           //Row 5
              6, 6, 6,              //Row 6

            /* Left eye  */
        0, 0, 0, 0, 0, 0,           //Row 0
        1, 1, 1, 1, 1, 1, 1,        //Row 1
        2, 2, 2, 2, 2, 2, 2, 2,     //Row 2
        3, 3, 3, 3, 3, 3, 3, 3,     //Row 3
           4, 4, 4, 4, 4, 4,        //Row 4
              5, 5, 5, 5, 5,        //Row 5
                 6, 6, 6,           //Row 6
};


/* Polar cordinates*/
uint32_t led_pos_pol_ang [N_LEDS] = {

            /* Right eye */
                                 589349511,  474898961,  316933406,  112889901, 4182077395, 3978033890,
                    3682454950, 3855092283, 4127508389,  167458907,  439875013,  612512346,  718871567,
         883505841,  813640877,  671803662,  316933406, 3978033890, 3623163634, 3481326419, 3411461455,
        3221225472, 3221225472, 3221225472, 3221225472, 1073741824, 1073741824, 1073741824, 1073741824,
                    1333842771, 1475679986, 1830550242, 2464417054, 2819287310, 2961124525,
                    2759995994, 2587358661, 2314942555, 1980024741, 1707608635,
                                2034593747, 2260373549, 2464417054,

            /* Left eye  */
        589349511,  474898961,  316933406,  112889901, 4182077395, 3978033890,
       3682454950, 3855092283, 4127508389,  167458907,  439875013,  612512346,  718871567,
        883505841,  813640877,  671803662,  316933406, 3978033890, 3623163634, 3481326419, 3411461455,
       3221225472, 3221225472, 3221225472, 3221225472, 1073741824, 1073741824, 1073741824, 1073741824,
                   1333842771, 1475679986, 1830550242, 2464417054, 2819287310, 2961124525,
                               2759995994, 2587358661, 2314942555, 1980024741, 1707608635,
                                           2034593747, 2260373549, 2464417054,
};

uint32_t led_pos_pol_rad [N_LEDS] = {

            /* Right eye */
                                3938440823, 3638440823, 3125047732, 2833682971, 2833682971, 3125047732,
                    2982924950, 2329273054, 1920767766, 1920767766, 2329273054, 2982924950, 3755839946,
        3391472759, 2508703855, 1679662686, 1041682577, 1041682577, 1679662686, 2508703855, 3391472759,
        3260982276, 2329273054, 1397563832,  465854610,  465854610, 1397563832, 2329273054, 3260982276,
                    2508703855, 1679662686, 1041682577, 1041682577, 1679662686, 2508703855,
                    2982924950, 2329273054, 1920767766, 1920767766, 2329273054,
                                            2833682971, 2833682971, 3125047732,

            /* Left eye  */
        3938440823, 3638440823, 3125047732, 2833682971, 2833682971, 3125047732,
        2982924950, 2329273054, 1920767766, 1920767766, 2329273054, 2982924950, 3755839946,
        3391472759, 2508703855, 1679662686, 1041682577, 1041682577, 1679662686, 2508703855, 3391472759,
        3260982276, 2329273054, 1397563832,  465854610,  465854610, 1397563832, 2329273054, 3260982276,
                    2508703855, 1679662686, 1041682577, 1041682577, 1679662686, 2508703855,
                                2982924950, 2329273054, 1920767766, 1920767766, 2329273054,
                                            2833682971, 2833682971, 3125047732,
};


#endif

#ifdef BOTTLEBLINK

uint8_t led_pos_cart_x [N_LEDS] = {

   /* dummy data*/
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8
};

uint8_t led_pos_cart_y [N_LEDS] = {

   /* dummy data*/
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8
};


/* Polar cordinates*/
uint32_t led_pos_pol_ang [N_LEDS] = {

   /* dummy data*/
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8
};

uint32_t led_pos_pol_rad [N_LEDS] = {

   /* Middle LED */
   0,

   /*First ring*/
   1, 1, 1, 1,

   /* Second ring*/
   2, 2, 2, 2, 2, 2, 2, 2,

   /* Third ring*/
   3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};

#endif

#ifdef LEDSQUARE

uint8_t led_pos_cart_x [N_LEDS];

uint8_t led_pos_cart_y [N_LEDS];

/* Polar cordinates*/
uint32_t led_pos_pol_rad [N_LEDS];

uint32_t led_pos_pol_ang [N_LEDS];

uint32_t led_pwm_controller_mapping [N_LEDS];

void led_init_internal(void) {
   uint8_t single_square_x [LEDS_PER_SQUARE];
   uint8_t single_square_y [LEDS_PER_SQUARE];

   /* Init led_pos_pol_rad */
   float origo_x = ((float)(N_COLS - 1)) / 2;
   float origo_y = ((float)(N_ROWS - 1)) / 2;

   float temp_array[N_LEDS];
   float max_distance = 0.0f;

   float max_distance_reciprocal;

#ifdef VERTICAL_MOUNTING
   float reference_angle_x = 1;
   float reference_angle_y = 0;
#else
   float reference_angle_x = 0;
   float reference_angle_y = 1;
#endif

   /* First a map for each square is created */
#ifdef VERTICAL_MOUNTING
   for(uint8_t row = 0; row < LEDS_PER_SQUARE_SIDE; row++) {
      uint32_t row_offset = row * LEDS_PER_SQUARE_SIDE;
      for(uint8_t col = 0; col < LEDS_PER_SQUARE_SIDE; col++) {
         if (0 == (row % 2)) {
            single_square_x[row_offset + col] = col;
         } else {
            single_square_x[row_offset + col] = LEDS_PER_SQUARE_SIDE - col - 1;
         }
      }
   }

   for(uint32_t row = 0; row < LEDS_PER_SQUARE_SIDE; row++) {
      uint32_t row_offset = row * LEDS_PER_SQUARE_SIDE;
      /* Value for each led is simply the row number */
      for(uint32_t j = 0; j < LEDS_PER_SQUARE_SIDE; j ++) {
         single_square_y[row_offset + j] = row;
      }
   }
#endif

   /* Init led_pos_cart_x */
#ifdef VERTICAL_MOUNTING

   for(uint32_t square_col = 0; square_col < N_LEDSQARE_COLS; square_col ++) {
      uint32_t col_offset = square_col * N_LEDSQARE_ROWS * LEDS_PER_SQUARE;

      for(uint32_t row = 0; row < N_LEDSQARE_ROWS; row++) {
         uint32_t row_offset = row * LEDS_PER_SQUARE;


         for(uint8_t i = 0; i < LEDS_PER_SQUARE_SIDE; i++) {
            uint32_t internal_row_offset = i * LEDS_PER_SQUARE_SIDE;
            for(uint8_t j = 0; j < LEDS_PER_SQUARE_SIDE; j++) {
               led_pos_cart_x[row_offset + col_offset + internal_row_offset + j] = single_square_x[internal_row_offset + j] + square_col * LEDS_PER_SQUARE_SIDE ;
            }
         }
      }
   }
#else
   for(uint32_t square_row = 0; square_row < N_LEDSQARE_ROWS; square_row++) {
      for(uint32_t col = 0; col < N_COLS; col++) {
         uint32_t row_offset = col * LEDS_PER_SQUARE_SIDE + LEDS_PER_SQUARE * N_LEDSQARE_COLS * square_row;
         /* Value for each led is simply the row number */
         for(uint32_t row = 0; row < LEDS_PER_SQUARE_SIDE; row++) {
            led_pos_cart_x[row_offset + row] = col;
         }
   }
   }
#endif

/* Init led_pos_cart_y */
#ifdef VERTICAL_MOUNTING
   for(uint32_t square_col = 0; square_col < N_LEDSQARE_COLS; square_col ++) {
      uint32_t col_offset = square_col * N_LEDSQARE_ROWS * LEDS_PER_SQUARE;

      for(uint32_t row = 0; row < N_LEDSQARE_ROWS; row++) {
         uint32_t row_offset = row * LEDS_PER_SQUARE;


         for(uint8_t i = 0; i < LEDS_PER_SQUARE_SIDE; i++) {
            uint32_t internal_row_offset = i * LEDS_PER_SQUARE_SIDE;
            for(uint8_t j = 0; j < LEDS_PER_SQUARE_SIDE; j++) {
               led_pos_cart_y[row_offset + col_offset + internal_row_offset + j] = single_square_y[internal_row_offset + j] + row * LEDS_PER_SQUARE_SIDE ;
            }
         }
      }
   }
#else
   for(uint32_t square_row = 0; square_row < N_LEDSQARE_ROWS; square_row++) {
      for(uint32_t current_square = 0; current_square < N_LEDSQARE_COLS; current_square++) {
         /* For each Ledsquare unit: */
         uint32_t square_offset = current_square * LEDS_PER_SQUARE + LEDS_PER_SQUARE * N_LEDSQARE_COLS * square_row;
         for(uint32_t row = 0; row < LEDS_PER_SQUARE_SIDE; row++) {
            uint32_t row_offset = square_offset + row * LEDS_PER_SQUARE_SIDE;
            /* For each row in a single row of squares: */
            if (1 == (row % 2) ){
               /* Even rows are numbered 0 to N_ROWS - 1*/
               for(uint8_t j = 0; j < LEDS_PER_SQUARE_SIDE; j ++) {
                  led_pos_cart_y[row_offset + j] = j + (N_ROWS - LEDS_PER_SQUARE_SIDE) * (N_LEDSQARE_ROWS - square_row - 1);
               }
            } else {
               /* Odd rows are numbered N_ROWS to 0*/
               for(uint8_t j = 0; j < LEDS_PER_SQUARE_SIDE; j ++) {
                  led_pos_cart_y[row_offset + j] = ((N_ROWS - LEDS_PER_SQUARE_SIDE)*(N_LEDSQARE_ROWS - square_row)) - j - 1;
               }
            }
         }
      }
   }
#endif

/* Init led_pos_pol_rad */

   for(uint32_t square_col = 0; square_col < N_LEDSQARE_COLS; square_col ++) {
      uint32_t col_offset = square_col * N_LEDSQARE_ROWS * LEDS_PER_SQUARE;

      for(uint32_t row = 0; row < N_LEDSQARE_ROWS; row++) {
         uint32_t row_offset = row * LEDS_PER_SQUARE;


         for(uint8_t i = 0; i < LEDS_PER_SQUARE_SIDE; i++) {
            uint32_t internal_row_offset = i * LEDS_PER_SQUARE_SIDE;
            for(uint8_t j = 0; j < LEDS_PER_SQUARE_SIDE; j++) {
               uint32_t led_index = row_offset + col_offset + internal_row_offset + j;


               temp_array[led_index] = sqrt(((float)led_pos_cart_x[led_index]-origo_x)*((float)led_pos_cart_x[led_index]-origo_x) + ((float)led_pos_cart_y[led_index]-origo_y) * ((float)led_pos_cart_y[led_index]-origo_y));
               if (temp_array[led_index] > max_distance) {
                  max_distance = temp_array[led_index];
               }
            }
         }
      }
   }

   max_distance_reciprocal = 1 / max_distance;

   for(uint32_t i = 0; i < N_COLS; i++) {
      uint32_t row_offset = i * N_ROWS;
      for(uint32_t j = 0; j < N_ROWS; j++) {
         float distance_normalized = temp_array[row_offset + j] * max_distance_reciprocal;
         uint32_t int_distance = (uint32_t)floor(distance_normalized * (float)UINT32_MAX);
         led_pos_pol_rad[row_offset + j] = int_distance;
      }
   }



/* Init led_pos_pol_ang*/
   for(uint32_t square_col = 0; square_col < N_LEDSQARE_COLS; square_col ++) {
      uint32_t col_offset = square_col * N_LEDSQARE_ROWS * LEDS_PER_SQUARE;

      for(uint32_t row = 0; row < N_LEDSQARE_ROWS; row++) {
         uint32_t row_offset = row * LEDS_PER_SQUARE;


         for(uint8_t i = 0; i < LEDS_PER_SQUARE_SIDE; i++) {
            uint32_t internal_row_offset = i * LEDS_PER_SQUARE_SIDE;
            for(uint8_t j = 0; j < LEDS_PER_SQUARE_SIDE; j++) {
               uint32_t led_index = row_offset + col_offset + internal_row_offset + j;

               volatile float diff_x = origo_x - (float)led_pos_cart_x[led_index];
               volatile float diff_y = origo_y - (float)led_pos_cart_y[led_index];


               float temp_value = atan2(diff_x, diff_y);

               temp_value += M_PI;

               temp_value = temp_value / (2 * M_PI);

               led_pos_pol_ang[led_index] = (uint32_t)(temp_value * (float)UINT32_MAX);
            }
         }
      }
   }
}

#endif


void led_initialization(void) {
#ifdef NEEDS_INITIALIZATION
   led_init_internal();
#endif
}
