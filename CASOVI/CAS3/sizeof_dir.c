#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <dirent.h>
#include <sys/types.h>
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
  //dohvatiti informacije o fajlu/datoteci
  struct stat finfo;
  osAssert(-1 != lstat(fpath, &finfo), "Lstat failed.\n");
  
  //dodati velicinu trenutnog fajla 
  *size += finfo.st_size;
  
  //preko st_mode proveriti da li je fajl datoteka
  // ako jeste datoteka, otvoriti datoteku
  if(S_ISDIR(finfo.st_mode)){
    DIR *direktorijum = opendir(fpath);
    osAssert(NULL != direktorijum, "Opendir failed.\n");
  
  //listati njene elemente preko dirent *entry dok ne prodjemo sve
    struct dirent *entry = NULL;
    while(NULL != (entry = readdir(direktorijum))){
  
      //napraviti novu putanju
     // char *newPath = malloc( strlen(fpath) + 1 + strlen(entry->d_name) + 1); // 1 za '/' i '/0'
      char newPath[1000];
      strcpy(newPath,fpath);
      strcat(newPath,"/");
      strcat(newPath, entry->d_name);
      
      //ako je datoteka . ili .., samo dodati njihove velicine, ne pozivati rekurzivno
      if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")){
	osAssert(-1 != lstat(newPath, &finfo), "Could not lstat . or .. .\n");
	*size += finfo.st_size;
	//free(newPath);
	continue;
      }
     
    
  // rekurzivno pozvati fju za svaki element datoteke
  osSizeOfDir(newPath, size);
    
  //osloboditi adresu putanje
  //free(newPath);
    }
    
    closedir(direktorijum);
  }
}

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  unsigned size = 0U;
  osSizeOfDir(argv[1], &size);
  printf("Size of directory: %u\n", size);
  
  return 0;
}