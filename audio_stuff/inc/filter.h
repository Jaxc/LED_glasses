/******************************* SOURCE LICENSE *********************************
Copyright (c) 2019 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to the Licensee to
use the following Information for academic, non-profit, or government-sponsored research purposes.
Use of the following Information under this License is restricted to NON-COMMERCIAL PURPOSES ONLY.
Commercial use of the following Information requires a separately executed written license agreement.

This Information is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/

// A commercial license for MicroModeler DSP can be obtained at http://www.micromodeler.com/launch.jsp

// Begin header file, filter1.h

#ifndef FILTER1_H_ // Include guards
#define FILTER1_H_

#include "main.h"

static const int filter1_numStages = 2;
static const int filter1_coefficientLength = 10;
extern short filter1_coefficients[10];

typedef struct
{
    short state[8];
    short output;
} filter_type;

typedef struct
{
    short *pInput;
    short *pOutput;
    short *pState;
    short *pCoefficients;
    short count;
} filter1_executionState;

#define filter1_writeInput( pThis, input )  \
    filter1_filterBlock( pThis, &(input), &(pThis)->output, 1 );

#define filter1_readOutput( pThis )  \
    (pThis)->output

 int filter_filterBlock( int16_t * pInput, int16_t * pOutput, uint16_t count );
#define filter1_outputToFloat( output )  \
    (( (1.0f/16384) * (output) ))

#define filter1_inputFromFloat( input )  \
    ((short)(32768f * (input)))

 void filter1_filterBiquad_3_14_15( filter1_executionState * pExecState );
#endif // FILTER1_H_

