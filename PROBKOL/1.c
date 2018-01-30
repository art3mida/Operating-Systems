#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ACCESS_SIZE 11

void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./1 fpath fsize"; 

bool osIsFileSmaller(const char *fpath, intmax_t fsize, char** ftype){
  struct stat finfo;
  osAssert(-1 != lstat(fpath, &finfo), "Lstat failed.\n");
  
  if(S_ISREG(finfo.st_mode)) *ftype = "Regular file";
  else if(S_ISDIR(finfo.st_mode)) *ftype = "Directory";
  else if(S_ISCHR(finfo.st_mode)) *ftype = "Character device";
  else if(S_ISBLK(finfo.st_mode)) *ftype = "Block file";
  else if(S_ISFIFO(finfo.st_mode)) *ftype = "FIFO";
  else if(S_ISLNK(finfo.st_mode)) *ftype = "Symbolic link";
  else if(S_ISSOCK(finfo.st_mode)) *ftype = "Socket";
  
  return (intmax_t)finfo.st_size > fsize;
}

int main(int argc, char** argv){
  osAssert(3 == argc, osUsage);
  char *ftype;
  bool isBigger = osIsFileSmaller(argv[1], (intmax_t)atoi(argv[2]), &ftype);
  printf("%s %s\n", ftype, isBigger? "true" : "false");
  
  return 0;
}
  