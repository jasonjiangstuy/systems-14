#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include <fcntl.h>

static void sighandler(int sig) {
  if (sig == SIGINT) {
    // 2 - SIGINT - interupt process stream, ctrl-C
    int fh = open("exit.log", O_WRONLY | O_TRUNC | O_CREAT, 0777);
    char * x = "program exited due to SIGNINT";
    write(fh, x, strlen(x));
    exit(0);
  }
  if (sig == SIGUSR1) {
    // 10 - SIGUSR1
    printf("ppid: %d\n", getppid());
  }
}


int main() {
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while (1) {
    /* code */
    printf("pid: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
