/*
 * File: _coder_bbbox_voiceprintLookup_api.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_bbbox_voiceprintLookup_api.h"
#include "_coder_bbbox_voiceprintLookup_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131466U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "bbbox_voiceprintLookup",            /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[20]);

static const mxArray *b_emlrt_marshallOut(const cell_0 *u);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *databaseFile, const char_T *identifier, char_T y[17]);

static const mxArray *c_emlrt_marshallOut(const real_T u[6144]);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const emlrtMsgIdentifier *parentId, char_T y[17]);

static const mxArray *d_emlrt_marshallOut(const emlrtStack *sp, const cell_1 u);

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *modelStructure, const char_T *identifier, cell_0 *y);

static const mxArray *e_emlrt_marshallOut(const real_T u[4]);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *wavFileA,
  const char_T *identifier, char_T y[20]);
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const char_T u[18]);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, cell_0 *y);
static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[6144]);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[20]);
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[17]);
static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[6144]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char_T y[20]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[20])
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const cell_0 *u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const cell_0 *u)
{
  const mxArray *y;
  int32_T i0;
  int32_T iv1[2];
  const mxArray *b_y;
  const mxArray *m1;
  y = NULL;
  for (i0 = 0; i0 < 2; i0++) {
    iv1[i0] = 4 + -2 * i0;
  }

  emlrtAssign(&y, emlrtCreateCellArrayR2014a(2, iv1));
  b_y = NULL;
  m1 = emlrtCreateDoubleScalar(u->f1);
  emlrtAssign(&b_y, m1);
  emlrtSetCell(y, 0, b_y);
  b_y = NULL;
  m1 = emlrtCreateDoubleScalar(u->f2);
  emlrtAssign(&b_y, m1);
  emlrtSetCell(y, 1, b_y);
  b_y = NULL;
  m1 = emlrtCreateDoubleScalar(u->f3);
  emlrtAssign(&b_y, m1);
  emlrtSetCell(y, 2, b_y);
  b_y = NULL;
  m1 = emlrtCreateDoubleScalar(u->f4);
  emlrtAssign(&b_y, m1);
  emlrtSetCell(y, 3, b_y);
  emlrtSetCell(y, 4, c_emlrt_marshallOut(u->f5));
  emlrtSetCell(y, 5, c_emlrt_marshallOut(u->f6));
  emlrtSetCell(y, 6, c_emlrt_marshallOut(u->f7));
  emlrtSetCell(y, 7, c_emlrt_marshallOut(u->f8));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *databaseFile
 *                const char_T *identifier
 *                char_T y[17]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *databaseFile,
  const char_T *identifier, char_T y[17])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(databaseFile), &thisId, y);
  emlrtDestroyArray(&databaseFile);
}

/*
 * Arguments    : const real_T u[6144]
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const real_T u[6144])
{
  const mxArray *y;
  const mxArray *m2;
  static const int32_T iv2[2] = { 256, 24 };

  real_T *pData;
  int32_T i1;
  int32_T i;
  int32_T b_i;
  y = NULL;
  m2 = emlrtCreateNumericArray(2, iv2, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m2);
  i1 = 0;
  for (i = 0; i < 24; i++) {
    for (b_i = 0; b_i < 256; b_i++) {
      pData[i1] = u[b_i + (i << 8)];
      i1++;
    }
  }

  emlrtAssign(&y, m2);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                char_T y[17]
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, char_T y[17])
{
  j_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const cell_1 u
 * Return Type  : const mxArray *
 */
static const mxArray *d_emlrt_marshallOut(const emlrtStack *sp, const cell_1 u)
{
  const mxArray *y;
  int32_T iv4[1];
  y = NULL;
  iv4[0] = 4;
  emlrtAssign(&y, emlrtCreateCellArrayR2014a(1, iv4));
  emlrtSetCell(y, 0, emlrt_marshallOut(sp, u.f1));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *modelStructure
 *                const char_T *identifier
 *                cell_0 *y
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *modelStructure, const char_T *identifier, cell_0 *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(modelStructure), &thisId, y);
  emlrtDestroyArray(&modelStructure);
}

