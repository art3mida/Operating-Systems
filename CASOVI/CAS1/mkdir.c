#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>         
#include <sys/stat.h>

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define osAssert(expr, msg) osAssertImpl(expr, msg, __FILE__, __LINE__)

static inline void osAssertImpl(bool expr, const char *msg, const char *fname, int line){
  if(!expr){
    perror(msg);
    fprintf(stderr, "File: %s, Line: %d",fname,line);
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./mkdir dirpath\n";

int main(int argc, char** argv){
  osAssert(2==argc, osUsage);
  osAssert(-1 != mkdir(argv[1],0755), "Failed to create directory.\n");
  
  return 0;
}