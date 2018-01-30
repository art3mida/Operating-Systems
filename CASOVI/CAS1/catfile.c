#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_SIZE (4096)

static inline void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./catfile fpath\n";

void osCatFile(const char *fpath){
  osAssert(NULL != fpath, "Wrong fpath arg.");
  int fd;
  fd = open(fpath, O_RDONLY, 0);
  osAssert(-1 != fd, "Failed to open file.\n");
  
  char buff[BUFF_SIZE];
  int bytesRead;
  
  while( (bytesRead = read(fd, buff, sizeof buff)) > 0){
    osAssert(bytesRead == write(STDOUT_FILENO, buff, bytesRead), "Write failed.\n");
  }
  
  osAssert(-1 != bytesRead, "Read failed.\n");
  close(fd);
}


int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  osCatFile(argv[1]);
  
  return 0;
}
  