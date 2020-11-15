#include <stdlib.h>
#include <stdio.h>
#define MAX_LENGHT 200
#define DIM 2048

int main(int argc, const char * argv[]) {
    FILE *fps;
    FILE *fpd;
    char buf[MAX_LENGHT];
    
    if(argc!=3){
        fprintf(stderr, "Error: expected 3 parameters\n");
        exit(1);
    }
    
    if((fps=fopen(argv[1], "r"))==NULL){
        fprintf(stderr, "Error: opening source file\n");
        exit(-1);
    }
    
    if((fpd=fopen(argv[2], "w"))==NULL){
        fprintf(stderr, "Error: opening destination file\n");
        exit(-1);
    }
    
    while((fgets(buf, MAX_LENGHT, fps))!=NULL) {
        fprintf(fpd, "%s", buf);
    }
    
    fclose(fps);
    fclose(fpd);
    
    return 0;
}
