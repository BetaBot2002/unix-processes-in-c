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

    if (pid==0){
        while(1){
            printf("Message\n");
            custom_usleep(50000); //calling custom_usleep as usleep is deprecated
        }
    }else{
        sleep(1);
        kill(pid,SIGKILL); //Killing a child from parent process
        wait(NULL);
    }
    
    return 0;
}
