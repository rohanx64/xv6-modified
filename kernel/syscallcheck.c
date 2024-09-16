#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    
    // Call the custom system call to get the count of system calls
    getnumofsyscall();
    int count = getnumofsyscall();
    printf("Total number of system calls made: %d\n", count);

    exit(0);
}
