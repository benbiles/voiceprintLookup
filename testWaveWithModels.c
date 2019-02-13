/// File: testWaveWithModels.c

#include <math.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "bbbox_voiceprintLookup_emxutil.h"
#include "generateScore.h"
#include "generateFeaturesForTesting.h"

// not needed

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
                        const cell_0 *modelStructure, cell_1 *choices, double scores[1000])
{

  emxArray_real_T *xSeparated;
  emxArray_real_T *xPostfiltered;

  double value;
  int k;

  emxArray_real_T *activeFeatures;
  emxArray_boolean_T *activeMask;

  double w[1024];
  boolean_T noiseMask[24];
  double Hl[24];
  double Bl[24];
  double choicesIndex[1000];

  extern char voiceId[20];

  (void)fileNameWaveSeparated;  // what does this do ? matlab generated!


  emxInit_real_T(&xSeparated, 1);
  emxInit_real_T(&xPostfiltered, 1);


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

// end error checking

  /*  not support audioread matlab function */
  /*  Load separated wave */
  /*   xSeparated = audioread(fileNameWaveSeparated);  */
  /*  Load post-filtered wave */
  /*   xPostfiltered = audioread(fileNameWavePostfiltered); */


  // debug
  // puts("in testWaveWithModels.c...  ");
  // puts(fileNameWaveSeparated);
  // puts(fileNameWavePostfiltered);

// file desciptor for reading wav files
FILE *fileid =NULL;




/// find size of wav file A
int wavSizeA = 0; // 512 samples per cell
signed short junkA;

fileid = fopen(fileNameWaveSeparated, "rb"); // error check
  if(fileid == NULL) {
      puts("Error determining wav file A size..");
      exit(1);
    }
  while (fread(&junkA, sizeof(signed short) ,1 , fileid) == 1) { wavSizeA++;}
  fclose(fileid);

  /// find size of wav file B
int wavSizeB = 0; // 512 samples per cell
signed short junkB;

fileid = fopen(fileNameWavePostfiltered, "rb"); // error check
  if(fileid == NULL) {
      puts("Error determining wav file B size..");
      exit(1);
    }
  while (fread(&junkB, sizeof(signed short) ,1 , fileid) == 1) { wavSizeB++;}
  fclose(fileid);

 if ( wavSizeA >= 15000000 ) {
  printf("\r\n WAV size to long EXIT... avoiding being a memory hog ");
  exit(1);
 }


 if ( wavSizeA == wavSizeB )
 {
// dynamically allocate amx array memory size according to wav file size.
 xSeparated->size[0]=wavSizeA+1000;  //
 xPostfiltered->size[0]=wavSizeB+1000;
  // assign mem
 emxEnsureCapacity_real_T((emxArray_real_T *)xSeparated,0);
 emxEnsureCapacity_real_T((emxArray_real_T *)xPostfiltered,0);

printf("\r\n dynamically allocated memory file1.. %u",wavSizeA,"\r\n");
printf("\r\n dynamically allocated memory file2.. %u",wavSizeB,"\r\n");
 }
else
    {
    printf("\r\n ERROR! please input wav pairs WaveSeparated & WavePostfiltered or use path to same wav file \r\n");
    exit(0);
     }

// impliment audioread, samples into memory.

// strip off the PCM file header 44 bytes , should we used 46bytes or use a proper WAV lib?


/// READ WAV A
int buffCountA = 0; // 512 samples per cell
signed short ssA;

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

printf("\r\n scan features.. \r\n");
  /*  Generate features  */
generateFeaturesForTesting(xSeparated, xPostfiltered, w, activeFeatures, activeMask, noiseMask, Hl, Bl);

printf("\r\n scan voiceprints.. \r\n");

  ///  Generate score
generateScore(modelStructure->f5, modelStructure->f6, modelStructure->f7,modelStructure->f8,
              modelStructure->f9, modelStructure->f10, modelStructure->f11,modelStructure->f12,
              modelStructure->f13, modelStructure->f14,
              activeFeatures, activeMask, noiseMask, Hl, Bl, choicesIndex, scores);



  // Clear memory before finalise results and exit program.
  emxFree_boolean_T(&activeMask);
  emxFree_real_T(&activeFeatures);
  emxFree_real_T(&xPostfiltered);
  emxFree_real_T(&xSeparated);

  //end


// PRINT FINAL VOICE PRINT!!!

int lox = (int)choicesIndex[0];  // cast double to int for indexing modelNames.

lox = lox; // matlab / octave .M arrays starts at 1 not 0

// printf("%u",lox);

printf ("\r\n \r\n Voiceprint Detected.. %s \r\n",choices->modelNames[lox]);  // 2d array modelNames in cell_1 strut

//*********************************************************************************

voiceId[0] = choices->modelNames[lox];  // get database voiceprint name of winner!
//*****************************************************************************************

return;
}

/*
 * File trailer for testWaveWithModels.c
 *
 * [EOF]
 */
