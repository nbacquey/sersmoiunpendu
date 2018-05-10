#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "coreStructs.h"


const char* GRAPHICS[] = {
"\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
","\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
                  \n\
============      \n\
                  \n\
","\
                  \n\
                  \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==============\n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==============\n\
   ||  /          \n\
   || /           \n\
   ||/            \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==========Y===\n\
   ||  /      |   \n\
   || /       |   \n\
   ||/            \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==========Y===\n\
   ||  /      |   \n\
   || /       |   \n\
   ||/        O   \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==========Y===\n\
   ||  /      |   \n\
   || /       |   \n\
   ||/        O   \n\
   ||         |   \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==========Y===\n\
   ||  /      |   \n\
   || /       |   \n\
   ||/        O   \n\
   ||        /|   \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==========Y===\n\
   ||  /      |   \n\
   || /       |   \n\
   ||/        O   \n\
   ||        /|\\ \n\
   ||             \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==========Y===\n\
   ||  /      |   \n\
   || /       |   \n\
   ||/        O   \n\
   ||        /|\\ \n\
   ||        /    \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
","\
                  \n\
   ,==========Y===\n\
   ||  /      |   \n\
   || /       |   \n\
   ||/        O   \n\
   ||        /|\\ \n\
   ||        /|   \n\
   ||             \n\
   ||             \n\
   ||             \n\
============      \n\
                  \n\
"
};



gallows* buildGallows(char* initWord){
  gallows* ret = malloc(sizeof(gallows));
  
  ret->currentStep = 0; // indice du graphic pendu
  ret->wordSize = strlen(initWord); // taille du mot
  ret->wrongLetters = malloc(sizeof(char)*MAXIMUM_WORD_SIZE); // vector de mauvaise lettre essayées par le jours
  ret->currentWord = malloc(sizeof(char)*(ret->wordSize+1)); // etat du mot
  ret->fullWord = initWord; // le mot a deviner
  ret->status = 0; // 0 : en cours ; 1 : gagné ; -1 : perdu
  
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
  
  return 1;
}

char* gallowsToString(gallows* g){
  /*
  Return the string associated to the game state.
   gallow graphic
    +  the current word
    +  the list of wrong lettters that have been tried
    +  the status
  */
  char* ret = malloc(sizeof(char)*OUTPUT_SIZE);

  strcpy(ret, "\n");
  strcat(ret, GRAPHICS[g -> currentStep]);
  strcat(ret, "\n");
  strcat(ret, g -> wrongLetters);
  strcat(ret, "\n");
  strcat(ret, g -> currentWord);
  strcat(ret, "\n");
  //if (g-> status == 0) strcat(ret, "What is your next move ? ");
  //else if (g-> status == 1) strcat(ret,"gg");
  //else strcat(ret, "fail");

  return ret;
}