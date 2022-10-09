/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>

/* all other header files needed to run the functions */
#include "errorCheck.h"
#include "fileOperations.h"
#include "pgmEcho.h"
#include "pgmOperations.h"

int main (int argc, char **argv) {
	/* if only one argument is given */
	if (argc == 1) {
	   printf("Usage: ./pgmEcho inputImage.pgm outputImage.pgm\n");
	   return 0;
   	}
	/* check for correct number of arguments */
	int argValue = checkArgs(argc, 3);
	/* if only two arguments are given */
	if (argValue == BAD_ARG_COUNT) {
		return EXIT_WRONG_ARG_COUNT;
	}

	/* creates the pgm struct variable, mallocs it, and calls the pgmStruct function */
	pgm *pgmImage = NULL;
	pgmImage = (pgm*) malloc (sizeof(pgm));
	pgmStruct(pgmImage);

	/* calls the readFile function */
	if (readFile(pgmImage, argv[1]) != 0) {
		return EXIT_BAD_INPUT_FILE;
	}
	
	/* variable to check if file has been written to correctly */
	int wCheck = 0;

	/* the image is in ASCII */
	if (pgmImage -> magic_number[1] == '2') {
		wCheck = writeFile(pgmImage, argv[2]);
	/* the image is in binary */
 	} else if (pgmImage -> magic_number[1] == '5') {
 		wCheck = writeBinary(pgmImage, argv[2]);
 	}

	/* checks if any errors were found when writing the file */
	if (wCheck != 0) {
		return EXIT_BAD_OUTPUT_FILE;
	} else {
		/* free any memory that has been allocated */
		free(pgmImage->imageData);
		free(pgmImage->commentLine);

		/* prints success message and success code */
		printf("ECHOED\n");
		return ECHOED;
	}
}
