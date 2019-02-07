/*
 * File: _coder_bbbox_voiceprintLookup_api.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

#ifndef _CODER_BBBOX_VOICEPRINTLOOKUP_API_H
#define _CODER_BBBOX_VOICEPRINTLOOKUP_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_bbbox_voiceprintLookup_api.h"

/* Type Definitions */
#ifndef typedef_cell_0
#define typedef_cell_0

typedef struct {
  real_T f1;
  real_T f2;
  real_T f3;
  real_T f4;
  real_T f5[6144];
  real_T f6[6144];
  real_T f7[6144];
  real_T f8[6144];
} cell_0;

#endif                                 /*typedef_cell_0*/

#ifndef typedef_cell_1
#define typedef_cell_1

typedef struct {
  char_T f1[18];
} cell_1;

#endif                                 /*typedef_cell_1*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void bbbox_voiceprintLookup(char_T wavFileA[20], char_T wavFileB[20],
  char_T databaseFile[17], char_T voiceId[18]);
extern void bbbox_voiceprintLookup_api(const mxArray * const prhs[3], int32_T
  nlhs, const mxArray *plhs[1]);
extern void bbbox_voiceprintLookup_atexit(void);
extern void bbbox_voiceprintLookup_initialize(void);
extern void bbbox_voiceprintLookup_terminate(void);
extern void bbbox_voiceprintLookup_xil_terminate(void);
extern void loadDatabaseFromFile(char_T fileNameDatabase[17], cell_0
  *varDatabase);
extern void loadDatabaseFromFile_api(const mxArray * const prhs[1], int32_T nlhs,
  const mxArray *plhs[1]);
extern void testWaveWithModels(char_T fileNameWaveSeparated[20], char_T
  fileNameWavePostfiltered[20], cell_0 *modelStructure, cell_1 *choices, real_T
  scores[4]);
extern void testWaveWithModels_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[2]);

#endif

/*
 * File trailer for _coder_bbbox_voiceprintLookup_api.h
 *
 * [EOF]
 */
