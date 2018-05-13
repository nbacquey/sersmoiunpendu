#include "networkIO.h"
#include <string.h>

char* getNewGameWordLocal(){
  char* ret = malloc(sizeof(char)*256);
  scanf("%s",ret);
  return ret;
}

char getNextCharLocal(){
  char ret;
  do{
    ret = (char) getchar();
  }
  while (ret < 'A' || ret > 'Z');
  return ret;
}

void displayStateLocal(gallows* state){
  printf("%s\n",gallowsToString(state));
}

void displayMessageLocal(char* message, int options){
  printf("%s\n",message);
  fflush(stdout);
}