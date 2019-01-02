#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo("requestFifo", 0644);
  printf("[SERVER]: Waiting for a request\n");
  int request = open("requestFifo", O_RDONLY);
  char client_info[11];
  read(request, client_info, 11);
  // printf("%s\n", client_info);
  remove("requestFifo");
  int fd = open(client_info, O_WRONLY);
  int f = fork();
  if (f) {
    return 0;
  } else {
    *to_client = fd;
    printf("[SERVER]: Request was successful\n");
    write(fd, "Request was confirmed", 22);
    char final[26];
    read(request, final, 26);
    printf("[SERVER]: %s\n", final);
    return request;
  }
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  mkfifo("serverFifo", 0644);
  int request = open("requestFifo", O_WRONLY);
  *to_server = request;
  printf("[CLIENT]: Sending a request\n");
  write(request, "serverFifo", 11);
  int fd = open("serverFifo", O_RDONLY);
  char confirmation[22];
  read(fd, confirmation, 22);
  printf("[CLIENT]: Received confirmation of working request\n");
  remove("serverFifo");
  write(request, "Confirmation was received", 26);
  printf("[CLIENT]: Sending final confirmation to server\n");
  return fd;
}
