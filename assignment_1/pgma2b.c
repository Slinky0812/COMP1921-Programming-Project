/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>

/* all other header files needed to run the functions */
#include "errorCheck.h"
#include "fileOperations.h"
#include "pgmOperations.h"

int main (int argc, char **argv) {
	/* if only one argument is given */
	if (argc == 1) {
	   printf("Usage: ./pgma2b inputImage.pgm outputImage.pgm\n");
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

	/* checks the last value of the magic number to see if it is an ASCII image */
	if (pgmImage->magic_number[1] != '2') {
		/* returns error function */
		badMagicNum(argv[1]);
		exit(3);
	}

	/* calls the writeBinary function */
	writeBinary(pgmImage, argv[2]);

	/* free any memory that has been allocated */
	free(pgmImage->imageData);
	free(pgmImage->commentLine);

	/* prints out the success message and returns success code */
	printf("CONVERTED\n");
    return CONVERTED;
}