#include "pipe_networking.h"

static void sighandler(int sig){
	if(sig == SIGINT){
		// Remove named pipe if program exits
		remove("requestFifo");
		exit(0);
	}
}

int main() {

  int to_client;
  int from_client;
  while(1) {
  	from_client = server_handshake( &to_client );
  	char input[200];
  	if (from_client) {
		while(read(from_client, input, 200)){
		    printf("[SERVER]: Received -<%s>-\n", input);
		    char modifiedInput[strlen(input)];
		    for(int i=0; i<strlen(input); i++) {
		    	modifiedInput[i] = input[strlen(input)-i-1];
		    }
		    modifiedInput[200] = '\0';
		    write(to_client, modifiedInput, strlen(input));
		}
	}
  }
}
