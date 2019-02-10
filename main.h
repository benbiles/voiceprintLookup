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

// testing file paths, use command argv normally

#define wavFileA "/home/ben/test/ben.wav"
#define wavFileB "/home/ben/test/ben.wav"
#define databaseFile "/home/ben/test/modelDatabase.txt"

extern char voiceId[20];

#endif

/*
 * File trailer for main.h
 *
 * [EOF]
 */
