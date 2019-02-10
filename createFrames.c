/// File: createFrames.c


/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "createFrames.h"
#include "bbbox_voiceprintLookup_emxutil.h"

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
 *  * Inputs:  x               Vector                                       *
 *  *          hop             Number of samples between adjacent windows   *
 *  *          windowSize      Size of each window                          *
 *  *                                                                       *
 *  * Outputs: vectorFrames    Resulting matrix made of all the frames      *
 *  *          numberSlices    Number of frames in the matrix               *
 *  *                                                                       *
 *  *************************************************************************
 *  *                                                                       *
 *  * Description:                                                          *
 *  *                                                                       *
 *  * This function splits a vector in overlapping frames and stores these  *
 *  * frames into a matrix:                                                 *
 *  *                                                                       *
 *  * |------------------Input vector---------------------|                 *
 *  *                                                                       *
 *  * |------1------|                                                       *
 *  *     |------2------|                                                   *
 *  *         |------3------|                                               *
 *  *             |------4------|                                           *
 *  *                      ...                                              *
 *  *                                                                       *
 *  * Index            Frame                                                *
 *  *   1         |------1------|                                           *
 *  *   2         |------2------|                                           *
 *  *   3         |------3------|                                           *
 *  *   4         |------4------|                                           *
 *  *  ...              ...                                                 *
 *  *                                                                       *
 *  *************************************************************************
 * Arguments    : emxArray_real_T *x
 *                emxArray_real_T *vectorFrames
 * Return Type  : void
 */
void createFrames(emxArray_real_T *x, emxArray_real_T *vectorFrames)
{
  int numberSlices;
  int i3;
  int i4;
  int indexTimeStart;
  int b_index;
  emxArray_real_T *b_x;
  int indexTimeEnd;

  /*  Find the max number of slices that can be obtained  */
  numberSlices = (int)floor(((double)x->size[0] - 1024.0) / 512.0);

  /*  Truncate if needed to get only a integer number of hop  */
  i3 = (numberSlices << 9) + 1024;
  if (1 > i3) {
    i3 = 0;
  }

  i4 = x->size[0];
  x->size[0] = i3;
  emxEnsureCapacity_real_T(x, i4);

  /*  Create a matrix with time slices  */
  indexTimeStart = (int)floor((double)i3 / 512.0);
  i3 = vectorFrames->size[0] * vectorFrames->size[1];
  vectorFrames->size[0] = indexTimeStart;
  vectorFrames->size[1] = 1024;
  emxEnsureCapacity_real_T1(vectorFrames, i3);
  indexTimeStart <<= 10;
  for (i3 = 0; i3 < indexTimeStart; i3++) {
    vectorFrames->data[i3] = 0.0;
  }

  /*  Fill the matrix  */
  b_index = 0;
  emxInit_real_T(&b_x, 1);
  while (b_index <= numberSlices - 1) {
    indexTimeStart = (b_index << 9) + 1;
    indexTimeEnd = (b_index << 9) + 1024;
    if (indexTimeStart > indexTimeEnd) {
      i3 = 0;
      indexTimeEnd = 0;
    } else {
      i3 = indexTimeStart - 1;
    }

    i4 = b_x->size[0];
    b_x->size[0] = indexTimeEnd - i3;
    emxEnsureCapacity_real_T(b_x, i4);
    indexTimeStart = indexTimeEnd - i3;
    for (i4 = 0; i4 < indexTimeStart; i4++) {
      b_x->data[i4] = x->data[i3 + i4];
    }

    for (i3 = 0; i3 < 1024; i3++) {
      vectorFrames->data[b_index + vectorFrames->size[0] * i3] = b_x->data[i3];
    }

    b_index++;
  }

  emxFree_real_T(&b_x);
}

/*
 * File trailer for createFrames.c
 *
 * [EOF]
 */
