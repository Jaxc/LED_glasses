/* Coefficients taken from http://www.micromodeler.com/dsp/ */

#include "../../audio_stuff/inc/filter.h"


filter_type filter_state = {0};

int16_t filter_coefficients[10] =
{
// Scaled for a 16x16:64 Direct form 1 IIR filter with:
// Feedback shift = 14
// Output shift = 14
// Input  has a maximum value of 1, scaled by 2^15
// Output has a maximum value of 1.3748823485402948, scaled by 2^14

    174, 174, 0, 15878, 0,// b0 Q13(0.0212), b1 Q13(0.0212), b2 Q13(0.00), a1 Q14(0.969), a2 Q14(0.00)
    8, 16, 8, 32219, -15879// b0 Q14(0.000488), b1 Q14(0.000977), b2 Q14(0.000488), a1 Q14(1.97), a2 Q14(-0.969)

};


 int decimation_filter( int16_t * samples_in, int16_t * samples_out, uint32_t count )
{
    filter1_executionState executionState;          // The executionState structure holds call data, minimizing stack reads and writes
    if( ! count ) return 0;                         // If there are no input samples, return immediately
    executionState.pInput = samples_in;                 // Pointers to the input and output buffers that each call to filterBiquad() will use
    executionState.pOutput = samples_out;               // - pInput and pOutput can be equal, allowing reuse of the same memory.
    executionState.count = count;                   // The number of samples to be processed
    executionState.pState = filter_state.state;
    executionState.pCoefficients = filter_coefficients;    // Each call to filterBiquad() will advance pState and pCoefficients to the next biquad

     // The 1st call to filter1_filterBiquad() reads from the caller supplied input buffer and writes to the output buffer.
     // The remaining calls to filterBiquad() recycle the same output buffer, so that multiple intermediate buffers are not required.

     filter1_filterBiquad_3_14_15( &executionState );        // Run biquad #0
     executionState.pInput = executionState.pOutput;         // The remaining biquads will now re-use the same output buffer.

     filter1_filterBiquad_3_14_15( &executionState );        // Run biquad #1

     // At this point, the caller-supplied output buffer will contain the filtered samples and the input buffer will contain the unmodified input samples.
     return count;       // Return the number of samples processed, the same as the number of input samples

 }

  void filter1_filterBiquad_3_14_15( filter1_executionState * pExecState )
 {
     // Read state variables
     short w0, x0;
     short w1 = pExecState->pState[0];
     short w2 = pExecState->pState[1];

     // Read coefficients into work registers
     short b0 = *(pExecState->pCoefficients++);
     short b1 = *(pExecState->pCoefficients++);
     short b2 = *(pExecState->pCoefficients++);
     short a1 = *(pExecState->pCoefficients++);
     short a2 = *(pExecState->pCoefficients++);

     // Read source and target pointers
     short *pInput  = pExecState->pInput;
     short *pOutput = pExecState->pOutput;
     short count = pExecState->count;
     long accumulator;

     // Loop for all samples in the input buffer
     while( count-- )
     {
         // Read input sample
         x0 = *(pInput++);

         // Run feedback part of filter
         accumulator  = (long)w2 * a2;
         accumulator += (long)w1 * a1;
         accumulator += (long)x0  << 3;

         w0 = accumulator  >> 14;

         // Run feedforward part of filter
         accumulator  = (long)w0 * b0;
         accumulator += (long)w1 * b1;
         accumulator += (long)w2 * b2;

         w2 = w1;        // Shuffle history buffer
         w1 = w0;

         // Write output
         *(pOutput++) = accumulator  >> 15;
     }

     // Write state variables
     *(pExecState->pState++) = w1;
     *(pExecState->pState++) = w2;


 }


