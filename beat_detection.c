#include "beat_detection.h"

#define N_AVG 64
int32_t old_values[64] = {0};
uint8_t old_values_pnt = 0;

#define THRESHHOLD 100000

uint32_t beat_buffer[WINDOW_SIZE] = {0};
uint32_t pwr_sum_buffer[WINDOW_SIZE*2] = {0};
uint32_t beat_buffer_pnt = 0;

void calc_power (int32_t new_sample, uint32_t *power_out, uint32_t *debug_out) {
    old_values[old_values_pnt] = new_sample >> 8;
    old_values_pnt = (old_values_pnt + 1) % N_AVG;
    
    uint64_t pwr_sum = 0; 
    
    for (uint32_t i = 0; i < N_AVG; i++) {
        pwr_sum += old_values[i] * old_values[i];
    }
    
    pwr_sum_buffer[beat_buffer_pnt % (WINDOW_SIZE >> 4)] = pwr_sum;
    
    uint32_t median_pwr = 0;
    for (uint32_t i = 0; i < WINDOW_SIZE; ++i) {
        median_pwr += pwr_sum_buffer[i] >> 7;
    }
    
    if (pwr_sum < THRESHHOLD) {
        pwr_sum = 0;
    } else if (pwr_sum < median_pwr ) {
        pwr_sum = 0;
    }
    
    beat_buffer[beat_buffer_pnt] = (uint32_t)pwr_sum;
    beat_buffer_pnt = (beat_buffer_pnt + 1) % WINDOW_SIZE;
    
    //*power_out = median_pwr; 
    *power_out = bpm_detect(beat_buffer)*10000;
    *debug_out = pwr_sum;
    
    
    
}

uint32_t bpm_detect(uint32_t window_in[WINDOW_SIZE]) {
    
    detection_states state = WAIT_FOR_FIRST_SAMPLE;
    uint32_t beats_start[1000] = {0};
    uint32_t n_beats = 0;
    uint8_t trans_state_cnt = 0;
    
    for(int i = 0; i < WINDOW_SIZE; ++i) {
        switch (state) {
            case WAIT_FOR_FIRST_SAMPLE:
                if (0 != window_in[i]){
                    if (0 == trans_state_cnt) {
                        beats_start[n_beats++] = i;
                    } 
                    if (64 == trans_state_cnt) {
                        state = SIGNAL;
                        trans_state_cnt = 0;
                    } else {
                        trans_state_cnt ++;
                    }
                }
                // mark as first sample
                break;
            case SIGNAL:
                if (0 == window_in[i] ) {
                    if (32 == trans_state_cnt) {
                        state = WAIT_FOR_FIRST_SAMPLE;
                        trans_state_cnt = 0;
                    } else {
                        trans_state_cnt++;
                    }
                } else {
                    trans_state_cnt = 0;
                }
                break;
            default:
                // Should not happen.
                break;
        }
    }
    
    return n_beats;
    uint32_t samples_per_beat = 0;
    if (n_beats > 3) {
        uint32_t n_diff = n_beats - 1;
        uint32_t sample_diff[n_diff];
        for (int i = 0; i < n_diff; ++i) {
            sample_diff[i] = beats_start[i + 1] - beats_start[i];
        }
        uint32_t temp;
        
        samples_per_beat = n_beats;
        for (int i = 0; i < n_diff - 1; ++i) {
            for (int j = i + 1; j < n_diff; ++j) {
                if (sample_diff[j] < sample_diff[i]) {
                    temp = sample_diff[i];
                    sample_diff[i] = sample_diff[j];
                    sample_diff[j] = temp;
                }
            }
        }
       
        samples_per_beat = (sample_diff[n_beats >> 2] +
                sample_diff[(n_beats >> 2) + 1]) >> 1;// +
                /*sample_diff[(n_beats >> 2) - 1] + 
                sample_diff[(n_beats >> 2) + 2]) >> 2; */
        
    }
    return samples_per_beat;
}