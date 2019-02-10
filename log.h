/// File: log.h

#ifndef LOG_H
#define LOG_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void b_log(emxArray_real_T *x);
extern void c_log(double x[6144]);

#endif

/*
 * File trailer for log.h
 *
 * [EOF]
 */
