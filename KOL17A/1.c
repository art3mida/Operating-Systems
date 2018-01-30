#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

static const char *osUsage = "Usage: ./1 fpath";

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  struct stat finfo;
  osAssert(-1 != lstat(argv[1], &finfo), "Lstat failed.\n");
  
  char access[ACCESS_SIZE] = {0};
  if(S_ISREG(finfo.st_mode)) access[0] = '-';
  else if(S_ISDIR(finfo.st_mode)) access[0] = 'd';
  else if(S_ISCHR(finfo.st_mode)) access[0] = 'c';
  else if(S_ISBLK(finfo.st_mode)) access[0]= 'b';
  else if(S_ISFIFO(finfo.st_mode)) access[0]= 'p';
  else if(S_ISLNK(finfo.st_mode)) access[0] = 'l';
  else if(S_ISSOCK(finfo.st_mode)) access[0] = 's';
  
  access[1] = (finfo.st_mode & S_IRUSR) ? 'r' : '-';
  access[2] = (finfo.st_mode & S_IWUSR) ? 'w' : '-';
  access[3] = (finfo.st_mode & S_IXUSR) ? 'x' : '-';
  
  access[4] = (finfo.st_mode & S_IRGRP) ? 'r' : '-';
  access[5] = (finfo.st_mode & S_IWGRP) ? 'w' : '-';
  access[6] = (finfo.st_mode & S_IXGRP) ? 'x' : '-';
  
  access[7] = (finfo.st_mode & S_IROTH) ? 'r' : '-';
  access[8] = (finfo.st_mode & S_IWOTH) ? 'w' : '-';
  access[9] = (finfo.st_mode & S_IXOTH) ? 'x' : '-';
  
  printf("%s\n", access);
  
  return 0;
}