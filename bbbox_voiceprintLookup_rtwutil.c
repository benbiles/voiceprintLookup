/// File: bbbox_voiceprintLookup_rtwutil.c

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * File trailer for bbbox_voiceprintLookup_rtwutil.c
 *
 * [EOF]
 */
