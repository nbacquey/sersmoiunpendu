#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "coreStructs.h"

char* getNewGameWordLocal();

char getNextCharLocal();
void sendNextCharToServer(int socket);

void displayMessageLocal(char* message, int options);
void displayStateLocal(gallows* state);

int initClient(); 