
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static inline void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char** argv){
  pid_t childPid = fork();
  osAssert(-1 != childPid, "Fork failed.\n");
  
  if(childPid > 0) { //parent
    printf("Hello from parent. My Id: %jd, Child Id: %jd\n", (intmax_t)getpid(), (intmax_t)childPid);
  }
  else if (childPid == 0) { //child
    printf("Hello from child. My Id: %jd, Parent Id: %jd\n", (intmax_t)getpid(), (intmax_t)childPid);
  }
  
  printf("Both proceses print this message.\n");
  
  return 0;
  
}
