#include "stdint.h"

#define WINDOW_SIZE 3250

void calc_power (int32_t new_sample, uint32_t *power_out);
uint32_t bpm_detect(uint32_t window_in[WINDOW_SIZE]);

typedef enum detection_state {
    NO_SIGNAL,
    WAIT_FOR_FIRST_SAMPLE,
    SIGNAL
}detection_states;
    