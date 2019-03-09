/// loadDatabaseFromFile.c

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

// only for loadDatabaseFlag variable, maybe just use extern instead?
#include "main.h"



/// WARNING nModelNames limited to 1000 , we need to dynamically size this array to unlimited

   /* int nModelNumber should be the index to the date cell */
 //    double cell_mega [1000] [6144]; // Warning this should be dynamically sized ?



  /*  open the database */
void loadDatabaseFromFile(const char *fileNameDatabase[256],cell_0 *varDatabase, cell_1 *choices)

{
  FILE *fileid;
  int iCentroid;
  int iDim;

// for debug
//  printf("were in loadDatabaseFromFile.c   ");
//  puts(fileNameDatabase);


  /*  open fileNameDatabase in read mode */
  fileid = fopen(fileNameDatabase, "r"); // was cfopen ? can't find any ref to cfopen in C !

 if(fileid == NULL) {
      puts("Error opening database text file");
   }

// number of voiceprint models = nModels
// centroids = 246
// Dims = 24


/// choices->modelNames[x] indexing is easy
/// f5 f6 f7 etc yet in varDatabase->f5 is nasty. not sure how to point to the struct in a loop.

/// make sure this application knows how many voice prints there are nModelNumber!!

  //************************************************************************


char nModels[20];
extern int nModelNumber; // number of models in database


char nCentroids[20];
char nDims[20];
char buffer[20];
char value[20];


/// get the 1st 3 entries in database txt file nModels, nCentroids, mDims

/// nModels
    while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { nModels[i] = buffer[i];}

          nModelNumber = atoi(nModels); // put nModels into int nVoiceprints
            break;
        }}
/// nCentroids
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { nCentroids[i] = buffer[i];}
            break;
        }}
///nDims
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { nDims[i] = buffer[i];}
            break;
        }}



/// LOAD NAMES and VOICEPRINTS from database
//*****************************************************************************************

/*
/// LOOP in data into multidimensional double array , index and 6144 double numbers per person model


for ( int modelCount = 0; modelCount < nModelNumber-1; modelCount++)

{

      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) {choices->modelNames[modelCount][i] = buffer[i];}
        printf("%s \r\n",choices->modelNames[modelCount]);
            break;
        }}

 // values for person 1 in database

 //  memset(&cell_mega[modelCount], 0, 6144U * sizeof(double));  // assign memory for new model

 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

        for (iDim = 0; iDim < 24; iDim++) {

           // GET value
  while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip newline char
        for (int i = 0; i<= len-1; i++) { value[i] = buffer[i]; }
        //END get value

   //puts(value);  // for debug
  char *ptr; // temporary place to read in string
  // string to double
  double finalValue = strtod(value, &ptr);

 // load multidimensional array of data at index modelCount
  cell_mega [modelCount] [iCentroid + (iDim << 8) ] = finalValue;

  break;
        }
        }
      }
  }


} // END nModelNumber loop ( number of people in database

*/






// ugly pointer to strut varDatabase->f5 , f6 , f7 , f8 , f9 etc ...
// WE WILL USE A DATA BASE OF SOME KIND SO JUST REPEAT CODE FOR EACH VOICE FOR NOW !!!!!!!



///VOICE 1

        // FIRST NAME in data base

      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) {choices->modelNames[0][i] = buffer[i];}
            break;
        }}

 // values for person 1 in database

  memset(&varDatabase->f5[0], 0, 6144U * sizeof(double));  // why here ?

 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

        for (iDim = 0; iDim < 24; iDim++) {

           // GET value
  while (!feof(fileid)) {
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
        }
        }
      }
  }

  //********************************************************************
///VOICE 2
  //  2ND NAME IN DATA BASE

      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { choices->modelNames[1][i] = buffer[i];}
            break;
        }}

  // values for person 2 in database
  memset(&varDatabase->f6[0], 0, 6144U * sizeof(double));
  // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

         for (iDim = 0; iDim < 24; iDim++) {

           // GET value
  while (!feof(fileid)) {
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
        }
    }
   }
  }


//********************************************************************************
/// VOICE 3

      // 3RD NAME in data base

      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { choices->modelNames[2][i] = buffer[i];}
            break;
        }}

  // values for person 3 in database
  memset(&varDatabase->f7[0], 0, 6144U * sizeof(double));

 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

        for (iDim = 0; iDim < 24; iDim++) {

           // GET value
  while (!feof(fileid)) {
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
        }
       }
    }
  }

  //*******************************************************************************************
