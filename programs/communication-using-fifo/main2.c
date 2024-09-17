#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

int main(int argc,char** argv){
    char* fifo_path="Files/sum";
    int arr_size;

    int file_descriptor = open(fifo_path,O_RDONLY); 

    read(file_descriptor,&arr_size,sizeof(int));
    printf("Read size: %d\n",arr_size);

    int* data=(int*)malloc(arr_size*sizeof(int));
    for (int i = 0; i < arr_size; i++){
        read(file_descriptor,&data[i],sizeof(int));
        printf("Data Read: %d\n",data[i]);
    }
    close(file_descriptor);
    return 0;
}