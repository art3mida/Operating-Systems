#define _XOPEN_SOURCE 700

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 
#include <pwd.h>
#include <grp.h>
#include <time.h>


#define ACCESS_BUFF 11
#define osAssert(expr, msg) osAssertImpl(expr, msg, __FILE__, __LINE__)

static inline void osAssertImpl(bool expr, const char *msg, const char *fname, int line){
  if(!expr){
    perror(msg);
    fprintf(stderr, "File: %s, Line: %d\n", fname, line);
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./fileinfo fpath\n"; 

// struct stat finfo ---> stat(fpath, &finfo);
// sa funkcijom stat dohvatamo informacije o fajlu, i smestamo ih u struct stat finfo
// sa makroima koji su navedeni proveravamo koji je od 7 tipova fajla nas fajl, i to 
// nam je prvi karakter u stringu
// karakteri 1-9 nam govore o privilegijama, po tri za redom user, grupa i others privilegije
// nakon toga ispisujemo i broj simbolickih linkova, ime vlasnika, vlasnicku grupu
// velicinu fajla i vreme poslednje promene

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  struct stat finfo;
  osAssert(-1 != stat(argv[1], &finfo), "Stat failed.\n");
  const mode_t defaultMode = 0666;
  
 // int fd = open(argv[1], O_RDONLY, defaultMode);
  char access[ACCESS_BUFF];
  
  if(S_ISREG(finfo.st_mode)) { access[0] = '-'; }
  else if(S_ISDIR(finfo.st_mode)) { access[0] = 'd'; }
  else if(S_ISCHR(finfo.st_mode)) { access[0] = 'c'; }
  else if(S_ISBLK(finfo.st_mode)) { access[0] = 'b'; }
  else if(S_ISFIFO(finfo.st_mode)) { access[0] = 'p'; }
  else if(S_ISLNK(finfo.st_mode)) { access[0] = 'l'; }
  else if(S_ISSOCK(finfo.st_mode)) { access[0] = 's'; }
  
  access[1]= (finfo.st_mode & S_IRUSR) ? 'r' : '-';
  access[2]= (finfo.st_mode & S_IWUSR) ? 'w' : '-';
  access[3]= (finfo.st_mode & S_IXUSR) ? 'x' : '-';
  
  access[4]= (finfo.st_mode & S_IRGRP) ? 'r' : '-';
  access[5]= (finfo.st_mode & S_IWGRP) ? 'w' : '-';
  access[6]= (finfo.st_mode & S_IXGRP) ? 'x' : '-';
  
  access[7]= (finfo.st_mode & S_IROTH) ? 'r' : '-';
  access[8]= (finfo.st_mode & S_IWOTH) ? 'w' : '-';
  access[9]= (finfo.st_mode & S_IXOTH) ? 'x' : '-';
  
  printf("Privileges: %s\nNumber od symbolic link: %d\n", access, finfo.st_nlink);
  
  struct passwd *user = getpwuid(finfo.st_uid);
  osAssert(NULL != user, "Getpwuid failed.\n");
  printf("Username: %s\n", user->pw_name);
  
  struct group *usergroup = getgrgid(finfo.st_gid);
  osAssert(NULL != user, "Getgrgid failed.\n");
  printf("Group: %s\n", usergroup->gr_name);
  
  printf("Size: %jd\n", (intmax_t)finfo.st_size);
  printf("Time of last change: %s\n", ctime(&finfo.st_ctime));
  
  return 0;
}
  
  
  
  
  
