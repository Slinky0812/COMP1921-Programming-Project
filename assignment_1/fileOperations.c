/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>
/* library for string routines */
#include <string.h>
#include <ctype.h>

/* all other header files needed to run the functions */
#include "pgmEcho.h"
#include "pgmOperations.h"
#include "fileOperations.h"
#include "errorCheck.h"
#include "pgmComp.h"

void pgmStruct(pgm *image) {
	/* assigns the values of the pgm struct into our pgmImage variable */
	image->magic_number[0] = '0';
	image->magic_number[1] = '0';
	image->magic_Number = NULL;
	image->commentLine = NULL;
	image->width = 0;
	image->height = 0;
	image->maxGray = 255;
	image->imageData = NULL;
}

int checkFileForReading(char *filename) {	
	/* checks the last 4 characters to see if it is a .pgm file*/
	const char *extension = ".pgm";
	int length = strlen(filename);
	const char *filetype = &filename[length - 4];
	int check = strcmp(extension, filetype);
	/* return error string and error code */
	if (check != 0)	{
		badFileName(filename);
		exit(BAD_FILE_NAME);
	}

	/* opens the file */
	FILE *file = fopen(filename, "r");
	/* if null, then return error */
	if (file == NULL) {
		badFileName(filename);
		exit(BAD_FILE_NAME);
	/* file opening successful */
	} else {
		/* closes file */
		fclose(file);
		return EXIT_NO_ERRORS;
	}
}

int checkFileForWriting(char *filename, char *commentLine, unsigned char **imageData) {
	/* checks the last 4 characters to see if it is a .pgm file*/
	const char *extension = ".pgm";
	int length = strlen(filename);
	const char *filetype = &filename[length - 4];
	int check = strcmp(extension, filetype);
	/* return error string and error code */
	if (check != 0) {
		badFileName(filename);
		exit(BAD_FILE_NAME);
	}

	/* opens the file */
	FILE *file = fopen(filename, "w");
	/* if null, then return error */
	if (file == NULL) {
		/* free memory */
		free(commentLine);
		free(imageData);

		badFileName(filename);
		exit(BAD_FILE_NAME);
	/* file opening successful */
	} else {
		/*closes file*/
		fclose(file);
		return EXIT_NO_ERRORS;
	}
}

int readFile(pgm *image, char *filename) {
	/* opens a file for reading and checks if it isn't NULL */
	checkFileForReading(filename);
	FILE *inputFile = fopen(filename, "r");

	/* read in the magic number */
	image->magic_number[0] = getc(inputFile);
	image->magic_number[1] = getc(inputFile);

	image->magic_Number = (unsigned short *)(image->magic_number);

	/* checks if magic_Number has been assigned correctly */
	magicNumberSanCheck(image->magic_Number, inputFile, filename);

	/* scan whitespace if present */
	int scanCount = fscanf(inputFile, " ");

	/* checks for any comment lines*/
	checkCommentLine(filename, image->commentLine, inputFile);

	/* read in width, height, grays (must read exactly three values) */
	scanCount = fscanf(inputFile, " %u %u %u ", &(image->width), &(image->height), &(image->maxGray));

	/* whitespace to skip blanks */
	graySanCheck(scanCount, image->width, image->height, image->maxGray, image->commentLine, inputFile, filename);

	/* mallocing image data */
	image->nImageBytes = (image->width) * (image->height) * sizeof(unsigned char *);
	image->imageData = (unsigned char **) malloc (image->height * sizeof(unsigned char *));
	/* checks if image->imageData has been malloced correctly */
	memAllocSanCheck(image->imageData, image->commentLine, inputFile);

	/* checks if each sub-array in the 2D array has been malloced correctly */
	for (int i = 0; i < image->height; i++) {
		image->imageData[i] = (unsigned char *) malloc (image->width * sizeof(unsigned char));
		memAllocSanCheck(image->imageData[i], image->commentLine, inputFile);
	}

	/* the file is in binary */
	if (image->magic_number[1] == '5') {
		readValueForBinary(image->width, image->height, image->imageData, inputFile, filename, image->commentLine);
	/* the file is in ASCII */
	} else if (image->magic_number[1] == '2') {
		readValueForASCII(image->imageData, inputFile, image->commentLine, filename, image->height, image->width);
	}

	/* closes the file */
	fclose(inputFile);

	/* return success code */
	return EXIT_NO_ERRORS;
}

int writeFile(pgm *image, char *filename) {
	/* open a file for writing and checks it isn't NULL*/
	checkFileForWriting(filename, image->commentLine, image->imageData);
	FILE *outputFile = fopen(filename, "w");

	/* write magic number, size & gray value */
	size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", (image->width), (image->height), (image->maxGray));

	/* checks the size of the dimensions of the output file */
	checkDimensions(nBytesWritten, image->commentLine, image->imageData, filename);

	/* writes the data efficiently */
	writeValueASCII(image->imageData, image->nImageBytes, image->width, image->height, nBytesWritten, outputFile, image->commentLine, filename);

	/* close the file*/
	fclose(outputFile);

	/* return success code */
	return EXIT_NO_ERRORS;
}

int writeBinary(pgm *image, char *filename) {
	/* open a file for writing and checks it isn't NULL */
	checkFileForWriting(filename, image->commentLine, image->imageData);
	FILE *outputFile = fopen(filename, "w");

	/* writes the header lines (magic number, width, height, and max gray) to the binary file */
	fprintf(outputFile, "P5\n%d %d\n%d\n", (image->width), (image->height), (image->maxGray));

	/* writes the data efficiently */
	writeValueBinary(image->height, image->width, image->imageData, outputFile, image->commentLine, filename);

	/* closes the file */
	fclose(outputFile);

	/* return success code */
	return EXIT_NO_ERRORS;
}

int reduceFileSize(pgm *image, int factor, char *filename) {
	/* open a file for writing and checks it isn't NULL*/
	checkFileForWriting(filename, image->commentLine, image->imageData);
	FILE *outputFile = fopen(filename, "w");

	/* calculates the new width and height */
	int newWidth = ((image->width) + factor - 1) / factor;
	int newHeight = ((image->height) + factor - 1) / factor;

	/* creating a new array called pixels which will store the reduced image data */
	long newImageBytes = newHeight * newWidth * sizeof(unsigned char *);
	unsigned char **pixels = (unsigned char **)malloc(newHeight * sizeof(unsigned char *));
	/* checks if pixels has been malloced correctly */
	memAllocSanCheck(pixels, image->commentLine, outputFile);

	/* checks if each sub-array in the 2D array has been malloced correctly */
	for (int i = 0; i < newHeight; i++) {
		pixels[i] = (unsigned char *)malloc(newWidth * sizeof(unsigned char));
		memAllocSanCheck(pixels[i], image->commentLine, outputFile);
	}

	/* write magic number, size & gray value */
	size_t newBytesWritten = fprintf(outputFile, "P%c\n%d %d\n%d\n", (image->magic_number[1]), (newWidth), (newHeight), (image->maxGray));

	/* checks the size of the dimensions of the output file */
	checkDimensions(newBytesWritten, image->commentLine, image->imageData, filename);

	/* iterates through each row of the pixels array */
	for (int row = 0; row < newHeight; row++) {
		/* iterates through each column of pixels array */
		for (int col = 0; col < newWidth; col++) {
			/* writes new image data to pixels */
			pixels[row][col] = image->imageData[row * factor][col * factor];
		}
	}

	/* calls the correct write function depending on whether the file is ASCII or binary */
	if ((image->magic_number[1]) == '5') {
		writeValueBinary(newHeight, newWidth, pixels, outputFile, image->commentLine, filename);

		fclose(outputFile);

	} else if ((image->magic_number[1]) == '2') {
		writeValueASCII(pixels, newImageBytes, newWidth, newHeight, newBytesWritten, outputFile, image->commentLine, filename);
	}
	/* return success code */
	return EXIT_NO_ERRORS;
}

