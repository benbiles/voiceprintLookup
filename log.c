/*
 * File: log.c
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
#include "log.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void b_log(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[0] * 24;
  for (k = 0; k < nx; k++) {
    x->data[k] = log(x->data[k]);
  }
}

/*
 * Arguments    : double x[6144]
 * Return Type  : void
 */
void c_log(double x[6144])
{
  int k;
  for (k = 0; k < 6144; k++) {
    x[k] = log(x[k]);
  }
}

/*
 * File trailer for log.c
 *
 * [EOF]
 */
