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

static const char *osUsage = "Usage: ./chmod fpath mode\n"; 

//prvo prebacimo mode iz komandne linije u dobar format
// otvorimo fajl ili ga napravimo ako ne postoji
// time i podesimo privilegije
// uraditi sa umaskom iako to nije u originalnom resenju

//ako je fajl vec postojao, fjom chmod mu menjamo privilegije
// zatvoriti fajl i vratiti umask

int main(int argc, char** argv){
  osAssert(3 == argc, osUsage);
  mode_t access = (mode_t)strtol(argv[2], NULL, 8);
  
  mode_t maska = umask(0);
  
  int fd = open(argv[1], O_CREAT, access);
  osAssert(-1 != fd, "Open failed.\n");
  
  osAssert(-1 != chmod(argv[1],access), "Chmod failed.\n");
  
  close(fd);
  (void) umask(maska);
  return 0;
}
  
  
  