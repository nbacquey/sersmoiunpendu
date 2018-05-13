#include "networkIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


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

  while ( send( socket, &nc, 1, 0 ) != 1 ){}
  // check that its return value is equal to the number of bytes you tried to send.
  // In most cases this can be resolved by resending the unsent data.

}

void displayStateLocal(gallows* state){
  printf("%s\n",gallowsToString(state));
}

void displayMessageLocal(char* message, int options){
  printf("%s\n",message);
  fflush(stdout);
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
	dest.sin_port = htons(8484);



	/*  make the connection and use it :*/
	// This tells our OS to use the socket mysocket to create a connection to the machine specified in dest.
	connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
	

	return mysocket;

}