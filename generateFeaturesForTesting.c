/// File: generateFeaturesForTesting.c

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "generateFeaturesForTesting.h"
#include "power.h"
#include "abs.h"
#include "fft.h"
#include "bbbox_voiceprintLookup_emxutil.h"
#include "combineVectorElements.h"
#include "sort1.h"
#include "rdivide.h"
#include "exp.h"
#include "log.h"
#include "generateFilterbank.h"
#include "createFrames.h"
#include "filter.h"
#include "sqrt.h"
#include "mean.h"

/* Function Definitions */

/*
 *  *************************************************************************
 *  *                                                                       *
 *  * Inputs:  xSeparated      Vector with separated audio stream           *
 *  *          xPostfiltered   Vector with post-filtered audio stream       *
 *  *          hopSize         Size of the hop in samples                   *
 *  *          frameSize       Size of the frame in samples                 *
 *  *          Fs              Sample rate (Samples/sec)                    *
 *  *          window          Vector witch holds the analysis window       *
 *  *                                                                       *
 *  * Outputs: activeFeatures  Matrix with generated features               *
 *  *          activeMask      Matrix with generated mask                   *
 *  *          noiseMask       Matrix with generated noise mask             *
 *  *          Hl              Vector with estimated convolutive noise      *
 *  *          Bl              Vector with estimated additive noise         *
 *  *                                                                       *
 *  *************************************************************************
 *  *                                                                       *
 *  * Description:                                                          *
 *  *                                                                       *
 *  * This generates the features used for testing.                         *
 *  *                                                                       *
 *  *************************************************************************
 * Arguments    : emxArray_real_T *xSeparated
 *                emxArray_real_T *xPostfiltered
 *                const double window[1024]
 *                emxArray_real_T *activeFeatures
 *                emxArray_boolean_T *activeMask
 *                boolean_T noiseMask[24]
 *                double Hl[24]
 *                double Bl[24]
 * Return Type  : void
 */

