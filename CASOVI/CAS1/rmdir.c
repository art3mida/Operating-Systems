#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#include <unistd.h>
#include <fcntl.h>

#define osAssert(expr, msg) osAssertImpl(expr, msg, __FILE__, __LINE__)

static inline void osAssertImpl(bool expr, const char *msg, const char *fname, int line){
  if(!expr){
    perror(msg);
    fprintf(stderr, "File: %s, Line: %d\n", fname, line);
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./rmdir -[f|d] fpath\n";

int main(int argc, char **argv){
  osAssert(3 == argc, osUsage);
  
  const char *type = argv[1];
  const char *fpath = argv[2];
  
  if('f'==type[1]){
    osAssert(-1 != unlink(fpath), "Greska pri brisanju fajla.\n");
  }
  else{
    osAssert(-1 != rmdir(fpath), "Greska pri brisanju datoteke.\n");
  }
  
  return 0;
}