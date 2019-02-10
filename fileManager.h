/// File: fileManager.h

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "bbbox_voiceprintLookup_types.h"

/* Function Declarations */
extern signed char b_cfopen(const char cfilename[255], const char * cpermission);
extern signed char cfopen(const char cfilename[255], const char * cpermission);
extern void filedata_init(void);

#endif

/*
 * File trailer for fileManager.h
 *
 * [EOF]
 */
