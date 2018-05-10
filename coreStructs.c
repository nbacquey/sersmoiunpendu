#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "coreStructs.h"

gallows* buildGallows(char* initWord){
  gallows* ret = malloc(sizeof(gallows));
  
  ret->currentStep = 0;
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

int tryLetter(gallows* g, char newC){
  if(g->status != 0)
    return -1;
  
  int i;
  for(i = 0; i < strlen(g->wrongLetters); ++i)
    if(newC == g->wrongLetters[i])
      return 1;
  
  int isCharCorrect = 0;
  int isWordCorrect = 1;
  for(i = 0; i < g->wordSize; ++i){
    if(g->fullWord[i] == newC){
      isCharCorrect = 1;
      g->currentWord[i] = newC;
    }
    if(g->currentWord[i] == '_')
      isWordCorrect = 0;
  }
  
  if(isWordCorrect){
    g->status = 1;
    return -1;
  }
  
  if(isCharCorrect){
    return 0;
  }
  
  sprintf(g->wrongLetters,"%s%c",g->wrongLetters,newC);
  if(++(g->currentStep) == NB_STEPS){
    g->status = -1;
    return -1;
  }
  
  return 1
}

char* gallowsToString(gallows* g){
  char* ret = malloc(sizeof(char)*OUTPUT_SIZE);
  ret[0] = '\0';
  return ret;
}