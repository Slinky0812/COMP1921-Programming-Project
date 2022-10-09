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
	   printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm\n");
	   return 0;
   	}
	/* check for correct number of arguments */
	int argValue = checkArgs(argc, 4);
	/* if only two arguments are given */
	if (argValue == BAD_ARG_COUNT) {
		return EXIT_WRONG_ARG_COUNT;
	}

    /* creates the pgm struct variable, mallocs it, and calls the pgmStruct function */
	pgm *pgmImage = NULL;
	pgmImage = (pgm *) malloc (sizeof(pgm));
	pgmStruct(pgmImage);

	/* calls the readFile function */
	if (readFile(pgmImage, argv[1]) != 0) {
		return EXIT_BAD_INPUT_FILE;
	}

	/* initialises the factor */
	int factor = atoi(argv[2]);

	/* checks factor to ensure validity */	
	if (factor == 0) {
		return miscellaneous("Non-numeric scaling factor");
	} else if (factor < 0) {
		return miscellaneous("Negative scaling factor");
	}

	/* calls the reduce function and checks if any errors were found */
	int rCheck = reduceFileSize(pgmImage, factor, argv[3]);

    if (rCheck != 0) {
		return EXIT_BAD_OUTPUT_FILE;
	} else {
		/* free any memory that has been allocated */
		free(pgmImage->imageData);
		free(pgmImage->commentLine);

		/* returns success code and message */
		printf("REDUCED\n");
		return REDUCED;
	}
}