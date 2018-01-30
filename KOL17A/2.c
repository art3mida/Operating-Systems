
#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <grp.h>
#include<pwd.h>

void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./2 fpath";

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  struct stat finfo;
  osAssert(-1 != lstat(argv[1], &finfo), "Lstat failed.\n");
  
  struct passwd *user = getpwuid(finfo.st_uid);
  osAssert(NULL != user, "Getpwuid failed.\n");
  printf("%s ", user->pw_name);
  
  struct group *usergroup = getgrgid(finfo.st_gid);
  osAssert(NULL != usergroup, "Getgrgid failed.\n");
  printf("%s", usergroup->gr_name);
  
  return 0;
}