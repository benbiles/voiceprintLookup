/// File: fileManager.c

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "fileManager.h"
#include "bbbox_voiceprintLookup_data.h"

/* Function Declarations */
static signed char filedata(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : signed char
 */
static signed char filedata(void)
{
  signed char f;
  signed char k;
  boolean_T exitg1;
  f = 0;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 256)) {
    if (eml_openfiles[k - 1] == NULL) {
      f = k;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return f;
}

/*
 * Arguments    : const char cfilename[20]
 *                const char * cpermission
 * Return Type  : signed char
 */
signed char b_cfopen(const char cfilename[255], const char * cpermission)
{
  signed char fileid;
  signed char j;
  int i2;
  char ccfilename[256];
  FILE * filestar;
  fileid = -1;
  j = filedata();
  if (!(j < 1)) {
    for (i2 = 0; i2 < 255; i2++) {
      ccfilename[i2] = cfilename[i2];
    }

    ccfilename[255] = '\x00';
    filestar = fopen(&ccfilename[0], cpermission);
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i2 = j + 2;
      if (i2 > 127) {
        i2 = 127;
      }

      fileid = (signed char)i2;
    }
  }

  return fileid;
}

/*
 * Arguments    : const char cfilename[17]
 *                const char * cpermission
 * Return Type  : signed char
 */
signed char cfopen(const char cfilename[255], const char * cpermission)
{
  signed char fileid;
  signed char j;
  int i1;
  char ccfilename[256];
  FILE * filestar;
  fileid = -1;
  j = filedata();
  if (!(j < 1)) {
    for (i1 = 0; i1 < 17; i1++) {
      ccfilename[i1] = cfilename[i1];
    }

    ccfilename[255] = '\x00';
    filestar = fopen(&ccfilename[0], cpermission);
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i1 = j + 2;
      if (i1 > 127) {
        i1 = 127;
      }

      fileid = (signed char)i1;
    }
  }

  return fileid;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void filedata_init(void)
{
  FILE * a;
  int i;
  a = NULL;
  for (i = 0; i < 255; i++) {
    eml_autoflush[i] = false;
    eml_openfiles[i] = a;
  }
}

/*
 * File trailer for fileManager.c
 *
 * [EOF]
 */
