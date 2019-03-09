/// File: generateScore.h

#ifndef GENERATESCORE_H
#define GENERATESCORE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

extern int nModelNumber; // number of models in database
extern double cell_mega [1000][6144]; // the voicePrint multidimensional array

int goodResult;


/* Function Declarations */
extern void generateScore(const double modelsDatabase_f5[6144],
const double modelsDatabase_f6[6144],const double modelsDatabase_f7[6144],
const double modelsDatabase_f8[6144], const double modelsDatabase_f9[6144],
const double modelsDatabase_f10[6144],const double modelsDatabase_f11[6144],
const double modelsDatabase_f12[6144],const double modelsDatabase_f13[6144],
const double modelsDatabase_f14[6144], const emxArray_real_T *activeFeatures,const emxArray_boolean_T *activeMask,
const boolean_T noiseMask[24], const double Hl[24],const double Bl[24], double choices[1000], double scores[1000]);
#endif;



/*
 * File trailer for generateScore.h
 *
 * [EOF]
 */
