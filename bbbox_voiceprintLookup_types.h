/// File: bbbox_voiceprintLookup_types.h

#ifndef BBBOX_VOICEPRINTLOOKUP_TYPES_H
#define BBBOX_VOICEPRINTLOOKUP_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#include <stdio.h>
#ifndef typedef_cell_0
#define typedef_cell_0

typedef struct {
  double f1;
  double f2;
  double f3;
  double f4;
  double f5[6144];
  double f6[6144];
  double f7[6144];
  double f8[6144];
  double f9[6144];
  double f10[6144];
  double f11[6144];
  double f12[6144];
  double f13[6144];
  double f14[6144];
} cell_0;

#endif                                 /*typedef_cell_0*/

#ifndef typedef_cell_1
#define typedef_cell_1

typedef struct {
  char modelNames[1000][20]; // 2d array of modelNames from database / up to 1000 names
  } cell_1;

#endif                                 /*typedef_cell_1*/

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_boolean_T*/

#ifndef typedef_emxArray_boolean_T
#define typedef_emxArray_boolean_T

typedef struct emxArray_boolean_T emxArray_boolean_T;

#endif                                 /*typedef_emxArray_boolean_T*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/
#endif


// BEN added this for testing memory




/*
 * File trailer for bbbox_voiceprintLookup_types.h
 *
 * [EOF]
 */
