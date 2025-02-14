/// File: combineVectorElements.h

#ifndef COMBINEVECTORELEMENTS_H
#define COMBINEVECTORELEMENTS_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void b_combineVectorElements(const double x[6144], double y[256]);
extern void combineVectorElements(const emxArray_real_T *x, double y[24]);

#endif

/*
 * File trailer for combineVectorElements.h
 *
 * [EOF]
 */
