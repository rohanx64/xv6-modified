#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>


int main(void) {
  int pid = fork();  // Create a new process

  if (pid < 0) {
        // Fork failed
        printf("Fork failed\n");
        exit(1);
  }
  getnumofsyscall();
  if (pid == 0) {
        // This is the child process
        char *args[] = { "SSS", 0 };  // Arguments for the exec call (no arguments in this case)
        exec("SSS", args);  // Replace child process with the sss program
        printf("exec failed\n");  // Only runs if exec fails
        exit(1);
    } else {
        wait(0);
        printf("%d \n",getnumofsyscall()-1);  
    }
  exit(0);  // Both parent and child processes will call exit()
}

