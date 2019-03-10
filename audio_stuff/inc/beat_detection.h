#include "stdint.h"

#define WINDOW_SIZE 3250

void calc_power (int32_t new_sample);
uint32_t bpm_detect(uint32_t window_in[WINDOW_SIZE]);

typedef enum detection_state {
    WAIT_FOR_FIRST_SAMPLE,
    NO_SIGNAL,
    SIGNAL
    
}detection_states;
    
