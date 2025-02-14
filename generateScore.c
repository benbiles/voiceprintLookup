/// File: generateScore.c


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
 *
 *                multi dimension or solution to loop over array struct for f5,f6,f7.... f1000, f1001 !!!

 *                const emxArray_real_T *activeFeatures
 *                const emxArray_boolean_T *activeMask
 *                const boolean_T noiseMask[24]
 *                const double Hl[24]
 *                const double Bl[24]
 *                double choices[4]
 *                double scores[4]
 * Return Type  : void
 */

 // We should only need to pass cell_0 here

void generateScore(const double modelsDatabase_f5[6144],
const double modelsDatabase_f6[6144],const double modelsDatabase_f7[6144],
const double modelsDatabase_f8[6144], const double modelsDatabase_f9[6144],
const double modelsDatabase_f10[6144],const double modelsDatabase_f11[6144],
const double modelsDatabase_f12[6144],const double modelsDatabase_f13[6144],
const double modelsDatabase_f14[6144],
const emxArray_real_T *activeFeatures,const emxArray_boolean_T *activeMask,
const boolean_T noiseMask[24],const double Hl[24],const double Bl[24],double choices[1000],double scores[1000])


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
  double resultModel[1000];
  double currentMask[24];
  double dv5[6144];
  double confidence;
  boolean_T exitg1;

  double x[1000];
  int iidx[1000];

  sumDiff = 0.0;


  nFeatures = activeFeatures->size[0] - 1;


 //  extern double cell_mega[1000][6144];

  /*  Parameters */

