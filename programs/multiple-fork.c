#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char** argv){
    int id1=fork();
    int id2=fork();

    /* The following creates 2^10 processes not only 10 processes

        for(int i=0;i<10;i++){
            fork();
        }

    */

    if(id1==0){
        if(id2==0){
            printf("We are in process Y\n");
        }else{
            printf("We are in process X\n");
        }
    }else{
        if(id2==0){
            printf("We are in process Z\n");
        }else{
            printf("We are in process Parent\n");
        }
    }
    return 0;
}