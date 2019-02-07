/*
 * File: rdivide.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "rdivide.h"
#include "bbbox_voiceprintLookup_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *z
 * Return Type  : void
 */
void rdivide(const emxArray_real_T *x, const emxArray_real_T *y, emxArray_real_T
             *z)
{
  int i5;
  int loop_ub;
  i5 = z->size[0] * z->size[1];
  z->size[0] = x->size[0];
  z->size[1] = 24;
  emxEnsureCapacity_real_T1(z, i5);
  loop_ub = x->size[0] * x->size[1];
  for (i5 = 0; i5 < loop_ub; i5++) {
    z->data[i5] = x->data[i5] / y->data[i5];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */
