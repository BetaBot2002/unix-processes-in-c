#define _POSIX_C_SOURCE 200809L //POSIX compliance for nanosleep
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<signal.h>

void custom_usleep(unsigned int microseconds){
    struct timespec req;

    // Convert microseconds to seconds and nanoseconds
    req.tv_sec = microseconds / 1000000;          // Whole seconds
    req.tv_nsec = (microseconds % 1000000) * 1000; // Remaining microseconds converted to nanoseconds

    // Call nanosleep with the required time
    nanosleep(&req,NULL);
}

int main(int argc,char** argv){
    int pid=fork();
    if(pid==-1) return 1;

    if(pid==0){
        int i=0;
        while (1){
            printf("Message %d\n",++i);
            custom_usleep(50000);
        }
        
    }else{
        kill(pid,SIGSTOP);

        int t;
        do{
            printf("Enter the time for execution in seconds: ");
            scanf("%d",&t);

            if(t>0){
                kill(pid,SIGCONT);
                sleep(t);
                kill(pid,SIGSTOP);
            }
        }while(t>0);
        
        kill(pid,SIGKILL);
        wait(NULL);
    }
    return 0;
}