void generateFeaturesForTesting(emxArray_real_T *xSeparated, emxArray_real_T
  *xPostfiltered, const double window[1024], emxArray_real_T *activeFeatures,
  emxArray_boolean_T *activeMask, boolean_T noiseMask[24], double Hl[24], double
  Bl[24])
{
  emxArray_real_T *r0;
  double y;
  int j;
  int coffset;
  emxArray_real_T *xSeparatedFrames;

  emxArray_real_T *xSeparatedPower;
  emxArray_real_T *b_xSeparatedPower;

  double b_window[1024];
  creal_T dcv0[1024];
  double dv0[1024];
  double dv1[1024];
  emxArray_real_T *xPostfilteredPower;
  creal_T dcv1[1024];
  double dv2[1024];
  emxArray_real_T *separatedFeatures;
  static double H_m[24576];
  int m;
  int boffset;
  int i;
  int k;
  emxArray_real_T *b_y;
  int aoffset;
  emxArray_real_T *activeFeaturesMasked;
  emxArray_real_T *b_activeFeaturesMasked;
  emxArray_boolean_T *maskFeatures;
  emxArray_boolean_T *x;
  emxArray_real_T *sumMask;
  emxArray_boolean_T *filterMask;
  emxArray_real_T *indexesSort;
  double activeFeaturesMean[24];
  emxArray_boolean_T *b_x;
  double noiseDen[24];
  emxArray_real_T *c_y;
  emxInit_real_T(&r0, 1);

  /*  Parameters */
  /*  Normalize volumes */

  power(xSeparated, r0);
  y = mean(r0);
  b_sqrt(&y);
  j = xSeparated->size[0];
  emxEnsureCapacity_real_T(xSeparated, j);

  coffset = xSeparated->size[0];

  for (j = 0; j < coffset; j++)
    {
    xSeparated->data[j] /= y + 1.0E-99;
    }

  power(xPostfiltered, r0);
  y = mean(r0);
  b_sqrt(&y);
  j = xPostfiltered->size[0];
  emxEnsureCapacity_real_T(xPostfiltered, j);

  coffset = xPostfiltered->size[0];

  for (j = 0; j < coffset; j++) {
    xPostfiltered->data[j] /= y + 1.0E-99;
  }

  emxInit_real_T1(&xSeparatedFrames, 2);
  emxInit_real_T1(&xSeparatedPower, 2);

  /*  Emphasis */
  /*  Create frames */
  filter(xSeparated, r0);
  createFrames(r0, xSeparatedFrames);

  /*  Compute power of frames */
  j = xSeparatedPower->size[0] * xSeparatedPower->size[1];

  xSeparatedPower->size[0] = xSeparatedFrames->size[0];
  xSeparatedPower->size[1] = 1024;

  emxEnsureCapacity_real_T1(xSeparatedPower, j);

  coffset = xSeparatedFrames->size[0] * xSeparatedFrames->size[1];

  for (j = 0; j < coffset; j++)
    {
    xSeparatedPower->data[j] = 0.0 * xSeparatedFrames->data[j];
    }

  for (coffset = 0; coffset < xSeparatedFrames->size[0]; coffset++)
    {
    for (j = 0; j < 1024; j++) {
      b_window[j] = window[j] * xSeparatedFrames->data[coffset +
        xSeparatedFrames->size[0] * j];
    }

    fft(b_window, dcv0);
    b_abs(dcv0, dv0);
    b_power(dv0, dv1);
    for (j = 0; j < 1024; j++)
        {
      xSeparatedPower->data[coffset + xSeparatedPower->size[0] * j] = dv1[j];
        }
  }

  emxInit_real_T(&b_xSeparatedPower, 1);
  coffset = xSeparatedPower->size[0];
  j = b_xSeparatedPower->size[0];
  b_xSeparatedPower->size[0] = coffset;
  emxEnsureCapacity_real_T(b_xSeparatedPower, j);
  for (j = 0; j < coffset; j++)
    {
    b_xSeparatedPower->data[j] = xSeparatedPower->data[j] * 0.0;
    }

  coffset = b_xSeparatedPower->size[0];
  for (j = 0; j < coffset; j++)
    {
    xSeparatedPower->data[j] = b_xSeparatedPower->data[j];
    }

  emxInit_real_T1(&xPostfilteredPower, 2);

  /*  Emphasis */
  /*  Create frames */
  filter(xPostfiltered, r0);
  createFrames(r0, xSeparatedFrames);

  /*  Compute power of frames */
  j = xPostfilteredPower->size[0] * xPostfilteredPower->size[1];
  xPostfilteredPower->size[0] = xSeparatedFrames->size[0];
  xPostfilteredPower->size[1] = 1024;
  emxEnsureCapacity_real_T1(xPostfilteredPower, j);
  coffset = xSeparatedFrames->size[0] * xSeparatedFrames->size[1];
  emxFree_real_T(&r0);
  for (j = 0; j < coffset; j++) {
    xPostfilteredPower->data[j] = 0.0 * xSeparatedFrames->data[j];
  }

  for (coffset = 0; coffset < xSeparatedFrames->size[0]; coffset++) {
    for (j = 0; j < 1024; j++) {
      b_window[j] = window[j] * xSeparatedFrames->data[coffset +
        xSeparatedFrames->size[0] * j];
    }

    fft(b_window, dcv1);
    b_abs(dcv1, dv2);
    b_power(dv2, dv1);
    for (j = 0; j < 1024; j++) {
      xPostfilteredPower->data[coffset + xPostfilteredPower->size[0] * j] =
        dv1[j];
    }
  }

  emxFree_real_T(&xSeparatedFrames);
  coffset = xPostfilteredPower->size[0];
  j = b_xSeparatedPower->size[0];
  b_xSeparatedPower->size[0] = coffset;
  emxEnsureCapacity_real_T(b_xSeparatedPower, j);
  for (j = 0; j < coffset; j++) {
    b_xSeparatedPower->data[j] = xPostfilteredPower->data[j] * 0.0;
  }

  coffset = b_xSeparatedPower->size[0];
  for (j = 0; j < coffset; j++) {
    xPostfilteredPower->data[j] = b_xSeparatedPower->data[j];
  }

  emxInit_real_T1(&separatedFeatures, 2);

  /*  Generate filterbank */
  generateFilterbank(H_m);

  /*  Features of the separated signal */
  m = xSeparatedPower->size[0];
  j = separatedFeatures->size[0] * separatedFeatures->size[1];
  separatedFeatures->size[0] = xSeparatedPower->size[0];
  separatedFeatures->size[1] = 24;
  emxEnsureCapacity_real_T1(separatedFeatures, j);
  for (j = 0; j < 24; j++) {
    coffset = j * m;
    boffset = j << 10;
    for (i = 1; i <= m; i++) {
      separatedFeatures->data[(coffset + i) - 1] = 0.0;
    }

    for (k = 0; k < 1024; k++) {
      if (H_m[boffset + k] != 0.0) {
        aoffset = k * m;
        for (i = 0; i < m; i++) {
          separatedFeatures->data[coffset + i] += H_m[boffset + k] *
            xSeparatedPower->data[aoffset + i];
        }
      }
    }
  }

  emxFree_real_T(&xSeparatedPower);
  coffset = separatedFeatures->size[0] * separatedFeatures->size[1] - 1;
  j = separatedFeatures->size[0] * separatedFeatures->size[1];
  separatedFeatures->size[1] = 24;
  emxEnsureCapacity_real_T1(separatedFeatures, j);
  for (j = 0; j <= coffset; j++) {
    separatedFeatures->data[j] += 1.0E-10;
  }

  emxInit_real_T1(&b_y, 2);
  b_log(separatedFeatures);

  /*  Features of the post-filtered signal */
  m = xPostfilteredPower->size[0];
  j = b_y->size[0] * b_y->size[1];
  b_y->size[0] = xPostfilteredPower->size[0];
  b_y->size[1] = 24;
  emxEnsureCapacity_real_T1(b_y, j);
  for (j = 0; j < 24; j++) {
    coffset = j * m;
    boffset = j << 10;
    for (i = 1; i <= m; i++) {
      b_y->data[(coffset + i) - 1] = 0.0;
    }

    for (k = 0; k < 1024; k++) {
      if (H_m[boffset + k] != 0.0) {
        aoffset = k * m;
        for (i = 0; i < m; i++) {
          b_y->data[coffset + i] += H_m[boffset + k] * xPostfilteredPower->
            data[aoffset + i];
        }
      }
    }
  }

  emxFree_real_T(&xPostfilteredPower);
  emxInit_real_T1(&activeFeaturesMasked, 2);

  /*  Mask */
  j = activeFeaturesMasked->size[0] * activeFeaturesMasked->size[1];
  activeFeaturesMasked->size[0] = separatedFeatures->size[0];
  activeFeaturesMasked->size[1] = 24;
  emxEnsureCapacity_real_T1(activeFeaturesMasked, j);
  coffset = separatedFeatures->size[0] * separatedFeatures->size[1];
  for (j = 0; j < coffset; j++) {
    activeFeaturesMasked->data[j] = separatedFeatures->data[j];
  }

  coffset = separatedFeatures->size[0] * 24;
  for (k = 0; k < coffset; k++) {
    activeFeaturesMasked->data[k] = exp(activeFeaturesMasked->data[k]);
  }

  coffset = b_y->size[0] * b_y->size[1] - 1;
  j = b_y->size[0] * b_y->size[1];
  b_y->size[1] = 24;
  emxEnsureCapacity_real_T1(b_y, j);
  for (j = 0; j <= coffset; j++) {
    b_y->data[j] += 1.0E-20;
  }

  emxInit_real_T1(&b_activeFeaturesMasked, 2);
  b_log(b_y);
  b_exp(b_y);
  j = b_activeFeaturesMasked->size[0] * b_activeFeaturesMasked->size[1];
  b_activeFeaturesMasked->size[0] = activeFeaturesMasked->size[0];
  b_activeFeaturesMasked->size[1] = 24;
  emxEnsureCapacity_real_T1(b_activeFeaturesMasked, j);
  coffset = activeFeaturesMasked->size[0] * activeFeaturesMasked->size[1];
  for (j = 0; j < coffset; j++) {
    b_activeFeaturesMasked->data[j] = activeFeaturesMasked->data[j] + 1.0E-99;
  }

  emxInit_boolean_T(&maskFeatures, 2);
  rdivide(b_y, b_activeFeaturesMasked, activeFeaturesMasked);
  j = maskFeatures->size[0] * maskFeatures->size[1];
  maskFeatures->size[0] = activeFeaturesMasked->size[0];
  maskFeatures->size[1] = 24;
  emxEnsureCapacity_boolean_T(maskFeatures, j);
  coffset = activeFeaturesMasked->size[0] * activeFeaturesMasked->size[1];
  emxFree_real_T(&b_activeFeaturesMasked);
  for (j = 0; j < coffset; j++) {
    maskFeatures->data[j] = (activeFeaturesMasked->data[j] > 0.05);
  }

  emxInit_boolean_T(&x, 2);

  /*  VAD */
  j = x->size[0] * x->size[1];
  x->size[0] = 24;
  x->size[1] = maskFeatures->size[0];
  emxEnsureCapacity_boolean_T(x, j);
  coffset = maskFeatures->size[0];
  for (j = 0; j < coffset; j++) {
    for (m = 0; m < 24; m++) {
      x->data[m + x->size[0] * j] = maskFeatures->data[j + maskFeatures->size[0]
        * m];
    }
  }

  emxInit_real_T1(&sumMask, 2);
  if (x->size[1] == 0) {
    j = sumMask->size[0] * sumMask->size[1];
    sumMask->size[0] = 1;
    sumMask->size[1] = 0;
    emxEnsureCapacity_real_T1(sumMask, j);
  } else {
    j = sumMask->size[0] * sumMask->size[1];
    sumMask->size[0] = 1;
    sumMask->size[1] = x->size[1];
    emxEnsureCapacity_real_T1(sumMask, j);
    for (i = 0; i < x->size[1]; i++) {
      coffset = i * 24;
      sumMask->data[i] = x->data[coffset];
      for (k = 0; k < 23; k++) {
        sumMask->data[i] += (double)x->data[(coffset + k) + 1];
      }
    }
  }

  emxFree_boolean_T(&x);
  emxInit_boolean_T(&filterMask, 2);
  j = filterMask->size[0] * filterMask->size[1];
  filterMask->size[0] = 1;
  filterMask->size[1] = sumMask->size[1];
  emxEnsureCapacity_boolean_T(filterMask, j);
  coffset = sumMask->size[0] * sumMask->size[1];
  for (j = 0; j < coffset; j++) {
    filterMask->data[j] = (sumMask->data[j] > 5.0);
  }

  if (filterMask->size[1] < 1) {
    j = sumMask->size[0] * sumMask->size[1];
    sumMask->size[0] = 1;
    sumMask->size[1] = 0;
    emxEnsureCapacity_real_T1(sumMask, j);
  } else {
    j = filterMask->size[1];
    m = sumMask->size[0] * sumMask->size[1];
    sumMask->size[0] = 1;
    sumMask->size[1] = (int)((double)j - 1.0) + 1;
    emxEnsureCapacity_real_T1(sumMask, m);
    coffset = (int)((double)j - 1.0);
    for (j = 0; j <= coffset; j++) {
      sumMask->data[sumMask->size[0] * j] = 1.0 + (double)j;
    }
  }

  coffset = sumMask->size[0] * sumMask->size[1] - 1;
  j = sumMask->size[0] * sumMask->size[1];
  sumMask->size[0] = 1;
  emxEnsureCapacity_real_T1(sumMask, j);
  for (j = 0; j <= coffset; j++) {
    sumMask->data[j] *= (double)filterMask->data[j];
  }

  sort(sumMask);  /// function in sort1.c

  j = filterMask->size[0] * filterMask->size[1];
  filterMask->size[0] = 1;
  filterMask->size[1] = sumMask->size[1];
  emxEnsureCapacity_boolean_T(filterMask, j);
  coffset = sumMask->size[0] * sumMask->size[1];
  for (j = 0; j < coffset; j++) {
    filterMask->data[j] = (sumMask->data[j] == 0.0);
  }

  if (filterMask->size[1] == 0) {
    y = 0.0;
  } else {
    y = filterMask->data[0];
    for (k = 2; k <= filterMask->size[1]; k++) {
      y += (double)filterMask->data[k - 1];
    }
  }

  emxFree_boolean_T(&filterMask);
  if (y + 1.0 > sumMask->size[1]) {
    j = 0;
    m = 0;
  } else {
    j = (int)(y + 1.0) - 1;
    m = sumMask->size[1];
  }

  emxInit_real_T1(&indexesSort, 2);
  aoffset = indexesSort->size[0] * indexesSort->size[1];
  indexesSort->size[0] = 1;
  indexesSort->size[1] = m - j;
  emxEnsureCapacity_real_T1(indexesSort, aoffset);
  coffset = m - j;
  for (aoffset = 0; aoffset < coffset; aoffset++) {
    indexesSort->data[indexesSort->size[0] * aoffset] = sumMask->data[j +
      aoffset];
  }

  emxFree_real_T(&sumMask);
  aoffset = activeFeatures->size[0] * activeFeatures->size[1];
  activeFeatures->size[0] = indexesSort->size[1];
  activeFeatures->size[1] = 24;
  emxEnsureCapacity_real_T1(activeFeatures, aoffset);
  for (aoffset = 0; aoffset < 24; aoffset++) {
    coffset = indexesSort->size[1];
    for (boffset = 0; boffset < coffset; boffset++) {
      activeFeatures->data[boffset + activeFeatures->size[0] * aoffset] =
        separatedFeatures->data[((int)indexesSort->data[indexesSort->size[0] *
        boffset] + separatedFeatures->size[0] * aoffset) - 1];
    }
  }

  aoffset = activeMask->size[0] * activeMask->size[1];
  activeMask->size[0] = indexesSort->size[1];
  activeMask->size[1] = 24;
  emxEnsureCapacity_boolean_T(activeMask, aoffset);
  for (aoffset = 0; aoffset < 24; aoffset++) {
    coffset = indexesSort->size[1];
    for (boffset = 0; boffset < coffset; boffset++) {
      activeMask->data[boffset + activeMask->size[0] * aoffset] =
        maskFeatures->data[((int)indexesSort->data[indexesSort->size[0] *
                            boffset] + maskFeatures->size[0] * aoffset) - 1];
    }
  }

  emxFree_real_T(&indexesSort);

  /*  Get mean of features */
  combineVectorElements(activeFeatures, activeFeaturesMean);
  coffset = m - j;
  for (aoffset = 0; aoffset < 24; aoffset++) {
    activeFeaturesMean[aoffset] /= (double)coffset;
  }

  emxInit_boolean_T(&b_x, 2);

  /*  Get noise */
  aoffset = b_x->size[0] * b_x->size[1];
  b_x->size[0] = maskFeatures->size[0];
  b_x->size[1] = 24;
  emxEnsureCapacity_boolean_T(b_x, aoffset);
  coffset = maskFeatures->size[0] * maskFeatures->size[1];
  for (aoffset = 0; aoffset < coffset; aoffset++) {
    b_x->data[aoffset] = !maskFeatures->data[aoffset];
  }

  if (b_x->size[0] == 0) {
    memset(&noiseDen[0], 0, 24U * sizeof(double));
  } else {
    for (i = 0; i < 24; i++) {
      coffset = i * b_x->size[0];
      noiseDen[i] = b_x->data[coffset];
      for (k = 2; k <= b_x->size[0]; k++) {
        noiseDen[i] += (double)b_x->data[(coffset + k) - 1];
      }
    }
  }

  emxFree_boolean_T(&b_x);
  aoffset = b_y->size[0] * b_y->size[1];
  b_y->size[0] = maskFeatures->size[0];
  b_y->size[1] = 24;
  emxEnsureCapacity_real_T1(b_y, aoffset);
  coffset = maskFeatures->size[0] * maskFeatures->size[1];
  for (aoffset = 0; aoffset < coffset; aoffset++) {
    b_y->data[aoffset] = (double)!maskFeatures->data[aoffset] *
      separatedFeatures->data[aoffset];
  }

  emxFree_boolean_T(&maskFeatures);
  emxFree_real_T(&separatedFeatures);
  combineVectorElements(b_y, Bl);

  /*  Get environment features */
  for (k = 0; k < 24; k++) {
    Bl[k] /= noiseDen[k] + 1.0E-99;
    Hl[k] = activeFeaturesMean[k];
    Hl[k] = exp(Hl[k]);
    Hl[k] -= exp(Bl[k]);
    Hl[k] = log(Hl[k]);
    noiseMask[k] = (activeFeaturesMean[k] - Bl[k] > 0.0);
  }

  coffset = m - j;
  j = b_y->size[0] * b_y->size[1];
  b_y->size[0] = coffset;
  b_y->size[1] = 24;
  emxEnsureCapacity_real_T1(b_y, j);
  for (j = 0; j < coffset; j++) {
    for (m = 0; m < 24; m++) {
      b_y->data[j + b_y->size[0] * m] = noiseMask[m];
    }
  }

  j = activeFeaturesMasked->size[0] * activeFeaturesMasked->size[1];

  activeFeaturesMasked->size[0] = activeFeatures->size[0];
  activeFeaturesMasked->size[1] = 24;
  emxEnsureCapacity_real_T1(activeFeaturesMasked, j);

  for (j = 0; j < 24; j++) {
    coffset = activeFeatures->size[0];
    for (m = 0; m < coffset; m++) {
      activeFeaturesMasked->data[m + activeFeaturesMasked->size[0] * j] =
        activeFeatures->data[m + activeFeatures->size[0] * j] * b_y->data[m +
        b_y->size[0] * j];
    }
  }

  emxFree_real_T(&b_y);
  if (activeFeaturesMasked->size[0] == 0) {
    j = b_xSeparatedPower->size[0];
    b_xSeparatedPower->size[0] = 0;
    emxEnsureCapacity_real_T(b_xSeparatedPower, j);
  } else {
    boffset = activeFeaturesMasked->size[0];
    j = b_xSeparatedPower->size[0];
    b_xSeparatedPower->size[0] = activeFeaturesMasked->size[0];
    emxEnsureCapacity_real_T(b_xSeparatedPower, j);
    for (j = 0; j < boffset; j++) {
      b_xSeparatedPower->data[j] = activeFeaturesMasked->data[j];
    }

    for (k = 0; k < 23; k++) {
      coffset = (k + 1) * boffset;
      for (j = 0; j < boffset; j++) {
        b_xSeparatedPower->data[j] += activeFeaturesMasked->data[coffset + j];
      }
    }
  }

  emxFree_real_T(&activeFeaturesMasked);
  emxInit_real_T(&c_y, 1);
  j = c_y->size[0];
  c_y->size[0] = b_xSeparatedPower->size[0];
  emxEnsureCapacity_real_T(c_y, j);
  coffset = b_xSeparatedPower->size[0];
  for (j = 0; j < coffset; j++) {
    c_y->data[j] = b_xSeparatedPower->data[j] / 24.0;
  }

  emxFree_real_T(&b_xSeparatedPower);
  j = activeFeatures->size[0] * activeFeatures->size[1];
  activeFeatures->size[0] = c_y->size[0];
  activeFeatures->size[1] = 24;
  emxEnsureCapacity_real_T1(activeFeatures, j);
  coffset = c_y->size[0];
  for (j = 0; j < coffset; j++) {
    for (m = 0; m < 24; m++) {
      y = c_y->data[j];
      activeFeatures->data[j + activeFeatures->size[0] * m] -= y;
    }
  }

  emxFree_real_T(&c_y);
}

/*
 * File trailer for generateFeaturesForTesting.c
 *
 * [EOF]
 */
