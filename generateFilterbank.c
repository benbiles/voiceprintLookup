/*
 * File: generateFilterbank.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "generateFilterbank.h"

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
 *  * Inputs:  N               Size of the frame in samples                 *
 *  *          Fs              Sample rate (Samples/sec)                    *
 *  *                                                                       *
 *  * Outputs: H_m             Matrix with filterbank                       *
 *  *                                                                       *
 *  *************************************************************************
 *  *                                                                       *
 *  * Description:                                                          *
 *  *                                                                       *
 *  * This generates the filterbank:                                        *
 *  *                                                                       *
 *  *         +----------------------------------------+                    *
 *  * Band 1  |000XXX0000000000000000000000000000000000|                    *
 *  *         +----------------------------------------+                    *
 *  * Band 2  |0000XXXX00000000000000000000000000000000|                    *
 *  *         +----------------------------------------+                    *
 *  *                            ...                                        *
 *  *         +----------------------------------------+                    *
 *  * Band 24 |0000000000000000000XXXXXXXXXXXXX00000000|                    *
 *  *         +----------------------------------------+                    *
 *  *                                                                       *
 *  *************************************************************************
 *
 *  Number of filters
 * Arguments    : double H_m[24576]
 * Return Type  : void
 */
void generateFilterbank(double H_m[24576])
{
  int m;
  short bands[72];
  int lowFreq;
  int centerFreq;
  int highFreq;
  int n;
  double H_m_k;
  double f;
  static double b_H_m[24576];

  /*  Matrix with band limits */
  /*  Fixed width */
  for (m = 0; m < 3; m++) {
    bands[24 * m] = (short)(50 * m);
    bands[1 + 24 * m] = (short)(100 + 50 * m);
    bands[2 + 24 * m] = (short)(200 + 50 * m);
    bands[3 + 24 * m] = (short)(300 + 50 * m);
    bands[4 + 24 * m] = (short)(390 + 60 * m);
    bands[5 + 24 * m] = (short)(510 + 60 * m);
    bands[6 + 24 * m] = (short)(630 + 70 * m);
    bands[7 + 24 * m] = (short)(760 + 80 * m);
    bands[8 + 24 * m] = (short)(920 + 80 * m);
    bands[9 + 24 * m] = (short)(1070 + 100 * m);
    bands[10 + 24 * m] = (short)(1260 + 110 * m);
    bands[11 + 24 * m] = (short)(1480 + 120 * m);
    bands[12 + 24 * m] = (short)(1700 + 150 * m);
    bands[13 + 24 * m] = (short)(1980 + 170 * m);
    bands[14 + 24 * m] = (short)(2300 + 200 * m);
    bands[15 + 24 * m] = (short)(2650 + 250 * m);
    bands[16 + 24 * m] = (short)(3100 + 300 * m);
    bands[17 + 24 * m] = (short)(3600 + 400 * m);
    bands[18 + 24 * m] = (short)(4300 + 500 * m);
    bands[19 + 24 * m] = (short)(5200 + 600 * m);
    bands[20 + 24 * m] = (short)(6300 + 700 * m);
    bands[21 + 24 * m] = (short)(7500 + 1000 * m);
    bands[22 + 24 * m] = (short)(9000 + 1500 * m);
    bands[23 + 24 * m] = (short)(11500 + 2000 * m);
  }

  /*  Create a matrix with all filters */
  /*  Loop for each filter */
  for (m = 0; m < 24; m++) {
    /*  Current frame */
    /*  Band limits */
    lowFreq = bands[m];
    centerFreq = bands[24 + m];
    highFreq = bands[48 + m];

    /*  For each sample */
    for (n = 0; n < 1024; n++) {
      H_m_k = 0.0;
      f = ((1.0 + (double)n) - 1.0) / 1024.0 * 48000.0;

      /*  Before triangle */
      /*  Inside triangle */
      if ((f >= lowFreq) && (f <= highFreq)) {
        /*  Rising slope */
        if (f <= centerFreq) {
          H_m_k = 1.0 / (double)(centerFreq - lowFreq) * (f - (double)lowFreq);
        }

        /*  Falling slope */
        if (f > centerFreq) {
          H_m_k = 1.0 / (double)(centerFreq - highFreq) * (f - (double)
            centerFreq) + 1.0;
        }
      }

      /*  After triangle */
      if (f > highFreq) {
        H_m_k = 0.0;
      }

      b_H_m[m + 24 * n] = H_m_k;
      H_m[n + (m << 10)] = b_H_m[m + 24 * n];
    }
  }
}

/*
 * File trailer for generateFilterbank.c
 *
 * [EOF]
 */
