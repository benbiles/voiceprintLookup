///File: bbbox_voiceprintLookup.h

#ifndef BBBOX_VOICEPRINTLOOKUP_H
#define BBBOX_VOICEPRINTLOOKUP_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern void bbbox_voiceprintLookup(const char *wavFileA[255], const char *wavFileB[255], const char *databaseFile[255]);


extern char voiceId[20];

#endif

/*
 * File trailer for bbbox_voiceprintLookup.h
 *
 * [EOF]
 */
