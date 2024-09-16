/**
 * wait() - Wait for a child process to change state
 *
 * Description:
 *  The wait() function suspends the execution of the calling process
 *  until one of its child processes changes state. This function is
 *  typically used to wait for a child process to terminate, at which
 *  point the child process's termination status can be retrieved.
 *
 * Parameters:
 *  - int *status: A pointer to an integer where the termination status
 *    of the child process will be stored. If status is not NULL, the
 *    integer pointed to by status will be filled with the child's
 *    termination status.
 *
 * Return Value:
 *  On success:
 *    - The process ID of the child process that changed state is returned.
 *  On failure:
 *    -1 is returned, and errno is set to indicate the error.
 *
 * Notes:
 *  - If the calling process has no child processes, or if all of its
 *    child processes have already terminated, wait() returns immediately.
 *  - The status returned can be inspected using macros defined in
 *    <sys/wait.h>, such as WIFEXITED(), WEXITSTATUS(), WIFSIGNALED(), etc.
 *  - The wait() function can be used to block the parent process until
 *    all of its child processes have terminated.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h> //contains the wait function

int main(int argc,char** argv){
    int pid=fork();
    int n=1;
    if(pid!=0){
        n=6;
        wait(NULL);
    }
    for (int i = n; i < n+5; i++){
        printf("%d ",i);
        fflush(stdout);
    }
    if(pid!=0) printf("\n");
    // printf("\n");
    
    return 0;
}