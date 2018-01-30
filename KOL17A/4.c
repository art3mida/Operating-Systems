#define _XOPEN_SOURCE 700
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define BUFF_SIZE (4096)


void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./4 -[r|w|a] fpath";

int main(int argc, char** argv){
  osAssert(3 == argc, osUsage);  
  char buff[BUFF_SIZE];
  int fd;
  char *fpath = argv[2];
  
  if(argv[1][1] == 'r'){
    fd = open(fpath, O_RDONLY, 0);
    osAssert(-1 != fd, "Open failed.\n");
    int bytesRead = -1;
    while((bytesRead = read(fd, buff, sizeof buff)) > 0)
      osAssert(bytesRead == write(STDOUT_FILENO, buff, bytesRead), "Write failed.\n");
    osAssert(-1 != bytesRead, "Read failed.\n");
    close(fd);
  }
  
  else if(argv[1][1] == 'w'){
    fd = open(fpath, O_CREAT | O_TRUNC | O_WRONLY, 0666);
    osAssert(-1 != fd, "Open failed.\n");
    int bytesRead = -1;
    while((bytesRead = read(STDIN_FILENO, buff, sizeof buff)) > 0)
      osAssert(bytesRead == write(fd, buff, bytesRead), "Write failed.\n");
    osAssert(-1 != bytesRead, "Read failed.\n");
    close(fd);
  }
  else if(argv[1][1] == 'a'){
    fd = open(fpath, O_CREAT | O_APPEND | O_WRONLY, 0666);
    osAssert(-1 != fd, "Open failed.\n");
    int bytesRead = -1;
    while((bytesRead = read(STDIN_FILENO, buff, sizeof buff)) > 0)
      osAssert(bytesRead == write(fd, buff, bytesRead), "Write failed.\n");
    osAssert(-1 != bytesRead, "Read failed.\n");
    close(fd);
  }
  
  return 0;
}
