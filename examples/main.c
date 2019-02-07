/*
 * File: main.c
 */

/* Include Files */
#include "stdio.h"
#include "stdlib.h"
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "main.h"
#include "bbbox_voiceprintLookup_terminate.h"
#include "bbbox_voiceprintLookup_initialize.h"

/* Function Declarations */

static void argInit_1x17_char_T(char result[255]); // increase database file name to 255 !
static void argInit_1x20_char_T(char result[255]);
static void argInit_1x255_char_T(char result[255]);
static void argInit_256x24_real_T(double result[6144]);
static void argInit_cell_0(cell_0 *result);
static char argInit_char_T(void);
static double argInit_real_T(void);

static void main_bbbox_voiceprintLookup(void);
static void main_loadDatabaseFromFile(void);
static void main_testWaveWithModels(void);

/* Function Definitions */

/*
 * Arguments    : char result[17]
 * Return Type  : void
 */
static void argInit_1x17_char_T(char result[255])  // increased to 255 database file path
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 255; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_char_T();
  }
}

/*
 * Arguments    : char result[20]
 * Return Type  : void
 */
static void argInit_1x20_char_T(char result[255])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 255; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_char_T();
  }
}

/*
 * Arguments    : double result[6144]
 * Return Type  : void
 */
static void argInit_256x24_real_T(double result[6144])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 256; idx0++) {
    for (idx1 = 0; idx1 < 24; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 8)] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : cell_0 *result
 * Return Type  : void
 */
static void argInit_cell_0(cell_0 *result)
{
  /* Set the value of each structure field.
     Change this value to the value that the application requires. */
  result->f1 = argInit_real_T();
  result->f2 = argInit_real_T();
  result->f3 = argInit_real_T();
  result->f4 = argInit_real_T();
  argInit_256x24_real_T(result->f5);
  argInit_256x24_real_T(result->f6);
  argInit_256x24_real_T(result->f7);
  argInit_256x24_real_T(result->f8);
}

/*
 * Arguments    : void
 * Return Type  : char
 */
static char argInit_char_T(void)
{
  return '?';
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_bbbox_voiceprintLookup(void)
{
  char cv1[255];
  char cv2[255];
  char cv3[255];

  char voiceId[18]; // Ben added this , maybe wrong!

  /* Initialize function 'bbbox_voiceprintLookup' input arguments. */
  /* Initialize function input argument 'wavFileA'. */
  /* Initialize function input argument 'wavFileB'. */
  /* Initialize function input argument 'databaseFile'. */
  /* Call the entry-point 'bbbox_voiceprintLookup'. */

  argInit_1x20_char_T(cv1);
  argInit_1x20_char_T(cv2);
  argInit_1x17_char_T(cv3);


 //  bbbox_voiceprintLookup(cv1, cv2, cv3, voiceId);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_loadDatabaseFromFile(void)
{
  char cv4[255];
  cell_0 varDatabase;

  /* Initialize function 'loadDatabaseFromFile' input arguments. */
  /* Initialize function input argument 'fileNameDatabase'. */
  /* Call the entry-point 'loadDatabaseFromFile'. */
  argInit_1x17_char_T(cv4);

  // loadDatabaseFromFile(cv4, &varDatabase);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_testWaveWithModels(void)
{
  char cv5[255];
  char cv6[255];
  static cell_0 r1;
  cell_1 choices;
  double scores[4];

  /* Initialize function 'testWaveWithModels' input arguments. */
  /* Initialize function input argument 'fileNameWaveSeparated'. */
  /* Initialize function input argument 'fileNameWavePostfiltered'. */
  /* Initialize function input argument 'modelStructure'. */
  /* Call the entry-point 'testWaveWithModels'. */
  argInit_1x20_char_T(cv5);
  argInit_1x20_char_T(cv6);
  argInit_cell_0(&r1);

 //  testWaveWithModels(cv5, cv6, &r1, &choices, scores);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, char** argv[])
{
 // (void)argc;
 // (void)argv;


 // inject path values for testing in debugger ...
// argv[1] = '/home/ben/test/newsound.wav';
// argv[2] = '/home/ben/test/newsound.wav';
// argv[3] = '/home/ben/test/modelDatabase.txt';




 printf("\r\n");
 printf("welcome to bbbox_voiceprintLookup V0.1 \r\n");
 printf("\r\n");
 puts("");

// enable this feature after debugging app

 if ( argc < 4 ) {
        printf("error...please supply nonfiltered.wav filtered.wav modelDatabase.txt \n");
        printf(" \r\n");
        printf("NOTE: the 2 wav files can be the same if three is no filtered wav file \n");
        printf("for now wav files should 48khz 16bit mono \n");
 puts("");
     exit(-1); // error code -1
     }


 printf ("running with...   ","\n");


    for (int i=1; i<argc; ++i)
    {
      printf(argv[i],"\r\n");
    }
puts("");



  /* Initialize the application.
     You do not need to do this more than one time. */

  bbbox_voiceprintLookup_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */

  main_loadDatabaseFromFile();
  main_bbbox_voiceprintLookup();
  main_testWaveWithModels();

// MAIN DO SOMETHING!


// loadDatabaseFromFile(db); ??

 int voiceId;


// test file paths defined in main.h , testing only
bbbox_voiceprintLookup(&wavFileA,&wavFileB,&databaseFile,&voiceId);

/// uncomment this for for deployed app using passed paths of wavs and database from command line!
/// wavA, wavB, databasefile, not sure what voiceID is here yet !!! will delete if possible

// bbbox_voiceprintLookup(argv[1],argv[2],argv[3],voiceId);



// wanted to do this here but its at the end of bbbox_voiceprintLookup for now!

// puts("newsound.wav is recognised as... \r\n");
// puts(voiceId); // display ID'd person


 bbbox_voiceprintLookup_terminate();  // Terminate application.


  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
