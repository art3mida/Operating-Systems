#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_SIZE 4096

static inline void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./cpfile fsrcpath fdestpath\n";

static int b;

void osCpFile(const char *fsrcpath, const char *fdestpath){
  int fdsrc;
  fdsrc = open(fsrcpath, O_RDONLY, 0);
  int fddest;
  fddest = open(fdestpath, O_CREAT | O_TRUNC | O_WRONLY, 0666);
  
  osAssert(-1 != fdsrc && -1 != fddest, "Failed to open file.\n");
  
  char buff[BUFF_SIZE];
  int bytesRead;
  b= sizeof buff;
  while( (bytesRead = read(fdsrc, buff, sizeof buff)) > 0 ){
    osAssert( (bytesRead == write(fddest, buff, bytesRead)), "Write failed.\n");
  }
  
  osAssert(-1 != bytesRead, "Read failed.\n");
  close(fdsrc);
  close(fddest);
}

int main(int argc, char** argv){
  osAssert(3 == argc, osUsage);
  osCpFile(argv[1],argv[2]);
  
  printf("sizeof buffsize %d\n", sizeof BUFF_SIZE);
  printf("sizeof buff: %d\n", b);
  return 0;
}