/*
 * File: sort1.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "sort1.h"
#include "sortIdx.h"
#include "bbbox_voiceprintLookup_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : double x[4]
 *                int idx[4]
 * Return Type  : void
 */
void b_sort(double x[4], int idx[4])
{
  int i;
  int nNaNs;
  int ib;
  double x4[4];
  int k;
  int idx4[4];
  double xwork[4];
  signed char perm[4];
  int i2;
  int i3;
  int i4;
  for (i = 0; i < 4; i++) {
    idx[i] = 0;
    x4[i] = 0.0;
    idx4[i] = 0;
    xwork[i] = 0.0;
  }

  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 4; k++) {
    if (rtIsNaN(x[k])) {
      idx[3 - nNaNs] = k + 1;
      xwork[3 - nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = k + 1;
      x4[ib - 1] = x[k];
      if (ib == 4) {
        i = k - nNaNs;
        if (x4[0] <= x4[1]) {
          ib = 1;
          i2 = 2;
        } else {
          ib = 2;
          i2 = 1;
        }

        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }

        if (x4[ib - 1] <= x4[i3 - 1]) {
          if (x4[i2 - 1] <= x4[i3 - 1]) {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)i2;
            perm[2] = (signed char)i3;
            perm[3] = (signed char)i4;
          } else if (x4[i2 - 1] <= x4[i4 - 1]) {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)i2;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)ib;
            perm[1] = (signed char)i3;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)i2;
          }
        } else if (x4[ib - 1] <= x4[i4 - 1]) {
          if (x4[i2 - 1] <= x4[i4 - 1]) {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)i2;
            perm[3] = (signed char)i4;
          } else {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)ib;
            perm[2] = (signed char)i4;
            perm[3] = (signed char)i2;
          }
        } else {
          perm[0] = (signed char)i3;
          perm[1] = (signed char)i4;
          perm[2] = (signed char)ib;
          perm[3] = (signed char)i2;
        }

        idx[i - 3] = idx4[perm[0] - 1];
        idx[i - 2] = idx4[perm[1] - 1];
        idx[i - 1] = idx4[perm[2] - 1];
        idx[i] = idx4[perm[3] - 1];
        x[i - 3] = x4[perm[0] - 1];
        x[i - 2] = x4[perm[1] - 1];
        x[i - 1] = x4[perm[2] - 1];
        x[i] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }

  if (ib > 0) {
    for (i = 0; i < 4; i++) {
      perm[i] = 0;
    }

    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }

    for (k = 4; k - 3 <= ib; k++) {
      idx[(k - nNaNs) - ib] = idx4[perm[k - 4] - 1];
      x[(k - nNaNs) - ib] = x4[perm[k - 4] - 1];
    }
  }

  i = nNaNs >> 1;
  for (k = 1; k <= i; k++) {
    ib = idx[(k - nNaNs) + 3];
    idx[(k - nNaNs) + 3] = idx[4 - k];
    idx[4 - k] = ib;
    x[(k - nNaNs) + 3] = xwork[4 - k];
    x[4 - k] = xwork[(k - nNaNs) + 3];
  }

  if ((nNaNs & 1) != 0) {
    x[(i - nNaNs) + 4] = xwork[(i - nNaNs) + 4];
  }

  if (4 - nNaNs > 1) {
    for (i = 0; i < 4; i++) {
      idx4[i] = 0;
    }

    i3 = (4 - nNaNs) >> 2;
    i2 = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        i = i2 * i3;
        ib = 4 - (nNaNs + i);
        if (ib > i2) {
          b_merge(idx, x, i, i2, ib - i2, idx4, xwork);
        }
      }

      i = i2 << 1;
      i3 >>= 1;
      for (k = 1; k <= i3; k++) {
        b_merge(idx, x, (k - 1) * i, i2, i2, idx4, xwork);
      }

      i2 = i;
    }

    if (4 - nNaNs > i2) {
      b_merge(idx, x, 0, i2, 4 - (nNaNs + i2), idx4, xwork);
    }
  }
}

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void sort(emxArray_real_T *x)
{
  emxArray_int32_T *idx;
  int ib;
  int i;
  int n;
  int b_n;
  emxArray_int32_T *iwork;
  double x4[4];
  int idx4[4];
  emxArray_real_T *xwork;
  int nNaNs;
  int k;
  int wOffset;
  signed char perm[4];
  int i3;
  int i4;
  emxInit_int32_T(&idx, 2);
  ib = idx->size[0] * idx->size[1];
  idx->size[0] = 1;
  idx->size[1] = x->size[1];
  emxEnsureCapacity_int32_T(idx, ib);
  i = x->size[1];
  for (ib = 0; ib < i; ib++) {
    idx->data[ib] = 0;
  }

  if (x->size[1] != 0) {
    n = x->size[1];
    b_n = x->size[1];
    for (i = 0; i < 4; i++) {
      x4[i] = 0.0;
      idx4[i] = 0;
    }

    emxInit_int32_T1(&iwork, 1);
    i = x->size[1];
    ib = iwork->size[0];
    iwork->size[0] = i;
    emxEnsureCapacity_int32_T1(iwork, ib);
    for (ib = 0; ib < i; ib++) {
      iwork->data[ib] = 0;
    }

    emxInit_real_T(&xwork, 1);
    i = x->size[1];
    ib = xwork->size[0];
    xwork->size[0] = i;
    emxEnsureCapacity_real_T(xwork, ib);
    for (ib = 0; ib < i; ib++) {
      xwork->data[ib] = 0.0;
    }

    nNaNs = 1;
    ib = 0;
    for (k = 0; k < b_n; k++) {
      if (rtIsNaN(x->data[k])) {
        idx->data[b_n - nNaNs] = k + 1;
        xwork->data[b_n - nNaNs] = x->data[k];
        nNaNs++;
      } else {
        ib++;
        idx4[ib - 1] = k + 1;
        x4[ib - 1] = x->data[k];
        if (ib == 4) {
          i = k - nNaNs;
          if (x4[0] <= x4[1]) {
            ib = 1;
            wOffset = 2;
          } else {
            ib = 2;
            wOffset = 1;
          }

          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }

          if (x4[ib - 1] <= x4[i3 - 1]) {
            if (x4[wOffset - 1] <= x4[i3 - 1]) {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)wOffset;
              perm[2] = (signed char)i3;
              perm[3] = (signed char)i4;
            } else if (x4[wOffset - 1] <= x4[i4 - 1]) {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)wOffset;
              perm[3] = (signed char)i4;
            } else {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)i4;
              perm[3] = (signed char)wOffset;
            }
          } else if (x4[ib - 1] <= x4[i4 - 1]) {
            if (x4[wOffset - 1] <= x4[i4 - 1]) {
              perm[0] = (signed char)i3;
              perm[1] = (signed char)ib;
              perm[2] = (signed char)wOffset;
              perm[3] = (signed char)i4;
            } else {
              perm[0] = (signed char)i3;
              perm[1] = (signed char)ib;
              perm[2] = (signed char)i4;
              perm[3] = (signed char)wOffset;
            }
          } else {
            perm[0] = (signed char)i3;
            perm[1] = (signed char)i4;
            perm[2] = (signed char)ib;
            perm[3] = (signed char)wOffset;
          }

          idx->data[i - 2] = idx4[perm[0] - 1];
          idx->data[i - 1] = idx4[perm[1] - 1];
          idx->data[i] = idx4[perm[2] - 1];
          idx->data[i + 1] = idx4[perm[3] - 1];
          x->data[i - 2] = x4[perm[0] - 1];
          x->data[i - 1] = x4[perm[1] - 1];
          x->data[i] = x4[perm[2] - 1];
          x->data[i + 1] = x4[perm[3] - 1];
          ib = 0;
        }
      }
    }

    wOffset = b_n - nNaNs;
    if (ib > 0) {
      for (i = 0; i < 4; i++) {
        perm[i] = 0;
      }

      if (ib == 1) {
        perm[0] = 1;
      } else if (ib == 2) {
        if (x4[0] <= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }

      for (k = 1; k <= ib; k++) {
        idx->data[(wOffset - ib) + k] = idx4[perm[k - 1] - 1];
        x->data[(wOffset - ib) + k] = x4[perm[k - 1] - 1];
      }
    }

    i = ((nNaNs - 1) >> 1) + 1;
    for (k = 1; k < i; k++) {
      ib = idx->data[wOffset + k];
      idx->data[wOffset + k] = idx->data[b_n - k];
      idx->data[b_n - k] = ib;
      x->data[wOffset + k] = xwork->data[b_n - k];
      x->data[b_n - k] = xwork->data[wOffset + k];
    }

    if (((nNaNs - 1) & 1) != 0) {
      x->data[wOffset + i] = xwork->data[wOffset + i];
    }

    wOffset = (n - nNaNs) + 1;
    i = 2;
    if (wOffset > 1) {
      if (n >= 256) {
        ib = wOffset >> 8;
        if (ib > 0) {
          for (i = 1; i <= ib; i++) {
            merge_pow2_block(idx, x, (i - 1) << 8);
          }

          i = ib << 8;
          ib = wOffset - i;
          if (ib > 0) {
            merge_block(idx, x, i, ib, 2, iwork, xwork);
          }

          i = 8;
        }
      }

      merge_block(idx, x, 0, wOffset, i, iwork, xwork);
    }

    emxFree_real_T(&xwork);
    emxFree_int32_T(&iwork);
  }

  emxFree_int32_T(&idx);
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
