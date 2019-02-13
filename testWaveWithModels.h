/// File: testWaveWithModels.h

#ifndef TESTWAVEWITHMODELS_H
#define TESTWAVEWITHMODELS_H

/* Include Files */


#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void testWaveWithModels(const char *fileNameWaveSeparated[255],const char
  *fileNameWavePostfiltered[255], const cell_0 *modelStructure, cell_1 *choices,
  double scores[1000]);

#endif

extern char voiceId[20];

/*
 * File trailer for testWaveWithModels.h
 *
 * [EOF]
 */
