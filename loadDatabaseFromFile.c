/*
 * File: loadDatabaseFromFile.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 01-Feb-2019 16:34:19
 */

/* Include Files */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "bbbox_voiceprintLookup.h"
#include "loadDatabaseFromFile.h"
#include "testWaveWithModels.h"
#include "fclose.h"
#include "fileManager.h"


/* Function Definitions */

/*
 * *************************************************************************                                                                      *
 *  * Inputs:  fileNameDatabase File which contains the database            *
 *  *                                                                       *
 *  * Outputs: varDatabase      Structure of the loaded database            *
 *  *                                                                       *
 *  *************************************************************************                                                                       *
 *  * Description:                                                          *
 *  *                                                                       *
 *  * This function loads the database stored in the file.                  *                                                                   *
 *  *************************************************************************
 * Arguments    : const char fileNameDatabase[17]
 *                cell_0 *varDatabase
 * Return Type  : void
 */

  /*  open the database */
void loadDatabaseFromFile(const char *fileNameDatabase[255], cell_0 *varDatabase,cell_1 *choices)

{
  FILE *fileid;
  int iCentroid;
  int iDim;

// for debug
   //debug print chunk
  printf("were in loadDatabaseFromFile.c   ");

  printf("   ");
  puts(fileNameDatabase);
  // END


  /*  open fileNameDatabase in read mode */
  fileid = fopen(fileNameDatabase, "r"); // was cfopen ? can't find any ref to cfopen in C !

 if(fileid == NULL) {
      puts("Error opening file");
   }

 //


// number of voiceprint models = nModels
// centroids = 246
// Dims = 24

// position in read of file depends on if entry is data name or other.

// this needs to be replaced with database, perhaps mysql or something faster?


/// begin caveman code / load 1st 4 database entries

  //************************************************************************

char nModels[20];
char nCentroids[20];
char nDims[20];


char buffer[20];
char value[20];


/// get the 1st 3 entries in database txt file nModels, nCentroids, mDims

   /* while not end-of-file */
    while (!feof(fileid)) {
        /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { nModels[i] = buffer[i];}
            puts(nModels);
            break;
        }}


      while (!feof(fileid)) {
       /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { nCentroids[i] = buffer[i];}
        puts(nCentroids);
            break;
        }
    }

      while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { nDims[i] = buffer[i];}
            puts(nDims);
            break;
        }}

//*****************************************************************************************

        // FIRST NAME in data base

      while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) {choices->modelNames[0][i] = buffer[i];}
        puts(choices->modelNames[0]);
            break;
        }}

 // varDatabase->f1[1] = modelName;


 // values for person 1 in database

  memset(&varDatabase->f5[0], 0, 6144U * sizeof(double));  // why here ?


 for (iDim = 0; iDim < 24; iDim++) {

 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

           // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip newline char
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i]; }
        //END get value

   //puts(value);  // for debug
  char *ptr;
  double finalValue = strtod(value, &ptr);
  varDatabase->f5[iCentroid + (iDim << 8) ] = finalValue; //

  break;
        }}
      } // end loop 256
  } // end 24 loop


  //********************************************************************

  //  2ND NAME IN DATA BASE

      while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { choices->modelNames[1][i] = buffer[i];}
        puts(choices->modelNames[1]);
            break;
        }}


  // varDatabase->f2 = modelName;  //


  // values for person 2 in database

  memset(&varDatabase->f6[0], 0, 6144U * sizeof(double));


   for (iDim = 0; iDim < 24; iDim++) {

 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

           // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip newline char
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i]; }
        //END get value

   //puts(value);  // for debug
  char *ptr;
  double finalValue = strtod(value, &ptr);
  varDatabase->f6[iCentroid + (iDim << 8) ] = finalValue; //

  break;
        }}
      } // end loop 256
  } // end 24 loop


//********************************************************************************

      // 3RD NAME in data base

      while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { choices->modelNames[2][i] = buffer[i];}
        puts(choices->modelNames[2]);
            break;
        }}

  // varDatabase->f3 = modelName;


  // values for person 3 in database

  memset(&varDatabase->f7[0], 0, 6144U * sizeof(double));

  for (iDim = 0; iDim < 24; iDim++) {

 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

           // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip newline char
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i]; }
        //END get value

   //puts(value);  // for debug
  char *ptr;
  double finalValue = strtod(value, &ptr);
  varDatabase->f7[iCentroid + (iDim << 8) ] = finalValue; //

  break;
        }}
      } // end loop 256
  } // end 24 loop

  //*******************************************************************************************

       // 4TH NAME in data base

      while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { choices->modelNames[3][i] = buffer[i];}
        puts(choices->modelNames[3]);
            break;
        }}


 // varDatabase->f4 = modelName;



 // values for person 4 in database

memset(&varDatabase->f8[0], 0, 6144U * sizeof(double));

  for (iDim = 0; iDim < 24; iDim++) {

 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

           // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip newline char
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i]; }
        //END get value

   //puts(value);  // for debug
  char *ptr;
  double finalValue = strtod(value, &ptr);
  varDatabase->f8[iCentroid + (iDim << 8) ] = finalValue; //

  break;
        }}
      } // end loop 256
  } // end 24 loop




  fclose(fileid);
}




/*
 * File trailer for loadDatabaseFromFile.c
 *
 * [EOF]
 */
