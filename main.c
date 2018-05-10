#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "networkIO.h"

void testA(){


	gallows* g = buildGallows ("mot");


	while ( tryLetter(g, getNextCharLocal() ) != -1 ){  // 0 -> lettre bonne, 1 -> lettre pas bonne -> -1 jeu terminé
		displayStateLocal(g);
	}
}

void testN(){
  while(1){
    char c = getNextCharLocal();
    printf("%c\n",c);
  }
}

int main(int argc, char** argv){
  
  testA();
  
  testN();
  return 0;
}

