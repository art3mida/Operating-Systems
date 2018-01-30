#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

static inline void osAssert( bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./umask fpath mode\n";

//hocemo da napravimo fajl sa privilegijama onakvim kakve stavimo, bez maske
//prvo prebacimo mode iz komandne linije u dobar format
// postavimo masku na nula f-jom umask, ali sacuvamo i prethodnu vred.
// napravimo fajl sa tim privilegijama, a ako vec postoji terminiramo program
// zatvorimo fajl
// vratimo umask

int main(int argc, char** argv){
  osAssert(3 == argc, osUsage);
  mode_t maska = umask(0);
  
  int fd = open(argv[1], O_CREAT | O_EXCL, (mode_t)strtol(argv[2],NULL,8));
  osAssert(-1 != fd, "Open failed.\n");
  
  close(fd);
  (void) umask(maska);
  
  return 0;
}
  