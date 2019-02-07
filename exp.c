/*
 * File: exp.c
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
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void b_exp(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[0] * 24;
  for (k = 0; k < nx; k++) {
    x->data[k] = exp(x->data[k]);
  }
}

/*
 * Arguments    : double x[6144]
 * Return Type  : void
 */
void c_exp(double x[6144])
{
  int k;
  for (k = 0; k < 6144; k++) {
    x[k] = exp(x[k]);
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
