#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    setbuf(stdout, 0);
    int i, n;
    pid_t pid;
    
    if (argc!=2){
        fprintf(stderr, "Parameters Error\n");
        exit(-1);
    }
    n=atoi(argv[1]);
    
    int *vett = (int*)malloc(n*sizeof(int));
    if(vett==NULL) {
        fprintf(stderr, "Allocation Error\n");
        exit(1);
    }
    fprintf(stdout, "Add vector elements:\n");
    for (i=0; i<n; i++) {
        fscanf(stdin, "%d", &vett[i]);
    }
    
    fprintf(stdout, "Output:\n");
    
    for (i=0; i<n-1; i++){
        pid=fork();
        if(pid==-1) {
            fprintf(stderr, "Fork Error\n");
            exit(2);
        }
        else if(pid>0){   // PADRE
            wait((int *)0);
            break;
        }
    }
    
    fprintf(stdout, "%d ", vett[i]);
    
    exit(0);
}
