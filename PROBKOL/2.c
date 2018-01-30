#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>



void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./2 fname";  

void osMakeFile(const char *fname){
  mode_t mode = 0733;
  mode_t maska = umask(0);
  
  int fd = open(fname, O_CREAT | O_EXCL , mode);
  osAssert(-1 != fd, "Open failed.\n");
  close(fd);
  
  (void)umask(maska);
}

int main(int argc, char** argv){
  osAssert(2==argc, osUsage);
  osMakeFile(argv[1]);
  
  return 0;
}
  