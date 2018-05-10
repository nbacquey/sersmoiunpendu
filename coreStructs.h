#define NB_STEPS 11

#define OUTPUT_SIZE 512
#define MAXIMUM_WORD_SIZE 128

#ifndef STRUCT_DEF
#define STRUCT_DEF
typedef struct  {
  unsigned int currentStep;
  unsigned int wordSize;
  char* wrongLetters;
  char* currentWord;
  char* fullWord
} gallows;

#endif

gallows* buildGallows(char* initWord);

char* gallowsToString(gallows* g);