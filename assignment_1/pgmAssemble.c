/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>
#include <string.h>

/* all other header files needed to run the functions */
#include "errorCheck.h"
#include "fileOperations.h"
#include "pgmOperations.h"

int main(int argc, char **argv) {
	/* if only one argument is given */
	if (argc == 1) {
		printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+\n");
		return 0;
	/* checks for at least 7 arguments given */
	} else if (argc <= 6) {
		printf("ERROR: Bad Argument Count\n");
      	return BAD_ARG_COUNT;
	}

	/* initialises the width */
	int width = atoi(argv[2]);
	if (width == 0) {
		return badLayout();
	} else if (width < 0) {
		return badLayout();
	}

	/* initialises the height */
	int height = atoi(argv[3]);
	if (height == 0) {
		return badLayout();
	} else if (height < 0) {
		return badLayout();
	}

	/* creates a pgm struct variable for the first tile, mallocs it and calls the pgmStruct function */
	pgm *firstImage = NULL;
	firstImage = (pgm *) malloc (sizeof(pgm));
	pgmStruct(firstImage);
	readFile(firstImage, argv[6]);

	/* creates a pgm struct variable for the total output image, mallocs it, and calls the pgmStruct function */
	pgm *outputImage = NULL;
	outputImage = (pgm *)malloc(sizeof(pgm));
	pgmStruct(outputImage);

	/* sets the magic number of the output image equal to that of the first image */
	outputImage->magic_number[0] = firstImage->magic_number[0];
	outputImage->magic_number[1] = firstImage->magic_number[1];
	/* sets the width and height of the outputImage to the width and height given by the user*/
	outputImage->width = width;
	outputImage->height = height;

	/* creates a general pgm struct used for each tile */
	pgm *tile = NULL;
	tile = (pgm *) malloc (sizeof(pgm));
	pgmStruct(tile);

	/* open a file for writing and checks it isn't NULL*/
	checkFileForWriting(argv[1], tile->commentLine, tile->imageData);
	FILE *outputFile = fopen(argv[1], "w");

	/* allocate the data pointer */
	outputImage->nImageBytes = outputImage->height * outputImage->width * sizeof(unsigned char *);
	outputImage->imageData = (unsigned char **) malloc (outputImage->height * sizeof(unsigned char *));
	/* checks if the imageData has been malloced correctly */
	memAllocSanCheck(outputImage->imageData, outputImage->commentLine, outputFile);

	/* checks if each sub-array in the 2D array has been malloced correctly */
	for (int i = 0; i < outputImage->height; i++) {
		outputImage->imageData[i] = (unsigned char *) malloc (outputImage->width * sizeof(unsigned char));
		memAllocSanCheck(outputImage->imageData[i], outputImage->commentLine, outputFile);
	}

	/* row and col variables for the tiles to start at */
	int row, col;

	/* counter to see what argument we are looking at */
	int count = 4;
	/* runs until there are no more arguments */
	while (argv[count] != NULL) {
		/* runs different cases depending on the result of count % 3 */
		switch (count % 3) {
			/* argument is the tile's filename */
			case 0:
				/* calls the readFile function */
				readFile(tile, argv[count]);

				/* calls the placeTile function*/
				placeTile(row, col, tile, outputImage);

				break;

			/* argument is the row at which the image should start */
			case 1:
				/* initialises the row */
				row = atoi(argv[count]);
				if (row < 0) {
					return badLayout();
				}
				break;

			/* argument is the column at which the image should start */
			case 2:
				/* intialises the height */
				col = atoi(argv[count]);
				if (col < 0) {
					return badLayout();
				}
				break;
			/* for any other value, just break */
			default:
				break;
		}
	/* increment count */
	count += 1;
	}

	/* variable to check if file has been written to correctly */
	int check = 0;
	
	/* calls the correct write function depending on whether the file is ASCII or binary */
	if (outputImage->magic_number[1] == '2') {
		check = writeFile(outputImage, argv[1]);
	} else if (outputImage->magic_number[1] == '5') {
		check = writeBinary(outputImage, argv[1]);
	}

	/* checks if any errors were found when writing to the file */
	if (check != 0) {
		return EXIT_BAD_OUTPUT_FILE;
	} else {
		/* return success message and success code */
		printf("ASSEMBLED\n");
		return ASSEMBLED;
	}
}