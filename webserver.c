#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "server.h"

void terminate_handler(int signum)
{
  end_server();
  exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[])
{
  int port;
  struct sigaction new_action, old_action;

  if(argc != 2) {
    fprintf(stderr, "Usage %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  new_action.sa_handler = terminate_handler;
  sigemptyset(&new_action.sa_mask);
  new_action.sa_flags = 0;

  sigaction(SIGINT, NULL, &old_action);
  if(old_action.sa_handler != SIG_IGN)
    sigaction(SIGINT, &new_action, NULL);
  sigaction(SIGTERM, NULL, &old_action);
  if(old_action.sa_handler != SIG_IGN)
    sigaction(SIGTERM, &new_action, NULL);
  sigaction(SIGQUIT, NULL, &old_action);
  if(old_action.sa_handler != SIG_IGN)
    sigaction(SIGQUIT, &new_action, NULL);

  port = atoi(argv[1]);

  init_server(port);
  run_server();

  exit(EXIT_SUCCESS);
}