///VOICE 4
       // 4TH NAME in data base

      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0;
        for (int i = 0; i<= len-1; i++) { choices->modelNames[3][i] = buffer[i];}
            break;
        }}

 // values for person 4 in database

memset(&varDatabase->f8[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {

         for (iDim = 0; iDim < 24; iDim++) {

           // GET value
  while (!feof(fileid)) {
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
        }}}}



  //*******************************************************************************************
///VOICE 5
       // 5TH NAME in data base
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip return line
        for (int i = 0; i<= len-1; i++) { choices->modelNames[4][i] = buffer[i];}
            break;
        }}
 // values for person 5 in database
memset(&varDatabase->f9[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
         for (iDim = 0; iDim < 24; iDim++) {
           // GET value
  while (!feof(fileid)) {
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
  varDatabase->f9[iCentroid + (iDim << 8) ] = finalValue; //

  break;
        }}}}



  //*******************************************************************************************
///VOICE 6
       // 5TH NAME in data base
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip return line
        for (int i = 0; i<= len-1; i++) { choices->modelNames[5][i] = buffer[i];}
            break;
        }}
 // values for person 5 in database
memset(&varDatabase->f10[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
         for (iDim = 0; iDim < 24; iDim++) {
           // GET value
  while (!feof(fileid)) {
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
  varDatabase->f10[iCentroid + (iDim << 8) ] = finalValue; //

  break;
        }}}}


  //*******************************************************************************************
///VOICE 7
       // 5TH NAME in data base
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip return line
        for (int i = 0; i<= len-1; i++) { choices->modelNames[6][i] = buffer[i];}
            break;
        }}
 // values for person 5 in database
memset(&varDatabase->f11[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
         for (iDim = 0; iDim < 24; iDim++) {
           // GET value
  while (!feof(fileid)) {
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
  varDatabase->f11[iCentroid + (iDim << 8) ] = finalValue; //
  break;
        }}}}



  //*******************************************************************************************
///VOICE 8
       // 5TH NAME in data base
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip return line
        for (int i = 0; i<= len-1; i++) { choices->modelNames[7][i] = buffer[i];}
            break;
        }}
 // values for person 5 in database
memset(&varDatabase->f12[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
         for (iDim = 0; iDim < 24; iDim++) {
           // GET value
  while (!feof(fileid)) {
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
  varDatabase->f12[iCentroid + (iDim << 8) ] = finalValue; //
  break;
        }}}}


  //*******************************************************************************************
///VOICE 9
       // 5TH NAME in data base
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip return line
        for (int i = 0; i<= len-1; i++) { choices->modelNames[8][i] = buffer[i];}
            break;
        }}
 // values for person 5 in database
memset(&varDatabase->f13[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
         for (iDim = 0; iDim < 24; iDim++) {
           // GET value
  while (!feof(fileid)) {
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
  varDatabase->f13[iCentroid + (iDim << 8) ] = finalValue; //
  break;
        }}}}



  //*******************************************************************************************
///VOICE 10
       // 5TH NAME in data base
      while (!feof(fileid)) {
        if (buffer != fgets(buffer, 20, fileid))
            break;
        int len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = 0; // strip return line
        for (int i = 0; i<= len-1; i++) { choices->modelNames[9][i] = buffer[i];}
            break;
        }}
 // values for person 5 in database
memset(&varDatabase->f14[0], 0, 6144U * sizeof(double));


 // get the values in 256 loop
  for (iCentroid = 0; iCentroid < 256; iCentroid++) {
         for (iDim = 0; iDim < 24; iDim++) {
           // GET value
  while (!feof(fileid)) {
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
  varDatabase->f14[iCentroid + (iDim << 8) ] = finalValue; //
  break;
        }}}}





  /// END keep this above until were sure alternative multi-dimensional database array is fully working :)


   if ( loadDatabaseFlag < 2 )
 {
    printf("\r\n database file load success.. \r\n");
    printf("\r\n number voiceprints in database... %s \r\n", nModels);
    printf("\r\n nCentroids... %s \r\n",nCentroids);
    printf("\r\n nDims... %s \r\n",nDims);

    printf("\r\n names in database.. \r\n \r\n");


 for ( int nms =0; nms < nModelNumber; nms++ )
 {
 printf("%s \r\n",choices->modelNames[nms]);
 }
 }



  fclose(fileid);  ///finished with open database text file
}


/*
 * File trailer for loadDatabaseFromFile.c
 *
 * [EOF]
 */
