#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

int main(int argv,char** argc){
    char* fifo_path="Files/sum";

    int fifo_status=mkfifo(fifo_path,0777);
    if (fifo_status==-1 && errno!=EEXIST){
        printf("Error while creating fifo\n");
        return 1;
    }else if(errno==EEXIST){
        printf("fifo already exists\n");
    }else{
        printf("fifo created\n");
    }

    int data[]={97,23,45,67,89,70};
    int arr_size=sizeof(data)/sizeof(int);
    int file_descriptor = open(fifo_path,O_WRONLY); 

    write(file_descriptor,&arr_size,sizeof(int));
    printf("Written size: %d\n",arr_size);
    
    for (int i = 0; i < arr_size; i++){
        write(file_descriptor,&data[i],sizeof(int));
        printf("Data Written: %d\n",data[i]);
    }
    
    close(file_descriptor);
    return 0;
}