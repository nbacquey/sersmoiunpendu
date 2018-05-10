#include <strings.h>
#include "coreStructs.h"

gallows* buildGallows(char* initWord){
  gallows* ret = malloc(sizeof(gallows));
  
  ret->curentStep = 0;
  ret->wordSize = strlen(initWord);
  ret->wrongLetters = malloc(sizeof(char)*MAXIMUM_WORD_SIZE);
  ret->currentWord = malloc(sizeof(char)*(ret->wordSize+1));
  ret->fullWord = initWord;
  
  int i;
  for(i = 0; i < ret->wordSize; ++i){
    ret->currentWord[i] = '_';
  }
  ret->currentWord[i] = '\0';
  
  ret->wrongLetters[0] = '\0';
  
  return ret;
}

char* gallowsToString(gallows* g){
  char* ret = malloc(sizeof(char)*OUTPUT_SIZE);
  ret[0] = '\0';
  return ret;
}