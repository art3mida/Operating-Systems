#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define osAssert(expr, msg) osAssertImpl(expr,msg,__FILE__,__LINE__)

static inline void osAssertImpl(bool expr, const char* msg, const char *fname, int line){
  if(!expr){
    perror(msg);
    fprintf(stderr, "File: %s, Line: %d", fname, line);
    exit(EXIT_FAILURE);
  }
}

static const char* osUsage = "Usage: ./mkfile fpath mode\n";

bool osMkFile(const char *fpath, const char *mode, int *pFd){
  
  osAssert(NULL!=fpath, "Wrong path arg.\n");
  osAssert(NULL != mode, "Wrong mode arg.\n");
  osAssert(NULL != pFd, "Wrong pfd arg.\n");
  
  static const mode_t sMode = 0777; //rw-rw-rw-
  
  int flags=0;
  
  if(mode[0]=='r'){
    if(mode[1]=='+'){
      flags|=O_RDWR;
    }
    else{
      flags|=O_RDONLY;
    }
  }
  
  else if(mode[0]=='w'){
    flags |= O_CREAT;
    flags |= O_TRUNC;
    flags |= ((mode[1]=='+') ? O_RDWR : O_WRONLY);
  }
  
  else if(mode[0]=='a'){
    flags |= O_CREAT;
    flags |= O_APPEND;
    flags |= ((mode[1]=='+') ? O_RDWR : O_WRONLY);
  }
  
  *pFd = open(fpath, flags, mode);
  return -1 != *pFd;
}

int main(int argc, char** argv){
  osAssert(3 == argc, osUsage);
  
  int fd;
  osAssert( osMkFile(argv[1], argv[2], &fd), "Failed to open/create file.\n");
  
  close(fd);
  return 0;
}
  
