/*
 * File: testWaveWithModels.c
 */

/* Include Files */

// #include <matrix.h>  // BEN included this for MX arrays ?

#include <math.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "bbbox_voiceprintLookup_emxutil.h"
#include "generateScore.h"
#include "generateFeaturesForTesting.h"



// #include "fclose.h"
// #include "fread.h"
// #include "fileManager.h"

/* Function Definitions */

/*
 * exist matlab function not supported by code generation, re-write error checking
 * Arguments    : const char fileNameWaveSeparated[20]
 *                const char fileNameWavePostfiltered[20]
 *                const cell_0 *modelStructure
 *                cell_1 *choices
 *                double scores[4]
 * Return Type  : void
 */
void testWaveWithModels(const char *fileNameWaveSeparated[255], const char *fileNameWavePostfiltered[255],
                        const cell_0 *modelStructure, cell_1 *choices, double scores[4])
{


  emxArray_real_T *xSeparated;
  emxArray_real_T *xPostfiltered;


 // xSeparated *mxCreateDoubleMatrix(5000000, 1, mxREAL);
 // xPostfiltered *mxCreateDoubleMatrix(5000000, 1, mxREAL);


  double value;
  int k;

  emxArray_real_T *activeFeatures;
  emxArray_boolean_T *activeMask;



  double w[1024];
  boolean_T noiseMask[24];
  double Hl[24];
  double Bl[24];
  double choicesIndex[4];


  (void)fileNameWaveSeparated;  // what does this do ? matlab generated!



  emxInit_real_T(&xSeparated, 1);
  emxInit_real_T(&xPostfiltered, 1);

  xSeparated->size[0]=5000000;  // max size of array, but i thought this was dynamic?
  xPostfiltered->size[0]=5000000;


 // assign mem

 emxEnsureCapacity_real_T((emxArray_real_T *)xSeparated,0);
 emxEnsureCapacity_real_T((emxArray_real_T *)xPostfiltered,0);


  // re-write of the error checking..

   if (fileNameWaveSeparated == 0) {
  puts("File name for separated wave not found!");
  int error = -1;
   }

  if (fileNameWavePostfiltered  == 0)  {
    puts("File name for post-filtered wave not found!");
    int error = -1;
    exit(1);
  }

// end error checking of filenames parsed here..

// the matlab way of loading wav files !

  /*  code generation does not support audioread matlab function */
  /*  Load separated wave */
  /*   xSeparated = audioread(fileNameWaveSeparated);  */
  /*  Load post-filtered wave */
  /*   xPostfiltered = audioread(fileNameWavePostfiltered); */

  // fileid = fopen genertaed from matlab


  // We have no stripped off the PCM file header, is this done somewhere ? do we need to ?
puts("opening wavA and wavB in testWaveWithModels.c...  ");
puts(fileNameWaveSeparated);
puts(fileNameWavePostfiltered);


// impliment audioread from matlab , samples into memory.

/// READ WAV A

FILE *fileid =NULL;
signed short ssA;

int buffCountA = 0; // 512 samples per cell


fileid = fopen(fileNameWaveSeparated, "rb");
 // error check
  if(fileid == NULL) {
      puts("Error opening wav file A..");
      exit(1);
    }

  fseek (fileid,44,SEEK_SET); // drop the wav header we don't need it
  while (fread(&ssA, sizeof(signed short) ,1 , fileid) == 1)
    {
    xSeparated->data[buffCountA]=((double)ssA) *(signed)0xFFFFFFFF; // wav sample signed short to double
    buffCountA++;
     }

  fclose(fileid);


// debug
// for ( int i = 1; i <=10000; i++) {printf("%f \r\n",xSeparated->data[i]);}



/// READ WAV B

// fileid already defined
signed short ssB;

int buffCountB = 0; //

fileid = fopen(fileNameWavePostfiltered, "rb");
 // error check
  if(fileid == NULL) {
      puts("Error opening wav file A..");
      exit(1);
    }

  fseek (fileid,44,SEEK_SET); // drop the wav header we don't need it

    while (fread(&ssB, sizeof(signed short) ,1 , fileid) == 1)
        {
     xPostfiltered->data[buffCountB]=((double)ssB) *(signed)0xFFFFFFFF;  // /(signed)0xFFFF; // wav sample signed short to double
     buffCountB++;
        }

  fclose(fileid);

//debug
  // for ( int i = 1; i <=10000; i++) { printf("%f \r\n",xPostfiltered->data[i]);}





  /*  Load models */
  /*  Parameters */
  /*  */
  /*  *************************************************************************  */
  /*  *                                                                       * */
  /*  * Inputs:  N               Size of the frame in samples                 * */
  /*  *                                                                       * */
  /*  * Outputs: window          Vector with the analysis window              * */
  /*  *                                                                       * */
  /*  *************************************************************************  */
  /*  *                                                                       * */
  /*  * Description:                                                          *  */
  /*  *                                                                       *  */
  /*  * This generates a custom window.                                       * */
  /*  *                                                                       *  */
  /*  ************************************************************************* */
  /*   */
  /*  Empty frame */

   /*  BEN added definition of value here for C code generation */
  /// float value = 0.0;  // should i define this as a floating point ? ?????
value = 0.0;

  for (k = 0; k < 1024; k++) {
    /*  Define the shape of the window */
    if (k < 256) {
      value = 0.5 - 0.5 * cos(7.9916 * (double)k / 1024.0);
    }

    if ((k >= 256) && (k < 512)) {
      value = 0.5 - 0.5 * cos(1.9979 * (2.0 - 4.0 * (double)k / 1024.0));
      value = sqrt(1.0 - value * value);
    }

    if ((k >= 512) && (k < 768)) {
      value = 0.5 - 0.5 * cos(1.9979 * (4.0 * (double)k / 1024.0 - 2.0));
      value = sqrt(1.0 - value * value);
    }

     if (k > 768) {
      value = 0.5 - 0.5 * cos(1.9979 * (4.0 - 4.0 * (double)k / 1024.0));
    }

    /*  Save value */
    w[k] = value;
  }

  emxInit_real_T1(&activeFeatures, 2);
  emxInit_boolean_T(&activeMask, 2);

  /*  Generate features  */
generateFeaturesForTesting(xSeparated, xPostfiltered, w, activeFeatures, activeMask, noiseMask, Hl, Bl);


  /*  Generate score */
generateScore(modelStructure->f5, modelStructure->f6, modelStructure->f7,modelStructure->f8,
              activeFeatures, activeMask, noiseMask, Hl, Bl, choicesIndex, scores);


  /*  write this in C from code gen */

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

  emxFree_boolean_T(&activeMask);
  emxFree_real_T(&activeFeatures);
  emxFree_real_T(&xPostfiltered);
  emxFree_real_T(&xSeparated);




// printf ("%f \r\n",choicesIndex[1]);



int bolox = choicesIndex[2];

printf ("voiceprint ID detected.. %s \r\n",choices->modelNames[bolox]);  // 2d array modelNames in cell_1 strut

     //*********************************************************************************

    // choices->f1(k) = modelsDatabase(&choicesIndex(k),1));   //  just change i to K , to simple !?

     //******************************************************************************************


  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */
}

/*
 * File trailer for testWaveWithModels.c
 *
 * [EOF]
 */
