/* definitions of success codes for different programs */
#define ECHOED 0
#define IDENTICAL 0
#define DIFFERENT 0
#define CONVERTED 0
#define REDUCED 0
#define TILED 0
#define ASSEMBLED 0

/* function prototypes */
int magicNumberSanCheck(unsigned short *magic_number, FILE *filename, char* input);
int checkCommentLine(char* input, char *commentLine, FILE *filename);
int graySanCheck (int scanCount, unsigned int width, unsigned int height, unsigned int maxGray, char *commentLine, FILE *filename, char* input);
int memAllocSanCheck (void *imageData, char *commentLine, FILE *filename);
int readValueForASCII (unsigned char **imageData, FILE *filename, char *commentLine, char* input, unsigned int height, unsigned int width);
int readValueForBinary (unsigned int width, unsigned int height, unsigned char **imageData, FILE *inputFile, char *filename, char *commentLine);
int checkDimensions (size_t nBytesWritten, char *commentLine, unsigned char **imageData, char* output);
int writeValueASCII (unsigned char **imageData, long nImageBytes, unsigned int width,  unsigned int height, size_t nBytesWritten, FILE *filename, char *commentLine, char* output);
int writeValueBinary (unsigned int height, unsigned int width, unsigned char **imageData, FILE *outputFile, char *commentLine, char* output);