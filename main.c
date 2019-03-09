/// File: main.c

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
/*inotify dep */
#include <sys/inotify.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
/*fork and pid */
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> // might not need this ?

/* Function Proto */

/*voiceprintLookup in child process with IPC pipe to main*/
static void spawnLookup ();
/* monitors incoming ODAS files in child process IPC to main*/
int watchFolder (int argc, char** argv[]);


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

/* Definitions */

int nModelNumber; // number of models in database
int welcomePostFlag = 1; // initial info post

char finalResult;
char *voiceId[256];

char *SPfileA[256];
char *SPfileB[256];
char *SPfileC[256];
int SPfileNameCount = 0;

char *PFfileA[256];
char *PFfileB[256];
char *PFfileC[256];
int PFfileNameCount = 0;

int SPfileReady =0;
int PFfileReady =0;

/*problem with basic tests, simplify to debug */
int goer = 0;
int goer2 =0;


/* inotify  */
#define EVENT_SIZE  sizeof(struct inotify_event)
#define EVENT_BUF_LEN  (1024*(EVENT_SIZE+16))


/// MAIN welcome post and check argv

int main(int argc, char** argv[])
{
 // (void)argc;
 // (void)argv;

 /*load database on 1st run flag*/
 loadDatabaseFlag = 0;


 /* get data base path from command line input */
 strcpy (databasePath ,argv[2]);
 // strcpy (wavPath ,argv[1]);

 /*Welcome Post*/
 if ( welcomePostFlag = 1 )
 {
 printf("\r\n Welcome to voiceLookup ver 0.3  [ multi-process version ] \r\n");
 // printf( "database path %s \n", databasePath);

 // print command args in console
 printf ("\r\n paths...  \r\n");
 for (int i=1; i<argc; ++i) {
      printf(argv[i],"  \r\n");
      puts("");
    }
    /* done welcome post , don't do it again !*/
    welcomePostFlag = 0;
 }

 /* error check argc */
 if ( argc < 3 )
     {
     printf("error...please supply ODAS watch folder path and modelDatabase.txt path \r\n");
     exit(-1); // error code -1
     }

  // Initialize the application, init amx array cells originally in matlab
  bbbox_voiceprintLookup_initialize();
  main_loadDatabaseFromFile();
  main_bbbox_voiceprintLookup();
  main_testWaveWithModels();


/// WATCHFOLDER function run in child process
/// IPC pipe in new file pairs found


  /*initialize the 2 watch folder pipes */
  pipe(pipeSPnew);
  pipe(pipePFnew);

  /*initialize new file paths to voiceprintLookup pipes */
  pipe(pipeSPtx);
  pipe(pipePFtx);

  /*initialize voiceprintLookup pipe */
  pipe(pipefd);


 /// SPAWN WATCHFOLDER CHILD PROCESS while loop
  switch (pid2 = fork())
  {

  case -1: perror ("\r\n watch folder fork process failed.. quit \r\n");
        exit(1);

  case  0: /// CHILD process

  /* get new matching file pair from ODAS folder*/
  watchFolder(argc,argv);  /// watchFolder while loop in child process.

/// PARENT process
  default:




/// SPAWN VOICEPRINTLOOKUP "1" CHILD PROCESS while loop

  switch (pid1 = fork())
  {

  case -1: perror ("voiceprintLookup fork process failed /r/n");
        exit(1);

  case  0: /// in CHILD process

   /* SP and PF wav pair found , GO bbbox_voiceprintLookup */
   bbbox_voiceprintLookup(databasePath);

  default: /// in PARENT process

 /*clear old messages*/
         fflush(stdin);

/// MAIN WHILE LOOP PARENT

 while(1)
    {

 // debug
// printf( " \r\n were in MAIN LOOP in PARENT ONE !!\r\n  ");

  /* read IPC pipes from child process for new file pair found */
  read(pipeSPnew[0],bufferPipeSPnew,256);
  read(pipePFnew[0],bufferPipePFnew,256);

  // debug
// printf("\r\n SP old %s \r\n SP new %s \r\n",SPfilenameOLD,bufferPipeSP );
// printf("\r\n PF old %s \r\n PF new %s \r\n",PFfilenameOLD,bufferPipePF );


/* test for empty buffer*/
if (( bufferPipeSPnew != NULL) && ( bufferPipeSPnew[0] == '\0' ) &&
    ( bufferPipePFnew != NULL) && ( bufferPipePFnew[0] == '\0' ) )

    {
    goer = 0;
    }
    else
    {
    goer = 1;
    }


/* make sure buffer is not same as old */
if ( (strcmp(bufferPipeSPnew,SPfilenameOLD) == 0) &&
   (strcmp(bufferPipePFnew,PFfilenameOLD) == 0) )
    {
  goer2 = 0;
    }
 else
    {
    goer2 = 1;
    }


if ( goer == 1 && goer2 == 1 )

  {

  goer = 0;
  goer2= 0;


  strcpy(SPfilename,bufferPipeSPnew);
  strcpy(PFfilename,bufferPipePFnew);

  /* clear bufferPipeSP & bufferPipePF so we prevent multiple runs in while loop*/
  memset(bufferPipeSPnew, 0, 256);
  memset(bufferPipePFnew, 0, 256);

    //debug
  printf("\r\n rx ipc %s \r\n",SPfilename);
  printf("\r\n rx ipc %s \r\n",PFfilename);


   strcpy(SPfilenameOLD,SPfilename);
   strcpy(PFfilenameOLD,PFfilename);

/// fork bbbox_voiceprintLookup function as child process

/* after 1st run we don't need to reload database*/
loadDatabaseFlag++;
//debug
// printf("loadDatabaseFlag %d",loadDatabaseFlag);


/// IPC SPfilename & PFfilename to voiceprintLook child process A
 /* wite IPC pipes from child process for new file pair found */
  write(pipeSPtx[1],SPfilename,256);
  write(pipePFtx[1],PFfilename,256);

   /// GET IPC RESULTS FROM voiceprintLookup

         /*clear old messages*/
         fflush(stdin);
         /*close unused end of pipe*/
         close(pipefd[1]);
        // read pipe
         read(pipefd[0],bufferPipe,sizeof(bufferPipe));
         /*print */

         /*FINAL RESULT FROM lookup child Process over IPC*/
         printf("result from IPC %s \r\n",bufferPipe);

        /* FINAL RESULT !!!! */
         finalResult = bufferPipe;


} // END new file paths ready and sent

} /// END switch 1

} /// END switch 2


} /// END while


  /* should never get here */
  bbbox_voiceprintLookup_terminate();
  /* error */
  printf("end of main error, exiting...");
  exit(1);

} ///end MAIN




