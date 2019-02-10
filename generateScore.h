/// File: generateScore.h

#ifndef GENERATESCORE_H
#define GENERATESCORE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void generateScore(const double modelsDatabase_f5[6144], const double
  modelsDatabase_f6[6144], const double modelsDatabase_f7[6144], const double
  modelsDatabase_f8[6144], const emxArray_real_T *activeFeatures, const
  emxArray_boolean_T *activeMask, const boolean_T noiseMask[24], const double
  Hl[24], const double Bl[24], double choices[4], double scores[4]);

#endif

/*
 * File trailer for generateScore.h
 *
 * [EOF]
 */
