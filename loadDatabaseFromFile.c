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
void loadDatabaseFromFile(const char *fileNameDatabase[255], cell_0 *varDatabase)

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


    //  if I read from fileid the position moves forward !?????
    // I read 3 lines so at  position in file for 1st name !! mmmm

  //************************************************************************

char nModels[20];
char nCentroids[20];
char nDims[20];
char modelName[20];
char buffer[20];
char value[20];

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
        for (int i = 0; i<= len-1; i++) { modelName[i] = buffer[i];}
        puts(modelName);
            break;
        }}


  varDatabase->f1 = 1.0;  // this defined a variable in matlab ! find out which and why !
  memset(&varDatabase->f5[0], 0, 6144U * sizeof(double));


   /*  get 256 values in loop */
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
    for (iDim = 0; iDim < 24; iDim++) {


    // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i];}
       // puts(value);
            break;
        }}
        //END get value


      /* does this load value into database? should 1.0 be value !  */
      varDatabase->f5[iCentroid + (iDim << 8)] = 1.0;
    }
  }


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
        for (int i = 0; i<= len-1; i++) { modelName[i] = buffer[i];}
        puts(modelName);
            break;
        }}


  varDatabase->f2 = 1.0;
  memset(&varDatabase->f6[0], 0, 6144U * sizeof(double));


   // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
    for (iDim = 0; iDim < 24; iDim++) {

    // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i];}
      //  puts(value);
            break;
        }}
        //END get value

      varDatabase->f6[iCentroid + (iDim << 8)] = 1.0;
    }
  }
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
        for (int i = 0; i<= len-1; i++) { modelName[i] = buffer[i];}
        puts(modelName);
            break;
        }}

  varDatabase->f3 = 1.0;
  memset(&varDatabase->f7[0], 0, 6144U * sizeof(double));

    // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
    for (iDim = 0; iDim < 24; iDim++) {


  // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i];}
       // puts(value);
            break;
        }}
        //END get value


    varDatabase->f7[iCentroid + (iDim << 8)] = 1.0;
    }
  }

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
        for (int i = 0; i<= len-1; i++) { modelName[i] = buffer[i];}
        puts(modelName);
            break;
        }}


  varDatabase->f4 = 1.0;
  memset(&varDatabase->f8[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
    for (iDim = 0; iDim < 24; iDim++) {

   // GET value
  while (!feof(fileid)) {
      /* we expect buffer pointer back if all is well, get out if we don't get it */
        if (buffer != fgets(buffer, 20, fileid))
            break;
        /* strip /n */
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i];}
      // puts(value);
            break;
        }}
        //END get value


      varDatabase->f8[iCentroid + (iDim << 8)] = 1.0;
    }
  }

  fclose(fileid);
}

/*
 * File trailer for loadDatabaseFromFile.c
 *
 * [EOF]
 */
