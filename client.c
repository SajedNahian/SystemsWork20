#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  from_server = client_handshake( &to_server );
  while(1){
    printf("[CLIENT] What would you like to send? (no spaces): ");
    char input[200];
    fgets(input, 200, stdin);
    strtok(input,"\n");
    write(to_server, input, 200);
    char receivedInput[strlen(input)]; // Since server is returning inverse of string, length is known
    read(from_server, receivedInput, strlen(input));
    printf("[CLIENT]: Received -<%s>- (Should be inverse string of %s)\n", receivedInput, input);
  }
}
