#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    // Create a new process using fork()
    int pid = fork();
    
    if (pid == -1) { // Error while forking
        return 1;
    }

    if (pid == 0) {
        // Child process

        // Open (or create) a file for writing with permissions 0777 (read, write, execute for all)
        int file_descriptor = open("Files/ping_results.txt", O_WRONLY | O_CREAT, 0777);
        if (file_descriptor == -1) {
            return 2;
        }

        // Print a message (this message will still be sent to the terminal because the redirection hasn't happened yet)
        printf("Writing into file....\n");

        // Redirect stdout (file descriptor 1) to the file using dup2
        // This means that any future output to stdout will go to the file
        int fd_duplicate = dup2(file_descriptor, STDOUT_FILENO); // STDOUT_FILENO = 1
        close(file_descriptor);  // Close the original file descriptor

        // Alternative method (commented out) - use a duplicated file descriptor
        // int fd_duplicate = dup(file_descriptor);

        // Commented-out version of printf to demonstrate flushing stdout after redirection:
        // printf("Writing into file.... %d\n", fd_duplicate);
        // fflush(stdout); // Ensure the buffer is flushed to the file

        /*
            Flushing the output buffer using `fflush(stdout)` is crucial before performing an `exec` call.
            This is because `exec` replaces the current process image, and any buffered output might not be written to its destination
            (in this case, the terminal redirected to the file) if it hasn't been flushed.
        */

        int err = execlp("ping", "ping", "-c", "3", "facebook.com", NULL);
        if (err == -1) {
            printf("Could not find program.\n");
            return 3;
        }

    } else {
        // Parent process
        int wait_status;
        wait(&wait_status);

        if (WIFEXITED(wait_status)) {
            int status_code = WEXITSTATUS(wait_status);
            if (status_code == 0) {
                printf("Successful\n");
            } else {
                printf("Failed with code: %d\n", status_code);
            }
        }

        printf("Other Tasks\n");
    }

    return 0;
}
