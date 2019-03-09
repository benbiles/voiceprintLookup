/// File: main.h

#ifndef MAIN_H
#define MAIN_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"

#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern int main(int argc, char** argv[]);
/* do we need to load the database */
int loadDatabaseFlag;

char *databasePath[256];


char *SPfilename[256];
char *PFfilename[256];
char *SPfilenameOLD[256];
char *PFfilenameOLD[256];

/* process ID's */
  pid_t pid1;
  pid_t pid2;

/* setup IPC watch folder pipes */

  int pipeSPnew[2];
  int pipePFnew[2];

  int pipeSPtx[2];
  int pipePFtx[2];


 /*setup voiceprintLookup result pipe */
  int pipefd[2];


  /*IPC voiceprintLookup result buffer*/
  char bufferPipe[256];

   /*IPC watch folder filename buffers*/
  char bufferPipeSPnew[256];
  char bufferPipePFnew[256];

     /*IPC watch folder filename buffers*/
  char bufferPipeSPtx[256];
  char bufferPipePFtx[256];



extern char *voiceId[256];

extern int nModelNumber; // number of models in database

#endif

/*
 * File trailer for main.h
 *
 * [EOF]
 */
