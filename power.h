/// File: power.h

#ifndef POWER_H
#define POWER_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void b_power(const double a[1024], double y[1024]);
extern void c_power(const double a[6144], double y[6144]);
extern void power(const emxArray_real_T *a, emxArray_real_T *y);

#endif

/*
 * File trailer for power.h
 *
 * [EOF]
 */
