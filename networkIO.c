#include "networkIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>

#define SERV_PORT_NUM 8484
#define MAXIMUM_CLIENT_NUMBER 16


int *clientSockets;
int servSocket;
struct sockaddr *clientAddresses;
int nbClients;

pthread_t listenerThread;

int initServer(){
  clientSockets = malloc(sizeof(int)*MAXIMUM_CLIENT_NUMBER);
  clientAddresses = malloc(sizeof(struct sockaddr)*MAXIMUM_CLIENT_NUMBER);
  nbClients = 0;
  
  struct sockaddr_in serv;  
  
  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
  serv.sin_addr.s_addr = htonl(INADDR_ANY); /* set our address to any interface */
  serv.sin_port = htons(SERV_PORT_NUM);     /* set the server port number */
  
  servSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  bind(servSocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
  listen(servSocket, 1);
  
  if(pthread_create(&listenerThread, NULL, acceptLoop, NULL) == -1) {
    perror("pthread_create");
    return EXIT_FAILURE;
  }
  
  return 0;
}

void *acceptLoop(void *arg){
  socklen_t socksize = sizeof(struct sockaddr_in);
  struct sockaddr newAddress;
  while(nbClients <= MAXIMUM_CLIENT_NUMBER){    
    int newSocket = accept(servSocket, &newAddress, &socksize);
    clientSockets[nbClients] = newSocket;
    clientAddresses[nbClients] = newAddress;
    
    //sets socket to nonblocking reading mode
   int flags = fcntl(newSocket, F_GETFL, 0);
   flags |=  O_NONBLOCK;
   fcntl(newSocket, F_SETFL, flags);
   
   printf("New client connected\n");
   ++nbClients;
  }
  
  close(servSocket);
  pthread_exit(NULL);
}

void closeServer(){
  pthread_kill(listenerThread, SIGINT);
  close(servSocket);
}

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

void sendNextCharToServer(int socket){
  char nc;
  nc = getNextCharLocal();

  while ( send( socket, &nc, 1, 0 ) != 1 );
  // check that its return value is equal to the number of bytes you tried to send.
  // In most cases this can be resolved by resending the unsent data.
}

char getNextCharServer(){
  int i, smax;
  int nbC = nbClients;
  
  fd_set set;
  FD_ZERO(&set);
  
  smax = 0;
  for(i = 0; i < nbC; ++i){
    int cSocket = clientSockets[i];
    if(cSocket > smax)
      smax = cSocket;
    FD_SET(cSocket,&set);
  }
  while(select(smax+1, &set, NULL, NULL, NULL) == 0);
  int readSocket;
  for(i = 0; i < nbC; ++i){
    int cSocket = clientSockets[i];
    if(FD_ISSET(cSocket,&set)){
      readSocket = cSocket;
      break;
    }      
  }
  char ret;
  recv(readSocket, &ret, 1, 0);
  
  printf("Client number %d said %c !\n",readSocket, ret);
  return ret;
}

void displayStateLocal(gallows* state){
  printf("%s\n",gallowsToString(state));
}

void displayStateNetwork(gallows* state){
  broadcastClients(gallowsToString(state));
}

void displayMessageLocal(char* message, int options){
  printf("%s\n",message);
}


int initClient(){

  int mysocket ; 
  struct sockaddr_in dest; // stores information about the machine we want to connect to.
  mysocket = socket(AF_INET, SOCK_STREAM, 0);
  memset(&dest, 0, sizeof(dest)); // zero the struct 
  dest.sin_family = AF_INET; // set the address family
  dest.sin_addr.s_addr = inet_addr("127.0.0.1"); // set destination IP number - localhost, 127.0.0.1
  dest.sin_port = htons(SERV_PORT_NUM); // set destination port number
  connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in)); /*  make the connection and use it :*/	

  pthread_t displayThread;
  int* socketRef = malloc(sizeof(int));
  *socketRef = mysocket;
  if(pthread_create(&displayThread, NULL, displayLoop, socketRef) == -1) {
    perror("pthread_create");
    return EXIT_FAILURE;
  }
  
  return mysocket;
}

void *displayLoop(void *args){
  int socket = *((int*)args);
  
  char buffer[256];
  while(1){
    while(recv(socket, buffer, 256, 0) == 0);
    printf("%s", buffer);
  }
}


void displayMessageNetwork(char* message, int options){
  if(options == 1)
    broadcastClients(message);
  else
    printf("%s\n",message);
}

void broadcastClients(char* message){
  int i;
  for(i = 0; i < nbClients; ++i){
    printf("sending message to client %d\n",clientSockets[i]);
    send(clientSockets[i], message, strlen(message), 0);
  }
}