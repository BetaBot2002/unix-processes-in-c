/*
    Parallel Sum of elements of an array.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char** argv){
    int numbers[]={1,2,3,4,5,6,7,8,9,10};
    int arr_size=sizeof(numbers)/sizeof(int);
    int start,end;

    int file_descriptors[2];
    int pipe_status=pipe(file_descriptors);
    if(pipe_status==-1) return 1;

    int id=fork();
    if(id==-1) return 2;

    if(id==0){
        start=0;
        end=arr_size/2;
    }else{
        start=arr_size/2;
        end=arr_size;
    }

    int sum=0;
    for (int i = start; i < end; i++){
        sum+=numbers[i];
    }

    if(id==0){
        close(file_descriptors[0]);
        write(file_descriptors[1],&sum,sizeof(int));
        close(file_descriptors[1]);
    }else{
        int sum_from_child=0;
        close(file_descriptors[1]);
        read(file_descriptors[0],&sum_from_child,sizeof(int));
        close(file_descriptors[0]);

        printf("Total Sum: %d\n",sum+sum_from_child);
        wait(NULL);
    }
    
    return 0;
}