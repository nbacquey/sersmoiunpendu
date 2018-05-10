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
  char* fullWord;
  int status;
} gallows;

#endif

gallows* buildGallows(char* initWord);
int tryLetter(gallows* g, char newC); //return 0 for right letter, 1 for wrong letter, -1 for game over

char* gallowsToString(gallows* g);