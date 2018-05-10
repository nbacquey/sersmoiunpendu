#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "coreStructs.h"

char* getNewGameWordLocal();

char getNextCharLocal();

void displayMessageLocal(char* message, int options);
void displayStateLocal(gallows* state);