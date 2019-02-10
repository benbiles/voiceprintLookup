/// File: filter.c


/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "filter.h"
#include "bbbox_voiceprintLookup_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void filter(const emxArray_real_T *x, emxArray_real_T *y)
{
  unsigned int x_idx_0;
  int k;
  int nx;
  int naxpy;
  int nx_m_nb;
  int j;
  x_idx_0 = (unsigned int)x->size[0];
  k = y->size[0];
  y->size[0] = (int)x_idx_0;
  emxEnsureCapacity_real_T(y, k);
  nx = x->size[0];
  naxpy = y->size[0];
  k = y->size[0];
  y->size[0] = naxpy;
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < naxpy; k++) {
    y->data[k] = 0.0;
  }

  if (x->size[0] >= 4) {
    for (k = 0; k < 2; k++) {
      for (j = k; j < nx; j++) {
        y->data[j] += (1.0 + -1.95 * (double)k) * x->data[j - k];
      }
    }
  } else {
    nx_m_nb = (x->size[0] > 2);
    k = 1;
    while (k <= nx_m_nb) {
      for (j = 0; j < 2; j++) {
        y->data[j] += x->data[0] * (1.0 + -1.95 * (double)j);
      }

      k = 2;
    }

    naxpy = x->size[0] - nx_m_nb;
    while (nx_m_nb + 1 <= nx) {
      for (j = 1; j <= naxpy; j++) {
        y->data[(nx_m_nb + j) - 1] += x->data[nx_m_nb] * (1.0 + -1.95 * (double)
          (j - 1));
      }

      naxpy--;
      nx_m_nb++;
    }
  }
}

/*
 * File trailer for filter.c
 *
 * [EOF]
 */
