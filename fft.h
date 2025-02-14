/// File: fft.h


#ifndef FFT_H
#define FFT_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void fft(const double x[1024], creal_T y[1024]);

#endif

/*
 * File trailer for fft.h
 *
 * [EOF]
 */
