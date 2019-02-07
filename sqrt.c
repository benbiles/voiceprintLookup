/*
 * File: sqrt.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : double *x
 * Return Type  : void
 */
void b_sqrt(double *x)
{
  *x = sqrt(*x);
}

/*
 * Arguments    : double x[256]
 * Return Type  : void
 */
void c_sqrt(double x[256])
{
  int k;
  for (k = 0; k < 256; k++) {
    x[k] = sqrt(x[k]);
  }
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */
