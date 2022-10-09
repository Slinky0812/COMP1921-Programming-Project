/* library for I/O routines */
#include <stdio.h>
/* library for memory routines */
#include <stdlib.h>
#include <string.h>

/* all other header files needed to run the functions */
#include "pgmOperations.h"
#include "fileOperations.h"
#include "errorCheck.h"


/* sanity check on the magic number */
int magicNumberSanCheck(unsigned short *magic_number, FILE *filename, char* input) {
	/* failed magic number check */
	if (*magic_number != MAGIC_NUMBER_ASCII_PGM && *magic_number != MAGIC_NUMBER_RAW_PGM) {
		/* close the file */
		fclose(filename);

		/* return error function */
		badMagicNum(input);
		exit(BAD_MAGIC_NUM);
	}
	/* magic number successful */
	return EXIT_NO_ERRORS; 
}


/* check for a comment line */
int checkCommentLine(char* input, char *commentLine, FILE *filename) {
	char nextChar = fgetc(filename);

	/* comment line */
	if (nextChar == '#') {
		/* allocate buffer */
		commentLine = (char *) malloc (MAX_COMMENT_LINE_LENGTH);

		/* fgets() reads a line and stores it into a char pointer */
		char *commentString = fgets(commentLine, MAX_COMMENT_LINE_LENGTH + 2, filename);

		/* NULL comment read */
		if (commentString == NULL || strlen(commentString) > MAX_COMMENT_LINE_LENGTH) {
			/* free memory */
			free(commentLine);
			
			/* close file */
			fclose(filename);
			
			/* return error function */
            badCommentLine(input);
			exit(BAD_COMMENT_LINE);
		}

	/* not a comment line */
	} else {
		/* put character back */
		ungetc(nextChar, filename);
	}

	return EXIT_NO_ERRORS;
}

/* sanity checks on size & grays */
int graySanCheck (int scanCount, unsigned int width, unsigned int height, unsigned int maxGray, char *commentLine, FILE *filename, char* input) {
	/* failed size sanity check */
	if ( (scanCount != 3) || (width < MIN_IMAGE_DIMENSION) || (width >= MAX_IMAGE_DIMENSION) || (height < MIN_IMAGE_DIMENSION) || (height >= MAX_IMAGE_DIMENSION) || (maxGray != 255) ) {

		/* free up the memory */
		free(commentLine);
		
		/* close file pointer */
		fclose(filename);

		/* return correct error function depending on what failed */
		if ( (scanCount != 3) || (width < MIN_IMAGE_DIMENSION) || (width >= MAX_IMAGE_DIMENSION) || (height < MIN_IMAGE_DIMENSION) || (height >= MAX_IMAGE_DIMENSION) ) {
			badDimensions(input);
			exit(BAD_DIMENSIONS);
		} else if (maxGray != 255) {
			badMaxGray(input);
			exit(BAD_MAX_GRAY_VAL);
		}
	
	}
	/* size check successful */
	return EXIT_NO_ERRORS;
}

/* sanity check for memory allocation */
int memAllocSanCheck (void* imageData, char *commentLine, FILE *filename) {
	/* malloc failed */
	if (imageData == NULL) {
		/* free up memory */
		free(commentLine);

		/* close file pointer */
		fclose(filename);

		/* return error function */
		mallocFail();
		exit(MALLOC_FAIL);
	/* malloc successful */
	} else {
		return EXIT_NO_ERRORS;
	}
}

int readValueForASCII (unsigned char **imageData, FILE *filename, char *commentLine, char* input, unsigned int height, unsigned int width) {
	/* loops through each row of the imageData */
	for (int row = 0; row < height; row++) {
		/* loops through each column of the imageData*/
		for (int col = 0; col < width; col++) {
			/* read next value */
	        int grayValue = -1;
			int scanCount = fscanf(filename, " %u", &grayValue);
			//printf("sc = %i\n", scanCount);

			/* fscanf failed */
        	if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255)) {
            	/* free memory */
            	free(commentLine);
            	free(imageData);

            	/* close file */
            	fclose(filename);

            	/* return error function */
            	badData(input);
				exit(BAD_DATA);
		
			}

			/* set the pixel value */
			imageData[row][col] = (unsigned char) grayValue;
		}
	}

	//Runs the same code one more time to check there isn't any more data than there is supposed to be
	int grayValue = -1;
	int scanCount = fscanf(filename, " %u", &grayValue);
	if (scanCount != -1) {
		free(commentLine);
		free(imageData);

		badData(input);
		exit(BAD_DATA);
	}

	/* reading successful */
	return EXIT_NO_ERRORS;
}

int readValueForBinary (unsigned int width, unsigned int height, unsigned char **imageData, FILE *inputFile, char *filename, char *commentLine) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int rCheck = fread(&imageData[i][j], sizeof(unsigned char), 1, inputFile);
			
			/* checks if every byte of imageData is read successfully */
			if (rCheck != 1) {
				free(imageData);
				free(commentLine);

				/* return error function */
				badData(filename);
				exit(BAD_DATA);
			}
		}
	}

	/* checks for more data by checking last piece of data and comparing it to what it should be (EOF) */
	if (fgetc(inputFile) != EOF) {
		free(imageData);
		free(commentLine);

		/* return error function */
		badData(filename);
		exit(BAD_DATA);
	}

	/* reading successful */
	return EXIT_NO_ERRORS;
}

/* check that dimensions wrote correctly */
int checkDimensions (size_t nBytesWritten, char *commentLine, unsigned char **imageData, char* output) {
	
	/* dimensional write failed */
    if (nBytesWritten < 0) {
        /* free memory */
        free(commentLine);
        free(imageData);

		/* return error function */
        badDimensions(output);
		exit(BAD_DIMENSIONS);
	}
	
	/* dimensional write successful*/
	return EXIT_NO_ERRORS;
}

int writeValueASCII (unsigned char **imageData, long nImageBytes, unsigned int width, unsigned int height, size_t nBytesWritten, FILE *filename, char *commentLine, char* output) {
	/* iterates through each row of the data */
	for (int row = 0; row < height; row++) {
		/* iterates through each column of the data*/
		for (int col = 0; col < width; col++) {

	        /* write the entry & whitespace */
    	    nBytesWritten = fprintf(filename, "%d%c", imageData[row][col],' ');

			/* data write failed */
        	if (nBytesWritten < 0) {
            	/* free memory */
	            free(commentLine);
    	        free(imageData);

				/* return error function */
				badFileName(output);
				exit(BAD_FILE_NAME);
			}
			
		}
		/* prints new line */
		nBytesWritten = fprintf(filename, "%c", '\n');
	}
	//writing successful
	return EXIT_NO_ERRORS;
}

int writeValueBinary (unsigned int height, unsigned int width, unsigned char **imageData, FILE *outputFile, char *commentLine, char* output) {

	/* iterates through each row of the imageData */
	for (int row = 0; row < height; row++) {
		/* iterates through each column of the imageData */
		for (int col = 0; col < width; col++) {
			/* writes the image data into the binary file */
			int fCheck = fwrite(&imageData[row][col], sizeof(unsigned char), 1, outputFile);

			/* checks if the image data has been written */
			if (fCheck != 1) {
				/* free memory */
				free(commentLine);
				free(imageData);

				/* close the file*/
				fclose(outputFile);

				/* call error function and exit the program*/
				badFileName(output);
				exit(BAD_FILE_NAME);
			}

		}
	}

	return EXIT_NO_ERRORS;
}