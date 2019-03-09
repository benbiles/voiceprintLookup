/// File: bbbox_voiceprintLookup.c

/* Include Files */
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"

/*needed to include main.h for IPC pipe definitions , not sure this is the best way to do this ? */
#include "main.h"


/* Function Definitions */

/*
 * load the database file
 * Arguments    : const char wavFileA[20]
 *                const char wavFileB[20]
 *                const char databaseFile[17]
 *                char voiceId[18]
 * Return Type  : void
 */



void bbbox_voiceprintLookup(const char *databaseFile[255])
 {

  static cell_0 modelsDatabase;  // voice print data from database file

  static cell_1 choices;  // peoples voiceprint names extracted from database file

  double scores[1000];  // temp fix until we know what is does !
  int i;



/* close unused ends of IPC pipes*/
close(pipeSPtx[1]);
close(pipePFtx[1]);
close(pipefd[0]);


while (1) /// runs as a child process

{

  /// Recieve IPC SPfilename & PFfilename

 /// read is blocking here until we receive both new file paths ?


 /* read IPC pipes from parent process for new file pair */
  read(pipeSPtx[0],bufferPipeSPtx,256);
  read(pipePFtx[0],bufferPipePFtx,256);


  loadDatabaseFromFile(databaseFile, &modelsDatabase, &choices);

  /*  Get score  % don't use leading '/' for file paths here */
  testWaveWithModels(bufferPipeSPtx,bufferPipePFtx,&modelsDatabase, &choices,scores);

  /// IPC result back to Parent Main.c
 int sze = strlen(voiceId[0]);
 /*write sizeof voiceId */
 write(pipefd[1],voiceId[0],sze+1);       /// write to stream

// debug
// printf("\r\n DONE in bbbox_voiceprintLookup.c exited \r\n");


} /// END while loop


printf(" error in bbbox_voiceprintLookup");
 exit(0);

 // i think we exit child process so no need for this return?
}

/*
 * File trailer for bbbox_voiceprintLookup.c
 *
 * [EOF]
 */
