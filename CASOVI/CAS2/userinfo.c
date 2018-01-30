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

static const char *osUsage = "Usage: ./userinfo username\n"; 

int main(int argc, char** argv){
  osAssert(2 == argc, osUsage);
  struct passwd *user = getpwnam(argv[1]);
  osAssert(NULL != user, "Getpwnam failed.\n");
  
  printf("Username: %s\n", user->pw_name);
  printf("Password: %s\n", user->pw_passwd);
  printf("User ID: %jd\n", (intmax_t)user->pw_uid);
  printf("Group ID: %jd\n", (intmax_t)user->pw_gid);
  printf("User info: %s\n", user->pw_gecos);
  printf("Home directory: %s\n", user->pw_dir);
  printf("Shell program: %s\n", user->pw_shell);
  
  return 0;
}
  