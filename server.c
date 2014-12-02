#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

//#include "http_request.h"
#include "server.h"
#include "strbuffer.h"

// Maximum length of queue for connections
#define BACKLOG 5

#define BUFLEN 128

static int portnum;
static int sockfd;

void handle_request(int sockfd)
{
  int n;
  char buffer[BUFLEN];
  struct StrBuffer *str = StrBuffer_create();
  
  do {
    if((n = recv(sockfd, buffer, BUFLEN, 0)) == -1)
      goto error;

    StrBuffer_append(str, buffer, n);
  } while(n == BUFLEN);

  StrBuffer_append(str, "\0", 1);
  printf("%s", str->buf);
 error:
  StrBuffer_destroy(str);
}

void end_server()
{
  printf("Ending server\n");
  close(sockfd);
}

void init_server(const int port)
{
  struct sockaddr_in serv_addr;

  portnum = port;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("can't open socket");
    return;
  }

  // set server address and port
  memset(&serv_addr, 0, sizeof(struct sockaddr_in));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(portnum);

  if(bind(sockfd, (struct sockaddr *)&serv_addr,
          sizeof(struct sockaddr_in)) == -1) {
    perror("can't bind");
    return;
  }

  if(listen(sockfd, BACKLOG) == -1) {
    perror("failed to listen");
    return;
  }
}

void run_server()
{
  int newsockfd;
  int run = 1;
  pid_t pid;

  while(run) {
    // accept a connection
    if((newsockfd = accept(sockfd, NULL, NULL)) == -1) {
      perror("failed to accept");
      continue;
    }

    // Fork to handle request
    if((pid = fork()) == -1) {
      perror("fork failed");
      continue;
    }

    // Child process
    if(pid == 0) {
      // handle request
      printf("Handling request\n");
      handle_request(newsockfd);
      run = 0;
    }
    close(newsockfd);
  }
}
