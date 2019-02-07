/*
 * File: bbbox_voiceprintLookup_initialize.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "bbbox_voiceprintLookup_initialize.h"
#include "fileManager.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void bbbox_voiceprintLookup_initialize(void)
{
  rt_InitInfAndNaN(8U);
  filedata_init();
}

/*
 * File trailer for bbbox_voiceprintLookup_initialize.c
 *
 * [EOF]
 */
