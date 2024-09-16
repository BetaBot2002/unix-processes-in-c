/**
 * fork() - Create a new process (child process)
 *
 * Description:
 *  The fork() function is used to create a new process by duplicating
 *  the calling (parent) process. The newly created process is known as
 *  the child process. Both the parent and the child processes continue
 *  execution from the next instruction following the fork() call.
 *
 * Return Value:
 *  On success:
 *    - 0 is returned to the child process.
 *    - The child's PID (Process ID) is returned to the parent process.
 *  On failure:
 *    -1 is returned, and no child process is created.
 *
 * Notes:
 *  - The child process is an exact copy of the parent process, except for the
 *    following differences:
 *    - The child process has a unique process ID.
 *    - The child process has its own copy of the parent's file descriptors.
 *    - The return value of fork() differs between the parent and the child.
 */


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>  //linux specific and contains the fork function

int main(int argc,char** argv){
    printf("Hello World\n");

    int pid=fork();
    printf("Hello World From PID:%d\n",pid);

    if(pid==0) printf("Child\n");

    return 0;
}