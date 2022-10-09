/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>
/* library for string methods */
#include <string.h>

/* all other header files needed to run the functions */
#include "pgmOperations.h"
#include "fileOperations.h"
#include "errorCheck.h"
#include "pgmComp.h"

int main (int argc, char **argv) {
	/* if only one argument is given */
	if (argc == 1) {
	   printf("Usage: ./pgmComp inputImage.pgm inputImage.pgm\n");
	   return 0;
   	}
	/* check for correct number of arguments */
	int argValue = checkArgs(argc, 3);
	/* if only two arguments are given */
	if (argValue == BAD_ARG_COUNT) {
		return EXIT_WRONG_ARG_COUNT;
	}
	/* creates the first pgm struct variable, mallocs it, and calls the pgmStruct function */
    pgm *image1 = NULL;
    image1 = (pgm*) malloc (sizeof(pgm));
	pgmStruct(image1);

	/* calls the readFile function */
	if (readFile(image1, argv[1]) != 0) {
		return EXIT_BAD_INPUT_FILE;
	}

	/* creates the second pgm struct variable, mallocs it, and calls the pgmStruct function */
    pgm *image2 = NULL;
    image2 = (pgm*) malloc (sizeof(pgm));
	pgmStruct(image2);

	/* calls the readFile function */
	if (readFile(image2, argv[2]) != 0) {
		return EXIT_BAD_INPUT_FILE;
	}

	/* runs the compare function */
	if (pgmCompare(image1, image2) == 0) {
		/* free any memory that has been allocated */
		free(image1->imageData);
		free(image1->commentLine);
		free(image2->imageData);
		free(image2->commentLine);

		/* all parts of the image checked and are the same, therefore can return identical message and exit code */
		printf("IDENTICAL\n");
		return IDENTICAL;
	} else {
		/* free any memory that has been allocated */
		free(image1->imageData);
		free(image1->commentLine);
		free(image2->imageData);
		free(image2->commentLine);

		/* one or more parts of the image are different, therefore return different message and exit code */
		printf("DIFFERENT\n");
		return DIFFERENT;
	}
}

int pgmCompare(pgm *image1, pgm *image2) {
	/* counter that increments when a part of image1 is not the same as image2 */
	int count = 0;

	/* checks width */
	if (image1->width != image2->width) {
		count += 1;
	}

	/* checks height*/
	if (image1->height != image2->height) {
		count += 1;
	}

	/* checks maxGray */
	if (image1->maxGray != image2->maxGray) {
		count += 1;
	}

	/* looping through the rows of the imageData */
	for (int i = 0; i < image1->height; i++) {
		/* looping throught the columns of the imageData */
		for (int j = 0; j < image1->width; j++) {
			/* checks if they're not the same */
			if (image1->imageData[i][j] != image2->imageData[i][j]) {
				count += 1;
			}
		}
	}

	/* checks if any part of the images were different through the count variable being incremented if any part wasn't the same */
	if (count == 0) {
		return EXIT_NO_ERRORS;
	} else {
		return EXIT_FAILURE;
	}
}
