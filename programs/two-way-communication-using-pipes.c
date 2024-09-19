#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char** argv){
    int file_descriptor_1[2];
    int file_descriptor_2[2];
    int pipe_status;

    pipe_status=pipe(file_descriptor_1);
    if(pipe_status==-1) return 1;

    pipe_status=pipe(file_descriptor_2);
    if(pipe_status==-1) return 2;

    int pid=fork();
    if(pid==-1) return 3;

    if(pid!=0){
        //Parent Process
        int data=6,result;
        
        close(file_descriptor_1[0]);
        write(file_descriptor_1[1],&data,sizeof(int));
        close(file_descriptor_1[1]);

        close(file_descriptor_2[1]);
        read(file_descriptor_2[0],&result,sizeof(int));
        close(file_descriptor_2[0]);

        printf("Result Read: %d\n",result);
        wait(NULL);
    }else{
        //Child Process
        int data,result;
        
        close(file_descriptor_1[1]);
        read(file_descriptor_1[0],&data,sizeof(int));
        close(file_descriptor_1[0]);

        printf("Data Received: %d\n",data);
        result=data*4;

        close(file_descriptor_2[0]);
        write(file_descriptor_2[1],&result,sizeof(int));
        close(file_descriptor_2[1]);
    }
    return 0;
}