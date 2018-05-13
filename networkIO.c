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

#define SERV_PORT_NUM 8484
#define MAXIMUM_CLIENT_NUMBER 16


int *clientSockets;
struct sockaddr_in *clientAddresses;
int nbClients;

pthread_t listenerThread;

void initServer(){
  clientSockets = malloc(sizeof(int)*MAXIMUM_CLIENT_NUMBER);
  clientAddresses = malloc(sizeof(struct sockaddr_in)*MAXIMUM_CLIENT_NUMBER);
  nbClients = 0;
  
  struct sockaddr_in serv;
  
  int servSocket;
  
  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;                /* set the type of connection to TCP/IP */
  serv.sin_addr.s_addr = htonl(INADDR_ANY); /* set our address to any interface */
  serv.sin_port = htons(SERV_PORT_NUM);     /* set the server port number */
  
  servSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));
  listen(mysocket, 1);
  
  if(pthread_create(&listenerThread, NULL, acceptLoop, NULL) == -1) {
    perror("pthread_create");
    return EXIT_FAILURE;
  }
  
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
   fcntl(fd, F_SETFL, flags);
   
   ++nbClients;
  }
  
  close(servSocket);
  pthread_exit(NULL);
}

int closeServer(){
  pthread_kill(listenerThread, SIGINT);
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
    int cSocket = clientSockets[i]
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
	// initialize client connection to the serveur throught TCP protocol

	int mysocket ; 
	struct sockaddr_in dest; // stores information about the machine we want to connect to.



	/* Init socket */ 
	// tells our OS that we want a file descriptor for a socket which we can use for a network stream connection :
	mysocket = socket(AF_INET, SOCK_STREAM, 0);


	/* Information about the machne we want to connect to */ 

	// zero the struct :
	memset(&dest, 0, sizeof(dest)); // zero the struct 

	// set the address family
	// should be the same value that was passed as the first parameter to socket(); 
	// for most purposes AF_INET will serve.
	dest.sin_family = AF_INET;
	
	// set destination IP number - localhost, 127.0.0.1
	// dest.sin_addr.s_addr = integer stored in Big Endian format
	// inet_addr() function will do the conversion from string into Big Endian integer for us
	dest.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  //dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 

  // set destination port number
  // for portability reasons htons() should always be used.
  // htons() function converts the port number into a Big Endian short integer
	dest.sin_port = htons(SERV_PORT_NUM);



	/*  make the connection and use it :*/
	// This tells our OS to use the socket mysocket to create a connection to the machine specified in dest.
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
	

	return mysocket;

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
    send(clientSockets[i], message, strlen(message), 0);
  }
}