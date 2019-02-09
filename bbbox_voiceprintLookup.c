/*
 * File: bbbox_voiceprintLookup.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

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
void bbbox_voiceprintLookup(const char *wavFileA[255], const char *wavFileB[255], const char *databaseFile[255], char voiceId[18])
 {
  static cell_0 modelsDatabase;  // voice print data from database file

  static cell_1 choices;  // peoples voiceprint names extracted from database file

  double scores[4];  // temp fix until we know what is does !
  int i;

  //debug print chunk
  printf("in voiceprint lookup   ");

  puts(wavFileA);
  puts(wavFileB);
  puts(databaseFile);



  // END

  loadDatabaseFromFile(databaseFile, &modelsDatabase, &choices);


  /*  Get score  % don't use leading '/' for file paths here */
  testWaveWithModels(wavFileA, wavFileB, &modelsDatabase, &choices, scores);

  /*  Print result */
  /* display ID'd person */



  /*  not sure if this is useful */


   // can we print the scores?

// voiceId = choices.fxyz;  // ???

return voiceId;
  /*  final ID'd speaking person output by function */
}



/*
 * File trailer for bbbox_voiceprintLookup.c
 *
 * [EOF]
 */
