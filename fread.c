/*
 * File: fread.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "fread.h"
#include "bbbox_voiceprintLookup_emxutil.h"
#include "fclose.h"
#include "bbbox_voiceprintLookup_rtwutil.h"
#include "bbbox_voiceprintLookup_data.h"

/* Type Definitions */
#include <stddef.h>

/* Function Definitions */

/*
 * Arguments    : double fileID
 *                emxArray_real_T *A
 * Return Type  : void
 */
void b_fread(double fileID, emxArray_real_T *A)
{
  size_t nBytes;
  signed char fileid;
  FILE * filestar;
  int numRead;
  int c;
  size_t numReadSizeT;
  short tbuf[1024];
  int loop_ub;
  int xs;
  nBytes = sizeof(short);
  fileid = (signed char)rt_roundd_snf(fileID);
  if ((fileid < 0) || (fileID != fileid)) {
    fileid = -1;
  }

  if (fileid >= 3) {
    filestar = eml_openfiles[fileid - 3];
  } else if (fileid == 0) {
    filestar = stdin;
  } else if (fileid == 1) {
    filestar = stdout;
  } else if (fileid == 2) {
    filestar = stderr;
  } else {
    filestar = NULL;
  }

  if ((fileID != 0.0) && (fileID != 1.0) && (fileID != 2.0)) {
  } else {
    filestar = NULL;
  }

  numRead = A->size[0];
  A->size[0] = 0;
  emxEnsureCapacity_real_T(A, numRead);
  if (!(filestar == NULL)) {
    c = 1;
    while (c > 0) {
      c = 0;
      numRead = 1;
      while ((c < 1024) && (numRead > 0)) {
        numReadSizeT = fread(&tbuf[c], nBytes, 1024 - c, filestar);
        numRead = (int)numReadSizeT;
        c += (int)numReadSizeT;
      }

      if (1 > c) {
        loop_ub = -1;
      } else {
        loop_ub = c - 1;
      }

      xs = A->size[0];
      numRead = A->size[0];
      A->size[0] = (xs + loop_ub) + 1;
      emxEnsureCapacity_real_T(A, numRead);
      for (numRead = 0; numRead <= loop_ub; numRead++) {
        A->data[xs + numRead] = tbuf[numRead];
      }
    }
  }
}

/*
 * File trailer for fread.c
 *
 * [EOF]
 */
