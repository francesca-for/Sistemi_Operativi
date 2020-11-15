#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int main(int argc, const char * argv[]) {
    int fdR, fdW, nR, nW;
    char buf[BUFFER_SIZE];
    
    if(argc!=3){
        fprintf(stderr, "Error: expected 3 parameters: %s oldfile newfile\n", argv[0]);
        exit(-1);
    }
    
    fdR = open(argv[1], O_RDONLY);
    fdW = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP);
    
    if(fdR == -1 || fdW ==-1) {
        fprintf(stderr, "%s: error opening a file\n", argv[0]);
        exit(-1);
    }
    
    while((nR = read(fdR, buf, BUFFER_SIZE)) > 0 ) {
        if((nW = write(fdW, buf, nR)) != nR){
            fprintf(stderr, "Write error: read %d, written %d", nR, nW);
            exit(2);
        }
    }
    if(nR < 0 || nW < 0) {
        fprintf(stderr, "An error occurred during read or writing process\n");
        exit(-2);
    }
    
    close(fdR);
    close(fdW);
    
    return 0;
}
