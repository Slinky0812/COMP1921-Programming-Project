/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>

/* all other header files needed to run the functions */
#include "pgmEcho.h"
#include "pgmOperations.h"
#include "fileOperations.h"
#include "errorCheck.h"
#include "pgmComp.h"


/* programme given wrong # of arguments */
int checkArgs (int numOfArgs, int correctNumOfArgs) {
   /* return error if num of args is not correct */
   if (numOfArgs != correctNumOfArgs) {
      printf("ERROR: Bad Argument Count\n");
      return BAD_ARG_COUNT;
   /* correct arg count */
   } else {
	   return 0;
   }
}

/* programme failed to open a file stream */
int badFileName (char* filename) {
   printf("ERROR: Bad File Name (%s)\n", filename);
   return BAD_FILE_NAME;
}

/* programme failed on a magic number */
int badMagicNum (char* filename) {
   printf("ERROR: Bad Magic Number (%s)\n", filename);
   return BAD_MAGIC_NUM;
}

/* programme failed on comment line */
int badCommentLine (char* filename) {
   printf ("ERROR: Bad Comment Line (%s)\n", filename);
   return BAD_COMMENT_LINE;
}

/* programme failed on image dimensions */
int badDimensions (char* filename) {
   printf ("ERROR: Bad Dimensions (%s)\n", filename);
   return BAD_DIMENSIONS;
}

/* programme failed on max gray value */
int badMaxGray (char* filename) {
   printf ("ERROR: Bad Max Gray Value (%s)\n", filename);
   return BAD_MAX_GRAY_VAL;
}

/* malloc failed for image allocation */
int mallocFail () {
   printf("ERROR: Image Malloc Failed\n");
   return MALLOC_FAIL;
}

/* programme failed when reading in data */
int badData (char* filename) {
   printf("ERROR: Bad Data (%s)\n", filename);
   return BAD_DATA;
}

/* programme failed during output */
int outputFail (char* filename) {
   printf("ERROR: Output Failed (%s)\n", filename);
   return OUTPUT_FAIL;
}

/* layout file for assembly went wrong */
int badLayout () {
   printf("ERROR: Bad Layout\n");
   return BAD_LAYOUT;
}

/* any other error that is detected */
int miscellaneous (char *text) {
   printf ("ERROR: Miscellaneous (%s)\n", text);
   return MISCELLANEOUS;
}