/// WARNING resultModel array size limit 1000? should sould scale dynamically ?


 /// Loop in nModelNumber ( number of voicePrints in database ) from multidimensional array

 /*

for ( int modelCount = 0; modelCount < nModelNumber -1; modelCount++)

{

 /// process voicePrints in memory array cell_mega

  //  Loop for each model

  ///  Modify for the environment
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = cell_mega[modelCount] [i + (k << 8)] + Hl[k];
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

  ///  Score

  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++)
        {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
        }

    if (sum(currentMask) > 5.0) /// whats this?
        {
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i << 8)];
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
          if (confidence > vectorDiff[i])
            {
            confidence = vectorDiff[i];
            }

          i++;
        }
      }

      sumDiff += confidence;
    }
  }

  //  Normalise
  y = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);

  // results loaded into resultModel array
  resultModel[modelCount] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


  //************************************************************************************************

   } // END nModelNumber loop

*/


  /// caveman code.... issues found by not using struct's , needs work


  /// These models should be in a loop.
  /// will do this when we sort out f5 f6 f7 strut problem.
  /// maybe just make a multidimesion 2d array rather than depending on a strut?

  ///***************************************************************************************************


 /// MODEL 1


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

  ///  Now score

  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++)
        {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
        }

    if (sum(currentMask) > 5.0) /// whats this?
        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] * k];
         dv5[i + (k << 8)] = confidence - modifiedModel[i + (k << 8)];
        }
      }

      c_power(dv5, b_modifiedModel);
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++)
            {
        iv0[i + (k << 8)] = (signed char)currentMask[k];
        }
      }

      for (i = 0; i < 24; i++) {
        for (k = 0; k < 256; k++) {
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i << 8)];
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
          if (confidence > vectorDiff[i])
            {
            confidence = vectorDiff[i];
            }

          i++;
        }
      }

      sumDiff += confidence;
    }
  }

  ///  Normalise

  y = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);

  resultModel[0] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


  //************************************************************************************************
  /// MODEL 2

  ///  Modify for the environment
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

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) ///
        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++)
            {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *k];
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i << 8)];
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

  ///  Normalise

  resultModel[1] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


  /// ************************************************************************************************
  /// MODEL 3

  //  Modify for the environment
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

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0)  /// ?
        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *k];
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i<< 8)];
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

  ///  Normalise

  resultModel[2] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


  /// **************************************************************************************************
  /// MODEL 4

  //  Modify for the environment
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

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0)  /// ?
        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *k];
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i<< 8)];
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

  ///  Normalise

  resultModel[3] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);



    /// **************************************************************************************************
  /// MODEL 5

  //  Modify for the environment
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f9[i + (k << 8)] + Hl[k];
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

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0)  /// ?
        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *k];
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i<< 8)];
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

  ///  Normalise

  resultModel[4] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


    /// **************************************************************************************************
  /// MODEL 6

  //  Modify for the environment
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f10[i + (k << 8)] + Hl[k];
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

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) /// ?
        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *k];
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double) iv0[k + (i<< 8)];
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

  ///  Normalise
  resultModel[5] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


   /// **************************************************************************************************
  /// MODEL 7

  //  Modify for the environment

  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f11[i + (k << 8)] + Hl[k];
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
      b_modifiedModel[k + (i << 8)] = modifiedModel[k + (i << 8)] * (double) iv0[k + (i << 8)];
    }
  }

  b_combineVectorElements(b_modifiedModel, vectorDiff);
  for (i = 0; i < 256; i++) {
    b_vectorDiff[i] = vectorDiff[i] / 24.0;
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] -= b_vectorDiff[i];
    }
  }

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0)  /// ?

        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *k];
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)
          iv0[k + (i<< 8)];
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

  ///  Normalise

  resultModel[6] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);



   /// **************************************************************************************************
  /// MODEL 8

  //  Modify for the environment

  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f12[i + (k << 8)] + Hl[k];
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

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *
        i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) /// ?
        {
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

  ///  Normalise

  resultModel[7] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


    /// **************************************************************************************************
  /// MODEL 9

  //  Modify for the environment

  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f13[i + (k << 8)] + Hl[k];
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
      b_modifiedModel[k + (i << 8)] = modifiedModel[k + (i << 8)] * (double) iv0[k + (i << 8)];
    }
  }

  b_combineVectorElements(b_modifiedModel, vectorDiff);
  for (i = 0; i < 256; i++) {
    b_vectorDiff[i] = vectorDiff[i] / 24.0;
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] -= b_vectorDiff[i];
    }
  }

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) /// ?
        {
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
          dv5[k + (i << 8)] = b_modifiedModel[k + (i << 8)] * (double)iv0[k + (i<< 8)];
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

  ///  Normalise

  resultModel[8] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);


   /// **************************************************************************************************
  /// MODEL 10

  //  Modify for the environment
  for (i = 0; i < 256; i++) {
    for (k = 0; k < 24; k++) {
      modifiedModel[i + (k << 8)] = modelsDatabase_f14[i + (k << 8)] + Hl[k];
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

  ///  Now score
  sumDiff = 0.0;
  for (iFeature = 0; iFeature <= nFeatures; iFeature++) {
    for (i = 0; i < 24; i++) {
      currentMask[i] = (double)activeMask->data[iFeature + activeMask->size[0] *
        i] * (double)noiseMask[i];
    }

    if (sum(currentMask) > 5.0) /// ?
        {
      for (i = 0; i < 256; i++) {
        for (k = 0; k < 24; k++) {
          confidence = activeFeatures->data[iFeature + activeFeatures->size[0] *k];
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

  ///  Normalise
  resultModel[9] = sumDiff / ((double)activeFeatures->size[0] + 1.0E-99);






///********************************************************************************************************
  /// GENERATE SCORES


 // copy results into x

  for (i = 0; i < nModelNumber; i++)
    {
    x[i] = resultModel[i];
   }



/// b_sort() bubble sort func needs fix to variable size array if multiple scores needed. but we only need winner!
//   b_sort(x, iidx);  /// don't bother bubble sort for scores , just get the winner


 get_winner(x, iidx);  // new function in sort1.c


 /* is winner score junk ? < 0.5 score */
 int junk = iidx[0];
if ( x[junk] < 0.5 )
 {
    goodResult = 0;
    printf("debug.. low result in generateScore %f",x[junk]);
 }
 else
 {
     goodResult = 1;
 }


// load final results into choices array
  for (i = 0; i < nModelNumber-1; i++)
    {
    choices[i] = iidx[i];
    }


} // terminate early


  /// from here on scores / confidence , we already got the winner
  /// **************************************************************************

  /*

  //  Get lowest model
  if (!rtIsNaN(resultModel[0])) {
    i = 1;
  } else {
    i = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) /// whats the 5 here , make sure its not nModelNumber.
        {
      if (!rtIsNaN(resultModel[k - 1]))
      {
        i = k;
        exitg1 = true;
      }
    else
        {
        k++;
        }
    }
  }

  if (i == 0) {
    i = 1;
  } else {
    y = resultModel[i - 1];

    for (k = i; k + 1 < 5; k++)  /// what is 5 ? make sure its not nModelNumber
        {
      if (y > resultModel[k])
        {
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
    while ((!exitg1) && (k < nModelNumber+1)) {
      if (!rtIsNaN(resultModel[k - 1])) {
        i = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (i == 0)
    {
    confidence = resultModel[0];
  }
  else {
    confidence = resultModel[i - 1];

    while (i + 1 < 5)      /// what is 5 ? make sure its not nModelNumber
        {
      if (confidence > resultModel[i])
      {
   confidence = resultModel[i];
      }

      i++;
    }
  }

  confidence = 1.0 / (1.0 + exp(-((confidence - y) - 0.02) / 0.01));


  for (i = 0; i < nModelNumber; i++) {
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
