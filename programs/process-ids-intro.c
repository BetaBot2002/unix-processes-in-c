#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int id=fork();
    if(id==0) sleep(1); //reason for zombie process
    printf("Current: %d\n",getpid());
    printf("Parent: %d\n",getppid());
    if(id!=0) wait(NULL); //solution for zombie process // wait(NULL) returns the process id for which we waited for , here its the child process
    return 0;
}

/**
 * Step-by-Step Breakdown:
 *
 * 1. Forking:
 *    - The `fork()` system call creates a new child process.
 *    - After `fork()` is called, two processes exist: the parent process and the child process.
 *    - The `id` variable stores the result of `fork()`:
 *      - In the child process, `fork()` returns `0`, so `id == 0`.
 *      - In the parent process, `fork()` returns the PID (Process ID) of the child process.
 *
 * 2. Child Process (id == 0):
 *    - If `id == 0`, the code is running in the child process.
 *    - The child process calls `sleep(1);`, pausing execution for 1 second.
 *
 * 3. Parent Process:
 *    - The parent process does not enter the `if` block, so it does not sleep.
 *    - The parent process immediately continues to the `printf` statements and then terminates.
 *
 * 4. Zombie Process Creation:
 *    - After the parent process terminates, the child process is still sleeping.
 *    - When the child process eventually completes, it becomes a zombie process if the parent
 *      has already terminated.
 *    - A zombie process is created because the child process has finished execution, but its
 *      exit status has not been read by its parent process. Since the parent is no longer
 *      running to call `wait()` or `waitpid()`, the child process remains in the process table as a zombie.
 *
 * 5. Why Zombie Processes Exist:
 *    - Zombie processes allow the parent process to retrieve the exit status of its child process,
 *      even after the child has terminated. If the parent does not call `wait()` or `waitpid()`
 *      to read this status, the process remains a zombie.
 *    - Zombies do not consume CPU or memory (other than a small entry in the process table),
 *      but if many zombies accumulate, they can exhaust system resources by filling up the process table.
 *
 * 6. How to Avoid Zombie Processes:
 *    - A parent process should call `wait()` or `waitpid()` to clean up any zombie child processes.
 *    - This allows the system to remove the child process's entry from the process table.
 */
