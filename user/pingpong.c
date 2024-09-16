#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

#define BUFFER_SIZE 1

int main(void) {
    int parentchild[2]; // Pipe 1 - parent to child ,0 is read, 1 is write
    int childparent[2]; // Pipe 2 - child to parent ,0 is read, 1 is write
    char buffer[BUFFER_SIZE];
    int pid;

    // error checking pipes
    if (pipe(parentchild) < 0 || pipe(childparent) < 0) {
        printf("PIPE FAILED\n");
        exit(1);
    }

    pid = fork(); // making child process

    if (pid < 0) {
        printf("FORK FAILED\n");
        exit(1);
    } //error checking fork

    if (pid == 0) { // Child process block
        // Closing unnecessary ends of our pipes
        close(parentchild[1]); // Close write end of parentchild (parent to child)
        close(childparent[0]); // Close read end of childparent (child to parent)

        // Read from parent (parentchild)
        read(parentchild[0], buffer, BUFFER_SIZE);
        printf("%d child: RECEIVED PING %s \n", getpid(), buffer);
        close(parentchild[0]);

        // Send response to parent (childparent)
        write(childparent[1], buffer, BUFFER_SIZE);
        //printf("child just wrote to pipe \n");
        close(childparent[1]);

        exit(0);
    } else { // Parent process
        // Close unnecessary ends of the pipes
        close(parentchild[0]); // Close read end of parentchild
        close(childparent[1]); // Close write end of childparent

        // Send message to child (parentchild)
        buffer[0] = 'B'; // Dummy data
        write(parentchild[1], buffer, BUFFER_SIZE);
        //printf("parent just wrote to pipe \n");
        close(parentchild[1]);

        // Wait for response from child (childparent)
        read(childparent[0], buffer, BUFFER_SIZE);
        printf("%d parent: RECEIVED PONG %s \n", getpid(),buffer);
        close(childparent[0]);

        // Wait for child process to terminate
        wait(NULL);

        exit(0);
    }
}

