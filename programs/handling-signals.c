/*IMPORTANT: Manually run this file by ./outpus/handlng-signals to see actual working*/

#define _POSIX_C_SOURCE 200809L //POSIX compliance
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>

void handle_sigtstp(int signal){
    printf("\nStopping not allowed!!\n");
}

int main(int argc,char** argv){
    struct sigaction signal_action;    
    signal_action.sa_handler=&handle_sigtstp;
    signal_action.sa_flags=SA_RESTART;
    sigaction(SIGTSTP,&signal_action,NULL);

    // signal(SIGTSTP,&handle_sigtstp); //Does the same thing but not very potable. Varies across different versions of Linux.

    int value;
    printf("Enter a number: ");
    scanf("%d",&value);
    printf("Result %d+10=%d\n",value,value+10);
    return 0;
}