/**
 * The exec family of functions in Unix-based operating systems (such as Linux) 
 * is used to replace the current process image with a new one. This means the 
 * process that calls exec stops executing its current program and starts 
 * executing a new program, as specified by the exec function.
 *
 * What Does exec Do?
 *
 *  - When a process calls exec, it completely replaces the current process image 
 *    (code, data, stack, etc.) with a new program. The new program runs in the 
 *    same process, meaning it retains the same process ID (PID), environment 
 *    variables, file descriptors, and other attributes of the original process.
 *
 *  - The original program’s instructions and data are discarded.
 *
 *  - exec is commonly used after a process has forked (using fork()) to run a 
 *    different program in the child process.
 *
 * Common Functions in the exec Family:
 *
 * 1. **execl()**:
 *    - Accepts a list of arguments, ending with NULL. Requires the full path 
 *      to the executable.
 *
 * 2. **execlp()**:
 *    - Similar to execl(), but it searches for the executable in the directories 
 *      listed in the PATH environment variable.
 *
 * 3. **execv()**:
 *    - Takes an array of arguments rather than a list. Requires the full path 
 *      to the executable.
 *
 * 4. **execvp()**:
 *    - Like execv(), but it searches for the executable in the directories 
 *      listed in the PATH.
 *
 * 5. **execve()**:
 *    - The most low-level function in the exec family. It takes an array of 
 *      arguments and an array of environment variables. It requires the full 
 *      path to the executable.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int main(int argc,char** argv){
    // execl("/bin/ping","ping","-c","3","google.com",NULL); //Takes full path of the program 
    execlp("ping","ping","-c","3","google.com",NULL); // Searches PATH to find program alias

    // Following lines will only execute if exec fails
    int err=errno;
    printf("Error: %d\n",err);
    return 0;
}

/**
 * After an `exec` function (like `execl`, `execlp`, `execvp`, etc.) is called 
 * in a program, the current process is completely replaced by the new program 
 * specified in the `exec` call. This means the original code that follows the 
 * `exec` call will not be executed because the process has now become the new 
 * program.
 *
 * What Happens When `exec` is Called:
 *
 * 1. **Process replacement**: 
 *    The `exec` family of functions replaces the current process image with a 
 *    new process image. This means the currently running program is overwritten 
 *    by the new program specified in the `exec` call.
 *
 * 2. **No return on success**: 
 *    If the `exec` call is successful, it never returns. The lines of code after 
 *    the `exec` call are not executed because the current process is no longer 
 *    running; it's been replaced by the new process.
 *
 * 3. **Return on failure**: 
 *    If `exec` fails (e.g., the executable is not found or cannot be run), 
 *    the function returns `-1`, and the lines after the `exec` call are executed.
 */
