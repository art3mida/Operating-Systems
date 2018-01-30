#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <dirent.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdint.h>

static inline void osAssert(bool expr, const char *msg){
  if(!expr){
    perror(msg);
    fprintf(stderr, "-1");
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./5 dirpath\n";

void osMinAndMaxSize(const char *fpath, char *pathmin, size_t *sizemin, char* pathmax, size_t *sizemax){
  //dohvatiti info o datoteci
  struct stat finfo;
  osAssert(-1 != lstat(fpath, &finfo), "Lstat failed.\n");
  
 
  
  //ako je datoteka, izlistati sve njene elemente
  if(S_ISDIR(finfo.st_mode)){
    DIR *direktorijum = opendir(fpath);
    osAssert(NULL != direktorijum, "Opendir failed.\n");
    struct dirent *entry = NULL;
    while(NULL != (entry = readdir(direktorijum))){
      // napraviti novu adresu
    //  char *newPath = malloc( strlen(fpath) + 1 + strlen(entry->d_name) + 1);
      char newPath[1000];
      osAssert(NULL != newPath, "Malloc failed.\n");
      strcpy(newPath, fpath);
      strcat(newPath, "/");
      strcat(newPath, entry->d_name);
      
      // ako se radi o . ili .. continue
      if(!strcmp(".", entry->d_name) || !strcmp("..", entry->d_name)){
	//free(newPath);
	continue;
      }
      
      //pozvati rekurzivno za newPath
      osMinAndMaxSize(newPath, pathmin, sizemin, pathmax, sizemax);
    // free(newPath);
    }
    closedir(direktorijum);
  }
  
   //ako je regularan fajl, proveriti da li je veci ili manji
  else if(S_ISREG(finfo.st_mode)){
    if(finfo.st_size > *sizemax){
      *sizemax = finfo.st_size;
      strcpy(pathmax, fpath);
    }
    else if(finfo.st_size < *sizemin){
      *sizemin=finfo.st_size;
      strcpy(pathmin, fpath);
    }
  }
}


int main(int argc, char** argv){
  osAssert(2 == argc, osUsage); //ako nije dobar broj arg
  
  struct stat finfo;
  osAssert(-1 != lstat(argv[1], &finfo), "Does not exist.\n"); //ako ne postoji putanja
  osAssert(S_ISDIR(finfo.st_mode), "Not a directory.\n"); //ako nije dir
  
  size_t sizemin, sizemax;
  sizemin=10000;
  sizemax=0;
  char pathmin[1000], pathmax[1000];
  
  osMinAndMaxSize(argv[1], pathmin, &sizemin, pathmax, &sizemax);
  
  printf("Rezulat je %d.\n", sizemax - sizemin);
  
  return 0;
}