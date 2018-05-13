#include "networkIO.h"
#include "gameplay.h"

int gameLocal(){
  displayMessageLocal("Enter a word to guess (all caps)",0);
  char* newWord = getNewGameWordLocal();
  gallows* g = buildGallows(newWord);
  
  displayMessageLocal("New game started",1);
  while (g->status == 0){
    displayMessageLocal("Enter a character",1);
    char c = getNextCharLocal();
    
    char* answer;
    switch (tryLetter(g, c)){
      case -1:
        answer = "Game Over !";
        break;
      case 0:
        answer = "Good Guess !";
        break;
      case 1:
        answer = "Wrong Guess !";
        break;      
    }
    
    displayMessageLocal(answer,1);
    displayMessageLocal(gallowsToString(g),1);
  }
  
  char* endGame = (g->status == 1) ? "You Win !" : "You Lose !";
  displayMessageLocal(endGame,1);
  
  return g->status;
}

int gameServer(){
  
  initServer();
  
  displayMessageNetwork("Enter a word to guess (all caps)",0);
  char* newWord = getNewGameWordLocal();
  gallows* g = buildGallows(newWord);
  displayMessageNetwork("Starting new game...",0);
  displayMessageNetwork("Starting new game...",1);
  while (g->status == 0){
    displayMessageNetwork("Enter a character",0);
    char c = getNextCharServer();
    
    char* answer;
    switch (tryLetter(g, c)){
      case -1:
        answer = "Game Over !";
        break;
      case 0:
        answer = "Good Guess !";
        break;
      case 1:
        answer = "Wrong Guess !";
        break;      
    }
    
    displayMessageNetwork(answer,0);
    displayMessageNetwork(gallowsToString(g),0);
  }
  
  char* endGame = (g->status == 1) ? "You Win !" : "You Lose !";
  displayMessageNetwork(endGame,0);
  return g->status;
}

int gameClient(){
  int clientSocket = initClient();
  while(1){
    printf("Send a character to the server\n");
    sendNextCharToServer(clientSocket);
  }
  return 0;
}