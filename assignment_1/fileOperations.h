/* definitions used for success or to exit the program */
#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_INPUT_FILE 2
#define EXIT_BAD_OUTPUT_FILE 3

/* definitions for checking certains aspects of the pgm image */
#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128

/* defines the pgm struct used to store the variables needed */
typedef struct pgm {
    unsigned char magic_number[2];
    unsigned short *magic_Number;
    char *commentLine;
    unsigned int width;
    unsigned int height;
    unsigned int maxGray;
    unsigned char **imageData;
    long nImageBytes;
} pgm;

/* function prototypes */
void pgmStruct (pgm *image);
int checkFileForReading (char* filename);
int checkFileForWriting (char *filename, char *commentLine, unsigned char **imageData);
int readFile(pgm *image, char *filename);
int writeFile(pgm *image, char *filename);
int writeBinary(pgm *image, char *filename);
// int b2a (pgm *image, char *filename);
int reduceFileSize(pgm *image, int factor, char *filename);
int tile(pgm *image, int factor, char *filename, char* format);
int placeTile (int row, int col, pgm *tile, pgm *outputImage);