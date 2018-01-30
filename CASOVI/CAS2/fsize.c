#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <unistd.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>


#define osAssert(expr, msg) osAssertImpl(expr, msg, __FILE__, __LINE__)

static inline void osAssertImpl(bool expr, const char *msg, const char *fname, int line){
  if(!expr){
    perror(msg);
    fprintf(stderr, "File: %s, Line: %d\n", fname, line);
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./fsize fpath\n";

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  int fd;
  fd = open(argv[1], O_RDONLY, 0);
  off_t offset = lseek(fd, 0, SEEK_END);
  osAssert(-1 != offset, "Lseek failed.\n");
  
  printf("Size of file: %jd\n", (intmax_t)offset);
  close(fd);
}