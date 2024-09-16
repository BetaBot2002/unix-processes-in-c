#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char** argv){
    int file_descriptors[2];
    int pipe_status=pipe(file_descriptors);

    if(pipe_status==-1){
        printf("Error in creating pipe.\n");
        return 1;
    }

    int id=fork();
    if(id==-1){
        printf("Error in creating fork.\n");
        return 2;
    }

    if(id==0){
        close(file_descriptors[0]);
        int input;
        printf("Enter a number:\n");
        scanf("%d",&input);
        int write_status=write(file_descriptors[1],&input,sizeof(int));
        if(write_status==-1){
            printf("Error in writing.\n");
            return 3;
        }
        close(file_descriptors[1]);
    }else{
        wait(NULL);
        close(file_descriptors[1]);
        int output;
        int read_status=read(file_descriptors[0],&output,sizeof(int));
        if(read_status==-1){
            printf("Error in reading.\n");
            return 4;
        }
        close(file_descriptors[0]);
        printf("Value from child process: %d\n",output);
    }
    return 0;
}