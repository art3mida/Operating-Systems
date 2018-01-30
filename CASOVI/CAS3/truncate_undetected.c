#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <utime.h>


static inline void osAssert( bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./truncate_undetected fpath\n";

// funkcijom stat uzmemo podatke o fajlu u finfo
// otvorimo fajl sa O_TRUNC
// zatvorimo fajl
// izmenimo vreme poslednje izmene sa utime

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  
  struct stat finfo; 
  osAssert(-1 != stat(argv[1], &finfo), "Stat failed.\n");
  
  int fd = open(argv[1], O_TRUNC, 0666);
  osAssert(-1 != fd, "Open failed.\n");
  
  struct utimbuf time = { .modtime = finfo.st_mtime,
			  .actime = finfo.st_atime };
  osAssert(-1 != utime(argv[1], &time), "Restoring time failed.\n");
  
  close(fd);
  return 0;
}
  
