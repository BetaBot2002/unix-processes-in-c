#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char** argv){
    int pid=fork();
    if(pid==-1) return 1;

    if (pid==0){
        int err=execlp("ping","ping","-c","3","facebook.com",NULL);
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