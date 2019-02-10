/// File: power.c


/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "power.h"
#include "bbbox_voiceprintLookup_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const double a[1024]
 *                double y[1024]
 * Return Type  : void
 */
void b_power(const double a[1024], double y[1024])
{
  int k;
  for (k = 0; k < 1024; k++) {
    y[k] = a[k] * a[k];
  }
}

/*
 * Arguments    : const double a[6144]
 *                double y[6144]
 * Return Type  : void
 */
void c_power(const double a[6144], double y[6144])
{
  int k;
  for (k = 0; k < 6144; k++) {
    y[k] = a[k] * a[k];
  }
}

/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *y
 * Return Type  : void
 */
void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int a_idx_0;
  unsigned int b_a_idx_0;
  int k;
  a_idx_0 = (unsigned int)a->size[0];
  b_a_idx_0 = (unsigned int)a->size[0];
  k = y->size[0];
  y->size[0] = (int)b_a_idx_0;
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < (int)a_idx_0; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/*
 * File trailer for power.c
 *
 * [EOF]
 */
