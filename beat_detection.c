#include "beat_detection.h"

#define N_AVG 64
int32_t old_values[64] = {0};
uint8_t old_values_pnt = 0;

#define THRESHHOLD 100000

#define MEDIAN_ATTACK 20
#define MEDIAN_DECAY 300

uint32_t beat_buffer[WINDOW_SIZE] = {0};
uint32_t pwr_sum_buffer[WINDOW_SIZE*2] = {0};
uint32_t beat_buffer_pnt = 0;

detection_states state = WAIT_FOR_FIRST_SAMPLE;
uint8_t trans_state_cnt = 0;
uint32_t median_pwr = 0;
int32_t median_slope = 0;
uint32_t median_max = 0;

void calc_power (int32_t new_sample, uint32_t *power_out, uint32_t *debug_out) {
    old_values[old_values_pnt] = new_sample >> 8;
    old_values_pnt = (old_values_pnt + 1) % N_AVG;
    
    uint64_t pwr_sum = 0; 
    
    for (uint32_t i = 0; i < N_AVG; i++) {
        pwr_sum += old_values[i] * old_values[i];
    }
    
    pwr_sum_buffer[beat_buffer_pnt % (212)] = pwr_sum;
    
    *debug_out = pwr_sum;

    
    if (pwr_sum > median_pwr) {
        median_slope += MEDIAN_ATTACK;
        median_max = pwr_sum;
    } else {
        if (median_pwr > ((median_max >> 1) + (median_max >> 2))) {
            if (median_slope > -MEDIAN_DECAY) {
                median_slope -= (MEDIAN_DECAY >> 2);
            } else {
                median_slope = -MEDIAN_DECAY;
            }
        } else if (median_pwr > ((median_max >> 1))) {
            median_slope = -MEDIAN_DECAY >> 2;
        } else {
            median_slope = -1;
        }
        pwr_sum = 0;
    }
    
    if (((int32_t)median_pwr + median_slope) < 0) {
        median_pwr = 0;
        median_slope = 0;
    } else {
        median_pwr += median_slope;
    }
    
    beat_buffer[beat_buffer_pnt] = (uint32_t)pwr_sum;
    beat_buffer_pnt = (beat_buffer_pnt + 1) % WINDOW_SIZE;
    switch (state) {
        case WAIT_FOR_FIRST_SAMPLE:
            if (0 != pwr_sum){
                if (16 == trans_state_cnt) {
                    state = SIGNAL;
                    trans_state_cnt = 0;
                } else {
                    trans_state_cnt ++;
                }
            } else {
                if (trans_state_cnt > 0) {
                    trans_state_cnt--;
                }
                trans_state_cnt = 0;
            }
            break;
        case SIGNAL:
            if(trans_state_cnt == 32) {
                state = NO_SIGNAL;
                trans_state_cnt = 0;
            } else {
                trans_state_cnt++;
            }
            break;
        case NO_SIGNAL:
            if (0 == pwr_sum ) {
                if (16 == trans_state_cnt) {
                    state = WAIT_FOR_FIRST_SAMPLE;
                    trans_state_cnt = 0;
                } else {
                    trans_state_cnt++;
                }
            } else {
                //trans_state_cnt = 0;
            }
            break;
        default:
            // Should not happen.
            break;
    }
    
    
    *power_out = (state) * 180000 ;
    //*power_out = median_pwr; 
    
    
    
}

uint32_t bpm_detect(uint32_t window_in[WINDOW_SIZE]) {
    
    
    uint32_t beats_start[1000] = {0};
    uint32_t n_beats = 0;
   
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