int tile(pgm *image, int factor, char *filename, char* format) {
	/* calculate format string */
	char* formatString = malloc(sizeof(char) * strlen(format));
	/* copies a character (0) to all the characters in formatString */
	memset(formatString, 0, sizeof(char) * strlen(format));

	/* find indices of <row> and <column> and check if they're not null */
	char* rowPointer = strstr(format, "<row>");
	char* colPointer = strstr(format, "<column>");
	if (rowPointer == 0 || colPointer == 0) {
		miscellaneous("Bad Template");
		exit(MISCELLANEOUS);
	}
	/* finds where <row> and <column> starts in format */
	int rowIndex = rowPointer - format;
	int colIndex = colPointer - format;

	/* copies first part of string and replace <row> with %i */
	memcpy(formatString, format, rowIndex + 1);
	formatString[rowIndex] = '%';
	formatString[rowIndex + 1] = 'i';

	/* copies second part of string, replace <column> with %i */
	memcpy(formatString + rowIndex + 2, format + rowIndex + 5, colIndex - (rowIndex + 5));
	formatString[rowIndex + 2 + colIndex - (rowIndex + 5)] = '%';
	formatString[rowIndex + 2 + colIndex - (rowIndex + 5) + 1] = 'i';

	/* copies the rest of the string after <column> */
	memcpy(formatString + rowIndex + 2 + colIndex - (rowIndex + 5) + 2, format + colIndex + 8, strlen(format) - (colIndex + 8));

	/* calculate the new width and height of the tiles */
	int newWidth = (image->width) / factor;
	int newHeight = (image->height) / factor;

	/* counter for the height */
	int xCount = 0;
	/* loops through the height of the original image */
	for (int x = 0; x < image->height; x+=newHeight) {

		/* counter for the width */
		int yCount = 0;
		/* loops through the width of the original image */
		for (int y = 0; y < image->width; y+=newWidth) {

			/* finds the name of the file and stores it in 'file' */
			int ogLength = strlen(filename);
			int newLength = ogLength - 4;
			char file[256];
			memcpy(file, filename, newLength);

			/* writes the name of the file, as well as the row and column to buffer */
			char buffer[256];
			int sizeLength = sizeof(buffer);
			snprintf(buffer, sizeLength, formatString, (xCount), (yCount));

			/* open a file for writing and checks it isn't NULL*/
			checkFileForWriting(buffer, image->commentLine, image->imageData);
			FILE *outputFile = fopen(buffer, "w");

			/* creating a new array called pixels which will store the new image data */
			long newImageBytes = newHeight * newWidth * sizeof(unsigned char *);
			unsigned char **pixels = (unsigned char **) malloc (newHeight * sizeof(unsigned char *));
			/* checks if pixels has been malloced correctly */
			memAllocSanCheck(pixels, image->commentLine, outputFile);

			/* checks if each sub-array in the 2D array has been malloced correctly */
			for (int i = 0; i < newHeight; i++) {
				pixels[i] = (unsigned char *) malloc (newWidth * sizeof(unsigned char));
				memAllocSanCheck(pixels[i], image->commentLine, outputFile);
			}


			/* write magic number, size & gray value */
			size_t newBytesWritten = fprintf(outputFile, "P%C\n%d %d\n%d\n", (image->magic_number[1]), (newWidth), (newHeight), (image->maxGray));

			/* checks the size of the dimensions of the output file */
			checkDimensions(newBytesWritten, image->commentLine, image->imageData, buffer);

			/* iterates through each row of the pixels array */
			for (int row = 0; row < newHeight; row++) {
				/* iterates through each column of pixels array */
				for (int col = 0; col < newWidth; col++) {
					/* writes new image data to pixels */
					pixels[row][col] = image->imageData[row + x][col + y];
				}
			}

			/* calls the correct write function depending on whether the file is ASCII or binary */
			if (image->magic_number[1] == '2') {
				writeValueASCII(pixels, newImageBytes, newWidth, newHeight, newBytesWritten, outputFile, image->commentLine, buffer);
			} else if (image->magic_number[1] == '5') {
				writeValueBinary(newHeight, newWidth, pixels, outputFile, image->commentLine, buffer);
			}

			/* increment the width counter */
			yCount += 1;
		}

		/* increment the height counter */
		xCount += 1;
		/* close the file */
	}

	/* return success code */
	return EXIT_NO_ERRORS;
}

int placeTile (int row, int col, pgm *tile, pgm *outputImage) {

	/* set k to the row of the output image */
	int k = row;
	/* increments through each row of the tile */
	for (int i = 0; i < tile->height; i++) {
		/* set l to the col of the output image */
		int l = col;
		/* increments through each row of the tile */
		for (int j = 0; j < tile->width; j++) {
			/* sets the output image's imageData equal to the tile's imageData */
			outputImage->imageData[k+i][l+j] = tile->imageData[i][j];
		}
	}

	/* return success code */
	return EXIT_NO_ERRORS;
}