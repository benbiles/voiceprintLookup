/// File: bbbox_voiceprintLookup.c

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"

/* Function Definitions */

/*
 * load the database file
 * Arguments    : const char wavFileA[20]
 *                const char wavFileB[20]
 *                const char databaseFile[17]
 *                char voiceId[18]
 * Return Type  : void
 */
void bbbox_voiceprintLookup(const char *wavFileA[255], const char *wavFileB[255],
                            const char *databaseFile[255])
 {



  static cell_0 modelsDatabase;  // voice print data from database file

  static cell_1 choices;  // peoples voiceprint names extracted from database file

  double scores[4];  // temp fix until we know what is does !
  int i;

 //debug
 // printf("in voiceprint lookup   ");
 // puts(wavFileA);
 // puts(wavFileB);
 // puts(databaseFile);

  // we could do all this from main ?
  loadDatabaseFromFile(databaseFile, &modelsDatabase, &choices);

  /*  Get score  % don't use leading '/' for file paths here */
  printf("scan voiceprints.. \r\n \r\n");
  testWaveWithModels(wavFileA, wavFileB, &modelsDatabase, &choices,scores);

return;
}

/*
 * File trailer for bbbox_voiceprintLookup.c
 *
 * [EOF]
 */
