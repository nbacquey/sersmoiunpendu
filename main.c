#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "networkIO.h"
#include "gameplay.h"

void testA(){

	int s = initClient(); 
	printf("%d\n", s);

	sendNextCharToServer(s);

	gallows* g = buildGallows ("MOT");


	while ( tryLetter(g, getNextCharLocal() ) != -1 ){  // 0 -> lettre bonne, 1 -> lettre pas bonne -> -1 jeu terminé
		displayStateLocal(g);
	}
}

void testN(){
  game();
}

int main(int argc, char** argv){
  
  testA();
  
  //testN();
  return 0;
}

