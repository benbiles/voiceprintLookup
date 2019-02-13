/// File: sort1.h

#ifndef SORT1_H
#define SORT1_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

extern int nModelNumber; // number of models in database

/* Function Declarations */

void get_winner(double x[1000], int idx[1000]);

extern void b_sort(double x[1000], int idx[1000]);

extern void sort(emxArray_real_T *x);

#endif

/*
 * File trailer for sort1.h
 *
 * [EOF]
 */