/*
 * Arguments    : const real_T u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *e_emlrt_marshallOut(const real_T u[4])
{
  const mxArray *y;
  const mxArray *m3;
  static const int32_T iv5[1] = { 0 };

  static const int32_T iv6[1] = { 4 };

  y = NULL;
  m3 = emlrtCreateNumericArray(1, iv5, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m3, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m3, iv6, 1);
  emlrtAssign(&y, m3);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *wavFileA
 *                const char_T *identifier
 *                char_T y[20]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *wavFileA,
  const char_T *identifier, char_T y[20])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(wavFileA), &thisId, y);
  emlrtDestroyArray(&wavFileA);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char_T u[18]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const char_T u[18])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 1, 18 };

  y = NULL;
  m0 = emlrtCreateCharArray(2, iv0);
  emlrtInitCharArrayR2013a(sp, 18, m0, &u[0]);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                cell_0 *y
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, cell_0 *y)
{
  emlrtMsgIdentifier thisId;
  int32_T i;
  int32_T iv3[2];
  boolean_T bv0[2];
  thisId.fParent = parentId;
  thisId.bParentIsCell = true;
  for (i = 0; i < 2; i++) {
    iv3[i] = 4 + -2 * i;
    bv0[i] = false;
  }

  emlrtCheckCell(sp, parentId, u, 2U, iv3, bv0);
  thisId.fIdentifier = "1";
  y->f1 = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 0)),
    &thisId);
  thisId.fIdentifier = "2";
  y->f2 = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 1)),
    &thisId);
  thisId.fIdentifier = "3";
  y->f3 = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 2)),
    &thisId);
  thisId.fIdentifier = "4";
  y->f4 = g_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 3)),
    &thisId);
  thisId.fIdentifier = "5";
  h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 4)), &thisId,
                     y->f5);
  thisId.fIdentifier = "6";
  h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 5)), &thisId,
                     y->f6);
  thisId.fIdentifier = "7";
  h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 6)), &thisId,
                     y->f7);
  thisId.fIdentifier = "8";
  h_emlrt_marshallIn(sp, emlrtAlias(emlrtGetCell(sp, parentId, u, 7)), &thisId,
                     y->f8);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = k_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[6144]
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T y[6144])
{
  l_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char_T ret[20]
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[20])
{
  static const int32_T dims[2] = { 1, 20 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "char", false, 2U, dims);
  emlrtImportCharArrayR2015b(sp, src, &ret[0], 20);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                char_T ret[17]
 * Return Type  : void
 */
static void j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, char_T ret[17])
{
  static const int32_T dims[2] = { 1, 17 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "char", false, 2U, dims);
  emlrtImportCharArrayR2015b(sp, src, &ret[0], 17);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[6144]
 * Return Type  : void
 */
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T ret[6144])
{
  static const int32_T dims[2] = { 256, 24 };

  int32_T i2;
  int32_T i3;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  for (i2 = 0; i2 < 24; i2++) {
    for (i3 = 0; i3 < 256; i3++) {
      ret[i3 + (i2 << 8)] = (*(real_T (*)[6144])emlrtMxGetData(src))[i3 + (i2 <<
        8)];
    }
  }

  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void bbbox_voiceprintLookup_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[1])
{
  char_T wavFileA[20];
  char_T wavFileB[20];
  char_T databaseFile[17];
  char_T voiceId[18];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "wavFileA", wavFileA);
  emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "wavFileB", wavFileB);
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "databaseFile", databaseFile);

  /* Invoke the target function */
  bbbox_voiceprintLookup(wavFileA, wavFileB, databaseFile, voiceId);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, voiceId);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void bbbox_voiceprintLookup_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  bbbox_voiceprintLookup_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */

void bbbox_voiceprintLookup_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void bbbox_voiceprintLookup_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void loadDatabaseFromFile_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1])
{
  char_T fileNameDatabase[17];
  cell_0 varDatabase;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "fileNameDatabase",
                     fileNameDatabase);

  /* Invoke the target function */
  loadDatabaseFromFile(fileNameDatabase, &varDatabase);

  /* Marshall function outputs */
  plhs[0] = b_emlrt_marshallOut(&varDatabase);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void testWaveWithModels_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[2])
{
  real_T (*scores)[4];
  char_T fileNameWaveSeparated[20];
  char_T fileNameWavePostfiltered[20];
  cell_0 modelStructure;
  cell_1 choices;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  scores = (real_T (*)[4])mxMalloc(sizeof(real_T [4]));

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "fileNameWaveSeparated",
                   fileNameWaveSeparated);
  emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "fileNameWavePostfiltered",
                   fileNameWavePostfiltered);
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "modelStructure",
                     &modelStructure);

  /* Invoke the target function */
  testWaveWithModels(fileNameWaveSeparated, fileNameWavePostfiltered,
                     &modelStructure, &choices, *scores);

  /* Marshall function outputs */
  plhs[0] = d_emlrt_marshallOut(&st, choices);
  if (nlhs > 1) {
    plhs[1] = e_emlrt_marshallOut(*scores);
  }
}

/*
 * File trailer for _coder_bbbox_voiceprintLookup_api.c
 *
 * [EOF]
 */
