#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void *T1(){
    fprintf(stdout, "C\n");
    fprintf(stdout, "F\n");
    //sleep(1);
    pthread_exit(NULL);
}

void *T2(){
    //sleep(1);
    fprintf(stdout, "E\n");
    pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
    pthread_t tid1, tid2;
    void * status;
    setbuf(stdout, 0);
    
    fprintf(stdout, "A\n");
    //sleep(1);
    
    if(pthread_create(&tid1, NULL, T1, NULL)!=0){
        fprintf(stderr, "Error creating 1st thread.\n");
        exit(1);
    }
    //sleep(1);
    
    fprintf(stdout, "B\n");
    //sleep(1);
    
    if(pthread_create(&tid2, NULL, T2, NULL)!=0){
        fprintf(stderr, "Error creating 2nd thread.\n");
        exit(1);
    }
    //sleep(1);
    
    fprintf(stdout, "D\n");
    
    pthread_join(tid2, &status);
    pthread_join(tid1, &status);
    
    fprintf(stdout, "G\n");

    return 0;
}
