/*
 * File: generateScore.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "generateScore.h"
#include "sqrt.h"
#include "combineVectorElements.h"
#include "power.h"
#include "sum.h"
#include "sort1.h"
#include "log.h"
#include "exp.h"

/* Function Definitions */

/*
 * *************************************************************************
 *  *                                                                       *
 *  * Project: WISS                                                         *
 *  * Author: François Grondin                                              *
 *  * Version: 1.0.0                                                        *
 *  * Date: 24/04/2013                                                      *
 *  *                                                                       *
 *  *************************************************************************
 *  *                                                                       *
 *  * License:                                                              *
 *  *                                                                       *
 *  * WISS is free software: you can redistribute it and/or modify it under *
 *  * the terms of the GNU General Public License as published by the Free  *
 *  * Software Foundation, either version 3 of the License, or (at your     *
 *  * option) any later version. WISS is distributed in the hope that it    *
 *  * will be useful, but WITHOUT ANY WARRANTY; without even the implied    *
 *  * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See  *
 *  * the GNU General Public License for more details. You should have      *
 *  * received a copy of the GNU General Public License along with WISS.    *
 *  * If not, see http://www.gnu.org/licenses/.                             *
 *  *                                                                       *
 *  *************************************************************************
 *  *                                                                       *
 *  * Inputs:  modelsDatabase  Database which holds the models              *
 *  *          activeFeatures  Features to be tested                        *
 *  *          activeMask      Masks used with features                     *
 *  *          noiseMask       Noise maks used with features                *
 *  *          Hl              Convolutive noise estimation                 *
 *  *          Bl              Additive noise estimation                    *
 *  *                                                                       *
 *  * Outputs: choices         List of potential people identified          *
 *  *          scores          Confidence level for each potential person   *
 *  *                                                                       *
 *  *************************************************************************
 *  *                                                                       *
 *  * Description:                                                          *
 *  *                                                                       *
 *  * Using the pretrained models, this function returns a list of people   *
 *  * that match the models given the features to test and a list with the  *
 *  * confidence level associated with each identification                  *
 *  *                                                                       *
 *  *************************************************************************
 *
 *  Dimensions
 * Arguments    : const double modelsDatabase_f5[6144]
 *                const double modelsDatabase_f6[6144]
 *                const double modelsDatabase_f7[6144]
 *                const double modelsDatabase_f8[6144]
 *                const emxArray_real_T *activeFeatures
 *                const emxArray_boolean_T *activeMask
 *                const boolean_T noiseMask[24]
 *                const double Hl[24]
 *                const double Bl[24]
 *                double choices[4]
 *                double scores[4]
 * Return Type  : void
 */
