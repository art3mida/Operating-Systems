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


#define osAssert(expr, msg) osAssertImpl(expr, msg, __FILE__, __LINE__)

static inline void osAssertImpl(bool expr, const char *msg, const char *fname, int line){
  if(!expr){
    perror(msg);
    fprintf(stderr, "File: %s, Line: %d\n", fname, line);
    exit(EXIT_FAILURE);
  }
}

static const char *osUsage = "Usage: ./listusers\n"; 

// napravicemo funkciju za ispis podataka jednog korisnika, premotati na pocetak password
// database-a, ispisati za svakod i zatvoriti database

void osPrintUserInfo(struct passwd *user){
  printf("-----------------------");
  printf("Username: %s\n", user->pw_name);
  printf("User password: %s\n", user->pw_passwd);
  printf("User ID: %jd\n", (intmax_t)user->pw_uid);
  printf("Group ID: %jd\n", (intmax_t)user->pw_gid);
  printf("User info: %s\n", user->pw_gecos);
  printf("Home directory: %s\n", user->pw_dir);
  printf("Shell program: %s\n", user->pw_shell);
}

int main(int argc, char** argv){
  osAssert(1 == argc, osUsage);
  struct passwd *user;
  
  setpwent();
  while(NULL != (user = getpwent())){
    osPrintUserInfo(user);
  }
  endpwent();
  
  return 0;
}