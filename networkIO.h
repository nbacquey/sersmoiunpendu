#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "coreStructs.h"

char* getNewGameWordLocal();

char getNextCharLocal();

void displayMessageLocal(char* message, int options);
void displayStateLocal(gallows* state);

int initClient(); 
void *displayLoop(void *args);
void displayResponse(int socket);
void sendNextCharToServer(int socket);

int initServer();
void closeServer();
void *acceptLoop();

char getNextCharServer();

void displayStateNetwork(gallows* state);
void displayMessageNetwork(char* message, int options);
void broadcastClients(char* message);