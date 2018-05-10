#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "graphics.h"

void testA(){

	int num_step = 11 ; 
	for (int step_idx = 0; step_idx < num_step; ++step_idx){
		getchar();
		system("clear");
		printf("%s\n", GRAPHICS[step_idx]);

	}
}

void testN(){
  
}

int main(int argc, char** argv){
  
  testA();
  
  testN();
  return 0;
}

