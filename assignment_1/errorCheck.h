/* definitions for error codes */
#define BAD_ARG_COUNT 1
#define BAD_FILE_NAME 2
#define BAD_MAGIC_NUM 3
#define BAD_COMMENT_LINE 4
#define BAD_DIMENSIONS 5
#define BAD_MAX_GRAY_VAL 6
#define MALLOC_FAIL 7
#define BAD_DATA 8
#define OUTPUT_FAIL 9
#define BAD_LAYOUT 10
#define MISCELLANEOUS 100

/* function prototypes */
int checkArgs (int numOfArgs, int correctNum);
int badFileName (char* filename);
int badMagicNum (char* filename);
int badCommentLine (char* filename);
int badDimensions (char* filename);
int badMaxGray (char* filename);
int mallocFail ();
int badData (char* filename);
int outputFail (char* filename);
int badLayout ();
int miscellaneous (char *text);
