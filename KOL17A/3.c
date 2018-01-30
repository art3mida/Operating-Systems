#define _XOPEN_SOURCE 700
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./3 -[f|d] fpath mode";

int main(int argc, char** argv){
  osAssert(4 == argc, osUsage); 
  mode_t mode = (mode_t)strtol(argv[3], NULL, 8);
  
  if(argv[1][1]=='f'){
    int fd = open(argv[2], O_CREAT, mode);
    osAssert(-1 != fd, "Open failed.\n");
    close(fd);
    
    osAssert(-1 != chmod(argv[2], mode), "Chmod failed.\n");
  }
  
  else {
    int dirExists = mkdir(argv[2], mode);
    if(dirExists == -1){
      if(errno == EEXIST)
	osAssert(-1 != chmod(argv[2],mode), "Chmode failed.\n");
      else osAssert(1, "Mkdir failed.\n");
    }
  }
  
  return 0;
}
  