/*
 * File: fclose.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "fclose.h"
#include "bbbox_voiceprintLookup_rtwutil.h"
#include "bbbox_voiceprintLookup_data.h"

/* Function Definitions */

/*
 * Arguments    : double fileID
 * Return Type  : void
 */
void b_fclose(double fileID)
{
  signed char fileid;
  signed char b_fileid;
  FILE * f;
  int cst;
  fileid = (signed char)rt_roundd_snf(fileID);
  if ((fileid < 0) || (fileID != fileid)) {
    fileid = -1;
  }

  b_fileid = fileid;
  if (fileid < 0) {
    b_fileid = -1;
  }

  if (b_fileid >= 3) {
    f = eml_openfiles[b_fileid - 3];
  } else if (b_fileid == 0) {
    f = stdin;
  } else if (b_fileid == 1) {
    f = stdout;
  } else if (b_fileid == 2) {
    f = stderr;
  } else {
    f = NULL;
  }

  if ((f != NULL) && (fileid >= 3)) {
    cst = fclose(f);
    if (cst == 0) {
      eml_openfiles[fileid - 3] = NULL;
      eml_autoflush[fileid - 3] = true;
    }
  }
}

/*
 * File trailer for fclose.c
 *
 * [EOF]
 */
