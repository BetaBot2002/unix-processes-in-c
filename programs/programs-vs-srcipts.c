/*
    `exec` does not run bash commands. It just executes a executable.
    `exec` can only run a single program. It does not handle shell-specific commands like piping (|), 
    which are features of the shell and not part of the individual executable programs.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char** argv){
    int pid=fork();
    if(pid==-1) return 1;

    if (pid==0){
        // int err=execlp("ping","ping","-c","3","facebook.com" , "|", "grep" ,"\"rtt\"",NULL); //This will fail
        //as exec cannot execute shell commands such as piping two programs
        
        int err = execlp("sh", "sh", "-c", "ping -c 3 facebook.com | grep 'rtt'", NULL); //This will run
        //as we are executing the sh program
        if (err==-1){
            printf("Could not find program.\n");
            return 2;
        }
        
    }else{
        int wait_status;
        wait(&wait_status);

        if(WIFEXITED(wait_status)){
            int status_code=WEXITSTATUS(wait_status);
            if(status_code==0){
                printf("Sucessful\n");
            }else{
                printf("Failed with code: %d\n",status_code);
            }
        }

        printf("Other Tasks\n");

    }
    
    return 0;
}