/* fifo - first-in first-out special file, named pipe */
/* Details: https://man7.org/linux/man-pages/man7/fifo.7.html */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

int main(int argv,char** argc){
    char* fifo_path="Files/myFifo1";

    int fifo_status=mkfifo(fifo_path,0777);
    if (fifo_status==-1 && errno!=EEXIST){
        printf("Error while creating fifo\n");
        return 1;
    }else if(errno==EEXIST){
        printf("fifo already exists\n");
    }else{
        printf("fifo created\n");
    }
    
    int file_descriptor = open(fifo_path,O_WRONLY); 
    /*Opening the read or write end of a FIFO blocks until the other 
    end is also opened (by another process or thread)*/
    int data=97;
    char* message="Sinchan Nandy\n";
    write(file_descriptor,message,sizeof(char)*strlen(message));
    write(file_descriptor,&data,sizeof(int));
    close(file_descriptor);
    return 0;
}