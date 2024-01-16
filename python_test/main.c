# include <stdio.h>
# include "pattern_generate.h"

extern uint8_t led_buffer[FRAME_SIZE];

volatile uint32_t random_2 = 22222;

int main()
{
    
    uint32_t random_hue_2 = random_2 % 1024;
    random_2 = (random_2 * 196314165) + 907633515;



	tx_led_buffer();
    tx_led_buffer();
    tx_led_buffer();

}