void generateScore(const double modelsDatabase_f5[6144], const double modelsDatabase_f6[6144], const double modelsDatabase_f7[6144],
                   const double modelsDatabase_f8[6144], const emxArray_real_T
                   *activeFeatures, const emxArray_boolean_T *activeMask, const
                   boolean_T noiseMask[24], const double Hl[24], const double
                   Bl[24], double choices[4], double scores[4])
{
  int nFeatures;
  int i;
  double modifiedModel[6144];
  int k;
  double b_modifiedModel[6144];
  double vectorDiff[256];
  signed char iv0[6144];
  double b_vectorDiff[256];
  double sumDiff;
  int iFeature;
  double y;
  double resultModel[4];
  double currentMask[24];
  double dv5[6144];
  double confidence;
  boolean_T exitg1;
  double x[4];
  int iidx[4];
  nFeatures = activeFeatures->size[0] - 1;

  /*  Parameters */
  /*  Loop for each model */
  /*  Modify for the environment */
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f5[i + (k << 8)] + Hl[k];
    }
  }

  c_exp(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      b_modifiedModel[i + (k << 8)] = Bl[k];
    }
  }

  c_exp(b_modifiedModel);
  for (i = 0; i < 6144; i++) {
    modifiedModel[i] += b_modifiedModel[i];
  }

  c_log(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      iv0[i + (k << 8)] = (signed char)noiseMask[k];
    }
  }

  for (i = 0; i < 24; i++) {
    for (k = 0; k < 256; k++) {
      b_modifiedModel[k + (i << 8)] = modifiedModel[k + (i << 8)] * (double)
        iv0[k + (i << 8)];
    }
  }

  b_combineVectorElements(b_modifiedModel, vectorDiff);
  for (i = 0; i < 256; i++) {
    b_vectorDiff[i] = vectorDiff[i] / 24.0;
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] -= b_vectorDiff[i];
    }
  }

  /*  Now score         */
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *
        i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *
            k];
          dv5[i + (k << 8)] = confidence - modifiedModel[i + (k << 8)];
        }
      }

      c_power(dv5, b_modifiedModel);
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          iv0[i + (k << 8)] = (signed char)currentMask[k];
        }
      }

      for (i = 0; i < 24; i++) {
        for (k = 0; k < 256; k++) {
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i
            << 8)];
        }
      }

      b_combineVectorElements(dv5, vectorDiff);
      c_sqrt(vectorDiff);
      if (!rtIsNaN(vectorDiff[0])) {
        i = 1;
      } else {
        i = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 257)) {
          if (!rtIsNaN(vectorDiff[k - 1])) {
            i = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (i == 0) {
        confidence = vectorDiff[0];
      } else {
        confidence = vectorDiff[i - 1];
        while (i + 1 < 257) {
          if (confidence > vectorDiff[i]) {
            confidence = vectorDiff[i];
          }

          i++;
        }
      }

      sumDiff += confidence;
    }
  }

  /*  Normalise */
  y = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);
  resultModel[0] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);

  /*  Modify for the environment */
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f6[i + (k << 8)] + Hl[k];
    }
  }

  c_exp(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      b_modifiedModel[i + (k << 8)] = Bl[k];
    }
  }

  c_exp(b_modifiedModel);
  for (i = 0; i < 6144; i++) {
    modifiedModel[i] += b_modifiedModel[i];
  }

  c_log(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      iv0[i + (k << 8)] = (signed char)noiseMask[k];
    }
  }

  for (i = 0; i < 24; i++) {
    for (k = 0; k < 256; k++) {
      b_modifiedModel[k + (i << 8)] = modifiedModel[k + (i << 8)] * (double)
        iv0[k + (i << 8)];
    }
  }

  b_combineVectorElements(b_modifiedModel, vectorDiff);
  for (i = 0; i < 256; i++) {
    b_vectorDiff[i] = vectorDiff[i] / 24.0;
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] -= b_vectorDiff[i];
    }
  }

  /*  Now score         */
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *
        i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *
            k];
          dv5[i + (k << 8)] = confidence - modifiedModel[i + (k << 8)];
        }
      }

      c_power(dv5, b_modifiedModel);
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          iv0[i + (k << 8)] = (signed char)currentMask[k];
        }
      }

      for (i = 0; i < 24; i++) {
        for (k = 0; k < 256; k++) {
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i
            << 8)];
        }
      }

      b_combineVectorElements(dv5, vectorDiff);
      c_sqrt(vectorDiff);
      if (!rtIsNaN(vectorDiff[0])) {
        i = 1;
      } else {
        i = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 257)) {
          if (!rtIsNaN(vectorDiff[k - 1])) {
            i = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (i == 0) {
        confidence = vectorDiff[0];
      } else {
        confidence = vectorDiff[i - 1];
        while (i + 1 < 257) {
          if (confidence > vectorDiff[i]) {
            confidence = vectorDiff[i];
          }

          i++;
        }
      }

      sumDiff += confidence;
    }
  }

  /*  Normalise */
  resultModel[1] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);

  /*  Modify for the environment */
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f7[i + (k << 8)] + Hl[k];
    }
  }

  c_exp(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      b_modifiedModel[i + (k << 8)] = Bl[k];
    }
  }

  c_exp(b_modifiedModel);
  for (i = 0; i < 6144; i++) {
    modifiedModel[i] += b_modifiedModel[i];
  }

  c_log(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      iv0[i + (k << 8)] = (signed char)noiseMask[k];
    }
  }

  for (i = 0; i < 24; i++) {
    for (k = 0; k < 256; k++) {
      b_modifiedModel[k + (i << 8)] = modifiedModel[k + (i << 8)] * (double)
        iv0[k + (i << 8)];
    }
  }

  b_combineVectorElements(b_modifiedModel, vectorDiff);
  for (i = 0; i < 256; i++) {
    b_vectorDiff[i] = vectorDiff[i] / 24.0;
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] -= b_vectorDiff[i];
    }
  }

  /*  Now score         */
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *
        i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *
            k];
          dv5[i + (k << 8)] = confidence - modifiedModel[i + (k << 8)];
        }
      }

      c_power(dv5, b_modifiedModel);
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          iv0[i + (k << 8)] = (signed char)currentMask[k];
        }
      }

      for (i = 0; i < 24; i++) {
        for (k = 0; k < 256; k++) {
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i
            << 8)];
        }
      }

      b_combineVectorElements(dv5, vectorDiff);
      c_sqrt(vectorDiff);
      if (!rtIsNaN(vectorDiff[0])) {
        i = 1;
      } else {
        i = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 257)) {
          if (!rtIsNaN(vectorDiff[k - 1])) {
            i = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (i == 0) {
        confidence = vectorDiff[0];
      } else {
        confidence = vectorDiff[i - 1];
        while (i + 1 < 257) {
          if (confidence > vectorDiff[i]) {
            confidence = vectorDiff[i];
          }

          i++;
        }
      }

      sumDiff += confidence;
    }
  }

  /*  Normalise */
  resultModel[2] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);

  /*  Modify for the environment */
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f8[i + (k << 8)] + Hl[k];
    }
  }

  c_exp(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      b_modifiedModel[i + (k << 8)] = Bl[k];
    }
  }

  c_exp(b_modifiedModel);
  for (i = 0; i < 6144; i++) {
    modifiedModel[i] += b_modifiedModel[i];
  }

  c_log(modifiedModel);
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      iv0[i + (k << 8)] = (signed char)noiseMask[k];
    }
  }

  for (i = 0; i < 24; i++) {
    for (k = 0; k < 256; k++) {
      b_modifiedModel[k + (i << 8)] = modifiedModel[k + (i << 8)] * (double)
        iv0[k + (i << 8)];
    }
  }

  b_combineVectorElements(b_modifiedModel, vectorDiff);
  for (i = 0; i < 256; i++) {
    b_vectorDiff[i] = vectorDiff[i] / 24.0;
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] -= b_vectorDiff[i];
    }
  }

  /*  Now score         */
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *
        i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *
            k];
          dv5[i + (k << 8)] = confidence - modifiedModel[i + (k << 8)];
        }
      }

      c_power(dv5, b_modifiedModel);
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          iv0[i + (k << 8)] = (signed char)currentMask[k];
        }
      }

      for (i = 0; i < 24; i++) {
        for (k = 0; k < 256; k++) {
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i
            << 8)];
        }
      }

      b_combineVectorElements(dv5, vectorDiff);
      c_sqrt(vectorDiff);
      if (!rtIsNaN(vectorDiff[0])) {
        i = 1;
      } else {
        i = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 257)) {
          if (!rtIsNaN(vectorDiff[k - 1])) {
            i = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (i == 0) {
        confidence = vectorDiff[0];
      } else {
        confidence = vectorDiff[i - 1];
        while (i + 1 < 257) {
          if (confidence > vectorDiff[i]) {
            confidence = vectorDiff[i];
          }

          i++;
        }
      }

      sumDiff += confidence;
    }
  }

  /*  Normalise */
  resultModel[3] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);
  for (i = 0; i < 4; i++) {
    x[i] = resultModel[i];
  }

  b_sort(x, iidx);
  for (i = 0; i < 4; i++) {
    choices[i] = iidx[i];
  }

  /*  Get lowest model */
  if (!rtIsNaN(resultModel[0])) {
    i = 1;
  } else {
    i = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (!rtIsNaN(resultModel[k - 1])) {
        i = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (i == 0) {
    i = 1;
  } else {
    y = resultModel[i - 1];
    for (k = i; k + 1 < 5; k++) {
      if (y > resultModel[k]) {
        y = resultModel[k];
        i = k + 1;
      }
    }
  }

  resultModel[i - 1] = rtInf;
  if (!rtIsNaN(resultModel[0])) {
    i = 1;
  } else {
    i = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (!rtIsNaN(resultModel[k - 1])) {
        i = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (i == 0) {
    confidence = resultModel[0];
  } else {
    confidence = resultModel[i - 1];
    while (i + 1 < 5) {
      if (confidence > resultModel[i]) {
        confidence = resultModel[i];
      }

      i++;
    }
  }

  confidence = 1.0 / (1.0 + exp(-((confidence - y) - 0.02) / 0.01));
  for (i = 0; i < 4; i++) {
    scores[i] = 0.0;
  }

  scores[0] = confidence;
  scores[1] = 1.0 - confidence;
}

/*
 * File trailer for generateScore.c
 *
 * [EOF]
 */