/// WATCH FOLDER FUNCTION

/// while loop runs as child process.
/// IPC pipe to to IPC pipe found file name pairs to parent.

int watchFolder(int argc, char** argv[])
    {

 while (1)
 {

 //debug
// printf( "\r\n were in watchfolder while loop \r\n");

 /* inotify loop, append SPfilename and PFfilename with new SP PF files from odas watch folder */

  /* watch ODAS folder for new file with inotify   */
  int length, i = 0;
  int fd;
  int wd;
  char buffer[EVENT_BUF_LEN];

  /*creating the usual INOTIFY instance*/
   fd = inotify_init();
  /*creating the !!! threaded !!!  INOTIFY instance*/
 //  fd = inotify_init1(IN_CLOEXEC);  // IN_NONBLOCK // IN_CLOEXEC

  /*checking for error*/
  if ( fd < 0 ) {
    perror( "inotify_init" );
  }


  /* TODO: validate watch directory argv[1] here before adding to inotfy */


 /* watch directory supplied by argv[1] command line” directory. */
  wd = inotify_add_watch( fd, argv[1] , IN_CREATE | IN_DELETE | IN_CLOSE );


  /// this read BLOCKS until file or defined EVENT occurs.
  length = read( fd, buffer, EVENT_BUF_LEN );

  //checking for error
  if ( length < 0 )
    {
        perror( "read" );
  }

  /*actually read return the list of change events happens.
  Here, read the change event one by one and process it accordingly.*/
  while ( i < length )
    {
    struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];

  if ( event->len ) {
  /* if generated audio file is finalised by ODAS */
      if ( event->mask & IN_CLOSE) {
      //    printf( "New file %s created.\n", event->name );
        /* get file name length to test file type */
        int len = strlen(event->name);

   /* sp.wav? */
   if (strcmp(&event->name[len-6], "sp.wav") == 0)
        {
     /* copy SPfilename into ring buffer */
     if (SPfileNameCount == 0 ) { strcpy (SPfileA ,event->name); }

     if (SPfileNameCount == 1 ) { strcpy (SPfileB ,event->name); }

     if (SPfileNameCount == 2 ) { strcpy (SPfileC ,event->name); }

      SPfileNameCount++;
      if ( SPfileNameCount >=3 ) { SPfileNameCount = 0;}
        /*SP file ready */
        SPfileReady =1;
         }

      /* pf.wav? */
     else if (strcmp(&event->name[len-6], "pf.wav") == 0)

     {
     /* copy PFfilename into ring buffer */
     if (PFfileNameCount == 0 ){ strcpy (PFfileA,event->name); }

     if (PFfileNameCount == 1 ){ strcpy (PFfileB,event->name); }

     if (PFfileNameCount == 2 ){ strcpy (PFfileC,event->name); }

      PFfileNameCount++;
      if ( PFfileNameCount >=3 )  { PFfileNameCount = 0; }
      /* PF file ready */
      PFfileReady = 1;
      }
    }

    /*uncomment to report other inotify action if wanted here */
/*
      else if ( event->mask & IN_DELETE )
      {
        if ( event->mask & IN_ISDIR ) { printf( "Directory %s deleted.\n", event->name ); }
        else { printf( "File %s deleted.\n", event->name ); }
         }
*/

/*clean up inotify*/
  }
    i += EVENT_SIZE + event->len;

  } // END WHILE LOOP

  /*cleanup removing the “/tmp” directory from the watch list.*/
   inotify_rm_watch( fd, wd );
  /*closing the INOTIFY instance*/
    close( fd );

/// test for Separated and PostFiltered pair ready and GO voiceprintLookup
if ( SPfileReady == 1  &&  PFfileReady == 1 )

{

SPfileReady = 0;
PFfileReady = 0;

    /*clear whatever was there before! */
 // memset(SPfilename, 0, 256);
 // memset(PFfilename, 0, 256);

    /* ODAS file recorder path to SP file name */
     strcpy (SPfilename,argv[1]);
     /* ODAS file recorder path to PF file name */
     strcpy (PFfilename,argv[1]);

/// test for new filename matching pair
/* N char to compare for match */
 int cmpN = 12;

 if (( SPfileA[0] != 0 ) && ( PFfileA[0] != 0 ) && (strncmp(SPfileA,PFfileA,cmpN) == 0 ))
          {
            strcat(SPfilename,SPfileA);
            strcat(PFfilename,PFfileA);
            /*clear filenames for next match testing*/
            memset(SPfileA, 0, 256);
            memset(PFfileA, 0, 256);
              }

 if (( SPfileA[0] != 0 ) && ( PFfileB[0] != 0 ) && (strncmp(SPfileA,PFfileB,cmpN) == 0 ))
            {
            strcat(SPfilename,SPfileA);
            strcat(PFfilename,PFfileB);
             /*clear filenames for next match testing*/
             memset(SPfileA, 0, 256);
             memset(PFfileB, 0, 256);
               }

 if (( SPfileB[0] != 0 ) && ( PFfileA[0] != 0 ) && (strncmp(SPfileB,PFfileA,cmpN) == 0 ))
              {
            strcat(SPfilename,SPfileB);
            strcat(PFfilename,PFfileA);
             memset(SPfileB, 0, 256);
             memset(PFfileA, 0, 256);
               }

 if (( SPfileB[0] != 0 ) && ( PFfileB[0] != 0 ) && (strncmp(SPfileB,PFfileB,cmpN) == 0 ))
            {
            strcat(SPfilename,SPfileB);
            strcat(PFfilename,PFfileB);
             memset(SPfileB, 0, 256);
             memset(PFfileB, 0, 256);
               }

 if (( SPfileB[0] != 0 ) && ( PFfileC[0] != 0 ) && (strncmp(SPfileB,PFfileC,cmpN) == 0 ))
              {
            strcat(SPfilename,SPfileB);
            strcat(PFfilename,PFfileC);
             memset(SPfileB, 0, 256);
             memset(PFfileC, 0, 256);
               }

 if (( SPfileC[0] != 0 ) && ( PFfileB[0] != 0 ) && (strncmp(SPfileC,PFfileB,cmpN) == 0 ))
             {
            strcat(SPfilename,SPfileC);
            strcat(PFfilename,PFfileB);
             memset(SPfileC, 0, 256);
             memset(PFfileB, 0, 256);
               }

 if (( SPfileC[0] != 0 ) && ( PFfileC[0] != 0 ) && (strncmp(SPfileC,PFfileC,cmpN) == 0 ))
              {
            strcat(SPfilename,SPfileC);
            strcat(PFfilename,PFfileC);
              memset(SPfileC, 0, 256);
              memset(PFfileC, 0, 256);
               }

 if (( SPfileA[0] != 0 ) && ( PFfileC[0] != 0 ) && (strncmp(SPfileA,PFfileC,cmpN) == 0 ))
              {
            strcat(SPfilename,SPfileA);
            strcat(PFfilename,PFfileC);
             memset(SPfileA, 0, 256);
             memset(PFfileC, 0, 256);
               }

 if (( SPfileC[0] != 0 ) && ( PFfileA[0] != 0 ) && (strncmp(SPfileC,PFfileA,cmpN) == 0 ))
                {
            strcat(SPfilename,SPfileC);
            strcat(PFfilename,PFfileA);
             memset(SPfileC, 0, 256);
             memset(PFfileA, 0, 256);
               }

// debug
 printf( "\r\n New SP file..%s \r\n", SPfilename);
 printf( "\r\n New PF file..%s \r\n", PFfilename);


 /// IPC pipe file names to main process !
  /*write to IPC main SPfilename and PFfilename to main process*/

  int sSP = sizeof(SPfilename);
  int sPF = sizeof(PFfilename);
  write(pipeSPnew[1],SPfilename,sSP);       /// write to stream
  write(pipePFnew[1],PFfilename,sPF);       /// write to stream

} /// end matching pair

} /// end while loop

} /// end watch folder function




///****************************************************************************************************


/// initialize multidimensional cell arrays

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

// BEN  don't think were using these ???? check this

  result->f1 = argInit_real_T();
  result->f2 = argInit_real_T();
  result->f3 = argInit_real_T();
  result->f4 = argInit_real_T();

  /* need to replace with 3D array ? how to do this 1st attempt failed !  */

  argInit_256x24_real_T(result->f5);
  argInit_256x24_real_T(result->f6);
  argInit_256x24_real_T(result->f7);
  argInit_256x24_real_T(result->f8);
  argInit_256x24_real_T(result->f9);
  argInit_256x24_real_T(result->f10);
  argInit_256x24_real_T(result->f11);
  argInit_256x24_real_T(result->f12);
  argInit_256x24_real_T(result->f13);
  argInit_256x24_real_T(result->f14);
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

  char voiceId[18]; // BEN added , prob not be needed here ?

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
  double scores[1000];

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

/// EOF

/*
 * File trailer for main.c
 *
 * [EOF]
 */
