#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE (4096)

void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./4 fpathsrc fpathdest offset";  

void osCatFileFromPos(const char *srcpath, const char *destpath, const off_t pos){
  int fdsrc = open(srcpath, O_RDONLY, 0);
  osAssert(-1 != fdsrc, "Open failed.\n");
  
  int fddest = open(destpath, O_CREAT | O_WRONLY, 0666);
  osAssert(-1 != fddest, "Open failed.\n");
  
  osAssert(-1 != lseek(fddest, pos, SEEK_SET), "Lseek failed.\n");
  
  char buff[BUFF_SIZE];
  int bytesRead = -1;
  while( (bytesRead = read(fdsrc, buff, sizeof buff)) > 0)
    osAssert( bytesRead == write(fddest, buff, bytesRead), "Write failed.\n");
  osAssert(-1 != bytesRead, "Read failed.\n");
}

int main(int argc, char **argv){
  osAssert(4 == argc, osUsage);
  osCatFileFromPos(argv[1], argv[2], (off_t)atoi(argv[3]));
  
  return 0;
}
 
