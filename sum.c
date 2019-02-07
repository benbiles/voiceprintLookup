/*
 * File: sum.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const double x[24]
 * Return Type  : double
 */
double sum(const double x[24])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 23; k++) {
    y += x[k + 1];
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
