/// File: combineVectorElements.c

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "combineVectorElements.h"

/* Function Definitions */

/*
 * Arguments    : const double x[6144]
 *                double y[256]
 * Return Type  : void
 */
void b_combineVectorElements(const double x[6144], double y[256])
{
  int k;
  int xoffset;
  int j;
  memcpy(&y[0], &x[0], sizeof(double) << 8);
  for (k = 0; k < 23; k++) {
    xoffset = (k + 1) << 8;
    for (j = 0; j < 256; j++) {
      y[j] += x[xoffset + j];
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double y[24]
 * Return Type  : void
 */
void combineVectorElements(const emxArray_real_T *x, double y[24])
{
  int i;
  int xpageoffset;
  int k;
  if (x->size[0] == 0) {
    memset(&y[0], 0, 24U * sizeof(double));
  } else {
    for (i = 0; i < 24; i++) {
      xpageoffset = i * x->size[0];
      y[i] = x->data[xpageoffset];
      for (k = 2; k <= x->size[0]; k++) {
        y[i] += x->data[(xpageoffset + k) - 1];
      }
    }
  }
}

/*
 * File trailer for combineVectorElements.c
 *
 * [EOF]
 */
