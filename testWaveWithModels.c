/*
 * File: testWaveWithModels.c
 */

/* Include Files */
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


  double value;
  int k;

  emxArray_real_T *activeFeatures;
  emxArray_boolean_T *activeMask;



  double w[1024];
  boolean_T noiseMask[24];
  double Hl[24];
  double Bl[24];
  double choicesIndex[4];

  // this was the dummy file...

   static const char cv0[18] = { 'j', 'u', 'n', 'k', ' ', 'b', 'e', 'n',
    ' ', 'd ','e ', 'f ', 'i ', 'n ', 'e ', ' ', ' ' };


  (void)fileNameWaveSeparated;

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


//fread into xSeparated which
//  is an emxArray_real_T  array ??!!!!!!!!!!!!!!!!!!!!!!!!!

// were trying to impliment audioread in matlab !
// read Wav A

FILE *fileid =NULL;
signed short ssA;


double *memdumpA;
memdumpA = malloc (sizeof(double) * 5000000);


double sampleA; // convert the signed short sample into double
int buffCountA = 0; // 512 samples per cell

// int indexer; // ?????

fileid = fopen(fileNameWaveSeparated, "rb");
 // error check
  if(fileid == NULL) {
      puts("Error opening wav file A..");
      exit(1);
    }

  fseek (fileid,46,SEEK_SET); // drop the wav header we don't need it
  while (fread(&ssA, sizeof(signed short) ,1 , fileid) == 1)
    {
    sampleA=((double)ssA); // *(signed)0xFFFF; // wav sample signed short to double
    memdumpA [buffCountA] = sampleA;
    buffCountA++;
     }

  fclose(fileid);

  memcpy(xSeparated,memdumpA,sizeof memdumpA);

 free(memdumpA); // free memory from samples wavA


  // read Wav B

// fileid already defined
signed short ssB;
double sampleB;

double *memdumpB;
memdumpB = malloc (sizeof(double) * 5000000);

int buffCountB = 0; //

fileid = fopen(fileNameWavePostfiltered, "rb");
 // error check
  if(fileid == NULL) {
      puts("Error opening wav file A..");
      exit(1);
    }

  fseek (fileid,46,SEEK_SET); // drop the wav header we don't need it

    while (fread(&ssB, sizeof(signed short) ,1 , fileid) == 1)
        {
     sampleB=((double)ssB);  // /(signed)0xFFFF; // wav sample signed short to double
     memdumpB[buffCountB] = sampleB;
     buffCountB++;
        }

  fclose(fileid);

  memcpy(xPostfiltered,memdumpB,sizeof memdumpB);

 free(memdumpB); // free memory from samples wavB

  // END read wav files to test


  // check samples are in memory , debugging
  // WARNING, can't use Xterm ! not enough buffer !

//  for ( int i = 0; i <=buffCountB; i++)
//  {
//  printf( "%f", &xSeparated[i],"\r\n");
//  printf( "%f", &xPostfiltered[i],"\r\n");
//   puts("");
//    }


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
  for (k = 0; k < 18; k++)

    {
        choices->f1[k] = cv0[k];

        /*  choices{i} = modelsDatabase{choicesIndex(i),1}; */ // original troubling line !!!
     //*********************************************************************************

    // choices->f1(k) = modelsDatabase(choicesIndex(k),1));   //  just change i to K , to simple !?

     //******************************************************************************************
    }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  */
}

/*
 * File trailer for testWaveWithModels.c
 *
 * [EOF]
 */
