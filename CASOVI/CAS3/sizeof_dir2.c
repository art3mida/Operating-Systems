#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include<string.h>

static inline void osAssert( bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./sizeof_dir fpath\n"; 

void osSizeOfDir(const char *fpath, unsigned *size){
  //dohvatimo informacije o fajlu sa lstat
  struct stat finfo;
  osAssert(-1 != lstat(fpath, &finfo), "Lstat failed.\n");
  
  //dodamo njegovu velicinu na size
  *size += finfo.st_size;
  
  //u ifu proveravamo da li je dir
  if(S_ISDIR(finfo.st_mode)){
    //pravimo strukturu DIR (opendir)
    DIR *direktorijum = opendir(fpath);
    
    //listamo njene elemente sa dirent *entry (readdir)
    struct dirent *entry;
    while(entry = readdir(direktorijum)){
      //pravimo novu adresu
      char *newPath = malloc( strlen(fpath) + 1 + strlen(entry->d_name) + 1);
      strcpy(newPath, fpath);
      strcat(newPath, "/");
      strcat(newPath, entry->d_name);
      
      //kada naidjemo na . i .., njihove velicine samo dodamo, ne ulazimo u njihove
      if(!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name)){
	osAssert(-1 != lstat(newPath, &finfo), "Lstat failed.\n");
	*size += finfo.st_size;
	continue;
      }
      
    //pozivamo rekurzivno za svaku datoteku
    osSizeOfDir(newPath, size);
    free(newPath);
    }
  //closedir
  closedir(direktorijum);
  }
  
}

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  unsigned size = 0U;
  osSizeOfDir(argv[1], &size);
  printf("Size of directory: %u", size);
  
  return 0;
}
