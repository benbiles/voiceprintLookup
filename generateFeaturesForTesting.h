/*
 * File: generateFeaturesForTesting.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

#ifndef GENERATEFEATURESFORTESTING_H
#define GENERATEFEATURESFORTESTING_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void generateFeaturesForTesting(emxArray_real_T *xSeparated,
  emxArray_real_T *xPostfiltered, const double window[1024], emxArray_real_T
  *activeFeatures, emxArray_boolean_T *activeMask, boolean_T noiseMask[24],
  double Hl[24], double Bl[24]);

#endif

/*
 * File trailer for generateFeaturesForTesting.h
 *
 * [EOF]
 */
