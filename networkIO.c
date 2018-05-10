#include "networkIO.h"

char getNextCharLocal(){
  char ret;
  do{
    ret = (char) getchar();
  }
  while (ret >= 'A' && ret <= 'Z');
  return ret;
}

void displayStateLocal(gallows* state){
  printf("%s\n",gallowsToString(state));
}