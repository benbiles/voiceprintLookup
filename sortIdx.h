/// File: sortIdx.h

#ifndef SORTIDX_H
#define SORTIDX_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void b_merge(int idx[4], double x[4], int offset, int np, int nq, int
                    iwork[4], double xwork[4]);
extern void merge_block(emxArray_int32_T *idx, emxArray_real_T *x, int offset,
  int n, int preSortLevel, emxArray_int32_T *iwork, emxArray_real_T *xwork);
extern void merge_pow2_block(emxArray_int32_T *idx, emxArray_real_T *x, int
  offset);

#endif

/*
 * File trailer for sortIdx.h
 *
 * [EOF]
 */
